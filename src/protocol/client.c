
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
#include	"message.h"
#include    "send.h"

pthread_mutex_t xm_mutex;
int g_xm_connect_num=XM_CONNECT_NUM;
int g_xm_send_num=MAX_SEND_POOL;

static pthread_t tid_dump_state=0;

XM_PROTOCOL *xm_protocl=NULL;
XM_NODE *xm_node=NULL;

void *dump_state_thread(void * arg)
{	
	XM_SEND *psend=(XM_SEND *)arg;
	int i;
	time_t currtime;
	int trylock=0;
	XM_NODE *pnodeseek,*pnodetmp;
	JavaVM * pjvm=psend->pjvm;
	XmSetLog("state_thread",0);
 #ifdef PLAT_LINUX
	XM_D("dump_state_thread%p\r\n",pjvm);
	if (pjvm!=NULL){			
			JNIEnv *env;
			XM_D("dump_state_thread g_jvm!=NULL!!!!\r\n");
			if((*pjvm)->AttachCurrentThread(pjvm,(void**)&env, NULL) != JNI_OK){
		       XM_E("%s: AttachCurrentThread() failed", __FUNCTION__);
		       goto exit_state_thread;
		   }
		}
#endif
	if(psend==NULL){
		XM_E("ERROR dump_state_thread:arg error %p\r\n",arg);
		goto exit_state_thread;
	}
	XmSetLog("dump_state_thread",0);
#if DEBUG_SCOKET
	XM_D("dump_state_thread loop\r\n");
#endif
#if DEBUG_RS
	XM_D("dump_state_thread: enter len %d exit %p  pxm %p\r\n",psend->xmlen,psend->pexit,psend->pxm);
#endif
	while(!(*psend->pexit)){
		time(&currtime);
		XM_D("dump_state_thread:currtime %d\r\n",currtime);
		for(i=0;i<g_xm_connect_num;i++){
			if(xm_protocl[i].timeout!=0){
				if((currtime-xm_protocl[i].timeout)>3*XM_SELECT_TIMEOUT){
					trylock=pthread_mutex_trylock(&xm_protocl[i].mutex);
					if(trylock==0){
						pthread_mutex_unlock(&xm_protocl[i].mutex);
					}
					XM_E("ERROR:pxm dead lock:index %d socket %d timeout=%d xm_seting=%d xm_waitsend=%d xm_send=%d xm_sendready=%d proc=%d node=%s lock %s\r\n",i,xm_protocl[i].xm_socket_client,(int)xm_protocl[i].timeout,xm_protocl[i].xm_seting,xm_protocl[i].xm_waitsend,xm_protocl[i].xm_send,xm_protocl[i].xm_sendready,xm_protocl[i].node_count,xm_protocl[i].node?"have":"empty",trylock==0?"off":"on");
					if(trylock!=0){
						pthread_mutex_unlock(&xm_protocl[i].mutex);
					}
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
					xm_protocl[i].node=NULL;
#ifdef DEBUG_TIMEOUT_ASK
					if(xm_protocl[i].xm_socket_client!=-1){
						xm_protocl[i].XM_Frame_Buffer[0]=0xf4;
						xm_protocl[i].XM_Frame_Buffer[1]=0xfb;
						send(xm_protocl[i].xm_socket_client, xm_protocl[i].XM_Frame_Buffer,2,0);
					}
#endif
					xm_protocl[i].xm_socket_client=-1;
					xm_protocl[i].xm_exit=0;
				}
#if DEBUG_CMD
				XM_D("dump_state_thread pxm:index %d socket %d timeout=%d xm_seting=%d xm_waitsend=%d xm_send=%d xm_sendready=%d proc=%d node=%s\r\n",i,xm_protocl[i].xm_socket_client,(int)xm_protocl[i].timeout,xm_protocl[i].xm_seting,xm_protocl[i].xm_waitsend,xm_protocl[i].xm_send,xm_protocl[i].xm_sendready,xm_protocl[i].node_count,xm_protocl[i].node?"have":"empty");
#endif	
			}
		}
		for(i=0;i<g_xm_send_num;i++){
			if(xm_node[i].sync.timeout!=0){
				if((currtime-xm_node[i].sync.timeout)>2*XM_SELECT_TIMEOUT){	
					trylock=pthread_mutex_trylock(&xm_node[i].sync.mutex);
					if(trylock==0){
						pthread_mutex_unlock(&xm_node[i].sync.mutex);
					}
					
					XM_E("ERROR:node dead lock:node %d index %d socket %d is_wait=%d errorid=%d xm_set=%d xm_sendready=%d	timeout=%d sync.is_wait=%d cmd=%s lock %s\r\n",xm_node[i].id,xm_node[i].index,xm_protocl[xm_node[i].index].xm_socket_client,xm_node[i].is_wait,xm_node[i].errorid,xm_node[i].xm_set,xm_node[i].xm_sendready,(int)xm_node[i].sync.timeout,xm_node[i].sync.is_wait,xm_node[i].xm_cmd?xm_node[i].xm_cmd->cmd:"none",trylock==0?"off":"on");
					if(xm_node[i].xm_sendready && xm_node[i].sync.is_wait){
						pthread_cond_signal(&xm_node[i].sync.cond);	
					}
				}
#if DEBUG_CMD
				XM_D("dump_state_thread node:node %d index %d socket %d is_wait=%d errorid=%d xm_set=%d xm_sendready=%d  timeout=%d sync.is_wait=%d cmd=%s\r\n",xm_node[i].id,xm_node[i].index,xm_protocl[xm_node[i].index].xm_socket_client,xm_node[i].is_wait,xm_node[i].errorid,xm_node[i].xm_set,xm_node[i].xm_sendready,(int)xm_node[i].sync.timeout,xm_node[i].sync.is_wait,xm_node[i].xm_cmd?xm_node[i].xm_cmd->cmd:"none");
#endif	
			}
		}	
		sleep(6);
	}
#if DEBUG_RS
	XM_D("state_thread: exit\r\n");
#endif
#ifdef PLAT_LINUX
	//Detach主线程
	if (pjvm!=NULL){
		if((*pjvm)->DetachCurrentThread(pjvm) != JNI_OK){
			 LOGE("%s: DetachCurrentThread() failed", __FUNCTION__);
		}
	}
#endif
exit_state_thread:
	free(psend);
	XmDelLog();
	return NULL;
}

