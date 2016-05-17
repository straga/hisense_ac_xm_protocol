//
//  DehumidifierLogic.cpp
//  Devices
//
//  Created by 肖芳亮 on 16/2/24.
//  Copyright © 2016年 XLF. All rights reserved.
//

#include "DehumidifierLogic.h"
#include "IOTConstants.h"
#include "IOTUtil.h"
#include <sstream>

DehumidifierLogic::DehumidifierLogic()
{
    DEVICE_TYPE = 0x15;
    At_QureyStatus = "CSZD";
    At_QueryFuntion = "CSGN";
    At_Setting = "CSSET";
    At_Status_Num = 20;
    At_Funtion_Num = 18;
    At_Modle_Num = 17;
    
    
    for(int i = 0; i < At_Status_Num; i++)
    {
        ZD.push_back("0");
    }
    
    for(int i = 0; i < At_Funtion_Num; i++)
    {
        GN.push_back(0);
    }
    
    for(int i = 0; i < At_Modle_Num; i++)
    {
        GN_EN.push_back(0);
    }
    
    //设置默认的功能列表
    setDeviceFunction("1,1,0,1,1,1,1,1,0,0,1,0,0,0,1,1,0,0");
}

DehumidifierLogic::~DehumidifierLogic()
{
    
}


/**
 * 1.直接设置 开/关机
 * 取消普通定时,取消实时关机,取消快速冷热,取消睡眠,取消左右风,取消电热,取消节能,取消净化,取消双模,取消显示,取消亮度
 */
string DehumidifierLogic::setDirctPower(int power, int manualOrnot)
{
    string atcmd = IOTConstants::CMD_AT_MARK + "CSKJ" + IOTConstants::CMD_AT_EQUALS_SINGNAL
    + deviceId + IOTConstants::PARAM_VALUE_SPLIT
    + IOTUtil::intToString(power)
    + IOTConstants::PARAM_VALUE_SPLIT
    + IOTUtil::intToString(manualOrnot)
    + IOTConstants::CMD_AT_WRAP;
    return	createNetBytes(atcmd);
}

/**
 * 2.设置风速
 */
string DehumidifierLogic::setWindSpeed(string speed, int manualOrnot)
{
    string modeStatus = getModeStatus();
    if(checkWaterFullWarning() || modeStatus == "auto")
    {
        return "";
    }
    ZD[0] = speed;
    string atcmd = IOTConstants::CMD_AT_MARK + "CSFS"
				+ IOTConstants::CMD_AT_EQUALS_SINGNAL + deviceId
				+ IOTConstants::PARAM_VALUE_SPLIT + speed
				+ IOTConstants::PARAM_VALUE_SPLIT
				+ IOTUtil::intToString(manualOrnot)
				+ IOTConstants::CMD_AT_WRAP;
    
    return	createNetBytes(atcmd);
}

/**
 * 3.设置模式
 */
string DehumidifierLogic::setMode(string mode, int manualOrnot)
{
    // 水满告警、硬件选择无电加热
    if(checkWaterFullWarning())
    {
        return "";
    }
    
    if(mode == "auto")
    {
        ZD[0] = "auto";
    }
    
    setElectricHeatSetTemperatureFN("3");
    setIndoorHumidityFN("3");
    setSmartWindFN("2") ;
    setHighWindFN("2") ;
    setMediumWindFN("2") ;
    setLowWindFN("2") ;
    
    ZD[1] = mode;
    
    if (IOTUtil::stringToInt(getEletricHeatingStatus()) )
    {
        return  "";
    }
    else
    {
        if(mode == IOTConstants::DEHUMIDIFIER_MODE_AUTO)
        {
            setSmartWindFN("3") ;
            setHighWindFN("3") ;
            setMediumWindFN("3") ;
            setLowWindFN("3") ;
        }
        else if (mode == IOTConstants::DEHUMIDIFIER_MODE_NORMAL)
        {
            setIndoorHumidityFN("2");
        }
        
        string atcmd =  IOTConstants::CMD_AT_MARK + "CSMS"
        + IOTConstants::CMD_AT_EQUALS_SINGNAL + deviceId
        + IOTConstants::PARAM_VALUE_SPLIT
        + mode
        + IOTConstants::PARAM_VALUE_SPLIT
        + IOTUtil::intToString(manualOrnot)
        + IOTConstants::CMD_AT_WRAP;
        return	createNetBytes(atcmd);
    }
}

