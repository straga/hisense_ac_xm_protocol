//
//  AirconditionControl.cpp
//  Devices
//
//  Created by 肖芳亮 on 16/2/24.
//  Copyright © 2016年 XLF. All rights reserved.
//

#include "AirconditionControl.h"

AirconditionControl::AirconditionControl(string deviceId)
{
    airConditionLogic = new AirconditionLogic();
    airConditionLogic->deviceId = deviceId;
    airConditionLogic->deviceType = "aircon";
    devicesLogic = airConditionLogic;
}

AirconditionControl::~AirconditionControl()
{
    if (airConditionLogic)
    {
        delete airConditionLogic;
    }
}

/**************************************** 控制 ****************************************/
/**
 * 设置风量
 */
string AirconditionControl::setWindSpeed(string value,int manualOrnot)
{
    return airConditionLogic->setWindSpeed(value,manualOrnot);
}

/**
 * 设置睡眠模式
 */
string AirconditionControl::setSleepMode(string sleepMode,int manualOrnot)
{
    return airConditionLogic->setSleepMode(sleepMode,manualOrnot);
}

/**
 * 设置模式
 */
string AirconditionControl::setMode(string Mode,int manualOrnot)
{
    return airConditionLogic->setMode(Mode,manualOrnot);
}

/**
 * 设置开/关机
 */
string AirconditionControl::setPower(int on,int manualOrnot)
{
    return airConditionLogic->setPower(on,manualOrnot);
}

/**
 * 设置KTSBOX
 */
string AirconditionControl::setKtSBox(int on,string Mode,string WindSpeed_value,int temperature,int IsMute,int manualOrnot)
{
    return airConditionLogic->setKtSBox(on,Mode,WindSpeed_value,temperature,IsMute,manualOrnot);
}

/**
 * 设置风向
 */
string AirconditionControl::setWindDirection(int on,int manualOrnot)
{
    return airConditionLogic->setWindDirection(on,manualOrnot);
}

/**
 * 设置温度
 */
string AirconditionControl::setTemperature(int temperature,int manualOrnot)
{
    return airConditionLogic->setTemperature(temperature,manualOrnot);
}

/**
 * 设置湿度
 */
string AirconditionControl::setHumidity(int humidity,int manualOrnot)
{
    
    return airConditionLogic->setHumidity(humidity,manualOrnot);
}

/**
 * 体感控制,体感室内温度,体感室内温度补偿
 */
string AirconditionControl::setSomatosensoryRealityTemperature(int on,int temperature,int compensation,int manualOrnot)
{
    return airConditionLogic->setSomatosensoryRealityTemperature(on,temperature,compensation,manualOrnot);
}

/**
 * 自动工作模式和除湿模式的温度补偿
 */
string AirconditionControl::setTemperatureCompensation(int compensation,int manualOrnot)
{
    return airConditionLogic->setTemperatureCompensation(compensation,manualOrnot);
}

/**
 * 华氏/摄氏温度显示设置
 */
string AirconditionControl::setTemperatureValueSwitch(int Fahrenheit,int manualOrnot)
{
    return airConditionLogic->setTemperatureValueSwitch(Fahrenheit,manualOrnot);
}

/**
 * 普通定时关机,普通定时关机时间
 */
string AirconditionControl::setGeneralTimingShutdown(int on,string hour,int manualOrnot)
{
    return airConditionLogic->setGeneralTimingShutdown(on,hour,manualOrnot);
}

/**
 * 实时时钟的小时值,实时时钟的分钟值
 */
string AirconditionControl::setRealityTime(string hour,string minute,int manualOrnot)
{
    return airConditionLogic->setRealityTime(hour,minute,manualOrnot);
}

/**
 * 实时开机控制,实时时钟的小时值,实时时钟的分钟值,实时开机小时,实时开机分钟
 */
string AirconditionControl::setRealityTimeBoot(int on,string Realityhour,string Realityminute, string boothour,string bootminute, string remainingHour,string remainingMinute, int manualOrnot)
{
    return airConditionLogic->setRealityTimeBoot(on,Realityhour,Realityminute,boothour,bootminute,remainingHour,remainingMinute,manualOrnot);
}

/**
 * 实时关机控制,实时时钟的小时值,实时时钟的分钟值,实时关机小时,实时关机分钟
 */
string AirconditionControl::setRealityTimeShutdown(int on,string Realityhour,string Realityminute, string shutdownhour,string shutdownminute, string remainingHour,string remainingMinute, int manualOrnot)
{
    return airConditionLogic->setRealityTimeShutdown(on,Realityhour,Realityminute,shutdownhour,shutdownminute,remainingHour,remainingMinute,manualOrnot);
}

/**
 * 设置除湿模式
 */
string AirconditionControl::setDehumidificationMode(string mode,int manualOrnot)
{
    return airConditionLogic->setDehumidificationMode(mode,manualOrnot);
}

/**
 * 上下风门模式,上下风开停控制
 */
string AirconditionControl::setVerticalWind(string mode,int on,int manualOrnot)
{
    return airConditionLogic->setVerticalWind(mode,on,manualOrnot);
}

/**
 * 左右风开停控制,左风摆,右风摆
 */
string AirconditionControl::setHorizontalWind(int on,int left,int right,int manualOrnot)
{
    return airConditionLogic->setHorizontalWind(on,left,right,manualOrnot);
}

/**
 * 自然风开停
 */
string AirconditionControl::setNatureWind(int on,int manualOrnot)
{
    return airConditionLogic->setNatureWind(on,manualOrnot);
}

/**
 * 设置电加热
 */
string AirconditionControl::setElectricalHeating(int on,int manualOrnot)
{
    return airConditionLogic->setElectricalHeating(on,manualOrnot);
}

/**
 * 设置节能
 */
string AirconditionControl::setEnergyConservation(int on,int manualOrnot)
{
    return airConditionLogic->setEnergyConservation(on,manualOrnot);
}

/**
 * 设置并用节电
 */
string AirconditionControl::setShare(int on,int manualOrnot)
{
    return airConditionLogic->setShare(on,manualOrnot);
}

/**
 * 设置高效
 */
string AirconditionControl::setEfficient(int on,int manualOrnot)
{
    return airConditionLogic->setEfficient(on,manualOrnot);
}

/**
 * 设置高效 OEM项目专用
 */
string AirconditionControl::setEfficientOem(int on,int manualOrnot)
{
    return airConditionLogic->setEfficientOem(on,manualOrnot);
}

/**
 * 设置双模
 */
string AirconditionControl::setDualMode(int on,int manualOrnot)
{
    return airConditionLogic->setDualMode(on,manualOrnot);
}

/**
 * 设置清新
 */
