
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
#include    "server.h"

#define IPv4_STR_PORT_PRT(addr,port) XM_D("%d.%d.%d.%d:%d\r\n", (addr)>>24&0xff, (addr)>>16&0xff, (addr)>>8&0xff, (addr)&0xff,(ushort)port)
#define SERVER_PORT "9999"
#define SERVER_RET 1
static int xm_socket_server=-1;

XM_SERVER_MAP *xm_connect;
char xm_status[XM_MAX_BUF];
char xm_server_buf[XM_MAX_BUF];
char xm_data[8];
char xm_devid[18];
char xm_baundrate[1];
char xm_wifi_buf[2];
char xm_ver_buf[4];
char xm_ver_mutil[255];
char xm_devpower[48];
char xm_rev[64];

int socket_proc(XM_SERVER_MAP *xm_server,uchar *pbuf,int socket_clinet){	
	int nRecv;
#if SERVER_RET	
	XM_Command *pCommd=NULL;
	int i,ret;
	uchar address,j,nBitOffset,nByteOffset,nMask,nValue,nLen=0;
	char Transfer_flag2=0;
	char Network_flag2=0;
	char Frame_flag2=0;
	char Encryption=0;
	char Retry=0;
	uchar *sendbuf=NULL;
#endif
#if DEBUG_SCOKET
	XM_D("socket_proc:%d\r\n", socket_clinet); 
#endif
	nRecv = recv(socket_clinet, pbuf, XM_MAX_BUF, 0);
	if (nRecv < 0) {
		XM_E("ERROR server recv() error, ret = %d\r\n", nRecv);
		return nRecv;
	}
	pbuf[nRecv]='\0';
#if SERVER_RET
#if DEBUG_SCOKET
	printf_buf("server recv",pbuf,nRecv);
#endif
#endif
#if SERVER_RET	
	if(pbuf[0]=='A' && pbuf[1]=='T' && pbuf[2]=='+'){
		send(socket_clinet, "AT+RET=0\r\n",strlen("AT+RET=0\r\n"),0);
	}else if(pbuf[0]=='X' && pbuf[1]=='M' && pbuf[2]=='-' && pbuf[3]=='M'){
		for(i=0;i<XM_CONNECT_NUM;i++){
			if(!xm_connect[i].xm_socket_module){
				xm_connect[i].xm_socket_module=socket_clinet;
				xm_connect[i].xm_module_id=atoi((char *)&pbuf[8]);
#if DEBUG_SCOKET
				XM_D("socket_proc:module %d\r\n", xm_connect[i].xm_module_id); 
#endif
				return -1;
			}
		}
	}else if(pbuf[0]=='X' && pbuf[1]=='M' && pbuf[2]=='-' && pbuf[3]=='C'){
		ret=atoi((char *)&pbuf[8]);		
#if DEBUG_SCOKET
		XM_D("socket_proc:clinet %d\r\n", ret); 
#endif
		for(i=0;i<XM_CONNECT_NUM;i++){
			if(xm_connect[i].xm_module_id==ret){
				xm_connect[i].xm_socket_client=socket_clinet;
				xm_connect[i].xm_socket_virtual=0;
				return -1;
			}
		}
	}else if(pbuf[0]=='X' && pbuf[1]=='M' && pbuf[2]=='-' && pbuf[3]=='V'){
		for(i=0;i<XM_CONNECT_NUM;i++){
			if(!xm_connect[i].xm_socket_client && !xm_connect[i].xm_socket_module){
				xm_connect[i].xm_socket_client=socket_clinet;
				xm_connect[i].xm_socket_virtual=1;
				ret=send(socket_clinet, "OK",strlen("OK"),0);
				return -1;
			}
		}
	}else if(xm_server){
		if(xm_server->xm_socket_virtual){
			statusInit(&xm_server->xm_protocl);
			for(i=0;i<nRecv;i++){
				ret=Parse_Read(&(xm_server->xm_protocl),xm_server->xm_protocl.XM_Frame_Buffer+i,Proc_recv);
				if(ret==XM_SUCCESS){
					MessageHead * pMsg=(MessageHead *)xm_server->xm_protocl.XM_Status_Buffer;
					pMsg->Result=1;
					//查找哪个命令执行
					if(xm_server->xm_protocl.xm_status.P_XM_KL_Network_Address_1){
						xm_server->xm_protocl.xm_addres_1[0]=xm_server->xm_protocl.xm_status.P_XM_KL_Network_Address_1[0];
						xm_server->xm_protocl.xm_addres_1[1]=xm_server->xm_protocl.xm_status.P_XM_KL_Network_Address_1[1];
					}
					if(xm_server->xm_protocl.xm_status.P_XM_KL_Network_Address_2){
						xm_server->xm_protocl.xm_addres_2[0]=xm_server->xm_protocl.xm_status.P_XM_KL_Network_Address_2[0];
						xm_server->xm_protocl.xm_addres_2[1]=xm_server->xm_protocl.xm_status.P_XM_KL_Network_Address_2[1];
					}
					address=xm_server->xm_protocl.xm_addres_1[0];
					if(xm_server->xm_protocl.xm_status.MsgLen>sizeof(MessageHead)){
						pCommd=getcommand(address,pMsg->MessageType,pMsg->MessageSubType,(char *)(xm_server->xm_protocl.XM_Status_Buffer+sizeof(MessageHead)),xm_server->xm_protocl.xm_status.MsgLen-sizeof(MessageHead));
					}
				#if DEBUG_RS
					XM_D("server:command %p c %d s %d a %d\r\n", pCommd,pMsg->MessageType,pMsg->MessageSubType,address);
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

						sendbuf=(uchar *)xm_rev;nLen=64;
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
								XM_D("server:recv len 0x%02x\r\n",pCommd->send[j].len);
#endif
								if(pCommd->send[j].len<=8){	
									nByteOffset=pCommd->send[j].offset/8;
									nBitOffset =7-pCommd->send[j].offset%8;
									nMask=(0xff>>(8-pCommd->send[j].len))<<nBitOffset;
									nValue=nMask & xm_server->xm_protocl.XM_Status_Buffer[sizeof(MessageHead)+nByteOffset];
									nValue>>=nBitOffset;
#if DEBUG_CMD
									XM_D("server:Offset 0x%02x\r\n",nBitOffset);	
									XM_D("server:Byte 0x%02x\r\n",nByteOffset);
									XM_D("server:nMask 0x%02x\r\n",nMask);
									XM_D("server:nValue 0x%02x\r\n",nValue);
#endif
									nBitOffset =7-pCommd->recv[j].offset%8;
									nByteOffset=pCommd->recv[j].offset/8;
									nMask=(0xff>>(8-pCommd->recv[j].len))<<nBitOffset;
									nValue<<=nBitOffset;
#if DEBUG_CMD
									XM_D("server:Offset 0x%02x\r\n",nBitOffset);	
									XM_D("server:Byte 0x%02x\r\n",nByteOffset);
									XM_D("server:nMask 0x%02x\r\n",nMask);
									XM_D("server:nValue 0x%02x\r\n",nValue);
#endif
									sendbuf[nByteOffset] &=~nMask;
									sendbuf[nByteOffset] |=nValue;
#if DEBUG_CMD
									XM_D("server:status 0x%02x\r\n",sendbuf[nByteOffset]);
#endif
								}else{
									nValue=pCommd->send[j].len/8;
#if DEBUG_CMD
									XM_D("server:buf len %d offset %d\r\n",pCommd->send[j].len,pCommd->send[j].offset);	
									XM_D("server:recv en %d offset %d\r\n",pCommd->recv[j].len,pCommd->recv[j].offset);
									XM_D("server:buf Offset 0x%02x\r\n",(pCommd->send[j].offset+1-pCommd->send[j].len)/8);	
									XM_D("server:recv Offset 0x%02x\r\n",(pCommd->recv[j].offset+1-pCommd->recv[j].len)/8);
#endif
									memcpy(&sendbuf[(pCommd->recv[j].offset+1-pCommd->recv[j].len)/8],&xm_server->xm_protocl.XM_Status_Buffer[sizeof(MessageHead)+(pCommd->send[j].offset+1-pCommd->send[j].len)/8],nValue);
#if DEBUG_CMD
									printf_buf("server status",(uchar *)sendbuf,pCommd->send[j].len/8);
#endif
								}
							}
						}
						
					}else{
						memcpy(xm_server->xm_protocl.XM_Status_Buffer+sizeof(MessageHead),sendbuf,nLen);
					}
					nRecv=Parse_Send(xm_server->xm_protocl.XM_Frame_Buffer,xm_server->xm_protocl.XM_Status_Buffer,sizeof(MessageHead)+nLen,xm_server->xm_protocl.xm_addres_2,xm_server->xm_protocl.xm_addres_1,xm_server->xm_protocl.xm_addres_3,xm_server->xm_protocl.xm_addres_4,xm_server->xm_protocl.xm_addres_5,xm_server->xm_protocl.xm_addres_count,xm_server->xm_protocl.xm_addres_all,xm_server->xm_protocl.xm_addres_type,xm_server->xm_protocl.xm_addres_struct,xm_server->xm_protocl.xm_encryption_type,xm_server->xm_protocl.xm_crc_type,1,Transfer_flag2,Network_flag2,Frame_flag2,Encryption,Retry);
				#if DEBUG_SCOKET
					printf_buf("server send",xm_server->xm_protocl.XM_Frame_Buffer,nRecv);
				#endif
					ret=send(socket_clinet, xm_server->xm_protocl.XM_Frame_Buffer,nRecv,0);
				#if DEBUG_SCOKET
					XM_D("server: sended  %d\r\n", ret);
					XM_D("write ok!\r\n");
				#endif
					break;
				}
			}
		}else{
			send(socket_clinet==xm_server->xm_socket_client?xm_server->xm_socket_module:xm_server->xm_socket_client,pbuf,nRecv,0);
		}
			
	}
