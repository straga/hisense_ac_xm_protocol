//
//  VoltameterLogic.cpp
//  devices
//
//  Created by administratiors on 15/12/15.
//  Copyright © 2015年 xiaofangliang. All rights reserved.
//

#include "VoltameterLogic.h"
#include "IOTConstants.h"
#include "IOTUtil.h"
#include <sstream>

VoltameterLogic::VoltameterLogic()
{
    At_QureyStatus = "VolZD";
    At_QueryFuntion = "VolGN";
    DEVICE_TYPE = 0x11;
    At_Status_Num = 27;
    At_Funtion_Num = 8;
    
    // 初始化ZD数组
    for(int i = 0; i < At_Status_Num; i++)
    {
        ZD.push_back("0");
    }
    
    // 初始化GN数组
    for(int i = 0; i < At_Funtion_Num;i ++)
    {
        GN.push_back(0);
    }
}

VoltameterLogic::~VoltameterLogic()
{
    
}

/******************************** 功能设置 ********************************************/
/** 总的电源开关 */
string  VoltameterLogic::setPower(int power)
{
    string A = getVoltameterValue();
    string atcmd = IOTConstants::CMD_AT_MARK + "VolSet" + IOTConstants::CMD_AT_EQUALS_SINGNAL
				+ deviceId +
                IOTConstants::PARAM_VALUE_SPLIT
                +A
                +IOTConstants::PARAM_VALUE_SPLIT
				+ IOTUtil::intToString(power)
				+ IOTConstants::CMD_AT_WRAP;
    return	createNetBytes(atcmd);
    
}

/** 电量统计清0 1清零，0不清零 */
string  VoltameterLogic::setResetCount(int isResetCount)
{
    string A = getPower();
    if (IOTUtil::stringToInt(A)==0) {
        return "";
    }
    else
    {
    string atcmd = IOTConstants::CMD_AT_MARK + "VolSet" + IOTConstants::CMD_AT_EQUALS_SINGNAL
				+ deviceId + IOTConstants::PARAM_VALUE_SPLIT
				+ IOTUtil::intToString(isResetCount)
                + IOTConstants::PARAM_VALUE_SPLIT
                + A
				+ IOTConstants::CMD_AT_WRAP;
    return	createNetBytes(atcmd);
    }
}

/******************************** 状态查询 ********************************************/
/** 总电源开关状态 */
string  VoltameterLogic::getPower()
{
    return ZD[0];
}

/** 电流值uA */
string  VoltameterLogic::getCurrentValue()
{
    int a = IOTUtil::stringToInt(ZD[1]);
    int b = IOTUtil::stringToInt(ZD[2]);
    int c = IOTUtil::stringToInt(ZD[3]);
    int d = IOTUtil::stringToInt(ZD[4]);
    return IOTUtil::intToString((a<<24)|(b<<16)|(c<<8)|d);
    
    
}

/** 电压值mV */
string  VoltameterLogic::getVoltageValue()
{
    int a = IOTUtil::stringToInt(ZD[5]);
    int b = IOTUtil::stringToInt(ZD[6]);
    int c = IOTUtil::stringToInt(ZD[7]);
    int d = IOTUtil::stringToInt(ZD[8]);
    return IOTUtil::intToString((a<<24)|(b<<16)|(c<<8)|d);
}

/**
 * 整个电量值的统计用64位数据表示，以大端字节序存储
 * 统计时使用 (PCountH * 0xffffffff)+PCountL得到最终结果，单位焦尔
 */
/** 电量值的统计 */
string VoltameterLogic::getVoltameterValue()
{
    int64 result;
    char buf[9];
    int i = 0;
    int data[8];
    string str;
    data[0] = IOTUtil::stringToInt(ZD[9]);
    data[1] = IOTUtil::stringToInt(ZD[10]);
    data[2] = IOTUtil::stringToInt(ZD[11]);
    data[3] = IOTUtil::stringToInt(ZD[12]);
    data[4] = IOTUtil::stringToInt(ZD[13]);
    data[5] = IOTUtil::stringToInt(ZD[14]);
    data[6] = IOTUtil::stringToInt(ZD[15]);
    data[7]= IOTUtil::stringToInt(ZD[16]);
    result=0;
    for(i=0;i<8;i++){
        result=result*256+data[i];
    
    }
    memset(buf,0,sizeof(buf));
    snprintf(buf,sizeof(buf),"%lld",result);
    str = buf;
    return str;
}

/** 当前电量累计的高32bit值焦尔 */
string  VoltameterLogic::getCountHValue()
{
    return "";
}

/** 当前电量累计的低32bit值焦尔 */
string  VoltameterLogic::getCountLValue()
{
    return "";
}

/**
 * 转换板通信错误
 *
 * @return 0为正常，1为通信错误
 */
string  VoltameterLogic::getIsPeripheralsCommunicationError()
{
    return ZD[17];
}

