
#include	<stdio.h>
#include	<stdlib.h>
#include	<signal.h>
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
#include    "send.h"
#include    "recv.h"

uchar send_tcp(XM_PROTOCOL *pxm,uchar *pbuf,uchar len)
{
	int ret =-1;
	int fd_act = 0;	
	struct timeval tmo;
	fd_set fd_SockSet;
	if(!pxm){
		XM_E("ERROR pxm is null\r \r\n");
		return XM_ERROR_SOCKET_FAIL;
	}
	if(pxm->xm_socket_client==-1){
		XM_E("ERROR send data socket fail\r \r\n");
		return XM_ERROR_SOCKET_FAIL;
	}
	if(!pbuf){
		XM_E("ERROR send data buf fail\r \r\n");
		return XM_ERROR_SOCKET_FAIL;
	}
	if(!len){
		XM_E("ERROR send data size fail\r \r\n");
		return XM_ERROR_SOCKET_FAIL;
	}
	#if DEBUG_RS
	XM_D("send: id %d socket %d buf %p len %d\r\n",pxm->xm_index,pxm->xm_socket_client,pbuf,len);
	#endif
	if(len){
		ret=send(pxm->xm_socket_client, pbuf,len,0);
		#if DEBUG_SCOKET
		XM_D("send: %d\r\n",ret);
		#endif
		if(ret!=len){
			XM_E("ERROR send data fail\r \r\n");
			return XM_ERROR_SOCKET_SEND;
		}
	}
	memset(pbuf,'\0',len);
	tmo.tv_sec = 5;
	tmo.tv_usec = 0;
	#if DEBUG_SCOKET
	XM_D("client recieving loop\r \r\n");
	#endif
	while(!(pxm->xm_socket_client < 0) && !pxm->xm_exit){
		/*init fd_set*/
		FD_ZERO(&fd_SockSet);
		FD_SET(pxm->xm_socket_client, &fd_SockSet);
		fd_act = select(pxm->xm_socket_client+1,&fd_SockSet, NULL, NULL, &tmo);
		if(fd_act <= 0)
		{
			#if DEBUG_SCOKET
			XM_D("client recieving timeout\r\n");
			#endif
			return XM_ERROR_RECV_TIMEOUT;
		}
		else
		{
			if (FD_ISSET(pxm->xm_socket_client, &fd_SockSet)) {
				#if DEBUG_SCOKET
				XM_D("client recieving data %d\r\n",pxm->xm_socket_client);
				#endif
				ret=recv_tcp(pxm,pbuf,pxm->xm_socket_client,0);
#if DEBUG_SCOKET
				XM_D("client recieving finish %d\r\n",pxm->xm_socket_client);
#endif
				if(ret!=XM_ERROR_WAIT_MOER){
					break;
				}
			}
		}
	}	
	#if DEBUG_SCOKET
	XM_D("client exit %d\r\n",ret);
	#endif
	return ret;

}