int init_socket_client(char * server_ip,char * server_port){
	int ret = 0,nport,nip,retry=10,socket_client;
	static struct sockaddr_in srv_addr;
    #if DEBUG_SCOKET
	XM_D("client connect start \r\n");
	#endif	
    /* setup socket */
    socket_client = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_client < 0) {
		XM_E("ERROR client socket fail\r\n");
		socket_client=-1;
		goto init_socket_client_exit;
    }
	nport=atoi(server_port);
	#if DEBUG_SCOKET
	XM_D("client:port %d\r\n",nport);
	#endif
	srv_addr.sin_port = htons(nport);
	
	#if DEBUG_SCOKET
	XM_D("client:ip %s\r\n",server_ip);
	#endif
	nip=inet_addr(server_ip);
    srv_addr.sin_addr.s_addr = nip;    
    srv_addr.sin_family = AF_INET;

    /* connect the socket */
	ret=-1;
	while(retry && ret<0){
    	ret = connect(socket_client, (struct sockaddr *) &srv_addr, sizeof (struct sockaddr_in));
		retry--;
		XM_D("client:connect retry %d ret = %d!\r\n",retry, ret);
	}
    if (ret < 0) {
        XM_E("ERROR client connect fail, ret = %d!\r\n", ret);
        goto init_socket_client_exit;
    }
	#if DEBUG_SCOKET
	XM_D("client conneting %d\r\n",socket_client);	
	#endif
	return socket_client;
  init_socket_client_exit:
  	if(socket_client!=-1){
		close(socket_client);
		socket_client=-1;
	}
    #if DEBUG_SCOKET
	XM_D("client conneting fail\r\n");
	#endif
    return -1;
}