string AirconditionControl::setFreshness(int on,int manualOrnot)
{
    return airConditionLogic->setFreshness(on,manualOrnot);
}

/**
 * 设置换风
 */
string AirconditionControl::setFreshAir(int on,int manualOrnot)
{
    return airConditionLogic->setFreshAir(on,manualOrnot);
}

/**
 * 设置室内清洁
 */
string AirconditionControl::setClernIndoor(int on,int manualOrnot)
{
    return airConditionLogic->setClernIndoor(on,manualOrnot);
}

/**
 * 设置室外清洁
 */
string AirconditionControl::setClernOutdoor(int on,int manualOrnot)
{
    return airConditionLogic->setClernOutdoor(on,manualOrnot);
}

/**
 * 设置智慧眼
 */
string AirconditionControl::setSmartEye(int on,int manualOrnot)
{
    return airConditionLogic->setSmartEye(on,manualOrnot);
}

/**
 * 设置室静音
 */
string AirconditionControl::setMute(int on,int manualOrnot)
{
    return airConditionLogic->setMute(on,manualOrnot);
}

/**
 * 设置语音
 */
string AirconditionControl::setVoice(int on,int manualOrnot)
{
    return airConditionLogic->setVoice(on,manualOrnot);
}

/**
 * 设置除烟
 */
string AirconditionControl::setClernSmoke(int on,int manualOrnot)
{
    return airConditionLogic->setClernSmoke(on,manualOrnot);
}

/**
 * 设置背景灯
 */
string AirconditionControl::setBackgroundLamp(int on,int manualOrnot)
{
    return airConditionLogic->setBackgroundLamp(on,manualOrnot);
}

/**
 * 显示屏发光
 */
string AirconditionControl::setScreen(int on,int manualOrnot)
{
    return airConditionLogic->setScreen(on,manualOrnot);
}

/**
 * LED指示灯
 */
string AirconditionControl::setLED(int on,int manualOrnot)
{
    return airConditionLogic->setLED(on,manualOrnot);
}

/**
 * 室内外温度切换显示
 */
string AirconditionControl::setIndoorOutdoorSwitch(int on,int manualOrnot)
{
    return airConditionLogic->setIndoorOutdoorSwitch(on,manualOrnot);
    
}

/**
 * 室内过滤网清洁复位控制
 */
string AirconditionControl::setIndoorFilterClear(int on,int manualOrnot)
{
    return airConditionLogic->setIndoorFilterClear(on,manualOrnot);
}

/**
 * 显示屏亮度值
 */
string AirconditionControl::setScreenLuminance(int light,int manualOrnot)
{
    return airConditionLogic->setScreenLuminance(light,manualOrnot);
}

/**
 * 直接设置开/关机
 */
string AirconditionControl::setDirctPower(string devid,int on,int manualOrnot)
{
    return airConditionLogic->setDirctPower(devid,on,manualOrnot);
}

/**
 * 获取空调所有状态
 */
string AirconditionControl::getAirConditionAllStatus(int manualOrnot)
{
    return airConditionLogic->getAirConditionAllStatus(manualOrnot);
}

/**************************************** 状态 ****************************************/
/**
 * 获取风量
 */
string AirconditionControl::getWindSpeed()
{
    return airConditionLogic->getWindSpeed();
}

/**
 * 获取睡眠
 */
string AirconditionControl::getSleepMode()
{
    return airConditionLogic->getSleepMode();
}

/**
 * 获取xx
 */
string AirconditionControl::getSleep()
{
    return airConditionLogic->getSleep();
}

/**
 * 获取模式
 */
string AirconditionControl::getMode()
{
    return airConditionLogic->getMode();
}

/**
 * 获取开机
 */
string AirconditionControl::getPower()
{
    return airConditionLogic->getPower();
}

/**
 * 获取风量
 */
/*风向*/
string AirconditionControl::getWindDirection()
{
    return airConditionLogic->getWindDirection();
    
}

/**
 * 获取设置温度
 */
string AirconditionControl::getSetingTemperature()
{
    return airConditionLogic->getSetingTemperature();
}

/**
 * 获取湿度
 */
string AirconditionControl::getHumidity()
{
    return airConditionLogic->getHumidity();
}

/**
 * 获取体感室内温度
 */
string AirconditionControl::getSomatosensoryRealityTemperature()
{
    return airConditionLogic->getSomatosensoryRealityTemperature();
}

/**
 * 获取室内实际温度
 */
string AirconditionControl::getIndoorRealityTemperature()
{
    return airConditionLogic->getIndoorRealityTemperature();
}

/**
 * 获取室内盘管温度
 */
string AirconditionControl::getIndoorPipeTemperature()
{
    return airConditionLogic->getIndoorPipeTemperature();
}

/**
 * 获取室内实际湿度值
 */
string AirconditionControl::getIndoorRealityHumidity()
{
    return airConditionLogic->getIndoorRealityHumidity();
}

/**
 * 获取体感室内温度补偿
 */
string AirconditionControl::getSomatosensoryCompensation()
{
    return airConditionLogic->getSomatosensoryCompensation();
}

/**
 * 获取体感控制
 */
string AirconditionControl::getSomatosensoryContrl()
{
    return airConditionLogic->getSomatosensoryContrl();
}

/**
 * 获取自动工作模式和除湿模式的温度补偿
 */
string AirconditionControl::getTemperatureCompensation()
{
    return airConditionLogic->getTemperatureCompensation();
}

/**
 * 获取华氏/摄氏温度显示设置
 */
string AirconditionControl::getTemperatureValueSwitch()
{
    return airConditionLogic->getTemperatureValueSwitch();
}

/**
 * 获取普通定时开关机
 */
string AirconditionControl::getGeneralTimingShutdownValue()
{
    return airConditionLogic->getGeneralTimingShutdownValue();
}

/**
 * 获取实时时钟的小时值
 */
string AirconditionControl::getRealityHour()
{
    return airConditionLogic->getRealityHour();
}

/**
 * 获取实时时钟的分钟值
 */
string AirconditionControl::getRealityMinute()
{
    return airConditionLogic->getRealityMinute();
}

/**
 * 获取实时开机控制
 */
string AirconditionControl::getRealityBootContrl()
{
    return airConditionLogic->getRealityBootContrl();
}

/**
 * 获取实时开机小时
 */
string AirconditionControl::getRealityBootHour()
{
    return airConditionLogic->getRealityBootHour();
}

/**
 * 获取实时开机分钟
 */
string AirconditionControl::getRealityBootMinute()
{
    return airConditionLogic->getRealityBootMinute();
}

/**
 * 获取实时关机控制
 */
string AirconditionControl::getRealityShutdownContrl()
{
    return airConditionLogic->getRealityShutdownContrl();
}

