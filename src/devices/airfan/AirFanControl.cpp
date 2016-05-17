//
//  AirFanControl.cpp
//  Devices
//
//  Created by 肖芳亮 on 16/2/24.
//  Copyright © 2016年 XLF. All rights reserved.
//

#include "AirFanControl.h"
#include "IOTUtil.h"

AirFanControl::AirFanControl(string deviceId)
{
    airFanLogic = new AirFanLogic();
    airFanLogic->deviceId = deviceId;
    airFanLogic->deviceType = "airfan";
    devicesLogic = airFanLogic;
}

AirFanControl::~AirFanControl()
{
    if (airFanLogic)
    {
        delete airFanLogic;
    }
}

/**
 * 风量支持档位数
 */
int AirFanControl::getGNspeed()
{
    return airFanLogic->getGNspeed();
}

/**
 * 全热换气模式
 */
int AirFanControl::getGNfullheat()
{
    return airFanLogic->getGNfullheat();
}

/**
 * 直通换气模式
 */
int AirFanControl::getGNdirect()
{
    return airFanLogic->getGNdirect();
}

/**
 * 室内回旋模式
 */
int AirFanControl::getGNindoor()
{
    return airFanLogic->getGNindoor();
}

/**
 * 普通定时模式
 */
int AirFanControl::getGNtiming()
{
    return airFanLogic->getGNtiming();
}

/**
 * 开关机控制位
 */
int AirFanControl::getGNpower()
{
    return airFanLogic->getGNpower();
}

/**
 * EPPROM
 */
int AirFanControl::getGNifUpdateEEPROM()
{
    return airFanLogic->getGNifUpdateEEPROM();
}

/**
 * 电量检测
 */
int AirFanControl::getGNbatteryIFdetection()
{
    return airFanLogic->getGNbatteryIFdetection();
}

string AirFanControl::getSpeed()
{
    return airFanLogic->getSpeed();
}

string AirFanControl::getPower()
{
    return airFanLogic->getPower();
}

string AirFanControl::getSuspendMode()
{
    return airFanLogic->getSuspendMode();
}

string AirFanControl::getMode()
{
    return airFanLogic->getMode();
}

string AirFanControl::getIsTiming()
{
    return airFanLogic->getIsTiming();
}

string AirFanControl::getTimingTime()
{
    return airFanLogic->getTimingTime();
}

string AirFanControl::getOuterFanSpeed()
{
    return airFanLogic->getOuterFanSpeed();
}

string AirFanControl::getInnerFanSpeed()
{
    return airFanLogic->getInnerFanSpeed();
}

string AirFanControl::getInnerTempratureValid()
{
    return airFanLogic->getInnerFanSpeed();
}

string AirFanControl::getInnerHumidityValid()
{
    return airFanLogic->getInnerFanSpeed();
}

string AirFanControl::getInnerco2DensityValid()
{
    return airFanLogic->getInnerFanSpeed();
}

string AirFanControl::getOuterTempratureValid()
{
    return airFanLogic->getInnerFanSpeed();
}

string AirFanControl::getOuterHumidityValid()
{
    return airFanLogic->getInnerFanSpeed();
}

string AirFanControl::getInnerTemprature()
{
    return airFanLogic->getInnerTemprature();
}

string AirFanControl::getInnerRelativeHumidity()
{
    return airFanLogic->getInnerRelativeHumidity();
}

string AirFanControl::getOuterTemprature()
{
    return airFanLogic->getOuterTemprature();
}

string AirFanControl::getOuterRelativeHumidity()
{
    return airFanLogic->getOuterRelativeHumidity();
}

string AirFanControl::getInnerCo2Solubility()
{
    return airFanLogic->getCo2Solubility();
}

string AirFanControl::getFilterIfReplace()
{
    return airFanLogic->getFilterIfReplace();
}

string AirFanControl::getOuterFanIfFault()
{
    return airFanLogic->getOuterFanIfFault();
}

string AirFanControl::getInnerFanIfFault()
{
    return airFanLogic->getInnerFanIfFault();
}

string AirFanControl::getOuterTemperatureSensorIfFault()
{
    return airFanLogic->getOuterTemperatureSensorIfFault();
}

string AirFanControl::getOuterHumiditySensorIfFault()
{
    return airFanLogic->getOuterHumiditySensorIfFault();
}

string AirFanControl::getCo2SensorIfFault()
{
    return airFanLogic->getCo2SensorIfFault();
}

string AirFanControl::getInnerTemperatureSensorFault()
{
    return airFanLogic->getInnerTemperatureSensorFault();
}

string AirFanControl::getInnerHumiditySensorFault()
{
    return airFanLogic->getInnerHumiditySensorFault();
}

string AirFanControl::setSpeed(string speed, bool manualOrnot)
{
    if(airFanLogic != NULL)
    {
        return airFanLogic->setSpeed(speed, manualOrnot);
    }
    return NULL;
}

string AirFanControl::setpowerOn(bool isPowerOn, bool manualOrnot)
{
    if(airFanLogic != NULL)
    {
        return airFanLogic->setPower(isPowerOn, manualOrnot);
    }
    return NULL;
}

string AirFanControl::setMode(string mode, bool manualOrnot)
{
    if(airFanLogic != NULL)
    {
        return airFanLogic->setMode(mode, manualOrnot);
    }
    return NULL;
}

string AirFanControl::setTiming(string hour, bool isOpen, bool manualOrnot)
{
    if(airFanLogic != NULL)
    {
        return airFanLogic->setTiming(hour, isOpen,manualOrnot);
    }
    return NULL;
}

string AirFanControl::getStatus(bool manualOrnot)
{
    if(airFanLogic != NULL)
    {
        return airFanLogic->getStatus(manualOrnot);
    }
    return NULL;
}

string AirFanControl::SetHotFanSBox(bool on,string  Mode,string  WindSpeed_value, bool manualOrnot)
{
    if(NULL != airFanLogic)
    {
        string power = airFanLogic->getPower();
        string modeStatus = airFanLogic->getMode();
        string windSpeedStatus = airFanLogic->getSpeed();
        
        if(power == IOTUtil::intToString(on) && modeStatus == Mode && windSpeedStatus == WindSpeed_value )
        {
            return NULL;
        }
        
        return airFanLogic->SetHotFanSBOX( on,  Mode,  WindSpeed_value,  manualOrnot);
    }
    return NULL;
}

bool AirFanControl::ParseResult(string result)
{
    bool bresult = false;
    
    if( airFanLogic != NULL)
    {
        bresult = airFanLogic->parseAtCommand(result);
    }
    
    return bresult;
}

