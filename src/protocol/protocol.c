
#include    <sys/types.h>
#include    <sys/stat.h>
#include    <sys/select.h>
#include    <sys/socket.h>
#include    <netinet/in.h>
#include    <arpa/inet.h>
#include    <netdb.h>
#include	"xmlog.h"
#include	"xm_type.h"
#include    "message.h"
#include	"hisense.h"
#include    "command.h"
#include    "cmdanalysis.h"
#include    "air-condition_msg.h"
#include    "protocol.h"
#include    "client.h"
#include    "server.h"
#include    "recv.h"
#include    "send.h"
#include 	"xlf_crc.h"

pthread_t tid_server=0;
pthread_t tid_send=0;
static int xm_inited=0;
static int xm_sendid=0;
static int g_xm_max_wait_node = MAX_CMD_NUM;
int xm_exited=1;
extern XM_PROTOCOL *xm_protocl;
extern int g_xm_connect_num;
extern uchar xm_address1[];
extern uchar xm_address2[];

void xm_wait_init(XM_SYNC * psync){
#if USE_SEM
	sem_init(&psync->sem, 0, 0);
#else
	pthread_cond_init(&psync->cond, NULL);
#endif
	pthread_mutex_init(&psync->mutex, NULL);
    psync->value=SEM_TIMEOUT;
	psync->is_wait=0;
}

void xm_wait_sync(XM_SYNC * psync){
#if DEBUG_THREAD
	XM_D("wait_sync:sync %p\r\n",psync);
#endif
	psync->is_wait=1;
	psync->value=SEM_TIMEOUT;
	time(&(psync->timeout));
#if USE_SEM
	while(sem_trywait(&psync->sem)!=0 && psync->value){
		sleep(1);
		psync->value--;
	}
#else
#if DEBUG_THREAD
	XM_D("wait_sync:sync cond\r\n");
#endif
    pthread_cond_wait(&psync->cond, &psync->mutex);
#endif
	psync->timeout=0;
}

void xm_wait_lock(XM_SYNC * psync){
	pthread_mutex_lock(&psync->mutex);
}

void xm_wait_signal(XM_SYNC * psync){
#if DEBUG_THREAD
	XM_D("wait_sync:wait signal %p\r\n",psync);
#endif
	//TP_DATA_IS_WAIT(psync);	
#if USE_SEM
	sem_post(&psync->sem);
#else
#if DEBUG_THREAD
	XM_D("wait_sync:wait signal\r\n");
#endif
	pthread_mutex_lock(&psync->mutex);
	pthread_cond_signal(&psync->cond);	
	pthread_mutex_unlock(&psync->mutex);
#endif
	psync->is_wait=0;
}

void xm_wait_broadcast(XM_SYNC * psync){
#if USE_SEM
#else
    pthread_cond_broadcast(&psync->cond);
#endif
}

void xm_wait_unlock(XM_SYNC * psync){
	pthread_mutex_unlock(&psync->mutex);
}
void xm_wait_destroy(XM_SYNC * psync){
#if USE_SEM
	sem_destroy(&(psync->sem));
#else
	pthread_cond_destroy(&(psync->cond));
#endif
	pthread_mutex_destroy(&(psync->mutex));
}

int xm_get_socket(int index){
	return client_get_socket(index);
}

void xm_init_index(JavaVM *pjvm,int connect_num,int send_num,int max_wait_node){
	if(!xm_inited){	
		xm_inited++;
		xm_exited=0;
		XmInitLog(MAX_SEND_POOL);
		if(max_wait_node>0)
			g_xm_max_wait_node=max_wait_node;
		client_init_lock();
		XM_D("init_index:jvm %p \r\n",pjvm);
#if DEBUG_RS
		XM_D("init_index:connect_num %d send_num %d max_wait_node %d\r\n",connect_num,send_num,max_wait_node);
#endif
		if(client_init_client(pjvm,&tid_send,&xm_exited,connect_num,send_num)!=0){
			xm_inited--;
			return ;
		}
	}else{
		xm_exited=0;
		client_clean_client(pjvm,&tid_send,&xm_exited);
	}
}
void xm_init(JavaVM *pjvm){	

	xm_init_index(pjvm,XM_CONNECT_NUM,MAX_SEND_POOL,MAX_CMD_NUM);
}

int xm_exit_socket(int socketfd){
	int nRet=-1;
	XmSetLog("exit_socket",xm_sendid++);
	if(xm_exited){
		XM_E("ERROR exit_socket:lib is exit %d\r\n",xm_exited);
		goto exit_socket_finish;
	}
	
	if(!xm_inited){
		XM_E("ERROR exit_socket:lib not init %d\r\n",xm_exited);
		goto exit_socket_finish;
	}
	if(socketfd<=0){
		XM_E("ERROR exit_socket:socket vail %d\r\n",socketfd);  
		goto exit_socket_finish;
	}
	nRet = client_exit_client(socketfd);
exit_socket_finish:
	XmDelLog();
	return nRet;
}
void xm_stop_servsr(void){
	servsr_stop();
}

int xm_init_servsr(char * server_port,int connect){
	if(xm_exited){
		XM_E("ERROR init_servsr:lib is exit %d\r\n",xm_exited);
		return -1;
	}
	
	if(!xm_inited){
		XM_E("ERROR init_servsr:lib not init %d\r\n",xm_exited);
		return -1;
	}
	if(!server_port){
		XM_E("ERROR init_servsr:port not set %p\r\n",server_port);  
		return XM_ERROR_NOT_INIT;
	}
	return servsr_start(&tid_server,server_port,&xm_exited,connect);
}
int xm_init_withsocket_index(int socketfd,int id){
	XM_PROTOCOL *pxm;
	if(xm_exited){
		XM_E("ERROR init_withsocket_index:lib is exit %d\r\n",xm_exited);
		return -1;
	}
	
	if(!xm_inited){
		XM_E("ERROR init_withsocket_index:lib not init %d\r\n",xm_exited);
		return -1;
	}
	pxm=client_new_index(socketfd,id);
	if(pxm==NULL){		
		XM_E("ERROR init_withsocket_index:socket add fail %p\r\n",pxm);
		return -1;
	}	
	return pxm->xm_index;
}
int xm_init_withsocket(int socketfd){
	return xm_init_withsocket_index(socketfd,0x1);
}

int xm_init_socket_index(char * server_ip,char * server_port,int id,int reset){
	int socketfd=-1;
	XM_PROTOCOL *pxm;
	XmSetLog("init_socket",xm_sendid++);
	if(!xm_inited){
		XM_E("ERROR init_socket_index:lib not init %d\r\n",xm_inited);
		goto exit_init_socket;
	}
	if(xm_exited){
		if (reset)
			xm_exited=0;
		else
			{
			XM_E("ERROR init_socket_index:lib is exit %d\r\n",xm_exited);
			goto exit_init_socket;
			}
	}
	xm_init_index(NULL,-1,-1,-1);
	socketfd=init_socket_client(server_ip,server_port);
	pxm=client_new_index(socketfd,id);
	if(pxm==NULL){
		if(socketfd!=-1){
			close(socketfd);
			socketfd=-1;
		}
		goto exit_init_socket;
	}
#if DEBUG_SCOKET
	XM_D("init_socket:socket %d index %p\r\n",socketfd,pxm);
#endif
	socketfd=pxm->xm_index;
exit_init_socket:
	XmDelLog();
	return socketfd;	
}
int xm_init_flag(char * server_ip,char * server_port,int id,char cflag){
	XM_PROTOCOL *pxm=NULL;
	int ret;
	if(xm_exited){
		XM_E("ERROR init_flag:lib is exit %d\r\n",xm_exited);
		return -1;
	}
	
	if(!xm_inited){
		XM_E("ERROR init_flag:lib not init %d\r\n",xm_exited);
		return -1;
	}
	ret=xm_init_socket_index(server_ip,server_port,id,0);
	pxm=client_get_client(ret);
	if(pxm!=NULL){
		pxm->XM_Frame_Buffer[0]='X';
		pxm->XM_Frame_Buffer[1]='M';
		pxm->XM_Frame_Buffer[2]='-';
		pxm->XM_Frame_Buffer[3]=cflag;
		pxm->XM_Frame_Buffer[4]='\0';
		ret=send_tcp(pxm,pxm->XM_Frame_Buffer,4);
		if(ret ==XM_ERROR_SOCKET_SEND){
#if DEBUG_SCOKET
			XM_D("flag:socket send fail %d\r\n",ret);
#endif
			close(pxm->xm_socket_client);
			pxm->xm_socket_client=-1;
		}else{
			return pxm->xm_index;
		}
	}
	return -1;
}
int xm_init_flag_withsocket(int socket_fd,int id,char cflag){
	XM_PROTOCOL *pxm=NULL;
	int ret;
	if(xm_exited){
		XM_E("ERROR init_flag_withsocket:lib is exit %d\r\n",xm_exited);
		return -1;
	}
	
	if(!xm_inited){
		XM_E("ERROR init_flag_withsocket:lib not init %d\r\n",xm_exited);
		return -1;
	}
	pxm=client_new_index(socket_fd,id);
	if(pxm==NULL){
		XM_E("ERROR init_flag_withsocket:error socket %d exit %d init %d\r\n",socket_fd,xm_exited,xm_inited);
		return -1;
	}	
	pxm->XM_Frame_Buffer[0]='X';
	pxm->XM_Frame_Buffer[1]='M';
	pxm->XM_Frame_Buffer[2]='-';
	pxm->XM_Frame_Buffer[3]=cflag;
	pxm->XM_Frame_Buffer[4]='\0';
	ret=send_tcp(pxm,pxm->XM_Frame_Buffer,4);
	if(ret ==XM_ERROR_SOCKET_SEND){
#if DEBUG_SCOKET
		XM_D("flag:socket send fail %d\r\n",ret);
#endif
		close(pxm->xm_socket_client);
		pxm->xm_socket_client=-1;
	}else{
		return pxm->xm_index;
	}
	return -1;
}

int xm_init_virtual(char * server_ip,char * server_port,int id){
	return xm_init_flag(server_ip,server_port,id,'V');
}

int xm_init_test(char * server_ip,char * server_port,int id){
	return xm_init_flag(server_ip,server_port,id,'C');
}

int xm_exit(void){
	int i;XM_NODE *pnodeseek,*pnodetmp;
	XmSetLog("exit",xm_sendid++);
#if DEBUG_RS
	XM_D("exit:enter \r\n");
#endif
//	xm_exited=1;
#if DEBUG_RS
	XM_D("exit:wait server\r\n");
#endif
	if(tid_server!=0){
		//servsr_stop();
		pthread_join (tid_server, NULL);
	}
	tid_server=0;
	
#ifndef ANDROID
	xm_exited=1;
#if DEBUG_RS
		XM_D("exit:wait send\r\n");
#endif

	if(tid_send!=0){
		pthread_join (tid_send, NULL);
	}
	tid_send=0;
#else
//add by mujian for close socket		
for (i=0;i<g_xm_connect_num;i++)	
{
	XM_D("socket %d i %d g_xm_connect_num %d!!\r\n",xm_protocl[i].xm_socket_client,i,g_xm_connect_num);
		pthread_mutex_lock(&xm_protocl[i].mutex);
	if (xm_protocl[i].xm_socket_client!=-1)
		{	
			xm_protocl[i].xm_exit=1;
			pnodeseek=xm_protocl[i].node;
			xm_protocl[i].xm_sendready=0;
			xm_protocl[i].xm_send=0;
			xm_protocl[i].timeout=0;
			xm_protocl[i].sendcmd=0;
			xm_protocl[i].sendsub=0;
			xm_protocl[i].xm_seting=1;			
			while(pnodeseek){
			pnodetmp=pnodeseek->end;			
			pnodeseek->errorid=XM_ERROR_FORCE_CLOSE_NODE;
			pnodeseek->xm_sendready=0;
#if DEBUG_THREAD
			XM_D("exit_client:state_thread post sem node %d index %d socket %d\r\n",pnodeseek->id,pnodeseek->index,xm_protocl[i].xm_socket_client);
#endif
			xm_wait_signal((XM_SYNC *)pnodeseek);
			pnodeseek=pnodetmp;
			}
			//XM_D("close %d socket !!5\r\n",xm_protocl[i].xm_socket_client);
			xm_protocl[i].node=NULL;
			XM_D("close %d socket !!\r\n",xm_protocl[i].xm_socket_client);
			close(xm_protocl[i].xm_socket_client);
			xm_protocl[i].xm_socket_client=-1;
			xm_protocl[i].xm_exit=0;			
	}
	pthread_mutex_unlock(&xm_protocl[i].mutex);
}	
//add by mujian for close socket
#endif

	
#if DEBUG_RS
	XM_D("exit:return\r\n");
#endif
	XmDelLog();
	return XM_SUCCESS;
}

char * xm_get_packet(int index){
	XM_PROTOCOL * pxm=client_get_client(index);
	if(pxm!=NULL){
		return pxm->XM_At_Send;
	}
	return NULL;
}

char * xm_get_parse(int index){
	XM_PROTOCOL * pxm=client_get_client(index);
	if(pxm!=NULL){
		return pxm->XM_At_Recv;
	}
	return NULL;
}