int client_get_socket(int index){
	if(index<0 || index >=g_xm_connect_num){
		XM_D("ERROR get_client:index vail %d\r\n",index);
		return -1;
	}
	return xm_protocl[index].xm_socket_client;
}

XM_PROTOCOL * client_get_client(int index){
	if(index<0 || index >=g_xm_connect_num){
		XM_D("ERROR get_client:index vail %d\r\n",index);
		return NULL;
	}
	return &xm_protocl[index];
}

XM_PROTOCOL * client_get_index(int socketfd){
	int i;
	if(socketfd<0){
		XM_D("ERROR get_index:socket vail %d\r\n",socketfd);
		return NULL;
	}
#if DEBUG_THREAD
	XM_D("get_index:lock \r\n");
#endif
	pthread_mutex_lock(&xm_mutex);	
	for(i=0;i<g_xm_connect_num;i++){
		if(xm_protocl[i].xm_socket_client==socketfd){
			break;
		}
	}	
#if DEBUG_THREAD
	XM_D("get_index:unlock \r\n");
#endif
	pthread_mutex_unlock(&xm_mutex);
	if(i!=g_xm_connect_num){
		return &xm_protocl[i];
	}
	return NULL;
}

int client_exit_client(int socketfd){
	XM_NODE *pnodeseek,*pnodetmp;
	XM_PROTOCOL *pxm;
	int socket_fd;
exit_again:
	pxm=client_get_index(socketfd);
	if(pxm!=NULL){
		socket_fd=pxm->xm_socket_client;
#if DEBUG_THREAD
		XM_D("exit_client:lock index %d socket %d\r\n",pxm->xm_index,socket_fd);
#endif
		pthread_mutex_lock(&pxm->mutex);	
		pxm->xm_exit=1;
		pnodeseek=pxm->node;
		pxm->xm_sendready=0;
		pxm->xm_send=0;
		pxm->timeout=0;
		pxm->sendcmd=0;
		pxm->sendsub=0;
		pxm->xm_seting=1;
		while(pnodeseek){
			pnodetmp=pnodeseek->end;			
			pnodeseek->errorid=XM_ERROR_SOCKET_EXIT;
			pnodeseek->xm_sendready=0;
#if DEBUG_THREAD
			XM_D("exit_client:exit post sem node %d index %d socket %d\r\n",pnodeseek->id,pnodeseek->index,pxm->xm_socket_client);
#endif
			xm_wait_signal((XM_SYNC *)pnodeseek);
			pnodeseek=pnodetmp;
		}
		pxm->node=NULL;
#ifdef DEBUG_TIMEOUT_ASK
		if(pxm->xm_socket_client!=-1){
			pxm->XM_Frame_Buffer[0]=0xf4;
			pxm->XM_Frame_Buffer[1]=0xfb;
			send(pxm->xm_socket_client, pxm->XM_Frame_Buffer,2,0);
		}
#endif
		pxm->xm_socket_client=-1;
#if DEBUG_THREAD
		XM_D("exit_client:unlock index %d socket %d\r\n",pxm->xm_index,socket_fd);
#endif
		pthread_mutex_unlock(&pxm->mutex);
		pxm->xm_exit=0;
		goto exit_again;
	}
	
	XM_E("ERROR exit_client:can't find socket %d\r\n",socketfd);
	return XM_SUCCESS;
}
void client_clear_socket(){
	int i;
	pthread_mutex_lock(&xm_mutex);	
	for(i=0;i<g_xm_connect_num;i++){
		if(xm_protocl[i].xm_socket_client!=-1){
		    close(xm_protocl[i].xm_socket_client);
		}
	}
	pthread_mutex_unlock(&xm_mutex);
}