/**
 * 获取实时关机小时
 */
string AirconditionControl::getRealityShutdownHour()
{
    return airConditionLogic->getRealityShutdownHour();
}

/**
 * 获取实时关机分钟
 */
string AirconditionControl::getRealityShutdownMinute()
{
    return airConditionLogic->getRealityShutdownMinute();
}

/**
 * 获取除湿模式
 */
string AirconditionControl::getDehumidificationMode()
{
    return airConditionLogic->getDehumidificationMode();
}

/**
 * 获取上下风门
 */
string AirconditionControl::getVerticalWindMode()
{
    return airConditionLogic->getVerticalWindMode();
}

/**
 * 获取上下风开停控制
 */
string AirconditionControl::getVerticalWindContrl()
{
    return airConditionLogic->getVerticalWindContrl();
}

/**
 * 获取左右风开停控制
 */
string AirconditionControl::getHorizontalWindContrl()
{
    return airConditionLogic->getHorizontalWindContrl();
}

/**
 * 获取自然风开停控制
 */
string AirconditionControl::getNatureWindContrl()
{
    return airConditionLogic->getNatureWindContrl();
}

/**
 * 获取电热
 */
string AirconditionControl::getElectricalHeating()
{
    return airConditionLogic->getElectricalHeating();
}

/**
 * 获取节能
 */
string AirconditionControl::getEnergyConservation()
{
    return airConditionLogic->getEnergyConservation();
}

/**
 * 获取并用节电
 */
string AirconditionControl::getShare()
{
    return airConditionLogic->getShare();
}

/**
 * 获取高效
 */
string AirconditionControl::getEfficient()
{
    return airConditionLogic->getEfficient();
}

/**
 * 获取双模
 */
string AirconditionControl::getDualMode()
{
    return airConditionLogic->getDualMode();
}

/**
 * 获取清新
 */
string AirconditionControl::getFreshness()
{
    return airConditionLogic->getFreshness();
}

/**
 * 获取换风
 */
string AirconditionControl::getFreshAir()
{
    return airConditionLogic->getFreshAir();
}

/**
 * 获取室内清洁
 */
string AirconditionControl::getClernIndoor()
{
    return airConditionLogic->getClernIndoor();
}

/**
 * 获取室外清洁
 */
string AirconditionControl::getClernOutdoor()
{
    return airConditionLogic->getClernOutdoor();
}

/**
 * 获取智慧眼
 */
string AirconditionControl::getSmartEye()
{
    return airConditionLogic->getSmartEye();
}

/**
 * 获取静音
 */
string AirconditionControl::getMute()
{
    return airConditionLogic->getMute();
}

/**
 * 获取语音
 */
string AirconditionControl::getVoice()
{
    return airConditionLogic->getVoice();
}

/**
 * 获取除烟
 */
string AirconditionControl::getClernSmoke()
{
    return airConditionLogic->getClernSmoke();
}

/**
 * 获取背景灯
 */
string AirconditionControl::getBackgroundLamp()
{
    return airConditionLogic->getBackgroundLamp();
}

/**
 * 获取显示屏发光
 */
string AirconditionControl::getScreen()
{
    return airConditionLogic->getScreen();
}

/**
 * 获取LED指示灯
 */
string AirconditionControl::getLED()
{
    return airConditionLogic->getLED();
}

/**
 * 获取室内外温度切换显示
 */
string AirconditionControl::getIndoorOutdoorSwitch()
{
    return airConditionLogic->getIndoorOutdoorSwitch();
}

/**
 * 获取室内过滤网清洁复位控制
 */
string AirconditionControl::getIndoorFilterClear()
{
    return airConditionLogic->getIndoorFilterClear();
}

/**
 * 获取左风摆
 */
string AirconditionControl::getLeftWind()
{
    return airConditionLogic->getLeftWind();
}

/**
 * 获取右风摆
 */
string AirconditionControl::getRightWind()
{
    return airConditionLogic->getRightWind();
}

/**
 * 获取室内电量板
 */
string AirconditionControl::getChargeBorad ()
{
    return airConditionLogic->getChargeBorad();
}

/**
 * 获取本次命令之前是否有过红外遥控与按键控制过
 */
string AirconditionControl::getHaveIRContrl()
{
    return airConditionLogic->getHaveIRContrl();
}

/**
 * 获取本次命令之前是否有过WIFI控制过
 */
string AirconditionControl::getHaveWIFIContrl()
{
    return airConditionLogic->getHaveWIFIContrl();
}

/**
 * 获取空调正常机型与测试机型
 */
string AirconditionControl::getModel()
{
    return airConditionLogic->getModel();
}

/**
 * 获取室内EEPROM在线升级
 */
string AirconditionControl::getEEPROMUpdate()
{
    return airConditionLogic->getEEPROMUpdate();
}

/**
 * 获取室内温度传感器故障
 */
string AirconditionControl::getIndoorTemperatureSensorTrouble()
{
    return airConditionLogic->getIndoorTemperatureSensorTrouble();
}

/**
 * 获取室内盘管温度传感器故障
 */
string AirconditionControl::getIndoorPipeTemperatureSensorTrouble()
{
    return airConditionLogic->getIndoorPipeTemperatureSensorTrouble();
}

/**
 * 获取室内湿度传感器故障
 */
string AirconditionControl::getIndoorHumiditySensorTrouble()
{
    return airConditionLogic->getIndoorHumiditySensorTrouble();
}

/**
 * 获取室内排水泵故障
 */
string AirconditionControl::getIndoorDrainsWaterPumpTrouble()
{
    return airConditionLogic->getIndoorDrainsWaterPumpTrouble();
}

/**
 * 获取室内风机电机运转异常故障
 */
string AirconditionControl::getIndoorFanMotorTrouble()
{
    return airConditionLogic->getIndoorFanMotorTrouble();
}

/**
 * 获取柜机格栅保护告警
 */
string AirconditionControl::getPioneerGrillingProtectTrouble()
{
    return airConditionLogic->getPioneerGrillingProtectTrouble();
}

/**
 * 获取室内电压过零检测故障
 */
string AirconditionControl::getIndoorVoltageZeroCrossDetectionTrouble()
{
    return airConditionLogic->getIndoorVoltageZeroCrossDetectionTrouble();
}

/**
 * 获取室内外通信故障
 */
string AirconditionControl::getIndoorOutdoorCommunicationTrouble()
{
    return airConditionLogic->getIndoorOutdoorCommunicationTrouble();
}

/**
 * 获取室内控制板与显示板通信故障
 */
string AirconditionControl::getIndoorContrlScreenCommunicationTrouble()
{
    return airConditionLogic->getIndoorContrlScreenCommunicationTrouble();
}

