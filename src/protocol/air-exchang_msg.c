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
#include	"air-exchang_msg.h"
#include	"cmdanalysis.h"

static XM_Value xm_SD2value[]={
		{"weak",0},
		{"middle",1},
		{"strong",2},
		{"auto",4},
		{"middle",5},//middle
		{"strong",6}//strong
};

static XM_Value xm_SD2value_return[]={
		{"weak",0},
		{"middle",1},
		{"strong",2},
		{"weak",4},
		{"middle",5},//middle
		{"strong",6}//strong
};


XM_Command xm_QRSD={//换气速度
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
		{6,7,sizeof(xm_SD2value)/sizeof(xm_SD2value[0]),xm_SD2value,0,0,1,0},
		{7,1,0,NULL,0,0,1,1},
		{8,1,0,NULL,0,0,1,0}
	},
	{
	}
};


XM_Command xm_QRKJ={//开机
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
		{10,1,0,NULL,0,0,1,0},
		{11,1,0,NULL,0,0,1,1},
		{8,1,0,NULL,0,0,1,0}
	},
	{
	}
};

static XM_Value xm_MS2value[]={
		{"fullheat",0},
		{"direct",1},
		{"indoor",2},
		{"auto",4},
		{"direct",5},
		{"indoor",6},
};

static XM_Value xm_MS2value_return[]={
		{"fullheat",0},
		{"direct",1},
		{"indoor",2},
		{"fullheat",4},
		{"direct",5},
		{"indoor",6},
};



XM_Command xm_QRMS={//换气模式
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
		{14,3,sizeof(xm_MS2value)/sizeof(xm_MS2value[0]),xm_MS2value,0,0,1,0},
		{15,1,0,NULL,0,0,1,1},
		{8,1,0,NULL,0,0,1,0}
	},
	{
	}
};

static XM_Value xm_DS2value[]={
		{"off",0},
		{"0.5h",1},
		{"1.0h",2},
		{"1.5h",3},
		{"2.0h",4},
		{"2.5h",5},
		{"3.0h",6},
		{"3.5h",7},
		{"4.0h",8},
		{"4.5h",9},
		{"5.0h",10},
		{"5.5h",11},
		{"6.0h",12},
		{"6.5h",13},
		{"7.0h",14},
		{"7.5h",15},
		{"8.0h",16},
		{"8.5h",17},
		{"9.0h",18},
		{"9.5h",19},
		{"10h",20},
		{"11h",21},
		{"12h",22},
		{"13h",23},
		{"14h",24},
		{"15h",25},
		{"16h",26},
		{"17h",27},
		{"18h",28},
		{"19h",29},
		{"20h",30},
		{"21h",31},
		{"22h",32},
		{"23h",33}
};


XM_Command xm_QRDS={//定时开关机
	4,
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
		{22,6,sizeof(xm_DS2value)/sizeof(xm_DS2value[0]),xm_DS2value,0,0,1,0},
		{16,1,0,NULL,0,0,1,0},
		{23,1,0,NULL,0,0,1,1},
		{8,1,0,NULL,0,0,1,0}
		
	},
	{
	}
};


XM_Command xm_QRSBOX={//smartbox；一条命令操作多个功能；
	7,
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
		{10,1,0,NULL,0,0,1,0},//开机
		{11,1,0,NULL,0,0,1,1},
		{14,3,sizeof(xm_MS2value)/sizeof(xm_MS2value[0]),xm_MS2value,0,0,1,0},//模式
		{15,1,0,NULL,0,0,1,1},
		{6,7,sizeof(xm_SD2value)/sizeof(xm_SD2value[0]),xm_SD2value,0,0,1,0},//风速
		{7,1,0,NULL,0,0,1,1},		
		{8,1,0,NULL,0,0,1,0}
	},
	{		
	}
};