XM_NODE * client_new_node(int index,char *atcmd,int len,int *nexit){
	int i=-1;
	if(index<0){
		XM_E("ERROR new_node:error index %d\r\n",index);
		return NULL;
	}
#if DEBUG_THREAD
	XM_D("new_node:lock index %d \r\n",index);
#endif
	pthread_mutex_lock(&xm_mutex);
	for(i=0;i<g_xm_send_num;i++){
		if(xm_node[i].index==-1){
			memset(&xm_node[i].xm_at,0,sizeof(XM_AT));			
			xm_node[i].index=index;
#if DEBUG_SCOKET
			XM_D("new_node:exist node %d\r\n",i);
#endif
			break;
		}
	}
#if DEBUG_THREAD
	XM_D("new_node:unlock index %d \r\n",index);
#endif
	pthread_mutex_unlock(&xm_mutex);
	if(i==g_xm_send_num){		
		i=-1;
	}
	if(i==-1){
		XM_E("ERROR send:get node fail %d\r\n",i);
	}else{
#if DEBUG_RS
		XM_D("new_node:last status cmd %d sub %d wait %d set %d\r\n",xm_protocl[index].sendcmd,xm_protocl[index].sendsub,xm_protocl[index].xm_waitsend,xm_protocl[index].xm_seting);
#endif
		xm_node[i].address=xm_protocl[index].xm_addres;		
		xm_node[i].index=index;
		xm_node[i].argc=0;
		xm_node[i].errorid=XM_ERROR_RECV_TIMEOUT;
		xm_node[i].xm_set=0;
		xm_node[i].xm_sendlen=0;
		xm_node[i].xm_sendready=0;
		xm_node[i].is_wait=0;
		memset(&xm_node[i].xm_at,0,sizeof(XM_AT));
		//memset(&xm_node[i].sync,0,sizeof(XM_SYNC));
		//xm_wait_init((XM_SYNC *)&xm_node[i]);
		return &xm_node[i];
	}
	return NULL;
}

void client_init_lock(void){
	pthread_mutex_init(&xm_mutex,NULL);	
}

void client_clean_client(JavaVM *pjvm,pthread_t *tid_send,int *nexit){
	int err,i;	
#if DEBUG_THREAD
	XM_D("clean_client:lock \r\n");
#endif
	pthread_mutex_lock(&xm_mutex);	
	for(i=0;i<g_xm_connect_num;i++){
		xm_protocl[i].xm_seting=1;
		xm_protocl[i].xm_socket_client=-1;
		xm_protocl[i].xm_exit=0;
	}
	for(i=0;i<g_xm_send_num;i++){
		xm_node[i].index=-1;
	}
#ifndef ANDROID
	if(tid_dump_state==0){
		XM_SEND *state_agr=(XM_SEND *)malloc(sizeof(XM_SEND));
		if(state_agr){
			memset(state_agr,0,sizeof(XM_SEND));
			state_agr->pexit=nexit;
			state_agr->xmlen=g_xm_connect_num;
			state_agr->pxm=xm_protocl;
			state_agr->pjvm=pjvm;
			XM_D("init_client: jvm %p %p",state_agr->pjvm,pjvm);
#ifdef DEBUG_RS
			XM_D("init_client:  len %d exit %p pmutex %p pxm %p\r\n",state_agr->xmlen,state_agr->pexit,state_agr->pmutex,state_agr->pxm);
#endif
			err=pthread_create(&tid_dump_state,NULL,dump_state_thread,(void *)state_agr);//创建线程	
			if(err!=0)	
			{  
				XM_E("ERROR init_client:state thread  error:%s\r\n",strerror(err));  
#if DEBUG_THREAD
				XM_D("init_client:create state thread fail unlock \r\n");
#endif
				free(state_agr);
				tid_dump_state=0;
			}
		}
	}
#endif
	if(*tid_send==0){
		XM_SEND *send_agr=(XM_SEND *)malloc(sizeof(XM_SEND));
		if(send_agr){
			memset(send_agr,0,sizeof(XM_SEND));
			send_agr->pexit=nexit;
			send_agr->xmlen=g_xm_connect_num;
			send_agr->pxm=xm_protocl;
			send_agr->pmutex=&xm_mutex;
#ifdef DEBUG_RS
			XM_D("clean_client:  len %d exit %p pmutex %p pxm %p\r\n",send_agr->xmlen,send_agr->pexit,send_agr->pmutex,send_agr->pxm);
#endif
			err=pthread_create(tid_send,NULL,send_thread,send_agr);//创建线程	
			if(err!=0)	
			{  
				XM_E("ERROR clean_client: thread  error:%s\r\n",strerror(err));  
#if DEBUG_THREAD
				XM_D("clean_client:create thread fail unlock \r\n");
#endif
				free(send_agr);
				*tid_send=0;
#if DEBUG_THREAD
				XM_D("clean_client:unlock \r\n");
#endif				
				pthread_mutex_unlock(&xm_mutex);
				return ;
			}
		}else{
#if DEBUG_THREAD
				XM_D("clean_client:malloc fail unlock \r\n");
#endif				
				pthread_mutex_unlock(&xm_mutex);
				return ;
		}
	}else{
#if DEBUG_THREAD
		XM_D("clean_client:unlock \r\n");
#endif
		pthread_mutex_unlock(&xm_mutex);
	}
}

