//
//  SmartCurtainControl.cpp
//  devices
//
//  Created by administratiors on 15/12/15.
//  Copyright © 2015年 xiaofangliang. All rights reserved.
//

#include "SmartCurtainControl.h"

SmartCurtainControl::SmartCurtainControl(string deviceId)
{
    smartCurtainLogic = new SmartCurtainLogic();
    smartCurtainLogic->deviceId = deviceId;
    smartCurtainLogic->deviceType = "curtain";
    devicesLogic = smartCurtainLogic;
}

SmartCurtainControl::~SmartCurtainControl()
{
    if (smartCurtainLogic)
    {
        delete smartCurtainLogic;
    }
}

/*********************************** 功能设置 *******************************************/
/** 模式：Mode : 设置功能:0打开、1 关闭、2停止、3 重启 */
string SmartCurtainControl::setMode(int mode)
{
    return smartCurtainLogic->setMode(mode);
}

/** 定点控制：Pos : 设置功能:设置的定点位置(0~16)，全开位置是0，中间闭合位置是16，每次设置位置间隔距离应大于等于4个单位 */
string SmartCurtainControl::setPosition(int position)
{
    return smartCurtainLogic->setPosition(position);
}

/*********************************** 状态查询 *******************************************/
/** Open or Close state 参数是否有效 */
string SmartCurtainControl::getPowerStatusParameterIsValid()
{
    return smartCurtainLogic->getPowerStatusParameterIsValid();
}

/** Open or Close state 开关状态 */
string SmartCurtainControl::getPowerStatus()
{
    return smartCurtainLogic->getPowerStatus();
}

/** 定点位置 参数是否有效 */
string SmartCurtainControl::getPositionParameterIsValid()
{
    return smartCurtainLogic->getPositionParameterIsValid();
}

/** 当前的定点位置 */
string SmartCurtainControl::getPositionStatus()
{
    return smartCurtainLogic->getPositionStatus();
}

/**
 * 转换板通信错误
 *
 * @return 0为正常，1为通信错误
 */

string SmartCurtainControl::getIsPeripheralsCommunicationError()
{
    return smartCurtainLogic->getIsPeripheralsCommunicationError();
}