/**
 * 获取室内控制板与按键板通信故障
 */
string AirconditionControl::getIndoorContrlKeypadCommunicationTrouble()
{
    return airConditionLogic->getIndoorContrlKeypadCommunicationTrouble();
}

/**
 * 获取WIFI控制板与室内控制板通信故障
 */
string AirconditionControl::getIndoorContrlWIFICommunicationTrouble()
{
    return airConditionLogic->getIndoorContrlWIFICommunicationTrouble();
}

/**
 * 获取室内控制板与室内电量板通信故障
 */
string AirconditionControl::getIndoorContrlChargeCommunicationTrouble()
{
    return airConditionLogic->getIndoorContrlChargeCommunicationTrouble();
}

/**
 * 获取室内控制板EEPROM出错
 */
string AirconditionControl::getIndoorContrlEEPROMTrouble()
{
    return airConditionLogic->getIndoorContrlEEPROMTrouble();
}

/**
 * 获取运行频率
 */
string AirconditionControl::getRunFrequency()
{
    return airConditionLogic->getRunFrequency();
}

/**
 * 获取目标频率
 */
string AirconditionControl::getTargetFrequency()
{
    return airConditionLogic->getTargetFrequency();
}

/**
 * 获取发给驱动器的频率
 */
string AirconditionControl::getDriveFrequency()
{
    return airConditionLogic->getDriveFrequency();
}

/**
 * 获取环境温度
 */
string AirconditionControl::getEnvironmentTemperature()
{
    return airConditionLogic->getEnvironmentTemperature();
}

/**
 * 获取冷凝器温度
 */
string AirconditionControl::getCondenserTemperature()
{
    return airConditionLogic->getCondenserTemperature();
}

/**
 * 获取排气温度
 */
string AirconditionControl::getExhaustTemperature()
{
    return airConditionLogic->getExhaustTemperature();
}

/**
 * 获取目标排气温度
 */
string AirconditionControl::getTargetExhaustTemperature()
{
    return airConditionLogic->getTargetExhaustTemperature();
}

/**
 * 获取室外电子膨胀阀开度
 */
string AirconditionControl::getOutdoorElectronicExpansion()
{
    return airConditionLogic->getOutdoorElectronicExpansion();
}

/**
 * 获取UABH
 */
string AirconditionControl::getUABH()
{
    return airConditionLogic->getUABH();
}

/**
 * 获取UABL
 */
string AirconditionControl::getUABL()
{
    return airConditionLogic->getUABL();
}

/**
 * 获取UBCH
 */
string AirconditionControl::getUBCH()
{
    return airConditionLogic->getUBCH();
}

/**
 * 获取UBCL
 */
string AirconditionControl::getUBCL()
{
    return airConditionLogic->getUBCL();
}

/**
 * 获取UCAH
 */
string AirconditionControl::getUCAH()
{
    return airConditionLogic->getUCAH();
}

/**
 * 获取UCAL
 */
string AirconditionControl::getUCAL()
{
    return airConditionLogic->getUCAL();
}

/**
 * 获取IAB
 */
string AirconditionControl::getIAB()
{
    return airConditionLogic->getIAB();
}

/**
 * 获取IBC
 */
string AirconditionControl::getIBC()
{
    return airConditionLogic->getIBC();
}

/**
 * 获取ICA
 */
string AirconditionControl::getICA()
{
    return airConditionLogic->getICA();
}

/**
 * 获取IUV
 */
string AirconditionControl::getIUV()
{
    return airConditionLogic->getIUV();
}

/**
 * 获取直流母线电压H
 */
string AirconditionControl::getCocurrentBusVoltageH()
{
    return airConditionLogic->getCocurrentBusVoltageH();
}

/**
 * 获取直流母线电压L
 */
string AirconditionControl::getCocurrentBusVoltageL()
{
    return airConditionLogic->getCocurrentBusVoltageL();
}

/**
 * 获取四通阀状态
 */
string AirconditionControl::getFourWayLimen()
{
    return airConditionLogic->getFourWayLimen();
}

/**
 * 获取室外机实际工作状态
 */
string AirconditionControl::getOutdoorRealityRuning()
{
    return airConditionLogic->getOutdoorRealityRuning();
}

/**
 * 获取风机运行状态
 */
string AirconditionControl::getFanRuning()
{
    return airConditionLogic->getFanRuning();
}

/**
 * 获取室外机强制室内机风门位置
 */
string AirconditionControl::getOutdoorForceIndoorWindPosition()
{
    return airConditionLogic->getOutdoorForceIndoorWindPosition();
}

/**
 * 获取室外机强制室内机风速
 */
string AirconditionControl::getOutdoorForceIndoorWindSpeed()
{
    return airConditionLogic->getOutdoorForceIndoorWindSpeed();
}

/**
 * 获取室外机强制室内机停
 */
string AirconditionControl::getOutdoorForceIndoorStop()
{
    return airConditionLogic->getOutdoorForceIndoorStop();
}

/**
 * 获取温控关机
 */
string AirconditionControl::getShutdownByTemperatureContrl()
{
    return airConditionLogic->getShutdownByTemperatureContrl();
}

/**
 * 获取一拖多标志
 */
string AirconditionControl::getOne4All()
{
    return airConditionLogic->getOne4All();
}

/**
 * 获取除湿阀标志
 */
string AirconditionControl::getDehumidifierLimen()
{
    return airConditionLogic->getDehumidifierLimen();
}

/**
 * 获取室外机化霜
 */
string AirconditionControl::getOutdoorDefrosting()
{
    return airConditionLogic->getOutdoorDefrosting();
}

/**
 * 获取室外旁通化霜
 */
string AirconditionControl::getOutdoorBypassDefrosting()
{
    return airConditionLogic->getOutdoorBypassDefrosting();
}

/**
 * 获取回油标志
 */
string AirconditionControl::getOilReturn()
{
    return airConditionLogic->getOilReturn();
}

/**
 * 获取室外故障显示标志
 */
string AirconditionControl::getOutdoorTroubleDisplay()
{
    return airConditionLogic->getOutdoorTroubleDisplay();
}

/**
 * 获取室外机EEPROM在线下载标志
 */
string AirconditionControl::getOutdoorEEPROMDownload()
{
    return airConditionLogic->getOutdoorEEPROMDownload();
}

/**
 * 获取室外机电量板
 */
string AirconditionControl::getOutdoorChargeBoard()
{
    return airConditionLogic->getOutdoorChargeBoard();
}

/**
 * 获取压缩机电热带
 */
string AirconditionControl::getcompressorRibbonHeater()
{
    return airConditionLogic->getcompressorRibbonHeater();
}