/**
 * 4.定时开关机
 */
string DehumidifierLogic::setTimerControl(int enable, string time, int manualOrnot)
{
    if(checkWaterFullWarning())
    {
        return "";
    }
    
    ZD[3] = time;
    ZD[2] = IOTUtil::intToString(enable);
    string atcmd = IOTConstants::CMD_AT_MARK + "CSDS"
				+ IOTConstants::CMD_AT_EQUALS_SINGNAL + deviceId
				+ IOTConstants::PARAM_VALUE_SPLIT + time
				+ IOTConstants::PARAM_VALUE_SPLIT
				+ IOTUtil::intToString(enable)
				+ IOTConstants::PARAM_VALUE_SPLIT
				+ IOTUtil::intToString(manualOrnot)
				+ IOTConstants::CMD_AT_WRAP;
    return	createNetBytes(atcmd);
}

/**
 * 5.设置湿度
 */
string DehumidifierLogic::setHumidity(int humidity, int manualOrnot)
{
    string modeStatus = getModeStatus();
    if(modeStatus == "continue" || modeStatus == "auto")
    {
        return "";
    }
    
    //配置范围：30-80
    if(humidity < 30 || 80 < humidity)
    {
        return "";
    }
    
    stringstream stream;
    stream << humidity;
    
    stream >> ZD[4];
    string atcmd = IOTConstants::CMD_AT_MARK + "CSSD"
				+ IOTConstants::CMD_AT_EQUALS_SINGNAL + deviceId
				+ IOTConstants::PARAM_VALUE_SPLIT + ZD[4]
				+ IOTConstants::PARAM_VALUE_SPLIT
				+ IOTUtil::intToString(manualOrnot)
				+ IOTConstants::CMD_AT_WRAP;
    return	createNetBytes(atcmd);
}

/**
 * 6.设置温度
 */
string DehumidifierLogic::setTemperature(int temperature, int manualOrnot)
{
    if(getElectricHeatFN() == 2)
    {
        stringstream stream;
        stream << temperature;
        stream >> ZD[5];
        
        string atcmd = IOTConstants::CMD_AT_MARK + "CSWD"
        + IOTConstants::CMD_AT_EQUALS_SINGNAL + deviceId
        + IOTConstants::PARAM_VALUE_SPLIT + ZD[5]
        + IOTConstants::PARAM_VALUE_SPLIT
        + IOTUtil::intToString(manualOrnot)
        + IOTConstants::CMD_AT_WRAP;
        return	createNetBytes(atcmd);
    }
    else
    {
        return "";
    }
}

/**
 * 7.设置开关电源
 */
string DehumidifierLogic::setPower(int power, int manualOrnot)
{
    if(checkWaterFullWarning())
    {
        return "";
    }
    
    ZD[3] = "";
    ZD[7] = IOTUtil::intToString(power);
    string atcmd = IOTConstants::CMD_AT_MARK + "CSKJ" + IOTConstants::CMD_AT_EQUALS_SINGNAL
				+ deviceId + IOTConstants::PARAM_VALUE_SPLIT
				+ IOTUtil::intToString(power)
				+ IOTConstants::PARAM_VALUE_SPLIT
				+ IOTUtil::intToString(manualOrnot)
				+ IOTConstants::CMD_AT_WRAP;
    return	createNetBytes(atcmd);
}

/**
 * 8.设置开关电加热
 */
string DehumidifierLogic::setEletricHeatControl(int isEletricHeatOn, int manualOrnot)
{
    if(checkWaterPumpError())
    {
        return "";
    }
    
    if(isEletricHeatOn)
    {
        setContinueModeFN("3");
        setAutoModeFN("3");
        setNormalModeFN("3");
        setIndoorHumidityFN("3");
        setElectricHeatSetTemperatureFN("2");
    }
    else
    {
        setContinueModeFN("2");
        setAutoModeFN("2");
        setNormalModeFN("2");
        setIndoorHumidityFN("2");
    }
    
    ZD[8] = IOTUtil::intToString(isEletricHeatOn);
    string atcmd = IOTConstants::CMD_AT_MARK + "CSDJR"
				+ IOTConstants::CMD_AT_EQUALS_SINGNAL + deviceId
				+ IOTConstants::PARAM_VALUE_SPLIT
				+ IOTUtil::intToString(isEletricHeatOn)
				+ IOTConstants::PARAM_VALUE_SPLIT
				+ IOTUtil::intToString(manualOrnot)
				+ IOTConstants::CMD_AT_WRAP;
    return	createNetBytes(atcmd);
}

