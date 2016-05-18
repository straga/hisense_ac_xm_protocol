#ifndef _Included_xm_type
#define _Included_xm_type

#include	<stdio.h>
#include	<stdlib.h>
#include    <string.h>
#include   <unistd.h>
#include    <pthread.h>
#include    <semaphore.h>
#include    <errno.h>
#include    <time.h>
#ifdef PLAT_LINUX
#include    <unistd.h>
#include    <sys/time.h>
#endif

#ifdef PLAT_LINUX
#ifdef XM_MEM_DEBUG
#include <mcheck.h>
#endif
#include <jni.h>
#else
#define JavaVM void
#endif
typedef unsigned char uchar;
typedef unsigned short ushort;
typedef	unsigned int uint;
typedef unsigned long ulong;
struct _at_fun;
#define USE_SEM 0
#define SEM_TIMEOUT 10
#define WAIT_TIMEOUT 100

#ifdef PLAT_LINUX
#ifdef ANDROID
#define  MAX_SEND_POOL 128
#define  XM_CONNECT_NUM 1
#else
#define  MAX_SEND_POOL 4096
#define  XM_CONNECT_NUM 1024
#endif
#else
#define  MAX_SEND_POOL 128
#define  XM_CONNECT_NUM 1
#endif
#define XM_RE_SEND 1
#define  MAX_CMD_NUM 64

//debug
#define DEBUG_VERIFY 0
#define DEBUG_MAIN 1
#define DEBUG_SEND 0
#define DEBUG_RECV 0
#define DEBUG_CRC 0
#define DEBUG_AT 0
#define DEBUG_SCOKET 0
#define DEBUG_THREAD 0
#define DEBUG_CMD 0
#define DEBUG_RS 1

#define TRUE	1
#define FALSE	0
#define XM_APP 0
#define XM_WITH_ID 1
#define XM_SEND_SETTING 1
#define XM_SEND_QUERY 0
#define XM_SEND_SUPPORT 2
#define XM_SEND_CONFIG 3

//**********************位操作定义*********************************
#define SETB(x,y)	(x|=1<<y)	//将X中的Y位置1
#define CLRB(x,y)	(x&=~(1<<y))	//将X中的Y位清0
#define GETB(x,y)	(x&(1<<y))	//检测X中的Y位内容
#define XORB(x,y)	(x^=(1<<y))	//将X中的Y位取反

//buf max
#define XM_ADDRES_MAX 24
#define XM_AT_MIN 3
#define XM_ID_MAX 32

#define XM_ERROR_MODUEL_RET_FAIL  0
#define XM_ERROR_MODUEL_NOT_SUPPORT  8
#define XM_ERROR_NET_SEND_FAIL  101
#define XM_ERROR_NET_RECV_FAIL  102
#define XM_ERROR_BUILD_PACKET_FAIL  103
#define XM_ERROR_RECV_FULL  104
#define XM_ERROR_RECV_TIMEOUT  105
#define XM_ERROR_SOCKET_FAIL  106
#define XM_ERROR_WAIT_MOER  107
#define XM_ERROR_VAIL  108
#define XM_ERROR_NOMACH_CMD  109
#define XM_ERROR_BUF_SMALL  110
#define XM_ERROR_PARAMETER  111
#define XM_ERROR_BUILD_MSG  112
#define XM_ERROR_MSG_SIZE  113
#define XM_ERROR_CONNECT  114
#define XM_ERROR_DNS  115
#define XM_ERROR_SOCKET_TIMEOUT  116
#define XM_ERROR_THEARD  117
#define XM_ERROR_NOT_INIT  118
#define XM_ERROR_CMD_NOT_SUPPORT  119
#define XM_ERROR_CMD_TYPE  120
#define XM_ERROR_CMD_EXEC  121
#define XM_ERROR_SOCKET_SEND  122
#define XM_ERROR_SOCKET_BREAK  123
#define XM_ERROR_INIT  124
#define XM_ERROR_AT_PRAR 125
#define XM_ERROR_NOT_SEND 126
#define XM_ERROR_LOCK 127
#define XM_ERROR_NODE 128
#define XM_ERROR_SOCKET_EXIT  129
#define XM_ERROR_MALLOC  130
#define XM_ERROR_INDEX  131
#define XM_ERROR_NODE_FULL  132
#define XM_ERROR_FORCE_CLOSE_NODE  133
#define XM_ERROR_FORCE_CLOSE_CONNETCTION  134


