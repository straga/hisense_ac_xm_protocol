#include	"xm_type.h"
/* 自动窗帘协议 0x55*/

XM_Command CurtainQuery={//查询
	1,
	5,
	3,
	0,
	0,
	101,
	0,
	102,
	0,
	0,
	0,
	{
		{7,1,0,NULL,0,1,0,0},
	},
	{
		{1,1,0,NULL,0,1,0,0},	//Open or Close state 参数是否有效
		{0,1,0,NULL,0,1,0,0},	//Open or Close state
		{7,1,0,NULL,0,1,0,0},	// 定点位置参数是否有效
		{6,5,0,NULL,0,1,0,0},	// 当前的定点位置(0~16)
		{23,1,0,NULL,0,1,0,0},
	}
};


XM_Command xm_CurtainMode={//Mode
	2,
	0,
	3,
	0,
	0,
	101,
	0,
	102,
	0,
	0,
	0,
	{
		{2,3,0,NULL,0,0,1,0},
		{7,1,0,NULL,0,0,1,1},
	},
	{
	}
};

XM_Command xm_CurtainPos={//Mode
	3,
	0,
	3,
	0,
	0,
	101,
	0,
	0,
	0,
	0,
	0,
	{
		{2,3,0,NULL,0,0,1,3},
		{7,1,0,NULL,0,0,1,1},
		{15,5,0,NULL,0,0,1,0},
	},
	{
	}
};



XM_AT_FUN at_cmd_curtain[3]={
	{"CurtainSetMode",NULL,0,&xm_CurtainMode},//换气速度
	{"CurtainSetPos",NULL,0,&xm_CurtainPos},//换气速度
	{"CurtainQuery",NULL,0,&CurtainQuery},//开机控制
};


XM_AT_RET at_cmd_ret_curtain[2]={
	{"CurtainQuery",XM_SEND_QUERY,102,0,&CurtainQuery},
	{"CurtainSet",XM_SEND_SETTING,101,0,NULL}		
};




