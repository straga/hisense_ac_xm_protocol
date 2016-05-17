//
//  SmartLightLogic.cpp
//  devices
//
//  Created by administratiors on 15/12/15.
//  Copyright © 2015年 xiaofangliang. All rights reserved.
//

#include "SmartLightLogic.h"
#include "IOTConstants.h"
#include "IOTUtil.h"
#include <sstream>


SmartLightLogic::SmartLightLogic()
{
    At_QureyStatus = "LightQuery";
    At_QueryFuntion = "LightGN";
    DEVICE_TYPE = 0x52;
    At_Status_Num = 15;
    At_Funtion_Num = 6;
    
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

SmartLightLogic::~SmartLightLogic()
{
    
}

/******************************** 功能设置 ********************************************/
/** 电源设置 此方法未实现 */
string SmartLightLogic::setPower(int power)
{
   string atcmd = IOTConstants::CMD_AT_MARK + "SetLightPwr" + IOTConstants::CMD_AT_EQUALS_SINGNAL
				+ deviceId + IOTConstants::PARAM_VALUE_SPLIT
				+ IOTUtil::intToString(power)
				+ IOTConstants::CMD_AT_WRAP;
    return	createNetBytes(atcmd);
}

/** 亮度设置：0~100 */
string SmartLightLogic::setBrightness(int brightnessValue)
{
    string atcmd = IOTConstants::CMD_AT_MARK + "SetBright" + IOTConstants::CMD_AT_EQUALS_SINGNAL
				+ deviceId + IOTConstants::PARAM_VALUE_SPLIT
				+ IOTUtil::intToString(brightnessValue)
				+ IOTConstants::CMD_AT_WRAP;
    return	createNetBytes(atcmd);
}

/** R G B 三元色设置 取值范围均为[0-255] */
string SmartLightLogic::setRGB(int redValue, int greenValue, int blueValue)
{
    string atcmd = IOTConstants::CMD_AT_MARK + "SetLightRGB" + IOTConstants::CMD_AT_EQUALS_SINGNAL
				+ deviceId + IOTConstants::PARAM_VALUE_SPLIT
				+ IOTUtil::intToString(redValue)
    + deviceId + IOTConstants::PARAM_VALUE_SPLIT
				+ IOTUtil::intToString(greenValue)
    + deviceId + IOTConstants::PARAM_VALUE_SPLIT
				+ IOTUtil::intToString(blueValue)
				+ IOTConstants::CMD_AT_WRAP;
    return	createNetBytes(atcmd);
}

/** 空气状况 3 优、2 良、1 一般 */
string SmartLightLogic::setAirQualityLevel(int airQualityLevel)
{
    string atcmd = IOTConstants::CMD_AT_MARK + "SetAirLevel" + IOTConstants::CMD_AT_EQUALS_SINGNAL
				+ deviceId + IOTConstants::PARAM_VALUE_SPLIT
				+ IOTUtil::intToString(airQualityLevel)
				+ IOTConstants::CMD_AT_WRAP;
    return	createNetBytes(atcmd);
}

/** 色温设置(0~65535) 此方法未实现 */
string SmartLightLogic::setColorTemperature(int colorTemperatureValue)
{
    string atcmd = IOTConstants::CMD_AT_MARK + "SetColorTemp" + IOTConstants::CMD_AT_EQUALS_SINGNAL
				+ deviceId + IOTConstants::PARAM_VALUE_SPLIT
				+ IOTUtil::intToString(colorTemperatureValue)
				+ IOTConstants::CMD_AT_WRAP;
    return	createNetBytes(atcmd);
}

// 新增 2015.11.12
/**
 * 设备状态 0 为正常，1 为掉线
 *
 * @param deviceStatus  0 为正常，1 为掉线
 * @return byte[]
 */
string SmartLightLogic::setDeviceStatus(int deviceStatus)
{
    string atcmd = IOTConstants::CMD_AT_MARK + "SetDevStat" + IOTConstants::CMD_AT_EQUALS_SINGNAL
				+ deviceId + IOTConstants::PARAM_VALUE_SPLIT
				+ IOTUtil::intToString(deviceStatus)
				+ IOTConstants::CMD_AT_WRAP;
    return	createNetBytes(atcmd);
}

/******************************** 状态查询 ********************************************/
/** 开关状态 此方法未实现 */
string SmartLightLogic::getPower()
{
     return ZD[0];
}

/** RGB 值是否有效 */
string SmartLightLogic::getRGBSetValid()
{
     return ZD[1];
}

/** 红色值 */
string SmartLightLogic::getRedValue()
{
     return ZD[2];
}

/** 绿色值 */
string SmartLightLogic::getGreenValue()
{
    return ZD[3];
}

/** 蓝色值 */
string SmartLightLogic::getBlueValue()
{
     return ZD[4];
}

/** 色温值是否有效 此方法未实现 */
string SmartLightLogic::getColorTemperatureValid()
{
     return ZD[5];
}

/** 色温值(0~65535) 此方法未实现 */
string SmartLightLogic::getColorTemperatureValue()
{
   
    int a = IOTUtil::stringToInt(ZD[6]);
    int b = IOTUtil::stringToInt(ZD[7]);
    return IOTUtil::intToString((a<<8)|b);
    
}

/** 亮度值是否有效 */
string SmartLightLogic::getBrightnessValid()
{
     return ZD[8];
}

/** 亮度 */
string SmartLightLogic::getBrightnessValue()
{
    int a = IOTUtil::stringToInt(ZD[9]);
    int b = IOTUtil::stringToInt(ZD[10]);
    return IOTUtil::intToString((a<<8)|b);
}

// 新增状态查询 2015.11.12
/**
 * 设备状态 0 为有效，1 为无效
 *
 * @return 0 为有效，1 为无效
 */
string SmartLightLogic::getDeviceStatusValid()
{
    return ZD[11];
}

/**
 * 设备状态 0 为正常，1 为掉线
 *
 * @return 0 为正常，1 为掉线
 */
string SmartLightLogic::getDeviceStatus()
{
    return ZD[12];
}

/**
 * 空气状况是否有效 0 为有效，1 为无效
 *
 * @return 0 为有效，1 为无效
 */
string SmartLightLogic::getAirStatusValid()
{
     return ZD[13];
}

/**
 * 空气状况 3 优、2 良、1 一般
 *
 * @return 3 优、2 良、1 一般
 */
string SmartLightLogic::getAirStatus()
{
     return ZD[14];
}

/**
 * 转换板通信错误
 *
 * @return 0为正常，1为通信错误
 */
string SmartLightLogic::getIsPeripheralsCommunicationError()
{
     return ZD[15];
}
