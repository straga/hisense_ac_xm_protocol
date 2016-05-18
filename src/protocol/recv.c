
#include	<stdio.h>
#include	<stdlib.h>
#include    <string.h>
#include    <unistd.h>
#include    <time.h>
#include    <sys/types.h>
#include    <sys/stat.h>
#include    <sys/select.h>
#include    <sys/socket.h>
#include    <netinet/in.h>
#include    <arpa/inet.h>
#include    <netdb.h>
#include    <pthread.h>
#include	"xmlog.h"
#include	"xm_type.h"
#include    "cmdanalysis.h"
#include	"message.h"
#include	"hisense.h"
#include    "recv.h"
char recv_tcp(XM_PROTOCOL *pxm,uchar *pbuf,int tcp_fd,int parse)
{
	uchar  nRecv,i,nRet=-3;
	if(!pbuf || tcp_fd<0){
		XM_E("ERROR client:para fail p %p b %p s %d\r\n",pxm,pbuf,tcp_fd);
		return XM_ERROR_PARAMETER;
	}
#if DEBUG_SCOKET
	XM_D("client: %d recv \r\n",tcp_fd);
#endif
	nRecv=recv(tcp_fd, pbuf, 0, 0);
#if DEBUG_SCOKET
	XM_D("client:test recv %d\r\n",nRecv);
#endif
	nRecv = recv(tcp_fd, pbuf, XM_MAX_BUF, 0);
	if (nRecv <=0) {
		XM_E("ERROR client:recv error, ret = %d\r\n", nRecv);
		return XM_ERROR_NET_RECV_FAIL;
	}
	pbuf[nRecv]=(char)'\0';
#if DEBUG_RS
	printf_buf("client:recv",pbuf,nRecv);
#endif
	if(pxm){
		if(parse){
#if DEBUG_CMD
			XM_D("client:init\r\n");
#endif
			statusInit(pxm);
#if DEBUG_RS
			XM_D("client:parse\r\n");
#endif
			memset(pxm->XM_At_Recv,0,XM_MAX_BUF);
			BIN2HEX((char *)pbuf,nRecv,pxm->XM_At_Recv);
			for(i=0;i<nRecv;i++){
				nRet=Parse_Read(pxm,pbuf+i,Proc_msg);
				if(nRet==XM_ERROR_WAIT_MOER){
					continue;
				}
				break;
			}
#if DEBUG_CMD
			XM_D("client:parse finish\r\n");
#endif
		}else {
#if DEBUG_RS
			XM_D("client:copy\r\n");
#endif
			if(pxm && (memcmp(pbuf,"+XM",3)==0 ||memcmp(pbuf,"AT+",3)==0 ) ){
				memcpy(pxm->XM_Status_Buffer,pbuf,nRecv);
				nRet=XM_SUCCESS;
			}else{
				nRet=XM_ERROR_WAIT_MOER;
			}
		}
	}else{
		nRet=XM_ERROR_NODE;
	}
	#if DEBUG_SCOKET
	XM_D("client:exit %d\r\n",nRet);
	#endif
	return nRet;
	
}

