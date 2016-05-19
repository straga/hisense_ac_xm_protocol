/*
 * 数据结构中把指针尽量放在前面
 */

#ifndef XLF_JS_TYPE__H
#define XLF_JS_TYPE__H
#include "cJSON.h"
#ifdef __cplusplus
extern "C" {
#endif

#define T_HEX	0
#define T_STR	1
#define T_BCD 	2


#pragma pack(push,1)

/*
 * 字符串到数值的映射
 */
#define END_KEY_VAL {NULL,0}
typedef struct key_val{
	char * key;
	u8 val;
}key_val_t;


/*
 * 每个底层协议元素对应的结构
 * @text 以key==NULL表示结束
 */
#define END_POS {NULL,0,0,0,0}
typedef struct pos{
	key_val_t *text; //映射表
	u16 offset;		//开始地址
	u16	takeLen;	// 占用长度
	u8	type_value;	// 0,HEX,BCD 255,其他为字符串
	u8 preset;		// 不为0，则填预设值（如果要预设0，则初始化时已经完成）
}pos_t;

/*
 * 每个JSON命令对应的结构
 * @extra_para 如果存在，则以 start 为0表示结束
 */
#define END_CMD_MAP {NULL,NULL,END_POS,END_POS}
typedef struct cmd_map{
	char *cmd;
	pos_t *set_extral;	//4
//	pos_t autoManual;
	pos_t set;	
	pos_t flag;	
}cmd_map_t;

/*
 * 每个JSON包对应的结构
 * 一个cmd 应该对应了一个具体的协议，
 * 所以cmd_type 和subtype是一一对应的
 * 同时，设置的参数个数也是定的，链路层标识也是定的
 * @appHeadLenFlag 0，表示3字节，1，表示5字节
 * @cmd_map 以cmd==NULL 表示结束
*/
#define END_PRO_CMD {NULL,NULL,0,0,0,0,0,0}
typedef struct pro_cmd{
	char *opt_cmd;	//对应于AT + "XXX" 内容
	cmd_map_t *cmd_map;	
	u8 cmd_type;
	u8 cmd_subtype;
	u8 set_num;		//要设置的参数个数
	u8 ret_num;		//保留,返回参数个数
	u8 link_flag;	//链路层标识
	u8 appHeadLenFlag;	//应用层首部长度标识
}pro_cmd_t;

/*
 * 表示哪一种产品
 * @type 设备类型
 * 
 * @cmdList 协议列表 以opt_cmd为NULL表示表的结束
 */
 #define END_PRO {NULL,NULL,0}
typedef struct pro{
	char *proName;
	pro_cmd_t *cmdList;
	u8 deviceType;
}pro_t;

#pragma pack(pop)


/*
 * 以下是提供的接口
 *
 */





#ifdef __cplusplus
}
#endif
#endif //JS_TYPE.H