/**
 * 9.设置开关水泵
 */
string DehumidifierLogic::setWaterPumpControl(int enable, int manualOrnot)
{
    if(checkWaterPumpError())
    {
        return "";
    }
    
    string power = getPower();
    string waterPumpWarning = getWaterFullWarning();
    
    if(!(power == "1") || (waterPumpWarning == "1"))
    {
        return "";
    }
    
    ZD[9] = IOTUtil::intToString(enable);
    string atcmd = IOTConstants::CMD_AT_MARK + "CSSB"
				+ IOTConstants::CMD_AT_EQUALS_SINGNAL + deviceId
				+ IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(enable)
				+ IOTConstants::PARAM_VALUE_SPLIT
				+ IOTUtil::intToString(manualOrnot)
				+ IOTConstants::CMD_AT_WRAP;
    return	createNetBytes(atcmd);
}

/**
 * 10.设置开关负离子
 */
string DehumidifierLogic::setNegativeIonsControl(int enable, int manualOrnot)
{
    if(checkWaterPumpError())
    {
        return "";
    }
    
    string power = getPower();
    string waterPumpWarning = getWaterFullWarning();
    
    if(!(power == "1") || (waterPumpWarning == "1"))
    {
        return "";
    }
    
    ZD[10] = IOTUtil::intToString(enable);
    
    string atcmd = IOTConstants::CMD_AT_MARK + "CSFNZ"
				+ IOTConstants::CMD_AT_EQUALS_SINGNAL + deviceId
				+ IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(enable)
				+ IOTConstants::PARAM_VALUE_SPLIT
				+ IOTUtil::intToString(manualOrnot)
				+ IOTConstants::CMD_AT_WRAP;
    return	createNetBytes(atcmd);
}

/**
 * 11.设置CSSBox
 */
string DehumidifierLogic::setCSSBox(int on,string Mode,string WindSpeed_value,int humidity,int manualOrnot)
{
    if(Mode == IOTConstants::DEHUMIDIFIER_WIND_AUTO)
    {
        WindSpeed_value = IOTConstants::DEHUMIDIFIER_WIND_AUTO;
        humidity = 50;
    }
    
    ZD[0] = WindSpeed_value;
    ZD[1] = Mode;
    ZD[7] = IOTUtil::intToString(on);
    
    stringstream stream;
    stream << humidity;
    stream >> ZD[4];
    
    string atcmd = IOTConstants::CMD_AT_MARK  + "CSSBOX" + IOTConstants::CMD_AT_EQUALS_SINGNAL + deviceId + IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(on) +IOTConstants::PARAM_VALUE_SPLIT + Mode
    + IOTConstants::PARAM_VALUE_SPLIT + WindSpeed_value
    + IOTConstants::PARAM_VALUE_SPLIT + ZD[4] + IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(manualOrnot) + IOTConstants::CMD_AT_WRAP;
    return	createNetBytes(atcmd);
}

/********************************** 功能 **********************************/
/**
 * 获取功能使能状态
 */
int DehumidifierLogic::getCSFN(int offset)
{
    if(GN[offset] > 0 && GN_EN[offset] > 0)
    {
        return GN_EN[offset];
    }
    
    return 0;
}

/**
 *
 */
int DehumidifierLogic::getSmartWindFN()
{
    return getCSFN(0);
}

/**
 *
 */
int DehumidifierLogic::getHighWindFN()
{
    return getCSFN(1);
}

/**
 *
 */
int DehumidifierLogic::getMediumWindFN()
{
    return getCSFN(2);
}

/**
 *
 */
int DehumidifierLogic::getLowWindFN()
{
    return getCSFN(3);
}

/**
 *
 */
int DehumidifierLogic::getContinueModeFN()
{
    return getCSFN(4);
}

