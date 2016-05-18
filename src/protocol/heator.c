
#include "vanword.h"

#define PowerOn 	0x01
#define PowerOff 	0x00

#define LIG_Y		0x01
#define LIG_N		0x00

#define SOFT		0x01
#define KITCHEN		0x02
#define SHOWER		0x03
#define SAVEPower	0x04
#define SMART		0x05
#define CUSTOM		0X06

static XM_Value if_power[]={
	{STR(PowerOn),PowerOn},
	{STR(PowerOff),PowerOff}
};
static XM_Value if_safe_lig[]={
	{STR(LIG_Y),LIG_Y},
	{STR(LIG_N),LIG_N}
};

static XM_Value sys_mode[]={
	{STR(SOFT),SOFT},
	{STR(KITCHEN),KITCHEN},
	{STR(SAVEPower),SAVEPower},
	{STR(SMART),SMART},
	{STR(CUSTOM),CUSTOM}
};

/* 说明: 1、如果P0中不含有效数据字段
 *       itme->num=0
 *       2、如果没有P0
 *		   &item=NULL
 */ 



/****** cmdCode 0x40 *******/
VANW_ITEM_T burn_water_stat={		//燃气热水器状态
	46,
	46,
	0,
	{
		{7,8, 2,if_power,0,1,0,0},	//开关机
		{15,8,2,if_safe_lig,0,1,0,0},	//安全灯
		{23,8,6,sys_mode,0,1,0,0},		//系统模式
		{31,8,0,NULL,0,1,0,0},			//注水功能
		{39,8,0,NULL,0,1,0,0},			//流水量
		
		{47,8,0,NULL,0,1,0,0},			//流水累加量高位
		{55,8,0,NULL,0,1,0,0},			//流水累加量低位
		
		{63,8,0,NULL,0,1,0,0},			//自定义功能
		{71,8,0,NULL,0,1,0,0},			// 自定义设置水温
		{79,8,0,NULL,0,1,0,0},			// 水流量比例
		{87,8,0,NULL,0,1,0,0},			//呼叫提示 推送
		{95,8,0,NULL,0,1,0,0},			//工作花洒
		{103,8,0,NULL,0,1,0,0},			//工作火焰
		{111,8,0,NULL,0,1,0,0},			//工作风机
		{119,8,0,NULL,0,1,0,0},			// 工作火力档
		{127,8,0,NULL,0,1,0,0},			//故障代码
		{135,8,0,NULL,0,1,0,0},			//智氧提示
		{143,8,0,NULL,0,1,0,0},			//CO超标
		{151,8,0,NULL,0,1,0,0},			//设置水温
		{159,8,0,NULL,0,1,0,0},			//进水温度
		{167,8,0,NULL,0,1,0,0},			//出水温度
		{175,8,0,NULL,0,1,0,0},			//当前流量
		
		{183,8,0,NULL,0,1,0,0},			//累加用水量高4位
		{191,8,0,NULL,0,1,0,0},			//累加用水量高3位
		{199,8,0,NULL,0,1,0,0},			//累加用水量高2位
		{207,8,0,NULL,0,1,0,0},			//累加用水量最低位

		{215,8,0,NULL,0,1,0,0},			//累加用气量高位
		{223,8,0,NULL,0,1,0,0},			//累加用气量低位
		
		{231,8,0,NULL,0,1,0,0},			//累加使用时间高4
		{239,8,0,NULL,0,1,0,0},			//累加使用时间高3
		{247,8,0,NULL,0,1,0,0},			//累加使用时间高2
		{255,8,0,NULL,0,1,0,0},			//累加使用时间高1

		{263,8,0,NULL,0,1,0,0},			// 累加开阀数高位
		{271,8,0,NULL,0,1,0,0},			// 累加开阀数低位

		{279,8,0,NULL,0,1,0,0},			//实时效能
		{287,8,0,NULL,0,1,0,0},			//预热功能
		{295,8,0,NULL,0,1,0,0},			//预热温度
		{303,8,0,NULL,0,1,0,0},			//预热1小时
		{311,8,0,NULL,0,1,0,0},			//预热1分钟
		{319,8,0,NULL,0,1,0,0},			//预热2小时
		{327,8,0,NULL,0,1,0,0},			//预热2分钟
		{335,8,0,NULL,0,1,0,0},			//防冻报警提示
		{343,8,0,NULL,0,1,0,0},			//水泵提示
		{351,8,0,NULL,0,1,0,0},			//回水温度
		{359,8,0,NULL,0,1,0,0},			//reserved
		{367,8,0,NULL,0,1,0,0} 		//reserved
	}
};