XM_Command xm_QRZD={//状态
	1,
	27,
	0,
	10,
	0,
	0,
	0,
	102,
	0,
	0,
	0,
	{
		{7,1,0,NULL,0,1,0,0}
	},
	{
		{6,7,sizeof(xm_SD2value_return)/sizeof(xm_SD2value_return[0]),xm_SD2value_return,0,1,0,0},//净化速度状态0
		{10,1,0,NULL,0,1,0,0},//换气机开停1
		{11,1,0,NULL,0,1,0,0},//待机模式2
		{14,3,sizeof(xm_MS2value_return)/sizeof(xm_MS2value_return[0]),xm_MS2value_return,0,1,0,0},//换气模式设置2
		{16,1,0,NULL,0,1,0,0},//普通定时4
		{22,6,sizeof(xm_DS2value)/sizeof(xm_DS2value[0]),xm_DS2value,0,1,0,0},//普通定时时间5
		{31,8,0,NULL,0,1,0,0},//室外风机转速6
		{39,8,0,NULL,0,1,0,0},//室内风机转速7
		{43,1,0,NULL,0,1,0,0},//室内侧温度参数有效8
		{44,1,0,NULL,0,1,0,0},//室内侧湿度参数有效9
		{45,1,0,NULL,0,1,0,0},//室内二氧化碳浓度参数有效10
		{46,1,0,NULL,0,1,0,0},//室外侧温度参数有效11
		{47,1,0,NULL,0,1,0,0},//室外侧湿度参数有效12		
		{55,8,0,NULL,0,1,0,0},//室内侧温度13
		{63,8,0,NULL,0,1,0,0},//室内侧相对湿度14
		{71,8,0,NULL,0,1,0,0},//室外侧温度15
		{79,8,0,NULL,0,1,0,0},//室外侧相对湿度16
		{87,8,0,NULL,0,1,0,0},//室内侧二氧化碳浓度高位17
		{95,8,0,NULL,0,1,0,0},//室内侧二氧化碳浓度低位18
		{96,1,0,NULL,0,1,0,0},//过滤器更换提示19
		{97,1,0,NULL,0,1,0,0},//室外风机故障20
		{98,1,0,NULL,0,1,0,0},//室内风机故障21
		{99,1,0,NULL,0,1,0,0},//室外侧温度传感器故障22
		{100,1,0,NULL,0,1,0,0},//室外侧湿度传感器故障23
		{101,1,0,NULL,0,1,0,0},//二氧化碳传感器故障24
		{102,1,0,NULL,0,1,0,0},//室内侧温度传感器故障25
		{103,1,0,NULL,0,1,0,0}//室内侧湿度传感器故障26
	}
};

XM_Command xm_QRGN={
	0,
	8,
	0,
	0,
	3,
	0,
	0,
	102,
	64,
	0,
	0,
	{
	},
	{
		{7,4,0,NULL,0,1,0,0},//风量支持档位数0
		{12,1,0,NULL,0,1,0,0},//全热换气模式1
		{13,1,0,NULL,0,1,0,0},//直通换气模式2
		{14,1,0,NULL,0,1,0,0},//室内回风模式3 
		{16,1,0,NULL,0,1,0,0},//普通定时功能4
		{17,1,0,NULL,0,1,0,0},//开关机控制位5
		{22,1,0,NULL,0,1,0,0},//EEPROM可改写功能6
		{23,1,0,NULL,0,1,0,0},//电量检测功能7
	}
};

XM_AT_RET at_cmd_ret_qr[3]={
		{"QRZD",XM_SEND_QUERY,102,0,&xm_QRZD},
		{"QRGN",XM_SEND_QUERY,102,64,&xm_QRGN},
		{"QRSET",XM_SEND_SETTING,101,0,NULL}		
};

XM_AT_FUN at_cmd_qr[7]={
	{"QRSD",NULL,0,&xm_QRSD},//换气速度
	{"QRKJ",NULL,0,&xm_QRKJ},//开机控制
	{"QRMS",NULL,0,&xm_QRMS},//换气模式
	{"QRDS",NULL,0,&xm_QRDS},//定时开关机
	{"QRZD",NULL,0,&xm_QRZD},//状态
	{"QRGN",NULL,0,&xm_QRGN},//功能
	{"QRSBOX",NULL,0,&xm_QRSBOX}//smartbox；一条命令操作多个功能；
};

