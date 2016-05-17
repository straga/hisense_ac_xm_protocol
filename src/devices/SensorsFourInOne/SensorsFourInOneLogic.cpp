//
//  SensorsFourInOneLogic.cpp
//  Service
//
//  Created by lz on 15/9/9.
//  Copyright (c) 2015年 新联锋科技. All rights reserved.
//

#include "SensorsFourInOneLogic.h"
#include "IOTConstants.h"
#include "IOTUtil.h"
#include <sstream>

SensorsFourInOneLogic::SensorsFourInOneLogic()
{
    At_QureyStatus = "SensorQuery";
    At_QueryFuntion = "sensorGN";
    DEVICE_TYPE = 0x53;
    At_Status_Num = 35;
    At_Funtion_Num = 3;
    
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

SensorsFourInOneLogic::~SensorsFourInOneLogic()
{
    
}

/*************************************** 功能设置 *************************************************/
/** PM2.5开关设置 设置功能：power[1] */
string SensorsFourInOneLogic::setPM2_5Power(int power)
{
    string atcmd = IOTConstants::CMD_AT_MARK + "Pm2_5Ctl" + IOTConstants::CMD_AT_EQUALS_SINGNAL
    + deviceId + IOTConstants::PARAM_VALUE_SPLIT
    + IOTUtil::intToString(power)
    + IOTConstants::CMD_AT_WRAP;
    return	createNetBytes(atcmd);
}

/** 传感器电源控制 切断 上电 电源控制：power[0/1] 传感器ID sensorID : [1 温度、2湿度、3 甲醛、4 PM2.5] */
string SensorsFourInOneLogic::setSensorsPower(int power, int sensorID)
{
    string atcmd = IOTConstants::CMD_AT_MARK + "sensorPwr" + IOTConstants::CMD_AT_EQUALS_SINGNAL
				+ deviceId + IOTConstants::PARAM_VALUE_SPLIT
				+ IOTUtil::intToString(power)
				+ IOTConstants::PARAM_VALUE_SPLIT
				+ IOTUtil::intToString(sensorID)
				+ IOTConstants::CMD_AT_WRAP;
    return	createNetBytes(atcmd);
}

/**
 * 主动上报频率设置 是否设置上报频率：responseFrequencyValid[0/1] 传感器ID responseID : [1 温度、2湿度、3 甲醛、4 PM2.5] 上报频率(单位
 * 秒)：responseFrequency
 */
string SensorsFourInOneLogic::setResponseFrequency(int responseFrequencyValid, int responseID, int responseFrequency)
{
    string atcmd = IOTConstants::CMD_AT_MARK + "sensorPwr" + IOTConstants::CMD_AT_EQUALS_SINGNAL
				+ deviceId + IOTConstants::PARAM_VALUE_SPLIT
				+ IOTUtil::intToString(responseFrequencyValid)
				+ IOTConstants::PARAM_VALUE_SPLIT
				+ IOTUtil::intToString(responseID)
                + IOTConstants::PARAM_VALUE_SPLIT
				+ IOTUtil::intToString(responseFrequency)
				+ IOTConstants::CMD_AT_WRAP;
    return	createNetBytes(atcmd);
}

/*************************************** 状态查询 *************************************************/
/** 获取 温度传感器ID */
string SensorsFourInOneLogic::getTemperatureSensorID()
{
    return ZD[0];
}

/** 获取 温度值是否有效 */
string SensorsFourInOneLogic::getTemperatureValueValid()
{
    return ZD[1];
}

/** 获取 温度传感器电源状态 */
string SensorsFourInOneLogic::getTemperatureSensorPowerStatus()
{
    return  ZD[2];
}

/** 获取 上次读温度值时间 */
string SensorsFourInOneLogic::getTemperatureInterval()
{
    int a = IOTUtil::stringToInt(ZD[3]);
    int b = IOTUtil::stringToInt(ZD[4]);
    return IOTUtil::intToString((a<<8)|b);
}

/** 获取 温度值 除以100 */
string SensorsFourInOneLogic::getTemperatureValue()
{
    int a = IOTUtil::stringToInt(ZD[5]);
    int b = IOTUtil::stringToInt(ZD[6]);
    return IOTUtil::floatToString(((a<<8)|b)/100.0);
}

/** 获取 湿度传感器ID */
string SensorsFourInOneLogic::getHumiditySensorID()
{
    return ZD[7];
}

/** 获取 湿度值是否有效 */
string SensorsFourInOneLogic::getHumidityValueValid()
{
    return ZD[8];
}

/** 获取 湿度传感器电源状态 */
string SensorsFourInOneLogic::getHumiditySensorPowerStatus()
{
     return ZD[9];
}

/** 获取 上次读湿度值时间 */
string SensorsFourInOneLogic::getHumidityInterval()
{
    int a = IOTUtil::stringToInt(ZD[10]);
    int b = IOTUtil::stringToInt(ZD[11]);
    return IOTUtil::intToString((a<<8)|b);
}

/** 获取 湿度值 */
string SensorsFourInOneLogic::getHumidityValue()
{
    return ZD[12];
}

/** 获取 甲醛传感器ID */
string SensorsFourInOneLogic::getH2COSensorID()
{
    return ZD[13];
}

/** 获取 甲醛值是否有效 */
string SensorsFourInOneLogic::getH2COValueValid()
{
     return ZD[14];
}

/** 获取 甲醛传感器电源状态 */
string SensorsFourInOneLogic::getH2COSensorPowerStatus()
{
    return ZD[15];
}

/** 获取 上次读甲醛值时间 */
string SensorsFourInOneLogic::getH2COInterval()
{
    int a = IOTUtil::stringToInt(ZD[16]);
    int b = IOTUtil::stringToInt(ZD[17]);
    return IOTUtil::intToString((a<<8)|b);
}

/** 获取 甲醛值 除以1000 */
string SensorsFourInOneLogic::getH2COValue()
{
    int a = IOTUtil::stringToInt(ZD[18]);
    int b = IOTUtil::stringToInt(ZD[19]);
    return IOTUtil::floatToString(((a<<8)|b)/1000.0);
}

/** 获取 PM2.5传感器ID */
string SensorsFourInOneLogic::getPM2_5SensorID()
{
    return ZD[20];
}

/** 获取 PM2.5值是否有效 */
string SensorsFourInOneLogic::getPM2_5ValueValid()
{
   return ZD[21];
}

/** 获取 PM2.5传感器电源状态 */
string SensorsFourInOneLogic::getPM2_5SensorPowerStatus()
{
   return ZD[22];
}

/** 获取 上次读PM2.5值时间 */
string SensorsFourInOneLogic::getPM2_5Interval()
{
    int a = IOTUtil::stringToInt(ZD[23]);
    int b = IOTUtil::stringToInt(ZD[24]);
    return IOTUtil::intToString((a<<8)|b);
}

/** 获取 PM2.5值 除以100 */
string SensorsFourInOneLogic::getPM2_5Value()
{
    int a = IOTUtil::stringToInt(ZD[25]);
    int b = IOTUtil::stringToInt(ZD[26]);
    return IOTUtil::floatToString(((a<<8)|b)/100.0);
}

/** 获取 CO2传感器ID */
string SensorsFourInOneLogic::getCO2SensorID()
{
    return ZD[27];
}

/** 获取 CO2值是否有效 */
string SensorsFourInOneLogic::getCO2ValueValid()
{
    return ZD[28];
}

/** 获取 CO2传感器电源状态 */
string SensorsFourInOneLogic::getCO2SensorPowerStatus()
{
    return ZD[29];
}

/** 获取 上次读CO2值时间 */
string SensorsFourInOneLogic::getCO2Interval()
{
    int a = IOTUtil::stringToInt(ZD[30]);
    int b = IOTUtil::stringToInt(ZD[31]);
    return IOTUtil::intToString((a<<8)|b);
}

/** 获取 CO2值 */
string SensorsFourInOneLogic::getCO2Value()
{
    int a = IOTUtil::stringToInt(ZD[32]);
    int b = IOTUtil::stringToInt(ZD[33]);
    return IOTUtil::intToString(((a<<8)|b));
}

/**
 * 转换板通信错误
 */
string SensorsFourInOneLogic::getIsPeripheralsCommunicationError()
{
    return ZD[34];
}