char *xm_build_packet(char *pbuf,int *len,int address){
	int i;
	XM_PROTOCOL xm;
	XM_NODE node;
	char *retstr=NULL;uchar *pdata=NULL,*psend=NULL;
	int sendlen;
	memset(&xm,0,sizeof(XM_PROTOCOL));
	xm.xm_socket_client=-1;
	xm.xm_addres=address;
	xm.xm_frame=-1;
	xm.xm_sub_frame=-1;	
	xm.xm_seting=1; 
	xm.xm_exit=0;
	xm.xm_index=0;
	node.address=0;		
	node.index=0;
	node.argc=0;
	node.errorid=XM_ERROR_RECV_TIMEOUT;
	node.xm_set=0;
	node.xm_sendlen=0;
	node.xm_sendready=0;
	node.is_wait=0;
	node.end=NULL;
	memset(&node.xm_at,0,sizeof(XM_AT));
	xm.node=&node;
	node.atbuf=pbuf;
	node.atlen=*len;	

	if((memcmp(pbuf,"AT+XM",5)==0)||(memcmp(pbuf,"AT+WHO",6)==0)||(memcmp(pbuf,"AT+WF",5)==0)){
			XM_E("WIFI COMMAND STRING\r\n");
			node.errorid=XM_ERROR_CMD_EXEC;
			retstr=(char *)malloc(4096);
			memset(retstr,'\0',4096);
			snprintf(retstr,4096,"%s",pbuf);
			*len=strlen(pbuf);XM_E("WIFICOMMAND STRING!ERROR %s\r\n",retstr);
			return retstr;
		}

	strDividing(&xm,&node,node.atbuf,node.atlen);
	if(node.argc){
		for( i=0;i<node.argc;i++){
			if(strncmp(node.xm_at.getparam[i],"?",1)==0){
				node.xm_set=XM_SEND_QUERY;
				xm.sendcmd=node.xm_cmd->parameter->query_cmd;;
				xm.sendsub=node.xm_cmd->parameter->query_sub;
#if DEBUG_CMD
				XM_D("build_packet:XM_SEND_QUERY!!\r\n");
#endif
				break;
			}else if(strncmp(node.xm_at.getparam[i],"*",1)==0){
				node.xm_set=XM_SEND_SUPPORT;
				xm.sendcmd=node.xm_cmd->parameter->support_cmd;;
				xm.sendsub=node.xm_cmd->parameter->support_sub;
#if DEBUG_CMD
				XM_D("build_packet:XM_SEND_SUPPORT!!\r\n");
#endif				
				break;
			}else{
				node.xm_set=XM_SEND_SETTING;
				xm.sendcmd=node.xm_cmd->parameter->set_cmd;;
				xm.sendsub=node.xm_cmd->parameter->set_sub;
#if DEBUG_CMD
				XM_D("build_packet:XM_SEND_SETTING!!\r\n");
#endif				
			}
		}
	}	else{
		node.xm_set=XM_SEND_SETTING;
	}	
#if XM_WITH_ID
	if((node.argc<2) ||(node.errorid!=XM_SUCCESS)){
		XM_E("UNPACKETD STRING\r\n");
		node.errorid=XM_ERROR_AT_PRAR;
		retstr=(char *)malloc(4096);
		memset(retstr,'\0',4096);
		snprintf(retstr,4096,"%s",pbuf);
		*len=strlen(pbuf);XM_E("UNPACKETD STRING!ERROR %s\r\n",retstr);
		return retstr;
	}
	if(node.xm_set==XM_SEND_SETTING)
		node.xm_sendlen=Build_Send(&xm,&node,node.argc-1,&node.xm_at.getparam[1]);
	else
		node.xm_sendlen=Build_Send(&xm,&node,node.argc-2,&node.xm_at.getparam[2]);
#else
	node.xm_sendlen=Build_Send(&xm,&node,node->argc,node.xm_at.getparam);
#endif
#if DEBUG_CMD
	XM_D("build_packet:sendlen %d\r\n",node.xm_sendlen);
#endif
	//add by mujian for copy node data to pxm data	
	memset(xm.XM_Status_Value,'\0',XM_MAX_BUF);
	snprintf((char *)xm.XM_Status_Value,XM_MAX_BUF,"%d",node.xm_sendlen);
	sendlen=node.xm_sendlen;
	psend=(uchar *)(xm.XM_Setting_Buffer);
	pdata=(uchar *)(node.xm_at.XM_At_Ret);
#if DEBUG_CMD
		printf_buf("node send data",(uchar *)node.xm_at.XM_At_Ret,node.xm_sendlen);
#endif
		while(sendlen>0){
#if DEBUG_CMD
			XM_D("Build_send: sendlen %d\r\n",node.xm_sendlen);
#endif
#if 0
			tempb=*psend;
#if DEBUG_CMD
			XM_D("Build_send:psend %02x\r\n",(uchar )tempb);
#endif
			tempa=*pdata;
#if DEBUG_CMD
			XM_D("Build_send:pdata %02x\r\n",(uchar )tempa);
#endif
#endif
			*psend++|=*pdata++;
			sendlen-=sizeof(uchar);			
		}
	xm.getparam[0]=(char *)xm.XM_Status_Value;
	xm.getparam[1]=(char *)xm.XM_Setting_Buffer;	
	//add by mujian for copy node data to pxm data
	ProcCmd(&xm,2,xm.getparam);
	*len=xm.xm_send;
	if(xm.xm_send){
		retstr=(char *)malloc(xm.xm_send+1);
		memset(retstr,'\0',xm.xm_send+1);
		memcpy(retstr,xm.XM_Frame_Buffer,xm.xm_send);
	}
	return retstr;
}

char *xm_build_packet_frame(char *pbuf,int *len,int address,int frame,int sub_frame){
	int i;
	XM_PROTOCOL xm;
	XM_NODE node;
	char *retstr=NULL;uchar *pdata=NULL,*psend=NULL;
	int sendlen;
	memset(&xm,0,sizeof(XM_PROTOCOL));
	xm.xm_socket_client=-1;
	xm.xm_addres=address;
	xm.xm_frame=frame;
	xm.xm_sub_frame=sub_frame;
	xm.xm_seting=1; 
	xm.xm_exit=0;
	xm.xm_index=0;
	node.address=0;		
	node.index=0;
	node.argc=0;
	node.errorid=XM_ERROR_RECV_TIMEOUT;
	node.xm_set=0;
	node.xm_sendlen=0;
	node.xm_sendready=0;
	node.is_wait=0;
	node.end=NULL;
	memset(&node.xm_at,0,sizeof(XM_AT));
	xm.node=&node;
	node.atbuf=pbuf;
	node.atlen=*len;	

	if((memcmp(pbuf,"AT+XM",5)==0)||(memcmp(pbuf,"AT+WHO",6)==0)||(memcmp(pbuf,"AT+WF",5)==0)){
			XM_E("WIFI COMMAND STRING\r\n");
			node.errorid=XM_ERROR_CMD_EXEC;
			retstr=(char *)malloc(4096);
			memset(retstr,'\0',4096);
			snprintf(retstr,4096,"%s",pbuf);
			*len=strlen(pbuf);XM_E("WIFICOMMAND STRING!ERROR %s\r\n",retstr);
			return retstr;
		}

	strDividing(&xm,&node,node.atbuf,node.atlen);
	if(node.argc){
		for( i=0;i<node.argc;i++){
			if(strncmp(node.xm_at.getparam[i],"?",1)==0){
				node.xm_set=XM_SEND_QUERY;
				xm.sendcmd=node.xm_cmd->parameter->query_cmd;;
				xm.sendsub=node.xm_cmd->parameter->query_sub;
#if DEBUG_CMD
				XM_D("build_packet:XM_SEND_QUERY!!\r\n");
#endif
				break;
			}else if(strncmp(node.xm_at.getparam[i],"*",1)==0){
				node.xm_set=XM_SEND_SUPPORT;
				xm.sendcmd=node.xm_cmd->parameter->support_cmd;;
				xm.sendsub=node.xm_cmd->parameter->support_sub;
#if DEBUG_CMD
				XM_D("build_packet:XM_SEND_SUPPORT!!\r\n");
#endif				
				break;
			}else{
				node.xm_set=XM_SEND_SETTING;
				xm.sendcmd=node.xm_cmd->parameter->set_cmd;;
				xm.sendsub=node.xm_cmd->parameter->set_sub;
#if DEBUG_CMD
				XM_D("build_packet:XM_SEND_SETTING!!\r\n");
#endif				
			}
		}
	}	else{
		node.xm_set=XM_SEND_SETTING;		
	}	
#if XM_WITH_ID
	if((node.argc<2) ||(node.errorid!=XM_SUCCESS)){
		XM_E("UNPACKETD STRING\r\n");
		node.errorid=XM_ERROR_AT_PRAR;
		retstr=(char *)malloc(4096);
		memset(retstr,'\0',4096);
		snprintf(retstr,4096,"%s",pbuf);
		*len=strlen(pbuf);XM_E("UNPACKETD STRING!ERROR %s\r\n",retstr);
		return retstr;
	}
	if(node.xm_set==XM_SEND_SETTING)
		node.xm_sendlen=Build_Send(&xm,&node,node.argc-1,&node.xm_at.getparam[1]);
	else
		node.xm_sendlen=Build_Send(&xm,&node,node.argc-2,&node.xm_at.getparam[2]);
#else
	node.xm_sendlen=Build_Send(&xm,&node,node->argc,node.xm_at.getparam);
#endif
#if DEBUG_CMD
	XM_D("build_packet:sendlen %d\r\n",node.xm_sendlen);
#endif
	//add by mujian for copy node data to pxm data	
	memset(xm.XM_Status_Value,'\0',XM_MAX_BUF);
	snprintf((char *)xm.XM_Status_Value,XM_MAX_BUF,"%d",node.xm_sendlen);
	sendlen=node.xm_sendlen;
	psend=(uchar *)(xm.XM_Setting_Buffer);
	pdata=(uchar *)(node.xm_at.XM_At_Ret);
#if DEBUG_CMD
		printf_buf("node send data",(uchar *)node.xm_at.XM_At_Ret,node.xm_sendlen);
#endif
		while(sendlen>0){
#if DEBUG_CMD
			XM_D("Build_send: sendlen %d\r\n",node.xm_sendlen);
#endif
#if 0
			tempb=*psend;
#if DEBUG_CMD
			XM_D("Build_send:psend %02x\r\n",(uchar )tempb);
#endif
			tempa=*pdata;
#if DEBUG_CMD
			XM_D("Build_send:pdata %02x\r\n",(uchar )tempa);
#endif
#endif
			*psend++|=*pdata++;
			sendlen-=sizeof(uchar);			
		}
	xm.getparam[0]=(char *)xm.XM_Status_Value;
	xm.getparam[1]=(char *)xm.XM_Setting_Buffer;	
	//add by mujian for copy node data to pxm data
	ProcCmd(&xm,2,xm.getparam);
	*len=xm.xm_send;
	if(xm.xm_send){
		retstr=(char *)malloc(xm.xm_send+1);
		memset(retstr,'\0',xm.xm_send+1);
		memcpy(retstr,xm.XM_Frame_Buffer,xm.xm_send);
	}
	return retstr;
}