/**
 * 获取
 */
/*压缩机预加热*/
string AirconditionControl::getcompressorBeforeHandheat()
{
    return airConditionLogic->getcompressorBeforeHandheat();
}

/**
 * 获取补气增晗
 */
string AirconditionControl::getReinflation()
{
    return airConditionLogic->getReinflation();
}

/**
 * 获取室内外机模式冲突
 */
string AirconditionControl::getOutdoorModeClash()
{
    return airConditionLogic->getOutdoorModeClash();
}

/**
 * 获取室外EEPROM出错
 */
string AirconditionControl::getOutdoorEEPROMTrouble()
{
    return airConditionLogic->getOutdoorEEPROMTrouble();
}

/**
 * 获取室外盘管温度传感器故障
 */
string AirconditionControl::getOutdoorPipeTemperatureSensorTrouble()
{
    return airConditionLogic->getOutdoorPipeTemperatureSensorTrouble();
}

/**
 * 获取排气温度传感器故障
 */
string AirconditionControl::getOutdoorExhausTemperatureSensorTrouble()
{
    return airConditionLogic->getOutdoorExhausTemperatureSensorTrouble();
}

/**
 * 获取室外环境温度传感器故障
 */
string AirconditionControl::getOutdoorEnvironmentTemperatureSensorTrouble()
{
    return airConditionLogic->getOutdoorEnvironmentTemperatureSensorTrouble();
}

/**
 * 获取电压变压器故障
 */
string AirconditionControl::getVoltageTransformerTrouble()
{
    return airConditionLogic->getVoltageTransformerTrouble();
}

/**
 * 获取电流互感器故障
 */
string AirconditionControl::getCurrentTransformerTrouble()
{
    return airConditionLogic->getCurrentTransformerTrouble();
}

/**
 * 获取室外控制与驱动通信故障
 */
string AirconditionControl::getOutdoorContrlDriveCommunicationTrouble()
{
    return airConditionLogic->getOutdoorContrlDriveCommunicationTrouble();
}

/**
 * 获取IPM模块过流保护
 */
string AirconditionControl::getIPMOvercurrentProtect()
{
    return airConditionLogic->getIPMOvercurrentProtect();
}

/**
 * 获取IPM模块过热保护
 */
string AirconditionControl::getIPMOverheatingProtect()
{
    return airConditionLogic->getIPMOverheatingProtect();
}

/**
 * 获取交流电过电压保护
 */
string AirconditionControl::getAlternatingCurrentOvervoltageProtect()
{
    return airConditionLogic->getAlternatingCurrentOvervoltageProtect();
}

/**
 * 获取交流电欠电压保护
 */
string AirconditionControl::getAlternatingCurrentUndervoltageProtect()
{
    return airConditionLogic->getAlternatingCurrentUndervoltageProtect();
}

/**
 * 获取母线电压过电压保护
 */
string AirconditionControl::getBusbarVoltageOvervoltageProtect()
{
    return airConditionLogic->getBusbarVoltageOvervoltageProtect();
}

/**
 * 获取
 */
/*母线电压欠电压保护*/
string AirconditionControl::getBusbarVoltageUndervoltageProtect()
{
    return airConditionLogic->getBusbarVoltageUndervoltageProtect();
}

/**
 * 获取PFC过电流保护
 */
string AirconditionControl::getPFCOvercurrentProtect()
{
    return airConditionLogic->getPFCOvercurrentProtect();
}

/**
 * 获取室外机最大电流保护
 */
string AirconditionControl::getOutdoorMaximumCurrentProtect()
{
    return airConditionLogic->getOutdoorMaximumCurrentProtect();
}

/**
 * 获取室外环境温度过低保护
 */
string AirconditionControl::getOutdooEnvironmentOvertemperatureProtect()
{
    return airConditionLogic->getOutdooEnvironmentOvertemperatureProtect();
}

/**
 * 获取排气温度过高保护
 */
string AirconditionControl::getExhaustOvertemperatureProtect()
{
    return airConditionLogic->getExhaustOvertemperatureProtect();
}

/**
 * 获取压缩机管壳温度保护
 */
string AirconditionControl::getCompressoPipeShellTemperatureProtect()
{
    return airConditionLogic->getCompressoPipeShellTemperatureProtect();
}

/**
 * 获取室内防冻结或防过载保护
 */
string AirconditionControl::getIndoorAntiFreezingProtect()
{
    return airConditionLogic->getIndoorAntiFreezingProtect();
}

/**
 * 室外机PFC保护
 */
string AirconditionControl::getOutdoorPFCProtect()
{
    return airConditionLogic->getOutdoorPFCProtect();
}

/**
 * 压缩机启动失败
 */
string AirconditionControl::getCompressoBootFail()
{
    return airConditionLogic->getCompressoBootFail();
}

/**
 * 获取压缩机失步
 */
string AirconditionControl::getCompressoStepOut()
{
    return airConditionLogic->getCompressoStepOut();
}

/**
 * 获取室外风机堵转
 */
string AirconditionControl::getOutdoorFanLockRotor()
{
    return airConditionLogic->getOutdoorFanLockRotor();
}

/**
 * 获取室外盘管防过载保护
 */
string AirconditionControl::getOutdoorPieOverloadProtect()
{
    return airConditionLogic->getOutdoorPieOverloadProtect();
}

/**
 * 获取冷媒泄漏
 */
string AirconditionControl::getRefrigerantLeakage()
{
    return airConditionLogic->getRefrigerantLeakage();
}

/**
 * 获取压缩机型号匹配错误
 */
string AirconditionControl::getCompressoModelMismatch()
{
    return airConditionLogic->getCompressoModelMismatch();
}

/**
 * 获取系统低频振动保护
 */
string AirconditionControl::getSystemLowFrequencyVibrationProtect()
{
    return airConditionLogic->getSystemLowFrequencyVibrationProtect();
}

/**
 * 获取室外散热器温度过高保护
 */
string AirconditionControl::getOutdoorRadiatorOvertemperatureProtect()
{
    return airConditionLogic->getOutdoorRadiatorOvertemperatureProtect();
}

/**
 * 获取系统压力过高保护
 */
string AirconditionControl::getSystemHypertonusProtect()
{
    return airConditionLogic->getSystemHypertonusProtect();
}

/**
 * 获取逆变器直流过电压故障
 */
string AirconditionControl::getInverterCocurrentOvervoltageTrouble()
{
    return airConditionLogic->getInverterCocurrentOvervoltageTrouble();
}

/**
 * 获取逆变器直流低电压故障
 */
string AirconditionControl::getInverterCocurrentUndervoltageTrouble()
{
    return airConditionLogic->getInverterCocurrentUndervoltageTrouble();
}

