//
//  AirconditionLogic.cpp
//  Devices
//
//  Created by 肖芳亮 on 16/2/24.
//  Copyright © 2016年 XLF. All rights reserved.
//

#include "AirconditionLogic.h"
#include "IOTConstants.h"
#include "IOTUtil.h"

/*产品码个数*/
#define KLPRODUCT_CODE_COUNT  23

/*华氏温度数组长度*/
#define FAHRENHEIT_COUNT  47

/**
 * 华氏转摄氏对应数组
 */
const  int AirconditionLogic::fahrenheit[] = {
    16, 18, 20, 22, 23, 25, 27, 29, 31, 32,
    34, 36, 37, 39, 41, 43, 45, 46, 48, 50,
    52, 54, 55, 57, 59, 61, 63, 64, 66, 68,
    70, 72, 73, 75, 77, 79, 81, 82, 84, 86,
    88, 90, 91, 93, 95, 97, 99
};
const  int AirconditionLogic::celsius[] = {
    -9, -8, -7, -6, -5, -4, -3, -2, -1, 0,
    1,  2,  3,  4,  5,  6,  7,  8,  9, 10,
    11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
    21, 22, 23, 24, 25, 26, 27, 28, 29, 30,
    31, 32, 33, 34, 35, 36, 37
};

/**
 * 华氏切换到摄氏时，温度值转换显示对应数组
 */
const  int AirconditionLogic::fahrenheitSwitch[] = {
    61, 62, 63, 64, 65, 66, 67, 68, 69, 70,
    71, 72, 73, 74, 75, 76, 77, 78, 79, 80,
    81, 82, 83, 84, 85, 86, 87, 88, 89, 90
};

const  int AirconditionLogic::celsiusSwitch[] = {
    16, 16, 17, 18, 18, 19, 19, 20, 20, 21,
    21, 22, 23, 23, 24, 24, 25, 25, 26, 26,
    27, 28, 28, 29, 29, 30, 30, 31, 31, 32
    
};

AirconditionLogic::AirconditionLogic()
{
    DEVICE_TYPE = 0x01;
    At_QureyStatus="KTZD";
    At_QueryFuntion="KTGN";
    At_Setting="KTSET";
    
    At_Status_Num = 185;
    At_Funtion_Num = 51;
    
    for( int i = 0; i< At_Funtion_Num; i++)
    {
        GN.push_back(0);
    }
    
    for( int i = 0; i < At_Status_Num; i++)
    {
        ZD.push_back("0");
    }
    
    for( int i = 0; i < At_Funtion_Num; i++)
    {
        if(GN[i] > 0)
        {
            GN_EN.push_back(1);
        }
        else
        {
            GN_EN.push_back(0);
        }
    }
    
    //海信柜机
    setDeviceFunction("4,4,1,1,1,1,0,1,0,0,0,0,0,0,1,1,1,1,0,1,1,0,1,1,1,1,0,0,0,0,1,0,1,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0");
    
    //海信挂机
    //SaveAirConditionAllFun("4,4,1,1,1,1,0,1,0,0,0,7,0,0,1,1,1,0,0,1,1,0,1,1,1,1,0,0,0,0,1,0,0,1,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0");
    
    setPowerStatus(true);
}

AirconditionLogic::~AirconditionLogic()
{
    
}

/**
 * 华氏转摄氏
 */
int  AirconditionLogic::fahrenheitConvertToCelsius(int temperature)
{
    if(temperature < 16)
    {
        temperature = -9;
    }
    else if(temperature > 99)
    {
        temperature = 37;
    }
    else
    {
        for(int i = 0; i < FAHRENHEIT_COUNT; i++)
        {
            if(fahrenheit[i] == temperature )
            {
                temperature = celsius[i];
            }
        }
    }
    return temperature;
}

/**
 * 摄氏转华氏
 */
int  AirconditionLogic::celsiusConvertToFahrenheit(int temperature)
{
    if(temperature < -9)
    {
        temperature = 16;
    }
    else if(temperature > 37)
    {
        temperature = 99;
    }
    else
    {
        for(int i = 0; i < FAHRENHEIT_COUNT; i++)
        {
            if(celsius[i] == temperature )
            {
                temperature = fahrenheit[i];
            }
        }
    }
    return temperature;
}



/**
 * 华氏切换摄氏显示温度
 */
int AirconditionLogic::fahrenheitSwitchCelsiusDisplay(int temperature)
{
    if(temperature < 61)
    {
        temperature = 16;
    }
    else if(temperature > 90)
    {
        temperature = 32;
    }
    else
    {
        for(int i = 0; i < 30; i++)
        {
            if(fahrenheitSwitch[i] == temperature )
            {
                temperature = celsiusSwitch[i];
            }
        }
    }
    return temperature;
}

/**
 * 摄氏切换华氏显示温度
 */
int AirconditionLogic::celsiusSwitchFahrenheitDisplay(int temperature)
{
    if(temperature < 16)
    {
        temperature = 61;
    }
    else if(temperature > 32)
    {
        temperature = 90;
    }
    else
    {
        for(int i = 0; i < 30; i++)
        {
            if(celsius[i] == temperature )
            {
                temperature = fahrenheit[i];
            }
        }
    }
    return temperature;
}

/**
 * 华氏与摄氏切换显示
 */
int AirconditionLogic::temperatureSwitchDisplay(int temperatureDispaly)
{
    int temperature;
    if (IOTUtil::stringToInt(getTemperatureValueSwitch()) == true)
    {
        temperature = celsiusSwitchFahrenheitDisplay(temperatureDispaly);
        return temperature;
    }
    else if (IOTUtil::stringToInt(getTemperatureValueSwitch()) == false)
    {
        temperature = fahrenheitSwitchCelsiusDisplay(temperatureDispaly);
        return temperature;
    }
    return -1;
}

/**
 * 刷新功能表
 */
void AirconditionLogic::refreshFn()
{
    if (strcmp(getPower().c_str(),"1")==0)
    {
        //单冷机型，不支持制热
        if((strcmp(getMode().c_str(),"heat")==0) && getCoolModeFN()==0)
        {
            return ;
        }
        
        if((strcmp(getMode().c_str(),"cool")==0))
        {
            setDehumidificationModeFN("3");
            setWindSpeedFN("2");
            setSleepModeFN("2");
            setElectricalHeatingFN("3");
            setDualModeFN("2");
            setTemperatureFN("2");
            setEfficientFN("2");
            setEnergyConservationFN("2");
            setShareFN("2");
            setMuteFN("2");
        }
        
        if((strcmp(getMode().c_str(),"heat")==0) && getCoolModeFN()>0)
        {
            setDehumidificationModeFN("3");
            setSleepModeFN("2");
            setElectricalHeatingFN("2");
            setWindSpeedFN("2");
            setDualModeFN("2");
            setTemperatureFN("2");
            setEfficientFN("2");
            setEnergyConservationFN("2");
            setShareFN("2");
            setMuteFN("2");
        }
        
        if((strcmp(getMode().c_str(),"blow")==0))
        {
            setDehumidificationModeFN("3");
            setDualModeFN("3");
            setTemperatureFN("3");
            setEfficientFN("3");
            setEnergyConservationFN("3");
            setShareFN("3");
            setSleepModeFN("3");
            setElectricalHeatingFN("3");
            setWindSpeedFN("2");
            setMuteFN("2");
        }
        
        if((strcmp(getMode().c_str(),"dehumidify")==0))
        {
            setDehumidificationModeFN("2");
            setSleepModeFN("2");
            setWindSpeedFN("3");
            setElectricalHeatingFN("3");
            setDualModeFN("2");
            setTemperatureFN("2");
            setEfficientFN("2");
            setEnergyConservationFN("2");
            setShareFN("2");
            setMuteFN("2");
        }
        
        if((strcmp(getMode().c_str(),"auto")==0)){
            setDehumidificationModeFN("3");
            setMuteFN("3");
            setElectricalHeatingFN("3");
            setEfficientFN("3");
            setSleepModeFN("3");
            setDualModeFN("2");
            setTemperatureFN("2");
            setEnergyConservationFN("2");
            setShareFN("2");
            setWindSpeedFN("2");
            
        }
        
        if((strcmp(getDualMode().c_str(),"1")==0)&& getDualModeFN()>0 )
        {
            setEnergyConservationFN("3");
            setShareFN("3");
        }
    }
}

/**
 * 根据开关状态 设置默认状态
 */
void AirconditionLogic::setPowerStatus(int PowerOn)
{
    if(PowerOn)
    {
        setWindSpeedFN("2");
        if((strcmp(getMode().c_str(),"dehumidify")==0)|| !(strcmp(getMode().c_str(),"off")==0))
        {
            setWindSpeedFN("3");
        }
        setSleepModeFN("2");
        if((strcmp(getMode().c_str(),"auto")==0)|| (strcmp(getMode().c_str(),"blow")==0))
        {
            setSleepModeFN("3");
        }
        setModeFN("2");
        setTemperatureFN("2");
        setHumidityFN("2");
        setSomatosensoryRealityTemperatureFN("2");
        setTemperatureCompensationFN("2");
        setTemperatureValueSwitchFN("2");
        setGeneralTimingShutdownFN("2");
        setRealityTimeFN("2");
        setVerticalWindFN("2");
        setHorizontalWindFN("2");
        setNatureWindFN("2");
        if((strcmp(getMode().c_str(),"heat")==0)&& getCoolModeFN()>0)
        {
            setElectricalHeatingFN("2");
        }
        if((strcmp(getMode().c_str(),"dehumidify")==0))
        {
            setDehumidificationModeFN("2");
        }
        
        setEnergyConservationFN("2");
        setShareFN("2");
        
        if((strcmp(getMode().c_str(),"blow")==0) || (strcmp(getDualMode().c_str(),"1")==0))
        {
            setEnergyConservationFN("3");
            setShareFN("3");
        }
        setEfficientFN("2");
        
        if(getEnergyConservation() == "1"||getMode() == "blow"|| getMode() == "auto"){
            setEfficientFN("3");
        }
        setDualModeFN("2");
        if((strcmp(getShare().c_str(),"1")==0) || (strcmp(getEnergyConservation().c_str(),"1")==0)){
            setDualModeFN("3");
        }
        setFreshnessFN("2");
        setFreshAirFN("2");
        setClernIndoorFN("2");
        setClernOutdoorFN("2");
        setSmartEyeFN("2");
        setMuteFN("2");
        setVoiceFN("2");
        setClernSmokeFN("2");
        setBackgroundLampFN("2");
        setScreenFN("2");
        setLEDFN("2");
        setIndoorOutdoorSwitchFN("2");
    }
    else
    {
        setWindSpeedFN("3");
        setSleepModeFN("3");
        setHumidityFN("3");
        setTemperatureValueSwitchFN("2");
        setGeneralTimingShutdownFN("3");
        setRealityTimeFN("4");
        setHorizontalWindFN("3");
        setNatureWindFN("3");
        setElectricalHeatingFN("3");
        setDehumidificationModeFN("3");
        setEnergyConservationFN("3");
        setShareFN("3");
        setEfficientFN("3");
        setDualModeFN("3");
        setFreshnessFN("3");
        setFreshAirFN("3");
        setClernIndoorFN("3");
        setClernOutdoorFN("3");
        setSmartEyeFN("3");
        setMuteFN("3");
        setVoiceFN("3");
        setClernSmokeFN("3");
        setBackgroundLampFN("3");
        setScreenFN("3");
        setLEDFN("3");
        setIndoorOutdoorSwitchFN("3");
    }
}

