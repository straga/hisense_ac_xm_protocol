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

#define XM_RSQ_SET_LEN 12
#define XM_RSQ_STATUS_LEN 19

XM_Command xm_RSQKJ={//开关机
	3,
	0,
	XM_RSQ_SET_LEN,
	XM_RSQ_STATUS_LEN,
	0,
	101,
	0,
	0,
	0,
	0,
	0,
	{		
		{7,8,0,NULL,0,0,1,0},
		{15,8,0,NULL,0,0,1,0},
		{23,8,0,NULL,0,0,1,0}
	},
	{

	}
};




XM_Command xm_RSQWD={//温度设置
	3,
	0,
	XM_RSQ_SET_LEN,
	XM_RSQ_STATUS_LEN,
	0,
	101,
	0,
	0,
	0,
	0,
	0,
	{		
		{7,8,0,NULL,0,0,1,0},
		{15,8,0,NULL,0,0,1,0},
		{23,8,0,NULL,0,0,1,0}
	},
	{

	}
};


XM_Command xm_RSQ50LOCK={//50℃温度锁设置
	3,
	0,
	XM_RSQ_SET_LEN,
	XM_RSQ_STATUS_LEN,
	0,
	101,
	0,
	0,
	0,
	0,
	0,
	{
		{7,8,0,NULL,0,0,1,0},
		{15,8,0,NULL,0,0,1,0},
		{23,8,0,NULL,0,0,1,0}
	},
	{

	}
};

XM_Command xm_RSQPRODUCT={//产品型号读取与写入
	0,
	4,
	0,
	26,
	0,
	103,
	0,
	103,
	0,
	0,
	0,
	{
	},
	{
		{7,8,0,NULL,0,1,0,0},//第一个字节代表数据类型0表示使用BCD编码，
		{191,184,0,NULL,0,1,0,0},//后续23个字节表示数据，
		{199,8,0,NULL,0,1,0,0},//后2字节为累加和
		{207,8,0,NULL,0,1,0,0},//后2字节为累加和
	}
};



XM_Command xm_RSQZD={//热水器状态查询
	0,
	19,
	0,
	XM_RSQ_STATUS_LEN,
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
		{7,8,0,NULL,0,1,0,0},//机器工作状态
		{15,8,0,NULL,0,1,0,0},//co报警
		{23,8,0,NULL,0,1,0,0},//燃气报警
		{31,8,0,NULL,0,1,0,0},//CO浓度（预留）
		{39,8,0,NULL,0,1,0,0},//燃气浓度（预留）
		{47,8,0,NULL,0,1,0,0},//保养时间（高位）
		{55,8,0,NULL,0,1,0,0},//保养时间（低位）
		{63,8,0,NULL,0,1,0,0},//出水温度
		{71,8,0,NULL,0,1,0,0},//设定温度
		{79,8,0,NULL,0,1,0,0},//50℃温度锁
		{87,8,0,NULL,0,1,0,0},//设定温度60℃限制
		{95,8,0,NULL,0,1,0,0},//燃烧状态
		{103,8,0,NULL,0,1,0,0},//预热响应0，无，1 手动，2，自动
		{111,8,0,NULL,0,1,0,0},//呼叫响应（预留）
		{119,8,0,NULL,0,1,0,0},//故障代码
		{127,8,0,NULL,0,1,0,0},//预留数据0
		{135,8,0,NULL,0,1,0,0},//预留数据1
		{143,8,0,NULL,0,1,0,0},//预留数据2
		{151,8,0,NULL,0,1,0,0}//预留数据3
	}
};



XM_Command xm_RSQOTHREZD={//热水器其他状态查询 (预留)
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

XM_Command xm_RSQPERHEAT={//预热功能设置
	5,
	0,
	XM_RSQ_SET_LEN,
	XM_RSQ_STATUS_LEN,
	0,
	101,
	0,
	0,
	0,
	0,
	0,
	{	
		{7,8,0,NULL,0,0,1,0},
		{15,8,0,NULL,0,0,1,0},
		{23,8,0,NULL,0,0,1,0},
		{30,3,0,NULL,0,0,1,0},// 0 取消，1 手动，2，自动
		{31,1,0,NULL,0,0,1,1},  
	},
	{
	
	}
};


XM_Command xm_RSQGN={//功能查询
	0,
	7,
	0,
	10,
	0,
	102,
	64,
	102,
	64,
	0,
	0,
	{		
	},
	{
		{7,8,0,NULL,0,1,0,0},// 容量
		{15,8,0,NULL,0,1,0,0},//最低温度
		{23,8,0,NULL,0,1,0,0},//最高温度

		{28,1,0,NULL,0,1,0,0},//50度锁是否可操作
		{29,1,0,NULL,0,1,0,0},//最否有紧急呼叫功能
		{30,1,0,NULL,0,1,0,0},//是否有预热功能
		{31,1,0,NULL,0,1,0,0},//是否有50度锁功能
	}
};


XM_AT_RET at_cmd_ret_rsq[]={
		{"RSQZD",XM_SEND_QUERY,102,0,&xm_RSQZD},
		{"RSQPRODUCT",XM_SEND_QUERY,103,0,&xm_RSQPRODUCT},
		{"RSQGN",XM_SEND_QUERY,102,64,&xm_RSQGN},
		{"RSQSET",XM_SEND_QUERY,101,0,&xm_RSQZD}		
};


XM_AT_FUN at_cmd_rsq[8]={
	{"RSQKJ",NULL,0,&xm_RSQKJ},//开关机设置
	{"RSQWD",NULL,0,&xm_RSQWD},//温度设置
	{"RSQ50LOCK",NULL,0,&xm_RSQ50LOCK},//50℃温度锁设置	
	{"RSQPRODUCT",NULL,0,&xm_RSQPRODUCT},//产品型号查询
	{"RSQGN",NULL,0,&xm_RSQGN},
	{"RSQZD",NULL,0,&xm_RSQZD},//热水器状态查询
	{"RSQPERHEAT",NULL,0,&xm_RSQPERHEAT},//热水器预热功能
	{"RSQOTHREZD",NULL,0,&xm_RSQOTHREZD},//热水器其他状态查询 (预留)	
};

