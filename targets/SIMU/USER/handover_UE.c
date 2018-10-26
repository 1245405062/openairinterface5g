
/*--------------------------------------only for using socket---------------------------------*/
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <linux/netlink.h>
#include <libconfig.h>
#include <sys/select.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <netinet/in.h>
#include <ifaddrs.h>

/*--------------------------------------only for using sem--------------------------------------*/

#include <semaphore.h>
#include <oaisim.h>

/*---------------------------------------only for using pthread---------------------------------*/
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>

/*----------------------------------------for error check---------------------------------------*/
#include <errno.h>


#include "assertions.h"


/*---------------------------------------for RRCConnection -------------------------------------*/
#include "intertask_interface.h"
#include  "timer.h"
#    include "s1ap_eNB.h"
#    include "sctp_eNB_task.h"
#    include "gtpv1u_eNB_task.h"
#include "LAYER2/PDCP_v10.1.0/pdcp.h"
#include "LAYER2/PDCP_v10.1.0/pdcp_primitives.h"
#include "UTIL/LISTS/list.h"
#include "UTIL/MEM/mem_block.h"
#include "LAYER2/MAC/defs.h"
#include "RRC/LITE/extern.h"

#include "COMMON/rrc_messages_types.h"
#include "handover_UE.h"



void *handover_ue_task(void *args_p)
{
    itti_mark_task_ready(TASK_HANDOVER_UE);
    //init recv_msg
    
    memset(&handover_ue_config_t.msg_recv, 0, sizeof(struct msghdr));
    memset(&handover_ue_config_t.iov_recv, 0, sizeof(struct iovec));
    memset(&handover_ue_config_t.addr_recv, 0, sizeof(struct sockaddr_nl));
    handover_ue_config_t.hdr_recv = (struct nlmsghdr *)malloc(NLMSG_SPACE(MSG_MAX_SIZE));
    handover_ue_config_t.addr_recv.nl_family = AF_NETLINK;
    handover_ue_config_t.addr_recv.nl_pid = PID_RECV;
    handover_ue_config_t.addr_recv.nl_pad = 0;
    handover_ue_config_t.addr_recv.nl_groups = 0;
    handover_ue_config_t.sock_recv = socket(PF_NETLINK, SOCK_RAW, NETLINK_HANDOVER);
    if (handover_ue_config_t.sock_recv == NULL)
    {
        printf("[HANDOVER] Create Socket Error\n");
        fflush(stdout);
    }
    int bind_type = bind(handover_ue_config_t.sock_recv, (struct sockaddr *)&handover_ue_config_t.addr_recv, sizeof(struct sockaddr_nl));
    if (bind_type < 0)
    {
        printf("[HANDOVER] Bind Socket Error\n");
    }
    handover_ue_config_t.iov_recv.iov_base = (void *)handover_ue_config_t.hdr_recv;
    handover_ue_config_t.iov_recv.iov_len = NLMSG_SPACE(MSG_MAX_SIZE);
    handover_ue_config_t.msg_recv.msg_name = &handover_ue_config_t.addr_recv;
    handover_ue_config_t.msg_recv.msg_namelen = sizeof(struct sockaddr_nl);
    handover_ue_config_t.msg_recv.msg_iov = &handover_ue_config_t.iov_recv;
    handover_ue_config_t.msg_recv.msg_iovlen = 1;
    while (1)
    {
        //从内核接收
        Handover_Trigger_Msg_t msg;
        memset(&msg, 0, sizeof(Handover_Trigger_Msg_t));
        int len = sizeof(struct sockaddr_nl);
        if(recvmsg(handover_ue_config_t.sock_recv, &handover_ue_config_t.msg_recv, 0) >= 0)
        {
            int len = handover_ue_config_t.hdr_recv->nlmsg_len - NLMSG_SPACE(0);
            memcpy(&msg, NLMSG_DATA(handover_ue_config_t.hdr_recv), sizeof(Handover_Trigger_Msg_t));
            
            MessageDef *msg_p = itti_alloc_new_message(TASK_HANDOVER_UE, HANDOVER_TRIGGER);
            HANDOVER_TRIGGER(msg_p).flag = msg.flag;
            itti_send_msg_to_task(TASK_RRC_UE, 0, msg_p);
            
            printf("[HANDOVER] Send Trigger Success flag = %d\n",msg.flag);
            fflush(stdout);
            
        }  
    }
    
}

