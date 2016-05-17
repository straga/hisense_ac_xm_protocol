//
//  AirCleanerLogic.hpp
//  Devices
//
//  Created by 肖芳亮 on 16/2/24.
//  Copyright © 2016年 XLF. All rights reserved.
//

#ifndef AirCleanerLogic_h
#define AirCleanerLogic_h

#include <stdio.h>
#include <string>
#include <vector>
#include "DeviceLogic.h"

using namespace::std;

class AirCleanerLogic : public DeviceLogic
{
    
private:
    
    
    
public:
    
    AirCleanerLogic();
    
    ~AirCleanerLogic();
    
    void refreshFn();
    
    bool checkError();
    
    /******************************* 设备控制 *******************************/
    /*开/关机*/
    string DirctSetPower(string devid, bool on, bool manualOrnot);
    
    // 1设置净化速度
    string SetWindSpeed(string speed, bool manualOrnot);
    
    // 2设置净化模式
    string SetMode(string mode, bool manualOrnot);
    
    // 3设置定时开关机
    string TimerControl(bool enable, string time, bool manualOrnot);
    
    // 开关电源
    string setPower(bool power, bool manualOrnot);
    
    // 开关儿童锁
    string ChildLock(bool power, bool manualOrnot);
    
    // 开关水离子
    string WaterIon(bool power, bool manualOrnot);
    
    // 开关加湿器
    string Humidification(bool power,bool manualOrnot);
    
    // 加湿器湿度设置
    string HumidificationSet(int  humidity_value,bool manualOrnot);
    
    /*设置AirCleanerSBox*/
    string SetAirCleanerSBox(bool power_on,string Mode,string WindSpeed_value,bool jsj_on,string humdity_value,bool manualOrnot);
    
    /******************************* 功能使能状态 *******************************/
    int GetJHFN(int offset);
    
    // 1净化速度状态-自动功能，
    int GetCleanSpeedAutoFN();
    
    // 2净化速度状态-净烟功能 ，
    int GetCleanSpeedDelSmokeFN();
    
    // 3净化速度状态-高风功能
    int GetCleanSpeedHighFN();
    
    // 4净化速度状态-中风功能，
    int GetCleanSpeedMiddleFN();
    
    // 5净化速度状态-低风功能，
    int GetCleanSpeedLowFN();
    
    // 6净化模式状态-睡眠功能，
    int GetCleanModeSleepFN();
    
    // 7净化模式状态-静音功能，
    int GetCleanModeMuteFN();
    
    // 8净化模式状态-智能功能，
    int GetCleanModeSmartFN();
    
    // 9净化模式状态-除味功能，
    int GetCleanModeDelTasteFN();
    
    // 10净化模式状态-除烟功能，
    int GetCleanModeDelSmokeFN();
    
    // 11普通定时功能，
    int GetGeneralTimingFN();
    
    // 12儿童锁功能，
    int GetChildLockFN();
    
    // 13水离子开停，
    int GetWaterIonFN();
    
    // 14加湿机开停功能，
    int GetDehumidifierFN();
    
    // 15净化机开停功能
    int GetCleanMachineFN();
    
    // 16 EEPROM可改写功能,
    int GetEEpromReadWriteFN();
    
    // 17电量检测功能,
    int GetPowerDetectFN();
    
    // 101#-0#第5字节预留位的控制功能
    int Get5ReserverdFN();
    
    // 101#-0#第6字节预留位的控制功能
    int Get6ReserverdFN();
    
    void SetJHFN(string value, int offset);
    
    void SetCleanSpeedAutoFN(string value);
    
    void SetCleanSpeedDelSmokeFN(string value);
    
    void SetCleanSpeedHighFN(string value);
    
    void SetCleanSpeedMiddleFN(string value);
    
    void SetCleanSpeedLowFN(string value);
    
    void SetCleanModeSleepFN(string value);
    
    void SetCleanModeMuteFN(string value);
    
    void SetCleanModeSmartFN(string value);
    
    void SetCleanModeDelTasteFN(string value);
    
    void SetCleanModeDelSmokeFN(string value);
    
    void SetGeneralTimingFN(string value);
    
    void SetChildLockFN(string value);
    
    void SetWaterIonFN(string value);
    
    void SetHumidifierFN(string value);
    
    void SetCleanMachineFN(string value);
    
    void SetEEpromReadWriteFN(string value);
    
    void SetPowerDetectFN(string value);
    
    void Set5ReserverdFN(string value);
    
    void Set6ReserverdFN(string value);
    
    
    /******************************* 获取设备状态 *******************************/
    // 0净化速度
    string getSpeedStatus();
    
    // 1净化模式
    string getModeStatus();
    
    // 2定时开关机控制
    string getTimeStatus();
    
    // 3定时开关机时间
    string getTimerValue();
    
    //4风机转速
    string getMotorSpeed();
    
    // 5空气质量
    string getAirQuality();
    
    // 6空气质量百分比
    string getAirQualityPercent();
    
    // 7相对湿度
    string getRelativeHumidityValue();
    
    //8开停净化机
    string GetPower();
    
    // 9儿童锁开关控制
    string getChildLockStatus();
    
    // 10水离子开停控制
    string getWaterionStatus();
    
    // 11加湿机开停控制
    string getHumidityStatus();
    
    // 12过滤网更换提示
    string ChangeFilter();
    
    // 13本次命令之前有否红外和按键控制过
    string infraredAndButtonBeforeCommand1();
    
    // 13本次命令之前有否红外和按键控制过
    string infraredAndButtonBeforeCommand2();
    
    // 15加湿转轮不动
    string getHumidityWheelError();
    
    // 16水箱空
    string getWaterSinkEmptyError();
    
    // 17水箱未装好
    string getWaterSinkNotSetup();
    
    // 18湿度传感器故障
    string getHumiditySensorError();
    
    // 19风机故障
    string getMotorError();
    
    // 20风尘传感器故障
    string getDustSensorError();
    
    // 21气味传感器故障
    string geSmellSensorError();
    
    //22机器倾斜故障
    string getLeanError();
    
    //23湿度设置值
    string getSettingHumid();
};

#endif /* AirCleanerLogic_h */