/*********************** 状态获取 ***********************/
/**
 * 获取风量
 */
string AirconditionLogic::getWindSpeed()
{
    return ZD[0];
}

/**
 * 获取睡眠
 */
string AirconditionLogic::getSleepMode()
{
    return ZD[1];
}

/**
 * 获取xx
 */
string AirconditionLogic::getSleep()
{
    return ZD[182];
}

/**
 * 获取模式
 */
string AirconditionLogic::getMode()
{
    return ZD[2];
}

/**
 * 获取开机
 */
string AirconditionLogic::getPower()
{
    return ZD[3];
}

/**
 * 获取风量
 */
/*风向*/
string AirconditionLogic::getWindDirection()
{
    return ZD[4];
}

/**
 * 获取设置温度
 */
string AirconditionLogic::getSetingTemperature()
{
    return ZD[5];
}

/**
 * 获取湿度
 */
string AirconditionLogic::getHumidity()
{
    return ZD[6];
}

/**
 * 获取体感室内温度
 */
string AirconditionLogic::getSomatosensoryRealityTemperature()
{
    return ZD[7];
}

/**
 * 获取室内实际温度
 */
string AirconditionLogic::getIndoorRealityTemperature()
{
    return ZD[8];
}

/**
 * 获取室内盘管温度
 */
string AirconditionLogic::getIndoorPipeTemperature()
{
    return ZD[9];
}

/**
 * 获取室内实际湿度值
 */
string AirconditionLogic::getIndoorRealityHumidity()
{
    return ZD[10];
}

/**
 * 获取体感室内温度补偿
 */
string AirconditionLogic::getSomatosensoryCompensation()
{
    return ZD[11];
}

/**
 * 获取体感控制
 */
string AirconditionLogic::getSomatosensoryContrl()
{
    return ZD[12];
}

/**
 * 获取自动工作模式和除湿模式的温度补偿
 */
string AirconditionLogic::getTemperatureCompensation()
{
    return ZD[13];
}

/**
 * 获取华氏/摄氏温度显示设置
 */
string AirconditionLogic::getTemperatureValueSwitch()
{
    return ZD[14];
}

/**
 * 获取普通定时开关机
 */
string AirconditionLogic::getGeneralTimingShutdownValue()
{
    return ZD[15];
}

/**
 * 获取实时时钟的小时值
 */
string AirconditionLogic::getRealityHour()
{
    return ZD[16];
}

/**
 * 获取实时时钟的分钟值
 */
string AirconditionLogic::getRealityMinute()
{
    return ZD[17];
}

/**
 * 获取实时开机控制
 */
string AirconditionLogic::getRealityBootContrl()
{
    return ZD[18];
}

/**
 * 获取实时开机小时
 */
string AirconditionLogic::getRealityBootHour()
{
    return ZD[19];
}

/**
 * 获取实时开机分钟
 */
string AirconditionLogic::getRealityBootMinute()
{
    return ZD[20];
}

/**
 * 获取实时关机控制
 */
string AirconditionLogic::getRealityShutdownContrl()
{
    return ZD[21];
}

/**
 * 获取实时关机小时
 */
string AirconditionLogic::getRealityShutdownHour()
{
    return ZD[22];
}

/**
 * 获取实时关机分钟
 */
string AirconditionLogic::getRealityShutdownMinute()
{
    return ZD[23];
}

/**
 * 获取除湿模式
 */
string AirconditionLogic::getDehumidificationMode()
{
    return ZD[24];
}

/**
 * 获取上下风门
 */
string AirconditionLogic::getVerticalWindMode()
{
    if (getVerticalWindModeNum() == 0)
    {
        if (IOTUtil::stringToInt(getVerticalWindContrl()))
            ZD[25] = "sweep";
        else
            ZD[25] = "fixed";
    }
    
    return ZD[25];
}

/**
 * 获取上下风开停控制
 */
string AirconditionLogic::getVerticalWindContrl()
{
    return ZD[26];
}

/**
 * 获取左右风开停控制
 */
string AirconditionLogic::getHorizontalWindContrl()
{
    return ZD[27];
}

/**
 * 获取自然风开停控制
 */
string AirconditionLogic::getNatureWindContrl()
{
    return ZD[28];
}

/**
 * 获取电热
 */
string AirconditionLogic::getElectricalHeating()
{
    return ZD[29];
}

/**
 * 获取节能
 */
string AirconditionLogic::getEnergyConservation()
{
    return ZD[30];
}

/**
 * 获取并用节电
 */
string AirconditionLogic::getShare()
{
    return ZD[31];
}

/**
 * 获取高效
 */
string AirconditionLogic::getEfficient()
{
    return ZD[32];
}

/**
 * 获取双模
 */
string AirconditionLogic::getDualMode()
{
    return ZD[33];
}

/**
 * 获取清新
 */
string AirconditionLogic::getFreshness()
{
    return ZD[34];
}

/**
 * 获取换风
 */
string AirconditionLogic::getFreshAir()
{
    return ZD[35];
}

/**
 * 获取室内清洁
 */
string AirconditionLogic::getClernIndoor()
{
    return ZD[36];
}

/**
 * 获取室外清洁
 */
string AirconditionLogic::getClernOutdoor()
{
    return ZD[37];
}

/**
 * 获取智慧眼
 */
string AirconditionLogic::getSmartEye()
{
    return ZD[38];
}

/**
 * 获取静音
 */
string AirconditionLogic::getMute()
{
    return ZD[39];
}

/**
 * 获取语音
 */
string AirconditionLogic::getVoice()
{
    return ZD[40];
}

/**
 * 获取除烟
 */
string AirconditionLogic::getClernSmoke()
{
    return ZD[41];
}

/**
 * 获取背景灯
 */
string AirconditionLogic::getBackgroundLamp()
{
    return ZD[42];
}

/**
 * 获取显示屏发光
 */
string AirconditionLogic::getScreen()
{
    return ZD[43];
}

/**
 * 获取LED指示灯
 */
string AirconditionLogic::getLED()
{
    return ZD[44];
}

/**
 * 获取室内外温度切换显示
 */
string AirconditionLogic::getIndoorOutdoorSwitch()
{
    return ZD[45];
}

/**
 * 获取室内过滤网清洁复位控制
 */
string AirconditionLogic::getIndoorFilterClear()
{
    return ZD[46];
}

/**
 * 获取左风摆
 */
string AirconditionLogic::getLeftWind()
{
    return ZD[47];
}

/**
 * 获取右风摆
 */
string AirconditionLogic::getRightWind()
{
    return ZD[48];
}

/**
 * 获取室内电量板
 */
string AirconditionLogic::getChargeBorad ()
{
    return ZD[49];
}

/**
 * 获取本次命令之前是否有过红外遥控与按键控制过
 */
string AirconditionLogic::getHaveIRContrl()
{
    return ZD[50];
}

/**
 * 获取本次命令之前是否有过WIFI控制过
 */
string AirconditionLogic::getHaveWIFIContrl()
{
    return ZD[51];
}

/**
 * 获取空调正常机型与测试机型
 */
string AirconditionLogic::getModel()
{
    return ZD[52];
}

/**
 * 获取室内EEPROM在线升级
 */
string AirconditionLogic::getEEPROMUpdate()
{
    return ZD[53];
}

/**
 * 获取室内温度传感器故障
 */
string AirconditionLogic::getIndoorTemperatureSensorTrouble()
{
    return ZD[54];
}

/**
 * 获取室内盘管温度传感器故障
 */
string AirconditionLogic::getIndoorPipeTemperatureSensorTrouble()
{
    return ZD[55];
}

/**
 * 获取室内湿度传感器故障
 */
string AirconditionLogic::getIndoorHumiditySensorTrouble()
{
    return ZD[56];
}

/**
 * 获取室内排水泵故障
 */
string AirconditionLogic::getIndoorDrainsWaterPumpTrouble()
{
    return ZD[57];
}

/**
 * 获取室内风机电机运转异常故障
 */
string AirconditionLogic::getIndoorFanMotorTrouble()
{
    return ZD[58];
}

/**
 * 获取柜机格栅保护告警
 */
string AirconditionLogic::getPioneerGrillingProtectTrouble()
{
    return ZD[59];
}

/**
 * 获取室内电压过零检测故障
 */
string AirconditionLogic::getIndoorVoltageZeroCrossDetectionTrouble()
{
    return ZD[60];
}

/**
 * 获取室内外通信故障
 */
string AirconditionLogic::getIndoorOutdoorCommunicationTrouble()
{
    return ZD[61];
}

/**
 * 获取室内控制板与显示板通信故障
 */
string AirconditionLogic::getIndoorContrlScreenCommunicationTrouble()
{
    return ZD[62];
}

/**
 * 获取室内控制板与按键板通信故障
 */
string AirconditionLogic::getIndoorContrlKeypadCommunicationTrouble()
{
    return ZD[63];
}

/**
 * 获取WIFI控制板与室内控制板通信故障
 */
string AirconditionLogic::getIndoorContrlWIFICommunicationTrouble()
{
    return ZD[64];
}

/**
 * 获取室内控制板与室内电量板通信故障
 */
string AirconditionLogic::getIndoorContrlChargeCommunicationTrouble()
{
    return ZD[65];
}

/**
 * 获取室内控制板EEPROM出错
 */
string AirconditionLogic::getIndoorContrlEEPROMTrouble()
{
    return ZD[66];
}

/**
 * 获取运行频率
 */
string AirconditionLogic::getRunFrequency()
{
    return ZD[67];
}

/**
 * 获取目标频率
 */
string AirconditionLogic::getTargetFrequency()
{
    return ZD[68];
}

/**
 * 获取发给驱动器的频率
 */
string AirconditionLogic::getDriveFrequency()
{
    return ZD[69];
}

/**
 * 获取环境温度
 */
string AirconditionLogic::getEnvironmentTemperature()
{
    return (ZD[70]);
}

/**
 * 获取冷凝器温度
 */
string AirconditionLogic::getCondenserTemperature()
{
    return (ZD[71]);
}

/**
 * 获取排气温度
 */
string AirconditionLogic::getExhaustTemperature()
{
    return ZD[72];
}

/**
 * 获取目标排气温度
 */
string AirconditionLogic::getTargetExhaustTemperature()
{
    return ZD[73];
}

/**
 * 获取室外电子膨胀阀开度
 */
string AirconditionLogic::getOutdoorElectronicExpansion()
{
    return ZD[74];
}

/**
 * 获取UABH
 */
string AirconditionLogic::getUABH()
{
    return ZD[75];
}

