//
//  SensorsFourInOneLogic.h
//  Service
//
//  Created by lz on 15/9/9.
//  Copyright (c) 2015年 新联锋科技. All rights reserved.
//

#ifndef __Service__SensorsFourInOneLogic__
#define __Service__SensorsFourInOneLogic__

#include <stdio.h>
#include "DeviceLogic.h"

class SensorsFourInOneLogic : public DeviceLogic
{
    
public:
    
    SensorsFourInOneLogic();
    
    ~SensorsFourInOneLogic();
    
    /*************************************** 功能设置 *************************************************/
    /** PM2.5开关设置 设置功能：power[1] */
    string setPM2_5Power(int power);
    
    /** 传感器电源控制 切断 上电 电源控制：power[0/1] 传感器ID sensorID : [1 温度、2湿度、3 甲醛、4 PM2.5] */
    string setSensorsPower(int power, int sensorID);
    
    /**
     * 主动上报频率设置 是否设置上报频率：responseFrequencyValid[0/1] 传感器ID responseID : [1 温度、2湿度、3 甲醛、4 PM2.5] 上报频率(单位
     * 秒)：responseFrequency
     */
    string setResponseFrequency(int responseFrequencyValid, int responseID, int responseFrequency);
    
    /*************************************** 状态查询 *************************************************/
    /** 获取 温度传感器ID */
    string getTemperatureSensorID();
    
    /** 获取 温度值是否有效 */
    string getTemperatureValueValid();
    
    /** 获取 温度传感器电源状态 */
    string getTemperatureSensorPowerStatus();
    
    /** 获取 上次读温度值时间 */
    string getTemperatureInterval();
    
    /** 获取 温度值 除以100 */
    string getTemperatureValue();
    
    /** 获取 湿度传感器ID */
    string getHumiditySensorID();
    
    /** 获取 湿度值是否有效 */
    string getHumidityValueValid();
    
    /** 获取 湿度传感器电源状态 */
    string getHumiditySensorPowerStatus();
    
    /** 获取 上次读湿度值时间 */
    string getHumidityInterval();
    
    /** 获取 湿度值 */
    string getHumidityValue();
    
    /** 获取 甲醛传感器ID */
    string getH2COSensorID();
    
    /** 获取 甲醛值是否有效 */
    string getH2COValueValid();
    
    /** 获取 甲醛传感器电源状态 */
    string getH2COSensorPowerStatus();
    
    /** 获取 上次读甲醛值时间 */
    string getH2COInterval();
    
    /** 获取 甲醛值 除以1000 */
    string getH2COValue();
    
    /** 获取 PM2.5传感器ID */
    string getPM2_5SensorID();
    
    /** 获取 PM2.5值是否有效 */
    string getPM2_5ValueValid();
    
    /** 获取 PM2.5传感器电源状态 */
    string getPM2_5SensorPowerStatus();
    
    /** 获取 上次读PM2.5值时间 */
    string getPM2_5Interval();
    
    /** 获取 PM2.5值 除以100 */
    string getPM2_5Value();
    
    /** 获取 CO2传感器ID */
    string getCO2SensorID();
    
    /** 获取 CO2值是否有效 */
    string getCO2ValueValid();
    
    /** 获取 CO2传感器电源状态 */
    string getCO2SensorPowerStatus();
    
    /** 获取 上次读CO2值时间 */
    string getCO2Interval();
    
    /** 获取 CO2值 */
    string getCO2Value();
    
    /**
     * 转换板通信错误
     * @return 0为正常，1为通信错误
     */
    string getIsPeripheralsCommunicationError();
};


#endif /* defined(__Service__SensorsFourInOneLogic__) */