char * xm_parse_data(char *cmdpbuf,int cmdlen,char *pbuf,int len){
	int i;
	XM_PROTOCOL xm;
	XM_NODE node;
	char *retstr=NULL;
	char *retstr_temp=NULL;
	memset(&xm,0,sizeof(XM_PROTOCOL));
	xm.xm_socket_client=-1;
	xm.xm_addres=0xff;
	xm.xm_seting=1; 
	xm.xm_exit=0;
	xm.xm_index=0;
	node.address=0;		
	node.index=0;
	node.argc=0;
	node.errorid=XM_ERROR_RECV_TIMEOUT;
	node.xm_set=0;
	node.xm_sendlen=0;
	node.xm_sendready=0;
	node.is_wait=0;
	node.end=NULL;
	memset(&node.xm_at,0,sizeof(XM_AT));
	xm.node=&node;
	node.atbuf=cmdpbuf;
	node.atlen=cmdlen;
	retstr_temp=(char *)malloc(4096);
	memset(retstr_temp,'\0',4096);
	BIN2HEX((char *)pbuf,len,retstr_temp);
	if((memcmp(retstr_temp,"f4f5",4)!=0)&&(memcmp(retstr_temp,"F4F5",4)!=0)){
			//HEX2BIN(retstr_temp,(char *)pbuf);
			return NULL;
		}
	strDividing(&xm,&node,node.atbuf,node.atlen);
	if(node.argc){
		for( i=0;i<node.argc;i++){
			if(strncmp(node.xm_at.getparam[i],"?",1)==0){
				node.xm_set=XM_SEND_QUERY;
				xm.sendcmd=node.xm_cmd->parameter->query_cmd;;
				xm.sendsub=node.xm_cmd->parameter->query_sub;
#if DEBUG_CMD
				XM_D("parse_data:XM_SEND_QUERY!!\r\n");
#endif
				break;
			}else if(strncmp(node.xm_at.getparam[i],"*",1)==0){
				node.xm_set=XM_SEND_SUPPORT;
				xm.sendcmd=node.xm_cmd->parameter->support_cmd;;
				xm.sendsub=node.xm_cmd->parameter->support_sub;
#if DEBUG_CMD
				XM_D("parse_data:XM_SEND_SUPPORT!!\r\n");
#endif				
				break;
			}else{
				node.xm_set=XM_SEND_SETTING;
				xm.sendcmd=node.xm_cmd->parameter->set_cmd;;
				xm.sendsub=node.xm_cmd->parameter->set_sub;
#if DEBUG_CMD
				XM_D("parse_data:XM_SEND_SETTING!!\r\n");
#endif				
			}
		}
	}	else{
		node.xm_set=XM_SEND_SETTING;
	}	
#if XM_WITH_ID
	if(node.argc<2){
		XM_E("parse_data:ERROR AT PRAR\r\n");
		node.errorid=XM_ERROR_AT_PRAR;
		return NULL;
	}
#endif
	statusInit(&xm);
	for(i=0;i<len;i++){
		node.errorid=Parse_Read(&xm,(uchar *)pbuf+i,Proc_msg);
		if(node.errorid!=XM_ERROR_WAIT_MOER){
			break;
		}
	}
	retstr=(char *)malloc(4096);
	memset(retstr,'\0',4096);
	if(node.errorid==XM_SUCCESS){		
		//snprintf(retstr,4096,"SUCCESS\r\n");
		//snprintf(retstr+strlen(retstr),4096-strlen(retstr),"%s\r\n",node.xm_at.XM_At_Ret);
		snprintf(retstr,4096-strlen(retstr),"%s\r\n",node.xm_at.XM_At_Ret);
	}else if(node.errorid==XM_ERROR_WAIT_MOER){	
		snprintf(retstr,4096,"MORE\r\n");
	}else {
		snprintf(retstr,4096,"%s\r\n",node.xm_at.XM_At_Ret);
	}
	return retstr;
}

#define FRAME_ERROR_PRE 0x1000
#define FRAME_ERROR_SIZE_TOOLAGER 0x1
#define NETWORK_ERROR_PRE 0x2000
#define TRANSFER_ERROR_PRE 0x3000
#define CRC_ERROR_PRE 0x4000
#define END_ERROR_PRE 0x5000
#define HEAD_ERROR_PRE 0x6000
#define HEAD_ERROR_DISCONNECT 0x7000
#define PACKET_MAX_LEN 255
#define ERROR_MSG_TIME_OUT 0xb
#define ERROR_MSG_TIME_OUT_MAX 0xc
#define MSG_TIME_OUT_SEND_COUNT 10
extern XM_AT_RET at_cmd_ret_kl[];
extern XM_AT_RET at_cmd_ret_kt[];
extern XM_AT_RET at_cmd_ret_jh[];
extern XM_AT_RET at_cmd_ret_cs[];
extern XM_AT_RET at_cmd_ret_qr[];
extern XM_AT_RET at_cmd_ret_oven[];
extern XM_AT_RET at_cmd_ret_rqz[];
extern XM_AT_RET at_cmd_ret_rsq[];
// Add by Hetao
//extern XM_AT_RET at_cmd_ret_clean[];
extern XM_AT_RET at_cmd_ret_DC[]; // ding cheng
extern XM_AT_RET at_cmd_ret_Seed[2];

extern XM_AT_RET at_cmd_ret_senser[2]; 
extern XM_AT_RET at_cmd_ret_curtain[2]; 
extern XM_AT_RET at_cmd_ret_volta[2]; 
extern XM_AT_RET at_cmd_ret_smartLight[2]; 


XM_AT_RET_LIST xm_at_ret_list[]={
		{8,at_cmd_ret_kl,0xFF,NULL},
		{6,at_cmd_ret_kt,0x01,NULL},
		// mobile air conditioner
		{6,at_cmd_ret_kt,0x36,NULL},
		{4,at_cmd_ret_jh,0x18,NULL},			
		{3,at_cmd_ret_cs,0x15,NULL},
		{13,at_cmd_ret_oven,0x27,NULL},			
		{3,at_cmd_ret_qr,0x19,NULL},
		{3,at_cmd_ret_rqz,0x22,NULL},			
		{4,at_cmd_ret_rsq,0x25,NULL},
		{6,at_cmd_ret_kt,0xfd,NULL},//hisense business aircon
		// add by hetao
		{2,at_cmd_ret_Seed,0x28,NULL},
		{5,at_cmd_ret_DC,0x29,NULL},
		{2,at_cmd_ret_senser,0x53,NULL},
		{2,at_cmd_ret_curtain,0x55,NULL},
		{2,at_cmd_ret_volta,0x11,NULL},
		{2,at_cmd_ret_smartLight,0x52,NULL},

		
};


void xlf_pasre_info(struct message_struct * packet_message_struct,uchar *buf,int buflen){
	uchar *pbuf=NULL;
	int packet_struct_head=-1,packet_struct_len=0,resend_count=0;
	int i;
	struct frame_head *packet_frame_head=NULL;
	struct frame_struct *packet_frame_struct=NULL;	
	struct network_struct *packet_network_struct=NULL;
	struct transfer_struct *packet_transfer_struct=NULL;
	struct frame_crc *packet_frame_crc=NULL;
	struct frame_crc verification_frame_crc;
	struct frame_end *packet_frame_end=NULL;
	int max_size=PACKET_MAX_LEN-sizeof(struct frame_head)-sizeof(struct frame_struct)-sizeof(struct frame_crc)-sizeof(struct frame_end);
	
	memset(packet_message_struct,0,sizeof(struct message_struct));
	packet_struct_len=sizeof(struct frame_struct);
	if(buflen>PACKET_MAX_LEN || buflen<=0){
		packet_message_struct->error=FRAME_ERROR_PRE|FRAME_ERROR_SIZE_TOOLAGER;
		return ;
	}
	//printf_buf("build_pasre",(char *)buf,buflen);
	/*完整性验证
	*1.查找头
	*2.解析长度
	*3.判断结束符是否正常
	*/
	/*查找头*/
	for(i=0;i<buflen-1;i++){
		if(buf[i]==0xf4 && buf[i+1]==0xf5){
			packet_struct_head=i+2;
			break;
		}
	}
	if(packet_struct_head==-1){
		packet_message_struct->error=HEAD_ERROR_PRE;
		return ;
	}
	pbuf=buf+packet_struct_head-sizeof(struct frame_head);
	packet_frame_head=(struct frame_head *)pbuf;

#if DEBUG_CMD
	printf_buf("frame_head",(char *)pbuf,sizeof(struct frame_head));
#endif
	pbuf+=sizeof(struct frame_head);
	packet_frame_struct=(struct frame_struct *)pbuf;
	//printf_buf("frame_struct",(char *)pbuf,sizeof(struct frame_struct));
	
	/*先进行帧结构的转义字符处理*/
	for(i=0;i<sizeof(struct frame_struct);i++){
		if(pbuf[i]==0xf4 && pbuf[i+1]==0xf4){
			memcpy(&pbuf[i],&pbuf[i+1],buflen-i-(pbuf-buf)-1);
			buf[buflen-1]=0;
		}
	}
	//if(packet_frame_struct->ack!=1){
		//packet_message_struct->error=FRAME_ERROR_PRE|packet_frame_struct->ack;
		//return ;
	//}
	//printf("build_pasre:packet len %u\r\n",packet_frame_struct->len);
	if(packet_frame_struct->len>max_size){
		packet_message_struct->error=FRAME_ERROR_PRE|FRAME_ERROR_SIZE_TOOLAGER;
		return ;
	}
	pbuf+=sizeof(struct frame_struct);
	packet_struct_len=packet_frame_struct->len+sizeof(struct network_struct)+sizeof(struct transfer_struct)+sizeof(struct frame_crc);
	/*进行网络/ 传输/ 消息/验证转义字符的处理*/
	for(i=0;i<packet_struct_len;i++){
		if(pbuf[i]==0xf4 && pbuf[i+1]==0xf4){
			memcpy(&pbuf[i],&pbuf[i+1],buflen-i-(pbuf-buf)-1);
			buf[buflen-1]=0;
		}
	}	
	packet_network_struct=(struct network_struct *)pbuf;
	//printf_buf("network_struct",(char *)pbuf,sizeof(struct network_struct));	
	packet_message_struct->source_module=packet_network_struct->source_module;
	packet_message_struct->source_no=packet_network_struct->source_no;
	packet_message_struct->destination_module=packet_network_struct->destination_module;
	packet_message_struct->destination_no=packet_network_struct->destination_no;
	//if(packet_network_struct->ack!=1){
		//packet_message_struct->error=NETWORK_ERROR_PRE|packet_network_struct->ack;
		//return ;
	//}
	/*获取传输结构*/
	pbuf+=sizeof(struct network_struct);
	packet_transfer_struct=(struct transfer_struct *)pbuf;
	//printf_buf("transfer_struct",(char *)pbuf,sizeof(struct transfer_struct));
	//if(packet_transfer_struct->ack!=1){
		//packet_message_struct->error=TRANSFER_ERROR_PRE|packet_transfer_struct->ack;
		//return ;
	//}
	/*获取消息*/
	pbuf+=sizeof(struct transfer_struct);
	packet_message_struct->data_size=packet_frame_struct->len-sizeof(struct network_struct)-sizeof(struct transfer_struct);
	//printf("build_pasre:data len %u\r\n",packet_message_struct->data_size);
	memcpy(packet_message_struct->data,pbuf,packet_message_struct->data_size);
	
	/*较验数据*/
	pbuf+=packet_message_struct->data_size;
	packet_frame_crc=(struct frame_crc *)pbuf;
	//printf_buf("frame_crc",(char *)pbuf,sizeof(struct frame_crc));
	xlf_crc((uchar *)packet_frame_struct,(uchar *)packet_frame_crc-(uchar *)packet_frame_struct,&verification_frame_crc);
	if(memcmp(&verification_frame_crc,packet_frame_crc,sizeof(struct frame_crc))!=0){
		packet_message_struct->error=CRC_ERROR_PRE;
		XM_D("verification_frame_crc:0x%x 0x%x  packet_frame_crc:0x%x 0x%x\r\n",verification_frame_crc.crc_high,verification_frame_crc.crc_low,packet_frame_crc->crc_high,packet_frame_crc->crc_low);
		return ;
	}
	/*检查帧尾*/
	pbuf+=sizeof(struct frame_crc);
	packet_frame_end=(struct frame_end *)pbuf;
	if(packet_frame_end->end1!=0xf4 || packet_frame_end->end2!=0xfb){
		packet_message_struct->error=END_ERROR_PRE;
		return ;
	}
	packet_message_struct->use_size=packet_struct_len+sizeof(struct frame_head)+sizeof(struct frame_end);
}