/**
 * 获取逆变器交流过电流故障
 */
string AirconditionControl::getInverterCocurrentOvercurrentTrouble()
{
    return airConditionLogic->getInverterCocurrentOvercurrentTrouble();
}

/**
 * 获取失步检出
 */
string AirconditionControl::getStepOutDetection()
{
    return airConditionLogic->getStepOutDetection();
}

/**
 * 获取速度推定脉冲检出法检出欠相故障
 */
string AirconditionControl::getSpeedPulseFault()
{
    return airConditionLogic->getSpeedPulseFault();
}

/**
 * 获取电流推定脉冲检出法检出欠相故障
 */
string AirconditionControl::getCurrentPulseFault()
{
    return airConditionLogic->getCurrentPulseFault();
}

/**
 * 获取逆变器IPM故障-边沿
 */
string AirconditionControl::getInverterEdgeFault()
{
    return airConditionLogic->getInverterEdgeFault();
}

/**
 * 获取逆变器IPM故障-电平
 */
string AirconditionControl::getInverterLevelFault()
{
    return airConditionLogic->getInverterLevelFault();
}

/**
 * 获取PFC_IPM故障-边沿
 */
string AirconditionControl::getPFC_IPMEdgeFault()
{
    return airConditionLogic->getPFC_IPMEdgeFault();
}

/**
 * 获取PFC_IPM故障-电平
 */
string AirconditionControl::getPFC_IPMLevelFault()
{
    return airConditionLogic->getPFC_IPMLevelFault();
}

/**
 * 获取PFC停电检出故障
 */
string AirconditionControl::getPFCPowerCutFault()
{
    return airConditionLogic->getPFCPowerCutFault();
}

/**
 * 获取PFC过电流检出故障
 */
string AirconditionControl::getPFCOvercurrentFault()
{
    return airConditionLogic->getPFCOvercurrentFault();
}

/**
 * 获取直流电压检出异常
 */
string AirconditionControl::getDCVException()
{
    return airConditionLogic->getDCVException();
}

/**
 * 获取PFC低电压（有效值）检出故障
 */
string AirconditionControl::getPFCLowVoltageFault()
{
    return airConditionLogic->getPFCLowVoltageFault();
}

/**
 * 获取AD偏置异常检出故障
 */
string AirconditionControl::getADOffsetAnomaliesFault()
{
    return airConditionLogic->getADOffsetAnomaliesFault();
}

/**
 * 获取逆变器PWM逻辑设置故障
 */
string AirconditionControl::getInverterPWMLogicFault()
{
    return airConditionLogic->getInverterPWMLogicFault();
}

/**
 * 获取逆变器PWM初始化故障
 */
string AirconditionControl::getInverterPWMInitFault()
{
    return airConditionLogic->getInverterPWMInitFault();
}

/**
 * 获取PFC_PWM逻辑设置故障
 */
string AirconditionControl::getPFCPWMLogicFault()
{
    return airConditionLogic->getPFCPWMLogicFault();
}

/**
 * 获取PFC_PWM初始化故障
 */
string AirconditionControl::getPFC_PWMInitFault()
{
    return airConditionLogic->getPFC_PWMInitFault();
}

/**
 * 获取温度异常
 */
string AirconditionControl::getTemperatureAnomaly()
{
    return airConditionLogic->getTemperatureAnomaly();
}

/**
 * 获取电流采样电阻不平衡调整故障
 */
string AirconditionControl::getCurrentSamplingFault()
{
    return airConditionLogic->getCurrentSamplingFault();
}

/**
 * 获取电机参数设置故障
 */
string AirconditionControl::getMotorDataFault()
{
    return airConditionLogic->getMotorDataFault();
}

/**
 * 获取MCE故障
 */
string AirconditionControl::getMCEFault()
{
    return airConditionLogic->getMCEFault();
}

/**
 * 获取驱动EEPROM故障
 */
string AirconditionControl::getEEPROMFault()
{
    return airConditionLogic->getEEPROMFault();
}

/**
 * 获取室外盘管过载禁升频
 */
string AirconditionControl::getOutdoorCoilOverloadUpFrequency()
{
    return airConditionLogic->getOutdoorCoilOverloadUpFrequency();
}

/**
 * 获取室外盘管过载降频
 */
string AirconditionControl::getOutdoorCoilOverloadDownFrequency()
{
    return airConditionLogic->getOutdoorCoilOverloadDownFrequency();
}

/**
 * 获取室内盘管过载禁升频
 */
string AirconditionControl::getIndoorCoilOverloadUpFrequency()
{
    return airConditionLogic->getIndoorCoilOverloadUpFrequency();
}

/**
 * 获取室内盘管过载降频
 */
string AirconditionControl::getIndoorCoilOverloadDownFrequency()
{
    return airConditionLogic->getIndoorCoilOverloadDownFrequency();
}

/**
 * 获取压降排气过载禁升频
 */
string AirconditionControl::getPressureUpFrequency()
{
    return airConditionLogic->getPressureUpFrequency();
}

/**
 * 获取压降排气过载降频
 */
string AirconditionControl::getPressureDownFrequency()
{
    return airConditionLogic->getPressureDownFrequency();
}

/**
 * 获取室内盘管冻结禁升频
 */
string AirconditionControl::getIndoorCoilFreezingUpFrequency()
{
    return airConditionLogic->getIndoorCoilFreezingUpFrequency();
}

/**
 * 获取室内盘管冻结降频
 */
string AirconditionControl::getIndoorCoilFreezingDownFrequency()
{
    return airConditionLogic->getIndoorCoilFreezingDownFrequency();
}

/**
 * 获取室内外通信降频
 */
string AirconditionControl::getCommunicationDownFrequency()
{
    return airConditionLogic->getCommunicationDownFrequency();
}

/**
 * 获取模块温度过载限频
 */
string AirconditionControl::getModuleTemperaturelimitFrequency()
{
    return airConditionLogic->getModuleTemperaturelimitFrequency();
}

/**
 * 获取变调率限频
 */
string AirconditionControl::getModulationRatelimitFrequency()
{
    return airConditionLogic->getModulationRatelimitFrequency();
}

/**
 * 获取相电流限频
 */
string AirconditionControl::getPhaseCurrentlimitFrequency()
{
    return airConditionLogic->getPhaseCurrentlimitFrequency();
}

/**
 * 获取并用节电保护禁升频
 */
string AirconditionControl::getPowerSaveUpFrequency()
{
    return airConditionLogic->getPowerSaveUpFrequency();
}

/**
 * 获取并用节电保护降频
 */
