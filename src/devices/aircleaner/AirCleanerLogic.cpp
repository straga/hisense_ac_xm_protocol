//
//  AirCleanerLogic.cpp
//  Devices
//
//  Created by 肖芳亮 on 16/2/24.
//  Copyright © 2016年 XLF. All rights reserved.
//

#include "AirCleanerLogic.h"
#include "IOTUtil.h"
#include <iostream>
#include "IOTConstants.h"
#include <sstream>

#define MODE_SMART      "smart"
#define MODE_MUTE       "mute"
#define MODE_SLEEP      "sleep"

AirCleanerLogic::AirCleanerLogic()
{
    DEVICE_TYPE = 0x18;
    At_QureyStatus = "JHZD";
    At_QueryFuntion = "JHGN";
    At_Status_Num = 24;
    At_Funtion_Num = 19;
    At_Modle_Num = 17;
    
    for(int i = 0; i < 19; i++)
    {
        GN.push_back(0);
    }
    
    for(int i = 0; i < 24; i++)
    {
        ZD.push_back("0");
    }
    
    for(int i = 0; i < 24; i++)
    {
        GN_EN.push_back(0);
    }
    
    setDeviceFunction("1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0");
}

AirCleanerLogic::~AirCleanerLogic()
{
    
}

void AirCleanerLogic::refreshFn()
{
    string power = GetPower();
    if(power == "1")
    {
        SetCleanSpeedAutoFN("2");
        
        string modeStatus = getModeStatus();
        if(modeStatus == MODE_SLEEP || modeStatus == MODE_SMART || modeStatus == MODE_MUTE)
        {
            SetCleanSpeedAutoFN("3");
        }
    }
}

/*开/关机*/
string AirCleanerLogic::DirctSetPower(string devid, bool on, bool manualOrnot)
{
    /*取消普通定时,取消实时关机,取消快速冷热,取消睡眠,取消左右风,取消电热,取消节能,取消净化,取消双模,取消显示,取消亮度*/
    if(on)
    {
        return IOTConstants::CMD_AT_MARK  + "JHQKJ" + IOTConstants::CMD_AT_EQUALS_SINGNAL + devid + IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(on) + IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(manualOrnot) + IOTConstants::CMD_AT_WRAP;
    }
    else
    {
        
        return IOTConstants::CMD_AT_MARK  + "JHQKJ" + IOTConstants::CMD_AT_EQUALS_SINGNAL + devid + IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(on)
        + IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(manualOrnot)
        + IOTConstants::PARAM_VALUE_SPLIT + "0"
        + IOTConstants::PARAM_VALUE_SPLIT + "0"
        + IOTConstants::PARAM_VALUE_SPLIT + "0"
        + IOTConstants::PARAM_VALUE_SPLIT + "off"
        + IOTConstants::PARAM_VALUE_SPLIT + "0,0,0,0,0"
        + IOTConstants::CMD_AT_WRAP;
    }
    
}

// 1设置净化速度
string AirCleanerLogic::SetWindSpeed(string speed, bool manualOrnot)
{
    if(checkError())
    {
        return "";
    }
    
    string modeStatus = getModeStatus();
    if(modeStatus == MODE_SLEEP || modeStatus == MODE_SMART || modeStatus == MODE_MUTE)
    {
        return "";
    }
    
    ZD[0] = speed;
    
    return   IOTConstants::CMD_AT_MARK + "JHFS"
    + IOTConstants::CMD_AT_EQUALS_SINGNAL + deviceId
    + IOTConstants::PARAM_VALUE_SPLIT + speed
    + IOTConstants::PARAM_VALUE_SPLIT
    + IOTUtil::intToString(manualOrnot)
    + IOTConstants::CMD_AT_WRAP;
}

// 2设置净化模式
string AirCleanerLogic::SetMode(string mode, bool manualOrnot)
{
    if(checkError())
    {
        return "";
    }
    
    if(mode == MODE_SLEEP || mode == MODE_SMART || mode == MODE_MUTE)
    {
        SetCleanSpeedAutoFN("3");
    }
    else
    {
        SetCleanSpeedAutoFN("2");
    }
    
    ZD[1] = mode;
    
    return   IOTConstants::CMD_AT_MARK + "JHMS"
    + IOTConstants::CMD_AT_EQUALS_SINGNAL + deviceId
    + IOTConstants::PARAM_VALUE_SPLIT + mode
    + IOTConstants::PARAM_VALUE_SPLIT
    + IOTUtil::intToString(manualOrnot)
    + IOTConstants::CMD_AT_WRAP;
}

