#ifndef _Included_Send
#define _Included_Send

typedef struct _send_arg{
	pthread_mutex_t *pmutex;
	XM_PROTOCOL *pxm;
	int xmlen;
	int *pexit;
	JavaVM *pjvm;
}XM_SEND;
/*
发送线程
参数:
arg:参数
返回:
*/
void *send_thread(void * arg);
/*
发送一个数据包，并接收返回
参数:
pxm:socket 数据指针
pbuf:需要发送的数据
len:数据长度
返回:
错误代码
*/
uchar send_tcp(XM_PROTOCOL *pxm,uchar *pbuf,uchar len);
/*
发送一个节点的内容,先分析AT 命令，再调 用proc_cmd 进行数据 准备，最后等 发送线程完成发送
参数:
pxm:socket 数据指针
pnode:发送节点
返回:
错误代码在发送节点中
*/
void send_data(XM_PROTOCOL *pxm,XM_NODE * pnode);
#endif
