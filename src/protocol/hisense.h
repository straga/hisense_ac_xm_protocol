/*********************KDA-1131-V01.h***********************
author:		ChenJianbo
edit date:	2012.11.26

**********************************************************/
#ifndef _Included_Hisense
#define _Included_Hisense

//**********************通信帧特殊字定义***************************
#define BAG_HEAD1	0xf4
#define BAG_HEAD2	0xf5
#define	Extension_Byte	0xf4		//数据中F4的扩展字节	
#define BAG_END1	0xf4
#define BAG_END2	0xfb
#define XM_ACK_FAIL 0
#define XM_ACK_SUCC 1
#define XM_ACK_NOT_SUPPORT 8
#define XM_FLAG_TWO 1
#define XM_FLAG_ADD 0
#define XM_FLAG_SHORTADD 1
#define XM_FLAG_SHORTCRC 2
#define XM_FLAG_CRC 3

#define XM_ACK_CEHCK(x)  (x!=XM_ACK_SUCC)
/*
初始化socket 结构中协议解析变量,目前指定 校验码为两字节
参数:
pxm:socket 数据指针
返回:
无
*/
void statusInit(XM_PROTOCOL * pxm);
/*
分析命令执行结果，正确时调 用build_at_ret
参数:
pxm:socket 数据指针
pMsgHead:消息头指针,因为命令数据是跟在命令头后面，是连续的，可以直接转取内容
len:数据长度
返回:
错误码
*/
uchar Proc_msg(XM_PROTOCOL *pxm,MessageHead * pMsgHead,uchar len);

/*
配置类命令不需要分析，直接拷贝接收到的内容
参数:
pxm:socket 数据指针
pMsgHead:消息头指针,因为命令数据是跟在命令头后面，是连续的，可以直接转取内容
len:数据长度
返回:
错误码
*/
uchar Proc_recv(XM_PROTOCOL *pxm,MessageHead * pMsgHead,uchar len);
/*
对接收的内容进行分析，以字节进行，数据缓存在XM_Frame_Buffer
参数:
pxm:socket 数据指针
cstr:字节
msg:结果处理函数
返回:
错误码,其中XM_ERROR_WAIT_MOER 表示需要更多数据
*/
uchar Parse_Read (XM_PROTOCOL *pxm,uchar *cstr,uchar (*msg)(XM_PROTOCOL *pxm,MessageHead * pMsgHead,uchar len));

/*
生成报文
参数:
pData:保存报文的指针
pbuf:命令和内容
MsgLen:命令和内容的长度
....其它为报文参数
返回:
报文长度
*/
uchar Parse_Send (uchar *pData,uchar *pbuf,uchar MsgLen,uchar * Address1,uchar * Address2,uchar * Address3,uchar * Address4,uchar * Address5,uchar Address_Count,uchar Address_All,uchar Address_Type,uchar Address_Struct,uchar EncryptionType,uchar CrcType,uchar nret,uchar Transfer_flag2,uchar Network_flag2,uchar Frame_flag2,uchar Encryption,uchar Retry);
//------------------------end------------------------------
#endif