void xlf_pasre(struct message_struct * packet_message_struct,uchar *buf,int buflen){
	uchar *pbuf=NULL;
	int packet_struct_head=-1,packet_struct_len=0,resend_count=0;
	int i;
	struct frame_head *packet_frame_head=NULL;
	struct frame_struct *packet_frame_struct=NULL;	
	struct network_struct *packet_network_struct=NULL;
	struct transfer_struct *packet_transfer_struct=NULL;
	struct frame_crc *packet_frame_crc=NULL,verification_frame_crc;
	struct frame_end *packet_frame_end=NULL;
	unsigned short crc16;
	int max_size=PACKET_MAX_LEN-sizeof(struct frame_head)-sizeof(struct frame_struct)-sizeof(struct frame_crc)-sizeof(struct frame_end);
	
	memset(packet_message_struct,0,sizeof(struct message_struct));
	packet_struct_len=sizeof(struct frame_struct);
	if(buflen>PACKET_MAX_LEN || buflen<=0){
		packet_message_struct->error=FRAME_ERROR_PRE|FRAME_ERROR_SIZE_TOOLAGER;
		return ;
	}
	//printf_buf("build_pasre",(char *)buf,buflen);
	/*完整性验证
	*1.查找头
	*2.解析长度
	*3.判断结束符是否正常
	*/
	/*查找头*/
	for(i=0;i<buflen-1;i++){
		if(buf[i]==0xf4 && buf[i+1]==0xf5){
			packet_struct_head=i+2;
			break;
		}
	}
	if(packet_struct_head==-1){
		packet_message_struct->error=HEAD_ERROR_PRE;
		return ;
	}
	pbuf=buf+packet_struct_head-sizeof(struct frame_head);
	packet_frame_head=(struct frame_head *)pbuf;

    if (pbuf[2]==0xb){//resend 10 times when message result ==11    
		int i,newlen=buflen;//new等于去掉尾的长度
		while(newlen>2){
			if(pbuf[newlen]==0xfb && pbuf[newlen-1]==0xf4){
				break;
			}
			newlen--;
		}
		newlen++;
		XM_D("xlf_pasre!!:error send timeout !!resend!!pbuf[2]=0x%x data_size=%d\r\n",pbuf[2],packet_message_struct->data_size);
		pbuf[2]=0;
		packet_message_struct->data_size=newlen;
		memcpy(packet_message_struct->data,pbuf,packet_message_struct->data_size);
		#if DEBUG_CMD
		printf_buf("MSG_BODY",(char *)packet_message_struct->data,packet_message_struct->data_size);
		#endif
		if (resend_count<ERROR_MSG_TIME_OUT)
			packet_message_struct->error=ERROR_MSG_TIME_OUT;
		else 
			packet_message_struct->error=ERROR_MSG_TIME_OUT_MAX;
		return;
    }else{
#if DEBUG_CMD
	printf_buf("frame_head",(char *)pbuf,sizeof(struct frame_head));
#endif
	pbuf+=sizeof(struct frame_head);
	packet_frame_struct=(struct frame_struct *)pbuf;
	//printf_buf("frame_struct",(char *)pbuf,sizeof(struct frame_struct));
	
	/*先进行帧结构的转义字符处理*/
	for(i=0;i<sizeof(struct frame_struct);i++){
		if(pbuf[i]==0xf4 && pbuf[i+1]==0xf4){
			memcpy(&pbuf[i],&pbuf[i+1],buflen-i-(pbuf-buf)-1);
			buf[buflen-1]=0;
		}
	}
	//if(packet_frame_struct->ack!=1){
		//packet_message_struct->error=FRAME_ERROR_PRE|packet_frame_struct->ack;
		//return ;
	//}
	//printf("build_pasre:packet len %u\r\n",packet_frame_struct->len);
	if(packet_frame_struct->len>max_size){
		packet_message_struct->error=FRAME_ERROR_PRE|FRAME_ERROR_SIZE_TOOLAGER;
		return ;
	}
	pbuf+=sizeof(struct frame_struct);
	packet_struct_len=packet_frame_struct->len+sizeof(struct network_struct)+sizeof(struct transfer_struct)+sizeof(struct frame_crc);
	/*进行网络/ 传输/ 消息/验证转义字符的处理*/
	for(i=0;i<packet_struct_len;i++){
		if(pbuf[i]==0xf4 && pbuf[i+1]==0xf4){
			memcpy(&pbuf[i],&pbuf[i+1],buflen-i-(pbuf-buf)-1);
			buf[buflen-1]=0;
		}
	}	
	packet_network_struct=(struct network_struct *)pbuf;
	//printf_buf("network_struct",(char *)pbuf,sizeof(struct network_struct));	
	packet_message_struct->source_module=packet_network_struct->destination_module;
	packet_message_struct->source_no=packet_network_struct->destination_no;
	packet_message_struct->destination_module=packet_network_struct->source_module;
	packet_message_struct->destination_no=packet_network_struct->source_no;
	if(packet_network_struct->ack==XM_ERROR_MODUEL_NOT_SUPPORT){
		packet_message_struct->error=XM_ERROR_MODUEL_NOT_SUPPORT;
		//return ;
	}
//	if(packet_network_struct->ack!=1){
//		packet_message_struct->error=NETWORK_ERROR_PRE|packet_network_struct->ack;
	//	return ;
	//}
	/*获取传输结构*/
	pbuf+=sizeof(struct network_struct);
	packet_transfer_struct=(struct transfer_struct *)pbuf;
	#if DEBUG_CMD
	 printf_buf("transfer_struct",(char *)pbuf,sizeof(struct transfer_struct));
	#endif
	 if(packet_transfer_struct->ack==XM_ERROR_MODUEL_NOT_SUPPORT){
	 	#if DEBUG_CMD
		XM_D("XM_ERROR_MODUEL_NOT_SUPPORT!!!\r\n");
		#endif
		packet_message_struct->error=XM_ERROR_MODUEL_NOT_SUPPORT;
		//return ;
	}
	//if(packet_transfer_struct->ack!=1){
		//packet_message_struct->error=TRANSFER_ERROR_PRE|packet_transfer_struct->ack;
		//return ;
	//}
	/*获取消息*/
	pbuf+=sizeof(struct transfer_struct);
	packet_message_struct->data_size=packet_frame_struct->len-sizeof(struct network_struct)-sizeof(struct transfer_struct);
	//printf("build_pasre:data len %u\r\n",packet_message_struct->data_size);
	memcpy(packet_message_struct->data,pbuf,packet_message_struct->data_size);
	
	/*较验数据*/
	pbuf+=packet_message_struct->data_size;
	packet_frame_crc=(struct frame_crc *)pbuf;
	switch((packet_frame_struct->flag>>6) & 0x3){
	case FCS_2BYTES_ADD:
		xlf_crc((uchar *)packet_frame_struct,(uchar *)packet_frame_crc-(uchar *)packet_frame_struct,&verification_frame_crc);
		break;
	case FCS_2BYTES_CRC:
		crc16 = do_crc16_1021((uchar *)packet_frame_struct,(uchar *)packet_frame_crc-(uchar *)packet_frame_struct,0);
		verification_frame_crc.crc_high = (crc16>>8)&0xff;
		verification_frame_crc.crc_low= crc16&0xff;
		break;
	}
	
	if(memcmp(&verification_frame_crc,packet_frame_crc,sizeof(struct frame_crc))!=0){
		packet_message_struct->error=packet_message_struct->error|CRC_ERROR_PRE;
		XM_D("verification_frame_crc:0x%x 0x%x  packet_frame_crc:0x%x 0x%x\r\n",verification_frame_crc.crc_high,verification_frame_crc.crc_low,packet_frame_crc->crc_high,packet_frame_crc->crc_low);
		return ;
	}
	/*检查帧尾*/
	pbuf+=sizeof(struct frame_crc);
	packet_frame_end=(struct frame_end *)pbuf;
	if(packet_frame_end->end1!=0xf4 || packet_frame_end->end2!=0xfb){
		packet_message_struct->error=packet_message_struct->error|END_ERROR_PRE;
		return ;
	}
	packet_message_struct->use_size=packet_struct_len+sizeof(struct frame_head)+sizeof(struct frame_end);
    	}
}
void xlf_get_string(char *retbuf,uchar value,XM_Offset *pOffset){
	int i=0;
	if(pOffset->textlen!=0 && pOffset){
#if DEBUG_CMD
		XM_D("get_string:%d %d\r\n",pOffset->textlen,value);
#endif
		for(i=0;i<pOffset->textlen;i++){
			if(value==pOffset->text[i].value){
#if DEBUG_CMD
				XM_D("get_string:Value %s %d\r\n",pOffset->text[i].str,pOffset->text[i].value);
#endif				
				snprintf(retbuf+strlen(retbuf),XM_MAX_BUF-strlen(retbuf),"%s,",pOffset->text[i].str);
				return;
			}
		}
		snprintf(retbuf+strlen(retbuf),XM_MAX_BUF-strlen(retbuf),"ERR,");
	}
	else{
	snprintf(retbuf+strlen(retbuf),XM_MAX_BUF-strlen(retbuf),"%d,",value);
		}
}

void xlf_parse_para(char *retbuf,XM_AT_RET * p_at_ret,char *value,XM_Offset *pOffset){
	uchar nValue,retlen=0;
	uint slen,i=0;
	uchar nByteOffset=0,nBitOffset,nMask;
#if DEBUG_CMD
	XM_D("parse_para: value %s len %d\r\n",value,pOffset->len);
#endif
	if(pOffset->len){
#if DEBUG_CMD
		XM_D("parse_para: pOffset %d\r\n",pOffset->offset);
#endif
		nBitOffset =7-pOffset->offset%8;
		nByteOffset=pOffset->offset/8;	
		nMask=(0xff>>(8-pOffset->len))<<nBitOffset;
#if DEBUG_CMD
		XM_D("parse_para:Offset 0x%02x\r\n",nBitOffset);	
		XM_D("parse_para:Byte 0x%02x\r\n",nByteOffset);
		XM_D("parse_para:nMask 0x%02x\r\n",nMask);
#endif
		retlen=nByteOffset+1;
#if DEBUG_CMD
		XM_D("Parse_Recv:slen %d\r\n",slen);
#endif			
		if(pOffset->len<=8){
			nValue=(value[nByteOffset] & nMask) >>nBitOffset;
#if DEBUG_CMD
			XM_D("Parse_Recv:nValue %d %d\r\n",nValue,value[nByteOffset]);
#endif
			xlf_get_string(retbuf,nValue,pOffset);
#if DEBUG_CMD
			XM_D("Parse_Recv :int Buffer %s\r\n",(char *)retbuf);
#endif
		}else{
		#if DEBUG_CMD
			XM_D("parse_para: major %d minor %d\r\n",p_at_ret->major,p_at_ret->minor);
		#endif
			int length= BIN2HEX((value+(pOffset->offset-pOffset->len+1)/8),pOffset->len/8,(char *)retbuf+strlen(retbuf));
			retbuf[strlen(retbuf)]=',';
#if DEBUG_CMD
			XM_D("Parse_Recv:str Buffer %d %s\r\n",nValue,(char *)retbuf);
#endif
		}
	}
}
void xlf_crc(uchar *pbuf,uchar len,struct frame_crc *crc_buf){	
	uchar i;
	short ncrc=0;
	for(i=0;i<len;i++){
		ncrc+=pbuf[i];
	}
	//printf("xm_crc:len:%d,value:0x%02x\r\n",len,ncrc);
	crc_buf->crc_high=((ncrc&0xff00)>>8);
	crc_buf->crc_low=ncrc&0xff;
}

int xlf_build(int type_checksum ,char sequence,uchar *sendbuf,uchar *buf,int buflen,uchar moblie_type,uchar moblie_address,uchar device_type,uchar device_address){
	uchar *message_buf=NULL;
	unsigned short crc16 = 0;
	uchar *pbuf=NULL;
	uchar crc_len=0;
	uchar replace_len=0;
	int replace_seek=0;
	int curr_size=0;
	int max_size=0;
	uchar ack=0;
	struct frame_head *packet_frame_head=NULL;
	struct frame_struct *packet_frame_struct=NULL;	
	struct network_struct *packet_network_struct=NULL;
	struct transfer_struct *packet_transfer_struct=NULL;
	struct frame_crc *packet_frame_crc=NULL;
	struct frame_end *packet_frame_end=NULL;
	//memset(sendbuf,0,PACKET_MAX_LEN);
	pbuf=sendbuf;
	max_size=PACKET_MAX_LEN-sizeof(struct frame_head)-sizeof(struct frame_struct)-sizeof(struct network_struct)-sizeof(struct transfer_struct)-sizeof(struct frame_crc)-sizeof(struct frame_end);
	if(buflen>max_size || buflen <1){
		printf("build_packet:error size error%d\r\n",buflen);
		return 0;
	}
	//if (packet_count>=15)
	//	packet_count=-1;
	curr_size=buflen+sizeof(struct frame_head)+sizeof(struct frame_struct)+sizeof(struct network_struct)+sizeof(struct transfer_struct)+sizeof(struct frame_crc)+sizeof(struct frame_end);
	packet_frame_head=(struct frame_head *)pbuf;
	packet_frame_head->head1=0xf4;
	packet_frame_head->head2=0xf5;
	pbuf+=sizeof(struct frame_head);
	//printf("build_packet:frame_struct seek %u\r\n",pbuf-sendbuf);
	packet_frame_struct=(struct frame_struct *)pbuf;
	packet_frame_struct->ack=ack;
	//packet_count++;	 
	//packet_frame_struct->flag=(0x40|(packet_count<<1));
	if(type_checksum == FCS_2BYTES_ADD)
		packet_frame_struct->flag= 0x40 |((sequence &0xf)<<1);
	else
		packet_frame_struct->flag= 0x80 |((sequence &0xf)<<1);
	pbuf+=sizeof(struct frame_struct);
	//printf("build_packet:network_struct seek %u\r\n",pbuf-sendbuf);
	packet_network_struct=(struct network_struct *)pbuf;
	packet_network_struct->ack=ack;
	packet_network_struct->source_module=moblie_type;	
	packet_network_struct->source_no=moblie_address;
	packet_network_struct->destination_module=device_type;
	packet_network_struct->destination_no=device_address;
	pbuf+=sizeof(struct network_struct);
	//printf("build_packet:transfer_struct seek %u\r\n",pbuf-sendbuf);
	packet_transfer_struct=(struct transfer_struct *)pbuf;
	packet_transfer_struct->ack=ack;	
	pbuf+=sizeof(struct transfer_struct);
	//printf("build_packet:message seek %u\r\n",pbuf-sendbuf);
	message_buf=pbuf;
	memcpy(message_buf,buf,buflen);
	pbuf+=buflen;
	packet_frame_struct->len=pbuf-(uchar *)packet_network_struct;
	//printf("build_packet:len %u\r\n",packet_frame_struct->len);
	crc_len=pbuf-(uchar *)packet_frame_struct;
	packet_frame_crc=(struct frame_crc *)pbuf;
	pbuf=(uchar *)packet_frame_struct;
	//printf("build_packet:frame_crc seek %u\r\n",(uchar *)packet_frame_crc-sendbuf);
	if(type_checksum == FCS_2BYTES_ADD){
		xlf_crc(pbuf,crc_len,packet_frame_crc);
	}else if(type_checksum == FCS_2BYTES_CRC){
		crc16 = do_crc16_1021(pbuf,crc_len,0);
		packet_frame_crc->crc_high = (crc16>>8) & 0xff;
		packet_frame_crc->crc_low = crc16 & 0xff;
	}
	pbuf=(uchar *)packet_frame_crc+sizeof(struct frame_crc);	
	replace_seek=replace_len=pbuf-(uchar *)packet_frame_struct;
	pbuf=(uchar *)packet_frame_struct;
	while(--replace_seek>0){
		if(pbuf[replace_seek]==packet_frame_head->head1){
			move_data(&pbuf[replace_seek],replace_len-replace_seek,1);
			replace_len++;
			curr_size++;
			if(curr_size>PACKET_MAX_LEN){
				XM_D("build_packet:error size over %d\r\n",curr_size);
				return 0;
			}
		}
	}
	//printf("build_packet:replace_len %u\r\n",replace_len);
	pbuf+=replace_len;
	//printf("build_packet:frame_end seek %u\r\n",pbuf-sendbuf);
	packet_frame_end=(struct frame_end *)pbuf;
	packet_frame_end->end1=0xf4;
	packet_frame_end->end2=0xfb;
	pbuf+=sizeof(struct frame_end);
	//printf("build_packet:success size %u\r\n",pbuf-sendbuf);
	//printf_buf("build_packet",sendbuf,pbuf-sendbuf);
	return pbuf-sendbuf;
}