/**
 * 获取UABL
 */
string AirconditionLogic::getUABL()
{
    return ZD[76];
}

/**
 * 获取UBCH
 */
string AirconditionLogic::getUBCH()
{
    return ZD[77];
}

/**
 * 获取UBCL
 */
string AirconditionLogic::getUBCL()
{
    return ZD[78];
}

/**
 * 获取UCAH
 */
string AirconditionLogic::getUCAH()
{
    return ZD[79];
}

/**
 * 获取UCAL
 */
string AirconditionLogic::getUCAL()
{
    return ZD[80];
}

/**
 * 获取IAB
 */
string AirconditionLogic::getIAB()
{
    return ZD[81];
}

/**
 * 获取IBC
 */
string AirconditionLogic::getIBC()
{
    return ZD[82];
}

/**
 * 获取ICA
 */
string AirconditionLogic::getICA()
{
    return ZD[83];
}

/**
 * 获取IUV
 */
string AirconditionLogic::getIUV()
{
    return ZD[84];
}

/**
 * 获取直流母线电压H
 */
string AirconditionLogic::getCocurrentBusVoltageH()
{
    return ZD[85];
}

/**
 * 获取直流母线电压L
 */
string AirconditionLogic::getCocurrentBusVoltageL()
{
    return ZD[86];
}

/**
 * 获取四通阀状态
 */
string AirconditionLogic::getFourWayLimen()
{
    return ZD[87];
}

/**
 * 获取室外机实际工作状态
 */
string AirconditionLogic::getOutdoorRealityRuning()
{
    return ZD[88];
}

/**
 * 获取风机运行状态
 */
string AirconditionLogic::getFanRuning()
{
    return ZD[89];
}

/**
 * 获取室外机强制室内机风门位置
 */
string AirconditionLogic::getOutdoorForceIndoorWindPosition()
{
    return ZD[90];
}

/**
 * 获取室外机强制室内机风速
 */
string AirconditionLogic::getOutdoorForceIndoorWindSpeed()
{
    return ZD[91];
}

/**
 * 获取室外机强制室内机停
 */
string AirconditionLogic::getOutdoorForceIndoorStop()
{
    return ZD[92];
}

/**
 * 获取温控关机
 */
string AirconditionLogic::getShutdownByTemperatureContrl()
{
    return ZD[93];
}

/**
 * 获取一拖多标志
 */
string AirconditionLogic::getOne4All()
{
    return ZD[94];
}

/**
 * 获取除湿阀标志
 */
string AirconditionLogic::getDehumidifierLimen()
{
    return ZD[95];
}

/**
 * 获取室外机化霜
 */
string AirconditionLogic::getOutdoorDefrosting()
{
    return ZD[96];
}

/**
 * 获取室外旁通化霜
 */
string AirconditionLogic::getOutdoorBypassDefrosting()
{
    return ZD[97];
}

/**
 * 获取回油标志
 */
string AirconditionLogic::getOilReturn()
{
    return ZD[98];
}

/**
 * 获取室外故障显示标志
 */
string AirconditionLogic::getOutdoorTroubleDisplay()
{
    return ZD[99];
}

/**
 * 获取室外机EEPROM在线下载标志
 */
string AirconditionLogic::getOutdoorEEPROMDownload()
{
    return ZD[100];
}

/**
 * 获取室外机电量板
 */
string AirconditionLogic::getOutdoorChargeBoard()
{
    return ZD[101];
}

/**
 * 获取压缩机电热带
 */
string AirconditionLogic::getcompressorRibbonHeater()
{
    return ZD[102];
}

/**
 * 获取
 */
/*压缩机预加热*/
string AirconditionLogic::getcompressorBeforeHandheat()
{
    return ZD[103];
}

/**
 * 获取补气增晗
 */
string AirconditionLogic::getReinflation()
{
    return ZD[104];
}

/**
 * 获取室内外机模式冲突
 */
string AirconditionLogic::getOutdoorModeClash()
{
    return ZD[105];
}

/**
 * 获取室外EEPROM出错
 */
string AirconditionLogic::getOutdoorEEPROMTrouble()
{
    return ZD[106];
}

/**
 * 获取室外盘管温度传感器故障
 */
string AirconditionLogic::getOutdoorPipeTemperatureSensorTrouble()
{
    return ZD[107];
}

/**
 * 获取排气温度传感器故障
 */
string AirconditionLogic::getOutdoorExhausTemperatureSensorTrouble()
{
    return ZD[108];
}

/**
 * 获取室外环境温度传感器故障
 */
string AirconditionLogic::getOutdoorEnvironmentTemperatureSensorTrouble()
{
    return ZD[109];
}

/**
 * 获取电压变压器故障
 */
string AirconditionLogic::getVoltageTransformerTrouble()
{
    return ZD[110];
}

/**
 * 获取电流互感器故障
 */
string AirconditionLogic::getCurrentTransformerTrouble()
{
    return ZD[111];
}

/**
 * 获取室外控制与驱动通信故障
 */
string AirconditionLogic::getOutdoorContrlDriveCommunicationTrouble()
{
    return ZD[112];
}

/**
 * 获取IPM模块过流保护
 */
string AirconditionLogic::getIPMOvercurrentProtect()
{
    return ZD[113];
}

/**
 * 获取IPM模块过热保护
 */
string AirconditionLogic::getIPMOverheatingProtect()
{
    return ZD[114];
}

/**
 * 获取交流电过电压保护
 */
string AirconditionLogic::getAlternatingCurrentOvervoltageProtect()
{
    return ZD[115];
}

/**
 * 获取交流电欠电压保护
 */
string AirconditionLogic::getAlternatingCurrentUndervoltageProtect()
{
    return ZD[116];
}

/**
 * 获取母线电压过电压保护
 */
string AirconditionLogic::getBusbarVoltageOvervoltageProtect()
{
    return ZD[117];
}

/**
 * 获取
 */
/*母线电压欠电压保护*/
string AirconditionLogic::getBusbarVoltageUndervoltageProtect()
{
    return ZD[118];
}

/**
 * 获取PFC过电流保护
 */
string AirconditionLogic::getPFCOvercurrentProtect()
{
    return ZD[119];
}

/**
 * 获取室外机最大电流保护
 */
string AirconditionLogic::getOutdoorMaximumCurrentProtect()
{
    return ZD[120];
}

/**
 * 获取室外环境温度过低保护
 */
string AirconditionLogic::getOutdooEnvironmentOvertemperatureProtect()
{
    return ZD[121];
}

/**
 * 获取排气温度过高保护
 */
string AirconditionLogic::getExhaustOvertemperatureProtect()
{
    return ZD[122];
}

/**
 * 获取压缩机管壳温度保护
 */
string AirconditionLogic::getCompressoPipeShellTemperatureProtect()
{
    return ZD[123];
}

/**
 * 获取室内防冻结或防过载保护
 */
string AirconditionLogic::getIndoorAntiFreezingProtect()
{
    return ZD[124];
}

/**
 * 获取室外机PFC保护
 */
string AirconditionLogic::getOutdoorPFCProtect()
{
    return ZD[125];
}

/**
 * 获取压缩机启动失败
 */
string AirconditionLogic::getCompressoBootFail()
{
    return ZD[126];
}

/**
 * 获取压缩机失步
 */
string AirconditionLogic::getCompressoStepOut()
{
    return ZD[127];
}

/**
 * 获取室外风机堵转
 */
string AirconditionLogic::getOutdoorFanLockRotor()
{
    return ZD[128];
}

/**
 * 获取室外盘管防过载保护
 */
string AirconditionLogic::getOutdoorPieOverloadProtect()
{
    return ZD[129];
}

/**
 * 获取冷媒泄漏
 */
string AirconditionLogic::getRefrigerantLeakage()
{
    return ZD[130];
}

/**
 * 获取压缩机型号匹配错误
 */
string AirconditionLogic::getCompressoModelMismatch()
{
    return ZD[131];
}

/**
 * 获取系统低频振动保护
 */
string AirconditionLogic::getSystemLowFrequencyVibrationProtect()
{
    return ZD[132];
}

/**
 * 获取室外散热器温度过高保护
 */
string AirconditionLogic::getOutdoorRadiatorOvertemperatureProtect()
{
    return ZD[133];
}

/**
 * 获取系统压力过高保护
 */
string AirconditionLogic::getSystemHypertonusProtect()
{
    return ZD[134];
}

/**
 * 获取逆变器直流过电压故障
 */
string AirconditionLogic::getInverterCocurrentOvervoltageTrouble()
{
    return ZD[135];
}

/**
 * 获取逆变器直流低电压故障
 */
string AirconditionLogic::getInverterCocurrentUndervoltageTrouble()
{
    return ZD[136];
}

/**
 * 获取逆变器交流过电流故障
 */
string AirconditionLogic::getInverterCocurrentOvercurrentTrouble()
{
    return ZD[137];
}

/**
 * 获取失步检出
 */
string AirconditionLogic::getStepOutDetection()
{
    return ZD[138];
}

/**
 * 获取速度推定脉冲检出法检出欠相故障
 */
string AirconditionLogic::getSpeedPulseFault()
{
    return ZD[139];
}

/**
 * 获取电流推定脉冲检出法检出欠相故障
 */
string AirconditionLogic::getCurrentPulseFault()
{
    return ZD[140];
}

/**
 * 获取逆变器IPM故障-边沿
 */
string AirconditionLogic::getInverterEdgeFault()
{
    return ZD[141];
}

/**
 * 获取逆变器IPM故障-电平
 */
string AirconditionLogic::getInverterLevelFault()
{
    return ZD[142];
}

/**
 * 获取PFC_IPM故障-边沿
 */
string AirconditionLogic::getPFC_IPMEdgeFault()
{
    return ZD[143];
}

/**
 * 获取PFC_IPM故障-电平
 */
string AirconditionLogic::getPFC_IPMLevelFault()
{
    return ZD[144];
}

/**
 * 获取PFC停电检出故障
 */
string AirconditionLogic::getPFCPowerCutFault()
{
    return ZD[145];
}

/**
 * 获取PFC过电流检出故障
 */
string AirconditionLogic::getPFCOvercurrentFault()
{
    return ZD[146];
}

/**
 * 获取直流电压检出异常
 */
string AirconditionLogic::getDCVException()
{
    return ZD[147];
}

/**
 * 获取PFC低电压（有效值）检出故障
 */
string AirconditionLogic::getPFCLowVoltageFault()
{
    return ZD[148];
}

/**
 * 获取AD偏置异常检出故障
 */
string AirconditionLogic::getADOffsetAnomaliesFault()
{
    return ZD[149];
}

/**
 * 获取逆变器PWM逻辑设置故障
 */
string AirconditionLogic::getInverterPWMLogicFault()
{
    return ZD[150];
}

/**
 * 获取逆变器PWM初始化故障
 */
string AirconditionLogic::getInverterPWMInitFault()
{
    return ZD[151];
}

/**
 * 获取PFC_PWM逻辑设置故障
 */
string AirconditionLogic::getPFCPWMLogicFault()
{
    return ZD[152];
}

