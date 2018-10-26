#include <linux/module.h>
#include <linux/netdevice.h>
#include <linux/device.h>
#include <linux/kernel.h>
#include <linux/interrupt.h>
#include <linux/skbuff.h>
#include <linux/spinlock.h>
#include <linux/string.h>
#include <net/sock.h>
#include <net/netlink.h>
#include <linux/if_ether.h>
//#include "srio.h"
#include <net/net_namespace.h>

MODULE_AUTHOR("xiejiawu_nL");
MODULE_LICENSE("GPL");
typedef	struct sk_buff  SRIO_PKT;
#define SRIO 0xf4f7
#define SRIO_CORE_OPEN	0
#define SRIO_EXEC_SUCC	0
#define MAX_STORED_PKT	100
#define NETLINK_TEST    21
#define NL_DEST_PID 100
#define	CORE_CLOSED	0
#define CORE_OPENED	1
#define		IOCKERNEL			SIOCDEVPRIVATE

//------------------------functions declaration---------------------------//
static DEFINE_MUTEX(nl_srio_mutex);
void nl_recfromuser(struct sk_buff *skb);
int nl_sendtouser(struct sk_buff *skb);
int core_netlink_init(void);
void netlink_release(void);
//void nl_send_packet_pending(struct sk_buff *skb);
int nl_sendtodriver(struct sk_buff *skb, struct nlmsghdr *nlh);

int srio_open(struct net_device *dev);
int srio_close(struct net_device *dev);
struct net_device_stats *srio_dev_get_stats(struct net_device *dev);
int srio_dev_set_config(struct net_device *dev, struct ifmap *p_ifmap);//define but not use cause unneccesary
int srio_dev_ioctl(struct net_device *dev, struct ifreq *ifr, int cmd);
int srio_tx(struct sk_buff *skb, struct net_device *dev);
void srio_send_packet_pending(SRIO_PKT *pkptr, struct net_device *dev, u16 protocol);
void srio_send_packet(unsigned long data);
void srio_tx_time_out(struct net_device *dev);
void srio_sendtouser(unsigned long data);
void srio_rx_pending(SRIO_PKT *pkptr, struct net_device *dev, u16 protocol);
int srio_recv(struct sk_buff *skb, struct net_device *dev1, struct packet_type *pktype, struct net_device *dev2);
void dev_init(struct net_device *dev);
int srio_init_module(void);
void srio_release (void);
//-----------------------------------------------------------------------//
struct sock *nl_sk = NULL;
struct netlink_kernel_cfg cfg =
{
    .input  = nl_recfromuser,
    .cb_mutex = &nl_srio_mutex,
};
struct packet_type pk_t =
{
    .type = __constant_htons(SRIO),
    .func = srio_recv,
};
typedef struct SRIO_CORE
{
    int state;
    void *dev;
    SRIO_PKT *pkptr;
    spinlock_t 		lock;		//lock the core
    struct sk_buff_head	*tx_queue;
    struct sk_buff_head	*rx_queue;
    struct sk_buff_head	*nl_tx_queue;  //try
    struct tasklet_struct	*tx_tsklt;
    struct tasklet_struct 	*rx_tsklt;
    //struct tasklet_struct* 	nl_tx_tsklt;
    //struct tasklet_struct*  do_ioctl_tsklt;
    spinlock_t		tx_queue_lock;		//lock the pending tx queue
    spinlock_t		rx_queue_lock;
    //spinlock_t		nl_tx_queue_lock;
    void *dev_eth;

} SRIO_CORE;
typedef struct handover_trigger_msg{
	uint8_t flag;
}Handover_Trigger_Msg;
static SRIO_CORE srio_core;

const struct net_device_ops srio_netdev_ops =
{
    .ndo_open = srio_open,
    .ndo_stop = srio_close,
    .ndo_start_xmit = srio_tx,
    .ndo_get_stats = srio_dev_get_stats,
    .ndo_do_ioctl = srio_dev_ioctl,
    .ndo_set_config = srio_dev_set_config,
    .ndo_tx_timeout = srio_tx_time_out,
};

