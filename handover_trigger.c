/*--------------------------------------only for using netlink---------------------------------*/
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <linux/netlink.h>
#include <libconfig.h>
#include <errno.h>
#include <unistd.h>

#define NETLINK_SW       21
#define MAX_PAYLOAD      1024
#define NL_DEST_PID      100

#pragma pack(2)


typedef struct handover_trigger_msg
{
    uint8_t flag;
} Handover_Trigger_Msg;

int senseInfo_recvfro_kernel()
{
    int            errno;
    struct         sockaddr_nl    localSock;
    struct         sockaddr_nl    destSock;
    int            sendFlag, bindFlag;
    int            nl_sockfd;
    struct         nlmsghdr       *nlh;
    //struct msghdr message;

    nlh = (struct nlmsghdr *)malloc(MAX_PAYLOAD);

    nl_sockfd = socket(PF_NETLINK, SOCK_RAW, 21);

    printf("nl_sockfd = %d\n", nl_sockfd);
    if(nl_sockfd == -1)
    {
        printf("[HANDOVER]Create a netlink socket failed!\n");
        printf("Create socket error ....%s\n", strerror(errno));
        return -1;
    }

    memset(&localSock, 0, sizeof(localSock));
    localSock.nl_family = AF_NETLINK;
    localSock.nl_pid = NL_DEST_PID;
    localSock.nl_groups = 0;

    bindFlag = bind(nl_sockfd, (struct sockaddr *)&localSock, sizeof(localSock));
    if(bindFlag != 0)
    {
        printf("[HANDOVER]bind error!\n");
        return -1;
    }

    memset(&destSock, 0, sizeof(destSock));
    destSock.nl_family = AF_NETLINK;
    destSock.nl_pid = 0;
    destSock.nl_groups = 0;

    memset(nlh, 0, sizeof(struct nlmsghdr));
    //tag
    // nlh->nlmsg_len = NLMSG_SPACE(11*sizeof(Sense_Message_Phy_t));
    nlh->nlmsg_flags = 1;
    nlh->nlmsg_type = 20;
    nlh->nlmsg_seq = 0;
    nlh->nlmsg_pid = localSock.nl_pid;

    Handover_Trigger_Msg *handover_trigger_msg = (Handover_Trigger_Msg *)malloc(sizeof(Handover_Trigger_Msg));
    handover_trigger_msg->flag=1;
    memcpy(NLMSG_DATA(nlh), handover_trigger_msg, sizeof(Handover_Trigger_Msg));
    nlh->nlmsg_len = NLMSG_SPACE(sizeof(Handover_Trigger_Msg));
    printf("NLMSG_SPACE(sizeof(Handover_Trigger_Msg)):%d\n", NLMSG_SPACE(sizeof(Handover_Trigger_Msg)));
    sendFlag = sendto(nl_sockfd, nlh, nlh->nlmsg_len, 0, (struct sockaddr *)&destSock, sizeof(destSock));
    
    free(handover_trigger_msg);
    return 0;
}


int main()
{
    senseInfo_recvfro_kernel();
    return 1;
}
