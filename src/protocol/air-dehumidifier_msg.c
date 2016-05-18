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
#include	"air-dehumidifier_msg.h"
#include	"cmdanalysis.h"
static XM_Value xm_FS2value[]={		
		{"weak",0},
		{"strong",1},
		{"auto",2}
};

XM_Command xm_CSFS={//风速设置
	3,
	0,
	8,
	0,
	0,
	101,
	0,
	0,
	0,
	0,
	0,
	{
		{6,3,sizeof(xm_FS2value)/sizeof(xm_FS2value[0]),xm_FS2value,0,0,1,0},
		{7,1,0,NULL,0,0,1,1},
		{8,1,0,NULL,0,0,1,0}
	},
	{
	}
};

static XM_Value xm_MS2value[]={
		{"continue",0},
		{"normal",1},
		{"auto",2}		
};

XM_Command xm_CSMS={//运行模式设置
	3,
	0,
	8,
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
		{"23h",33},
		{"24h",34}
};

XM_Command xm_CSDS={//定时开关机
	4,
	0,
	8,
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

XM_Command xm_CSSD={//湿度设置
	3,
	0,
	8,
	0,
	0,
	101,
	0,
	0,
	0,
	0,
	0,
	{
		{30,7,0,NULL,0,0,1,0},
		{31,1,0,NULL,0,0,1,1},	
		{8,1,0,NULL,0,0,1,0}
	},
	{
	}
};


XM_Command xm_CSWD={//湿度设置
	3,
	0,
	8,
	0,
	0,
	101,
	0,
	0,
	0,
	0,
	0,
	{
		{38,7,0,NULL,0,0,1,0},
		{39,1,0,NULL,0,0,1,1},	
		{8,1,0,NULL,0,0,1,0}
	},
	{
	}
};


XM_Command xm_CSKJ={//开停除湿机
	3,
	0,
	8,
	0,
	0,
	101,
	0,
	0,
	0,
	0,
	0,
	{
		{40,1,0,NULL,0,0,1,0},
		{41,1,0,NULL,0,0,1,1},
		{8,1,0,NULL,0,0,1,0}
	},
	{
	}
};


XM_Command xm_CSDJR={//电加热控制
	3,
	0,
	8,
	0,
	0,
	101,
	0,
	0,
	0,
	0,
	0,
	{
		{42,1,0,NULL,0,0,1,0},
		{43,1,0,NULL,0,0,1,1},
		{8,1,0,NULL,0,0,1,0}
	},
	{
	}
};


XM_Command xm_CSSB={//水泵开停控制
	3,
	0,
	8,
	0,
	0,
	101,
	0,
	0,
	0,
	0,
	0,
	{
		{44,1,0,NULL,0,0,1,0},
		{45,1,0,NULL,0,0,1,1},
		{8,1,0,NULL,0,0,1,0},
	},
	{
	}
};


XM_Command xm_CSFNZ={//负离子开停控制
	3,
	0,
	8,
	0,
	0,
	101,
	0,
	0,
	0,
	0,
	0,
	{
		{46,1,0,NULL,0,0,1,0},
		{47,1,0,NULL,0,0,1,1},
		{8,1,0,NULL,0,0,1,0},
	},
	{
	}
};

XM_Command xm_CSSBOX={//smartbox；一条命令操作多个功能；
	9,
	0,
	8,
	0,
	0,
	101,
	0,
	0,
	0,
	0,
	0,
	{
		{40,1,0,NULL,0,0,1,0},//开机
		{41,1,0,NULL,0,0,1,1},
		{14,3,sizeof(xm_MS2value)/sizeof(xm_MS2value[0]),xm_MS2value,0,0,1,0},//模式
		{15,1,0,NULL,0,0,1,1},
		{6,3,sizeof(xm_FS2value)/sizeof(xm_FS2value[0]),xm_FS2value,0,0,1,0},//风速
		{7,1,0,NULL,0,0,1,1},
		{30,7,0,NULL,0,0,1,0},//湿度设置
		{31,1,0,NULL,0,0,1,1},	
		{8,1,0,NULL,0,0,1,0}
	},
	{		
	}
};




XM_Command xm_CSZD={//状态
	1,
	20,
	0,
	9,
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
		{6,3,sizeof(xm_FS2value)/sizeof(xm_FS2value[0]),xm_FS2value,0,1,0,0},//风速设置 0
		{14,3,sizeof(xm_MS2value)/sizeof(xm_MS2value[0]),xm_MS2value,0,1,0,0},//运行模式设置 1
		{16,1,0,NULL,0,1,0,0},//定时开关机有效2
		{22,6,sizeof(xm_DS2value)/sizeof(xm_DS2value[0]),xm_DS2value,0,1,0,0},//定时开关机3
		{31,8,0,NULL,0,1,0,0},//湿度设置4
		{39,8,0,NULL,0,1,0,0},//电加热设定温度5
		{47,8,0,NULL,0,1,0,0},//室内温度6
		{48,1,0,NULL,0,1,0,0},//开停除湿机7
		{49,1,0,NULL,0,1,0,0},//电加热控制8
		{50,1,0,NULL,0,1,0,0},//水泵开停控制9
		{51,1,0,NULL,0,1,0,0},//负离子开停控制10
		{52,1,0,NULL,0,1,0,0},//本次命令之前有否红外和按键控制过11
		{53,1,0,NULL,0,1,0,0},//本次命令之前有否WIFI控制过12
		{56,1,0,NULL,0,1,0,0},//过滤网清洁告警13
		{57,1,0,NULL,0,1,0,0},//湿度传感器故障14
		{58,1,0,NULL,0,1,0,0},//管温传感器故障15
		{59,1,0,NULL,0,1,0,0},//室温传感器故障16
		{60,1,0,NULL,0,1,0,0},//水满告警17
		{61,1,0,NULL,0,1,0,0},//水泵故障18
		{71,8,0,NULL,0,1,0,0}//实际湿度19
	}
};



