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

#define XM_RQZ_SET_LEN 11
#define XM_RQZ_STATUS_LEN 19


XM_Command xm_RQZGJL={//左开关机
	2,
	0,
	XM_RQZ_SET_LEN,
	XM_RQZ_STATUS_LEN,
	0,
	101,
	0,
	0,
	0,
	0,
	0,
	{		
		{0,1,0,NULL,0,0,1,0},
		{1,1,0,NULL,0,0,1,0}
		
		
		//{7,8,0,NULL,0,0,1,0}
	},
	{
		{7,8,0,NULL,0,1,0,0},//左灶机器工作状态
		{15,8,0,NULL,0,1,0,0},//右灶机器工作状态
		{23,8,0,NULL,0,1,0,0},//左灶定时剩余小时
		{31,8,0,NULL,0,1,0,0},//左灶定时剩余分钟
		{39,8,0,NULL,0,1,0,0},//右灶定时剩余小时
		{47,8,0,NULL,0,1,0,0},//右灶定时剩余分钟
		{55,8,0,NULL,0,1,0,0},//CO报警（预留）
		{63,8,0,NULL,0,1,0,0},//燃气报警（预留）
		{71,8,0,NULL,0,1,0,0},//燃气报警（预留）
		{79,8,0,NULL,0,1,0,0},//燃气浓度（预留）
		{87,8,0,NULL,0,1,0,0},//故障代码
		{95,8,0,NULL,0,1,0,0},//故障代码（预留）
		{103,8,0,NULL,0,1,0,0},//故障代码（预留）
		{111,8,0,NULL,0,1,0,0},//故障代码（预留）
		{119,8,0,NULL,0,1,0,0},//故障代码（预留）
		{127,8,0,NULL,0,1,0,0},//预留数据
		{135,8,0,NULL,0,1,0,0},//预留数据
		{143,8,0,NULL,0,1,0,0},//预留数据
		{151,8,0,NULL,0,1,0,0}//预留数据
	}
};

XM_Command xm_RQZGJR={//右开关机
	2,
	0,
	XM_RQZ_SET_LEN,
	XM_RQZ_STATUS_LEN,
	0,
	101,
	0,
	0,
	0,
	0,
	0,
	{	
		{0,1,0,NULL,0,0,1,0},
		{1,1,0,NULL,0,0,1,0}	
				
		//{7,8,0,NULL,0,0,1,0}
	},
	{
		{7,8,0,NULL,0,1,0,0},//左灶机器工作状态
		{15,8,0,NULL,0,1,0,0},//右灶机器工作状态
		{23,8,0,NULL,0,1,0,0},//左灶定时剩余小时
		{31,8,0,NULL,0,1,0,0},//左灶定时剩余分钟
		{39,8,0,NULL,0,1,0,0},//右灶定时剩余小时
		{47,8,0,NULL,0,1,0,0},//右灶定时剩余分钟
		{55,8,0,NULL,0,1,0,0},//CO报警（预留）
		{63,8,0,NULL,0,1,0,0},//燃气报警（预留）
		{71,8,0,NULL,0,1,0,0},//燃气报警（预留）
		{79,8,0,NULL,0,1,0,0},//燃气浓度（预留）
		{87,8,0,NULL,0,1,0,0},//故障代码
		{95,8,0,NULL,0,1,0,0},//故障代码（预留）
		{103,8,0,NULL,0,1,0,0},//故障代码（预留）
		{111,8,0,NULL,0,1,0,0},//故障代码（预留）
		{119,8,0,NULL,0,1,0,0},//故障代码（预留）
		{127,8,0,NULL,0,1,0,0},//预留数据
		{135,8,0,NULL,0,1,0,0},//预留数据
		{143,8,0,NULL,0,1,0,0},//预留数据
		{151,8,0,NULL,0,1,0,0}//预留数据
	}
};


XM_Command xm_RQZPRODUCT={//产品型号读取与写入
	4,
	4,
	26,
	26,
	0,
	103,
	1,
	103,
	0,
	0,
	0,
	{
		{7,8,0,NULL,0,0,1,0},//第一个字节代表数据类型0表示使用BCD编码，
		{191,184,0,NULL,0,0,1,0},//后续23个字节表示数据，
		{199,8,0,NULL,0,0,1,0},//后2字节为累加和
		{207,8,0,NULL,0,0,1,0},//后2字节为累加和
	},
	{
		{7,8,0,NULL,0,1,0,0},//第一个字节代表数据类型0表示使用BCD编码，
		{191,184,0,NULL,0,1,0,0},//后续23个字节表示数据，
		{199,8,0,NULL,0,1,0,0},//后2字节为累加和
		{207,8,0,NULL,0,1,0,0},//后2字节为累加和
	}
};



