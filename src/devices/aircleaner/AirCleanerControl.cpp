//
//  AirCleanerControl.cpp
//  Devices
//
//  Created by 肖芳亮 on 16/2/24.
//  Copyright © 2016年 XLF. All rights reserved.
//

#include "AirCleanerControl.h"
#include "IOTUtil.h"

AirCleanerControl::AirCleanerControl(string deviceId)
{
    airCleanerLogic = new AirCleanerLogic();
    airCleanerLogic->deviceId = deviceId;
    airCleanerLogic->deviceType = "aircleaner";
    devicesLogic = airCleanerLogic;
}

AirCleanerControl::~AirCleanerControl()
{
    if(airCleanerLogic)
    {
        delete airCleanerLogic;
    }
}

//检测是否有风机故障、机器倾斜故障、过滤网更换提示
bool AirCleanerControl::checkError()
{
    return airCleanerLogic->checkError();
}

//1设置净化速度
string AirCleanerControl::setWindSpeed(string speed, bool manualOrnot)
{
    return airCleanerLogic->SetWindSpeed(speed, manualOrnot);
}

//2设置模式
string AirCleanerControl::setMode(string mode, bool manualOrnot)
{
    return airCleanerLogic->SetMode(mode,manualOrnot);
}

//定时开关机
string AirCleanerControl::setTimerControl(bool enable, string time, bool manualOrnot)
{
    return airCleanerLogic->TimerControl(enable, time, manualOrnot);
}

// 开关清新机电源
string AirCleanerControl::setpower(bool power, bool manualOrnot)
{
    return airCleanerLogic->setPower(power, manualOrnot);
    
}

// 开关儿童锁
string AirCleanerControl::setChildLock(bool power, bool manualOrnot)
{
    return airCleanerLogic->ChildLock(power, manualOrnot);
}

// 开关水离子
string AirCleanerControl::setWaterIon(bool power, bool manualOrnot)
{
    return airCleanerLogic->WaterIon(power,manualOrnot);
}

// 开关加湿功能
string AirCleanerControl::setHumidification(bool power, bool manualOrnot)
{
    return airCleanerLogic->Humidification(power,manualOrnot);
}

// 加湿器湿度设置
string AirCleanerControl::Humidification_ValueSet(int humidity_value, bool manualOrnot)
{
    return airCleanerLogic->HumidificationSet(humidity_value,manualOrnot);
}

string AirCleanerControl:: SetAirCleanerSBox(bool power_on,string Mode,string WindSpeed_value,bool jsj_on,string humdity_value,bool manualOrnot)
{
    string power = airCleanerLogic->GetPower();
    string modeStatus = airCleanerLogic->getModeStatus();
    string speedStatus = airCleanerLogic->getSpeedStatus();
    string humidityStatus = airCleanerLogic->getHumidityStatus();
    
    if(power == IOTUtil::intToString(power_on) && modeStatus == Mode && speedStatus == WindSpeed_value && humidityStatus == IOTUtil::intToString(jsj_on))
    {
        return "";
    }
    
    return airCleanerLogic->SetAirCleanerSBox(power_on, Mode, WindSpeed_value, jsj_on, humdity_value, manualOrnot);
}

/**************************************************************************/

//获取设备的各个状态


// 0净化速度
string AirCleanerControl::getSpeedStatus()
{
    return airCleanerLogic->getSpeedStatus();
}

// 1净化模式,
string AirCleanerControl::getModeStatus()
{
    return airCleanerLogic->getModeStatus();
}

//2定时开关机控制,
string AirCleanerControl::getTimeStatus()
{
    return airCleanerLogic->getTimeStatus();
}

//3定时开关机时间,
string AirCleanerControl::getTimerValue()
{
    return airCleanerLogic->getTimerValue();
}

//4风机转速,
string AirCleanerControl::getMotorSpeed()
{
    return airCleanerLogic->getMotorSpeed();
}

// 5空气质量,
string AirCleanerControl::getAirQuality()
{
    return airCleanerLogic->getAirQuality();
}

// 6空气质量百分比,
string AirCleanerControl::getAirQualityPercent()
{
    return airCleanerLogic->getAirQualityPercent();
}

// 7相对湿度,
string AirCleanerControl::getRelativeHumidityValue()
{
    return airCleanerLogic->getRelativeHumidityValue();
}

//8开停净化机,
string AirCleanerControl::getPowerStatus()
{
    return airCleanerLogic->GetPower();
}

// 9儿童锁开关控制,
string AirCleanerControl::getChildLockStatus()
{
    return airCleanerLogic->getChildLockStatus();
}

// 10水离子开停控制,
string AirCleanerControl::getWaterionStatus()
{
    return airCleanerLogic->getWaterionStatus();
}

// 11加湿机开停控制,
string AirCleanerControl::getHumidityStatus()
{
    return airCleanerLogic->getHumidityStatus();
}

// 12过滤网更换提示,
string AirCleanerControl::ChangeFilter()
{
    return airCleanerLogic->ChangeFilter();
}

