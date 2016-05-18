#ifndef _Included_Client
#define _Included_Client

/*
在节点数组中加入一个发送节点
参数:
index: socket 数组的序号
atcmd:要发送的AT 命令
len:AT 命令的长度
nexit:退出标志位的指针
返回:
节点数据的指针
*/
XM_NODE * client_new_node(int index,char *atcmd,int len,int *nexit);
/*
参数:
tid_send: 线程句柄的指针
nexit:退出标志位的指针
返回:
*/
void client_clean_client(JavaVM *pjvm,pthread_t *tid_send,int *nexit);
/*
初始化socket数组和发送节点
参数:
tid_send: 线程句柄的指针
nexit:退出标志位的指针
connect_num:最大连接数
send_num:最大发送数
返回:
成功返回0
*/
int client_init_client(JavaVM *pjvm,pthread_t *tid_send,int *nexit,int connect_num,int send_num);
/*
参数:
index: socket 数组的序号
返回:
socket句柄，出错返回-1
*/
int client_get_socket(int index);
/*
获取socket 数组的序号
参数:
socket_fd: socket句柄
返回:
socket 数组的序号，出错返回-1
*/
int client_get_index(int socket_fd);
/*
获取socket数组的指针
参数:
index: socket 数组的序号
返回:
socket数组的指针
*/
XM_PROTOCOL * client_get_client(int index);
/*
初始化全局锁
参数:
返回:
*/
void client_init_lock(void);
/*
清除指定的socket数组和相关节点, 不关闭socket
参数:
socketfd:socket句柄
返回:
成功为0
*/
int client_exit_client(int socketfd);
/*
在socket 数组中加入一个socket句柄
参数:
socket:socket句柄
id:设备地址
返回:
返回socket 数组指针,出错返回NULL
*/
XM_PROTOCOL * client_new_index(int socket,int id);
void client_clear_socket();
#endif