string AirconditionControl::getPowerSaveDownFrequency()
{
    return airConditionLogic->getPowerSaveDownFrequency();
}

/**
 * 获取过电流保护禁升频
 */
string AirconditionControl::getOvercurrentUpFrequency()
{
    return airConditionLogic->getOvercurrentUpFrequency();
}

/**
 * 获取过电流保护降频
 */
string AirconditionControl::getOvercurrentDownFrequency()
{
    return airConditionLogic->getOvercurrentDownFrequency();
}

/**
 * 获取室内风机转速xx
 */
string AirconditionControl::getIndoorFanSpeedH()
{
    return airConditionLogic->getIndoorFanSpeedH();
}

/**
 * 获取室内风机转速00xx
 */
string AirconditionControl::getIndoorFanSpeed00L()
{
    return airConditionLogic->getIndoorFanSpeed00L();
}

/**
 * 获取有否PM2.5检测功能
 */
string AirconditionControl::getPM25()
{
    return airConditionLogic->getPM25();
}

/**
 * 获取PM2.5污染程度
 */
string AirconditionControl::getPM25Level()
{
    return airConditionLogic->getPM25Level();
}

/**
 * 获取空气PM2.5质量百分比表示
 */
string AirconditionControl::getPM25Percent()
{
    return airConditionLogic->getPM25Percent();
}

/**
 * 获取显示屏亮度值
 */
string AirconditionControl::getScreenLuminance()
{
    return airConditionLogic->getScreenLuminance();
}

/**
 * 获取普通定时开关机有效
 */
string AirconditionControl::getGeneralTimingShutdown()
{
    return airConditionLogic->getGeneralTimingShutdown();
}

/**************************************** 功能 ****************************************/
/**
 * 获取命令支持状态
 */
int AirconditionControl::getWindSpeedNum()
{
    return airConditionLogic->getWindSpeedNum();
}

/**
 * 设置睡眠模式
 */
int AirconditionControl::getSleepModeFN()
{
    return airConditionLogic->getSleepModeFN();
}

/**
 * 设置模式
 */
int AirconditionControl::getCoolModeFN()
{
    return airConditionLogic->getCoolModeFN();
}

/**
 * 开/关机
 */
int AirconditionControl::getPowerFN()
{
    return airConditionLogic->getPowerFN();
}

/**
 * 室内单个风向控制功能
 */
int AirconditionControl::getWindDirectionFN()
{
    return airConditionLogic->getWindDirectionFN();
}

/**
 * 设置温度
 */
int AirconditionControl::getTemperatureFN()
{
    return airConditionLogic->getTemperatureFN();
}

/**
 * 设置湿度
 */
int AirconditionControl::getHumidityFN()
{
    return airConditionLogic->getHumidityFN();
}

/**
 * 体感控制,体感室内温度,体感室内温度补偿
 */
int AirconditionControl::getSomatosensoryRealityTemperatureFN()
{
    return airConditionLogic->getSomatosensoryRealityTemperatureFN();
}

/**
 * 自动工作模式和除湿模式的温度补偿
 */
int AirconditionControl::getTemperatureCompensationFN()
{
    return airConditionLogic->getTemperatureCompensationFN();
}

/**
 * 华氏/摄氏温度显示设置
 */
int AirconditionControl::getTemperatureValueSwitchFN()
{
    return airConditionLogic->getTemperatureValueSwitchFN();
}

/**
 * 普通定时关机,普通定时关机时间
 */
int AirconditionControl::getGeneralTimingShutdownFN()
{
    return airConditionLogic->getGeneralTimingShutdownFN();
}

/**
 * 实时开机控制,实时时钟的小时值,实时时钟的分钟值,实时开机小时,实时开机分钟
 */
int AirconditionControl::getRealityTimeFN()
{
    return airConditionLogic->getRealityTimeFN();
}

/**
 * 6位置可定室内风门位置控制
 */
int AirconditionControl::getVerticalWindModeNum()
{
    return airConditionLogic->getVerticalWindModeNum();
}

/**
 * 上下风门模式,上下风开停控制
 */
int AirconditionControl::getVerticalWindFN()
{
    return airConditionLogic->getVerticalWindFN();
}

/**
 * 左右风开停控制,左风摆,右风摆
 */
int AirconditionControl::getHorizontalWindFN()
{
    return airConditionLogic->getHorizontalWindFN();
}

/**
 * 自然风开停
 */
int AirconditionControl::getNatureWindFN()
{
    return airConditionLogic->getNatureWindFN();
}

/**
 * 设置电加热
 */
int AirconditionControl::getElectricalHeatingFN()
{
    return airConditionLogic->getElectricalHeatingFN();
}

/**
 * 除湿模式
 */
int AirconditionControl::getDehumidificationModeFN()
{
    return airConditionLogic->getDehumidificationModeFN();
}

/**
 * 设置节能
 */
int AirconditionControl::getEnergyConservationFN()
{
    return airConditionLogic->getEnergyConservationFN();
}

/**
 * 设置并且节能
 */
int AirconditionControl::getShareFN()
{
    return airConditionLogic->getShareFN();
}

/**
 * 设置高效
 */
int AirconditionControl::getEfficientFN()
{
    return airConditionLogic->getEfficientFN();
}

/**
 * 设置双模
 */
int AirconditionControl::getDualModeFN()
{
    return airConditionLogic->getDualModeFN();
}

/**
 * 设置清新
 */
int AirconditionControl::getFreshnessFN()
{
    return airConditionLogic->getFreshnessFN();
}

/**
 * 设置换风
 */
int AirconditionControl::getFreshAirFN()
{
    return airConditionLogic->getFreshAirFN();
}

/**
 * 设置室内清洁
 */
int AirconditionControl::getClernIndoorFN()
{
    return airConditionLogic->getClernIndoorFN();
}

/**
 * 设置室外清洁
 */
int AirconditionControl::getClernOutdoorFN()
{
    return airConditionLogic->getClernOutdoorFN();
}

/**
 * 设置室智能眼
 */
int AirconditionControl::getSmartEyeFN()
{
    return airConditionLogic->getSmartEyeFN();
}

/**
 * 设置室静音
 */
int AirconditionControl::getMuteFN()
{
    return airConditionLogic->getMuteFN();
}

/**
 * 设置语音
 */
int AirconditionControl::getVoiceFN()
{
    return airConditionLogic->getVoiceFN();
}

/**
 * 设置除烟
 */
int AirconditionControl::getClernSmokeFN()
{
    return airConditionLogic->getClernSmokeFN();
}

/**
 * 背景灯
 */
int AirconditionControl::getBackgroundLampFN()
{
    return airConditionLogic->getBackgroundLampFN();
}

/**
 * 显示屏发光
 */