#define XM_ERROR_FRAME_MAX 10
#define XM_ERROR_FRAME_HEAD 11
#define XM_ERROR_FRAME_ACK 12
#define XM_ERROR_FRAME_SUPPORT 13
#define XM_ERROR_FRAME_FLAG 14
#define XM_ERROR_FRAME_UNKOWN 15
#define XM_ERROR_FRAME_SIZE 16
#define XM_ERROR_FRAME_CRC 17
#define XM_ERROR_FRAME_END 18
#define XM_ERROR_FRAME_END2 19
#define XM_ERROR_FRAME_MORE 20
#define XM_ERROR_NETWORK_ACK 21
#define XM_ERROR_NETWORK_SUPPORT 22
#define XM_ERROR_NETWORK_FLAG 23
#define XM_ERROR_NETWORK_UNKOWN 24
#define XM_ERROR_TRANSFER_ACK 25
#define XM_ERROR_TRANSFER_SUPPORT 26
#define XM_ERROR_TRANSFER_FLAG 27
#define XM_ERROR_TRANSFER_UNKOWN 28
#define XM_ERROR_DEV_ADDRESS 29
#define XM_ERROR_WIFI_ADDRESS 30
#define XM_ERROR_MAX_CMD_IN_ONE_SOCKET 31
#define XM_ERROR_MAX_CMD_IN_STRING_PARSE_ERROR 32

#define XM_SUCCESS 0

#define XM_ERROR_NO_BODY	33
#define XM_ERROR_NO_AT		34

/*Add by Tao He*/
/* type of Frame Check Sum*/
#define FCS_1BYTE_ADD 	0
#define FCS_2BYTES_ADD	1
#define FCS_2BYTES_CRC	2
#define FCS_4BYTES_CRC	3



//at cmd
#define MAX_CMD_PARAM_NUM 256
#define XM_MAX_BUF 1024
#define  XM_SELECT_TIMEOUT 2
#define  XM_SELECT_TIME 1
#define  XM_SELECT_TIME_US 0
#define MAX_AT_CMD_NUM 1
#pragma pack(1)
typedef struct _str2int{
	char *str;
	uchar  value;
}XM_Value;

typedef struct _offset_struct{
	ushort offset;//偏移
	ushort  len;//长度
	uchar textlen;//映射表长度
	XM_Value *text;//映射表
	uchar  support;//在功能查询时有效
	uchar  query;//在状态查询 时有效
	uchar  set;//在设置 时有效
	uchar preset;//预设值,在设置 时自动生效
}XM_Offset;

typedef struct _command_struct{
	uchar  send_num;//发送的参数个数
	uchar  recv_num;//接收的参数个数
	uchar  set_len;//设置发送字符长度
	uchar  query_len;//状态返回字符长度
	uchar  support_len;//功能支持查询返回字符长度
	uchar  set_cmd;//设置的命令
	uchar  set_sub;//设置子命令
	uchar  query_cmd;//状态的命令
	uchar  query_sub;//状态的子命令
	uchar  support_cmd;//功能支持查询的命令
	uchar  support_sub;//功能支持查询的子命令
	XM_Offset send[MAX_CMD_PARAM_NUM];//发送参数组
	XM_Offset recv[MAX_CMD_PARAM_NUM];//接收参数组
}XM_Command;

typedef struct _xm_at{
/*单条指令解析后参数*/ 
	char *getcmd;
	char *getparam[MAX_CMD_PARAM_NUM];
	char XM_At_Buffer[XM_MAX_BUF]; //缓存命令数据
	char XM_At_Ret[XM_MAX_BUF]; //保存返回结果
}XM_AT;