/**
 * 获取PFC_PWM初始化故障
 */
string AirconditionLogic::getPFC_PWMInitFault()
{
    return ZD[153];
}

/**
 * 获取温度异常
 */
string AirconditionLogic::getTemperatureAnomaly()
{
    return ZD[154];
}

/**
 * 获取电流采样电阻不平衡调整故障
 */
string AirconditionLogic::getCurrentSamplingFault()
{
    return ZD[155];
}

/**
 * 获取电机参数设置故障
 */
string AirconditionLogic::getMotorDataFault()
{
    return ZD[156];
}

/**
 * 获取MCE故障
 */
string AirconditionLogic::getMCEFault()
{
    return ZD[157];
}

/**
 * 获取驱动EEPROM故障
 */
string AirconditionLogic::getEEPROMFault()
{
    return ZD[158];
}

/**
 * 获取室外盘管过载禁升频
 */
string AirconditionLogic::getOutdoorCoilOverloadUpFrequency()
{
    return ZD[159];
}

/**
 * 获取室外盘管过载降频
 */
string AirconditionLogic::getOutdoorCoilOverloadDownFrequency()
{
    return ZD[160];
}

/**
 * 获取室内盘管过载禁升频
 */
string AirconditionLogic::getIndoorCoilOverloadUpFrequency()
{
    return ZD[161];
}

/**
 * 获取室内盘管过载降频
 */
string AirconditionLogic::getIndoorCoilOverloadDownFrequency()
{
    return ZD[162];
}

/**
 * 获取压降排气过载禁升频
 */
string AirconditionLogic::getPressureUpFrequency()
{
    return ZD[163];
}

/**
 * 获取压降排气过载降频
 */
string AirconditionLogic::getPressureDownFrequency()
{
    return ZD[164];
}

/**
 * 获取室内盘管冻结禁升频
 */
string AirconditionLogic::getIndoorCoilFreezingUpFrequency()
{
    return ZD[165];
}

/**
 * 获取室内盘管冻结降频
 */
string AirconditionLogic::getIndoorCoilFreezingDownFrequency()
{
    return ZD[166];
}

/**
 * 获取室内外通信降频
 */
string AirconditionLogic::getCommunicationDownFrequency()
{
    return ZD[167];
}

/**
 * 获取模块温度过载限频
 */
string AirconditionLogic::getModuleTemperaturelimitFrequency()
{
    return ZD[168];
}

/**
 * 获取变调率限频
 */
string AirconditionLogic::getModulationRatelimitFrequency()
{
    return ZD[169];
}

/**
 * 获取相电流限频
 */
string AirconditionLogic::getPhaseCurrentlimitFrequency()
{
    return ZD[170];
}

/**
 * 获取并用节电保护禁升频
 */
string AirconditionLogic::getPowerSaveUpFrequency()
{
    return ZD[171];
}

/**
 * 获取并用节电保护降频
 */
string AirconditionLogic::getPowerSaveDownFrequency()
{
    return ZD[172];
}

/**
 * 获取过电流保护禁升频
 */
string AirconditionLogic::getOvercurrentUpFrequency()
{
    return ZD[173];
}

/**
 * 获取过电流保护降频
 */
string AirconditionLogic::getOvercurrentDownFrequency()
{
    return ZD[174];
}

/**
 * 获取室内风机转速xx
 */
string AirconditionLogic::getIndoorFanSpeedH()
{
    return ZD[175];
}

/**
 * 获取室内风机转速00xx
 */
string AirconditionLogic::getIndoorFanSpeed00L()
{
    return ZD[176];
}

/**
 * 获取有否PM2.5检测功能
 */
string AirconditionLogic::getPM25()
{
    return ZD[177];
}

/**
 * 获取PM2.5污染程度
 */
string AirconditionLogic::getPM25Level()
{
    return ZD[178];
}

/**
 * 获取空气PM2.5质量百分比表示
 */
string AirconditionLogic::getPM25Percent()
{
    return ZD[179];
}

/**
 * 获取显示屏亮度值
 */
string AirconditionLogic::getScreenLuminance()
{
    return ZD[180];
}

/**
 * 获取普通定时开关机有效
 */
string AirconditionLogic::getGeneralTimingShutdown()
{
    return ZD[181];
}

/**************************************** 功能 ****************************************/
/**
 * 设置功能
 */
void AirconditionLogic::setKtFN(string value,int offset)
{
    if((strcmp(value.c_str(),"0")==0)){
        GN[offset]=0;
    }else if((strcmp(value.c_str(),"1")==0)){
        GN[offset]=1;
    }else if((strcmp(value.c_str(),"2")==0)){
        GN_EN[offset]=1;
    }else if((strcmp(value.c_str(),"3")==0)){
        GN_EN[offset]=0;
    }else if((strcmp(value.c_str(),"4")==0)){
        GN_EN[offset]=4;
    }else{
        GN[offset]=IOTUtil::stringToInt(value);;
    }
}

/**
 * 获取功能
 */
int AirconditionLogic::getKtFN(int offset)
{
    if((GN[offset]>0) && (GN_EN[offset]>0) && (GN_EN[offset]<4))
    {
        return GN[offset];
    }
    else if (GN_EN[offset]>=4)
    {
        return GN_EN[offset];
    }
    return 0;
}

/********* 设置功能 ********/
/**
 * 获取命令支持状态
 */
int AirconditionLogic::getWindSpeedNum()
{
    return getKtFN(0);
}

/**
 * 设置睡眠模式
 */
int AirconditionLogic::getSleepModeFN()
{
    return getKtFN(1);
}

/**
 * 设置模式
 */
int AirconditionLogic::getCoolModeFN()
{
    return getKtFN(2);
}

/**
 * 开/关机
 */
int AirconditionLogic::getPowerFN()
{
    return getKtFN(3);
}

/**
 * 室内单个风向控制功能
 */
int AirconditionLogic::getWindDirectionFN()
{
    return getKtFN(4);
}

/**
 * 设置温度
 */
int AirconditionLogic::getTemperatureFN()
{
    return getKtFN(5);
}

/**
 * 设置湿度
 */
int AirconditionLogic::getHumidityFN()
{
    return getKtFN(6);
}

/**
 * 体感控制,体感室内温度,体感室内温度补偿
 */
int AirconditionLogic::getSomatosensoryRealityTemperatureFN()
{
    return getKtFN(8);
}

/**
 * 自动工作模式和除湿模式的温度补偿
 */
int AirconditionLogic::getTemperatureCompensationFN()
{
    return getKtFN(9);
}

/**
 * 华氏/摄氏温度显示设置
 */
int AirconditionLogic::getTemperatureValueSwitchFN()
{
    return getKtFN(12);
}

/**
 * 普通定时关机,普通定时关机时间
 */
int AirconditionLogic::getGeneralTimingShutdownFN()
{
    return getKtFN(13);
}

/**
 * 实时开机控制,实时时钟的小时值,实时时钟的分钟值,实时开机小时,实时开机分钟
 */
int AirconditionLogic::getRealityTimeFN()
{
    return getKtFN(14);
}

/**
 * 6位置可定室内风门位置控制
 */
int AirconditionLogic::getVerticalWindModeNum()
{
    return getKtFN(15);
}

/**
 * 上下风门模式,上下风开停控制
 */
int AirconditionLogic::getVerticalWindFN()
{
    return getKtFN(16);
}

/**
 * 左右风开停控制,左风摆,右风摆
 */
int AirconditionLogic::getHorizontalWindFN()
{
    return getKtFN(17);
}

/**
 * 自然风开停
 */
int AirconditionLogic::getNatureWindFN()
{
    return getKtFN(18);
}

/**
 * 设置电加热
 */
int AirconditionLogic::getElectricalHeatingFN()
{
    return getKtFN(19);
}

/**
 * 除湿模式
 */
int AirconditionLogic::getDehumidificationModeFN()
{
    return getKtFN(20);
}

/**
 * 设置节能
 */
int AirconditionLogic::getEnergyConservationFN()
{
    return getKtFN(21);
}

/**
 * 设置并且节能
 */
int AirconditionLogic::getShareFN()
{
    return getKtFN(22);
}

/**
 * 设置高效
 */
int AirconditionLogic::getEfficientFN()
{
    return getKtFN(23);
}

/**
 * 设置双模
 */
int AirconditionLogic::getDualModeFN()
{
    return getKtFN(24);
}

/**
 * 设置清新
 */
int AirconditionLogic::getFreshnessFN()
{
    return getKtFN(25);
}

/**
 * 设置换风
 */
int AirconditionLogic::getFreshAirFN()
{
    return getKtFN(26);
}

/**
 * 设置室内清洁
 */
int AirconditionLogic::getClernIndoorFN()
{
    return getKtFN(27);
}

/**
 * 设置室外清洁
 */
int AirconditionLogic::getClernOutdoorFN()
{
    return getKtFN(28);
}

/**
 * 设置室智能眼
 */
int AirconditionLogic::getSmartEyeFN()
{
    return getKtFN(29);
}

/**
 * 设置室静音
 */
int AirconditionLogic::getMuteFN()
{
    return getKtFN(30);
}

/**
 * 设置语音
 */
int AirconditionLogic::getVoiceFN()
{
    return getKtFN(31);
}

/**
 * 设置除烟
 */
int AirconditionLogic::getClernSmokeFN()
{
    return getKtFN(32);
}

/**
 * 背景灯
 */
int AirconditionLogic::getBackgroundLampFN()
{
    return getKtFN(33);
}

/**
 * 显示屏发光
 */
int AirconditionLogic::getScreenFN()
{
    return getKtFN(34);
}

/**
 * LED指示灯
 */
int AirconditionLogic::getLEDFN()
{
    return getKtFN(35);
}

/**
 * 室内外温度切换显示
 */
int AirconditionLogic::getIndoorOutdoorSwitchFN()
{
    return getKtFN(36);
}

/**
 * 室内过滤网清洁复位控制
 */
int AirconditionLogic::getIndoorFilterClearFN()
{
    return getKtFN(37);
}

/**
 * 左风摆开停控制
 */
int AirconditionLogic::getLeftFanContrlFN()
{
    return getKtFN(38);
}

/**
 * 右风摆开停控制
 */
int AirconditionLogic::getRightFanContrlFN()
{
    return getKtFN(39);
}

/**
 * 控制规则
 */
int AirconditionLogic::getContrlRate()
{
    return getKtFN(43);
}

/********* 设置功能 ********/
/**
 * 设置睡眠模式
 */
void AirconditionLogic::setWindSpeedFN(string value)
{
    setKtFN(value,0);
}

/**
 *
 */
void AirconditionLogic::setSleepModeFN(string value)
{
    setKtFN(value,1);
}

/**
 * 设置模式
 */
void AirconditionLogic::setModeFN(string value)
{
    setKtFN(value,2);
}

/**
 * 开/关机
 */
void AirconditionLogic::setPowerFN(string value)
{
    setKtFN(value,3);
}

/**
 * 设置温度
 */
void AirconditionLogic::setTemperatureFN(string value)
{
    setKtFN(value,5);
}

