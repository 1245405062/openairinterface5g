
/*--------------------------------------only for using netlink---------------------------------*/
#ifndef __HANDOVER_UE_H_
#define __HANDOVER_UE_H_
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <linux/netlink.h>
#include <libconfig.h>
#include <semaphore.h>
#include <sys/time.h>
#include <signal.h>
#include <time.h>
#include "COMMON/platform_types.h"
#include "openair2/RRC/LITE/defs.h"

#include "assertions.h"
/*
#define NETLINK_SW 25
#define MSG_LEN 2048
#define MAX_PAYLOAD 1024
#define SERVER_IP "192.168.89.181"
#define SERVER_PORT 2552
#define BUFF_LEN 2048



struct u_packet_msg{
	struct nlmsghdr hdr;
	unsigned char msgBuff[MSG_LEN];
};


socklen_t addrlen = sizeof(struct sockaddr_nl);
socklen_t udpsk_len = sizeof(struct sockaddr_in);
*/


#define NETLINK_HANDOVER 21

#define MSG_MAX_SIZE 1024

#define PID_RECV 100;

void *handover_ue_task(void *args_p);

typedef struct  handover_ue_config{
	
	int sock_recv;

	struct sockaddr_nl addr_recv;

	struct msghdr msg_recv;

	struct iovec iov_recv;

	struct nlmsghdr *hdr_recv;

}Handover_UE_Config_t;

typedef struct handover_trigger_msg{

	uint8_t flag;

	PhysCellId_t targetCellId;

	uint8_t *cellIdentity;

}Handover_Trigger_Msg_t;


Handover_UE_Config_t handover_ue_config_t;
#endif