int xlf_packet_build_frame(int type_checksum,char sequence,char *sendbuf,char *buf,int buflen,int moblie_type,int moblie_address,int device_type,int device_address,int frame,int sub_frame){
	int i,retlen=0;
	XM_PROTOCOL xm;
	XM_NODE node;
	uchar *pdata=NULL,*psend=NULL;
	int sendlen;
	memset(&xm,0,sizeof(XM_PROTOCOL));
	xm.xm_socket_client=-1;
	xm.xm_addres=device_address;
	xm.xm_frame=frame;
	xm.xm_sub_frame=sub_frame;	
	xm_address1[0]=moblie_type;
	xm_address1[1]=moblie_address;
	xm_address2[0]=device_type;
	xm_address2[1]=device_address;
	xm.xm_seting=1; 
	xm.xm_exit=0;
	xm.xm_index=0;
	node.address=0;		
	node.index=0;
	node.argc=0;
	node.errorid=XM_ERROR_RECV_TIMEOUT;
	node.xm_set=0;
	node.xm_sendlen=0;
	node.xm_sendready=0;
	node.is_wait=0;
	node.end=NULL;
	memset(&node.xm_at,0,sizeof(XM_AT));
	xm.node=&node;
	node.atbuf=buf;
	node.atlen=buflen;

	if((memcmp(buf,"AT+XM",5)==0)||(memcmp(buf,"AT+WHO",6)==0)||(memcmp(buf,"AT+WF",5)==0)){			
			node.errorid=XM_ERROR_CMD_EXEC;			
			snprintf(sendbuf,1024,"%s",buf);
			retlen=strlen(sendbuf);
			XM_D("WIFICOMMAND STRING! %s\r\n",sendbuf);
			return retlen;
		}
	
	strDividing(&xm,&node,node.atbuf,node.atlen);
	XM_D("xlf_packet_build:argc %d!!\r\n",node.argc);
	if(node.argc){
		for( i=0;i<node.argc;i++){
			if(strncmp(node.xm_at.getparam[i],"?",1)==0){
				node.xm_set=XM_SEND_QUERY;
				xm.sendcmd=node.xm_cmd->parameter->query_cmd;;
				xm.sendsub=node.xm_cmd->parameter->query_sub;
#if DEBUG_CMD
				XM_D("xlf_packet_build:XM_SEND_QUERY!!\r\n");
#endif
				break;
			}else if(strncmp(node.xm_at.getparam[i],"*",1)==0){
				node.xm_set=XM_SEND_SUPPORT;
				xm.sendcmd=node.xm_cmd->parameter->support_cmd;;
				xm.sendsub=node.xm_cmd->parameter->support_sub;
#if DEBUG_CMD
				XM_D("xlf_packet_build:XM_SEND_SUPPORT!!\r\n");
#endif				
				break;
			}else{
				node.xm_set=XM_SEND_SETTING;
				xm.sendcmd=node.xm_cmd->parameter->set_cmd;;
				xm.sendsub=node.xm_cmd->parameter->set_sub;
#if DEBUG_CMD
				XM_D("xlf_packet_build:XM_SEND_SETTING!!\r\n");
#endif				
			}
		}
	}	else{
		node.xm_set=XM_SEND_SETTING;
	}	
#if XM_WITH_ID
	if((node.argc<2) ||(node.errorid!=XM_SUCCESS)){
		XM_E("UNPACKETD STRING\r\n");
		node.errorid=XM_ERROR_AT_PRAR;		
		snprintf(sendbuf,1024,"%s",buf);
		retlen=strlen(sendbuf);
		XM_E("UNPACKETD STRING!ERROR %s\r\n",sendbuf);
		return retlen;
	}
	if(node.xm_set==XM_SEND_SETTING)
		node.xm_sendlen=Build_Send(&xm,&node,node.argc-1,&node.xm_at.getparam[1]);
	else
		node.xm_sendlen=Build_Send(&xm,&node,node.argc-2,&node.xm_at.getparam[2]);
#else
	node.xm_sendlen=Build_Send(&xm,&node,node->argc,node.xm_at.getparam);
#endif
#if DEBUG_CMD
	XM_D("build_packet:sendlen %d\r\n",node.xm_sendlen);
#endif
	//add by mujian for copy node data to pxm data	
	memset(xm.XM_Status_Value,'\0',XM_MAX_BUF);
	snprintf((char *)xm.XM_Status_Value,XM_MAX_BUF,"%d",node.xm_sendlen);
	sendlen=node.xm_sendlen;
	psend=(uchar *)(xm.XM_Setting_Buffer);
	pdata=(uchar *)(node.xm_at.XM_At_Ret);
#if DEBUG_CMD
		printf_buf("node send data",(uchar *)node.xm_at.XM_At_Ret,node.xm_sendlen);
#endif
	while(sendlen>0){
#if DEBUG_CMD
		XM_D("Build_send: sendlen %d\r\n",node.xm_sendlen);
#endif
#if 0
		tempb=*psend;
#if DEBUG_CMD
		XM_D("Build_send:psend %02x\r\n",(uchar )tempb);
#endif
		tempa=*pdata;
#if DEBUG_CMD
		XM_D("Build_send:pdata %02x\r\n",(uchar )tempa);
#endif
#endif
		*psend++|=*pdata++;
		sendlen-=sizeof(uchar);			
	}
	
	//add by mujian for copy node data to pxm data
	statusInit(&xm);
	retlen=xlf_build(type_checksum,sequence,xm.XM_Frame_Buffer,(uchar *)xm.XM_Status_Value,New_Msg_Head(&xm,(uchar *)xm.XM_Status_Value,xm.sendcmd,xm.sendsub,(uchar *)xm.XM_Setting_Buffer,atoi(xm.XM_Status_Value)),moblie_type,moblie_address,device_type,device_address);
	retlen=BIN2HEX(xm.XM_Frame_Buffer,retlen,sendbuf);
	if(retlen){
		sendbuf[retlen]='\r';
		sendbuf[retlen+1]='\n';
		retlen+=2;
	}
	return retlen;
}



int xlf_packet_build(int type_checksum,char sequence,char *sendbuf,char *buf,int buflen,int device_type,int device_address,int moblie_type,int moblie_address){
	int i,retlen=0;
	XM_PROTOCOL xm;
	XM_NODE node;
	uchar *pdata=NULL,*psend=NULL;
	int sendlen;
	memset(&xm,0,sizeof(XM_PROTOCOL));
	xm.xm_socket_client=-1;
	xm.xm_addres=device_address;
	xm.xm_frame=moblie_address;	
	xm.xm_sub_frame=255;	
	xm_address1[0]=device_type;
	xm_address1[1]=device_address;
	xm_address2[0]=moblie_type;
	xm_address2[1]=moblie_address;	
	xm.xm_seting=1; 
	xm.xm_exit=0;
	xm.xm_index=0;
	node.address=0;		
	node.index=0;
	node.argc=0;
	node.errorid=XM_ERROR_RECV_TIMEOUT;
	node.xm_set=0;
	node.xm_sendlen=0;
	node.xm_sendready=0;
	node.is_wait=0;
	node.end=NULL;
	memset(&node.xm_at,0,sizeof(XM_AT));
	xm.node=&node;
	node.atbuf=buf;
	node.atlen=buflen;

	if((memcmp(buf,"AT+XM",5)==0)||(memcmp(buf,"AT+WHO",6)==0)||(memcmp(buf,"AT+WF",5)==0)){			
			node.errorid=XM_ERROR_CMD_EXEC;			
			snprintf(sendbuf,1024,"%s",buf);
			retlen=strlen(sendbuf);
			XM_D("WIFICOMMAND STRING! %s\r\n",sendbuf);
			return retlen;
		}
	
	strDividing(&xm,&node,node.atbuf,node.atlen);
#if DEBUG_CMD
	XM_D("xlf_packet_build:argc %d!!\r\n",node.argc);
#endif
	if(node.argc){
		for( i=0;i<node.argc;i++){
			if(strncmp(node.xm_at.getparam[i],"?",1)==0){
				node.xm_set=XM_SEND_QUERY;
				xm.sendcmd=node.xm_cmd->parameter->query_cmd;;
				xm.sendsub=node.xm_cmd->parameter->query_sub;
#if DEBUG_CMD
				XM_D("xlf_packet_build:XM_SEND_QUERY!!\r\n");
#endif
				break;
			}else if(strncmp(node.xm_at.getparam[i],"*",1)==0){
				node.xm_set=XM_SEND_SUPPORT;
				xm.sendcmd=node.xm_cmd->parameter->support_cmd;;
				xm.sendsub=node.xm_cmd->parameter->support_sub;
#if DEBUG_CMD
				XM_D("xlf_packet_build:XM_SEND_SUPPORT!!\r\n");
#endif				
				break;
			}else{
				node.xm_set=XM_SEND_SETTING;
				xm.sendcmd=node.xm_cmd->parameter->set_cmd;;
				xm.sendsub=node.xm_cmd->parameter->set_sub;
#if DEBUG_CMD
				XM_D("xlf_packet_build:XM_SEND_SETTING!!\r\n");
#endif				
			}
		}
	}	else{
		node.xm_set=XM_SEND_SETTING;
	}	
#if XM_WITH_ID
	if((node.argc<2) ||(node.errorid!=XM_SUCCESS)){
		node.errorid=XM_ERROR_AT_PRAR;		
		snprintf(sendbuf,1024,"+ERROR:ERROR,PACKAGE\r\n");
		retlen=strlen(sendbuf);
		XM_E("UNPACKETD STRING!ERROR %s\r\n",sendbuf);
		return retlen;
	}
	if(node.xm_set==XM_SEND_SETTING)
		node.xm_sendlen=Build_Send(&xm,&node,node.argc-1,&node.xm_at.getparam[1]);
	else
		node.xm_sendlen=Build_Send(&xm,&node,node.argc-2,&node.xm_at.getparam[2]);
#else
	node.xm_sendlen=Build_Send(&xm,&node,node->argc,node.xm_at.getparam);
#endif
#if DEBUG_CMD
	XM_D("build_packet:sendlen %d\r\n",node.xm_sendlen);
#endif
	//add by mujian for copy node data to pxm data	
	memset(xm.XM_Status_Value,'\0',XM_MAX_BUF);
	snprintf((char *)xm.XM_Status_Value,XM_MAX_BUF,"%d",node.xm_sendlen);
	sendlen=node.xm_sendlen;
	psend=(uchar *)(xm.XM_Setting_Buffer);
	pdata=(uchar *)(node.xm_at.XM_At_Ret);
#if DEBUG_CMD
		printf_buf("node send data",(uchar *)node.xm_at.XM_At_Ret,node.xm_sendlen);
#endif
	while(sendlen>0){
#if 0
		tempb=*psend;
#if DEBUG_CMD
		XM_D("Build_send:psend %02x\r\n",(uchar )tempb);
#endif
		tempa=*pdata;
#if DEBUG_CMD
		XM_D("Build_send:pdata %02x\r\n",(uchar )tempa);
#endif
#endif
		*psend++|=*pdata++;
		sendlen-=sizeof(uchar);			
	}
	
	//add by mujian for copy node data to pxm data
	statusInit(&xm);
	retlen=xlf_build(type_checksum,sequence,xm.XM_Frame_Buffer,(uchar *)xm.XM_Status_Value,New_Msg_Head(&xm,(uchar *)xm.XM_Status_Value,xm.sendcmd,xm.sendsub,(uchar *)xm.XM_Setting_Buffer,atoi(xm.XM_Status_Value)),moblie_type,moblie_address,device_type,device_address);
	retlen=BIN2HEX(xm.XM_Frame_Buffer,retlen,sendbuf);
	if(retlen){
		sendbuf[retlen]='\r';
		sendbuf[retlen+1]='\n';
		retlen+=2;
	}
	return retlen;
}
void xlf_pasre_msg(struct message_struct * packet_message_struct,MessageHead * pdata){
	int i=0;
	uchar MessageHead_len=sizeof(MessageHead);	
	#if DEBUG_CMD
	XM_D(" MessageType %d datasize %d\r\n",packet_message_struct->data[0],packet_message_struct->data_size);	
	#endif
	if (packet_message_struct->data[0] < 200 && packet_message_struct->data[0] != 1)//\\211 change to 200
		{
	#if DEBUG_CMD
		XM_E("msg: unframe packet! len-2!!\r\n");
	#endif
	//	MessageHead_len=sizeof(MessageHead)-2;
		MessageHead_len -= 2;
		}
	//else
	//	{
	//	pxm->xm_frame=pdata->frame;
	//	pxm->xm_sub_frame=pdata->sub_frame;
	//	}
	if(packet_message_struct->data_size<MessageHead_len){
		XM_E("msg: buffer too small!!\r\n");
		packet_message_struct->error=XM_ERROR_BUF_SMALL;
		return;
	}
	memcpy(pdata,packet_message_struct->data,MessageHead_len);	
	#if 0
	memcpy(packet_message_struct->data,packet_message_struct->data+MessageHead_len,packet_message_struct->data_size-MessageHead_len);
	#else
	for(i=0;i<packet_message_struct->data_size-MessageHead_len;i++)
			packet_message_struct->data[i]=packet_message_struct->data[MessageHead_len+i];
	#endif
	packet_message_struct->data_size-=MessageHead_len;	
	#if DEBUG_CMD
	printf_buf("xlf_pasre_msg:data",(char *)packet_message_struct->data,packet_message_struct->data_size);
	#endif
 }