/**
 * 设置湿度
 */
void AirconditionLogic::setHumidityFN(string value)
{
    setKtFN(value,6);
}

/**
 * 体感控制,体感室内温度,体感室内温度补偿
 */
void AirconditionLogic::setSomatosensoryRealityTemperatureFN(string value)
{
    setKtFN(value,8);
}

/**
 * 自动工作模式和除湿模式的温度补偿
 */
void AirconditionLogic::setTemperatureCompensationFN(string value)
{
    setKtFN(value,9);
}

/**
 * 华氏/摄氏温度显示设置
 */
void AirconditionLogic::setTemperatureValueSwitchFN(string value)
{
    setKtFN(value,12);
}

/**
 * 普通定时关机,普通定时关机时间
 */
void AirconditionLogic::setGeneralTimingShutdownFN(string value)
{
    setKtFN(value,13);
}

/**
 * 实时开机控制,实时时钟的小时值,实时时钟的分钟值,实时开机小时,实时开机分钟
 */
void AirconditionLogic::setRealityTimeFN(string value)
{
    setKtFN(value,14);
}

/**
 * 上下风门模式,上下风开停控制
 */
void AirconditionLogic::setVerticalWindFN(string value)
{
    setKtFN(value,16);
}

/**
 * 左右风开停控制,左风摆,右风摆
 */
void AirconditionLogic::setHorizontalWindFN(string value)
{
    setKtFN(value,17);
}

/**
 * 自然风开停
 */
void AirconditionLogic::setNatureWindFN(string value)
{
    setKtFN(value,18);
}

/**
 * 设置电加热
 */
void AirconditionLogic::setElectricalHeatingFN(string value)
{
    setKtFN(value,19);
}

/**
 * 除湿模式
 */
void AirconditionLogic::setDehumidificationModeFN(string value)
{
    setKtFN(value,20);
}

/**
 * 设置节能
 */
void AirconditionLogic::setEnergyConservationFN(string value)
{
    setKtFN(value,21);
}

/**
 * 设置并且节能
 */
void AirconditionLogic::setShareFN(string value)
{
    setKtFN(value,22);
}

/**
 * 设置高效
 */
void AirconditionLogic::setEfficientFN(string value)
{
    setKtFN(value,23);
}

/**
 * 设置双模
 */
void AirconditionLogic::setDualModeFN(string value)
{
    setKtFN(value,24);
}

/**
 * 设置清新
 */
void AirconditionLogic::setFreshnessFN(string value)
{
    setKtFN(value,25);
}

/**
 * 设置换风
 */
void AirconditionLogic::setFreshAirFN(string value)
{
    setKtFN(value,26);
}

/**
 * 设置室内清洁
 */
void AirconditionLogic::setClernIndoorFN(string value)
{
    setKtFN(value,27);
}

/**
 * 设置室外清洁
 */
void AirconditionLogic::setClernOutdoorFN(string value)
{
    setKtFN(value,28);
}

/**
 * 设置室智能眼
 */
void AirconditionLogic::setSmartEyeFN(string value)
{
    setKtFN(value,29);
}

/**
 * 设置室静音
 */
void AirconditionLogic::setMuteFN(string value)
{
    setKtFN(value,30);
}

/**
 * 设置语音
 */
void AirconditionLogic::setVoiceFN(string value)
{
    setKtFN(value,31);
}

/**
 * 设置除烟
 */
void AirconditionLogic::setClernSmokeFN(string value)
{
    setKtFN(value,32);
}

/**
 * 背景灯
 */
void AirconditionLogic::setBackgroundLampFN(string value)
{
    setKtFN(value,33);
}

/**
 * 显示屏发光
 */
void AirconditionLogic::setScreenFN(string value)
{
    setKtFN(value,34);
}

/**
 * LED指示灯
 */
void AirconditionLogic::setLEDFN(string value)
{
    setKtFN(value,35);
}

/**
 * 室内外温度切换显示
 */
void AirconditionLogic::setIndoorOutdoorSwitchFN(string value)
{
    setKtFN(value,36);
}

/**
 * 室内过滤网清洁复位控制
 */
void AirconditionLogic::setIndoorFilterClearFN(string value)
{
    setKtFN(value,37);
}

/************************** 空调设置接口 **************************/
/**
 * 设置风量
 */
string AirconditionLogic::setWindSpeed(string value,int manualOrnot)
{
    /*取消快速冷热,取消睡眠*/
    bool slientmode=false;
    if(0!=value.length())
    {
        //除湿模式下，只能设置自动
        if((strcmp(getMode().c_str(),"dehumidify")==0))
        {
            value="auto";
            setWindSpeedFN("3");
        }
        
        //当模式为自动，不能设置静音，目前还未能配置
        if((strcmp(getMode().c_str(),"auto")==0) && (strcmp(value.c_str(),"mute")==0))
        {
            return "";
        }
        
        //当模式为通风，不能设置自动，目前还未能配置
        if((strcmp(getMode().c_str(),"blow")==0) && (strcmp(value.c_str(),"auto")==0))
        {
            return "";
        }
        
        if ((strcmp(value.c_str(),"mute")==0))
            slientmode=true;
        
        ZD[0]=value;
        ZD[1]="off";
        ZD[32]="0";
        ZD[39]=IOTUtil::intToString(slientmode);
        string atcmd =  IOTConstants::CMD_AT_MARK  + "KTFL" + IOTConstants::CMD_AT_EQUALS_SINGNAL + deviceId + IOTConstants::PARAM_VALUE_SPLIT + value + IOTConstants::PARAM_VALUE_SPLIT + "off" + IOTConstants::PARAM_VALUE_SPLIT + "0"+ IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(slientmode) + IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(manualOrnot) + IOTConstants::CMD_AT_WRAP;
        return createNetBytes(atcmd);
    }
    return "";
}

/**
 * 设置睡眠模式
 */
string AirconditionLogic::setSleepMode(string sleepMode,int manualOrnot)
{
    /*当前温度,低风,取消静音,取消快速冷热*/
    string WindSpeed="auto";
    if(0!=sleepMode.length() && getSleepModeFN()>0)
    {
        //当模式为自动，不能设置睡眠
        if((strcmp(getMode().c_str(),"auto")==0))
        {
            setSleepModeFN("3");
            ZD[1]="off";
            return "";
        }
        
        //当模式为送风，不能设置睡眠
        if((strcmp(getMode().c_str(),"blow")==0))
        {
            setSleepModeFN("3");
            ZD[1]="off";
            return "";
        }
        
        setWindSpeedFN("3");
        
        if((strcmp(sleepMode.c_str(),"off")==0))
        {
            setWindSpeedFN("2");
        }
        else
        {
            WindSpeed="weak";
        }
        
        ZD[0]=WindSpeed;
        ZD[1]=sleepMode;
        ZD[32]="0";
        ZD[39]="0";
        string atcmd =  IOTConstants::CMD_AT_MARK  + "KTSM" + IOTConstants::CMD_AT_EQUALS_SINGNAL + deviceId + IOTConstants::PARAM_VALUE_SPLIT + sleepMode
        + IOTConstants::PARAM_VALUE_SPLIT + WindSpeed+IOTConstants::PARAM_VALUE_SPLIT +"0,0"
        + IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(manualOrnot) + IOTConstants::CMD_AT_WRAP;
        return  createNetBytes(atcmd);
    }
    return "";
}

/**
 * 设置模式
 */
string AirconditionLogic::setMode(string Mode,int manualOrnot)
{
    bool isSwitchDiaplay = IOTUtil::stringToInt(getTemperatureValueSwitch());
    string temperature = "";
    if(isSwitchDiaplay)
    {
        temperature = "77";
    }
    else
    {
        temperature = "25";
    }
    
    string WindSpeed="auto";
    
    /*自动/(送风模式)中风,温度25/(制冷)26/(制热)23,取消静音,取消快速冷热,取消睡眠,上下风自动,左右停止，取消电热*/
    if(0!=Mode.length())
    {
        if ((strcmp(getPower().c_str(),"1")==0))
        {
            //单冷机型，不支持制热
            if((strcmp(Mode.c_str(),"heat")==0) && getCoolModeFN()==0)
            {
                return "";
            }
            
            setDehumidificationModeFN("3");
            setWindSpeedFN("2");
            setSleepModeFN("3");
            setElectricalHeatingFN("3");
            setDualModeFN("2");
            setTemperatureFN("2");
            setEfficientFN("2");
            setEnergyConservationFN("2");
            setShareFN("2");
            setMuteFN("2");
            
            ZD[0]="auto";
            ZD[1]="off";
            ZD[5]="25";
            ZD[29]="0";
            ZD[32]="0";
            ZD[39]="0";
            
            if((strcmp(Mode.c_str(),"cool")==0))
            {
                if(isSwitchDiaplay){
                    temperature = "79";
                }else{
                    temperature = "26";
                }
                setSleepModeFN("2");
            }
            
            if((strcmp(Mode.c_str(),"heat")==0) && getCoolModeFN()>0)
            {
                if(isSwitchDiaplay){
                    temperature = "73";
                }else{
                    temperature = "23";
                }
                setSleepModeFN("2");
                setElectricalHeatingFN("2");
            }
            if((strcmp(Mode.c_str(),"blow")==0)){
                WindSpeed="middle";
                ZD[0]="middle";
                setDualModeFN("3");
                setTemperatureFN("3");
                setEfficientFN("3");
                setEnergyConservationFN("3");
                setShareFN("3");
            }
            
            if((strcmp(Mode.c_str(),"dehumidify")==0))
            {
                setDehumidificationModeFN("2");
                setSleepModeFN("2");
                setWindSpeedFN("3");
            }
            
            if((strcmp(Mode.c_str(),"auto")==0))
            {
                if(isSwitchDiaplay){
                    temperature = "79";
                }else{
                    temperature = "25";
                }
                setMuteFN("3");
                setEfficientFN("3");
            }
        }
        else
        {
            ZD[0]="auto";
            ZD[1]="off";
            ZD[5]="25";
            ZD[29]="0";
            ZD[32]="0";
            ZD[39]="0";
            if((strcmp(Mode.c_str(),"cool")==0)){
                if(isSwitchDiaplay){
                    temperature = "79";
                }else{
                    temperature = "26";
                }
            }
            if((strcmp(Mode.c_str(),"heat")==0)&& getCoolModeFN()>0){
                if(isSwitchDiaplay){
                    temperature = "73";
                }else{
                    temperature = "23";
                }
            }
            if((strcmp(Mode.c_str(),"blow")==0)){
                WindSpeed="middle";
                ZD[0]="middle";
            }
            if((strcmp(Mode.c_str(),"dehumidify")==0)){
            }
            if((strcmp(Mode.c_str(),"auto")==0)){
            }
        }
        ZD[5]=temperature;
        ZD[2]=Mode;
        ZD[24]="auto";
        string atcmd = IOTConstants::CMD_AT_MARK  + "KTYX" + IOTConstants::CMD_AT_EQUALS_SINGNAL + deviceId + IOTConstants::PARAM_VALUE_SPLIT + Mode
        + IOTConstants::PARAM_VALUE_SPLIT + WindSpeed
        + IOTConstants::PARAM_VALUE_SPLIT + temperature
        + IOTConstants::PARAM_VALUE_SPLIT + "0"
        + IOTConstants::PARAM_VALUE_SPLIT + "0"
        + IOTConstants::PARAM_VALUE_SPLIT + "off"
        + IOTConstants::PARAM_VALUE_SPLIT + "0"
        + IOTConstants::PARAM_VALUE_SPLIT +"auto"
        + IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(manualOrnot) + IOTConstants::CMD_AT_WRAP;
        return createNetBytes(atcmd);
    }
    return "";
}