typedef struct _xm_protocol_status{
	uchar	XM_KL_Frame_Ack;		   //Usart0无线接收帧应答
	uchar	XM_KL_Frame_Size_Count; 		   //Usart0无线接收帧长度字节数个数
	uchar	XM_KL_Frame_Checksum_Type;
	uchar	XM_KL_Frame_Checksum_Count; 	   //Usart0无线接收校验和节数个数
	uchar	XM_KL_Frame_Flag_1; 	   //Usart0无线接收帧标识1
	uchar	XM_KL_Frame_Flag_2; 	   //Usart0无线接收帧标识2
	ushort	XM_KL_Frame_Size;			   //Usart0无线接收帧包含网络包的长度
	uint	XM_KL_Frame_Checksum;		   //Usart0无线接收校验和
	uchar	XM_KL_Network_Ack;		   //Usart0无线接收网络应答
	uchar	XM_KL_Network_Flag_1;		   //Usart0无线接收网络标识1
	uchar	XM_KL_Network_Address_Struct;			   //网络地址结构
	uchar	XM_KL_Network_Address_Type; 		   //网络地址类型
	uchar	XM_KL_Network_Address_All;			   //网络地址个数
	uchar	XM_KL_Network_Address_Count;		   //Usart0无线接收网络地址个数
	uchar	XM_KL_Network_Flag_2;		   //Usart0无线接收网络标识2
	uchar	XM_KL_Network_Address_Len;		   //Usart0无线接收网络地址字节数
	uchar	*P_XM_KL_Network_Address_1; 		   //Usart0无线接收帧地址1
	uchar	*P_XM_KL_Network_Address_2; 		   //Usart0无线接收帧地址2
	uchar	*P_XM_KL_Network_Address_3; 		   //Usart0无线接收帧地址3
	uchar	*P_XM_KL_Network_Address_4; 		   //Usart0无线接收帧地址4
	uchar	*P_XM_KL_Network_Address_5; 		   //Usart0无线接收帧地址5
	uchar	XM_KL_Transfer_Ack; 	   //Usart0无线接收传输应答
	uchar	XM_KL_Transfer_Flag_1;		   //Usart0无线接收传输标识1
	uchar	XM_KL_Transfer_Encryption_Type; 		   //应用加密类型
	uchar	XM_KL_Transfer_Retry_Count; 		   //应用重传次数
	uchar	XM_KL_Transfer_Flag_2;		   //Usart0无线接收传输标识2
	uchar	XM_KL_Transfer_Encryption;		   //Usart0无线接收传输加密指针
	uchar	*P_XM_KL_Recv_Frame;		//USART0接收数组的指针	
	//接收状态控制
	uchar	XM_KL_Status;			   //帧分析进度
	uchar	XM_KL_Recv_Count;		   //当前状态有效字符数
	uchar	XM_KL_More_Flag;			   //存在第二标识
	uchar	*P_XM_KL_Crc;		// CRC开始
	uchar	*P_XM_KL_Link_Msg;		//消息头

	uchar oldValue;	
	uchar LenCount;
	uchar CrcCount;
	uchar CrcLen;
	short PacketLen;	
	uchar AddresCount;
	uint PacketAddressLen;
	uint MsgLen;
	uchar IsHaveHead;
	ushort xm_error;

}XM_PROTOCOL_STATUS;

struct frame_head{
	uchar head1;
	uchar head2;
};
struct frame_end{
	uchar end1;
	uchar end2;
};
struct frame_struct{
	uchar ack;
	uchar flag;
	uchar len;
};
struct frame_crc{
	uchar crc_high;
	uchar crc_low;
};
struct network_struct{
	uchar ack;
	uchar flag;
	uchar destination_module;
	uchar destination_no;
	uchar source_module;
	uchar source_no;	
};
struct transfer_struct{
	uchar ack;
	uchar flag;
};
struct message_struct{
	uchar type;
	uchar sub;
	uchar respon;
	uchar frame;
	uchar frameno;
	uchar data[255];	
	uchar source_module;
	uchar source_no;
	uchar destination_module;
	uchar destination_no;
	int error;
	int use_size;
	int data_size;
};

#pragma pack( )

typedef struct _xm_sync{
#if USE_SEM
	sem_t sem;
#else
	pthread_cond_t cond;
#endif
	pthread_mutex_t mutex;
	int value;
	int is_wait;
	time_t timeout;	//发送时的时间	
}XM_SYNC;
#define TP_DATA_IS_WAIT(psync) \
do \
{ \
	while(1) \
	{ \
		pthread_mutex_lock(&psync->mutex); \
		if(psync->is_wait) \
		{ \
			pthread_mutex_unlock(&psync->mutex); \
			break; \
		} \
		pthread_mutex_unlock(&psync->mutex); \
		sleep(1); \
	} \
}while(0)

typedef struct _xm_node{
	XM_SYNC sync;
#if XM_WITH_ID
	char xm_id[XM_ID_MAX];//解析出的设备ID
#endif
	char *atbuf;//AT 命令缓存
	int atlen;//AT 命令缓存的长度
	int xm_sendlen;//需要发送的字节数
	int index;//对应socket 在数组中的序号
	int id;//节点的序号
	uchar is_wait;//节点在等待状态
	uchar address;//设备地址
	uchar argc;//AT 命令的参数个数
	uchar errorid;	//错误代码
	uchar xm_set;//表示命令操作类型, 分别是设置，查询状态，查询功能
	uchar xm_sendready;//数据 准备好
	XM_AT xm_at;//AT 结构，保存AT 命令的内容和分析后的数据以及返回结果
	struct _at_fun *xm_cmd;//正在处理的命令结构指针
	struct _xm_node *end;//下一个节点
	
}XM_NODE;