int xlf_packet_pasre_deviceaddress(char *retbuf,char *pbuf,int len){
	struct message_struct ret_data;
	MessageHead msg;	
	#if DEBUG_CMD
	printf_buf("xlf_packet_pasre string",(uchar *)pbuf,len);
	#endif
	XM_AT_RET * p_at_ret;
	int datalen,i,j,k,packetlen;
	char binbuf[512];
	memset(binbuf,0,512);
	packetlen=HEX2BIN(pbuf,binbuf);
	#if DEBUG_CMD
	printf_buf("xlf_packet_pasre hex",(uchar *)binbuf,packetlen);
	#endif
	memset(&ret_data,0,sizeof(struct message_struct));
	xlf_pasre_info(&ret_data,binbuf,packetlen);
	XM_D("xlf_packet_pasre:error %d\r\n",ret_data.error);
	if(ret_data.error==0){
		snprintf(retbuf,XM_MAX_BUF,"%d",ret_data.source_no);
		return strlen(retbuf);
		}
   else if (ret_data.error==ERROR_MSG_TIME_OUT)
   	{
   	char sendbuf[XM_MAX_BUF]; 
   	int retlen=BIN2HEX((char *)(ret_data.data),ret_data.data_size,sendbuf);   	
   	snprintf(retbuf,XM_MAX_BUF,"+%s:ERROR,%s","timeout",sendbuf);
	if(strlen(retbuf)){
				retbuf[strlen(retbuf)-1]='\r';
				retbuf[strlen(retbuf)]='\n';
			}
	#if DEBUG_CMD
	printf_buf("ret_buf",retbuf,strlen(retbuf));	
	#endif
	return strlen(retbuf);
   	}
	return 0;
}




int xlf_packet_pasre_sourcedevicetype(char *retbuf,char *pbuf,int len){
	struct message_struct ret_data;
	MessageHead msg;	
	#if DEBUG_CMD
	printf_buf("xlf_packet_pasre string",(uchar *)pbuf,len);
	#endif
	XM_AT_RET * p_at_ret;
	int datalen,i,j,k,packetlen;
	char binbuf[512];
	memset(binbuf,0,512);
	packetlen=HEX2BIN(pbuf,binbuf);
	#if DEBUG_CMD
	printf_buf("xlf_packet_pasre hex",(uchar *)binbuf,packetlen);
	#endif
	memset(&ret_data,0,sizeof(struct message_struct));
	xlf_pasre_info(&ret_data,binbuf,packetlen);
	XM_D("xlf_packet_pasre:error %d\r\n",ret_data.error);
	if(ret_data.error==0){
		snprintf(retbuf,XM_MAX_BUF,"%d",ret_data.source_module);
		return strlen(retbuf);
		}
   else if (ret_data.error==ERROR_MSG_TIME_OUT)
   	{
   	char sendbuf[XM_MAX_BUF]; 
   	int retlen=BIN2HEX((char *)(ret_data.data),ret_data.data_size,sendbuf);   	
   	snprintf(retbuf,XM_MAX_BUF,"+%s:ERROR,%s","timeout",sendbuf);
	if(strlen(retbuf)){
				retbuf[strlen(retbuf)-1]='\r';
				retbuf[strlen(retbuf)]='\n';
			}
	#if DEBUG_CMD
	printf_buf("ret_buf",retbuf,strlen(retbuf));	
	#endif
	return strlen(retbuf);
   	}
	return 0;
}



int xlf_packet_pasre_sourcedeviceaddress(char *retbuf,char *pbuf,int len){
	struct message_struct ret_data;
	MessageHead msg;	
	#if DEBUG_CMD
	printf_buf("xlf_packet_pasre string",(uchar *)pbuf,len);
	#endif
	XM_AT_RET * p_at_ret;
	int datalen,i,j,k,packetlen;
	char binbuf[512];
	memset(binbuf,0,512);
	packetlen=HEX2BIN(pbuf,binbuf);
	#if DEBUG_CMD
	printf_buf("xlf_packet_pasre hex",(uchar *)binbuf,packetlen);
	#endif
	memset(&ret_data,0,sizeof(struct message_struct));
	xlf_pasre_info(&ret_data,binbuf,packetlen);
	XM_D("xlf_packet_pasre:error %d\r\n",ret_data.error);
	if(ret_data.error==0){
		snprintf(retbuf,XM_MAX_BUF,"%d",ret_data.source_no);
		return strlen(retbuf);
		}
   else if (ret_data.error==ERROR_MSG_TIME_OUT)
   	{
   	char sendbuf[XM_MAX_BUF]; 
   	int retlen=BIN2HEX((char *)(ret_data.data),ret_data.data_size,sendbuf);   	
   	snprintf(retbuf,XM_MAX_BUF,"+%s:ERROR,%s","timeout",sendbuf);
	if(strlen(retbuf)){
				retbuf[strlen(retbuf)-1]='\r';
				retbuf[strlen(retbuf)]='\n';
			}
	#if DEBUG_CMD
	printf_buf("ret_buf",retbuf,strlen(retbuf));	
	#endif
	return strlen(retbuf);
   	}
	return 0;
}

int xlf_packet_pasre_destinationdevicetype(char *retbuf,char *pbuf,int len){
	struct message_struct ret_data;
	MessageHead msg;	
	#if DEBUG_CMD
	printf_buf("xlf_packet_pasre string",(uchar *)pbuf,len);
	#endif
	XM_AT_RET * p_at_ret;
	int datalen,i,j,k,packetlen;
	char binbuf[512];
	memset(binbuf,0,512);
	packetlen=HEX2BIN(pbuf,binbuf);
	#if DEBUG_CMD
	printf_buf("xlf_packet_pasre hex",(uchar *)binbuf,packetlen);
	#endif
	memset(&ret_data,0,sizeof(struct message_struct));
	xlf_pasre_info(&ret_data,binbuf,packetlen);
	XM_D("xlf_packet_pasre:error %d\r\n",ret_data.error);
	if(ret_data.error==0){
		snprintf(retbuf,XM_MAX_BUF,"%d",ret_data.destination_module);
		return strlen(retbuf);
		}
   else if (ret_data.error==ERROR_MSG_TIME_OUT)
   	{
   	char sendbuf[XM_MAX_BUF]; 
   	int retlen=BIN2HEX((char *)(ret_data.data),ret_data.data_size,sendbuf);   	
   	snprintf(retbuf,XM_MAX_BUF,"+%s:ERROR,%s","timeout",sendbuf);
	if(strlen(retbuf)){
				retbuf[strlen(retbuf)-1]='\r';
				retbuf[strlen(retbuf)]='\n';
			}
	#if DEBUG_CMD
	printf_buf("ret_buf",retbuf,strlen(retbuf));	
	#endif
	return strlen(retbuf);
   	}
	return 0;
}



int xlf_packet_pasre_destinationdeviceaddress(char *retbuf,char *pbuf,int len){
	struct message_struct ret_data;
	MessageHead msg;	
	#if DEBUG_CMD
	printf_buf("xlf_packet_pasre string",(uchar *)pbuf,len);
	#endif
	XM_AT_RET * p_at_ret;
	int datalen,i,j,k,packetlen;
	char binbuf[512];
	memset(binbuf,0,512);
	packetlen=HEX2BIN(pbuf,binbuf);
	#if DEBUG_CMD
	printf_buf("xlf_packet_pasre hex",(uchar *)binbuf,packetlen);
	#endif
	memset(&ret_data,0,sizeof(struct message_struct));
	xlf_pasre_info(&ret_data,binbuf,packetlen);
	XM_D("xlf_packet_pasre:error %d\r\n",ret_data.error);
	if(ret_data.error==0){
		snprintf(retbuf,XM_MAX_BUF,"%d",ret_data.destination_no);
		return strlen(retbuf);
		}
   else if (ret_data.error==ERROR_MSG_TIME_OUT)
   	{
   	char sendbuf[XM_MAX_BUF]; 
   	int retlen=BIN2HEX((char *)(ret_data.data),ret_data.data_size,sendbuf);   	
   	snprintf(retbuf,XM_MAX_BUF,"+%s:ERROR,%s","timeout",sendbuf);
	if(strlen(retbuf)){
				retbuf[strlen(retbuf)-1]='\r';
				retbuf[strlen(retbuf)]='\n';
			}
	#if DEBUG_CMD
	printf_buf("ret_buf",retbuf,strlen(retbuf));	
	#endif
	return strlen(retbuf);
   	}
	return 0;
}


