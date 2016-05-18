#include	"xm_type.h"
/* 电量计0x11*/

XM_Command VolSet={//Mode
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
		{4,1,0,NULL,0,0,1,0},	// 电量统计清0
		{5,1,0,NULL,0,0,1,1},	
		{6,1,0,NULL,0,0,1,0},	// 总的电源开关
		{7,1,0,NULL,0,0,1,1},
	},
	{
	},
};




XM_Command VolQuery={//Mode
	1,
	18,
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

		{7,1,0,NULL,0,1,0,0},//总电源开关状态0
		
		{39,8,0,NULL,0,1,0,0}, // Current [31:24]  1
		{47,8,0,NULL,0,1,0,0},//Current[23:16]  2
		{55,8,0,NULL,0,1,0,0}, //Current[15:8]  3
		{63,8,0,NULL,0,1,0,0}, //Current[7:0]  4

		{71,8,0,NULL,0,1,0,0},//Volatage [31:24]  5
		{79,8,0,NULL,0,1,0,0},//Volatage [23:16] 6
		{87,8,0,NULL,0,1,0,0},//Volatage [15:8]  7
		{95,8,0,NULL,0,1,0,0},//Volatage [7:0]  8

		{103,8,0,NULL,0,1,0,0}, //Voltameter[63:56] 9 
		{111,8,0,NULL,0,1,0,0},//Voltameter[55:48] 10
		{119,8,0,NULL,0,1,0,0},//Voltameter[47:40] 11 
		{127,8,0,NULL,0,1,0,0},//Voltameter[39:32] 12 
		{135,8,0,NULL,0,1,0,0},//Voltameter[31:24] 13 
		{143,8,0,NULL,0,1,0,0},//Voltameter[23:16] 14 
		{151,8,0,NULL,0,1,0,0},//Voltameter[15:8] 15 
		{159,8,0,NULL,0,1,0,0},//Voltameter[7:0] 16

		{23,1,0,NULL,0,1,0,0},	//  Peripherals communication error  17
	},
};



XM_AT_FUN at_cmd_volta[2]={
	{"VolSet",NULL,0,&VolSet},// 
	{"VolQuery",NULL,0,&VolQuery},// 
};


XM_AT_RET at_cmd_ret_volta[2]={
	{"VolQuery",XM_SEND_QUERY,102,0,&VolQuery},
	{"VolSet",XM_SEND_SETTING,101,0,NULL}		
};




