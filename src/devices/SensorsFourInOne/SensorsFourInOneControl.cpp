//
//  SensorsFourInOneControl.cpp
//  Service
//
//  Created by lz on 15/9/9.
//  Copyright (c) 2015年 新联锋科技. All rights reserved.
//

#include "SensorsFourInOneControl.h"

SensorsFourInOneControl::SensorsFourInOneControl(string deviceId)
{
    sensorsFourInOneLogic = new SensorsFourInOneLogic();
    sensorsFourInOneLogic->deviceId = deviceId;
    sensorsFourInOneLogic->deviceType = "sensor";
    devicesLogic = sensorsFourInOneLogic;
}

SensorsFourInOneControl::~SensorsFourInOneControl()
{
    if(sensorsFourInOneLogic)
    {
        delete sensorsFourInOneLogic;
    }
}

/** PM2.5开关设置 设置功能：power[1] */
string SensorsFourInOneControl::setPM2_5Power(int power)
{
    return sensorsFourInOneLogic->setPM2_5Power(power);
}

/** 传感器电源控制 切断 上电 电源控制：power[0/1] 传感器ID: [1 温度、2湿度、3 甲醛、4 PM2.5] */
string SensorsFourInOneControl::setSensorsPower(int power, int SensorID)
{
    return sensorsFourInOneLogic->setSensorsPower(power, SensorID);
}

/**
 * 主动上报频率设置 是否设置上报频率：responseFrequencyValid[0/1] 传感器ID responseID : [1 温度、2湿度、3 甲醛、4 PM2.5] 上报频率(单位
 * 秒)：responseFrequency
 */
string SensorsFourInOneControl::setResponseFrequency(int responseFrequencyValid, int responseID, int responseFrequency)
{
    return sensorsFourInOneLogic->setResponseFrequency(responseFrequencyValid, responseID, responseFrequency);
}

/*************************************** 状态查询 *************************************************/
/** 获取 温度传感器ID */
string SensorsFourInOneControl::getTemperatureSensorID()
{
    return sensorsFourInOneLogic->getTemperatureSensorID();
}

/** 获取 温度值是否有效 */
string SensorsFourInOneControl::getTemperatureValueValid()
{
    return sensorsFourInOneLogic->getTemperatureValueValid();
}

/** 获取 温度传感器电源状态 */
string SensorsFourInOneControl::getTemperatureSensorPowerStatus()
{
    return sensorsFourInOneLogic->getTemperatureSensorPowerStatus();
}

/** 获取 上次读温度值时间 */
string SensorsFourInOneControl::getTemperatureInterval()
{
    return sensorsFourInOneLogic->getTemperatureInterval();
}

/** 获取 温度值 */
string SensorsFourInOneControl::getTemperatureValue()
{
    return sensorsFourInOneLogic->getTemperatureValue();
}

/** 获取 湿度传感器ID */
string SensorsFourInOneControl::getHumiditySensorID()
{
    return sensorsFourInOneLogic->getHumiditySensorID();
}

/** 获取 湿度值是否有效 */
string SensorsFourInOneControl::getHumidityValueValid()
{
    return sensorsFourInOneLogic->getHumidityValueValid();
}

/** 获取 湿度传感器电源状态 */
string SensorsFourInOneControl::getHumiditySensorPowerStatus()
{
    return sensorsFourInOneLogic->getHumiditySensorPowerStatus();
}

/** 获取 上次读湿度值时间 */
string SensorsFourInOneControl::getHumidityInterval()
{
    return sensorsFourInOneLogic->getHumidityInterval();
}

/** 获取 湿度值 */
string SensorsFourInOneControl::getHumidityValue()
{
    return sensorsFourInOneLogic->getHumidityValue();
}

/** 获取 甲醛传感器ID */
string SensorsFourInOneControl::getH2COSensorID()
{
    return sensorsFourInOneLogic->getH2COSensorID();
}

/** 获取 甲醛值是否有效 */
string SensorsFourInOneControl::getH2COValueValid()
{
    return sensorsFourInOneLogic->getH2COValueValid();
}

/** 获取 甲醛传感器电源状态 */
string SensorsFourInOneControl::getH2COSensorPowerStatus()
{
    return sensorsFourInOneLogic->getH2COSensorPowerStatus();
}

/** 获取 上次读甲醛值时间 */
string SensorsFourInOneControl::getH2COInterval()
{
    return sensorsFourInOneLogic->getH2COInterval();
}

/** 获取 甲醛值 */
string SensorsFourInOneControl::getH2COValue()
{
    return sensorsFourInOneLogic->getH2COValue();
}

/** 获取 PM2.5传感器ID */
string SensorsFourInOneControl::getPM2_5SensorID()
{
    return sensorsFourInOneLogic->getPM2_5SensorID();
}

/** 获取 PM2.5值是否有效 */
string SensorsFourInOneControl::getPM2_5ValueValid()
{
    return sensorsFourInOneLogic->getPM2_5ValueValid();
}

/** 获取 PM2.5传感器电源状态 */
string SensorsFourInOneControl::getPM2_5SensorPowerStatus()
{
    return sensorsFourInOneLogic->getPM2_5SensorPowerStatus();
}

/** 获取 上次读PM2.5值时间 */
string SensorsFourInOneControl::getPM2_5Interval()
{
    return sensorsFourInOneLogic->getPM2_5Interval();
}

/** 获取 PM2.5值 */
string SensorsFourInOneControl::getPM2_5Value()
{
    return sensorsFourInOneLogic->getPM2_5Value();
}

/** 获取 CO2传感器ID */
string SensorsFourInOneControl::getCO2SensorID()
{
    return sensorsFourInOneLogic->getCO2SensorID();
}

/** 获取 CO2值是否有效 */
string SensorsFourInOneControl::getCO2ValueValid()
{
    return sensorsFourInOneLogic->getCO2ValueValid();
}

/** 获取 CO2传感器电源状态 */
string SensorsFourInOneControl::getCO2SensorPowerStatus()
{
    return sensorsFourInOneLogic->getCO2SensorPowerStatus();
}

/** 获取 上次读CO2值时间 */
string SensorsFourInOneControl::getCO2Interval()
{
    return sensorsFourInOneLogic->getCO2Interval();
}

/** 获取 CO2值 */
string SensorsFourInOneControl::getCO2Value()
{
    return sensorsFourInOneLogic->getCO2Value();
}

/**
 * 转换板通信错误
 *
 * @return
 *         0为正常，1为通信错误
 */
string SensorsFourInOneControl::getIsPeripheralsCommunicationError()
{
    return sensorsFourInOneLogic->getIsPeripheralsCommunicationError();
}