int xlf_packet_pasre(char *retbuf,char *pbuf,int len,int address){
	struct message_struct ret_data;
	MessageHead msg;
	if(address==0)
		address=0xff;
	#if DEBUG_CMD
	XM_D("xlf_packet_pasre:type %d",address);	
	printf_buf("xlf_packet_pasre string",(uchar *)pbuf,len);
	#endif
	XM_AT_RET * p_at_ret;
	int datalen,i,j,k,packetlen;
	char binbuf[512];
	memset(binbuf,0,512);
	// here should check the length if it too long 
	packetlen=HEX2BIN(pbuf,binbuf);
	#if DEBUG_CMD
	printf_buf("xlf_packet_pasre hex",(uchar *)binbuf,packetlen);
	#endif
	memset(&ret_data,0,sizeof(struct message_struct));
	xlf_pasre(&ret_data,binbuf,packetlen);
	if(memcmp(pbuf,"+DISCONNECT",11)==0){			
				ret_data.error=HEAD_ERROR_DISCONNECT;
				XM_D("xlf_packet_pasre:error HEAD_ERROR_DISCONNECT=%d\r\n",ret_data.error);
		}
	else if (memcmp(pbuf,"+",1)==0)
		{		
		snprintf(retbuf,XM_MAX_BUF,"%s\r\n",pbuf);
	#if DEBUG_CMD
		XM_D("xlf_packet_pasre:return input string!\r\n");
		printf_buf("ret_buf",retbuf,strlen(retbuf));		
	#endif
		return strlen(retbuf);
		}
	
#if DEBUG_CMD
	XM_D("xlf_packet_pasre:error %d!\r\n",ret_data.error);
#endif
	if((ret_data.error==0)|| ((ret_data.error!=ERROR_MSG_TIME_OUT) && (ret_data.error!=HEAD_ERROR_PRE))){
		xlf_pasre_msg(&ret_data,&msg);
	#if DEBUG_CMD
		XM_D("xlf_packet_pasre:data_size %d\r\n",ret_data.data_size);
	#endif
		if (ret_data.data_size>=0){
		#if DEBUG_CMD
		XM_D("xlf_packet_pasre: type %d sub %d\r\n",msg.MessageType,msg.MessageSubType);
		#endif
		for(i=0;i<sizeof(xm_at_ret_list)/sizeof(xm_at_ret_list[0]);i++){
			#if DEBUG_CMD
			XM_D("xlf_packet_pasre:i %d address %d type %d\r\n",i,address,xm_at_ret_list[i].type);
			#endif
			if((address==xm_at_ret_list[i].type)||(msg.MessageType==30 ||msg.MessageType==10 ||msg.MessageType==3 || msg.MessageType==7)){
				p_at_ret=xm_at_ret_list[i].funlist;
				for(j=0;j<xm_at_ret_list[i].listnum;j++){
					#if DEBUG_CMD
					XM_D("xlf_packet_pasre:j %d major %d type %d minor %d sub %d\r\n",j,p_at_ret[j].major,msg.MessageType,p_at_ret[j].minor,msg.MessageSubType);
					#endif
					if(p_at_ret[j].major==msg.MessageType && p_at_ret[j].minor==msg.MessageSubType){
						if((NULL!=p_at_ret[j].parameter)&&(p_at_ret[j].parameter->recv_num>0)&&((ret_data.error==0))){
							#if DEBUG_CMD
							XM_D("xlf_packet_pasre:cmd %s recv_num %d\r\n",p_at_ret[j].cmd,p_at_ret[j].parameter->recv_num);
							#endif
							if(msg.MessageType == 0x65 ){
								if(ret_data.error !=0){
									snprintf(retbuf,XM_MAX_BUF,"+%s:ERROR,%d,",p_at_ret[j].cmd,ret_data.error);
								}else if(msg.Result!=1){						
									snprintf(retbuf,XM_MAX_BUF,"+%s:ERROR,%d,",p_at_ret[j].cmd,msg.Result);
								}else{
									snprintf(retbuf,XM_MAX_BUF,"+%s:SUCCEED,0,",p_at_ret[j].cmd);
								}
							}else{
								snprintf(retbuf,XM_MAX_BUF,"+%s:",p_at_ret[j].cmd);
							}
							for(k=0;k<p_at_ret[j].parameter->recv_num;k++){
								#if DEBUG_CMD
								XM_D("xlf_packet_pasre:type %d query %d support %d set %d offset %d len %d \r\n",p_at_ret[j].type,p_at_ret[j].parameter->recv[k].query,p_at_ret[j].parameter->recv[k].support,p_at_ret[j].parameter->recv[k].set,p_at_ret[j].parameter->recv[k].offset,p_at_ret[j].parameter->recv[k].len);
								#endif
								if((p_at_ret[j].type==XM_SEND_QUERY && p_at_ret[j].parameter->recv[k].query) || (p_at_ret[j].type==XM_SEND_SUPPORT && p_at_ret[j].parameter->recv[k].support) || (p_at_ret[j].type==XM_SEND_SETTING && p_at_ret[j].parameter->recv[k].set) ){
									xlf_parse_para(retbuf,&(p_at_ret[j]),ret_data.data,&p_at_ret[j].parameter->recv[k]);
								}
							}
						}else{
						    if (ret_data.error!=0)
						    	{
						    	snprintf(retbuf,XM_MAX_BUF,"+%s:ERROR,%d,",p_at_ret[j].cmd,ret_data.error);
								#if DEBUG_CMD
								XM_D("MessageType<210:retbuf=%s!!\r\n",retbuf);
								#endif
						    	}
							else if (msg.Result!=1)
							snprintf(retbuf,XM_MAX_BUF,"+%s:ERROR,%d,",p_at_ret[j].cmd,msg.Result);
							else
							snprintf(retbuf,XM_MAX_BUF,"+%s:SUCCEED,%d,",p_at_ret[j].cmd,ret_data.error);
						}	
						if (msg.MessageType > 200 || msg.MessageType == 1)
						{
							snprintf(retbuf+strlen(retbuf),XM_MAX_BUF-strlen(retbuf),"%d,%d\r\n",msg.frame,msg.sub_frame);
		#if DEBUG_CMD
							XM_D("Frame %d, Frame No %d\r\n",msg.frame,msg.sub_frame);
							XM_D("MessageType>200:retbuf=%s!!\r\n",retbuf);
		#endif
						}
					}
				}
			}
			}
		}
		if(strlen(retbuf)){
				retbuf[strlen(retbuf)-1]='\r';
				retbuf[strlen(retbuf)]='\n';
			}
			return strlen(retbuf);
	}
   else if (ret_data.error==ERROR_MSG_TIME_OUT)
   	{
   	char *sendbuf=(char *)malloc(sizeof(char)*ret_data.data_size*2); 
   	int retlen=BIN2HEX((char *)(ret_data.data),ret_data.data_size,sendbuf);	
#if DEBUG_CMD
	XM_D("sendbuf:data_size!! %d strlen(sendbuf)=%d retlen=%d\r\n",ret_data.data_size,strlen(sendbuf),retlen);
#endif

	#if DEBUG_CMD
	printf_buf("sendbuf",sendbuf,strlen(sendbuf));	
	#endif
	
   	snprintf(retbuf,XM_MAX_BUF,"+%s:ERROR,%s\r\n","timeout",sendbuf);
	
	#if DEBUG_CMD
	printf_buf("ret_buf",retbuf,strlen(retbuf));	
	#endif
	
	free(sendbuf);
	return strlen(retbuf);
   	}
    return 0;
}

char *xm_build_para(char *pbuf,int *len){
	int i;
	XM_PROTOCOL xm;
	XM_NODE node;
	char *retstr=NULL;
	memset(&xm,0,sizeof(XM_PROTOCOL));
	xm.xm_socket_client=-1;
	xm.xm_addres=0;
	xm.xm_seting=1; 
	xm.xm_exit=0;
	xm.xm_index=0;
	node.address=0;		
	node.index=0;
	node.argc=0;
	node.errorid=XM_ERROR_RECV_TIMEOUT;
	node.xm_set=0;
	node.xm_sendlen=0;
	node.xm_sendready=0;
	node.is_wait=0;
	node.end=NULL;
	memset(&node.xm_at,0,sizeof(XM_AT));
	xm.node=&node;
	node.atbuf=pbuf;
	node.atlen=*len;
	*len=0;
	strDividing(&xm,&node,node.atbuf,node.atlen);
	if(node.argc){
		for( i=0;i<node.argc;i++){
			if(strncmp(node.xm_at.getparam[i],"?",1)==0){
				node.xm_set=XM_SEND_QUERY;
#if DEBUG_CMD
				XM_D("build_para:XM_SEND_QUERY!!\r\n");
#endif
				break;
			}else if(strncmp(node.xm_at.getparam[i],"*",1)==0){
				node.xm_set=XM_SEND_SUPPORT;				
#if DEBUG_CMD
				XM_D("build_para:XM_SEND_SUPPORT!!\r\n");
#endif				
				break;
			}else{
				node.xm_set=XM_SEND_SETTING;				
#if DEBUG_CMD
				XM_D("build_para:XM_SEND_SETTING!!\r\n");
#endif				
			}
		}
	}	else{
		node.xm_set=XM_SEND_SETTING;
	}	
#if XM_WITH_ID
	if(node.argc<2){
		XM_E("build_para:ERROR AT PRAR\r\n");
		node.errorid=XM_ERROR_AT_PRAR;
		return NULL;
	}
	if(node.xm_set==XM_SEND_SETTING)
		node.xm_sendlen=Build_Send(&xm,&node,node.argc-1,&node.xm_at.getparam[1]);
	else
		node.xm_sendlen=Build_Send(&xm,&node,node.argc-2,&node.xm_at.getparam[2]);
#else
	node.xm_sendlen=Build_Send(&xm,&node,node.argc,node.xm_at.getparam);
#endif
	if(node.xm_sendlen){
		retstr=(char *)malloc(node.xm_sendlen+1);
		memset(retstr,'\0',node.xm_sendlen+1);
		memcpy(retstr,node.xm_at.XM_At_Ret,node.xm_sendlen);
		*len=node.xm_sendlen;
#if DEBUG_CMD
		XM_D("build_para:len %d!!\r\n",*len);
#endif
	}
	return retstr;
}

char *xm_parse_para(char *cmdpbuf,int cmdlen,char *pbuf,int len){
	int i;
	XM_PROTOCOL xm;
	XM_NODE node;
	char *retstr=NULL;
	memset(&xm,0,sizeof(XM_PROTOCOL));
	xm.xm_socket_client=-1;
	xm.xm_addres=0xff;
	xm.xm_seting=1; 
	xm.xm_exit=0;
	xm.xm_index=0;
	node.address=0;		
	node.index=0;
	node.argc=0;
	node.errorid=XM_ERROR_RECV_TIMEOUT;
	node.xm_set=0;
	node.xm_sendlen=0;
	node.xm_sendready=0;
	node.is_wait=0;
	node.end=NULL;
	memset(&node.xm_at,0,sizeof(XM_AT));
	xm.node=&node;
	node.atbuf=cmdpbuf;
	node.atlen=cmdlen;
	strDividing(&xm,&node,node.atbuf,node.atlen);
	if(node.argc){
		for( i=0;i<node.argc;i++){
			if(strncmp(node.xm_at.getparam[i],"?",1)==0){
				node.xm_set=XM_SEND_QUERY;
#if DEBUG_CMD
				XM_D("parse_para:XM_SEND_QUERY!!\r\n");
#endif
				break;
			}else if(strncmp(node.xm_at.getparam[i],"*",1)==0){
				node.xm_set=XM_SEND_SUPPORT;				
#if DEBUG_CMD
				XM_D("parse_para:XM_SEND_SUPPORT!!\r\n");
#endif				
				break;
			}else{
				node.xm_set=XM_SEND_SETTING;				
#if DEBUG_CMD
				XM_D("parse_para:XM_SEND_SETTING!!\r\n");
#endif				
			}
		}
	}	else{
		node.xm_set=XM_SEND_SETTING;
	}	
#if XM_WITH_ID
	if(node.argc<2){
		XM_E("parse_para:ERROR AT PRAR\r\n");
		node.errorid=XM_ERROR_AT_PRAR;
		return NULL;
	}
#endif
	memcpy(xm.XM_Status_Buffer,pbuf,len);
	build_at_ret(&xm,&node,NULL,XM_SUCCESS);
	//if(node.errorid==XM_SUCCESS){		
		retstr=(char *)malloc(4096);
		memset(retstr,'\0',4096);
		snprintf(retstr,4096,"%s\r\n",node.xm_at.XM_At_Ret);
	//}
	return retstr;
}

