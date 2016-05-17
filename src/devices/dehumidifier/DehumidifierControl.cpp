//
//  DehumidifierControl.cpp
//  Devices
//
//  Created by 肖芳亮 on 16/2/24.
//  Copyright © 2016年 XLF. All rights reserved.
//

#include "DehumidifierControl.h"

DehumidifierControl::DehumidifierControl(string deviceId)
{
    dehumidifierLogic = new DehumidifierLogic();
    dehumidifierLogic->deviceId = deviceId;
    dehumidifierLogic->deviceType = "dehumidifier";
    devicesLogic = dehumidifierLogic;
}

DehumidifierControl::~DehumidifierControl()
{
    if (dehumidifierLogic)
    {
        delete dehumidifierLogic;
    }
}

/**
 * 1.直接设置 开/关机
 * 取消普通定时,取消实时关机,取消快速冷热,取消睡眠,取消左右风,取消电热,取消节能,取消净化,取消双模,取消显示,取消亮度
 */
string DehumidifierControl::setDirctPower(int power, int manualOrnot)
{
    return dehumidifierLogic->setDirctPower(power, manualOrnot);
}

/**
 * 2.设置风速
 */
string DehumidifierControl::setWindSpeed(string speed, int manualOrnot)
{
    return dehumidifierLogic->setWindSpeed(speed, manualOrnot);
}

/**
 * 3.设置模式
 */
string DehumidifierControl::setMode(string mode, int manualOrnot)
{
    return dehumidifierLogic->setMode(mode, manualOrnot);
}

/**
 * 4.定时开关机
 */
string DehumidifierControl::setTimerControl(int enable, string time, int manualOrnot)
{
    return dehumidifierLogic->setTimerControl(enable, time, manualOrnot);
}

/**
 * 5.设置湿度
 */
string DehumidifierControl::setHumidity(int humidity, int manualOrnot)
{
    return dehumidifierLogic->setHumidity(humidity, manualOrnot);
}

/**
 * 6.设置温度
 */
string DehumidifierControl::setTemperature(int temperature, int manualOrnot)
{
    return dehumidifierLogic->setTemperature(temperature, manualOrnot);
}

/**
 * 7.设置开关电源
 */
string DehumidifierControl::setPower(int power, int manualOrnot)
{
    return dehumidifierLogic->setPower(power, manualOrnot);
}

/**
 * 8.设置开关电加热
 */
string DehumidifierControl::setEletricHeatControl(int isEletricHeatOn, int manualOrnot)
{
    return dehumidifierLogic->setEletricHeatControl(isEletricHeatOn, manualOrnot);
}

/**
 * 9.设置开关水泵
 */
string DehumidifierControl::setWaterPumpControl(int enable, int manualOrnot)
{
    return dehumidifierLogic->setWaterPumpControl(enable, manualOrnot);
}

/**
 * 10.设置开关负离子
 */
string DehumidifierControl::setNegativeIonsControl(int enable, int manualOrnot)
{
    return dehumidifierLogic->setNegativeIonsControl(enable, manualOrnot);
}

/**
 * 11.设置CSSBox
 */
string DehumidifierControl::setCSSBox(int on,string Mode,string WindSpeed_value,int humidity,int manualOrnot)
{
    return dehumidifierLogic->setCSSBox(on, Mode, WindSpeed_value, humidity, manualOrnot);
}

/********************************** 功能 **********************************/
/**
 * 智慧风
 */
int DehumidifierControl::getSmartWindFN()
{
    return dehumidifierLogic->getSmartWindFN();
}

/**
 * 高风
 */
int DehumidifierControl::getHighWindFN()
{
    return dehumidifierLogic->getHighWindFN();
}

/**
 * 中风
 */
int DehumidifierControl::getMediumWindFN()
{
    return dehumidifierLogic->getMediumWindFN();
}

/**
 * 低风
 */
int DehumidifierControl::getLowWindFN()
{
    return dehumidifierLogic->getLowWindFN();
}

/**
 * 运行模式 持续运行
 */
int DehumidifierControl::getContinueModeFN()
{
    return dehumidifierLogic->getContinueModeFN();
}

/**
 * 运行模式 正常运行
 */
int DehumidifierControl::getNormalModeFN()
{
    return dehumidifierLogic->getNormalModeFN();
}

