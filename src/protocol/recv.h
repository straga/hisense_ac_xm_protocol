#ifndef _Included_Recv
#define _Included_Recv
/*
接收网络数据，并根据标志进行处理
参数:
pxm:socket 数据指针
pbuf:保存接收到数据的指针
tcp_fd:需要接收的socket 句柄
parse:数据分析还是拷贝
返回:
出错代码
*/
char recv_tcp(XM_PROTOCOL *pxm,uchar *pbuf,int tcp_fd,int parse);
#endif