// 3设置定时开关机
string AirCleanerLogic::TimerControl(bool enable, string time, bool manualOrnot)
{
    if(checkError())
    {
        return "";
    }
    
    ZD[2] = IOTUtil::intToString(enable);
    ZD[3] = time;
    return    IOTConstants::CMD_AT_MARK + "JHDS"
    + IOTConstants::CMD_AT_EQUALS_SINGNAL + deviceId
    + IOTConstants::PARAM_VALUE_SPLIT + time
    + IOTConstants::PARAM_VALUE_SPLIT
    + IOTUtil::intToString(enable)
    + IOTConstants::PARAM_VALUE_SPLIT
    + IOTUtil::intToString(manualOrnot)
    + IOTConstants::CMD_AT_WRAP;
}

// 开关电源
string AirCleanerLogic::setPower(bool power, bool manualOrnot)
{
    if(checkError())
    {
        return "";
    }
    
    ZD[8] = IOTUtil::intToString(power);
    return IOTConstants::CMD_AT_MARK + "JHKJ"
    + IOTConstants::CMD_AT_EQUALS_SINGNAL + deviceId
    + IOTConstants::PARAM_VALUE_SPLIT
    + IOTUtil::intToString(power)
    + IOTConstants::PARAM_VALUE_SPLIT
    + IOTUtil::intToString(manualOrnot)
    + IOTConstants::CMD_AT_WRAP;
}


// 开关儿童锁
string AirCleanerLogic::ChildLock(bool power, bool manualOrnot)
{
    if(checkError())
    {
        return "";
    }
    ZD[9] = IOTUtil::intToString(power);
    
    return   IOTConstants::CMD_AT_MARK + "JHRT"
    + IOTConstants::CMD_AT_EQUALS_SINGNAL + deviceId
    + IOTConstants::PARAM_VALUE_SPLIT
    + IOTUtil::intToString(power)
    + IOTConstants::PARAM_VALUE_SPLIT
    + IOTUtil::intToString(manualOrnot)
    + IOTConstants::CMD_AT_WRAP;
}


// 开关水离子
string AirCleanerLogic::WaterIon(bool power, bool manualOrnot)
{
    if(checkError())
    {
        return "";
    }
    
    ZD[10] = IOTUtil::intToString(power);
    return IOTConstants::CMD_AT_MARK + "JHSLZ"
				+ IOTConstants::CMD_AT_EQUALS_SINGNAL + deviceId
				+ IOTConstants::PARAM_VALUE_SPLIT
				+ IOTUtil::intToString(power)
				+ IOTConstants::PARAM_VALUE_SPLIT
				+ IOTUtil::intToString(manualOrnot)
				+ IOTConstants::CMD_AT_WRAP;
}


// 开关加湿器
string AirCleanerLogic::Humidification(bool power,bool manualOrnot)
{
    if(checkError())
    {
        return "";
    }
    
    ZD[11] = IOTUtil::intToString(power);
    return IOTConstants::CMD_AT_MARK + "JHJSJ"
				+ IOTConstants::CMD_AT_EQUALS_SINGNAL + deviceId
				+ IOTConstants::PARAM_VALUE_SPLIT
				+ IOTUtil::intToString(power)
				+ IOTConstants::PARAM_VALUE_SPLIT
				+ IOTUtil::intToString(manualOrnot)
				+ IOTConstants::CMD_AT_WRAP;
}

// 加湿器湿度设置
string AirCleanerLogic::HumidificationSet(int  humidity_value,bool manualOrnot)
{
    if(checkError())
    {
        return "";
    }
    
    if(humidity_value < 40 || 80 < humidity_value)
    {
        return "";
    }
    
    ZD[23] = IOTUtil::intToString(humidity_value);
    return IOTConstants::CMD_AT_MARK + "JHHS"
    + IOTConstants::CMD_AT_EQUALS_SINGNAL + deviceId
    + IOTConstants::PARAM_VALUE_SPLIT
    + IOTUtil::intToString(humidity_value)
    + IOTConstants::PARAM_VALUE_SPLIT
    + IOTUtil::intToString(manualOrnot)
    + IOTConstants::CMD_AT_WRAP;
}