int client_init_client(JavaVM *pjvm,pthread_t *tid_send,int *nexit,int connect_num,int send_num){
	int err,i;
	XM_D("init_client:jvm %p \r\n",pjvm);
#if DEBUG_THREAD
	XM_D("init_client:lock \r\n");
#endif
	pthread_mutex_lock(&xm_mutex);
	if(xm_protocl==NULL){
		if(connect_num>0)
			g_xm_connect_num=connect_num;
		
#if DEBUG_RS
		XM_D("init_client:connect_num %d send_num %d\r\n",connect_num,send_num);
#endif
		xm_protocl=(XM_PROTOCOL *)malloc(g_xm_connect_num*sizeof(XM_PROTOCOL));
		if(xm_protocl==NULL){
			XM_E("ERROR init_client:protocl malloc fail \r\n");
#if DEBUG_THREAD
			XM_D("init_client:create thread fail unlock \r\n");
#endif
			pthread_mutex_unlock(&xm_mutex);
			return -1;
		}
		for(i=0;i<g_xm_connect_num;i++){
		memset(&xm_protocl[i],0,sizeof(XM_PROTOCOL));
		xm_protocl[i].xm_socket_client=-1;
		xm_protocl[i].xm_addres=0xff;
		xm_protocl[i].xm_seting=1;
		pthread_mutex_init(&xm_protocl[i].mutex, NULL);
	}
	}
	if(xm_node==NULL){
		if(send_num>0)
			g_xm_send_num=send_num;
		xm_node=(XM_NODE *)malloc(g_xm_send_num*sizeof(XM_NODE));
		if(xm_node==NULL){
			XM_E("ERROR init_client:node malloc fail \r\n");
#if DEBUG_THREAD
			XM_D("init_client:create thread fail unlock \r\n");
#endif
			pthread_mutex_unlock(&xm_mutex);
			return -1;
		}
		for(i=0;i<g_xm_send_num;i++){
			memset(&xm_node[i],0,sizeof(XM_NODE));			
			xm_wait_init((XM_SYNC *)&xm_node[i]);
			xm_node[i].index=-1;
			xm_node[i].id=i;
		}
	}	
	
#ifndef ANDROID
	if(tid_dump_state==0){
		XM_SEND *state_agr=(XM_SEND *)malloc(sizeof(XM_SEND));
		memset(state_agr,0,sizeof(XM_SEND));
		state_agr->pexit=nexit;
		state_agr->xmlen=g_xm_connect_num;
		state_agr->pxm=xm_protocl;
		state_agr->pmutex=&xm_mutex;
		state_agr->pjvm=pjvm;
#ifdef DEBUG_RS
		XM_D("init_client:  len %d exit %p pmutex %p pxm %p\r\n",state_agr->xmlen,state_agr->pexit,state_agr->pmutex,state_agr->pxm);
#endif
		err=pthread_create(&tid_dump_state,NULL,dump_state_thread,(void *)state_agr);//创建线程	
		if(err!=0)	
		{  
			XM_E("ERROR init_client:state thread  error:%s\r\n",strerror(err));  
#if DEBUG_THREAD
			XM_D("init_client:create state thread fail unlock \r\n");
#endif
			tid_dump_state=0;
		}
	}else{
#if DEBUG_THREAD
		XM_D("init_client:unlock \r\n");
#endif
	}
#endif
	if(*tid_send==0){
		XM_SEND *send_agr=(XM_SEND *)malloc(sizeof(XM_SEND));
		if(send_agr){
			memset(send_agr,0,sizeof(XM_SEND));
			send_agr->pexit=nexit;
			send_agr->xmlen=g_xm_connect_num;
			send_agr->pxm=xm_protocl;
			send_agr->pmutex=&xm_mutex;
			send_agr->pjvm=pjvm;
#ifdef DEBUG_RS
			XM_D("init_client:  len %d exit %p pmutex %p pxm %p\r\n",send_agr->xmlen,send_agr->pexit,send_agr->pmutex,send_agr->pxm);
#endif
			err=pthread_create(tid_send,NULL,send_thread,(void *)send_agr);//创建线程	
			if(err!=0)	
			{  
				free(send_agr);
				XM_E("ERROR init_client:thread  error:%s\r\n",strerror(err));  
#if DEBUG_THREAD
				XM_D("init_client:create thread fail unlock \r\n");
#endif
				pthread_mutex_unlock(&xm_mutex);
				return -2;
			}
		}else{
#if DEBUG_THREAD
		XM_D("init_client:malloc fail unlock \r\n");
#endif
			pthread_mutex_unlock(&xm_mutex);
			return -3;
		}
	}else{
#if DEBUG_THREAD
		XM_D("init_client:unlock \r\n");
#endif
		pthread_mutex_unlock(&xm_mutex);
	}
	return 0;
}