/**
 * 同步状态  不是控制指令
 */
void AirconditionLogic::syncPower()
{
   setPowerStatus(IOTUtil::stringToInt(getPower()));
}


/**
 * 设置开/关机
 */
string AirconditionLogic::setPower(int on,int manualOrnot)
{
    /*取消普通定时,取消实时关机,取消快速冷热,取消睡眠,取消电热,取消节能,取消净化,取消双模,取消显示,取消亮度*/
    string atcmd;
    if(getPowerFN()>0)
    {
        if(on)
        {
            setPowerStatus(true);
            ZD[3]="1";
            atcmd =  IOTConstants::CMD_AT_MARK  + "KTKJ" + IOTConstants::CMD_AT_EQUALS_SINGNAL + deviceId + IOTConstants::PARAM_VALUE_SPLIT  + IOTUtil::intToString(on) + IOTConstants::PARAM_VALUE_SPLIT  + IOTUtil::intToString(manualOrnot) + IOTConstants::CMD_AT_WRAP;
        }
        else
        {
            setPowerStatus(false);
            ZD[3]="0";
            ZD[181]="0";	//取消普通定时关机
            ZD[21]="0";	//取消实时定时关机
            ZD[32]="0";	//取消高效
            ZD[1]="off";	//取消睡眠
            ZD[29]="0";	//取消电热
            ZD[30]="0";	//取消节能
            ZD[31]="0";	//取消并用节电
            ZD[41]="0";	//除烟(净化)
            ZD[33]="0";	//取消双模
            atcmd = IOTConstants::CMD_AT_MARK  + "KTKJ" + IOTConstants::CMD_AT_EQUALS_SINGNAL + deviceId + IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(on)
            + IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(manualOrnot)
            + IOTConstants::PARAM_VALUE_SPLIT + "0"
            + IOTConstants::PARAM_VALUE_SPLIT + "0"
            + IOTConstants::PARAM_VALUE_SPLIT + "0"
            + IOTConstants::PARAM_VALUE_SPLIT + "off"
            + IOTConstants::PARAM_VALUE_SPLIT + "0,0,0,0,0"
            + IOTConstants::CMD_AT_WRAP;
        }
    }
    return createNetBytes(atcmd);
}

/**
 * 设置KTSBOX
 */
string AirconditionLogic::setKtSBox(int on,string Mode,string WindSpeed_value,int temperature,int IsMute,int manualOrnot)
{
    if(IsMute)
    {
        WindSpeed_value = IOTConstants::AIRCONDITION_WIND_MUTE;
    }
    
    ZD[0]=WindSpeed_value;
    ZD[2]=Mode;
    ZD[3]=IOTUtil::intToString(on);
    ZD[5]=IOTUtil::intToString(temperature);
    ZD[39]=IOTUtil::intToString(IsMute);
    string atcmd = IOTConstants::CMD_AT_MARK  + "KTSBOX" + IOTConstants::CMD_AT_EQUALS_SINGNAL + deviceId + IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(on) +IOTConstants::PARAM_VALUE_SPLIT + Mode
    + IOTConstants::PARAM_VALUE_SPLIT + WindSpeed_value
    + IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(temperature) +IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(IsMute)+ IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(manualOrnot) + IOTConstants::CMD_AT_WRAP;
    return createNetBytes(atcmd);
}

/**
 * 设置风向
 */
string AirconditionLogic::setWindDirection(int on,int manualOrnot)
{
    if(getWindDirectionFN()==0)
    {
        ZD[4]=IOTUtil::intToString(on);
        string atcmd = IOTConstants::CMD_AT_MARK  + "KTFX" + IOTConstants::CMD_AT_EQUALS_SINGNAL + deviceId + IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(on) + IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(manualOrnot) + IOTConstants::CMD_AT_WRAP;
        return createNetBytes(atcmd);
    }
    return "";
}

/**
 * 设置温度
 */
string AirconditionLogic::setTemperature(int temperature,int manualOrnot)
{
    if(getTemperatureFN()>0)
    {
        //送风模式下无效
        if((strcmp(getMode().c_str(),"blow")==0))
        {
            setTemperatureFN("3");
            ZD[5]="25";
            return "";
        }
        ZD[5]=IOTUtil::intToString(temperature);
        string atcmd =  IOTConstants::CMD_AT_MARK  + "KTWD" + IOTConstants::CMD_AT_EQUALS_SINGNAL + deviceId + IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(temperature) + IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(manualOrnot) + IOTConstants::CMD_AT_WRAP;
        return createNetBytes(atcmd);
    }
    return "";
}

/**
 * 设置湿度
 */
string AirconditionLogic::setHumidity(int humidity,int manualOrnot)
{
    if(getHumidityFN()>0)
    {
        ZD[6]=IOTUtil::intToString(humidity);
        string atcmd = IOTConstants::CMD_AT_MARK  + "KTSD" + IOTConstants::CMD_AT_EQUALS_SINGNAL + deviceId + IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(humidity) + IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(manualOrnot) + IOTConstants::CMD_AT_WRAP;
        return createNetBytes(atcmd);
    }
    return "";
}

/**
 * 体感控制,体感室内温度,体感室内温度补偿
 */
string AirconditionLogic::setSomatosensoryRealityTemperature(int on,int temperature,int compensation,int manualOrnot)
{
    if(getSomatosensoryRealityTemperatureFN()>0)
    {
        ZD[7]=IOTUtil::intToString(temperature);
        ZD[11]=IOTUtil::intToString(compensation);
        ZD[12]=IOTUtil::intToString(on);
        string atcmd = IOTConstants::CMD_AT_MARK  + "KTTG" + IOTConstants::CMD_AT_EQUALS_SINGNAL + deviceId + IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(on) + IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(temperature) + IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(compensation) + IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(manualOrnot) + IOTConstants::CMD_AT_WRAP;
        return createNetBytes(atcmd);
    }
    return "";
}

/**
 * 自动工作模式和除湿模式的温度补偿
 */
string AirconditionLogic::setTemperatureCompensation(int compensation,int manualOrnot)
{
    if(getTemperatureCompensationFN()>0)
    {
        ZD[13]=IOTUtil::intToString(compensation);
        string atcmd =  IOTConstants::CMD_AT_MARK  + "KTWDBC" + IOTConstants::CMD_AT_EQUALS_SINGNAL + deviceId + IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(compensation) + IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(manualOrnot) + IOTConstants::CMD_AT_WRAP;
        return createNetBytes(atcmd);
    }
    return "";
}

/**
 * 华氏/摄氏温度显示设置
 */
string AirconditionLogic::setTemperatureValueSwitch(int Fahrenheit,int manualOrnot)
{
    if(getTemperatureValueSwitchFN()>0)
    {
        ZD[14]=IOTUtil::intToString(Fahrenheit);
        string atcmd =  IOTConstants::CMD_AT_MARK  + "KTHS" + IOTConstants::CMD_AT_EQUALS_SINGNAL + deviceId + IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(Fahrenheit) + IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(manualOrnot) + IOTConstants::CMD_AT_WRAP;
        return createNetBytes(atcmd);
    }
    return "";
}

/**
 * 普通定时关机,普通定时关机时间
 */
string AirconditionLogic::setGeneralTimingShutdown(int on,string hour,int manualOrnot)
{
    if(0!=hour.length() && getGeneralTimingShutdownFN()>0)
    {
        ZD[15]=hour;
        ZD[181]=IOTUtil::intToString(on);
        string atcmd =  IOTConstants::CMD_AT_MARK  + "KTGTT" + IOTConstants::CMD_AT_EQUALS_SINGNAL + deviceId + IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(on) + IOTConstants::PARAM_VALUE_SPLIT + hour + IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(manualOrnot) + IOTConstants::CMD_AT_WRAP;
        return createNetBytes(atcmd);
    }
    return "";
}

/**
 * 实时时钟的小时值,实时时钟的分钟值
 */
string AirconditionLogic::setRealityTime(string hour,string minute,int manualOrnot)
{
    if(0!=hour.length() && 0!=minute.length() && getRealityTimeFN()>0)
    {
        string atcmd =  IOTConstants::CMD_AT_MARK  + "KTSS" + IOTConstants::CMD_AT_EQUALS_SINGNAL + deviceId + IOTConstants::PARAM_VALUE_SPLIT + hour + IOTConstants::PARAM_VALUE_SPLIT + minute + IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(manualOrnot) + IOTConstants::CMD_AT_WRAP;
        return createNetBytes(atcmd);
    }
    return "";
}

/**
 * 实时开机控制,实时时钟的小时值,实时时钟的分钟值,实时开机小时,实时开机分钟
 */
string AirconditionLogic::setRealityTimeBoot(int on,string Realityhour,string Realityminute, string boothour,string bootminute, string remainingHour,string remainingMinute, int manualOrnot)
{
    if(0!=Realityminute.length() && 0!=Realityhour.length() && 0!=boothour.length() && 0!=bootminute.length() && getRealityTimeFN()>0)
    {
        ZD[20]=remainingMinute;
        ZD[19]=remainingHour;
        ZD[18]=IOTUtil::intToString(on);
        string atcmd =  IOTConstants::CMD_AT_MARK  + "KTKT" + IOTConstants::CMD_AT_EQUALS_SINGNAL + deviceId + IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(on)
        + IOTConstants::PARAM_VALUE_SPLIT + boothour
        + IOTConstants::PARAM_VALUE_SPLIT + bootminute
        + IOTConstants::PARAM_VALUE_SPLIT + Realityhour
        + IOTConstants::PARAM_VALUE_SPLIT + Realityminute
        + IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(manualOrnot)
        + IOTConstants::CMD_AT_WRAP;
        return createNetBytes(atcmd);
    }
    return "";
}

/**
 * 实时关机控制,实时时钟的小时值,实时时钟的分钟值,实时关机小时,实时关机分钟
 */