// 13本次命令之前有否红外和按键控制过,
string AirCleanerControl::infraredAndButtonBeforeCommand1()
{
    return airCleanerLogic->infraredAndButtonBeforeCommand1();
}

// 14本次命令之前有否红外和按键控制过,
string AirCleanerControl::infraredAndButtonBeforeCommand2()
{
    return airCleanerLogic->infraredAndButtonBeforeCommand2();
}

// 15加湿转轮不动,

string AirCleanerControl::getHumidityWheelError()
{
    return airCleanerLogic->getHumidityWheelError();
}

// 16水箱空,
string AirCleanerControl::getWaterSinkEmptyError()
{
    return airCleanerLogic->getWaterSinkEmptyError();
}

// 17水箱未装好,
string AirCleanerControl::getWaterSinkNotSetup()
{
    return airCleanerLogic->getWaterSinkNotSetup();
}

// 18湿度传感器故障,
string AirCleanerControl::getHumiditySensorError()
{
    return airCleanerLogic->getHumiditySensorError();
}

// 19风机故障,
string AirCleanerControl::getMotorError()
{
    return airCleanerLogic->getMotorError();
}

// 20风尘传感器故障,
string AirCleanerControl::getDustSensorError()
{
    return airCleanerLogic->getDustSensorError();
}

// 21气味传感器故障，
string AirCleanerControl::geSmellSensorError()
{
    return airCleanerLogic->geSmellSensorError();
}

//22机器倾斜故障
string AirCleanerControl::getLeanError()
{
    return airCleanerLogic->getLeanError();
}

//23湿度设置值
string AirCleanerControl::getSettingHumid()
{
    return airCleanerLogic->getSettingHumid();
}

/**************************************************************************/

// 获取功能使能状态

//功能查询
//命令:JHGN
//查询状态:?
//状态返回:净化速度状态-自动功能，净化速度状态-净烟功能 ，净化速度状态-高风功能，净化速度状态-中风功能，净化速度状态-低风功能，
//净化模式状态-睡眠功能，净化模式状态-静音功能，净化模式状态-智能功能，净化模式状态-除味功能，净化模式状态-除烟功能，
//普通定时功能，儿童锁功能，水离子开停，加湿机开停功能，净化机开停功能  EEPROM可改写功能,电量检测功能,
//101#-0#第5字节预留位的控制功能,101#-0#第6字节预留位的控制功能

int AirCleanerControl::GetCleanSpeedAutoFN()
{
    return airCleanerLogic->GetCleanSpeedAutoFN();
}

int AirCleanerControl::GetCleanSpeedDelSmokeFN()
{
    return airCleanerLogic->GetCleanSpeedDelSmokeFN();
}

int AirCleanerControl::GetCleanSpeedHighFN()
{
    return airCleanerLogic->GetCleanSpeedHighFN();
}

int AirCleanerControl::GetCleanSpeedMiddleFN()
{
    return airCleanerLogic->GetCleanSpeedMiddleFN();
}

int AirCleanerControl::GetCleanSpeedLowFN()
{
    return airCleanerLogic->GetCleanSpeedLowFN();
}

int AirCleanerControl::GetCleanModeSleepFN()
{
    return airCleanerLogic->GetCleanModeSleepFN();
}

int AirCleanerControl::GetCleanModeMuteFN()
{
    return airCleanerLogic->GetCleanModeMuteFN();
}

int AirCleanerControl::GetCleanModeSmartFN()
{
    return airCleanerLogic->GetCleanModeSmartFN();
}

int AirCleanerControl::GetCleanModeDelTasteFN() {
    
    return airCleanerLogic->GetCleanModeDelTasteFN();
}

int AirCleanerControl::GetCleanModeDelSmokeFN()
{
    return airCleanerLogic->GetCleanModeDelSmokeFN();
}

int AirCleanerControl::GetGeneralTimingFN()
{
    return airCleanerLogic->GetGeneralTimingFN();
}

int AirCleanerControl::GetChildLockFN()
{
    return airCleanerLogic->GetChildLockFN();
}

int AirCleanerControl::GetWaterIonFN()
{
    return airCleanerLogic->GetWaterIonFN();
}

int AirCleanerControl::GetDehumidifierFN()
{
    return airCleanerLogic->GetDehumidifierFN();
}

int AirCleanerControl::GetCleanMachineFN()
{
    return airCleanerLogic->GetCleanMachineFN();
}

int AirCleanerControl::GetEEpromReadWriteFN()
{
    return airCleanerLogic->GetEEpromReadWriteFN();
}

int AirCleanerControl::GetPowerDetectFN()
{
    return airCleanerLogic->GetPowerDetectFN();
}

int AirCleanerControl::Get5ReserverdFN()
{
    return airCleanerLogic->Get5ReserverdFN();
}

int AirCleanerControl::Get6ReserverdFN()
{
    return airCleanerLogic->Get6ReserverdFN();
}