/**
 * 运行模式 自动运行
 */
int DehumidifierControl::getAutoModeFN()
{
    return dehumidifierLogic->getAutoModeFN();
}

/**
 * 定时
 */
int DehumidifierControl::getTimerControlFN()
{
    return dehumidifierLogic->getTimerControlFN();
}

/**
 * 电加热
 */
int DehumidifierControl::getElectricHeatFN()
{
    return dehumidifierLogic->getElectricHeatFN();
}

/**
 * 电加热 温度
 */
int DehumidifierControl::getElectricHeatSetTemperatureFN()
{
    return dehumidifierLogic->getElectricHeatSetTemperatureFN();
}

/**
 * 室内湿度
 */
int DehumidifierControl::getIndoorHumidityFN()
{
    return dehumidifierLogic->getIndoorHumidityFN();
}

/**
 * 水泵
 */
int DehumidifierControl::getWaterPumpFN()
{
    return dehumidifierLogic->getWaterPumpFN();
}

/**
 * 负离子
 */
int DehumidifierControl::getAnionFN()
{
    return dehumidifierLogic->getAnionFN();
}

/**
 * 电量检测
 */
int DehumidifierControl::getElectronicDetectFN()
{
    return dehumidifierLogic->getElectronicDetectFN();
}

/**
 * 开停机
 */
int DehumidifierControl::getPowerFN()
{
    return dehumidifierLogic->getPowerFN();
}

/**
 * EEPROM可改写功能
 */
int DehumidifierControl::getEEPROMWriteFN()
{
    return dehumidifierLogic->getEEPROMWriteFN();
}

/**
 * 101#-0#第 7 字节预留位的控制功能
 */
int DehumidifierControl::get7ReserverdFN()
{
    return dehumidifierLogic->get7ReserverdFN();
}

/**
 * 101#-0#第 8 字节预留位的控制功能
 */
int DehumidifierControl::get8ReserverdFN()
{
    return dehumidifierLogic->get8ReserverdFN();
}

/********************************** 使能 **********************************/
/**
 * 智慧风
 */
void DehumidifierControl::setSmartWindFN(string value)
{
    dehumidifierLogic->setSmartWindFN(value);
}

/**
 * 高风
 */
void DehumidifierControl::setHighWindFN(string value)
{
    dehumidifierLogic->setHighWindFN(value);
}

/**
 * 中风
 */
void DehumidifierControl::setMediumWindFN(string value)
{
    dehumidifierLogic->setMediumWindFN(value);
}

/**
 * 低风
 */
void DehumidifierControl::setLowWindFN(string value)
{
    dehumidifierLogic->setLowWindFN(value);
}

/**
 * 运行模式 持续运行
 */
void DehumidifierControl::setContinueModeFN(string value)
{
    dehumidifierLogic->setContinueModeFN(value);
}

/**
 * 运行模式 正常运行
 */
void DehumidifierControl::setNormalModeFN(string value)
{
    dehumidifierLogic->setNormalModeFN(value);
}

/**
 * 运行模式 自动运行
 */
void DehumidifierControl::setAutoModeFN(string value)
{
    dehumidifierLogic->setAutoModeFN(value);
}

/**
 * 定时
 */
void DehumidifierControl::setTimerControlFN(string value)
{
    dehumidifierLogic->setTimerControlFN(value);
}

/**
 * 电加热
 */
void DehumidifierControl::setElectricHeatFN(string value)
{
    dehumidifierLogic->setElectricHeatFN(value);
}

/**
 * 电加热 温度
 */
void DehumidifierControl::setElectricHeatSetTemperatureFN(string value)
{
    dehumidifierLogic->setElectricHeatSetTemperatureFN(value);
}

/**
 * 室内湿度
 */
void DehumidifierControl::setIndoorHumidityFN(string value)
{
    dehumidifierLogic->setIndoorHumidityFN(value);
}

/**
 * 水泵
 */
void DehumidifierControl::setWaterPumpFN(string value)
{
    dehumidifierLogic->setWaterPumpFN(value);
}

/**
 * 负离子
 */
void DehumidifierControl::setAnionFN(string value)
{
    dehumidifierLogic->setAnionFN(value);
}

/**
 * 电量检测
 */
void DehumidifierControl::setElectronicDetectFN(string value)
{
    dehumidifierLogic->setElectronicDetectFN(value);
}