typedef struct srio_sv
{
    int packet_count;
    int recv_count;
    unsigned int interval;
    bool racomplete;
    u16 sfn;
    u16 subframeN;
    SRIO_PKT *pkts[MAX_STORED_PKT];//for 5ms send to srio test
    u16 stored_pkt_count;//for 5ms send to srio test
    u32 recv_upper_pkt_num;
    u32 recv_pkt_from_enb;
    char *mem_zero;
    u32 pre_pkt_no;
    u32 recv_interval;
    u32 send_interval;
    u32 lost_pkt_count;
    u32 send_count;
    u32 recvFromUp;
    u32 sendToLower;
    //u32 sendToDsp;
} srio_sv;//define here but not use yet
typedef struct srio_priv
{
    struct net_device_stats stats;
    srio_sv *srio_sv_ptr;
} srio_priv;//define here but not use yet
u32 sendToDSP;
//-----------------------------------------------------------------------//
struct net_device_stats *srio_dev_get_stats(struct net_device *dev)
{
    srio_priv *priv;
    priv = (srio_priv *)netdev_priv(dev);
    return &(priv->stats);
}
int srio_dev_set_config(struct net_device *dev, struct ifmap *p_ifmap)
{
    return 0;
}

int srio_open(struct net_device *dev)
{
    unsigned long flags;
    srio_core.dev_eth = dev_get_by_name(&init_net, "eth0"); //transmix data to eth driver
    netif_start_queue(dev);
    //pk_t.dev=dev_get_by_name(&init_net,"eth0");
    dev_add_pack(&pk_t);
    //srio_core open
    if(srio_core.state == CORE_CLOSED)
    {
        spin_lock_irqsave(&srio_core.lock, flags);
        //Initialize queues
        skb_queue_head_init(srio_core.tx_queue);
        skb_queue_head_init(srio_core.rx_queue);
        spin_lock_init(&srio_core.tx_queue_lock);
        spin_lock_init(&srio_core.rx_queue_lock);
        //Initialize tasklets
        tasklet_init(srio_core.tx_tsklt, srio_send_packet, 0);
        tasklet_init(srio_core.rx_tsklt, srio_sendtouser, 0);
        //tasklet_init(srio_core.nl_tx_tsklt, nl_sendtodriver, 0);
        srio_core.state = CORE_OPENED;
        spin_unlock_irqrestore(&srio_core.lock, flags);
        printk("core has opened.\n");
    }

    return SRIO_CORE_OPEN;
}
int srio_close(struct net_device *dev)
{
    unsigned long flags;
    if(srio_core.state == CORE_CLOSED)
        return SRIO_EXEC_SUCC;
    spin_lock_irqsave(&srio_core.lock, flags);
    tasklet_kill(srio_core.tx_tsklt);
    tasklet_kill(srio_core.rx_tsklt);
    if (srio_core.dev_eth)
    {
        dev_put(srio_core.dev_eth);
    }
    while(!skb_queue_empty(srio_core.tx_queue))
    {
        kfree_skb(skb_dequeue(srio_core.tx_queue));
    }
    srio_core.state = CORE_CLOSED;
    spin_unlock_irqrestore(&srio_core.lock, flags);
    dev_remove_pack(&pk_t);
    netif_stop_queue(dev);
    return SRIO_EXEC_SUCC;
}
int srio_dev_ioctl(struct net_device *dev, struct ifreq *ifr, int cmd)
{
    //struct kifreq* kifr_ptr;
    if(cmd == IOCKERNEL)
    {
        //kifr_ptr = (struct kifreq*)ifr;
        //switch(kifr_ptr->cmd)
        //{
        //case PRINT:

        printk("recvFromUp:%d\n", sendToDSP);
        //printk("sendToLower:%d\n",srio_sv->sendToLower);
        //printk("sendtodsp: %d\n",srio_sv->sendToDSP);
        //break;
        //default:
        //printK("SRIO:Unrecognized I/O control command.\n");
        //}
    }
    return 0;
}
int srio_tx(SRIO_PKT *pkptr, struct net_device *dev)
{
    /**
     * 定义源、目的MAC，获取接收的skb_buff数据长度，分配一个新的sk_buff缓冲区ptr_cpy，长度为以太网帧头部+收到的数据长度
     * 将pkptr中的data部分拷贝到新建的sk_buff,并将源、目的mac地址通过memcpy封装到ptr_cpy中，调用srio发送等待函数
     */
    //unsigned long flags2;
    unsigned int size;
    //int erro;
    //SRIO_PKT* ptr;
    SRIO_PKT *ptr_cpy;
    struct ethhdr *head_ptr;
    char dst_addr[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
    char sour_addr[6] = {0x00, 0x1c, 0x42, 0x37, 0x46, 0x68}; //:6a:25:43
    size = pkptr->len;
    ptr_cpy = (SRIO_PKT *) dev_alloc_skb(size + sizeof(struct ethhdr));
    if(ptr_cpy == NULL)
    {
        srio_close(srio_core.dev);
        printk("[send]something wrong with allocate skb!\n");
    }
    memset(ptr_cpy->head, 0, size + sizeof(struct ethhdr));
    skb_put(ptr_cpy, size);
    memcpy(ptr_cpy->data, pkptr->data, size);

    if (ptr_cpy != NULL)
    {

        skb_push(ptr_cpy, ETH_HLEN);
        head_ptr = (struct ethhdr *)ptr_cpy->data;
        memcpy(head_ptr->h_dest, dst_addr, ETH_ALEN);
        memcpy(head_ptr->h_source, sour_addr, ETH_ALEN);
        head_ptr->h_proto = htons(SRIO);
        srio_send_packet_pending(ptr_cpy, srio_core.dev_eth, SRIO);
        return 0;
    }
    printk("[send]NOTHING TO SEND \n");
    return 0;
}
//wait to send to eth when receive from netlink
void srio_send_packet_pending(SRIO_PKT *pkptr, struct net_device *dev, u16 protocol)
{
    struct sk_buff *skb;
    unsigned long flags;
    skb = (struct sk_buff *)pkptr;
    skb->dev = srio_core.dev_eth;
    skb->protocol = htons(protocol);
    spin_lock_irqsave(&srio_core.tx_queue_lock, flags);
    skb_queue_tail(srio_core.tx_queue, pkptr);
    spin_unlock_irqrestore(&srio_core.tx_queue_lock, flags);
    tasklet_schedule(srio_core.tx_tsklt);
    return;
}
//send to eth by netlink after pending
void srio_send_packet(unsigned long data)
{

    SRIO_PKT *pkptr;
    unsigned long flags;
    int ret;
    while(1)
    {
        spin_lock_irqsave(&srio_core.tx_queue_lock, flags);
        if(skb_queue_empty(srio_core.tx_queue))
        {
            spin_unlock_irqrestore(&srio_core.tx_queue_lock, flags);
            break;
        }
        else
        {
            pkptr = skb_dequeue(srio_core.tx_queue);
            spin_unlock_irqrestore(&srio_core.tx_queue_lock, flags);
            ret = dev_queue_xmit(pkptr);
            sendToDSP++;
            if (ret != 0)
            {
                srio_close(srio_core.dev);
                printk(" srio send to eth fail \n");
            }
        }
    }

    return;
}


void srio_tx_time_out(struct net_device *dev)
{
    return;
}
//wait to send to uplayer when receive from eth
void srio_rx_pending(SRIO_PKT *pkptr, struct net_device *dev, u16 protocol)
{
    struct sk_buff *skb;
    unsigned long flags;
    skb = (struct sk_buff *)pkptr;
    skb->protocol = htons(protocol);
    skb->dev = dev;
    if(skb->protocol == htons(ETH_P_IP))
    {
        skb->ip_summed = CHECKSUM_UNNECESSARY;
    }


    //skb的队列管理函数，在尾部插入队列，其实就是将

    spin_lock_irqsave(&srio_core.rx_queue_lock, flags);
    skb_queue_tail(srio_core.rx_queue, pkptr);
    spin_unlock_irqrestore(&srio_core.rx_queue_lock, flags);
    tasklet_schedule(srio_core.rx_tsklt);


    return;
}
//send to uplayer by netlink after pending
void srio_sendtouser(unsigned long data)
{
    SRIO_PKT *pkptr;
    unsigned long flags;


    while(1)
    {
        spin_lock_irqsave(&srio_core.rx_queue_lock, flags);
        if(skb_queue_empty(srio_core.rx_queue))
        {

            spin_unlock_irqrestore(&srio_core.rx_queue_lock, flags);
            break;
        }
        else
        {
            pkptr = skb_dequeue(srio_core.rx_queue);
            spin_unlock_irqrestore(&srio_core.rx_queue_lock, flags);
            nl_sendtouser(pkptr);
        }
    }
    return;
}
int srio_recv(SRIO_PKT *pkptr, struct net_device *dev1, struct packet_type *pktype, struct net_device *dev2)
{
    //unsigned long flags;
    SRIO_PKT *ptr_cpy;
    int size;
    size = pkptr->len;
    ptr_cpy = (SRIO_PKT *) dev_alloc_skb(size);
    if(ptr_cpy == NULL)
    {
        srio_close(srio_core.dev);
        printk("[rec]something wrong with allocate skb!\n");
    }
    memset(ptr_cpy->head, 0, size);
    skb_put(ptr_cpy, size);
    memcpy(ptr_cpy->data, pkptr->data, size);
    dev_kfree_skb(pkptr);
    if (ptr_cpy != NULL)
    {
        srio_rx_pending(ptr_cpy, srio_core.dev, SRIO);

        return 0;
    }
    //spin_unlock_irqrestore(&srio_core.lock ,flags);
    return 0;
}

void dev_init(struct net_device *dev)
{
    srio_priv *priv;
    //dev->init=devinti;
    dev->tx_queue_len = 128;   			/* the queue length */
    dev->mtu = 1500;					/* now we do not fragmentate the packet */
    dev->header_ops = 0;   		/* cancle eth_header function for not building ethnet mac header */
    dev->addr_len = 0;
    dev->hard_header_len = 0;
    dev->watchdog_timeo = 1000;  				/* the time unit is jiffy */
    dev->flags = IFF_BROADCAST | IFF_MULTICAST | IFF_NOARP;
    dev->netdev_ops = &srio_netdev_ops;
    core_netlink_init();
    //dev->features |= NETIF_F_NO_CSUM;
    priv = (srio_priv *)netdev_priv(dev);
    memset(priv, 0, sizeof(srio_priv));
    //init srio_core
    spin_lock_init(&srio_core.lock);
    srio_core.tx_queue = (struct sk_buff_head *)kmalloc(sizeof(struct sk_buff_head), GFP_ATOMIC);
    srio_core.rx_queue = (struct sk_buff_head *)kmalloc(sizeof(struct sk_buff_head), GFP_ATOMIC);
    srio_core.tx_tsklt = (struct tasklet_struct *)kmalloc(sizeof(struct tasklet_struct), GFP_ATOMIC);
    srio_core.rx_tsklt = (struct tasklet_struct *)kmalloc(sizeof(struct tasklet_struct), GFP_ATOMIC);
    srio_core.dev = dev;
    srio_core.dev_eth = 0;
    srio_core.pkptr = 0;
    priv->srio_sv_ptr = kmalloc(sizeof(srio_sv), GFP_ATOMIC);
    memset(priv->srio_sv_ptr, 0, sizeof(srio_sv));
    srio_core.state = CORE_CLOSED;

    return ;
}
int srio_init_module(void)
{
    srio_priv *priv;
    const char  *name = "SRIO%d";
    char dev_addr[6] = {0x00, 0x1c, 0x42, 0x37, 0x46, 0x68};
    struct net_device *dev = NULL;
    dev = alloc_netdev(sizeof(srio_priv), name, NET_NAME_UNKNOWN, dev_init);
    if (dev == NULL)   /* allocation error */
    {
        return -1;
    }
    memcpy(dev->dev_addr, &dev_addr, 6);
    /* ---------ADD some private data into the net_device struct */
    priv = netdev_priv(dev);
    if (priv == NULL)
    {
        return -2;
    }
    /* register the net device */
    if (register_netdev(dev))    /* register error */
    {
        free_netdev(dev);   /* release the struct net_device */
        dev = NULL;
        printk("register failled\n") ;
        return -3;
    }
    //printk("register success\n");
    return 0;
}
void srio_release (void)
{
    //struct net_device* dev;
    srio_priv *priv;
    unsigned long flags;
    if(srio_core.state != CORE_CLOSED)
    {
        spin_lock_irqsave(&srio_core.lock, flags);
        tasklet_kill(srio_core.tx_tsklt);
        tasklet_kill(srio_core.rx_tsklt);
        if (srio_core.dev_eth)
        {
            dev_put(srio_core.dev_eth);
        }
        while(!skb_queue_empty(srio_core.tx_queue))
        {
            kfree_skb(skb_dequeue(srio_core.tx_queue));
        }
        while(!skb_queue_empty(srio_core.rx_queue))
        {
            kfree_skb(skb_dequeue(srio_core.rx_queue));
        }
        srio_core.state = CORE_CLOSED;
        spin_unlock_irqrestore(&srio_core.lock, flags);
        // netif_stop_queue(srio_core.dev);
        // dev_remove_pack(&pk_t);

    };
    priv = netdev_priv(srio_core.dev);
    kfree(priv->srio_sv_ptr);
    kfree(srio_core.tx_queue);
    kfree(srio_core.rx_queue);
    kfree(srio_core.nl_tx_queue);
    kfree(srio_core.tx_tsklt);
    kfree(srio_core.rx_tsklt);
    unregister_netdev(srio_core.dev);
    free_netdev(srio_core.dev);
    netlink_release();
}
//--------------------------------netlink----------------------------//
void nl_recfromuser(struct sk_buff *skb)
{
    if(skb && nl_sk)
    {
        struct nlmsghdr *nlh ;
        Handover_Trigger_Msg *handover_trigger_msg=(Handover_Trigger_Msg *)kmalloc(sizeof(Handover_Trigger_Msg), GFP_ATOMIC);
        nlh = nlmsg_hdr(skb);
        memcpy(handover_trigger_msg, NLMSG_DATA(nlh), sizeof(Handover_Trigger_Msg));
        printk(KERN_INFO "received Handover_Trigger_Msg form USER , the flag is %d\n",handover_trigger_msg->flag);
        kfree(handover_trigger_msg);
        mutex_lock(&nl_srio_mutex);
        netlink_rcv_skb(skb, &nl_sendtodriver);
        mutex_unlock(&nl_srio_mutex);

    }
}
/*void nl_send_packet_pending(struct sk_buff *skb)
  {

  unsigned long flags;
  skb->dev=srio_core.dev;
  skb->protocol = htons(SRIO);
  spin_lock_irqsave(&srio_core.nl_tx_queue_lock, flags);
  skb_queue_tail(srio_core.nl_tx_queue, skb);
  spin_unlock_irqrestore(&srio_core.nl_tx_queue_lock, flags);
  tasklet_schedule(srio_core.nl_tx_tsklt);

  return;
  }*/
int nl_sendtodriver(struct sk_buff *skb, struct nlmsghdr *nlh)
{
    if(skb)
    {
        struct nlmsghdr *nlh ;
        Handover_Trigger_Msg *handover_trigger_msg=(Handover_Trigger_Msg *)kmalloc(sizeof(Handover_Trigger_Msg), GFP_ATOMIC);
        nlh = nlmsg_hdr(skb);
        memcpy(handover_trigger_msg, NLMSG_DATA(nlh), sizeof(Handover_Trigger_Msg));
        printk(KERN_INFO "received Handover_Trigger_Msg form USER , the flag is %d\n",handover_trigger_msg->flag);
        kfree(handover_trigger_msg);
        srio_tx(skb, srio_core.dev);
        //kfree_skb(skb);
        return 0;
    }
    //printk("[kernel SKB IS NULL\n");
    return 0;
}
// send data to user by netlink
int nl_sendtouser(struct sk_buff *skb)
{

    int len;
    int status;
    struct nlmsghdr *nlh1;
    struct sk_buff *nl_skb;
    struct nlmsghdr *nlh;
    struct nlmsghdr *nl_hdr;
    if (skb)
    {
        //mutex_lock(&nl_srio_mutex);

        nl_hdr = nlmsg_hdr(skb);
        printk(KERN_INFO "\n Message received from eNB handover module : %s\n", (char *)NLMSG_DATA(nl_hdr));
        nlh1 = (struct nlmsghdr *)skb->data;
        len = nlh1->nlmsg_len;

        nl_skb = alloc_skb(NLMSG_SPACE(len), GFP_ATOMIC);
        printK("[HANDOVER SRIO] NLMSG_SPACE(len):%d",NLMSG_SPACE(len));
        nlh = (struct nlmsghdr *)nl_skb->data;
        skb_put(nl_skb, NLMSG_SPACE(len));
        memcpy(NLMSG_DATA(nlh), NLMSG_DATA(nlh1), len);

        nlh->nlmsg_len = NLMSG_SPACE(len);
        nlh->nlmsg_pid = 0;
        NETLINK_CB(nl_skb).portid = 0;
        kfree_skb(skb);
        if(nlh == NULL)
        {
            printk("[kernel netlink]nlmsg_put failure! \n");
            nlmsg_free(nl_skb);
            return -1;
        }
        //mutex_lock(&nl_srio_mutex);
        status = netlink_unicast(nl_sk, nl_skb, NL_DEST_PID, MSG_DONTWAIT);
        //mutex_unlock(&nl_srio_mutex);
        if (status < 0)
        {
            printk("[kernel NETLINK] SEND status is %d\n", status);
            return 0;
        }
        else
        {

            printk("[NETLINK] SEND status is %d\n", status);
            return len;
        }
    }
    //printk("[send to user] nothing send to user\n");
    return 0;
    //mutex_unlock(&nl_srio_mutex);

}

//creat kernel netlink
int core_netlink_init(void)
{
    nl_sk = netlink_kernel_create(&init_net, NETLINK_TEST, &cfg);

    if (!nl_sk)
    {
        printk(KERN_ERR "net_link: Cannot create netlink socket.\n");
        return -1;
    }
    printk(KERN_INFO "Handover kernel module start successfully!\n");
    return 0;
}
//netlink release
void netlink_release(void)
{

    printk("Handover  kernel module exits!\n");
    if(nl_sk)
    {
        netlink_kernel_release(nl_sk);

    }

}
module_init(srio_init_module);
module_exit(srio_release);

