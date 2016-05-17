//
//  SmartCurtainLogic.cpp
//  devices
//
//  Created by administratiors on 15/12/15.
//  Copyright © 2015年 xiaofangliang. All rights reserved.
//

#include "SmartCurtainLogic.h"
#include "IOTConstants.h"
#include "IOTUtil.h"
#include <sstream>

SmartCurtainLogic::SmartCurtainLogic()
{

    At_QureyStatus = "CurtainQuery";
    At_QueryFuntion = "CurtainGN";
    DEVICE_TYPE = 0x55;
    At_Status_Num = 5;
    At_Funtion_Num = 2;
    
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

SmartCurtainLogic::~SmartCurtainLogic()
{
    
}

/******************************** 功能设置 ********************************************/
/** 模式：Mode : 设置功能:0打开、1 关闭、2停止、3 重启 */
string SmartCurtainLogic::setMode(int mode)
{
    string atcmd = IOTConstants::CMD_AT_MARK + "CurtainSetMode" + IOTConstants::CMD_AT_EQUALS_SINGNAL
				+ deviceId + IOTConstants::PARAM_VALUE_SPLIT
				+ IOTUtil::intToString(mode)
				+ IOTConstants::CMD_AT_WRAP;
    return	createNetBytes(atcmd);
}

/** 定点控制：Pos : 设置功能:设置的定点位置(0~16)，全开位置是0，中间闭合位置是16，每次设置位置间隔距离应大于等于4个单位 */
// 需要同时设置"Mode":3
string SmartCurtainLogic::setPosition(int position)
{
    string atcmd = IOTConstants::CMD_AT_MARK + "CurtainSetPos" + IOTConstants::CMD_AT_EQUALS_SINGNAL
				+ deviceId + IOTConstants::PARAM_VALUE_SPLIT
				+ IOTUtil::intToString(position)
				+ IOTConstants::CMD_AT_WRAP;
    return	createNetBytes(atcmd);
}

/******************************** 状态查询 ********************************************/
/** Open or Close state 参数是否有效 */
string SmartCurtainLogic::getPowerStatusParameterIsValid()
{
     return ZD[0];
}

/** Open or Close state 开关状态 查一下，有异常 */
string SmartCurtainLogic::getPowerStatus()
{
     return ZD[1];
}

/** 定点位置 参数是否有效 */
string SmartCurtainLogic::getPositionParameterIsValid()
{
     return ZD[2];
}

/** 当前的定点位置 */
string SmartCurtainLogic::getPositionStatus()
{
    return ZD[3];
}

/**
 * 转换板通信错误
 * @return 0为正常，1为通信错误
 */
string SmartCurtainLogic::getIsPeripheralsCommunicationError()
{
   return ZD[4];
}