#endif
#if DEBUG_SCOKET
	XM_D("socket_proc:%d exit\r\n", socket_clinet); 
#endif
	return nRecv;		
}

void *init_socket_server(void * arg){
	XM_SERVER *pserver=(XM_SERVER *)arg;
	int fd_act,i,ret,tmp_accept,max_fb,connect_num=0;
	struct sockaddr_in s_add,c_add;
	socklen_t sin_size=16;
	unsigned short portnum=8888;
	fd_set fd_sockserver;	
	struct timeval tmo;	
	int *xm_tmp_connect;
	int *xm_tmp_addr;
	short *xm_tmp_port;
	int rep = 1;
	
	XmSetLog("socket_server",0);
#if DEBUG_RS
	XM_D("init_socket_server:port %s\r\n",pserver->serverport);
#endif
	if(!pserver){
		XM_E("ERROR socket_server:arg error %p!\r\n",arg);
		return NULL;
	}
	xm_connect=(XM_SERVER_MAP *)malloc(sizeof(XM_SERVER_MAP)*pserver->xmlen);
	if(xm_connect==NULL){
		XM_E("ERROR socket_server:xm_connect malloc fail %p!\r\n",xm_connect);
		return NULL;
	}
	memset(xm_connect,0,pserver->xmlen*sizeof(XM_SERVER_MAP));
	xm_tmp_connect=(int *)malloc(sizeof(int)*pserver->xmlen);
	xm_tmp_addr=(int *)malloc(sizeof(int)*pserver->xmlen);
	xm_tmp_port=(short *)malloc(sizeof(short)*pserver->xmlen);
	memset(xm_status,0,XM_MAX_BUF);
	for(i=0;i<pserver->xmlen;i++){
		xm_tmp_connect[i]=0;
		xm_tmp_addr[i]=0;
		xm_tmp_port[i]=0;
	}
	xm_socket_server = socket(AF_INET, SOCK_STREAM, 0);
	if(-1 == xm_socket_server)
	{
	    XM_E("ERROR socket fail ! \r\n");
	    goto server_exit;
	}
	XM_D("socket ok !\r\n");
	setsockopt( xm_socket_server, SOL_SOCKET, SO_REUSEADDR, &rep, sizeof(rep) );
	portnum=atoi(pserver->serverport);
	//portnum=atoi(SERVER_PORT);
	#if DEBUG_SCOKET
	XM_D("init_socket_server:port %d\r\n",portnum);
	#endif
	memset(&s_add,0,sizeof(struct sockaddr_in));	
	s_add.sin_family=AF_INET;
	s_add.sin_addr.s_addr=htonl(INADDR_ANY);
	s_add.sin_port=htons(portnum);

	if(-1 == bind(xm_socket_server,(struct sockaddr *)(&s_add), sizeof(struct sockaddr)))
	{
	    XM_E("ERROR bind fail !\r\n");
		goto server_exit;
	}
	#if DEBUG_SCOKET
	XM_D("bind ok !\r\n");
	#endif
	if(-1 == listen(xm_socket_server,5))
	{
	    XM_E("ERROR listen fail !\r\n");
	    goto server_exit;
	}
	#if DEBUG_SCOKET
	XM_D("listen ok\r\n");
	#endif
	while( xm_socket_server>0 && ! (*pserver->pexit)){		
		/* wait for somebody to connect me */
#if DEBUG_SCOKET
		//XM_D("accpet ZERO \r\n");
#endif
		tmo.tv_sec = XM_SELECT_TIME;
		tmo.tv_usec = 0;
		FD_ZERO(&fd_sockserver);
#if DEBUG_SCOKET
		//XM_D("Accept SET \r\n");
#endif
		max_fb=xm_socket_server;
		FD_SET(xm_socket_server, &fd_sockserver);
		for(i=0;i<pserver->xmlen;i++){
			if(xm_connect[i].xm_socket_client){
				FD_SET(xm_connect[i].xm_socket_client, &fd_sockserver);
				if(xm_connect[i].xm_socket_client>max_fb)
					max_fb=xm_connect[i].xm_socket_client;
			}
			if(xm_connect[i].xm_socket_module){
				FD_SET(xm_connect[i].xm_socket_module, &fd_sockserver);
				if(xm_connect[i].xm_socket_module>max_fb)
					max_fb=xm_connect[i].xm_socket_module;
			}
			if(xm_tmp_connect[i]){
				FD_SET(xm_tmp_connect[i], &fd_sockserver);
				if(xm_tmp_connect[i]>max_fb)
					max_fb=xm_tmp_connect[i];
			}
		}
#if DEBUG_SCOKET
		//XM_D("Accept select %d\r\n",max_fb);
#endif
		fd_act = select(max_fb+1, &fd_sockserver, NULL, NULL, &tmo);
		if(fd_act <= 0)
		{
#if DEBUG_SCOKET
			XM_D("connec %d time %d exit %d\r\n",connect_num,(int)tmo.tv_sec,*pserver->pexit);
#endif
			continue ;
		}
		else{
#if DEBUG_SCOKET				
			//XM_D("accpet:select %d\r\n",fd_act);
#endif
			if (FD_ISSET(xm_socket_server, &fd_sockserver)) {
				memset(&c_add,0,sizeof(struct sockaddr_in));
				tmp_accept = accept(xm_socket_server, (struct sockaddr *) &c_add, &sin_size);
				if (tmp_accept < 0) {
					XM_D("ERROR accept fail, ret = %d!\r\n", tmp_accept);
					break;
				}
#if DEBUG_RS				
				XM_D("accpet:%d %d %d\r\n",tmp_accept,connect_num,sin_size);
#endif
				if(connect_num<(pserver->xmlen)){
					for(i=0;i<pserver->xmlen;i++){
						if(!xm_tmp_connect[i]){
							xm_tmp_connect[i]=tmp_accept;
							xm_tmp_addr[i] = ntohl(c_add.sin_addr.s_addr);
							xm_tmp_port[i] = ntohs(c_add.sin_port);
#if DEBUG_SCOKET
							IPv4_STR_PORT_PRT(xm_tmp_addr[i],xm_tmp_port[i]);
#endif
							connect_num++;							
#if DEBUG_SCOKET						
							XM_D("accpet:new%d %d\r\n",i,connect_num);
#endif
							ret=send(xm_tmp_connect[i],"AT+WHO=?",strlen("AT+WHO=?"),0);
							break;
						}
					}
				}else{
					send(tmp_accept,"\t connect is full!!!",strlen("connect is full!!!"),0);
					close(tmp_accept);
				}
			}else{
				for(i=0;i<pserver->xmlen;i++){
					if(xm_connect[i].xm_socket_client){
						if (FD_ISSET(xm_connect[i].xm_socket_client, &fd_sockserver)) {
#if DEBUG_RS
							XM_D("server:client_proc %d\r\n",xm_tmp_connect[i]);
#endif
							ret=socket_proc(&xm_connect[i],xm_connect[i].xm_protocl.XM_Frame_Buffer,xm_connect[i].xm_socket_client);
#if DEBUG_RS
							XM_D("server: client_proc finish %d\r\n",ret);
#endif
							if(ret<=0){
#if DEBUG_SCOKET
								XM_D("server: client_proc exit %d\r\n",ret);
#endif
								close(xm_connect[i].xm_socket_client);
								xm_connect[i].xm_socket_client=0;
							}
						}
					}
					if(xm_connect[i].xm_socket_module){
						if (FD_ISSET(xm_connect[i].xm_socket_module, &fd_sockserver)) {
#if DEBUG_SCOKET
							XM_D("server:module_proc %d\r\n",xm_tmp_connect[i]);
#endif
							ret=socket_proc(&xm_connect[i],xm_connect[i].xm_protocl.XM_Frame_Buffer,xm_connect[i].xm_socket_module);
							if(ret<=0){
#if DEBUG_SCOKET
								XM_D("server: client_proc exit %d\r\n",ret);
#endif
								close(xm_connect[i].xm_socket_module);
								xm_connect[i].xm_socket_module=0;
								if(xm_connect[i].xm_socket_client){
									close(xm_connect[i].xm_socket_client);
									xm_connect[i].xm_socket_client=0;
								}
							}
						}
					}
#if DEBUG_SCOKET
					XM_D("server:tmp_connect proc %d\r\n",xm_tmp_connect[i]);
#endif
					if(xm_tmp_connect[i]){
						if (FD_ISSET(xm_tmp_connect[i], &fd_sockserver)) {
							ret=socket_proc(NULL,(uchar *)xm_server_buf,xm_tmp_connect[i]);
							if(ret<0){
#if DEBUG_SCOKET
								XM_D("server: socket_proc exit %d\r\n",ret);
#endif
								xm_tmp_connect[i]=0;
								connect_num--;
							}
						}else{
							ret=send(xm_tmp_connect[i],"AT+WHO=?",strlen("AT+WHO=?"),0);
#if DEBUG_SCOKET						
							XM_D("accpet:send %d\r\n",ret);
#endif
						}
					}
				}
				
			}
		}
	}
#if DEBUG_SCOKET
	XM_D("Accept exit\r\n");
#endif
	for(i=0;i<pserver->xmlen;i++){
		if(xm_connect[i].xm_socket_client!=-1){
			close(xm_connect[i].xm_socket_client);
			xm_connect[i].xm_socket_client=-1;							
		}
	}
#if DEBUG_RS
	XM_D("server exit!\r\n");
#endif
server_exit:
	if(xm_socket_server!=-1){
		close(xm_socket_server);
		xm_socket_server=-1;
	}
	return NULL;
}