typedef struct _xm_protocol{
	pthread_mutex_t mutex;
#if XM_WITH_ID
	char xm_id[XM_ID_MAX];
#endif
	XM_NODE *node;//发送节点指针，可以链表结构，目前只支持一个节点
	int xm_socket_client;//socket 句柄
	int xm_index;//数组中的序号
	time_t timeout;	//发送时的时间
	uchar xm_addres;//设备地址
	uchar xm_frame;//设备帧序号
	uchar xm_sub_frame;//设备帧子序号
	uchar	XM_Frame_Buffer[XM_MAX_BUF]; //帧数据
	uchar xm_addres_type;//地址类型,详见协议文档
	uchar xm_addres_count;//地址个数,详见协议文档
	uchar xm_addres_all;//是否是全部地址有效,详见协议文档
	uchar xm_addres_struct;//地址的组成方式,详见协议文档
	uchar xm_crc_type;//校验类型,详见协议文档
	uchar xm_encryption_type;//加密类型,详见协议文档
	uchar xm_exit;//退出标志	
	uchar xm_seting;//需要发送命令
	uchar XM_Status_Buffer[XM_MAX_BUF];//保存状态
	uchar XM_Setting_Buffer[XM_MAX_BUF];//保存设置内容
	uchar XM_Status_Value[XM_MAX_BUF];	//临时保存用
	char XM_At_Send[XM_MAX_BUF]; //保存发送的命令
	char XM_At_Recv[XM_MAX_BUF]; //保存接收的返回
	uchar	*xm_addres_1;//地址1 ,详见协议文档
	uchar	*xm_addres_2;//地址2 ,详见协议文档
	uchar	*xm_addres_3;//地址3 ,详见协议文档
	uchar	*xm_addres_4;//地址4 ,详见协议文档
	uchar	*xm_addres_5;//地址5 ,详见协议文档
	int	xm_waitsend;//表示是否需要等待发送
	uchar	xm_send;//表示是否需要发送
	uchar	xm_sendready;//数据准备好，等待发送
	uchar	xm_parse;//需要对返回结果进行分析
	uchar   sendcmd;//上次的命令字
	uchar   sendsub;//上次的子命令
	XM_PROTOCOL_STATUS xm_status;//返回值分析 的状态保存	
	char *getparam[MAX_CMD_PARAM_NUM];//AT 的参数指针
	int node_count; //一个socket的最大命令发送个数
	int resend_count;//重发的次数，目前重发3次
	int xm_sended;//表示已发送
	// ADD by Tao He
	uchar frame_flag; //表示是否有额外的两个字节的frame、和frame NO
}XM_PROTOCOL;

typedef struct _xm_server_map{
#if XM_WITH_ID
	char xm_id[XM_ID_MAX];
#endif
	int xm_socket_client;
	int xm_socket_module;
	int xm_module_id;
	int xm_socket_virtual;
	int client_ip_addr;
	int client_l4_port;
	int module_ip_addr;
	int module_l4_port;
	XM_PROTOCOL xm_protocl;
}XM_SERVER_MAP;

typedef struct _at_fun{
	char *cmd;// AT 的命令字
	uchar (*set)(XM_PROTOCOL *pxm,XM_NODE *pnode,uchar *pbuf,uchar argc,char **argv);//处理函数
	uchar type;	//命令类型, 0 表示 发设置，1 表示模块处理,  2 表示本地处理
	XM_Command *parameter;//命令参数
}XM_AT_FUN;

typedef struct _at_return{
	char *cmd;//AT
	uchar type;// 命令类型
	uchar major;// 主命令
	uchar minor;// 次命令
	XM_Command *parameter;//命令参数
}XM_AT_RET;

typedef struct _at_fun_lsit{
	int listnum;//命令节点数
	XM_AT_FUN *funlist; //命令链表
	uchar type;	//设备地址
	char * cmddesc;	//说明 
}XM_AT_LIST;

typedef struct _at_fun_ret_lsit{
	int listnum;//命令节点数
	XM_AT_RET *funlist; //命令链表
	uchar type;	//设备地址
	char * cmddesc;	//说明 
}XM_AT_RET_LIST;

void xm_wait_init(XM_SYNC * psync);
void xm_wait_sync(XM_SYNC * psync);
void xm_wait_lock(XM_SYNC * psync);
void xm_wait_signal(XM_SYNC * psync);
void xm_wait_broadcast(XM_SYNC * psync);
void xm_wait_unlock(XM_SYNC * psync);
#endif