/****** cmdCode 0x20 *******/
VANW_ITEM_T elect_water_stat={		//电热水器状态
	18,
	18,
	0,
	{
		{7,8,2,if_power,0,1,0,0},	//开关机状态
		{15,8,0,NULL,0,1,0,0},	//系统运行状态，加热还是求加热
		{23,8,0,NULL,0,1,0,0},		//功能状态
		{31,8,0,NULL,0,1,0,0},		//预约状态
		{39,8,0,NULL,0,1,0,0},		//内胆水温
		{47,8,0,NULL,0,1,0,0},		//预约小时
		{55,8,0,NULL,0,1,0,0},		//预约分钟
		{63,8,0,NULL,0,1,0,0},		//设置水温
		{71,8,0,NULL,0,1,0,0},		//设置功率
		{79,8,0,NULL,0,1,0,0},		//剩余加热时间
		{87,8,0,NULL,0,1,0,0},		//热水量
		{95,8,0,NULL,0,1,0,0},		//警告代码
		
		{103,8,0,NULL,0,1,0,0},		//用电量高位
		{111,8,0,NULL,0,1,0,0},		//用电量低位
		
		{119,8,0,NULL,0,1,0,0},		//发热加热累计时间高位
		{127,8,0,NULL,0,1,0,0},		//发热加热时间低位
		
		{135,8,0,NULL,0,1,0,0},		//未加热时间高位
		{143,8,0,NULL,0,1,0,0}		//未加热时间低位

		// when setting below is the 
	//	{7,8,0,NULL,0,0,1,0}		//未加热时间低位
	}
};

/****** cmdCode 0x60 *******/
VANW_ITEM_T worm_stove={
	46,
	46,
	0,
	{
		{7,8, 2,if_power,0,1,0,0},	//开关机
		{15,8,2,if_safe_lig,0,1,0,0},	//安全灯
		{23,8,0,NULL,0,1,0,0},		//故障状态
		{31,8,0,NULL,0,1,0,0},		//季节状态
		{39,8,0,NULL,0,1,0,0},		//火焰状态
		{47,8,0,NULL,0,1,0,0},			//卫浴水流状态
		{55,8,0,NULL,0,1,0,0},			//供暖热传导模式
		{63,8,0,NULL,0,1,0,0},			//沐浴模式
		{71,8,0,NULL,0,1,0,0},			// 机器类型
		{79,8,0,NULL,0,1,0,0},			// 风机状态
		{87,8,0,NULL,0,1,0,0},			//水泵状态
		{95,8,0,NULL,0,1,0,0},			//三通阀状态
		{103,8,0,NULL,0,1,0,0},			//点火器状态
		{111,8,0,NULL,0,1,0,0},			//防冻状态0（停止）、1（机器正在运行防冻）
		{119,8,0,NULL,0,1,0,0},			// 防冻状态0（停止）、1（运行）
		{127,8,0,NULL,0,1,0,0},			//远程启动供暖状态
		{135,8,0,NULL,0,1,0,0},			//水压值
		{143,8,0,NULL,0,1,0,0},			//卫浴目标温度
		{151,8,0,NULL,0,1,0,0},			//卫浴实际温度
		{159,8,0,NULL,0,1,0,0},			//供暖目标温度
		{167,8,0,NULL,0,1,0,0},			//供暖实际温度
		{175,8,0,NULL,0,1,0,0},			//室外温度
		{183,8,0,NULL,0,1,0,0},			//供暖运行模式
		
		{191,8,0,NULL,0,1,0,0},			//累计用气量3
		{199,8,0,NULL,0,1,0,0},			// 2
		{207,8,0,NULL,0,1,0,0},			// 1
		{215,8,0,NULL,0,1,0,0},			//  0
		{223,8,0,NULL,0,1,0,0},			//  实时耗气量12字节
		
	 	{319,96,0,NULL,0,1,0,0},			// 主板序列号
	 #if 0
		{231,8,0,NULL,0,1,0,0},			// 主板序列号11
		{239,8,0,NULL,0,1,0,0},			// 10
		{247,8,0,NULL,0,1,0,0},			// 9
		{255,8,0,NULL,0,1,0,0},			// 8
		{263,8,0,NULL,0,1,0,0},			// 7
		{271,8,0,NULL,0,1,0,0},			// 6
		{279,8,0,NULL,0,1,0,0},			// 5
		{287,8,0,NULL,0,1,0,0},			// 4
		{295,8,0,NULL,0,1,0,0},			// 3
		{303,8,0,NULL,0,1,0,0},			// 2
		{311,8,0,NULL,0,1,0,0},			// 1
		{319,8,0,NULL,0,1,0,0},			//  0
	#endif	
		{327,8,0,NULL,0,1,0,0},			// FF
		{335,8,0,NULL,0,1,0,0},			// FF
		{343,8,0,NULL,0,1,0,0},			// FF
		{351,8,0,NULL,0,1,0,0},			// FF
		{359,8,0,NULL,0,1,0,0},			// FF
		{367,8,0,NULL,0,1,0,0} 			// FF
	}
};