/**
 *
 */
int DehumidifierLogic::getNormalModeFN()
{
    return getCSFN(5);
}

/**
 *
 */
int DehumidifierLogic::getAutoModeFN()
{
    return getCSFN(6);
}

/**
 *
 */
int DehumidifierLogic::getTimerControlFN()
{
    return getCSFN(7);
}

/**
 * 电加热
 */
int DehumidifierLogic::getElectricHeatFN()
{
    return getCSFN(8);
}

/**
 *
 */
int DehumidifierLogic::getElectricHeatSetTemperatureFN()
{
    return getCSFN(9);
}

/**
 * 室内湿度
 */
int DehumidifierLogic::getIndoorHumidityFN()
{
    return getCSFN(10);
}

/**
 * 水泵
 */
int DehumidifierLogic::getWaterPumpFN()
{
    return getCSFN(11);
}

/**
 * 负离子
 */
int DehumidifierLogic::getAnionFN()
{
    return getCSFN(12);
}

/**
 * 电量检测
 */
int DehumidifierLogic::getElectronicDetectFN()
{
    return getCSFN(13);
}

/**
 * 开停机
 */
int DehumidifierLogic::getPowerFN()
{
    return getCSFN(14);
}

/**
 * EEPROM可改写功能
 */
int DehumidifierLogic::getEEPROMWriteFN()
{
    return getCSFN(15);
}

/**
 * 101#-0#第 7 字节预留位的控制功能
 */
int DehumidifierLogic::get7ReserverdFN()
{
    return getCSFN(16);
}

/**
 * 101#-0#第 8 字节预留位的控制功能
 */
int DehumidifierLogic::get8ReserverdFN()
{
    return getCSFN(17);
}

/********************************** 使能 **********************************/
/**
 * 设置功能使能状态
 */
void DehumidifierLogic::setCSFN(string value, int offset)
{
    if(value == "0")
    {
        GN[offset] = 0;
    }
    else if(value == "1")
    {
        GN[offset] = 1;
    }
    else if (value == "2")
    {
        GN_EN[offset] = 1;
    }
    else if (value == "3")
    {
        GN_EN[offset] = 0;
    }
    else
    {
        stringstream stream;
        stream << value;
        stream >> GN[offset];
    }
}

/**
 *
 */
void DehumidifierLogic::setSmartWindFN(string value)
{
    setCSFN(value, 0);
}

/**
 *
 */
void DehumidifierLogic::setHighWindFN(string value)
{
    setCSFN(value, 1);
}

/**
 *
 */
void DehumidifierLogic::setMediumWindFN(string value)
{
    setCSFN(value, 2);
}

/**
 *
 */
void DehumidifierLogic::setLowWindFN(string value)
{
    setCSFN(value, 3);
}

/**
 *
 */
void DehumidifierLogic::setContinueModeFN(string value)
{
    setCSFN(value, 4);
}

/**
 *
 */
void DehumidifierLogic::setNormalModeFN(string value)
{
    setCSFN(value, 5);
}

/**
 *
 */
void DehumidifierLogic::setAutoModeFN(string value)
{
    setCSFN(value, 6);
}

/**
 *
 */
void DehumidifierLogic::setTimerControlFN(string value)
{
    setCSFN(value, 7);
}

/**
 *
 */
void DehumidifierLogic::setElectricHeatFN(string value)
{
    setCSFN(value, 8);
}

/**
 *
 */
void DehumidifierLogic::setElectricHeatSetTemperatureFN(string value)
{
    setCSFN(value, 9);
}

/**
 *
 */
void DehumidifierLogic::setIndoorHumidityFN(string value)
{
    setCSFN(value, 10);
}

/**
 *
 */
void DehumidifierLogic::setWaterPumpFN(string value)
{
    setCSFN(value, 11);
}

/**
 *
 */
void DehumidifierLogic::setAnionFN(string value)
{
    setCSFN(value, 12);
}

/**
 *
 */
void DehumidifierLogic::setElectronicDetectFN(string value)
{
    setCSFN(value, 13);
}

/**
 *
 */
void DehumidifierLogic::setPowerFN(string value)
{
    setCSFN(value, 14);
}

/**
 *
 */
void DehumidifierLogic::setEEPROMWriteFN(string value)
{
    setCSFN(value, 15);
}

