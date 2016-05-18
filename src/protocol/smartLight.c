#include	"xm_type.h"

XM_Command lightPwr={//开关
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
		{6,1,0,NULL,0,0,1,0},	// 开关
		{7,1,0,NULL,0,0,1,1},	
	},
	{
	},
};

XM_Command lightLevel={//空气等级
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
		{23,8,0,NULL,0,0,1,0},	// 空气等级
		{15,1,0,NULL,0,0,1,1},	
	},
	{
	},
};

XM_Command lightColorTemp={//设置色瘟
	3,
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
		{14,1,0,NULL,0,0,1,1},	
		{31,8,0,NULL,0,0,1,0},	//色温高
		{39,8,0,NULL,0,0,1,0},	//色温低
	},
	{
	},
};



XM_Command lightBright={//亮度
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
		{4,3,0,NULL,0,0,1,0},	
		{5,1,0,NULL,0,0,1,1},	
	},
	{
	},
};

XM_Command lightRGB={//亮度
	4,
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
		{13,1,0,NULL,0,0,1,1}, //SetFlag
		{47,8,0,NULL,0,0,1,0},	// R
		{55,8,0,NULL,0,0,1,0},	// G
		{63,8,0,NULL,0,0,1,0},	// B
	},
	{
	},
};

XM_Command lightDevStat={// 设备状态
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
		{71,1,0,NULL,0,0,1,1}, //SetFlag
		{70,7,0,NULL,0,0,1,0},	// 状态
	},
	{
	},
};



XM_Command Query_light={//Mode
	1,
	15,
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
		{7,1,0,NULL,0,1,0,0},
	},
	{
		{7,1,0,NULL,0,1,0,0}, //开关状态 0
		{4,1,0,NULL,0,1,0,0}, //RGB 值是否有效 1
		{15,8,0,NULL,0,1,0,0}, //红色  2
		{23,8,0,NULL,0,1,0,0}, //绿色  3
		{31,8,0,NULL,0,1,0,0}, //蓝色  4
		
		{5,1,0,NULL,0,1,0,0}, //色温值是否有效5
		{39,8,0,NULL,0,1,0,0}, // 色温值高6
		{47,8,0,NULL,0,1,0,0}, // 色温值低7
		
		{6,1,0,NULL,0,1,0,0}, // brightness vailed 8
		{55,8,0,NULL,0,1,0,0}, // brightness  9

		{71,1,0,NULL,0,1,0,0}, //设备状态值是否有效10
		{70,7,0,NULL,0,1,0,0}, //设备状态, 0 为正常，1 为掉线 11	

		{59,1,0,NULL,0,1,0,0}, //空气状况是否有效 12 
		{58,3,0,NULL,0,1,0,0}, //空气状况,3 优、2 良、1 一般13 
		
		{87,1,0,NULL,0,1,0,0}, //	Peripherals communication error  14
	},
};




XM_AT_FUN at_cmd_smartLight[7]={
	{"SetLightPwr",NULL,0,&lightPwr},// 开关
	{"SetAirLevel",NULL,0,&lightLevel},//质量等级
	{"SetBright",NULL,0,&lightBright},//亮度
	{"SetColorTemp",NULL,0,&lightColorTemp},//设置色温
	{"SetLightRGB",NULL,0,&lightRGB},//设置RGB
	{"SetDevStat",NULL,0,&lightDevStat},//设置设置状态
	{"lightQuery",NULL,0,&Query_light},// 
};



XM_AT_RET at_cmd_ret_smartLight[2]={
	{"LightQuery",XM_SEND_QUERY,102,0,&Query_light},
	{"LightSet",XM_SEND_SETTING,101,0,NULL}		
};





