//
//  AirFanLogic.cpp
//  Devices
//
//  Created by 肖芳亮 on 16/2/24.
//  Copyright © 2016年 XLF. All rights reserved.
//

#include "AirFanLogic.h"
#include "IOTUtil.h"
#include "IOTConstants.h"

AirFanLogic::AirFanLogic()
{
    At_QureyStatus = "QRZD";
    At_QueryFuntion = "QRGN";
    DEVICE_TYPE = 0x19;
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

AirFanLogic::~AirFanLogic()
{
    
}


/***************************** 获取使能位 *****************************/
/**
 * 风量支持档位数
 */
int AirFanLogic::getGNspeed()
{
    return GN[0];
}

/**
 * 全热换气模式
 */
int AirFanLogic::getGNfullheat()
{
    return GN[1];
}

/**
 * 直通换气模式
 */
int AirFanLogic::getGNdirect()
{
    return GN[2];
}

/**
 * 室内回旋模式
 */
int AirFanLogic::getGNindoor()
{
    return GN[3];
}

/**
 * 普通定时模式
 */
int AirFanLogic::getGNtiming()
{
    return GN[4];
}

/**
 * 开关机控制位
 */
int AirFanLogic::getGNpower()
{
    return GN[5];
}

/**
 * EPPROM
 */
int AirFanLogic::getGNifUpdateEEPROM()
{
    return GN[6];
}

/**
 * 电量检测
 */
int AirFanLogic::getGNbatteryIFdetection()
{
    return GN[7];
}


/***************************** 获取状态位 *****************************/
/**
 * 获取 风速 [weak/middle/strong/auto]
 */
string AirFanLogic::getSpeed()
{
    return ZD[0];
}

/**
 * 获取电源 0 关，1 开
 */
string AirFanLogic::getPower()
{
    return ZD[1];
}

/**
 * 是否待机
 */
string AirFanLogic::getSuspendMode()
{
    return ZD[2];
}

/**
 * 获取 模式 [fullheat/direct/indoor/auto]
 */
string AirFanLogic::getMode()
{
    return ZD[3];
}

/**
 * 是否有定时开关
 */
string AirFanLogic::getIsTiming()
{
    return ZD[4];
}

/**
 * 定时开关时间
 */
string AirFanLogic::getTimingTime()
{
    return ZD[5];
}

/**
 * 室外风机转速*10为实际转速，无此项时为1
 */
string AirFanLogic::getOuterFanSpeed()
{
    return ZD[6];
}

/**
 * 室内风机转速*10为实际转速，无此项时为1
 */
string AirFanLogic::getInnerFanSpeed()
{
    return ZD[7];
}

/**
 * 室内实际温度有效
 */
string AirFanLogic::getInnerTempratureValid()
{
    return ZD[8];
}

/**
 * 室内实际湿度有效
 */
string AirFanLogic::getInnerHumidityValid()
{
    return ZD[9];
}

/**
 * 室内侧二氧化碳 值 有效
 */
string AirFanLogic::getInnerco2DensityValid()
{
    return ZD[10];
}

/**
 * 室外侧温度有效
 */
string AirFanLogic::getOuterTempratureValid()
{
    return ZD[11];
}

/**
 * 室外侧湿度有效
 */
string AirFanLogic::getOuterHumidityValid()
{
    return ZD[12];
}

/**
 * 室内温度值
 */
string AirFanLogic::getInnerTemprature()
{
    return ZD[13];
}

/**
 * 室内湿度值
 */
string AirFanLogic::getInnerRelativeHumidity()
{
    return ZD[14];
}

/**
 * 室外温度值
 */
string AirFanLogic::getOuterTemprature()
{
    return ZD[15];
}

/**
 * 室外湿度值
 */
string AirFanLogic::getOuterRelativeHumidity()
{
    return ZD[16];
}

/**
 * 室内CO2浓度
 */
string AirFanLogic::getCo2Solubility()
{
    int zd17 = 0;
    int zd18 = 0;
    
    zd17 = IOTUtil::stringToInt(ZD[17]);
    zd18 = IOTUtil::stringToInt(ZD[18]);
    
    int value = zd17 * 256 + zd18;
    
    return IOTUtil::intToString(value);
}

/**
 * 过滤网更换提示
 */
string AirFanLogic::getFilterIfReplace()
{
    return ZD[19];
}

/**
 * 室外风机故障
 */
string AirFanLogic::getOuterFanIfFault()
{
    return ZD[20];
}

/**
 * 室内风机故障
 */
string AirFanLogic::getInnerFanIfFault()
{
    return ZD[21];
}

/**
 * 室外侧温度传感器故障
 */
string AirFanLogic::getOuterTemperatureSensorIfFault()
{
    return ZD[22];
}

/**
 * 室外侧湿度传感器故障
 */
string AirFanLogic::getOuterHumiditySensorIfFault()
{
    return ZD[23];
}

/**
 * 二氧化碳传感器故障
 */
string AirFanLogic::getCo2SensorIfFault()
{
    return ZD[24];
}

/**
 * 室内侧温度传感器故障
 */
string AirFanLogic::getInnerTemperatureSensorFault()
{
    return ZD[25];
}

/**
 * 室内侧湿度传感器故障
 */
string AirFanLogic::getInnerHumiditySensorFault()
{
    return ZD[26];
}

/***************************** 控制指令 *****************************/
/**
 * 风速 设置功能:风量[weak/middle/strong/auto]，提示声[0/1]
 */
string AirFanLogic::setSpeed(string speed, bool manualOrnot)
{
    ZD[0] = speed;
    string atCmd = IOTConstants::CMD_AT_MARK + "QRSD" +
				IOTConstants::CMD_AT_EQUALS_SINGNAL + deviceId + IOTConstants::PARAM_VALUE_SPLIT +
				speed  + IOTConstants::PARAM_VALUE_SPLIT +
				IOTUtil::intToString(manualOrnot) + IOTConstants::CMD_AT_WRAP;
    return createNetBytes(atCmd);
}

/**
 * 电源 power : 设置功能:开机[0/1]，提示声[0/1]
 */
string AirFanLogic::setPower(bool isPowerOn, bool manualOrnot)
{
    ZD[1] = IOTUtil::intToString(isPowerOn);
    string atCmd = IOTConstants::CMD_AT_MARK + "QRKJ" +
				IOTConstants::CMD_AT_EQUALS_SINGNAL + deviceId + IOTConstants::PARAM_VALUE_SPLIT +
				IOTUtil::intToString(isPowerOn)  + IOTConstants::PARAM_VALUE_SPLIT +
				IOTUtil::intToString(manualOrnot) + IOTConstants::CMD_AT_WRAP;
    return createNetBytes(atCmd);
}

/**
 * 模式 设置功能:模式[fullheat/direct/indoor/auto]，提示声[0/1]
 */
string AirFanLogic::setMode(string mode, bool manualOrnot)
{
    ZD[2] = mode;
    string atCmd =  IOTConstants::CMD_AT_MARK + "QRMS" +
				IOTConstants::CMD_AT_EQUALS_SINGNAL + deviceId + IOTConstants::PARAM_VALUE_SPLIT +
				mode  + IOTConstants::PARAM_VALUE_SPLIT +
				IOTUtil::intToString(manualOrnot) + IOTConstants::CMD_AT_WRAP;
    return createNetBytes(atCmd);
}

/**
 * 定时开关机 设置功能:普通定时开关机[0.5h-23h],普通定时有效位[0/1]，提示声[0/1]
 * 定时时间格式严格为[1.0h,2.0h,3.0h,4.0h,5.0h,6.0h,7.0h,8.0h,9.0h,10h,11h,12h,13h,14,15h,16,17h,18h,19h,20h,21h,22,23h],
 */
string AirFanLogic::setTiming(string hour, bool isOpen,bool manualOrnot)
{
    ZD[3] = IOTUtil::intToString(isOpen);
    if(isOpen)
    {
        ZD[4] = hour;
        string atCmd = IOTConstants::CMD_AT_MARK + "QRDS" +
        IOTConstants::CMD_AT_EQUALS_SINGNAL + deviceId + IOTConstants::PARAM_VALUE_SPLIT +
        hour + IOTConstants::PARAM_VALUE_SPLIT +
        IOTUtil::intToString(isOpen) + IOTConstants::PARAM_VALUE_SPLIT +
        IOTUtil::intToString(manualOrnot) + IOTConstants::CMD_AT_WRAP;
        return createNetBytes(atCmd);
    }
    
    ZD[4] = "off";
    string atCmd = IOTConstants::CMD_AT_MARK + "QRDS" +
    IOTConstants::CMD_AT_EQUALS_SINGNAL + deviceId + IOTConstants::PARAM_VALUE_SPLIT +
    "off" + IOTConstants::PARAM_VALUE_SPLIT +
    IOTUtil::intToString(isOpen) + IOTConstants::PARAM_VALUE_SPLIT +
    IOTUtil::intToString(manualOrnot) + IOTConstants::CMD_AT_WRAP;
    return createNetBytes(atCmd);
}

/**
 * 未知功能
 */
string AirFanLogic::getStatus(bool manualOrnot)
{
    string atCmd = IOTConstants::CMD_AT_MARK + "QRZD" +
				IOTConstants::CMD_AT_EQUALS_SINGNAL + deviceId + IOTConstants::PARAM_VALUE_SPLIT +
				"?"  + IOTConstants::PARAM_VALUE_SPLIT +
				IOTUtil::intToString(manualOrnot) + IOTConstants::CMD_AT_WRAP;
    return createNetBytes(atCmd);
}

/**
 * Box 设置功能:开关机[0/1], 模式[fullheat/direct/indoor/auto]，风量[weak/middle/strong/auto]，提示声[0/1]
 */
string AirFanLogic::SetHotFanSBOX(bool on,string  Mode,string  WindSpeed_value, bool manualOrnot)
{
    ZD[1] = IOTUtil::intToString(on);
    ZD[3] = Mode;
    ZD[0] = WindSpeed_value;
    
    string atCmd = IOTConstants::CMD_AT_MARK  + "QRSBOX" + IOTConstants::CMD_AT_EQUALS_SINGNAL + deviceId + IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(on) +IOTConstants::PARAM_VALUE_SPLIT + Mode
    + IOTConstants::PARAM_VALUE_SPLIT + WindSpeed_value
    + IOTConstants::PARAM_VALUE_SPLIT  + IOTUtil::intToString(manualOrnot) + IOTConstants::CMD_AT_WRAP;
    return createNetBytes(atCmd);
}

/**
 * 解析AT指令
 */
bool AirFanLogic::parseAtCommand(string result)
{
    return false;
}