/****** cmdCode 0x50 *******/
VANW_ITEM_T all_heartBeat={
	0,
	0,
	0,
	{
	}
};


//----------------Below is  electric water heator ---------------

/****** cmdCode 0xdd *******/
VANW_ITEM_T all_refresh={
	0,
	0,
	0,
	{
	}
};

/****** cmdCode 0x01 *******/
VANW_ITEM_T elect_water_kj={
	1,
	0,
	1,
	{
		{7,8,0,NULL,0,0,1,0}
	}

};

/****** cmdCode 0x02 *******/
VANW_ITEM_T elect_water_set={
	1,
	0,
	1,
	{
		{7,8,0,NULL,0,0,1,0}
	}

};

/****** cmdCode 0x03 *******/
VANW_ITEM_T elect_water_temp={
	1,
	0,
	1,
	{
		{7,8,0,NULL,0,0,1,0}
	}

};
/****** cmdCode 0x04 *******/
VANW_ITEM_T elect_water_pwerRating={   	// power rating setting ; unit KW 1 ~5
	1,
	0,
	1,
	{
		{7,8,0,NULL,0,0,1,0}
	}

};

/****** cmdCode 0x05 *******/
VANW_ITEM_T elect_water_appointment={
	4,
	0,
	4,
	{
		{7,8,0,NULL,0,0,1,0}, 	//	hour 	:0~23
		{15,8,0,NULL,0,0,1,0},	// minute	:0~59
		{23,8,0,NULL,0,0,1,0},	// temprature  :35~75
		{31,8,0,NULL,0,0,1,0}	// power rating:1~5
	}

};

/****** cmdCode 0x06 *******/
VANW_ITEM_T elect_water_cancelApoint={
	0,
	0,
	0,
	{
	}

};

//----------------Below is  burn water heator ---------------

/****** cmdCode 0x80 *******/
VANW_ITEM_T burn_water_kj={
	1,
	0,
	1,
	{
		{7,8,0,NULL,0,0,1,0}
	}

};

// safe light
/****** cmdCode 0x81 *******/
VANW_ITEM_T burn_water_light={
	1,
	0,
	1,
	{
		{7,8,0,NULL,0,0,1,0}
	}

};

/****** cmdCode 0x82 *******/
VANW_ITEM_T burn_water_set={
	1,
	0,
	1,
	{
		{7,8,0,NULL,0,0,1,0} //35~48  50,55,60,65
	}

};

/****** cmdCode 0x83 *******/
VANW_ITEM_T burn_water_addWater={
	1,
	0,
	1,
	{
		{7,8,0,NULL,0,0,1,0} //0~99
	}

};

/****** cmdCode 0x84 *******/
VANW_ITEM_T burn_water_callCmd={
	1,
	0,
	1,
	{
		{7,8,0,NULL,0,0,1,0} 
	}

};

/****** cmdCode 0x86 *******/
VANW_ITEM_T burn_water_mode={
	1,
	0,
	1,
	{
		{7,8,0,NULL,0,0,1,0} 
	}

};

