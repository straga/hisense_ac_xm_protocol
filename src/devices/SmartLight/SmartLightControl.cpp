//
//  SmartLightControl.cpp
//  devices
//
//  Created by administratiors on 15/12/15.
//  Copyright © 2015年 xiaofangliang. All rights reserved.
//

#include "SmartLightControl.h"

SmartLightControl::SmartLightControl(string deviceId)
{
    smartCurtainLogic = new SmartLightLogic();
    smartCurtainLogic->deviceId = deviceId;
    smartCurtainLogic->deviceType = "smartlight";
    devicesLogic = smartCurtainLogic;
}

SmartLightControl::~SmartLightControl()
{
    if (smartCurtainLogic)
    {
        delete smartCurtainLogic;
    }
}

/*********************************** 功能设置 *******************************************/
/** 电源设置 此方法未实现 */
string  SmartLightControl::setPower(int power)
{
   
    return smartCurtainLogic->setPower(power);
   
}

/** 亮度设置：0~100 */
string  SmartLightControl::setBrightness(int brightnessValue)
{
   
    return smartCurtainLogic->setBrightness(brightnessValue);
   
}

/** R G B 三元色设置 取值范围均为[0-255] */
string  SmartLightControl::setRGB(int redValue, int greenValue, int blueValue)
{
   
    return smartCurtainLogic->setRGB(redValue, greenValue, blueValue);
   
}

/** 空气状况 3 优、2 良、1 一般 */
string  SmartLightControl::setAirQualityLevel(int airQualityLevel)
{
  
    return smartCurtainLogic->setAirQualityLevel(airQualityLevel);
   
}

/** 色温设置(0~65535) 此方法未实现 */
string  SmartLightControl::setColorTemperature(int colorTemperatureValue)
{
    
    return smartCurtainLogic->setColorTemperature(colorTemperatureValue);
   
}

// 新增 2015.11.12
/**
 * 设备状态 0 为正常，1 为掉线
 *
 * @param deviceStatus 0 为正常，1 为掉线
 * @return byte[]
 */
string  SmartLightControl::setDeviceStatus(int deviceStatus)
{
    return smartCurtainLogic->setDeviceStatus(deviceStatus);
}

/*********************************** 状态查询 *******************************************/
/** 开关状态 此方法未实现 */
string SmartLightControl::getPower()
{
    return smartCurtainLogic->getPower();
}

/** RGB 值是否有效 */
string SmartLightControl::getRGBSetValid()
{
    return smartCurtainLogic->getRGBSetValid();
}

/** 红色值 */
string SmartLightControl::getRedValue()
{
    return smartCurtainLogic->getRedValue();
}

/** 绿色值 */
string SmartLightControl::getGreenValue()
{
    return smartCurtainLogic->getGreenValue();
}

/** 蓝色值 */
string SmartLightControl::getBlueValue()
{
    return smartCurtainLogic->getBlueValue();
}

/** 色温值是否有效 此方法未实现 */
string SmartLightControl::getColorTemperatureValid()
{
    return smartCurtainLogic->getColorTemperatureValid();
}

/** 色温值(0~65535) 此方法未实现 */
string SmartLightControl::getColorTemperatureValue()
{
    return smartCurtainLogic->getColorTemperatureValue();
}

/** 亮度值是否有效 */
string SmartLightControl::getBrightnessValid()
{
    return smartCurtainLogic->getBrightnessValid();
}

/** 亮度 */
string SmartLightControl::getBrightnessValue()
{
    return smartCurtainLogic->getBrightnessValue();
}

// 新增状态查询 2015.11.12
/**
 * 设备状态 0 为有效，1 为无效
 *
 * @return 0 为有效，1 为无效
 */
string SmartLightControl::getDeviceStatusValid()
{
    return smartCurtainLogic->getDeviceStatusValid();
}

/**
 * 设备状态 0 为正常，1 为掉线
 *
 * @return  0 为正常，1 为掉线
 */
string SmartLightControl::getDeviceStatus()
{
    return smartCurtainLogic->getDeviceStatus();
}

/**
 * 空气状况是否有效 0 为有效，1 为无效
 *
 * @return 0 为有效，1 为无效
 */
string SmartLightControl::getAirStatusValid()
{
    return smartCurtainLogic->getAirStatusValid();
}

/**
 * 空气状况 3 优、2 良、1 一般
 *
 * @return 3 优、2 良、1 一般
 */
string SmartLightControl::getAirStatus()
{
    return smartCurtainLogic->getAirStatus();
}

/**
 * 转换板通信错误
 *
 * @return 0为正常，1为通信错误
 */
string SmartLightControl::getIsPeripheralsCommunicationError()
{
    return smartCurtainLogic->getIsPeripheralsCommunicationError();
}
