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
#include	"air-cleansing_msg.h"
#include	"cmdanalysis.h"
static XM_Value xm_FS2value[]={
		{"weak",0},
		{"middle",1},
		{"strong",2},
		{"clear",3},
		{"auto",4},
		{"auto",5},
		{"auto",6},
		{"auto",7}
};

XM_Command xm_JHFS={//净化速度设置
	3,
	0,
	6,
	0,
	0,
	101,
	0,
	0,
	0,
	0,
	0,
	{
		{6,7,sizeof(xm_FS2value)/sizeof(xm_FS2value[0]),xm_FS2value,0,0,1,0},
		{7,1,0,NULL,0,0,1,1},
		{8,1,0,NULL,0,0,1,0}
	},
	{
	}
};

static XM_Value xm_MS2value[]={
		{"cleardust",0},
		{"clearsmell",1},
		{"smart",2},
		{"mute",3},
		{"sleep",4},
};

XM_Command xm_JHMS={//净化模式设置
	3,
	0,
	6,
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
		{"10h",29},
		{"20h",30},
		{"21h",31},
		{"22h",32},
		{"23h",33}
};

XM_Command xm_JHDS={//定时开关机
	4,
	0,
	6,
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
		{23,1,0,NULL,0,0,1,1},
		{16,1,0,NULL,0,0,1,0},
		{8,1,0,NULL,0,0,1,0}
	
	},
	{
	}
};

XM_Command xm_JHKJ={//开停净化机
	3,
	0,
	6,
	0,
	0,
	101,
	0,
	0,
	0,
	0,
	0,
	{
		{24,1,0,NULL,0,0,1,0},
		{25,1,0,NULL,0,0,1,1},
		{8,1,0,NULL,0,0,1,0}
	},
	{
	}
};

XM_Command xm_JHRT={//儿童锁开关控制
	3,
	0,
	6,
	0,
	0,
	101,
	0,
	0,
	0,
	0,
	0,
	{
		{26,1,0,NULL,0,0,1,0},
		{27,1,0,NULL,0,0,1,1},
		{8,1,0,NULL,0,0,1,0}
	},
	{
	}
};

XM_Command xm_JHSLZ={//水离子开停控制
	3,
	0,
	6,
	0,
	0,
	101,
	0,
	0,
	0,
	0,
	0,
	{
		{28,1,0,NULL,0,0,1,0},
		{29,1,0,NULL,0,0,1,1},
		{8,1,0,NULL,0,0,1,0}
	},
	{
	}
};

XM_Command xm_JHSBOX={//smartbox；一条命令操作多个功能；
	11,
	0,
	6,
	0,
	0,
	101,
	0,
	0,
	0,
	0,
	0,
	{
		{24,1,0,NULL,0,0,1,0},//开机
		{25,1,0,NULL,0,0,1,1},
		{14,3,sizeof(xm_MS2value)/sizeof(xm_MS2value[0]),xm_MS2value,0,0,1,0},//模式
		{15,1,0,NULL,0,0,1,1},
		{6,7,sizeof(xm_FS2value)/sizeof(xm_FS2value[0]),xm_FS2value,0,0,1,0},//风速
		{7,1,0,NULL,0,0,1,1},
		{30,1,0,NULL,0,0,1,0},//加湿机开停控制
		{31,1,0,NULL,0,0,1,1},
		{38,7,0,NULL,0,0,1,0},//加湿机湿度设置
		{39,1,0,NULL,0,0,1,1},
		{8,1,0,NULL,0,0,1,0}
	},
	{		
	}
};



XM_Command xm_JHJSJ={//加湿机开停控制
	3,
	0,
	6,
	0,
	0,
	101,
	0,
	0,
	0,
	0,
	0,
	{
		{30,1,0,NULL,0,0,1,0},
		{31,1,0,NULL,0,0,1,1},
		{8,1,0,NULL,0,0,1,0}
	},
	{
	}
};