/****** cmdCode 0x88 *******/
VANW_ITEM_T burn_water_preHeat={
	6,
	0,
	6,
	{
		{7,8,0,NULL,0,0,1,0}, // 0 ~4 preHeater mode
		{15,8,0,NULL,0,0,1,0}, // temprature
		{23,8,0,NULL,0,0,1,0}, // unit one hour setting
		{31,8,0,NULL,0,0,1,0}, // unit one minutes setting
		{39,8,0,NULL,0,0,1,0}, // unit two houres setting
		{47,8,0,NULL,0,0,1,0}  // unit two minutes setting
	}

};

/****** cmdCode 0x89 *******/
VANW_ITEM_T burn_water_profiles={
	3,
	0,
	3,
	{
		{7,8,0,NULL,0,0,1,0},  // 0 ~4 preHeater mode
		{15,8,0,NULL,0,0,1,0}, // temprature
		{23,8,0,NULL,0,0,1,0}  // unit one hour setting
	}

};

//----------------Below is  Warm Stove ---------------
/****** cmdCode 0xa0 *******/
VANW_ITEM_T warm_stove_kj={
	1,
	0,
	1,
	{
		{7,8,0,NULL,0,0,1,0},  // 1: powerOn 0:powerOff
	}

};

// safe light
/****** cmdCode 0xa1 *******/
VANW_ITEM_T warm_stove_light={
	1,
	0,
	1,
	{
		{7,8,0,NULL,0,0,1,0}
	}

};

/****** cmdCode 0xa2 *******/
VANW_ITEM_T warm_stove_showerTemp={
	1,
	0,
	1,
	{
		{7,8,0,NULL,0,0,1,0}
	}
};

/****** cmdCode 0xa3 *******/
VANW_ITEM_T warm_stove_warmtTemp={
	1,
	0,
	1,
	{
		{7,8,0,NULL,0,0,1,0}	//30 ~80
	}
};

/****** cmdCode 0xa4 *******/
VANW_ITEM_T warm_stove_reset={
	1,
	0,
	1,
	{
		{7,8,0,NULL,0,0,1,0}	//0xff
	}
};

/****** cmdCode 0xa5 *******/
VANW_ITEM_T warm_stove_warmMode={
	1,
	0,
	1,
	{
		{7,8,0,NULL,0,0,1,0}	//0xa0 a1 a2
	}
};

/****** cmdCode 0xa6 *******/
VANW_ITEM_T warm_stove_showerMode={
	1,
	0,
	1,
	{
		{7,8,0,NULL,0,0,1,0}	//0 1
	}
};

/****** cmdCode 0xa7 *******/
VANW_ITEM_T warm_stove_seasonMode={
	1,
	0,
	1,
	{
		{7,8,0,NULL,0,0,1,0}	//0 1
	}
};

/****** cmdCode 0xa8 *******/
VANW_ITEM_T warm_stove_remoteWarmMode={
	1,
	0,
	1,
	{
		{7,8,0,NULL,0,0,1,0}	//0xa0 a1 a2
	}
};





/*关于状态的数组*/

VANW_AT_T ret_commProduce[1]={
	{"VWGETPROID", XM_SEND_SETTING, COMM_PRODUCT,0xFF,{0x03,0x07},NULL}
};

VANW_AT_T ret_clectWaterHeator[2]={
	{"VWEWZT", XM_SEND_QUERY, ELECT_HEATOR,0x20,{0x03,0x05}, &elect_water_stat},
	{"VWEWHHB",XM_SEND_QUERY, ELECT_HEATOR,0x50,{0x03,0x05},&all_heartBeat}
};

VANW_AT_T ret_burnWaterHeator[2]={
	{"VWBWHZT", XM_SEND_QUERY, BURN_HEATOR,0x40,{0x03,0x05},&burn_water_stat},
	{"VWBWHHB", XM_SEND_QUERY, BURN_HEATOR,0x50,{0x03,0x05},&all_heartBeat}
};

VANW_AT_T ret_warmStoveHeator[2]={
	{"VWWSZT", XM_SEND_QUERY,WARM_STOVE,0x60,{0x03,0x05},&worm_stove},
	{"VWWSHB", XM_SEND_QUERY,WARM_STOVE,0x50,{0x03,0x05},&all_heartBeat}
};


/*关于控制的数组*/