char* xm_ret_cmd (char * status,char *pbuf,int *len){
	int i;
	uchar address,j,nBitOffset,nByteOffset,nMask,nValue,nLen=0,ret,nRecv=0;
	uchar *sendbuf=NULL;
	XM_Command *pCommd=NULL;
	MessageHead * pMsg=NULL;
	XM_PROTOCOL xm;	
	char *retstr=NULL;
	char *xm_status=status;
	char *xm_data=status+62;
	char *xm_devid=status+62+8;
	char *xm_baundrate=status+62+8+18;
	char *xm_wifi_buf=status+62+8+18+1;
	char *xm_ver_buf=status+62+8+18+1+2;
	char *xm_devpower=status+62+8+18+1+2+4;
	char *xm_gn=status+62+8+18+1+2+4+48;
	char *xm_ver_mutil=status+62+8+18+1+2+4+48+17;
	memset(&xm,0,sizeof(XM_PROTOCOL));
	xm.xm_socket_client=-1;
	xm.xm_addres=0xff;
	xm.xm_seting=1; 
	xm.xm_exit=0;
	xm.xm_index=0;
	statusInit(&xm);	
#if DEBUG_CMD
	printf_buf("buf",pbuf,*len);
#endif
	memcpy(xm.XM_Frame_Buffer,pbuf,*len);
	for(i=0;i<*len;i++){
		ret=Parse_Read(&xm,xm.XM_Frame_Buffer+i,Proc_recv);
		if(ret==XM_SUCCESS){
			pMsg=(MessageHead *)xm.XM_Status_Buffer;
			pMsg->Result=1;
			//查找哪个命令执行
			if(xm.xm_status.P_XM_KL_Network_Address_1){
				xm.xm_addres_1[0]=xm.xm_status.P_XM_KL_Network_Address_1[0];
				xm.xm_addres_1[1]=xm.xm_status.P_XM_KL_Network_Address_1[1];
			}
			if(xm.xm_status.P_XM_KL_Network_Address_2){
				xm.xm_addres_2[0]=xm.xm_status.P_XM_KL_Network_Address_2[0];
				xm.xm_addres_2[1]=xm.xm_status.P_XM_KL_Network_Address_2[1];
			}
			address=xm.xm_addres_1[0];
			if(xm.xm_status.MsgLen>sizeof(MessageHead)){
				pCommd=getcommand(address,pMsg->MessageType,pMsg->MessageSubType,(char *)(xm.XM_Status_Buffer+sizeof(MessageHead)),xm.xm_status.MsgLen-sizeof(MessageHead));
			}
	#if DEBUG_RS
			XM_D("ret_cmd:command %p c %d s %d a %d\r\n", pCommd,pMsg->MessageType,pMsg->MessageSubType,address);
	#endif
			if(pMsg->MessageType==101 && pMsg->MessageSubType==0 && address==0x01){
				sendbuf=(uchar *)xm_status;nLen=62;
			}
			if(pMsg->MessageType==4 && address==0x01){
				sendbuf=(uchar *)xm_devid;nLen=16;
			}
			if(pMsg->MessageType==5 && address==0x01){
				sendbuf=(uchar *)xm_devid;nLen=18;
			}
			if(pMsg->MessageType==7 && (pMsg->MessageSubType==0 || pMsg->MessageSubType==1) && address==0x01){
				sendbuf=(uchar *)xm_ver_buf;nLen=4;
			}
			if(pMsg->MessageType==7 && pMsg->MessageSubType==4 && address==0x01){
				sendbuf=(uchar *)xm_ver_mutil;nLen=255;
			}
			if(pMsg->MessageType==9 && pMsg->MessageSubType==2 && address==0x01){
				sendbuf=(uchar *)xm_devid+16;nLen=2;
			}
			if(pMsg->MessageType==10 && (pMsg->MessageSubType==0 || pMsg->MessageSubType==1)  && address==0x01){
				sendbuf=(uchar *)xm_devid+16;nLen=2;
			}
			if(pMsg->MessageType==10 && pMsg->MessageSubType==4 && address==0x01){
				sendbuf=(uchar *)xm_devid;nLen=18;
			}
			if(pMsg->MessageType==26 && pMsg->MessageSubType==0 && address==0x01){
				sendbuf=(uchar *)xm_baundrate;nLen=1;
			}
			if(pMsg->MessageType==30 && pMsg->MessageSubType==0 && address==0x01){
				sendbuf=(uchar *)xm_wifi_buf;nLen=2;
			}					
			if((pMsg->MessageType==101 || pMsg->MessageType==102) && pMsg->MessageSubType==0 && address==0x01){
				sendbuf=(uchar *)xm_status;nLen=62;
			}
			if((pMsg->MessageType==101 || pMsg->MessageType==102) && pMsg->MessageSubType==32 && address==0x01){
				sendbuf=(uchar *)xm_data;nLen=8;
			}
			if(pMsg->MessageType==102 && pMsg->MessageSubType==48 && address==0x01){
				sendbuf=(uchar *)xm_devpower;nLen=48;
			}
			if(pMsg->MessageType==102 && pMsg->MessageSubType==64 && address==0x01){
				sendbuf=(uchar *)xm_gn;nLen=17;
			}
			if(pMsg->MessageType==103 && address==0x01){
				sendbuf=(uchar *)xm_devid;nLen=16;
			}
			if(pCommd && sendbuf){	
				nLen=0;
				for(j=0;j<pCommd->recv_num;j++){
					if(pCommd->recv[j].set)
						nLen=pCommd->query_len;
					if(pCommd->send[j].set==1 && pCommd->send[j].preset==0){
#if DEBUG_CMD
						XM_D("ret_cmd:recv len 0x%02x\r\n",pCommd->send[j].len);
#endif
						if(pCommd->send[j].len<=8){ 
							nByteOffset=pCommd->send[j].offset/8;
							nBitOffset =7-pCommd->send[j].offset%8;
							nMask=(0xff>>(8-pCommd->send[j].len))<<nBitOffset;
							nValue=nMask & xm.XM_Status_Buffer[sizeof(MessageHead)+nByteOffset];
							nValue>>=nBitOffset;
#if DEBUG_CMD
							XM_D("ret_cmd:Offset 0x%02x\r\n",nBitOffset);	
							XM_D("ret_cmd:Byte 0x%02x\r\n",nByteOffset);
							XM_D("ret_cmd:nMask 0x%02x\r\n",nMask);
							XM_D("ret_cmd:nValue 0x%02x\r\n",nValue);
#endif
							nBitOffset =7-pCommd->recv[j].offset%8;
							nByteOffset=pCommd->recv[j].offset/8;
							nMask=(0xff>>(8-pCommd->recv[j].len))<<nBitOffset;
							nValue<<=nBitOffset;
#if DEBUG_CMD
							XM_D("ret_cmd:Offset 0x%02x\r\n",nBitOffset);	
							XM_D("ret_cmd:Byte 0x%02x\r\n",nByteOffset);
							XM_D("ret_cmd:nMask 0x%02x\r\n",nMask);
							XM_D("ret_cmd:nValue 0x%02x\r\n",nValue);
#endif
							sendbuf[nByteOffset] &=~nMask;
							sendbuf[nByteOffset] |=nValue;
#if DEBUG_CMD
							XM_D("ret_cmd:status 0x%02x\r\n",sendbuf[nByteOffset]);
#endif
						}else{
							nValue=pCommd->send[j].len/8;
#if DEBUG_CMD
							XM_D("ret_cmd:buf len %d offset %d\r\n",pCommd->send[j].len,pCommd->send[j].offset); 
							XM_D("ret_cmd:recv en %d offset %d\r\n",pCommd->recv[j].len,pCommd->recv[j].offset);
							XM_D("ret_cmd:buf Offset 0x%02x\r\n",(pCommd->send[j].offset+1-pCommd->send[j].len)/8);	
							XM_D("ret_cmd:recv Offset 0x%02x\r\n",(pCommd->recv[j].offset+1-pCommd->recv[j].len)/8);
#endif
							memcpy(&sendbuf[(pCommd->recv[j].offset+1-pCommd->recv[j].len)/8],&xm.XM_Status_Buffer[sizeof(MessageHead)+(pCommd->send[j].offset+1-pCommd->send[j].len)/8],nValue);
#if DEBUG_CMD
							printf_buf("ret_cmd status",(uchar *)sendbuf,pCommd->send[j].len/8);
#endif
						}
					}
				}
				
			}else{
				memcpy(xm.XM_Status_Buffer+sizeof(MessageHead),sendbuf,nLen);
			}
			nRecv=Parse_Send(xm.XM_Frame_Buffer,xm.XM_Status_Buffer,sizeof(MessageHead)+nLen,xm.xm_addres_2,xm.xm_addres_1,xm.xm_addres_3,xm.xm_addres_4,xm.xm_addres_5,xm.xm_addres_count,xm.xm_addres_all,xm.xm_addres_type,xm.xm_addres_struct,xm.xm_encryption_type,xm.xm_crc_type,1,0,0,0,0,0);
	#if DEBUG_SCOKET
			printf_buf("ret_cmd send",xm.XM_Frame_Buffer,nRecv);
	#endif
			break;
		}
	}
	*len=0;
	if(nRecv){
		retstr=(char *)malloc(nRecv+1);
		memcpy(retstr,xm.XM_Frame_Buffer,nRecv);
		retstr[nRecv]='\0';
		*len=nRecv;
	}
	return retstr;
}

char * xm_send(char *psend){
	return xm_send_index(0,psend,strlen(psend));
}

char * xm_send_index(int index,char *psend,int sendlen){
	XM_NODE *pnode=NULL;
	XM_PROTOCOL *pxm=NULL;	
	char *strRet=(char *)malloc(XM_MAX_BUF);
	XmSetLog("send",xm_sendid++);
	if(xm_exited){
		XM_E("ERROR send:lib is exit %d\r\n",xm_exited);		
		XM_E("ERROR node:ret fail %d\r\n",XM_ERROR_VAIL);
		goto exit_send;
	}
	
	if(!xm_inited){
		XM_E("ERROR send:lib not init %d\r\n",xm_exited);
		XM_E("ERROR node:ret fail %d\r\n",XM_ERROR_VAIL);
		goto exit_send;
	}
	
	if(psend==NULL){
		XM_E("ERROR send:cmd buf is null %p\r\n",psend);
		XM_E("ERROR node:ret fail %d\r\n",XM_ERROR_VAIL);
		goto exit_send;
	}

	if(sendlen<=XM_AT_MIN){
		XM_E("ERROR send:cmd len error %d %s\r\n",sendlen,psend);
		XM_E("ERROR node:ret fail %d\r\n",XM_ERROR_VAIL);
		goto exit_send;
	}

	if(index<0){
		XM_E("ERROR send:socket index error %d\r\n",index);
		XM_E("ERROR node:ret fail %d\r\n",XM_ERROR_VAIL);
		goto exit_send;
	}
	
#if DEBUG_RS
	XM_D("send:enter index %d %s\r\n",index,psend);
#endif
	
	pnode=client_new_node(index,psend,sendlen,&xm_exited);
	if(pnode==NULL){
		XM_E("ERROR send:index get fail\r\n");
		XM_E("ERROR node:ret fail %d\r\n",XM_ERROR_NODE);
		goto exit_send;
	}	
	pxm=client_get_client(index);
	if(pxm==NULL){
		XM_E("ERROR send:socket index get fail\r\n");
		XM_E("ERROR node:ret fail %d\r\n",XM_ERROR_INDEX);
		pnode->errorid=XM_ERROR_INDEX;
		goto exit_send;
	}	
	pxm->node_count++;
	if(pxm->node_count>g_xm_max_wait_node){
		pxm->node_count--;
		XM_E("ERROR send:socket node full\r\n");
		XM_E("ERROR node:ret fail %d\r\n",XM_ERROR_MAX_CMD_IN_ONE_SOCKET);
		pnode->errorid=XM_ERROR_MAX_CMD_IN_ONE_SOCKET;
		goto exit_send;
	}	
	while(!xm_exited){		
#if DEBUG_THREAD
		XM_D("send:lock node %d index %d socket %d\r\n",pnode->id,pxm->xm_index,pxm->xm_socket_client);
#endif
		pthread_mutex_lock(&pxm->mutex);
		if(pxm->xm_exit || pxm->xm_socket_client==-1){
			pnode->index=-1;
			pnode->sync.timeout=0;
#if DEBUG_THREAD
			XM_D("send:xm_exit unlock node %d index %d socket %d\r\n",pnode->id,pxm->xm_index,pxm->xm_socket_client);
#endif
			pthread_mutex_unlock(&pxm->mutex);
			XM_E("ERROR send:socket is exit\r\n");
			XM_E("ERROR node:ret fail %d\r\n",XM_ERROR_SOCKET_EXIT);
			pnode->errorid=XM_ERROR_SOCKET_EXIT;
			pxm->node_count--;
			goto exit_send;
		}else if(pxm->node==NULL){
			break;
		}
#if DEBUG_THREAD
		XM_D("send:clean unlock node %d index %d socket %d\r\n",pnode->id,pxm->xm_index,pxm->xm_socket_client);
#endif
		pthread_mutex_unlock(&pxm->mutex);
		XM_E("ERROR send:node %d index %d socket %d wait  node clean\r\n",pnode->id,pxm->xm_index,pxm->xm_socket_client);
		sleep(1);
	}
	if(xm_exited || pxm->xm_exit){
		XM_E("ERROR send:socket is %s,lib is %s\r\n",pxm->xm_exit?"exit":"run",xm_exited?"exit":"run");
#if DEBUG_THREAD
		XM_D("send:exited unlock node %d index %d socket %d\r\n",pnode->id,pxm->xm_index,pxm->xm_socket_client);
#endif
		pthread_mutex_unlock(&pxm->mutex);
		XM_E("ERROR node:ret fail %d\r\n",XM_ERROR_SOCKET_EXIT);
		pnode->errorid=XM_ERROR_SOCKET_EXIT;
		pxm->node_count--;
		goto exit_send;
	}
	if(strRet!=NULL){
#if DEBUG_THREAD
		XM_D("send:enter node lock node %d index %d socket %d\r\n",pnode->id,pnode->index,pxm->xm_socket_client);
#endif
		xm_wait_lock((XM_SYNC *)pnode);
		memset(strRet,0,XM_MAX_BUF);
		pnode->atbuf=psend;
		pnode->atlen=sendlen;
		send_data(pxm,pnode);
#if DEBUG_CMD
		XM_D("send:%d ret %d\r\n",pnode->id,pnode->errorid);
#endif
		strncpy(strRet,pnode->xm_at.XM_At_Ret,XM_MAX_BUF);
#if DEBUG_CMD
		printf_buf("send",(uchar *)strRet,strlen(strRet));
#endif	
#if DEBUG_THREAD
		XM_D("send:exit unlock socket %d node %d\r\n",pxm->xm_socket_client,pnode->id);
#endif	
		pnode->errorid=0;
		pnode->sync.timeout=0;
		pnode->xm_cmd=NULL;
#if DEBUG_THREAD
		XM_D("send:enter node unlock node %d index %d socket %d\r\n",pnode->id,pnode->index,pxm->xm_socket_client);
#endif
		xm_wait_unlock((XM_SYNC *)pnode);
	}else{
		XM_E("ERROR send:strRet malloc fail\r\n");
		XM_E("ERROR node:ret fail %d\r\n",XM_ERROR_MALLOC);
		pnode->errorid=XM_ERROR_MALLOC;
#if DEBUG_THREAD
		XM_D("send:strRet unlock node %d index %d socket %d\r\n",pnode->id,pxm->xm_index,pxm->xm_socket_client);
#endif
		pthread_mutex_unlock(&pxm->mutex);
	}
	pnode->index=-1;
	pxm->node_count--;
	//xm_wait_destroy((XM_SYNC *)pnode);
exit_send:
	XmDelLog();
	if(pnode && strRet && pnode->errorid!=XM_SUCCESS){
		snprintf(strRet,XM_MAX_BUF,"AT+ERROR=%d",pnode->errorid);
	}
	return strRet;
}

char * xm_get_version(void){
	char *pbuf=malloc(XM_MAX_BUF);
	if(!pbuf){
		memset(pbuf,0,XM_MAX_BUF);
		snprintf(pbuf,XM_MAX_BUF,"V %d.%d.%d",XM_VER_MID,XM_VER_SID,XM_VER_LID);
	}
	return pbuf;
}

