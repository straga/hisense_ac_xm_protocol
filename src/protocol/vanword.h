#ifndef __XLF__VANWORD_H
#define __XLF__VANWORD_H

#include "xm_type.h"
#include "xmlog.h"
#include <arpa/inet.h>

#define VANW_DEBUG 1
#if VANW_DEBUG

#ifndef ANDROID
#define xlf_debug(fmt,args...) printf("%s >> %d: "fmt,__func__,__LINE__,##args)
#else
#define xlf_debug(fmt,args...) __android_log_print(ANDROID_LOG_DEBUG, TAG, fmt, ##args)
#endif

#else
#define xlf_debug(fmt,args...)
#endif

// error code
#define XM_ERROR_0307		35



#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))
#define STR(s) #s
#define STR_MAP_VAL(n) ({STR(n),n})
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
// 支持的设备类型
#define BURN_HEATOR 		0x01
#define ELECT_HEATOR 		0x02
#define WARM_STOVE			0x03
#define COMM_PRODUCT		0XFF

// 1 字节对齐
//
#define	PACKET_MAX_LEN	255
#define	PACKET_MIN_LEN	6
#define	FRAME_ERROR_CTRLID	0x03
#pragma pack(push,1)

struct ctl_id{
	u8 dataH;
	u8 dataL;
};
typedef struct _p0{
	u8 p0_data[256];//待解析的BODY
	u32 error;		//解析的结果
	struct ctl_id id;	//通讯控制命令ID
	u16 len;		// body的长度
	u8	headDataLen;
}p0_t;

typedef struct _head{
	u8 *bodyHex;
	u8 len;
	u32 conNUM;
	struct ctl_id id;
}build_info_t;



#if 0
/*每一个有用信息的描述*/
typedef struct VANW_Offset{
	u16 offset;//偏移
	u16 takeLen;//长度
//	u8 	valType;	//如果超过8位的，判断其类型由上面的类型定义
	uchar textlen;//映射表长度
	XM_Value *text;//映射表
	u8  support;//在功能查询时有效
	u8  query;//在状态查询 时有效
	u8  set;//在设置 时有效
	u8 preset;//预设值,在设置 时自动生效
}VANW_OFFSET_T;
#endif
/*对每个AT指令所能接受的参数进行描述*/
typedef struct vanw_item{
	u16  num;// 总参数个数 	
	u8 queryNum;	//状态返回时的个数
	u8 setNum;		//设置的个数
	XM_Offset cmdArry[MAX_CMD_PARAM_NUM];//参数组
}VANW_ITEM_T;

/*这个结构对每个AT指令的描述，这里的device_type其实可以省略，但协议上也没有指明不同的产品不会出现相同的命令码
 *所以我用两个合起来判断是不是这个AT指令
*/
typedef struct vanw_at_info{
	char *at;	//AT指令头
	u8 type;	//命令类型, 0 表示 发设置，1 表示模块处理,  2 表示本地处理
	u8 device_type;	//表示是哪一种产品，比如01是燃热，02是电热
	u8 cmdCode;
	struct ctl_id id;	//建立好控制ID的映射
	VANW_ITEM_T *item;
}VANW_AT_T;

/*这个结构体表示万和某一种产品的描述*/
typedef struct vanw_produce{
	int atNum;			//这个产品支持的AT指令的条数也是atList元素的个数
	VANW_AT_T *atList;	//At指令的列表
	u8 device_type;			//表示是哪一种产品, 热水器还是燃气灶等
	char *produceName;	//产品的名字，也相当于XM_AT_RET_LIST 的说明
}VANW_PRO_T;

typedef struct vanw_cmd_info{
	char *at;	//AT指令头
	u8 type;	//命令类型, 0 表示 发设置，1 表示模块处理,  2 表示本地处理
	u8 device_type;	//表示是哪一种产品，比如01是燃热，02是电热
	u8 cmdCode;
	struct ctl_id id;	//建立好控制ID的映射
//	u32 conNUM;			//控制连接数，这个在at传递下来的时候，要一一匹配的
	VANW_ITEM_T *item;

}VAN_CMD_T;

typedef struct vanw_produce_cmd{
	int atNum;
	VAN_CMD_T *cmdList;
	u8 device_type;
	char *produceName;
}VANW_PRO_CMD_T;



typedef struct head_p0{
	struct frame_head p0_head;
	u8 device_type;
	u8 answerAddr;
	u8 cmdCode;
}HEAD_P0_T;

typedef struct at_cmd{
	int error;
	VAN_CMD_T *xm_cmd;
	char xm_id[XM_ID_MAX];//解析出的设备ID
	u8 argc;
	u8 xm_set;		//表示命令操作类型, 分别是设置，查询状态，查询功能
	u8 xm_sendlen;
	XM_AT xm_at;

}AT_CMD_T;





#pragma pack(pop)
extern void printf_buf(char * text,unsigned char *pbuf,int len);
extern int BIN2HEX(char *	p_binstr, int bin_len, char * p_hexstr);
extern int HEX2BIN(char *	p_hexstr, char * p_binstr);
extern void xlf_crc(uchar *pbuf,uchar len,struct frame_crc *crc_buf);
int xlf_vanword_build(char *sendbuf ,char *buf,int conNum,u8 ctl_id_index,u8 device_type);
int xlf_vanword_pasre(char * retbuf,char *hexstr,u8 device_type);


#endif



