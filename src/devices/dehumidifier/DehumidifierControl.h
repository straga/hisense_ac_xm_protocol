//
//  DehumidifierControl.h
//  Devices
//
//  Created by 肖芳亮 on 16/2/24.
//  Copyright © 2016年 XLF. All rights reserved.
//

#ifndef DehumidifierControl_h
#define DehumidifierControl_h

#include "DeviceControl.h"
#include "DehumidifierLogic.h"

class DehumidifierControl : public DeviceControl
{
    
private:
    
    /** 逻辑类 */
    DehumidifierLogic *dehumidifierLogic;
    
public:
    
    DehumidifierControl(string deviceId);
    
    ~DehumidifierControl();
    
    /**
     * 1.直接设置 开/关机
     * 取消普通定时,取消实时关机,取消快速冷热,取消睡眠,取消左右风,取消电热,取消节能,取消净化,取消双模,取消显示,取消亮度
     */
    string setDirctPower(int power, int manualOrnot);
    
    /**
     * 2.设置风速
     */
    string setWindSpeed(string speed, int manualOrnot);
    
    /**
     * 3.设置模式
     */
    string setMode(string mode, int manualOrnot);
    
    /**
     * 4.定时开关机
     */
    string setTimerControl(int enable, string time, int manualOrnot);
    
    /**
     * 5.设置湿度
     */
    string setHumidity(int humidity, int manualOrnot);
    
    /**
     * 6.设置温度
     */
    string setTemperature(int temperature, int manualOrnot);
    
    /**
     * 7.设置开关电源
     */
    string setPower(int power, int manualOrnot);
    
    /**
     * 8.设置开关电加热
     */
    string setEletricHeatControl(int isEletricHeatOn, int manualOrnot);
    
    /**
     * 9.设置开关水泵
     */
    string setWaterPumpControl(int enable, int manualOrnot);
    
    /**
     * 10.设置开关负离子
     */
    string setNegativeIonsControl(int enable, int manualOrnot);
    
    /**
     * 11.设置CSSBox
     */
    string setCSSBox(int on,string Mode,string WindSpeed_value,int humidity,int manualOrnot);
    
    /********************************** 功能 **********************************/
    /**
     * 智慧风
     */
    int getSmartWindFN();
    
    /**
     * 高风
     */
    int getHighWindFN();
    
    /**
     * 中风
     */
    int getMediumWindFN();
    
    /**
     * 低风
     */
    int getLowWindFN();
    
    /**
     * 运行模式 持续运行
     */
    int getContinueModeFN();
    
    /**
     * 运行模式 正常运行
     */
    int getNormalModeFN();
    
    /**
     * 运行模式 自动运行
     */
    int getAutoModeFN();
    
    /**
     * 定时
     */
    int getTimerControlFN();
    
    /**
     * 电加热
     */
    int getElectricHeatFN();
    
    /**
     * 电加热 温度
     */
    int getElectricHeatSetTemperatureFN();
    
    /**
     * 室内湿度
     */
    int getIndoorHumidityFN();
    
    /**
     * 水泵
     */
    int getWaterPumpFN();
    
    /**
     * 负离子
     */
    int getAnionFN();
    
    /**
     * 电量检测
     */
    int getElectronicDetectFN();
    
    /**
     * 开停机
     */
    int getPowerFN();
    
    /**
     * EEPROM可改写功能
     */
    int getEEPROMWriteFN();
    
    /**
     * 101#-0#第 7 字节预留位的控制功能
     */
    int get7ReserverdFN();
    
    /**
     * 101#-0#第 8 字节预留位的控制功能
     */
    int get8ReserverdFN();
    
    /********************************** 使能 **********************************/
    /**
     * 智慧风
     */
    void setSmartWindFN(string value);
    
    /**
     * 高风
     */
    void setHighWindFN(string value);
    
    /**
     * 中风
     */
    void setMediumWindFN(string value);
    
    /**
     * 低风
     */
    void setLowWindFN(string value);
    
    /**
     * 运行模式 持续运行
     */
    void setContinueModeFN(string value);
    
    /**
     * 运行模式 正常运行
     */
    void setNormalModeFN(string value);
    
    /**
     * 运行模式 自动运行
     */
    void setAutoModeFN(string value);
    
    /**
     * 定时
     */
    void setTimerControlFN(string value);
    
    /**
     * 电加热
     */
    void setElectricHeatFN(string value);
    
    /**
     * 电加热 温度
     */
    void setElectricHeatSetTemperatureFN(string value);
    
    /**
     * 室内湿度
     */
    void setIndoorHumidityFN(string value);
    
    /**
     * 水泵
     */
    void setWaterPumpFN(string value);
    
    /**
     * 负离子
     */
    void setAnionFN(string value);
    
    /**
     * 电量检测
     */
    void setElectronicDetectFN(string value);
    
    /**
     * 电源
     */
    void setPowerFN(string value);
    
    /**
     * EEPROM可改写功能
     */
    void setEEPROMWriteFN(string value);
    
    /**
     * 7 字节预留位的控制功能
     */
    void set7ReserverdFN(string value);
    
    /**
     * 8 字节预留位的控制功能
     */
    void set8ReserverdFN(string value);
    
    
    /********************************** 获取设备状态 **********************************/
    /**
     * 获取风速
     */
    string getWindSpeedStatus();
    
    /**
     * 获取模式
     */
    string getModeStatus();
    
    /**
     * 获取定时开关机控制
     */
    string getTimeStatus();
    
    /**
     * 获取定时开关机时间
     */
    string getTimerValue();
    
    /**
     * 获取设置湿度
     */
    string getSettingHumidityValue();
    
    /**
     * 获取电加热设定温度
     */
    string getEletricHeatingTempratureStatus();
    
    /**
     * 获取室内温度
     */
    string getIndoorTempStatus();
    
    /**
     * 获取除湿机电源开关状态
     */
    string getPower();
    
    /**
     * 获取电加热功能开关状态
     */
    string getEletricHeatingStatus();
    
    /**
     * 获取水泵开关状态
     */
    string getWaterPumpStatus();
    
    /**
     * 获取负离子开关状态
     */
    string getAnionStatus();
    
    /**
     * 本次命令之前有否红外和按键控制过
     */
    string getInfrarediKeypadControl();
    
    /**
     * 本次命令之前有否 WIFI 控制过
     */
    string getWifiControl();
    
    /**
     * 过滤网清洁告警
     */
    string getFilterNetCleanWarning();
    
    /**
     * 湿度传感器故障
     */
    string getHumidSensorError();
    
    /**
     *  管温传感器故障
     */
    string getPumpTempratureError();
    
    /**
     * 室内温度传感器故障
     */
    string getIndoorTempratureError();
    
    /**
     * 水满警告
     */
    string getWaterFullWarning();
    
    /**
     * 水泵故障
     */
    string getWaterPumpWarning();
    
    /**
     * 获取实际湿度
     */
    string getRealHumidityValue();
    
    /**
     * 解析的返回数据
     */
    bool parseAtCommand(string result);
};

#endif /* DehumidifierControl_h */
