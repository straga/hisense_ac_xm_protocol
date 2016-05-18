#include "xm_type.h"
#include "xmlog.h"

#include <ctype.h>


XM_Command dcWorkMode={
	16,
	0,
	16,
	0,
	0,
	101,
	0,
	102,
	0,
	0,
	0,
	{
		{3,4,0,NULL,0,0,1,0},	
		{7,4,0,NULL,0,0,1,1} //  set this time
	},
	{
	}
};

XM_Command dcHeatMode={
	16,
	0,
	16,
	0,
	0,
	101,
	0,
	102,
	0,
	0,
	0,
	{

		{15,8,0,NULL,0,0,1,1},  // SET MODE
		{23,8,0,NULL,0,0,1,0},
		{39,8,0,NULL,0,0,1,0},	//temperature
		
		{47,8,0,NULL,0,0,1,0},	// volume Hight Byte
		{55,8,0,NULL,0,0,1,0},	//volume low byte
	},
	{
	}
};

XM_Command dcSet={
	16,
	0,
	16,
	0,
	0,
	101,
	0,
	102,
	0,
	0,
	0,

	{
		{27,4,0,NULL,0,0,1,0},	// set open or close
		{31,4,0,NULL,0,0,1,1},	// set this time
		{39,8,0,NULL,0,0,1,0},	//temperature
		
		{47,8,0,NULL,0,0,1,0},	// volume Hight Byte
		{55,8,0,NULL,0,0,1,0},	//volume low byte
	},
	{
	}
};

XM_Command dcChildLock={
	16,
	0,
	16,
	0,
	0,
	101,
	0,
	102,
	0,
	0,
	0,

	{
		{59,4,0,NULL,0,0,1,0},	//lock or unlock
		{63,4,0,NULL,0,0,1,1},  //child lock  set
		{71,8,0,NULL,0,0,1,0},	//lock protect temp
	},
	{
	}
};
XM_Command dcStat={
	1,
	22,
	1,
	20,
	0,
	101,
	0,
	102,
	0,
	0,
	0,
	{
		{7,8,0,NULL,0,1,0,0}, //auto or manual
	},
	{
		{ 7,8,0,NULL,0,1,0,0},	// work mode
		{15,8,0,NULL,0,1,0,0},	// heat mode	
		{23,8,0,NULL,0,1,0,0},	// current tempuratur
		
		{31,8,0,NULL,0,1,0,0},	// water out high
		{39,8,0,NULL,0,1,0,0},	// water out low
		
		{47,8,0,NULL,0,1,0,0},	// water left 31:24
		{55,8,0,NULL,0,1,0,0},	// water left 23:16	
		{63,8,0,NULL,0,1,0,0},	// water left 15:8
		{71,8,0,NULL,0,1,0,0},	// water left 7:1
//		{79....}
		{79,1,0,NULL,0,1,0,0},	// heating unit exception	9
		{80,1,0,NULL,0,1,0,0},	// pump tempurature senser exception 	10
		{81,1,0,NULL,0,1,0,0},	// water in ,tempurature senser exception 11
		{82,1,0,NULL,0,1,0,0},	// child lock flag	12
		{83,1,0,NULL,0,1,0,0},	//lack water flag	13
		{84,1,0,NULL,0,1,0,0},	// power senser exception	14
		{85,1,0,NULL,0,1,0,0},	// pump senser exception	15	
		{86,1,0,NULL,0,1,0,0},	// water in		16
		{87,1,0,NULL,0,1,0,0},	// pulling			17
		
		{95,8,0,NULL,0,1,0,0},	//voltage high
		{103,8,0,NULL,0,1,0,0},	//voltage low
		{111,8,0,NULL,0,1,0,0},	//TDS ∏ﬂ
		{119,8,0,NULL,0,1,0,0}	// TDS µÕ
	}
		
};



XM_AT_FUN at_cmd_DC[5]={
	{"DCSTAT",NULL,0,&dcStat},
	{"DCWORKMODE",NULL,0,&dcWorkMode},//…Ë÷√
	{"DCHEATMODE",NULL,0,&dcHeatMode},
	{"DCSET",NULL,0,&dcSet},
	{"DCCLOCK",NULL,0,&dcChildLock}
};

XM_AT_RET at_cmd_ret_DC[2]={
	{"DCSTAT",XM_SEND_QUERY,102,0,&dcStat},
	{"DCSET",XM_SEND_SETTING,101,0,NULL},
};