/*设置AirCleanerSBox*/
string AirCleanerLogic::SetAirCleanerSBox(bool power_on,string Mode,string WindSpeed_value,bool jsj_on,string humdity_value,bool manualOrnot)
{
    if(Mode == IOTConstants::AIRCLEANER_MODE_MUTE || Mode == IOTConstants::AIRCLEANER_MODE_SLEEP || Mode == IOTConstants::AIRCLEANER_MODE_SMART)
    {
        WindSpeed_value = IOTConstants::AIRCLEANER_WIND_AUTO;
    }
    
    ZD[0] = WindSpeed_value;
    ZD[1] = Mode;
    ZD[8] = IOTUtil::intToString(power_on);
    ZD[11] = IOTUtil::intToString(jsj_on);
    ZD[23] = humdity_value;
    
    return IOTConstants::CMD_AT_MARK  + "JHSBOX" + IOTConstants::CMD_AT_EQUALS_SINGNAL + deviceId +
    IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(power_on) +IOTConstants::PARAM_VALUE_SPLIT +
    Mode + IOTConstants::PARAM_VALUE_SPLIT + WindSpeed_value + IOTConstants::PARAM_VALUE_SPLIT +  IOTUtil::intToString(jsj_on) + IOTConstants::PARAM_VALUE_SPLIT + humdity_value + IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(manualOrnot) + IOTConstants::CMD_AT_WRAP;
}

/**************************************************************************/

// 获取功能使能状态
int AirCleanerLogic::GetJHFN(int offset)
{
    if(0 < GN[offset] && 0 < GN_EN[offset])
    {
        return GN_EN[offset];
    }
    
    return 0;
}

// 1净化速度状态-自动功能，
int AirCleanerLogic::GetCleanSpeedAutoFN()
{
    return GetJHFN(0);
}

// 2净化速度状态-净烟功能 ，
int AirCleanerLogic::GetCleanSpeedDelSmokeFN()
{
    return GetJHFN(1);
}

// 3净化速度状态-高风功能
int AirCleanerLogic::GetCleanSpeedHighFN()
{
    return GetJHFN(2);
}

// 4净化速度状态-中风功能，
int AirCleanerLogic::GetCleanSpeedMiddleFN()
{
    return GetJHFN(3);
}

// 5净化速度状态-低风功能，
int AirCleanerLogic::GetCleanSpeedLowFN()
{
    return GetJHFN(4);
}

// 6净化模式状态-睡眠功能，
int AirCleanerLogic::GetCleanModeSleepFN()
{
    return GetJHFN(5);
}

// 7净化模式状态-静音功能，
int AirCleanerLogic::GetCleanModeMuteFN()
{
    return GetJHFN(6);
}

// 8净化模式状态-智能功能，
int AirCleanerLogic::GetCleanModeSmartFN()
{
    return GetJHFN(7);
}

// 9净化模式状态-除味功能，
int AirCleanerLogic::GetCleanModeDelTasteFN()
{
    return GetJHFN(8);
}

// 10净化模式状态-除烟功能，
int AirCleanerLogic::GetCleanModeDelSmokeFN()
{
    return GetJHFN(9);
}

// 11普通定时功能，
int AirCleanerLogic::GetGeneralTimingFN()
{
    return GetJHFN(10);
}

// 12儿童锁功能，
int AirCleanerLogic::GetChildLockFN()
{
    return GetJHFN(11);
}

// 13水离子开停，
int AirCleanerLogic::GetWaterIonFN()
{
    return GetJHFN(12);
}

// 14加湿机开停功能，
int AirCleanerLogic::GetDehumidifierFN()
{
    return GetJHFN(13);
}

// 15净化机开停功能
int AirCleanerLogic::GetCleanMachineFN()
{
    return GetJHFN(14);
}

// 16 EEPROM可改写功能,
int AirCleanerLogic::GetEEpromReadWriteFN()
{
    return GetJHFN(15);
}

// 17电量检测功能,
int AirCleanerLogic::GetPowerDetectFN()
{
    return GetJHFN(16);
}

// 101#-0#第5字节预留位的控制功能
int AirCleanerLogic::Get5ReserverdFN()
{
    return GetJHFN(17);
}

// 101#-0#第6字节预留位的控制功能
int AirCleanerLogic::Get6ReserverdFN()
{
    return GetJHFN(18);
}


//设置设备功能使能状态
void AirCleanerLogic::SetJHFN(string value, int offset)
{
    if(value == "0")
    {
        GN[offset] = 0;
    }
    else if(value == "1")
    {
        GN[offset] = 1;
    }
    else if(value == "2")
    {
        GN_EN[offset] = 1;
    }
    else if(value == "3")
    {
        GN_EN[offset] = 0;
    }
    else
    {
        stringstream stream;
        stream << value;
        int intValue;
        stream >> intValue;
        GN[offset] = intValue;
    }
}

void AirCleanerLogic::SetCleanSpeedAutoFN(string value)
{
    SetJHFN(value, 0);
}

void AirCleanerLogic::SetCleanSpeedDelSmokeFN(string value)
{
    SetJHFN(value, 1);
}

void AirCleanerLogic::SetCleanSpeedHighFN(string value)
{
    SetJHFN(value, 2);
}

void AirCleanerLogic::SetCleanSpeedMiddleFN(string value)
{
    SetJHFN(value, 3);
}