string AirconditionLogic::setRealityTimeShutdown(int on,string Realityhour,string Realityminute, string shutdownhour,string shutdownminute, string remainingHour,string remainingMinute, int manualOrnot)
{
    if(0!=Realityminute.length() && 0!=Realityhour.length() && 0!=shutdownhour.length() && 0!=shutdownminute.length() && getRealityTimeFN()>0){
        ZD[23]=remainingMinute;
        ZD[22]=remainingHour;
        ZD[21]=IOTUtil::intToString(on);
        string atcmd = IOTConstants::CMD_AT_MARK  + "KTGT" + IOTConstants::CMD_AT_EQUALS_SINGNAL + deviceId + IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(on)
        + IOTConstants::PARAM_VALUE_SPLIT  + shutdownhour
        + IOTConstants::PARAM_VALUE_SPLIT + shutdownminute
        + IOTConstants::PARAM_VALUE_SPLIT + Realityhour
        + IOTConstants::PARAM_VALUE_SPLIT + Realityminute
        + IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(manualOrnot)
        + IOTConstants::CMD_AT_WRAP;
        return createNetBytes(atcmd);
    }
    return "";
}

/**
 * 设置除湿模式
 */
string AirconditionLogic::setDehumidificationMode(string mode,int manualOrnot)
{
    if(0!=mode.length() && getDehumidificationModeFN()>0)
    {
        //只在除湿模式下有效
        if(!(strcmp(getMode().c_str(),"dehumidify")==0))
        {
            setDehumidificationModeFN("3");
            ZD[24]="0";
            return "";
        }
        ZD[24]=mode;
        string atcmd = IOTConstants::CMD_AT_MARK  + "KTCS" + IOTConstants::CMD_AT_EQUALS_SINGNAL + deviceId
        + IOTConstants::PARAM_VALUE_SPLIT + mode
        + IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(manualOrnot) + IOTConstants::CMD_AT_WRAP;
        return createNetBytes(atcmd);
    }
    return "";
}

/**
 * 上下风门模式,上下风开停控制
 */
string AirconditionLogic::setVerticalWind(string mode,int on,int manualOrnot)
{
    if(0!=mode.length() && getVerticalWindFN()>0)
    {
        ZD[25]=mode;
        ZD[26]=IOTUtil::intToString(on);
        string atcmd = IOTConstants::CMD_AT_MARK  + "KTVF" + IOTConstants::CMD_AT_EQUALS_SINGNAL + deviceId
        + IOTConstants::PARAM_VALUE_SPLIT + mode
        + IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(on)
        + IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(manualOrnot) + IOTConstants::CMD_AT_WRAP;
        return createNetBytes(atcmd);
    }
    return "";
}

/**
 * 左右风开停控制,左风摆,右风摆
 */
string AirconditionLogic::setHorizontalWind(int on,int left,int right,int manualOrnot)
{
    if(getHorizontalWindFN()>0)
    {
        if(getLeftFanContrlFN()==0)
        {
            left=false;
        }
        if(getRightFanContrlFN()==0)
        {
            right=false;
        }
        ZD[47]=IOTUtil::intToString(left);
        ZD[48]=IOTUtil::intToString(right);
        ZD[27]=IOTUtil::intToString(on);
        string atcmd = IOTConstants::CMD_AT_MARK  + "KTHFM" + IOTConstants::CMD_AT_EQUALS_SINGNAL + deviceId
        + IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(on)
        + IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(left)
        + IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(right)
        + IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(manualOrnot) + IOTConstants::CMD_AT_WRAP;
        return createNetBytes(atcmd);
    }
    return "";
}

/**
 * 自然风开停
 */
string AirconditionLogic::setNatureWind(int on,int manualOrnot)
{
    if(getNatureWindFN()>0)
    {
        ZD[28]=IOTUtil::intToString(on);
        string atcmd = IOTConstants::CMD_AT_MARK  + "KTZRF" + IOTConstants::CMD_AT_EQUALS_SINGNAL + deviceId + IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(on)
        + IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(manualOrnot) + IOTConstants::CMD_AT_WRAP;
        return createNetBytes(atcmd);
    }
    return "";
}

/**
 * 设置电加热
 */
string AirconditionLogic::setElectricalHeating(int on,int manualOrnot)
{
    if(getElectricalHeatingFN()>0)
    {
        if(!(strcmp(getMode().c_str(),"heat")==0))
        {
            setDehumidificationModeFN("3");
            ZD[29]="0";
            return "";
        }
        ZD[29]=IOTUtil::intToString(on);
        string atcmd = IOTConstants::CMD_AT_MARK  + "KTDR" + IOTConstants::CMD_AT_EQUALS_SINGNAL + deviceId + IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(on)
        + IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(manualOrnot) + IOTConstants::CMD_AT_WRAP;
        return createNetBytes(atcmd);
    }
    return "";
}

/**
 * 设置节能
 */
string AirconditionLogic::setEnergyConservation(int on,int manualOrnot)
{
    /*取消快速冷热*/
    if(getEnergyConservationFN()>0)
    {
        //节能在送风模式下无效
        if((strcmp(getMode().c_str(),"blow")==0))
        {
            setEnergyConservationFN("3");
            setShareFN("3");
            ZD[30]="0";
            return "";
        }
        //节能在双模下无效
        if((strcmp(getDualMode().c_str(),"1")==0))
        {
            setEnergyConservationFN("3");
            setShareFN("3");
            ZD[30]="0";
            return "";
        }
        ZD[30]=IOTUtil::intToString(on);
        ZD[32]="0";
        string atcmd = IOTConstants::CMD_AT_MARK  + "KTJN" + IOTConstants::CMD_AT_EQUALS_SINGNAL + deviceId + IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(on)
        + IOTConstants::PARAM_VALUE_SPLIT + "0"
        + IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(manualOrnot) + IOTConstants::CMD_AT_WRAP;
        return createNetBytes(atcmd);
    }
    return "";
}

/**
 * 设置并用节电
 */
string AirconditionLogic::setShare(int on,int manualOrnot)
{
    if(getShareFN()>0)
    {
        //节能在并用节电模式下无效
        if((strcmp(getMode().c_str(),"blow")==0))
        {
            setEnergyConservationFN("3");
            setShareFN("3");
            ZD[30]="0";
            return "";
        }
        //并用节电在双模下无效
        if((strcmp(getDualMode().c_str(),"1")==0)){
            setEnergyConservationFN("3");
            setShareFN("3");
            ZD[30]="0";
            return "";
        }
        ZD[31]=IOTUtil::intToString(on);
        ZD[32]="0";
        string atcmd = IOTConstants::CMD_AT_MARK  + "KTBY" + IOTConstants::CMD_AT_EQUALS_SINGNAL + deviceId + IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(on)
        + IOTConstants::PARAM_VALUE_SPLIT + "0"
        + IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(manualOrnot) + IOTConstants::CMD_AT_WRAP;
        return createNetBytes(atcmd);
    }
    return "";
}

/**
 * 设置高效
 */
string AirconditionLogic::setEfficient(int on,int manualOrnot)
{
    /*自动风/（关）高风,取消静音,取消睡眠,取消节能*/
    if(getEfficientFN()>0)
    {
        if((strcmp(getMode().c_str(),"blow")==0))
        {
            setEfficientFN("3");
            ZD[32]="0";
            return "";
        }
        if((strcmp(getMode().c_str(),"auto")==0))
        {
            setEfficientFN("3");
            ZD[32]="0";
            return "";
        }
        
        ZD[32]=IOTUtil::intToString(on);
        ZD[39]="0";
        ZD[0]="auto";
        ZD[1]="off";
        ZD[30]="0";
        ZD[31]="0";
        string atcmd = IOTConstants::CMD_AT_MARK  + "KTGXex" + IOTConstants::CMD_AT_EQUALS_SINGNAL + deviceId + IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(on)
        + IOTConstants::PARAM_VALUE_SPLIT + "0"
        + IOTConstants::PARAM_VALUE_SPLIT + "auto"
        + IOTConstants::PARAM_VALUE_SPLIT + "off"
        + IOTConstants::PARAM_VALUE_SPLIT + "0"
        + IOTConstants::PARAM_VALUE_SPLIT + "0"
        + IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(manualOrnot) + IOTConstants::CMD_AT_WRAP;
        return createNetBytes(atcmd);
    }
    return "";
}

/**
 * 设置高效 OEM项目专用
 */
string AirconditionLogic::setEfficientOem(int on,int manualOrnot)
{
    /*自动风/（关）高风,取消静音,取消睡眠,取消节能*/
    if(getEfficientFN()>0)
    {
        if((strcmp(getMode().c_str(),"blow")==0))
        {
            setEfficientFN("3");
            ZD[32]="0";
            return "";
        }
        if((strcmp(getMode().c_str(),"auto")==0))
        {
            setEfficientFN("3");
            ZD[32]="0";
            return "";
        }
        
        if(on)
        {
            if (IOTUtil::stringToInt(getTemperatureValueSwitch())==false)
            {
                if((strcmp(getMode().c_str(),"cool")==0))
                {
                    ZD[5] = "16";
                }
                else if((strcmp(getMode().c_str(),"heat")==0))
                {
                    ZD[5] = "32";
                }
            }
            else
            {
                if((strcmp(getMode().c_str(),"cool")==0))
                {
                    ZD[5] = "61";
                }else if((strcmp(getMode().c_str(),"heat")==0))
                {
                    ZD[5] = "90";
                }
            }
        }
        
        ZD[32]=IOTUtil::intToString(on);
        ZD[39]="0";
        ZD[0]="auto";
        ZD[1]="off";
        ZD[30]="0";
        ZD[31]="0";
        string atcmd = IOTConstants::CMD_AT_MARK  + "KTGXex" + IOTConstants::CMD_AT_EQUALS_SINGNAL + deviceId + IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(on)
        + IOTConstants::PARAM_VALUE_SPLIT + "0"
        + IOTConstants::PARAM_VALUE_SPLIT + "auto"
        + IOTConstants::PARAM_VALUE_SPLIT + "off"
        + IOTConstants::PARAM_VALUE_SPLIT + "0"
        + IOTConstants::PARAM_VALUE_SPLIT + "0"
        + IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(manualOrnot) + IOTConstants::CMD_AT_WRAP;
        return createNetBytes(atcmd);
    }
    return "";
}

/**
 * 设置双模
 */
string AirconditionLogic::setDualMode(int on,int manualOrnot)
{
    /*取消快速冷热*/
    if(getDualModeFN()>0)
    {
        
        if((strcmp(getMode().c_str(),"blow")==0))
        {
            setDualModeFN("3");
            ZD[33]="0";
            return "";
        }
        if(getEnergyConservationFN()>0 && on)
        {
            setEnergyConservationFN("3");
            ZD[30]="0";
        }
        if(getShareFN()>0 && on)
        {
            setShareFN("3");
            ZD[31]="0";
        }
        if(!on)
        {
            setEnergyConservationFN("2");
            setShareFN("2");
        }
        ZD[33]=IOTUtil::intToString(on);
        //ZD[32]="0";
        string atcmd = IOTConstants::CMD_AT_MARK  + "KTDM" + IOTConstants::CMD_AT_EQUALS_SINGNAL + deviceId + IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(on)
        + IOTConstants::PARAM_VALUE_SPLIT + "0"
        + IOTConstants::PARAM_VALUE_SPLIT + "0"
        + IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(manualOrnot) + IOTConstants::CMD_AT_WRAP;
        return createNetBytes(atcmd);
    }
    return "";
}