void *send_thread(void * arg)
{	
	XM_SEND *psend=(XM_SEND *)arg;
	int ret = -1,i,max_fb;
	int fd_act = 0;	
	time_t currtime,runtime,newtime;
	struct timeval tmo;
	fd_set fd_SockSet;
	XM_NODE *pnodeseek,*pnodetmp;
	JavaVM * pjvm=psend->pjvm;
	static int printflag=0;
	struct sigaction sa;
    sa.sa_handler = SIG_IGN;
    sigaction( SIGPIPE, &sa,0);
	XmSetLog("send_thread",0);
	XM_E("send_thread g_jvm?=NULL\r\n");
#ifdef PLAT_LINUX
	if (pjvm!=NULL)
		{	XM_E("send_thread g_jvm!=NULL!!!!\r\n");
			JNIEnv *env;
			if((*pjvm)->AttachCurrentThread(pjvm,(void**)&env, NULL) != JNI_OK)
			{
		       XM_E("%s: AttachCurrentThread() failed", __FUNCTION__);
#if DEBUG_THREAD
				XM_D("send_thread:unlock \r\n");
#endif				
			   	pthread_mutex_unlock(psend->pmutex);
		       goto exit_send_thread;
		   }
		}
#endif
	if(psend==NULL){
		XM_E("ERROR send_thread:arg error %p\r\n",arg);
#if DEBUG_THREAD
		XM_D("send_thread:unlock \r\n");
#endif				
		pthread_mutex_unlock(psend->pmutex);
		goto exit_send_thread;
	}
	
	XmSetLog("send_thread",0);
#if DEBUG_SCOKET
	XM_D("send_thread loop\r\n");
#endif
#if DEBUG_THREAD
	XM_D("tcp_send:unlock\r\n");
#endif
#ifdef DEBUG_RS
	XM_D("send_thread: enter len %d exit %p pmutex %p pxm %p\r\n",psend->xmlen,psend->pexit,psend->pmutex,psend->pxm);
#endif
#ifdef DEBUG_RS
	XM_D("send_thread: enter exit %d\r\n",*psend->pexit);
#endif
#if DEBUG_THREAD
	XM_D("send_thread:unlock \r\n");
#endif
	pthread_mutex_unlock(psend->pmutex);
	while(!(*psend->pexit)){
		/*init fd_set*/
#ifdef ANDROID
		//XM_D("send_thread: start %d\r\n",*psend->pexit);
#endif
		FD_ZERO(&fd_SockSet);		
		tmo.tv_sec = XM_SELECT_TIME;
		tmo.tv_usec = XM_SELECT_TIME_US;
		max_fb=0;
#if DEBUG_THREAD
		if(printflag++==1000){
			printflag=0;
			XM_D("send_thread: loop\r\n");
		}
#endif
		for(i=0;i<psend->xmlen;i++){
#if DEBUG_THREAD
			//XM_D("send_thread:send lock index %d socket %d\r\n",psend->pxm[i].xm_index,psend->pxm[i].xm_socket_client);
#endif
			pthread_mutex_lock(&psend->pxm[i].mutex);
			if( psend->pxm[i].xm_sendready && psend->pxm[i].xm_send){
#if DEBUG_SCOKET
				XM_D("send_thread:send time %d socket %d\r\n",(int)psend->pxm[i].timeout,psend->pxm[i].xm_socket_client);
#endif
#if DEBUG_RS
				printf_buf("send",(uchar *)psend->pxm[i].XM_Frame_Buffer,psend->pxm[i].xm_send);
#endif
				memset(psend->pxm[i].XM_At_Send,'\0',XM_MAX_BUF);
				BIN2HEX((char *)psend->pxm[i].XM_Frame_Buffer,psend->pxm[i].xm_send,psend->pxm[i].XM_At_Send);
#if DEBUG_RS
				XM_D("send_thread: id %d socket %d buf %p len %d\r\n",i,psend->pxm[i].xm_socket_client,psend->pxm[i].XM_Frame_Buffer,psend->pxm[i].xm_send);
#endif
				time(&(psend->pxm[i].timeout));
				pnodeseek=psend->pxm[i].node;
				while(pnodeseek){
					time(&(pnodeseek->sync.timeout));
					pnodeseek=pnodeseek->end;
				}
				ret=send(psend->pxm[i].xm_socket_client, psend->pxm[i].XM_Frame_Buffer,psend->pxm[i].xm_send,0);
				#if DEBUG_SCOKET
				XM_D("send_thread: %d\r\n",ret);
				#endif
				if(ret!=psend->pxm[i].xm_send){
					XM_E("ERROR send data fail\r \r\n");
					pnodeseek=psend->pxm[i].node;
					psend->pxm[i].xm_sendready=0;
					psend->pxm[i].xm_send=0;
					psend->pxm[i].timeout=0;
					psend->pxm[i].sendcmd=0;
					psend->pxm[i].sendsub=0;
					psend->pxm[i].xm_seting=1;
					while(pnodeseek){
						pnodetmp=pnodeseek->end;
						pnodeseek->errorid=XM_ERROR_SOCKET_SEND;
						pnodeseek->xm_sendready=0;
#if DEBUG_THREAD
						XM_D("send_thread:send post sem node %d index %d socket %d\r\n",pnodeseek->id,pnodeseek->index,psend->pxm[i].xm_socket_client);
#endif
						xm_wait_signal((XM_SYNC *)pnodeseek);
						pnodeseek=pnodetmp;
					}
					psend->pxm[i].node=NULL;						
				}else{
					psend->pxm[i].xm_sended=psend->pxm[i].xm_send;
					psend->pxm[i].xm_send=0;
				}
			}
			if(psend->pxm[i].xm_sendready && psend->pxm[i].xm_socket_client!=-1){
				FD_SET(psend->pxm[i].xm_socket_client, &fd_SockSet);
				if(psend->pxm[i].xm_socket_client>max_fb){
					max_fb=psend->pxm[i].xm_socket_client;
				}
			}
#if DEBUG_THREAD
			//XM_D("send_thread:send unlock index %d socket %d\r\n",psend->pxm[i].xm_index,psend->pxm[i].xm_socket_client);
#endif
			pthread_mutex_unlock(&psend->pxm[i].mutex);
		}
		if(max_fb){
			fd_act = select(max_fb+1,&fd_SockSet, NULL, NULL, &tmo);
			if(fd_act <= 0){
				for(i=0;i<psend->xmlen;i++){
#if DEBUG_THREAD
					//XM_D("send_thread:select lock index %d socket %d\r\n",psend->pxm[i].xm_index,psend->pxm[i].xm_socket_client);
#endif
					pthread_mutex_lock(&psend->pxm[i].mutex);
					if(psend->pxm[i].timeout!=0){
						time(&currtime);
						if(currtime-psend->pxm[i].timeout>(XM_SELECT_TIMEOUT)){							
							if(psend->pxm[i].resend_count<3)
								{
								time(&(psend->pxm[i].timeout));
								pnodeseek=psend->pxm[i].node;
								while(pnodeseek){
									time(&(pnodeseek->sync.timeout));
									pnodeseek=pnodeseek->end;
								}
								XM_E("send_thread:resend !!!!!resend_count=%d\r\n",psend->pxm[i].resend_count);
								printf_buf("send",(uchar *)psend->pxm[i].XM_Frame_Buffer,psend->pxm[i].xm_sended);
								ret=send(psend->pxm[i].xm_socket_client, psend->pxm[i].XM_Frame_Buffer,psend->pxm[i].xm_sended,0);
								psend->pxm[i].resend_count++;
								}
							else
								{
								psend->pxm[i].resend_count=0;
								psend->pxm[i].xm_sended=0;
							XM_E("send_thread:select curr %d time %d socket %d\r\n",(int)currtime,(int)psend->pxm[i].timeout,psend->pxm[i].xm_socket_client);
							pnodeseek=psend->pxm[i].node;
							psend->pxm[i].timeout=0;
							psend->pxm[i].xm_send=0;
							psend->pxm[i].xm_sendready=0;
							psend->pxm[i].sendcmd=0;
							psend->pxm[i].sendsub=0;
							psend->pxm[i].xm_seting=1;
							while(pnodeseek){
								pnodetmp=pnodeseek->end;
								pnodeseek->errorid=XM_ERROR_RECV_TIMEOUT;
								pnodeseek->xm_sendready=0;
#if DEBUG_THREAD
								XM_D("send_thread:select post sem node %d index %d socket %d\r\n",pnodeseek->id,pnodeseek->index,psend->pxm[i].xm_socket_client);
#endif
								xm_wait_signal((XM_SYNC *)pnodeseek);
								pnodeseek=pnodetmp;								
							}
							psend->pxm[i].node=NULL;
#ifdef DEBUG_TIMEOUT_ASK
							if(psend->pxm[i].xm_socket_client!=-1){
								psend->pxm[i].XM_Frame_Buffer[0]=0xf4;
								psend->pxm[i].XM_Frame_Buffer[1]=0xfb;
								send(psend->pxm[i].xm_socket_client, psend->pxm[i].XM_Frame_Buffer,2,0);
							}
#endif
						}}
					}
#if DEBUG_THREAD
					//XM_D("send_thread:select unlock index %d socket %d\r\n",psend->pxm[i].xm_index,psend->pxm[i].xm_socket_client);
#endif
					pthread_mutex_unlock(&psend->pxm[i].mutex);
				}
			}else{
				for(i=0;i<psend->xmlen;i++){
					time(&currtime);
#if DEBUG_THREAD
					//XM_D("send_thread:recv lock index %d socket %d\r\n",psend->pxm[i].xm_index,psend->pxm[i].xm_socket_client);
#endif
					pthread_mutex_lock(&psend->pxm[i].mutex);
					if (psend->pxm[i].xm_socket_client!=-1 && FD_ISSET(psend->pxm[i].xm_socket_client, &fd_SockSet)){
#if DEBUG_SCOKET
						XM_D("send_thread:recv time %d socket %d\r\n",(int)psend->pxm[i].timeout,psend->pxm[i].xm_socket_client);
#endif
						time(&psend->pxm[i].timeout);
						ret=recv_tcp(&psend->pxm[i],psend->pxm[i].XM_Frame_Buffer,psend->pxm[i].xm_socket_client,psend->pxm[i].xm_parse);
						if(ret!=XM_ERROR_WAIT_MOER){
							pnodeseek=psend->pxm[i].node;
							psend->pxm[i].timeout=0;
							psend->pxm[i].xm_send=0;
							psend->pxm[i].xm_sendready=0;
							psend->pxm[i].xm_seting=1;
							if(ret!=XM_SUCCESS){
								psend->pxm[i].sendcmd=0;
								psend->pxm[i].sendsub=0;
							}
							while(pnodeseek){
								pnodetmp=pnodeseek->end;
								if(ret!=XM_SUCCESS){
									XM_D("send_thread:recv parse fail %d\r\n",ret);
								}
								pnodeseek->errorid=ret;
								pnodeseek->xm_sendready=0;
#if DEBUG_THREAD
								XM_D("send_thread:recv post sem node %d index %d socket %d\r\n",pnodeseek->id,pnodeseek->index,psend->pxm[i].xm_socket_client);
#endif
								xm_wait_signal((XM_SYNC *)pnodeseek);
								pnodeseek=pnodetmp;
							}								
							psend->pxm[i].node=NULL;
						}
					}else{
						
						if(psend->pxm[i].timeout!=0 && (currtime-psend->pxm[i].timeout) >(XM_SELECT_TIMEOUT)){
							if(psend->pxm[i].resend_count<3)
								{
								time(&(psend->pxm[i].timeout));
								pnodeseek=psend->pxm[i].node;
								while(pnodeseek){
									time(&(pnodeseek->sync.timeout));
									pnodeseek=pnodeseek->end;
								}
								XM_E("send_thread:resend !!!resend_count=%d\r\n",psend->pxm[i].resend_count);
								printf_buf("send",(uchar *)psend->pxm[i].XM_Frame_Buffer,psend->pxm[i].xm_sended);
								ret=send(psend->pxm[i].xm_socket_client, psend->pxm[i].XM_Frame_Buffer,psend->pxm[i].xm_sended,0);
								psend->pxm[i].resend_count++;
								}
							else
								{
								psend->pxm[i].resend_count=0;
								psend->pxm[i].xm_sended=0;
							XM_E("send_thread:sum curr %d time %d\r\n",(int)currtime,(int)psend->pxm[i].timeout);
							pnodeseek=psend->pxm[i].node;
							psend->pxm[i].timeout=0;
							psend->pxm[i].xm_send=0;
							psend->pxm[i].xm_sendready=0;
							psend->pxm[i].sendcmd=0;
							psend->pxm[i].sendsub=0;
							psend->pxm[i].xm_seting=1;
							while(pnodeseek){
								pnodetmp=pnodeseek->end;
								pnodeseek->errorid=XM_ERROR_RECV_TIMEOUT;
								pnodeseek->xm_sendready=pnodeseek->xm_sendlen=0;
								pnodeseek->xm_sendready=0;
#if DEBUG_THREAD
								XM_D("send_thread:sum post sem node %d index %d socket %d\r\n",pnodeseek->id,pnodeseek->index,psend->pxm[i].xm_socket_client);
#endif
								xm_wait_signal((XM_SYNC *)pnodeseek);									
								pnodeseek=pnodetmp;
							}
							psend->pxm[i].node=NULL;
#ifdef DEBUG_TIMEOUT_ASK
							if(psend->pxm[i].xm_socket_client!=-1){
								psend->pxm[i].XM_Frame_Buffer[0]=0xf4;
								psend->pxm[i].XM_Frame_Buffer[1]=0xfb;
								send(psend->pxm[i].xm_socket_client, psend->pxm[i].XM_Frame_Buffer,2,0);
							}
#endif	
						}}
					}
					time(&runtime);
					newtime=runtime-currtime; 
					if(psend->pxm[i].timeout){
						psend->pxm[i].timeout+=newtime;
						pnodeseek=psend->pxm[i].node;
						while(pnodeseek){
							pnodetmp=pnodeseek->end;
							pnodeseek->sync.timeout+=newtime;
							pnodeseek=pnodetmp;
						}
					}
#if DEBUG_THREAD
					//XM_D("send_thread:recv unlock index %d socket %d\r\n",psend->pxm[i].xm_index,psend->pxm[i].xm_socket_client);
#endif
					pthread_mutex_unlock(&psend->pxm[i].mutex);
				}	
			}
		}else{
//#ifdef ANDROID
			//sleep(1);
//#else
			usleep(10000);
//#endif
		}
#ifdef ANDROID
		//XM_D("send_thread: next %d\r\n",*psend->pexit);
#endif
	}
#ifdef DEBUG_RS
	XM_D("send_thread: exit %d\r\n",psend->xmlen);
#endif
	for(i=0;i<psend->xmlen;i++){
#if DEBUG_THREAD
		XM_D("send_thread:exit lock index %d socket %d\r\n",psend->pxm[i].xm_index,psend->pxm[i].xm_socket_client);
#endif
		pthread_mutex_lock(&psend->pxm[i].mutex);
		if( psend->pxm[i].xm_sendready && psend->pxm[i].xm_socket_client>0){			
			psend->pxm[i].xm_socket_client=-1;
			psend->pxm[i].xm_exit=1;
			psend->pxm[i].xm_sendready=0;
			psend->pxm[i].xm_send=0;
			psend->pxm[i].xm_sendready=0;
			psend->pxm[i].sendcmd=0;
			psend->pxm[i].sendsub=0;
			pnodeseek=psend->pxm[i].node;							
			while(pnodeseek){
				pnodetmp=pnodeseek->end;
				pnodeseek->errorid=XM_ERROR_NOT_SEND;
				pnodeseek->xm_sendready=0;
#if DEBUG_THREAD
				XM_D("send_thread:exit post sem node %d index %d socket %d\r\n",pnodeseek->id,pnodeseek->index,psend->pxm[i].xm_socket_client);
#endif
				xm_wait_signal((XM_SYNC *)pnodeseek);
				pnodeseek=pnodetmp;
			}
			psend->pxm[i].node=NULL;
		}
		if(psend->pxm[i].xm_socket_client!=-1){
#ifdef DEBUG_TIMEOUT_ASK
			psend->pxm[i].XM_Frame_Buffer[0]=0xf4;
			psend->pxm[i].XM_Frame_Buffer[1]=0xfb;
			send(psend->pxm[i].xm_socket_client, psend->pxm[i].XM_Frame_Buffer,2,0);
#endif
			psend->pxm[i].xm_socket_client=-1;
		}
#if DEBUG_THREAD
		XM_D("send_thread:exit unlock index %d socket %d\r\n",psend->pxm[i].xm_index,psend->pxm[i].xm_socket_client);
#endif
		pthread_mutex_unlock(&psend->pxm[i].mutex);
	}
	#if DEBUG_RS
	XM_D("send_thread: exit\r\n");
	#endif
#ifdef PLAT_LINUX
	//DetachÖ÷Ïß³Ì
	if (pjvm!=NULL){
	    if((*pjvm)->DetachCurrentThread(pjvm) != JNI_OK)
	    {
	         LOGE("%s: DetachCurrentThread() failed", __FUNCTION__);
	    }
	}
#endif
exit_send_thread:
	free(psend);
	XmDelLog();
	return NULL;
}
void send_data(XM_PROTOCOL *pxm,XM_NODE * pnode){
	pnode->end=NULL;
	pnode->errorid=XM_SUCCESS;
	pxm->xm_frame=0xff;
	pxm->xm_sub_frame=0xff;
	strDividing(pxm,pnode,pnode->atbuf,pnode->atlen);
	if(pnode->errorid!=XM_SUCCESS){
		XM_E("ERROR node:at parse fail  %s\r\n",pnode->atbuf);
#if DEBUG_THREAD
		XM_D("node:pasre unlock node %d index %d socket %d\r\n",pnode->id,pxm->xm_index,pxm->xm_socket_client);
#endif
		pthread_mutex_unlock(&pxm->mutex);
		goto append_exit;
	}
	proc_cmd(pxm,pnode);
#if DEBUG_RS
	XM_D("node:proc_cmd node %d error %d\r\n",pnode->index,pnode->errorid);
#endif
	if(pnode->errorid!=XM_SUCCESS){
		if(XM_ERROR_NOT_SEND==pnode->errorid || XM_ERROR_WAIT_MOER==pnode->errorid){
#if DEBUG_RS
			XM_D("node:not need or wait send data %d error %d\r\n",pnode->index,pnode->errorid);
#endif
			pnode->errorid=XM_SUCCESS;
		}
		if(XM_SUCCESS!=pnode->errorid ){
			XM_E("ERROR node:at cmd fail  %s\r\n",pnode->xm_cmd->cmd);
		}
	}
append_exit:
#if DEBUG_CMD
	XM_D("node:exit index %d \r\n",pnode->index);
#endif
	if(pnode->errorid!=XM_SUCCESS || !strlen(pnode->xm_at.XM_At_Ret)){
		XM_E("ERROR node:ret fail %d\r\n",pnode->errorid);			
		build_at_ret(pxm,pnode,NULL,pnode->errorid);
	}
	return;
}

