//
//  VoltameterControl.cpp
//  devices
//
//  Created by administratiors on 15/12/15.
//  Copyright © 2015年 xiaofangliang. All rights reserved.
//
#include "VoltameterControl.h"

VoltameterControl::VoltameterControl(string deviceId)
{
    voltameterLogic = new VoltameterLogic();
    voltameterLogic->deviceId = deviceId;
    voltameterLogic->deviceType = "voltameter";
    devicesLogic = voltameterLogic;
}

VoltameterControl::~VoltameterControl()
{
    if (voltameterLogic)
    {
        delete voltameterLogic;
    }
}

/** 总的电源开关 */
string VoltameterControl::setPower(int power)
{
    return voltameterLogic->setPower(power);
}

/** 电量统计清0 1清零，0不清零 */
string VoltameterControl::setResetCount(int isResetCount)
{
    return voltameterLogic->setResetCount(isResetCount);
}

/** 总电源开关状态 */
string VoltameterControl::getPower()
{
    return voltameterLogic->getPower();
}

/** 电流值uA */
string VoltameterControl::getCurrentValue()
{
    return voltameterLogic->getCurrentValue();
}

/** 电压值mV */
string VoltameterControl::getVoltageValue()
{
    return voltameterLogic->getCurrentValue();
}

/**
 * 整个电量值的统计用64位数据表示，以大端字节序存储
 * 统计时使用 (PCountH * 0xffffffff)+PCountL得到最终结果，单位焦尔
 */
/** 电量值的统计 */
string VoltameterControl::getVoltameterValue()
{
    return voltameterLogic->getVoltameterValue();
}

/**
 * 转换板通信错误
 *
 * @return  0为正常，1为通信错误
 */
string VoltameterControl::getIsPeripheralsCommunicationError()
{
    return voltameterLogic->getIsPeripheralsCommunicationError();
}