int AirconditionControl::getScreenFN()
{
    return airConditionLogic->getScreenFN();
}

/**
 * LED指示灯
 */
int AirconditionControl::getLEDFN()
{
    return airConditionLogic->getLEDFN();
}

/**
 * 室内外温度切换显示
 */
int AirconditionControl::getIndoorOutdoorSwitchFN()
{
    return airConditionLogic->getIndoorOutdoorSwitchFN();
}

/**
 * 室内过滤网清洁复位控制
 */
int AirconditionControl::getIndoorFilterClearFN()
{
    return airConditionLogic->getIndoorFilterClearFN();
}

/**
 * 左风摆开停控制
 */
int AirconditionControl::getLeftFanContrlFN()
{
    return airConditionLogic->getLeftFanContrlFN();
}

/**
 * 右风摆开停控制
 */
int AirconditionControl::getRightFanContrlFN()
{
    return airConditionLogic->getRightFanContrlFN();
}

/**
 * 控制规则
 */
int AirconditionControl::getContrlRate()
{
    return airConditionLogic->getContrlRate();
}

/********* 设置功能 ********/
/**
 * 设置睡眠模式
 */
void AirconditionControl::setWindSpeedFN(string value)
{
    airConditionLogic->setWindSpeedFN(value);
}

/**
 *
 */
void AirconditionControl::setSleepModeFN(string value)
{
    airConditionLogic->setSleepModeFN(value);
}

/**
 * 设置模式
 */
void AirconditionControl::setModeFN(string value)
{
    airConditionLogic->setModeFN(value);
}

/**
 * 开/关机
 */
void AirconditionControl::setPowerFN(string value)
{
    airConditionLogic->setPowerFN(value);
}

/**
 * 设置温度
 */
void AirconditionControl::setTemperatureFN(string value)
{
    airConditionLogic->setTemperatureFN(value);
}

/**
 * 设置湿度
 */
void AirconditionControl::setHumidityFN(string value)
{
    airConditionLogic->setHumidityFN(value);
}

/**
 * 体感控制,体感室内温度,体感室内温度补偿
 */
void AirconditionControl::setSomatosensoryRealityTemperatureFN(string value)
{
    airConditionLogic->setSomatosensoryRealityTemperatureFN(value);
}

/**
 * 自动工作模式和除湿模式的温度补偿
 */
void AirconditionControl::setTemperatureCompensationFN(string value)
{
    airConditionLogic->setTemperatureCompensationFN(value);
}

/**
 * 华氏/摄氏温度显示设置
 */
void AirconditionControl::setTemperatureValueSwitchFN(string value)
{
    airConditionLogic->setTemperatureValueSwitchFN(value);
}

/**
 * 普通定时关机,普通定时关机时间
 */
void AirconditionControl::setGeneralTimingShutdownFN(string value)
{
    airConditionLogic->setGeneralTimingShutdownFN(value);
}

/**
 * 实时开机控制,实时时钟的小时值,实时时钟的分钟值,实时开机小时,实时开机分钟
 */
void AirconditionControl::setRealityTimeFN(string value)
{
    airConditionLogic->setRealityTimeFN(value);
}

/**
 * 上下风门模式,上下风开停控制
 */
void AirconditionControl::setVerticalWindFN(string value)
{
    airConditionLogic->setVerticalWindFN(value);
}

/**
 * 左右风开停控制,左风摆,右风摆
 */
void AirconditionControl::setHorizontalWindFN(string value)
{
    airConditionLogic->setHorizontalWindFN(value);
}

/**
 * 自然风开停
 */
void AirconditionControl::setNatureWindFN(string value)
{
    airConditionLogic->setNatureWindFN(value);
}

/**
 * 设置电加热
 */
void AirconditionControl::setElectricalHeatingFN(string value)
{
    airConditionLogic->setElectricalHeatingFN(value);
}

/**
 * 除湿模式
 */
void AirconditionControl::setDehumidificationModeFN(string value)
{
    airConditionLogic->setDehumidificationModeFN(value);
}

/**
 * 设置节能
 */
void AirconditionControl::setEnergyConservationFN(string value)
{
    airConditionLogic->setEnergyConservationFN(value);
}

/**
 * 设置并且节能
 */
void AirconditionControl::setShareFN(string value)
{
    airConditionLogic->setShareFN(value);
}

/**
 * 设置高效
 */
void AirconditionControl::setEfficientFN(string value)
{
    airConditionLogic->setEfficientFN(value);
}

/**
 * 设置双模
 */
void AirconditionControl::setDualModeFN(string value)
{
    airConditionLogic->setDualModeFN(value);
}

/**
 * 设置清新
 */
void AirconditionControl::setFreshnessFN(string value)
{
    airConditionLogic->setFreshnessFN(value);
}

/**
 * 设置换风
 */
void AirconditionControl::setFreshAirFN(string value)
{
    airConditionLogic->setFreshAirFN(value);
}

/**
 * 设置室内清洁
 */
void AirconditionControl::setClernIndoorFN(string value)
{
    airConditionLogic->setClernIndoorFN(value);
}

/**
 * 设置室外清洁
 */
void AirconditionControl::setClernOutdoorFN(string value)
{
    airConditionLogic->setClernOutdoorFN(value);
}

/**
 * 设置室智能眼
 */
void AirconditionControl::setSmartEyeFN(string value)
{
    airConditionLogic->setSmartEyeFN(value);
}

/**
 * 设置室静音
 */
void AirconditionControl::setMuteFN(string value)
{
    airConditionLogic->setMuteFN(value);
}

/**
 * 设置语音
 */
void AirconditionControl::setVoiceFN(string value)
{
    airConditionLogic->setVoiceFN(value);
}

/**
 * 设置除烟
 */
void AirconditionControl::setClernSmokeFN(string value)
{
    airConditionLogic->setClernSmokeFN(value);
}

/**
 * 背景灯
 */
void AirconditionControl::setBackgroundLampFN(string value)
{
    airConditionLogic->setBackgroundLampFN(value);
}

/**
 * 显示屏发光
 */
void AirconditionControl::setScreenFN(string value)
{
    airConditionLogic->setScreenFN(value);
}

/**
 * LED指示灯
 */
void AirconditionControl::setLEDFN(string value)
{
    airConditionLogic->setLEDFN(value);
}

/**
 * 室内外温度切换显示
 */
void AirconditionControl::setIndoorOutdoorSwitchFN(string value)
{
    airConditionLogic->setIndoorOutdoorSwitchFN(value);
}

/**
 * 室内过滤网清洁复位控制
 */
void AirconditionControl::setIndoorFilterClearFN(string value)
{
    airConditionLogic->setIndoorFilterClearFN(value);
}