/**
 * 设置清新
 */
string AirconditionLogic::setFreshness(int on,int manualOrnot)
{
    if(getFreshnessFN()>0)
    {
        ZD[34]=IOTUtil::intToString(on);
        string atcmd = IOTConstants::CMD_AT_MARK  + "KTJH" + IOTConstants::CMD_AT_EQUALS_SINGNAL + deviceId + IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(on) + IOTConstants::PARAM_VALUE_SPLIT
        + IOTUtil::intToString(manualOrnot) + IOTConstants::CMD_AT_WRAP;
        return createNetBytes(atcmd);
    }
    return "";
}

/**
 * 设置换风
 */
string AirconditionLogic::setFreshAir(int on,int manualOrnot)
{
    if(getFreshAirFN()>0)
    {
        ZD[35]=IOTUtil::intToString(on);
        string atcmd = IOTConstants::CMD_AT_MARK  + "KTHF" + IOTConstants::CMD_AT_EQUALS_SINGNAL + deviceId + IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(on) + IOTConstants::PARAM_VALUE_SPLIT
        + IOTUtil::intToString(manualOrnot) + IOTConstants::CMD_AT_WRAP;
        return createNetBytes(atcmd);
    }
    return "";
}

/**
 * 设置室内清洁
 */
string AirconditionLogic::setClernIndoor(int on,int manualOrnot)
{
    if(getClernIndoorFN()>0)
    {
        ZD[36]=IOTUtil::intToString(on);
        string atcmd = IOTConstants::CMD_AT_MARK  + "KTQJ" + IOTConstants::CMD_AT_EQUALS_SINGNAL + deviceId + IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(on) + IOTConstants::PARAM_VALUE_SPLIT
        + IOTUtil::intToString(manualOrnot) + IOTConstants::CMD_AT_WRAP;
        return createNetBytes(atcmd);
    }
    return "";
}

/**
 * 设置室外清洁
 */
string AirconditionLogic::setClernOutdoor(int on,int manualOrnot)
{
    if(getClernOutdoorFN()>0)
    {
        ZD[37]=IOTUtil::intToString(on);
        string atcmd = IOTConstants::CMD_AT_MARK  + "KTSWQJ" + IOTConstants::CMD_AT_EQUALS_SINGNAL + deviceId + IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(on) + IOTConstants::PARAM_VALUE_SPLIT
        + IOTUtil::intToString(manualOrnot) + IOTConstants::CMD_AT_WRAP;
        return createNetBytes(atcmd);
    }
    return "";
}

/**
 * 设置智慧眼
 */
string AirconditionLogic::setSmartEye(int on,int manualOrnot)
{
    if(getSmartEyeFN()>0)
    {
        ZD[38]=IOTUtil::intToString(on);
        string atcmd = IOTConstants::CMD_AT_MARK  + "KTZN" + IOTConstants::CMD_AT_EQUALS_SINGNAL + deviceId + IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(on) + IOTConstants::PARAM_VALUE_SPLIT
        + IOTUtil::intToString(manualOrnot) + IOTConstants::CMD_AT_WRAP;
        return createNetBytes(atcmd);
    }
    return "";
}

/**
 * 设置室静音
 */
string AirconditionLogic::setMute(int on,int manualOrnot)
{
    //取消快速冷热，取消睡眠
    if(getMuteFN()>0)
    {
        if((strcmp(getMode().c_str(),"auto")==0))
        {
            setMuteFN("3");
            ZD[39]="0";
            return "";
        }
        
        ZD[0]="mute";
        ZD[1]="off";
        ZD[32]="0";
        ZD[39]=IOTUtil::intToString(on);
        string atcmd = IOTConstants::CMD_AT_MARK  + "KTJY" + IOTConstants::CMD_AT_EQUALS_SINGNAL + deviceId + IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(on)
        + IOTConstants::PARAM_VALUE_SPLIT + "0"
        + IOTConstants::PARAM_VALUE_SPLIT + "off"
        + IOTConstants::PARAM_VALUE_SPLIT + "mute"
        + IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(manualOrnot) + IOTConstants::CMD_AT_WRAP;
        return createNetBytes(atcmd);
    }
    return "";
}

/**
 * 设置语音
 */
string AirconditionLogic::setVoice(int on,int manualOrnot)
{
    if(getVoiceFN()>0)
    {
        ZD[40]=IOTUtil::intToString(on);
        string atcmd = IOTConstants::CMD_AT_MARK  + "KTYY" + IOTConstants::CMD_AT_EQUALS_SINGNAL + deviceId + IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(on) + IOTConstants::PARAM_VALUE_SPLIT
        + IOTUtil::intToString(manualOrnot) + IOTConstants::CMD_AT_WRAP;
        return createNetBytes(atcmd);
    }
    return "";
}
/**
 * 设置除烟
 */
string AirconditionLogic::setClernSmoke(int on,int manualOrnot)
{
    if(getClernSmokeFN()>0)
    {
        ZD[41]=IOTUtil::intToString(on);
        string atcmd = IOTConstants::CMD_AT_MARK  + "KTCY" + IOTConstants::CMD_AT_EQUALS_SINGNAL + deviceId + IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(on) + IOTConstants::PARAM_VALUE_SPLIT
        + IOTUtil::intToString(manualOrnot) + IOTConstants::CMD_AT_WRAP;
        return createNetBytes(atcmd);
    }
    return "";
}

/**
 * 设置背景灯
 */
string AirconditionLogic::setBackgroundLamp(int on,int manualOrnot)
{
    if(getBackgroundLampFN()>0)
    {
        ZD[42]=IOTUtil::intToString(on);
        string atcmd = IOTConstants::CMD_AT_MARK  + "KTBJD" + IOTConstants::CMD_AT_EQUALS_SINGNAL + deviceId + IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(on) + IOTConstants::PARAM_VALUE_SPLIT
        + IOTUtil::intToString(manualOrnot) + IOTConstants::CMD_AT_WRAP;
        return createNetBytes(atcmd);
    }
    return "";
}

/**
 * 显示屏发光
 */
string AirconditionLogic::setScreen(int on,int manualOrnot)
{
    if(getScreenFN()>0)
    {
        ZD[43]=IOTUtil::intToString(on);
        string atcmd = IOTConstants::CMD_AT_MARK  + "KTXSP" + IOTConstants::CMD_AT_EQUALS_SINGNAL + deviceId + IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(on) + IOTConstants::PARAM_VALUE_SPLIT
        + IOTUtil::intToString(manualOrnot) + IOTConstants::CMD_AT_WRAP;
        return createNetBytes(atcmd);
    }
    return "";
}

/**
 * LED指示灯
 */
string AirconditionLogic::setLED(int on,int manualOrnot)
{
    if(getLEDFN()>0)
    {
        ZD[44]=IOTUtil::intToString(on);
        string atcmd = IOTConstants::CMD_AT_MARK  + "KTLED" + IOTConstants::CMD_AT_EQUALS_SINGNAL + deviceId + IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(on) + IOTConstants::PARAM_VALUE_SPLIT
        + IOTUtil::intToString(manualOrnot) + IOTConstants::CMD_AT_WRAP;
        return createNetBytes(atcmd);
    }
    return "";
}

/**
 * 室内外温度切换显示
 */
string AirconditionLogic::setIndoorOutdoorSwitch(int on,int manualOrnot)
{
    if(getIndoorOutdoorSwitchFN()>0)
    {
        ZD[45]=IOTUtil::intToString(on);
        string atcmd = IOTConstants::CMD_AT_MARK  + "KTSRW" + IOTConstants::CMD_AT_EQUALS_SINGNAL + deviceId + IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(on) + IOTConstants::PARAM_VALUE_SPLIT
        + IOTUtil::intToString(manualOrnot) + IOTConstants::CMD_AT_WRAP;
        return createNetBytes(atcmd);
    }
    return "";
}

/**
 * 室内过滤网清洁复位控制
 */
string AirconditionLogic::setIndoorFilterClear(int on,int manualOrnot)
{
    if(getIndoorFilterClearFN()>0)
    {
        ZD[46]=IOTUtil::intToString(on);
        string atcmd = IOTConstants::CMD_AT_MARK  + "KTGLW" + IOTConstants::CMD_AT_EQUALS_SINGNAL + deviceId + IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(on) + IOTConstants::PARAM_VALUE_SPLIT
        + IOTUtil::intToString(manualOrnot) + IOTConstants::CMD_AT_WRAP;
        return createNetBytes(atcmd);
    }
    return "";
}

/**
 * 显示屏亮度值
 */
string AirconditionLogic::setScreenLuminance(int light,int manualOrnot)
{
    if( getScreenFN()>0)
    {
        ZD[180]=IOTUtil::intToString(light);
        string atcmd = IOTConstants::CMD_AT_MARK  + "KTLD" + IOTConstants::CMD_AT_EQUALS_SINGNAL + deviceId + IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(light) + IOTConstants::PARAM_VALUE_SPLIT
        + IOTUtil::intToString(manualOrnot) + IOTConstants::CMD_AT_WRAP;
        return createNetBytes(atcmd);
    }
    return "";
}

/**
 * 直接设置开/关机
 */
string AirconditionLogic::setDirctPower(string devid,int on,int manualOrnot)
{
    /*取消普通定时,取消实时关机,取消快速冷热,取消睡眠,取消左右风,取消电热,取消节能,取消净化,取消双模,取消显示,取消亮度*/
    if(on)
    {
        string atcmd = IOTConstants::CMD_AT_MARK  + "KTKJ" + IOTConstants::CMD_AT_EQUALS_SINGNAL + devid + IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(on) + IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(manualOrnot) + IOTConstants::CMD_AT_WRAP;
        return createNetBytes(atcmd);
    }else
    {
        
        string atcmd = IOTConstants::CMD_AT_MARK  + "KTKJ" + IOTConstants::CMD_AT_EQUALS_SINGNAL + devid + IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(on)
        + IOTConstants::PARAM_VALUE_SPLIT + "0"
        + IOTConstants::PARAM_VALUE_SPLIT + "0"
        + IOTConstants::PARAM_VALUE_SPLIT + "0"
        + IOTConstants::PARAM_VALUE_SPLIT + "off"
        + IOTConstants::PARAM_VALUE_SPLIT + "0,0,0,0,0,0,0"
        + IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(manualOrnot) + IOTConstants::CMD_AT_WRAP;
        return createNetBytes(atcmd);
    }
}

/**
 * 获取空调所有状态
 */
string AirconditionLogic::getAirConditionAllStatus(int manualOrnot)
{
    string atcmd = IOTConstants::CMD_AT_MARK  + "KTZD" + IOTConstants::CMD_AT_EQUALS_SINGNAL + deviceId + IOTConstants::PARAM_VALUE_SPLIT +  IOTConstants::CMD_AT_GET_STATUS_MARK + IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(manualOrnot) + IOTConstants::CMD_AT_WRAP;
    return createNetBytes(atcmd);
}

/**
 * 解析返回的数据
 */
bool AirconditionLogic::parseAtCommand(string result)
{
    return false;
}

