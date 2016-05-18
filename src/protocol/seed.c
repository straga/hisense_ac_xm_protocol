/*
 * Copyright 2009-2011 Cedric Priscal
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include	"xmlog.h"
#include	"xm_type.h"
#include	"message.h"
#include	"hisense.h"
#include	"cmdanalysis.h"

#define XM_SEED_SET_LEN 14
#define XM_SEED_STATUS_LEN 26

static XM_Command powerSet={
	2,
	0,
	XM_SEED_SET_LEN,
	0,
	0,
	101,
	0,
	101,
	0,
	0,
	0,
	{
		{6,7,0,NULL,0,0,1,0},	//开关机
		{7,1,0,NULL,0,0,1,1},	//lock or unlock
	},
	{
	}
};

static XM_Command musicSet={//音乐
	2,
	0,
	XM_SEED_SET_LEN,
	0,
	0,
	101,
	0,
	101,
	0,
	0,
	0,
	{
		{14,7,0,NULL,0,0,1,0},	
		{15,1,0,NULL,0,0,1,1},	
	},
	{
	}
};

static XM_Command SetVolume={//音乐
	2,
	0,
	XM_SEED_SET_LEN,
	0,
	0,
	101,
	0,
	101,
	0,
	0,
	0,
	{
		{12,1,0,NULL,0,0,1,0},	
		{13,1,0,NULL,0,0,1,1},	
	},
	{
	}
};

static XM_Command lightSet={//照明
	2,
	0,
	XM_SEED_SET_LEN,
	0,
	0,
	101,
	0,
	101,
	0,
	0,
	0,
	{
		{21,6,0,NULL,0,0,1,0},	
		{23,1,0,NULL,0,0,1,1},	
	},
	{
	}
};

static XM_Command anionSet={//负离子
	2,
	0,
	XM_SEED_SET_LEN,
	0,
	0,
	101,
	0,
	101,
	0,
	0,
	0,
	{
		{30,7,0,NULL,0,0,1,0},	
		{31,1,0,NULL,0,0,1,1},	
	},
	{
	}
};

static XM_Command lightTimer={//灯定时
	10,
	0,
	XM_SEED_SET_LEN,
	0,
	0,
	101,
	0,
	101,
	0,
	0,
	0,
	{
		{54,7,0,NULL,0,0,1,0},	//当前时间小时
		{63,8,0,NULL,0,0,1,0},	//当前时间分钟
		{55,1,0,NULL,0,0,1,1},	

		{70,1,0,NULL,0,0,1,0},	// 1定时
		{71,1,0,NULL,0,0,1,1},	

		{38,1,0,NULL,0,0,1,0},	//0表示是关灯设置，1表示开灯设定
		{37,6,0,NULL,0,0,1,0},	//定时小时
		{47,8,0,NULL,0,0,1,0},	//定时分钟
		{39,1,0,NULL,0,0,1,1},	
		{69,6,0,NULL,0,0,1,0},	//同时指定开哪几层灯
	},
	{
	}
};


static XM_Command pm25Set={//pm2.5设定
	2,
	0,
	XM_SEED_SET_LEN,
	0,
	0,
	101,
	0,
	101,
	0,
	0,
	0,
	{
		{78,7,0,NULL,0,0,1,0},	
		{79,1,0,NULL,0,0,1,1},	
	},
	{
	}
};

static XM_Command warningClose={//报警解除
	3,
	0,
	XM_SEED_SET_LEN,
	0,
	0,
	101,
	0,
	101,
	0,
	0,
	0,
	{
		{85,1,0,NULL,0,0,1,0},	//关水位报警
		{86,1,0,NULL,0,0,1,0},	// 关水泵报警
		{87,1,0,NULL,0,0,1,0},	// 关营养液报警
	},
	{
	}
};



XM_Command seedStat={
	1,
	25,
	1,
	XM_SEED_STATUS_LEN,
	0,
	102,
	0,
	102,
	0,
	0,
	0,
	{
		{7,8,0,NULL,0,1,0,0}, //auto or manual
	},
	{
		{ 0,1,0,NULL,0,1,0,0},	// Power State
		{1,1,0,NULL,0,1,0,0},	// Music State
		{2,1,0,NULL,0,1,0,0},	//负离子
		{3,1,0,NULL,0,1,0,0},	//灯定时功能
		
		{14,7,0,NULL,0,1,0,0},	// Light Mask
		
		{23,8,0,NULL,0,1,0,0},	// 温度整数部分
		{31,8,0,NULL,0,1,0,0},	// 温度小数部分

		{39,8,0,NULL,0,1,0,0},	// 湿度整数部分
		{47,8,0,NULL,0,1,0,0},	// 湿度小数部分
		
		{55,1,0,NULL,0,1,0,0},	//是否有外接传感 器

		/*算法 val*15/100000*/
		{63,8,0,NULL,0,1,0,0},	//PM3.0最高位 10
		{71,8,0,NULL,0,1,0,0},	//PM3.0次高位
		{79,8,0,NULL,0,1,0,0},	//PM3.0次低位
		{87,8,0,NULL,0,1,0,0},	//PM3.0最低位
		/*算法 val/10 */
		{159,8,0,NULL,0,1,0,0},	//湿度值1    14
		{167,8,0,NULL,0,1,0,0},	//湿度值2
		/*算法 (val-500)/10 */
		{175,8,0,NULL,0,1,0,0},	//温度值1    16
		{183,8,0,NULL,0,1,0,0},	//温度值2
		
		{191,1,0,NULL,0,1,0,0},	// 是否有灯报警
		{190,7,0,NULL,0,1,0,0},	//灯报警信息
		
		{193,2,0,NULL,0,1,0,0},	//水位报警值
		{194,1,0,NULL,0,1,0,0},	//水泵故障报警
		{195,1,0,NULL,0,1,0,0},	//营养液报警

        // ADD in 1.7
        {4,1,0,NULL,0,1,0,0},	// 水循环状态
        {54,1,0,NULL,0,1,0,0}, //是否有PM2.5的值，如果有，使用PM3.0最高位和次高位为值
	}

};

static XM_Command WaterPump={//报警解除
	3,
	0,
	XM_SEED_SET_LEN,
	0,
	0,
	101,
	0,
	101,
	0,
	0,
	0,
	{
		{94,1,0,NULL,0,0,1,0},	// 水循环设置
		{95,1,1,NULL,0,0,1,1},	// 水循环设置标志
	},
	{
	}
};


XM_AT_FUN at_cmd_Seed[10]={
	{"SEEDStat",NULL,0,&seedStat}, 	//状态查询
	{"SEEDPSet",NULL,0,&powerSet}, 	//电源	
	{"SEEDMSet",NULL,0,&musicSet},	//音乐设置
	{"SEEDVSet",NULL,0,&SetVolume},	//音量设置
	{"SEEDLSet",NULL,0,&lightSet}, 	//灯开关
	{"SEEDAnion",NULL,0,&anionSet},
	{"SEEDLTime",NULL,0,&lightTimer},
	{"SEEDCWarn",NULL,0,&warningClose},
	{"SEEDPm25",NULL,0,&pm25Set},
	
	{"WaterPump",NULL,0,&WaterPump},

};

XM_AT_RET at_cmd_ret_Seed[2]={
	{"SEEDStat",XM_SEND_QUERY,102,0,&seedStat},
	{"DCSET",XM_SEND_SETTING,101,0,NULL},
};

