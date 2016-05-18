#ifndef _Included_Server
#define _Included_Server
typedef struct _server_arg{
	int xmlen;//最大连接
	int *pexit;//退出标志位指针
	char *serverport;//服务端口
}XM_SERVER;
/*
虚拟服务线程
参数:
tid_server:线程句柄指针
server_port:服务端口
nexit:退出标志位指针
connect:最大连接
返回:

*/
int servsr_start(pthread_t *tid_server,char * server_port,int *nexit,int connect);
/*
停止虚拟服务线程
参数:
返回:
*/
void servsr_stop(void);

#endif