void AirCleanerLogic::SetCleanSpeedLowFN(string value)
{
    SetJHFN(value, 4);
}

void AirCleanerLogic::SetCleanModeSleepFN(string value)
{
    SetJHFN(value, 5);
}

void AirCleanerLogic::SetCleanModeMuteFN(string value)
{
    SetJHFN(value, 6);
}

void AirCleanerLogic::SetCleanModeSmartFN(string value)
{
    SetJHFN(value, 7);
}

void AirCleanerLogic::SetCleanModeDelTasteFN(string value)
{
    SetJHFN(value, 8);
}

void AirCleanerLogic::SetCleanModeDelSmokeFN(string value)
{
    SetJHFN(value, 9);
}

void AirCleanerLogic::SetGeneralTimingFN(string value)
{
    SetJHFN(value, 10);
}

void AirCleanerLogic::SetChildLockFN(string value)
{
    SetJHFN(value, 11);
}

void AirCleanerLogic::SetWaterIonFN(string value)
{
    SetJHFN(value, 12);
}

void AirCleanerLogic::SetHumidifierFN(string value)
{
    SetJHFN(value, 13);
}

void AirCleanerLogic::SetCleanMachineFN(string value)
{
    SetJHFN(value, 14);
}

void AirCleanerLogic::SetEEpromReadWriteFN(string value)
{
    SetJHFN(value, 15);
}

void AirCleanerLogic::SetPowerDetectFN(string value)
{
    SetJHFN(value, 16);
}

void AirCleanerLogic::Set5ReserverdFN(string value)
{
    SetJHFN(value, 17);
}

void AirCleanerLogic::Set6ReserverdFN(string value)
{
    SetJHFN(value, 18);
}

/***********************************************************************/
bool AirCleanerLogic::checkError()
{
    string motorError = getMotorError();
    string leanError = getLeanError();
    string filter = ChangeFilter();
    
    if(motorError == "1" || leanError == "1" || filter == "1")
    {
        return true;
    }
    else
    {
        return false;
    }
}

string AirCleanerLogic::getSpeedStatus()
{
    return ZD[0];// 0净化速度
}

string AirCleanerLogic::getModeStatus()
{
    return ZD[1];// 1净化模式,
}

string AirCleanerLogic::getTimeStatus()
{
    return ZD[2];//2定时开关机控制,
}

string AirCleanerLogic::getTimerValue()
{
    return ZD[3];//3定时开关机时间,
}

string AirCleanerLogic::getMotorSpeed()
{
    return ZD[4];//4风机转速,
}

string AirCleanerLogic::getAirQuality()
{
    return ZD[5];// 5空气质量,
}

string AirCleanerLogic::getAirQualityPercent()
{
    return ZD[6];// 6空气质量百分比,
}

string AirCleanerLogic::getRelativeHumidityValue()
{
    return ZD[7];// 7相对湿度,
}

//override base class function
string AirCleanerLogic::GetPower()
{
    return ZD[8]; //8开停净化机,
}

string AirCleanerLogic::getChildLockStatus()
{
    return ZD[9];// 9儿童锁开关控制,
}

string AirCleanerLogic::getWaterionStatus()
{
    return ZD[10];// 10水离子开停控制,
}

string AirCleanerLogic::getHumidityStatus()
{
    return ZD[11];// 11加湿机开停控制,
}

string AirCleanerLogic::ChangeFilter()
{
    return ZD[12];// 12过滤网更换提示,
}

string AirCleanerLogic::infraredAndButtonBeforeCommand1()
{
    return ZD[13];// 13本次命令之前有否红外和按键控制过,
}

string AirCleanerLogic::infraredAndButtonBeforeCommand2()
{
    return ZD[14];// 13本次命令之前有否红外和按键控制过,
}

string AirCleanerLogic::getHumidityWheelError()
{
    return ZD[15];// 15加湿转轮不动,
}

string AirCleanerLogic::getWaterSinkEmptyError()
{
    return ZD[16];// 16水箱空,
}

string AirCleanerLogic::getWaterSinkNotSetup()
{
    return ZD[17];// 17水箱未装好,
}

string AirCleanerLogic::getHumiditySensorError()
{
    return ZD[18];// 18湿度传感器故障,
}

string AirCleanerLogic::getMotorError()
{
    return ZD[19];// 19风机故障,
}

string AirCleanerLogic::getDustSensorError()
{
    return ZD[20];// 20风尘传感器故障,
}

string AirCleanerLogic::geSmellSensorError()
{
    return ZD[21];// 21气味传感器故障,
}

string AirCleanerLogic::getLeanError()
{
    return ZD[22];//22机器倾斜故障
}

string AirCleanerLogic::getSettingHumid()
{
    return ZD[23];//23湿度设置值
}