XM_Command xm_CSGN={//功能
	0,
	18,
	0,
	0,
	6,
	0,
	0,
	102,
	64,
	0,
	0,
	{
	},
	{
		{4,1,0,NULL,0,1,0,0},//风速可设置状态-智慧风0
		{5,1,0,NULL,0,1,0,0},//风速可设置状态-高风1
		{6,1,0,NULL,0,1,0,0},//风速可设置状态-中风2
		{7,1,0,NULL,0,1,0,0},//风速可设置状态-低风3
		{13,1,0,NULL,0,1,0,0},//运行模式状态-持续运行模式4
		{14,1,0,NULL,0,1,0,0},//运行模式状态-正常运行模式5
		{15,1,0,NULL,0,1,0,0},//运行模式状态-自动运行模式6
		{16,1,0,NULL,0,1,0,0},//工作模式设置与控制1-普通定时功能7
		{17,1,0,NULL,0,1,0,0},//工作模式设置与控制1-电加热功能8
		{18,1,0,NULL,0,1,0,0},//工作模式设置与控制1=电加热温度设置9
		{19,1,0,NULL,0,1,0,0},//工作模式设置与控制1-室内湿度设置10
		{20,1,0,NULL,0,1,0,0},//工作模式设置与控制1-水泵开停控制11
		{21,1,0,NULL,0,1,0,0},//工作模式设置与控制1-负离子开停控制12
		{22,1,0,NULL,0,1,0,0},//工作模式设置与控制1-电量检测功能13
		{23,1,0,NULL,0,1,0,0},//工作模式设置与控制1-开停机功能14
		{24,1,0,NULL,0,1,0,0},//EEPROM可改写功能15
		{39,8,0,NULL,0,1,0,0},//101#-0#第7字节预留位的控制功能16
		{47,8,0,NULL,0,1,0,0}//101#-0#第8字节预留位的控制功能17
	}
};

XM_AT_RET at_cmd_ret_cs[]={
		{"CSZD",XM_SEND_QUERY,102,0,&xm_CSZD},
		{"CSGN",XM_SEND_QUERY,102,64,&xm_CSGN},
		{"CSSET",XM_SEND_SETTING,101,0,NULL}		
};


XM_AT_FUN at_cmd_cs[12]={
	{"CSFS",NULL,0,&xm_CSFS},//风速设置
	{"CSMS",NULL,0,&xm_CSMS},//运行模式设置
	{"CSDS",NULL,0,&xm_CSDS},//定时开关机
	{"CSSD",NULL,0,&xm_CSSD},//湿度设置
	{"CSWD",NULL,0,&xm_CSWD},//温度设置
	{"CSKJ",NULL,0,&xm_CSKJ},//开停净化机
	{"CSDJR",NULL,0,&xm_CSDJR},//电加热控制
	{"CSSB",NULL,0,&xm_CSSB},//水泵开停控制
	{"CSFNZ",NULL,0,&xm_CSFNZ},//负离子开停控制
	{"CSZD",NULL,0,&xm_CSZD},//状态
	{"CSGN",NULL,0,&xm_CSGN},//功能
	{"CSSBOX",NULL,0,&xm_CSSBOX}//smartbox；一条命令操作多个功能；

};

