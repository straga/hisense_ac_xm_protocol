//
//  AirCleanerControl.h
//  Devices
//
//  Created by 肖芳亮 on 16/2/24.
//  Copyright © 2016年 XLF. All rights reserved.
//

#ifndef AirCleanerControl_h
#define AirCleanerControl_h

#include <stdio.h>
#include <string>
#include <vector>
#include "DeviceControl.h"
#include "AirCleanerLogic.h"

using namespace::std;

class AirCleanerControl : public DeviceControl
{
    
private:
    
    /** 逻辑类 */
    AirCleanerLogic *airCleanerLogic;
    
public:
    
    AirCleanerControl(string deviceId);
    
    ~AirCleanerControl();
    
    //检测是否有风机故障、机器倾斜故障、过滤网更换提示
    bool checkError();
    
    /************************************ 设备控制 **************************************/
    //1设置净化速度
    string setWindSpeed(string speed, bool manualOrnot);
    
    //2设置模式
    string setMode(string mode, bool manualOrnot);
    
    //定时开关机
    string setTimerControl(bool enable, string time, bool manualOrnot);
    
    // 开关清新机电源
    string setpower(bool power, bool manualOrnot);
    
    // 开关儿童锁
    string setChildLock(bool power, bool manualOrnot);
    
    // 开关水离子
    string setWaterIon(bool power, bool manualOrnot);
    
    // 开关加湿功能
    string setHumidification(bool power, bool manualOrnot);
    
    // 加湿器湿度设置
    string Humidification_ValueSet(int humidity_value, bool manualOrnot);
    
    // 盒子控制
    string  SetAirCleanerSBox(bool power_on,string Mode,string WindSpeed_value,bool jsj_on,string humdity_value,bool manualOrnot);
    
    /************************************ 获取设备的各个状态 **************************************/
    // 0净化速度
    string getSpeedStatus();
    
    // 1净化模式,
    string getModeStatus();
    
    //2定时开关机控制,
    string getTimeStatus();
    
    //3定时开关机时间,
    string getTimerValue();
    
    //4风机转速,
    string getMotorSpeed();
    
    // 5空气质量,
    string getAirQuality();
    
    // 6空气质量百分比,
    string getAirQualityPercent();
    
    // 7相对湿度,
    string getRelativeHumidityValue();
    
    //8开停净化机,
    string getPowerStatus();
    
    // 9儿童锁开关控制,
    string getChildLockStatus();
    
    // 10水离子开停控制,
    string getWaterionStatus();
    
    // 11加湿机开停控制,
    string getHumidityStatus();
    
    // 12过滤网更换提示,
    string ChangeFilter();
    
    // 13本次命令之前有否红外和按键控制过,
    string infraredAndButtonBeforeCommand1();
    
    // 14本次命令之前有否红外和按键控制过,
    string infraredAndButtonBeforeCommand2();
    
    // 15加湿转轮不动,
    string getHumidityWheelError();
    
    // 16水箱空,
    string getWaterSinkEmptyError();
    
    // 17水箱未装好,
    string getWaterSinkNotSetup();
    
    // 18湿度传感器故障,
    string getHumiditySensorError();
    // 19风机故障,
    string getMotorError();
    
    // 20风尘传感器故障,
    string getDustSensorError();
    
    // 21气味传感器故障，
    string geSmellSensorError();
    
    //22机器倾斜故障
    string getLeanError();
    
    //23湿度设置值
    string getSettingHumid();
    
    /********************************** 获取功能使能状态 ****************************************/
     // 1净化速度状态-自动功能，
    int GetCleanSpeedAutoFN();
    
    // 2净化速度状态-净烟功能
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
    
};

#endif /* AirCleanerControl_h */