void servsr_stop(void){
	if(xm_socket_server>0){
		close(xm_socket_server);
		xm_socket_server=-1;
	}
}
int servsr_start(pthread_t *tid_server,char * server_port,int *nexit,int connect){
	int err,timeout=10;
	XM_SERVER * server_arg;
	if(xm_socket_server>0){
		XM_E("ERROR server thread  error:alary init\r\n");  
		return XM_SUCCESS;
	}
	server_arg=(XM_SERVER *)malloc(sizeof(XM_SERVER));
	if(server_arg==NULL){
		XM_E("ERROR server thread  error:arg malloc fail\r\n"); 
		return -1;
	}
	server_arg->xmlen=connect;
	server_arg->pexit=nexit;
	server_arg->serverport=server_port;
	err=pthread_create(tid_server,NULL,init_socket_server,server_arg);//创建线程  
    if(err!=0)
    {  
        XM_E("ERROR server thread  error:%s\r\n",strerror(err));  
        return XM_ERROR_THEARD;
    }
	while(xm_socket_server==-1 && timeout){
#if DEBUG_SCOKET
        XM_D("server:wait socket server:%d\r\n",timeout);
#endif
		sleep(1);
		timeout--;
	}
	if(!timeout){
		XM_E("ERROR server socket timeout :%d\r\n",timeout);  
        return XM_ERROR_SOCKET_TIMEOUT;
	}
	return XM_SUCCESS;
}