/**
 * 电源
 */
void DehumidifierControl::setPowerFN(string value)
{
    dehumidifierLogic->setPowerFN(value);
}

/**
 * EEPROM可改写功能
 */
void DehumidifierControl::setEEPROMWriteFN(string value)
{
    dehumidifierLogic->setEEPROMWriteFN(value);
}

/**
 * 7 字节预留位的控制功能
 */
void DehumidifierControl::set7ReserverdFN(string value)
{
    dehumidifierLogic->set7ReserverdFN(value);
}

/**
 * 8 字节预留位的控制功能
 */
void DehumidifierControl::set8ReserverdFN(string value)
{
    dehumidifierLogic->set8ReserverdFN(value);
}


/********************************** 获取设备状态 **********************************/
/**
 * 获取风速
 */
string DehumidifierControl::getWindSpeedStatus()
{
    return dehumidifierLogic->getWindSpeedStatus();
}

/**
 * 获取模式
 */
string DehumidifierControl::getModeStatus()
{
    return dehumidifierLogic->getModeStatus();
}

/**
 * 获取定时开关机控制
 */
string DehumidifierControl::getTimeStatus()
{
    return dehumidifierLogic->getTimeStatus();
}

/**
 * 获取定时开关机时间
 */
string DehumidifierControl::getTimerValue()
{
    return dehumidifierLogic->getTimerValue();
}

/**
 * 获取设置湿度
 */
string DehumidifierControl::getSettingHumidityValue()
{
    return dehumidifierLogic->getSettingHumidityValue();
}

/**
 * 获取电加热设定温度
 */
string DehumidifierControl::getEletricHeatingTempratureStatus()
{
    return dehumidifierLogic->getEletricHeatingTempratureStatus();
}

/**
 * 获取室内温度
 */
string DehumidifierControl::getIndoorTempStatus()
{
    return dehumidifierLogic->getIndoorTempStatus();
}

/**
 * 获取除湿机电源开关状态
 */
string DehumidifierControl::getPower()
{
    return dehumidifierLogic->getPower();
}

/**
 * 获取电加热功能开关状态
 */
string DehumidifierControl::getEletricHeatingStatus()
{
    return dehumidifierLogic->getEletricHeatingStatus();
}

/**
 * 获取水泵开关状态
 */
string DehumidifierControl::getWaterPumpStatus()
{
    return dehumidifierLogic->getWaterPumpStatus();
}

/**
 * 获取负离子开关状态
 */
string DehumidifierControl::getAnionStatus()
{
    return dehumidifierLogic->getAnionStatus();
}

/**
 * 本次命令之前有否红外和按键控制过
 */
string DehumidifierControl::getInfrarediKeypadControl()
{
    return dehumidifierLogic->getInfrarediKeypadControl();
}

/**
 * 本次命令之前有否 WIFI 控制过
 */
string DehumidifierControl::getWifiControl()
{
    return dehumidifierLogic->getWifiControl();
}

/**
 * 过滤网清洁告警
 */
string DehumidifierControl::getFilterNetCleanWarning()
{
    return dehumidifierLogic->getFilterNetCleanWarning();
}

/**
 * 湿度传感器故障
 */
string DehumidifierControl::getHumidSensorError()
{
    return dehumidifierLogic->getHumidSensorError();
}

/**
 *  管温传感器故障
 */
string DehumidifierControl::getPumpTempratureError()
{
    return dehumidifierLogic->getPumpTempratureError();
}

/**
 * 室内温度传感器故障
 */
string DehumidifierControl::getIndoorTempratureError()
{
    return dehumidifierLogic->getIndoorTempratureError();
}

/**
 * 水满警告
 */
string DehumidifierControl::getWaterFullWarning()
{
    return dehumidifierLogic->getWaterFullWarning();
}

/**
 * 水泵故障
 */
string DehumidifierControl::getWaterPumpWarning()
{
    return dehumidifierLogic->getWaterPumpWarning();
}

/**
 * 获取实际湿度
 */
string DehumidifierControl::getRealHumidityValue()
{
    return dehumidifierLogic->getRealHumidityValue();
}

/**
 * 解析的返回数据
 */
bool DehumidifierControl::parseAtCommand(string result)
{
    return dehumidifierLogic->parseAtCommand(result);
}