VAN_CMD_T cmd_commProduce[1]={
	{"VWGETPROID", XM_SEND_SETTING, COMM_PRODUCT,0xFF,{0x03,0x06},NULL}
};



/* electric water heator  */
VAN_CMD_T cmd_clectWaterHeator[7]={
	{"VWEWZT", XM_SEND_SETTING, ELECT_HEATOR,0xDD,{0x03,0x01}, &all_refresh},

	{"VWEWKJ",XM_SEND_SETTING,ELECT_HEATOR,0x01,{0x03,0x01},&elect_water_kj},
	{"VWEWSETMD",XM_SEND_SETTING,ELECT_HEATOR,0x02,{0x03,0x01},&elect_water_set},
	{"VWEWTEMP",XM_SEND_SETTING,ELECT_HEATOR,0x03,{0x03,0x01},&elect_water_temp},
	{"VWEWPRT",XM_SEND_SETTING,ELECT_HEATOR,0x04,{0x03,0x01},&elect_water_pwerRating},
	{"VWEWAPNT",XM_SEND_SETTING,ELECT_HEATOR,0x05,{0x03,0x01},&elect_water_appointment},
	{"VWEWCAPNT",XM_SEND_SETTING,ELECT_HEATOR,0x06,{0x03,0x01},&elect_water_cancelApoint}
	
};

/* burn water heator  */
VAN_CMD_T cmd_burnWaterHeator[9]={
	{"VWBWHZT", XM_SEND_SETTING,BURN_HEATOR,0xDD,{0x03,0x01},&all_refresh},
		
	{"VWBWKJ",XM_SEND_SETTING,BURN_HEATOR,0x80,{0x03,0x01},&burn_water_kj},
	{"VWBWLIG",XM_SEND_SETTING,BURN_HEATOR,0x81,{0x03,0x01},&burn_water_light},
	{"VWBWTSET",XM_SEND_SETTING,BURN_HEATOR,0x82,{0x03,0x01},&burn_water_set},
	{"VWBWAW",XM_SEND_SETTING,BURN_HEATOR,0x83,{0x03,0x01},&burn_water_addWater},
	{"VWBWCCMD",XM_SEND_SETTING,BURN_HEATOR,0x84,{0x03,0x01},&burn_water_callCmd},
	{"VWBWMODE",XM_SEND_SETTING,BURN_HEATOR,0x86,{0x03,0x01},&burn_water_mode},
	{"VWBWPREH",XM_SEND_SETTING,BURN_HEATOR,0x88,{0x03,0x01},&burn_water_preHeat},
	{"VWBWPROF",XM_SEND_SETTING,BURN_HEATOR,0x89,{0x03,0x01},&burn_water_profiles}
};

/* worm stove heator  */
VAN_CMD_T cmd_warmStoveHeator[10]={
	{"VWWSZT", XM_SEND_SETTING, WARM_STOVE,0xDD,{0x03,0x01},&all_refresh},

	{"VWWSKJ", XM_SEND_SETTING, WARM_STOVE,0xA0,{0x03,0x01},&warm_stove_kj},
	{"VWWSLIG", XM_SEND_SETTING, WARM_STOVE,0xA1,{0x03,0x01},&warm_stove_light},
	{"VWWSSHWRTMP", XM_SEND_SETTING, WARM_STOVE,0xA2,{0x03,0x01},&warm_stove_showerTemp},
	{"VWWSWRMTEMP", XM_SEND_SETTING, WARM_STOVE,0xA3,{0x03,0x01},&warm_stove_warmtTemp},
	{"VWWSRST", XM_SEND_SETTING, WARM_STOVE,0xA4,{0x03,0x01},&warm_stove_reset},
	{"VWWSWRMMD", XM_SEND_SETTING, WARM_STOVE,0xA5,{0x03,0x01},&warm_stove_warmMode},
	{"VWWSSWRMD", XM_SEND_SETTING, WARM_STOVE,0xA6,{0x03,0x01},&warm_stove_showerMode},
	{"VWWSSNMD", XM_SEND_SETTING, WARM_STOVE,0xA7,{0x03,0x01},&warm_stove_seasonMode},
	{"VWWSRMTMD", XM_SEND_SETTING, WARM_STOVE,0xA8,{0x03,0x01},&warm_stove_remoteWarmMode},
};