XM_Command xm_RQZZD={//燃气灶状态查询
	0,
	19,
	0,
	XM_RQZ_STATUS_LEN,
	0,
	0,
	0,
	102,
	0,
	0,
	0,
	{	
	},
	{
		{7,8,0,NULL,0,1,0,0},//左灶机器工作状态
		{15,8,0,NULL,0,1,0,0},//右灶机器工作状态
		{23,8,0,NULL,0,1,0,0},//左灶定时剩余小时
		{31,8,0,NULL,0,1,0,0},//左灶定时剩余分钟
		{39,8,0,NULL,0,1,0,0},//右灶定时剩余小时
		{47,8,0,NULL,0,1,0,0},//右灶定时剩余分钟
		{55,8,0,NULL,0,1,0,0},//CO报警（预留）
		{63,8,0,NULL,0,1,0,0},//燃气报警（预留）
		{71,8,0,NULL,0,1,0,0},//燃气报警（预留）
		{79,8,0,NULL,0,1,0,0},//燃气浓度（预留）
		{87,8,0,NULL,0,1,0,0},//故障代码
		{95,8,0,NULL,0,1,0,0},//故障代码（预留）
		{103,8,0,NULL,0,1,0,0},//故障代码（预留）
		{111,8,0,NULL,0,1,0,0},//故障代码（预留）
		{119,8,0,NULL,0,1,0,0},//故障代码（预留）
		{127,8,0,NULL,0,1,0,0},//预留数据
		{135,8,0,NULL,0,1,0,0},//预留数据
		{143,8,0,NULL,0,1,0,0},//预留数据
		{151,8,0,NULL,0,1,0,0}//预留数据
	}
};



XM_Command xm_RQZOTHREZD={//燃气灶其他状态查询 (预留)
	0,
	18,
	0,
	0,
	6,
	0,
	0,
	102,
	1,
	0,
	0,
	{
	},
	{
		{7,8,0,NULL,0,1,0,0},//预留数据0
		{15,8,0,NULL,0,1,0,0},//预留数据1
		{23,8,0,NULL,0,1,0,0},//预留数据2
		{31,8,0,NULL,0,1,0,0},//预留数据3
		{39,8,0,NULL,0,1,0,0},//预留数据4
		{47,8,0,NULL,0,1,0,0},//预留数据5
		{55,8,0,NULL,0,1,0,0},//预留数据6
		{63,8,0,NULL,0,1,0,0},//预留数据7
		{71,8,0,NULL,0,1,0,0},//预留数据8
		{79,8,0,NULL,0,1,0,0},//预留数据9
		{87,8,0,NULL,0,1,0,0},//预留数据10
		{95,8,0,NULL,0,1,0,0},//预留数据11
		{103,8,0,NULL,0,1,0,0},//预留数据12
		{111,8,0,NULL,0,1,0,0},//预留数据13
		{119,8,0,NULL,0,1,0,0},//预留数据14
		{127,8,0,NULL,0,1,0,0},//预留数据15
		{135,8,0,NULL,0,1,0,0},//预留数据16
		{143,8,0,NULL,0,1,0,0},//预留数据17
		{151,8,0,NULL,0,1,0,0}//预留数据18
	}
};

XM_AT_RET at_cmd_ret_rqz[]={
		{"RQZZD",XM_SEND_QUERY,102,0,&xm_RQZZD},
		{"RQZGN",XM_SEND_QUERY,102,64,NULL},
		{"RQZSET",XM_SEND_QUERY,101,0,&xm_RQZZD}		
};

XM_AT_FUN at_cmd_rqz[5]={
	{"RQZGJL",NULL,0,&xm_RQZGJL},//左开关机
	{"RQZGJR",NULL,0,&xm_RQZGJR},//右开关机
	{"RQZPRODUCT",NULL,0,&xm_RQZPRODUCT},//产品型号读取与写入
	{"RQZZD",NULL,0,&xm_RQZZD},//燃气灶状态查询
	{"RQZOTHREZD",NULL,0,&xm_RQZOTHREZD},//燃气灶其他状态查询 (预留)
};