XM_Command xm_JHHS={//加湿机湿度设置
	3,
	0,
	6,
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




XM_Command xm_JHZD={//状态
	1,
	24,
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
		{6,7,sizeof(xm_FS2value)/sizeof(xm_FS2value[0]),xm_FS2value,0,1,0,0},////净化速度设置 0
		{14,3,sizeof(xm_MS2value)/sizeof(xm_MS2value[0]),xm_MS2value,0,1,0,0},//净化模式设置1
		{16,1,0,NULL,0,1,0,0},//定时开关机控制2
		{22,6,sizeof(xm_DS2value)/sizeof(xm_DS2value[0]),xm_DS2value,0,1,0,0},//定时开关机时间3
		{31,8,0,NULL,0,1,0,0},//风机转速4
		{39,8,0,NULL,0,1,0,0},//空气质量5
		{47,8,0,NULL,0,1,0,0},//空气质量百分比6
		{55,8,0,NULL,0,1,0,0},//相对湿度7
		{56,1,0,NULL,0,1,0,0},//开停净化机8
		{57,1,0,NULL,0,1,0,0},//儿童锁开关控制9
		{58,1,0,NULL,0,1,0,0},	//水离子开停控制10
		{59,1,0,NULL,0,1,0,0},//加湿机开停控制11
		{60,1,0,NULL,0,1,0,0},//过滤网更换提示12
		{61,1,0,NULL,0,1,0,0},//本次命令之前有否红外和按键控制过13
		{62,1,0,NULL,0,1,0,0},//本次命令之前有否红外和按键控制过14
		{64,1,0,NULL,0,1,0,0},//加湿转轮不动15
		{65,1,0,NULL,0,1,0,0},//水箱空16
		{66,1,0,NULL,0,1,0,0},//水箱未装好17
		{67,1,0,NULL,0,1,0,0},//湿度传感器故障18
		{68,1,0,NULL,0,1,0,0},//风机故障19
		{69,1,0,NULL,0,1,0,0},//风尘传感器故障20
		{70,1,0,NULL,0,1,0,0},//气味传感器故障21
		{71,1,0,NULL,0,1,0,0},//机器倾斜故障22
		{79,8,0,NULL,0,1,0,0}//湿度控制湿度设置23
	}
};

XM_Command xm_JHGN={//功能查询
	0,
	19,
	0,
	0,
	5,
	0,
	0,
	102,
	64,
	0,
	0,
	{
	},
	{
		{3,1,0,NULL,0,1,0,0},//净化速度状态-自动功能
		{4,1,0,NULL,0,1,0,0},//净化速度状态-净烟功能
		{5,1,0,NULL,0,1,0,0},//净化速度状态-高风功能
		{6,1,0,NULL,0,1,0,0},//净化速度状态-中风功能
		{7,1,0,NULL,0,1,0,0},//净化速度状态-低风功能		
		{11,1,0,NULL,0,1,0,0},//净化模式状态-睡眠功能	
		{12,1,0,NULL,0,1,0,0},//净化模式状态-静音功能	
		{13,1,0,NULL,0,1,0,0},//净化模式状态-智能功能	
		{14,1,0,NULL,0,1,0,0},//净化模式状态-除味功能	
		{15,1,0,NULL,0,1,0,0},//净化模式状态-	除烟功能	
		{16,1,0,NULL,0,1,0,0},//普通定时功能
		{17,1,0,NULL,0,1,0,0},//儿童锁功能
		{18,1,0,NULL,0,1,0,0},//水离子开停
		{19,1,0,NULL,0,1,0,0},//加湿机开停功能
		{20,1,0,NULL,0,1,0,0},//净化机开停功能
		{22,1,0,NULL,0,1,0,0},//EEPROM可改写功能
		{23,1,0,NULL,0,1,0,0},//电量检测功能
		{24,8,0,NULL,0,1,0,0},//101#-0#第5字节预留位的控制功能
		{32,8,0,NULL,0,1,0,0}//101#-0#第6字节预留位的控制功能
	}
};

XM_Command xm_EXTEND={//扩展的查询状态
	1,
	3,
	1,
	8,
	0,
	0,
	0,
	102,
	8,
	0,
	0,
	{
		{7,1,0,NULL,0,1,0,0}
	},
	{
		{7,7,0,NULL,0,1,0,0},//室内温度
		{15,8,0,NULL,0,1,0,0},//剩余使用时间小时高位
		{23,8,0,NULL,0,1,0,0},//剩余使用时间小时低位
	}
};


XM_AT_RET at_cmd_ret_jh[4]={
		{"JHZD",XM_SEND_QUERY,102,0,&xm_JHZD},
		{"JHGN",XM_SEND_QUERY,102,64,&xm_JHGN},
		{"JHSET",XM_SEND_SETTING,101,0,NULL},
		{"JHEXTEND",XM_SEND_QUERY,102,8,&xm_EXTEND}
};

XM_AT_FUN at_cmd_jh[12]={
	{"JHFS",NULL,0,&xm_JHFS},//净化速度设置
	{"JHMS",NULL,0,&xm_JHMS},//净化模式设置
	{"JHDS",NULL,0,&xm_JHDS},//定时开关机
	{"JHKJ",NULL,0,&xm_JHKJ},//开停净化机
	{"JHRT",NULL,0,&xm_JHRT},//儿童锁开关控制
	{"JHSLZ",NULL,0,&xm_JHSLZ},//水离子开停控制
	{"JHJSJ",NULL,0,&xm_JHJSJ},//加湿机开停控制
	{"JHHS",NULL,0,&xm_JHHS},//湿度设置
	{"JHZD",NULL,0,&xm_JHZD},//状态
	{"JHGN",NULL,0,&xm_JHGN},//功能查询
	{"JHSBOX",NULL,0,&xm_JHSBOX},//smartbox；一条命令操作多个功能；
	{"JHEXTEND",NULL,0,&xm_EXTEND},
};