/**
 *
 */
void DehumidifierLogic::set7ReserverdFN(string value)
{
    setCSFN(value, 16);
}

/**
 *
 */
void DehumidifierLogic::set8ReserverdFN(string value)
{
    setCSFN(value, 17);
}


/********************************** 获取设备状态 **********************************/
/**
 * 获取风速
 */
string DehumidifierLogic::getWindSpeedStatus()
{
    return ZD[0];
}

/**
 * 获取模式
 */
string DehumidifierLogic::getModeStatus()
{
    return ZD[1];
}

/**
 * 获取定时开关机控制
 */
string DehumidifierLogic::getTimeStatus()
{
    return ZD[2];
}

/**
 * 获取定时开关机时间
 */
string DehumidifierLogic::getTimerValue()
{
    return ZD[3];
}

/**
 * 获取设置湿度
 */
string DehumidifierLogic::getSettingHumidityValue()
{
    return ZD[4];
}

/**
 * 获取电加热设定温度
 */
string DehumidifierLogic::getEletricHeatingTempratureStatus()
{
    return ZD[5];
}

/**
 * 获取室内温度
 */
string DehumidifierLogic::getIndoorTempStatus()
{
    return ZD[6];
}

/**
 * 获取除湿机电源开关状态
 */
string DehumidifierLogic::getPower()
{
    return ZD[7];
}

/**
 * 获取电加热功能开关状态
 */
string DehumidifierLogic::getEletricHeatingStatus()
{
    return ZD[8];
}

/**
 * 获取水泵开关状态
 */
string DehumidifierLogic::getWaterPumpStatus()
{
    return ZD[9];
}

/**
 * 获取负离子开关状态
 */
string DehumidifierLogic::getAnionStatus()
{
    return ZD[10];
}

/**
 * 本次命令之前有否红外和按键控制过
 */
string DehumidifierLogic::getInfrarediKeypadControl()
{
    return ZD[11];
}

/**
 * 本次命令之前有否 WIFI 控制过
 */
string DehumidifierLogic::getWifiControl()
{
    return ZD[12];
}

/**
 * 过滤网清洁告警
 */
string DehumidifierLogic::getFilterNetCleanWarning()
{
    return ZD[13];
}

/**
 * 湿度传感器故障
 */
string DehumidifierLogic::getHumidSensorError()
{
    return ZD[14];
}

/**
 *  管温传感器故障
 */
string DehumidifierLogic::getPumpTempratureError()
{
    return ZD[15];
}

/**
 * 室内温度传感器故障
 */
string DehumidifierLogic::getIndoorTempratureError()
{
    return ZD[16];
}

/**
 * 水满警告
 */
string DehumidifierLogic::getWaterFullWarning()
{
    return ZD[17];
}

/**
 * 水泵故障
 */
string DehumidifierLogic::getWaterPumpWarning()
{
    return ZD[18];
}

/**
 * 获取实际湿度
 */
string DehumidifierLogic::getRealHumidityValue()
{
    return ZD[19];
}

/**
 * 检测水满和水泵
 */
bool DehumidifierLogic::checkTwoError()
{
    if (checkWaterFullWarning() || checkWaterPumpError())
    {
        return true;
    }
    else
    {
        return false;
    }
}

/**
 * true为水满
 */
bool DehumidifierLogic::checkWaterFullWarning()
{
    if("1" == getWaterFullWarning())
    {
        return true;
    }
    else
    {
        return false;
    }
}

/**
 * 检查水泵
 */
bool DehumidifierLogic::checkWaterPumpError()
{
    if(getWaterPumpWarning() == "1")
    {
        setContinueModeFN("0");
        setNormalModeFN("0");
        setAutoModeFN("0");
        
        setPowerFN("0");
        setWaterPumpFN("0");
        setAnionFN("0");
        return true;
    }
    else
    {
        if(1)
        {
            setContinueModeFN("0");
            setNormalModeFN("0");
            setAutoModeFN("0");
            
            setPowerFN("0");
            setWaterPumpFN("0");
            setAnionFN("0");
        }
        
        return false;
    }
}

/**
 * 解析的返回数据
 */
bool DehumidifierLogic::parseAtCommand(string result)
{
    return false;
}