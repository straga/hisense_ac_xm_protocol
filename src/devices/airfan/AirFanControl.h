//
//  AirFanControl.h
//  Devices
//
//  Created by 肖芳亮 on 16/2/24.
//  Copyright © 2016年 XLF. All rights reserved.
//

#ifndef AirFanControl_h
#define AirFanControl_h

#include "DeviceControl.h"
#include "AirFanLogic.h"

class AirFanControl : public DeviceControl
{
    
private:
    
    AirFanLogic *airFanLogic;
    
public:
    
    AirFanControl(string deviceId);
    
    ~AirFanControl();
    /***************************** 获取使能位 *****************************/
    /**
     * 风量支持档位数
     */
    int getGNspeed();
    
    /**
     * 全热换气模式
     */
    int getGNfullheat();
    
    /**
     * 直通换气模式
     */
    int getGNdirect();
    
    /**
     * 室内回旋模式
     */
    int getGNindoor();
    
    /**
     * 普通定时模式
     */
    int getGNtiming();
    
    /**
     * 开关机控制位
     */
    int getGNpower();
    
    /**
     * EPPROM
     */
    int getGNifUpdateEEPROM();
    
    /**
     * 电量检测
     */
    int getGNbatteryIFdetection();
    
    /***************************** 获取状态位 *****************************/
    /**
     * 获取 风速 [weak/middle/strong/auto]
     */
    string getSpeed();
    
    /**
     * 获取电源 0 关，1 开
     */
    string getPower();
    
    /**
     * 是否待机
     */
    string getSuspendMode();
    
    /**
     * 获取 模式 [fullheat/direct/indoor/auto]
     */
    string getMode();
    
    /**
     * 是否有定时开关
     */
    string getIsTiming();
    
    /**
     * 定时开关时间
     */
    string getTimingTime();
    
    /**
     * 室外风机转速*10为实际转速，无此项时为1
     */
    string getOuterFanSpeed();
    
    /**
     * 室内风机转速*10为实际转速，无此项时为1
     */
    string getInnerFanSpeed();
    
    /**
     * 室内实际温度有效
     */
    string getInnerTempratureValid();
    
    /**
     * 室内实际湿度有效
     */
    string getInnerHumidityValid();
    
    /**
     * 室内侧二氧化碳 值 有效
     */
    string getInnerco2DensityValid();
    
    /**
     * 室外侧温度有效
     */
    string getOuterTempratureValid();
    
    /**
     * 室外侧湿度有效
     */
    string getOuterHumidityValid();
    
    /**
     * 室内温度值
     */
    string getInnerTemprature();
    
    /**
     * 室内湿度值
     */
    string getInnerRelativeHumidity();
    
    /**
     * 室外温度值
     */
    string getOuterTemprature();
    
    /**
     * 室外湿度值
     */
    string getOuterRelativeHumidity();
    
    /**
     * 室内CO2浓度
     */
    string getInnerCo2Solubility();
    
    /**
     * 过滤网更换提示
     */
    string getFilterIfReplace();
    
    /**
     * 室外风机故障
     */
    string getOuterFanIfFault();
    
    /**
     * 室内风机故障
     */
    string getInnerFanIfFault();
    
    /**
     * 室外侧温度传感器故障
     */
    string getOuterTemperatureSensorIfFault();
    
    /**
     * 室外侧湿度传感器故障
     */
    string getOuterHumiditySensorIfFault();
    
    /**
     * 二氧化碳传感器故障
     */
    string getCo2SensorIfFault();
    
    /**
     * 室内侧温度传感器故障
     */
    string getInnerTemperatureSensorFault();
    
    /**
     * 室内侧湿度传感器故障
     */
    string getInnerHumiditySensorFault();
    
    /***************************** 控制指令 *****************************/
    /**
     * 风速 设置功能:风量[weak/middle/strong/auto]，提示声[0/1]
     */
    string setSpeed(string speed, bool manualOrnot);
    
    /**
     * 电源 power : 设置功能:开机[0/1]，提示声[0/1]
     */
    string setpowerOn(bool isPowerOn, bool manualOrnot);
    
    /**
     * 模式 设置功能:模式[fullheat/direct/indoor/auto]，提示声[0/1]
     */
    string setMode(string mode, bool manualOrnot);
    
    /**
     * 定时开关机 设置功能:普通定时开关机[0.5h-23h],普通定时有效位[0/1]，提示声[0/1]
     * 定时时间格式严格为[1.0h,2.0h,3.0h,4.0h,5.0h,6.0h,7.0h,8.0h,9.0h,10h,11h,12h,13h,14,15h,16,17h,18h,19h,20h,21h,22,23h],
     */
    string setTiming(string hour, bool isOpen, bool manualOrnot);
    
    /**
     * 未知功能
     */
    string getStatus(bool manualOrnot);
    
    /**
     * Box 设置功能:开关机[0/1], 模式[fullheat/direct/indoor/auto]，风量[weak/middle/strong/auto]，提示声[0/1]
     */
    string SetHotFanSBox(bool on,string  Mode,string  WindSpeed_value, bool manualOrnot);
    
    /**
     * 解析AT指令
     */
    bool ParseResult(string result);
};

#endif /* AirFanControl_h */