int client_get_socket_index(int socket_fd){
	int i=-1;
#if DEBUG_THREAD
	XM_D("get_socket:lock socket %d \r\n",socket_fd);
#endif
	pthread_mutex_lock(&xm_mutex);
	for(i=0;i<g_xm_connect_num;i++){
		if(xm_protocl[i].xm_socket_client==socket_fd){
			break;
		}
	}	
#if DEBUG_THREAD
	XM_D("get_socket:unlock socket %d \r\n",socket_fd);
#endif
	pthread_mutex_unlock(&xm_mutex);
	if(i==g_xm_connect_num)
		i=-1;
	return i;
}

XM_PROTOCOL * client_new_index(int socket,int id){
	int i=-1;
	if(socket<0){
		XM_E("ERROR new_index:socket fail %d\r\n",socket);  
		return NULL;
	}
	pthread_mutex_lock(&xm_mutex);
refined:	
	for(i=0;i<g_xm_connect_num;i++){//查找已有的
		if(xm_protocl[i].xm_socket_client==socket){
			while(xm_protocl[i].xm_exit && xm_protocl[i].xm_socket_client==socket){//当前有相同的socket，但处于退出状态,等待退出
				XM_E("ERROR new_index:socket %d %d wait exit \r\n",socket,i);
				sleep(1);
			}
			if(xm_protocl[i].xm_socket_client!=socket){
				goto refined;
			}
			break;
		}
	}
	if(i!=g_xm_connect_num && xm_protocl[i].xm_socket_client==-1){
		i=g_xm_connect_num;
	}
#if DEBUG_THREAD
	XM_D("new_index:lock socket %d \r\n",socket);
#endif
	if(i==g_xm_connect_num){
		i=0;
		for(i=0;i<g_xm_connect_num;i++){
			if(xm_protocl[i].xm_socket_client==-1 && xm_protocl[i].xm_exit==0){
				xm_protocl[i].xm_socket_client=socket;
				xm_protocl[i].xm_addres=id;
				xm_protocl[i].xm_index=i;
				xm_protocl[i].node_count=0;
				xm_protocl[i].resend_count=0;
				break;
			}
		}
	}
#if DEBUG_THREAD
	XM_D("new_index:unlock socket %d \r\n",socket);
#endif
	pthread_mutex_unlock(&xm_mutex);
	if(i==g_xm_connect_num){		
		i=-1;
	}
	if(i==-1){		
		XM_E("ERROR send:get index fail %d\r\n",i);
	}else{
		return &xm_protocl[i];
	}
	return NULL;
}

