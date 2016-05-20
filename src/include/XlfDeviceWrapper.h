//
//  XlfDeviceWrapper.h
//  Devices
//
//  Created by 肖芳亮 on 16/2/24.
//  Copyright ? 2016年 XLF. All rights reserved.
//

#ifndef XlfDeviceWrapper_h
#define XlfDeviceWrapper_h

#include <stdio.h>
#include <iostream>

using namespace std;

class XlfDeviceWrapper
{
    
private:
    
    void* devicesControlManager;
    
    /**
     * 获取设备控制类
     */
    void* getDeviceControl(const string &deviceId);
    
    /**
     * 获取wifi控制类
     */
    void* getWifiControl(string deviceId);
    
public:
    /*
        * 某一ID的设备类型
        */
    int getDeviceType(const string &deviceId);

    XlfDeviceWrapper();
    
    /**
     * 初始化设备的控制类
     */
   bool initDevicesControl(const string &deviceId, int deviceType);
    
    /**
     * 删除设备的控制类
     */
    bool delDevicesControl(const string &deviceId);
    
    
    /**************************  deviceControl  **************************/
    /**
     * 通用开、关机
     */
    string setPowerCommon(string deviceId, int power, int soundSet);
    
    /**
     * 查询设备所有状态
     */
    string setQueryDeviceAllStatus(string deviceId, int soundSet);
    
    /**
     * 查询设备功能列表
     */
    string setQueryDeviceAllFunctions(string deviceId, int soundSet);
    
    /**
     * 查询设备型号信息
     */
    string setQueryDeviceModle(string deviceId, int soundSet);
    
    /**
     * 查询设备类型
     */
    string setQueryDeviceAddress(string deviceId, int soundSet);
    
    // 查询固件版本
    string sendQueryVersion(string deviceId);
    
    // 获取固件版本
    string getSoftVersion(string deviceId);
    
    /**
     * 解析设备标识
     */
    bool saveDeviceImformationCode(string deviceId, string resultText);
    
    /**
     * 更新设备所有状态
     */
    bool setDeviceAllStatus(string deviceId, string allStauts);
    
    /**
     * 更新设备功能列表
     */
    bool setDeviceFunction(string deviceId, string function);
    
    /**
     *  获取设备型号信息
     */
    string getDeviceModle(string deviceId);
    
    /**
     * 获取设备类型
     */
    string getDeviceAddress(string deviceId);
    
    /**
     * 获取控制类版本号
     */
    string getVersionNumberOfDevicesControl(string deviceId);
    
    /**
     * 获取协议库版本号
     */
    string getVersionNumberOfProtocolLibrary(string deviceId);
    
    /**
     * 获取获取wifi模块版本号
     */
    string getVersionNumberOfWifiModule(string deviceId);
    
    /**
     * 设置空调在线状态
     */
    void setOnlineStatus(string deviceId, bool status);
    
    /**
     * 获取空调在线状态 "0":不在线  "1":在线
     */
    string getOnlineStatus(string deviceId);
    
    /**
     * 获取空调的受控状态
     */
    string getSmartStatus(string deviceId);
    
    /**
     *  解析 F4F5指令  错误情况下返回""  状态解析返回 "KTZD:SUCCEED"  功能解析返回 "KTGN:SUCCEED"  控制解析返回 "KTSET:SUCCEED" 或者 "KTSET:ERROR"
     */
    string parseResult(const string &deviceId, const string &result);
    
    /**************************  airconditionControl  **************************/
    
    /**************************************** 控制 ****************************************/
    /**
     * 设置风量
     */
    string setAirconWindSpeed(string deviceId, string value,int manualOrnot);
    
    /**
     * 设置睡眠模式
     */
    string setAirconSleepMode(string deviceId, string sleepMode,int manualOrnot);
    
    /**
     * 设置模式
     */
    string setAirconMode(string deviceId, string Mode,int manualOrnot);
    
    /**
     * 设置开/关机
     */
    string setAirconPower(string deviceId, int on,int manualOrnot);
    
    /**
     * 设置KTSBOX
     */
    string setAirconKtSBox(string deviceId, int on,string Mode,string WindSpeed_value,int temperature,int IsMute,int manualOrnot);
    
    /**
     * 设置风向
     */
    string setAirconWindDirection(string deviceId, int on,int manualOrnot);
    
    /**
     * 设置温度
     */
    string setAirconTemperature(string deviceId, int temperature,int manualOrnot);
    
    /**
     * 设置湿度
     */
    string setAirconHumidity(string deviceId, int humidity,int manualOrnot);
    
    /**
     * 体感控制,体感室内温度,体感室内温度补偿
     */
    string setAirconSomatosensoryRealityTemperature(string deviceId, int on,int temperature,int compensation,int manualOrnot);
    
    /**
     * 自动工作模式和除湿模式的温度补偿
     */
    string setAirconTemperatureCompensation(string deviceId, int compensation,int manualOrnot);
    
    /**
     * 华氏/摄氏温度显示设置
     */
    string setAirconTemperatureValueSwitch(string deviceId, int Fahrenheit,int manualOrnot);
    
    /**
     * 普通定时关机,普通定时关机时间
     */
    string setAirconGeneralTimingShutdown(string deviceId, int on,string hour,int manualOrnot);
    
    /**
     * 实时时钟的小时值,实时时钟的分钟值
     */
    string setAirconRealityTime(string deviceId, string hour,string minute,int manualOrnot);
    
    /**
     * 实时开机控制,实时时钟的小时值,实时时钟的分钟值,实时开机小时,实时开机分钟
     */
    string setAirconRealityTimeBoot(string deviceId, int on,string Realityhour,string Realityminute, string boothour,string bootminute, string remainingHour,string remainingMinute, int manualOrnot);
    
    /**
     * 实时关机控制,实时时钟的小时值,实时时钟的分钟值,实时关机小时,实时关机分钟
     */
    string setAirconRealityTimeShutdown(string deviceId, int on,string Realityhour,string Realityminute, string shutdownhour,string shutdownminute, string remainingHour,string remainingMinute, int manualOrnot);
    
    /**
     * 设置除湿模式
     */
    string setAirconDehumidificationMode(string deviceId,string mode,int manualOrnot);
    
    /**
     * 上下风门模式,上下风开停控制
     */
    string setAirconVerticalWind(string deviceId, string mode,int on,int manualOrnot);
    
    /**
     * 左右风开停控制,左风摆,右风摆
     */
    string setAirconHorizontalWind(string deviceId, int on,int left,int right,int manualOrnot);
    
    /**
     * 自然风开停
     */
    string setAirconNatureWind(string deviceId, int on,int manualOrnot);
    
    /**
     * 设置电加热
     */
    string setAirconElectricalHeating(string deviceId, int on,int manualOrnot);
    
    /**
     * 设置节能
     */
    string setAirconEnergyConservation(string deviceId, int on,int manualOrnot);
    
    /**
     * 设置并用节电
     */
    string setAirconShare(string deviceId, int on,int manualOrnot);
    
    /**
     * 设置高效
     */
    string setAirconEfficient(string deviceId, int on,int manualOrnot);
    
    /**
     * 设置高效 OEM项目专用
     */
    string setAirconEfficientOem(string deviceId, int on,int manualOrnot);
    
    /**
     * 设置双模
     */
    string setAirconDualMode(string deviceId, int on,int manualOrnot);
    
    /**
     * 设置清新
     */
    string setAirconFreshness(string deviceId, int on,int manualOrnot);
    
    /**
     * 设置换风
     */
    string setAirconFreshAir(string deviceId, int on,int manualOrnot);
    
    /**
     * 设置室内清洁
     */
    string setAirconClernIndoor(string deviceId, int on,int manualOrnot);
    
    /**
     * 设置室外清洁
     */
    string setAirconClernOutdoor(string deviceId, int on,int manualOrnot);
    
    /**
     * 设置智慧眼
     */
    string setAirconAirconditionSmartEye(string deviceId,int on,int manualOrnot);
    
    /**
     * 设置室静音
     */
    string setAirconMute(string deviceId, int on,int manualOrnot);
    
    /**
     * 设置语音
     */
    string setAirconVoice(string deviceId, int on,int manualOrnot);
    
    /**
     * 设置除烟
     */
    string setAirconClernSmoke(string deviceId, int on,int manualOrnot);
    
    /**
     * 设置背景灯
     */
    string setAirconBackgroundLamp(string deviceId, int on,int manualOrnot);
    
    /**
     * 显示屏发光
     */
    string setAirconScreen(string deviceId, int on,int manualOrnot);
    
    /**
     * LED指示灯
     */
    string setAirconLED(string deviceId, int on,int manualOrnot);
    
    /**
     * 室内外温度切换显示
     */
    string setAirconIndoorOutdoorSwitch(string deviceId, int on,int manualOrnot);
    
    /**
     * 室内过滤网清洁复位控制
     */
    string setAirconIndoorFilterClear(string deviceId, int on,int manualOrnot);
    
    /**
     * 显示屏亮度值
     */
    string setAirconScreenLuminance(string deviceId, int light,int manualOrnot);
    
    /**
     * 直接设置开/关机
     */
    string setAirconDirctPower(string deviceId, int on,int manualOrnot);
    
    /**
     * 获取空调所有状态
     */
    string getAirconAllStatus(string deviceId, int manualOrnot);
    
    /**************************************** 状态 ****************************************/
    /**
     * 获取风量
     */
    string getAirconWindSpeed(string deviceId);
    
    /**
     * 获取睡眠
     */
    string getAirconSleepMode(string deviceId);
    
    /**
     * 获取xx
     */
    string getAirconSleep(string deviceId);
    
    /**
     * 获取模式
     */
    string getAirconMode(string deviceId);
    
    /**
     * 获取开机
     */
    string getAirconPower(string deviceId);
    
    /**
     * 获取风量
     */
    /*风向*/
    string getAirconWindDirection(string deviceId);
    
    /**
     * 获取设置温度
     */
    string getAirconSetingTemperature(string deviceId);
    
    /**
     * 获取湿度
     */
    string getAirconHumidity(string deviceId);
    
    /**
     * 获取体感室内温度
     */
    string getAirconSomatosensoryRealityTemperature(string deviceId);
    
    /**
     * 获取室内实际温度
     */
    string getAirconIndoorRealityTemperature(string deviceId);
    
    /**
     * 获取室内盘管温度
     */
    string getAirconIndoorPipeTemperature(string deviceId);
    
    /**
     * 获取室内实际湿度值
     */
    string getAirconIndoorRealityHumidity(string deviceId);
    
    /**
     * 获取体感室内温度补偿
     */
    string getAirconSomatosensoryCompensation(string deviceId);
    
    /**
     * 获取体感控制
     */
    string getAirconSomatosensoryContrl(string deviceId);
    
    /**
     * 获取自动工作模式和除湿模式的温度补偿
     */
    string getAirconTemperatureCompensation(string deviceId);
    
    /**
     * 获取华氏/摄氏温度显示设置
     */
    string getAirconTemperatureValueSwitch(string deviceId);
    
    /**
     * 获取普通定时开关机
     */
    string getAirconGeneralTimingShutdownValue(string deviceId);
    
    /**
     * 获取实时时钟的小时值
     */
    string getAirconRealityHour(string deviceId);
    
    /**
     * 获取实时时钟的分钟值
     */
    string getAirconRealityMinute(string deviceId);
    
    /**
     * 获取实时开机控制
     */
    string getAirconRealityBootContrl(string deviceId);
    
    /**
     * 获取实时开机小时
     */
    string getAirconRealityBootHour(string deviceId);
    
    /**
     * 获取实时开机分钟
     */
    string getAirconRealityBootMinute(string deviceId);
    
    /**
     * 获取实时关机控制
     */
    string getAirconRealityShutdownContrl(string deviceId);
    
    /**
     * 获取实时关机小时
     */
    string getAirconRealityShutdownHour(string deviceId);
    
    /**
     * 获取实时关机分钟
     */
    string getAirconRealityShutdownMinute(string deviceId);
    
    /**
     * 获取除湿模式
     */
    string getAirconDehumidificationMode(string deviceId);
    
    /**
     * 获取上下风门
     */
    string getAirconVerticalWindMode(string deviceId);
    
    /**
     * 获取上下风开停控制
     */
    string getAirconVerticalWindContrl(string deviceId);
    
    /**
     * 获取左右风开停控制
     */
    string getAirconHorizontalWindContrl(string deviceId);
    
    /**
     * 获取自然风开停控制
     */
    string getAirconNatureWindContrl(string deviceId);
    
    /**
     * 获取电热
     */
    string getAirconElectricalHeating(string deviceId);
    
    /**
     * 获取节能
     */
    string getAirconEnergyConservation(string deviceId);
    
    /**
     * 获取并用节电
     */
    string getAirconShare(string deviceId);
    
    /**
     * 获取高效
     */
    string getAirconEfficient(string deviceId);
    
    /**
     * 获取双模
     */
    string getAirconDualMode(string deviceId);
    
    /**
     * 获取清新
     */
    string getAirconFreshness(string deviceId);
    
    /**
     * 获取换风
     */
    string getAirconFreshAir(string deviceId);
    
    /**
     * 获取室内清洁
     */
    string getAirconClernIndoor(string deviceId);
    
    /**
     * 获取室外清洁
     */
    string getAirconClernOutdoor(string deviceId);
    
    /**
     * 获取智慧眼
     */
    string getAirconSmartEye(string deviceId);
    
    /**
     * 获取静音
     */
    string getAirconMute(string deviceId);
    
    /**
     * 获取语音
     */
    string getAirconVoice(string deviceId);
    
    /**
     * 获取除烟
     */
    string getAirconClernSmoke(string deviceId);
    
    /**
     * 获取背景灯
     */
    string getAirconBackgroundLamp(string deviceId);
    
    /**
     * 获取显示屏发光
     */
    string getAirconScreen(string deviceId);
    
    /**
     * 获取LED指示灯
     */
    string getAirconLED(string deviceId);
    
    /**
     * 获取室内外温度切换显示
     */
    string getAirconIndoorOutdoorSwitch(string deviceId);
    
    /**
     * 获取室内过滤网清洁复位控制
     */
    string getAirconIndoorFilterClear(string deviceId);
    
    /**
     * 获取左风摆
     */
    string getAirconLeftWind(string deviceId);
    
    /**
     * 获取右风摆
     */
    string getAirconRightWind(string deviceId);
    
    /**
     * 获取室内电量板
     */
    string getAirconChargeBorad (string deviceId);
    
    /**
     * 获取本次命令之前是否有过红外遥控与按键控制过
     */
    string getAirconHaveIRContrl(string deviceId);
    
    /**
     * 获取本次命令之前是否有过WIFI控制过
     */
    string getAirconHaveWIFIContrl(string deviceId);
    
    /**
     * 获取空调正常机型与测试机型
     */
    string getAirconModel(string deviceId);
    
    /**
     * 获取室内EEPROM在线升级
     */
    string getAirconEEPROMUpdate(string deviceId);
    
    /**
     * 获取室内温度传感器故障
     */
    string getAirconIndoorTemperatureSensorTrouble(string deviceId);
    
    /**
     * 获取室内盘管温度传感器故障
     */
    string getAirconIndoorPipeTemperatureSensorTrouble(string deviceId);
    
    /**
     * 获取室内湿度传感器故障
     */
    string getAirconIndoorHumiditySensorTrouble(string deviceId);
    
    /**
     * 获取室内排水泵故障
     */
    string getAirconIndoorDrainsWaterPumpTrouble(string deviceId);
    
    /**
     * 获取室内风机电机运转异常故障
     */
    string getAirconIndoorFanMotorTrouble(string deviceId);
    
    /**
     * 获取柜机格栅保护告警
     */
    string getAirconPioneerGrillingProtectTrouble(string deviceId);
    
    /**
     * 获取室内电压过零检测故障
     */
    string getAirconIndoorVoltageZeroCrossDetectionTrouble(string deviceId);
    
    /**
     * 获取室内外通信故障
     */
    string getAirconIndoorOutdoorCommunicationTrouble(string deviceId);
    
    /**
     * 获取室内控制板与显示板通信故障
     */
    string getAirconIndoorContrlScreenCommunicationTrouble(string deviceId);
    
    /**
     * 获取室内控制板与按键板通信故障
     */
    string getAirconIndoorContrlKeypadCommunicationTrouble(string deviceId);
    
    /**
     * 获取WIFI控制板与室内控制板通信故障
     */
    string getAirconIndoorContrlWIFICommunicationTrouble(string deviceId);
    
    /**
     * 获取室内控制板与室内电量板通信故障
     */
    string getAirconIndoorContrlChargeCommunicationTrouble(string deviceId);
    
    /**
     * 获取室内控制板EEPROM出错
     */
    string getAirconIndoorContrlEEPROMTrouble(string deviceId);
    
    /**
     * 获取运行频率
     */
    string getAirconRunFrequency(string deviceId);
    
    /**
     * 获取目标频率
     */
    string getAirconTargetFrequency(string deviceId);
    
    /**
     * 获取发给驱动器的频率
     */
    string getAirconDriveFrequency(string deviceId);
    
    /**
     * 获取环境温度
     */
    string getAirconEnvironmentTemperature(string deviceId);
    
    /**
     * 获取冷凝器温度
     */
    string getAirconCondenserTemperature(string deviceId);
    
    /**
     * 获取排气温度
     */
    string getAirconExhaustTemperature(string deviceId);
    
    /**
     * 获取目标排气温度
     */
    string getAirconTargetExhaustTemperature(string deviceId);
    
    /**
     * 获取室外电子膨胀阀开度
     */
    string getAirconOutdoorElectronicExpansion(string deviceId);
    
    /**
     * 获取UABH
     */
    string getAirconUABH(string deviceId);
    
    /**
     * 获取UABL
     */
    string getAirconUABL(string deviceId);
    
    /**
     * 获取UBCH
     */
    string getAirconUBCH(string deviceId);
    
    /**
     * 获取UBCL
     */
    string getAirconUBCL(string deviceId);
    
    /**
     * 获取UCAH
     */
    string getAirconUCAH(string deviceId);
    
    /**
     * 获取UCAL
     */
    string getAirconUCAL(string deviceId);
    
    /**
     * 获取IAB
     */
    string getAirconIAB(string deviceId);
    
    /**
     * 获取IBC
     */
    string getAirconIBC(string deviceId);
    
    /**
     * 获取ICA
     */
    string getAirconICA(string deviceId);
    
    /**
     * 获取IUV
     */
    string getAirconIUV(string deviceId);
    
    /**
     * 获取直流母线电压H
     */
    string getAirconCocurrentBusVoltageH(string deviceId);
    
    /**
     * 获取直流母线电压L
     */
    string getAirconCocurrentBusVoltageL(string deviceId);
    
    /**
     * 获取四通阀状态
     */
    string getAirconFourWayLimen(string deviceId);
    
    /**
     * 获取室外机实际工作状态
     */
    string getAirconOutdoorRealityRuning(string deviceId);
    
    /**
     * 获取风机运行状态
     */
    string getFanRuning();
    
    /**
     * 获取室外机强制室内机风门位置
     */
    string getAirconOutdoorForceIndoorWindPosition(string deviceId);
    
    /**
     * 获取室外机强制室内机风速
     */
    string getAirconOutdoorForceIndoorWindSpeed(string deviceId);
    
    /**
     * 获取室外机强制室内机停
     */
    string getAirconOutdoorForceIndoorStop(string deviceId);
    
    /**
     * 获取温控关机
     */
    string getAirconShutdownByTemperatureContrl(string deviceId);
    
    /**
     * 获取一拖多标志
     */
    string getAirconOne4All(string deviceId);
    
    /**
     * 获取除湿阀标志
     */
    string getAirconDehumidifierLimen(string deviceId);
    
    /**
     * 获取室外机化霜
     */
    string getAirconOutdoorDefrosting(string deviceId);
    
    /**
     * 获取室外旁通化霜
     */
    string getAirconOutdoorBypassDefrosting(string deviceId);
    
    /**
     * 获取回油标志
     */
    string getAirconOilReturn(string deviceId);
    
    /**
     * 获取室外故障显示标志
     */
    string getAirconOutdoorTroubleDisplay(string deviceId);
    
    /**
     * 获取室外机EEPROM在线下载标志
     */
    string getAirconOutdoorEEPROMDownload(string deviceId);
    
    /**
     * 获取室外机电量板
     */
    string getAirconOutdoorChargeBoard(string deviceId);
    
    /**
     * 获取压缩机电热带
     */
    string getAirconcompressorRibbonHeater(string deviceId);
    
    /**
     * 获取
     */
    /*压缩机预加热*/
    string getAirconcompressorBeforeHandheat(string deviceId);
    
    /**
     * 获取补气增晗
     */
    string getAirconReinflation(string deviceId);
    
    /**
     * 获取室内外机模式冲突
     */
    string getAirconOutdoorModeClash(string deviceId);
    
    /**
     * 获取室外EEPROM出错
     */
    string getAirconOutdoorEEPROMTrouble(string deviceId);
    
    /**
     * 获取室外盘管温度传感器故障
     */
    string getAirconOutdoorPipeTemperatureSensorTrouble(string deviceId);
    
    /**
     * 获取排气温度传感器故障
     */
    string getAirconOutdoorExhausTemperatureSensorTrouble(string deviceId);
    
    /**
     * 获取室外环境温度传感器故障
     */
    string getAirconOutdoorEnvironmentTemperatureSensorTrouble(string deviceId);
    
    /**
     * 获取电压变压器故障
     */
    string getAirconVoltageTransformerTrouble(string deviceId);
    
    /**
     * 获取电流互感器故障
     */
    string getAirconCurrentTransformerTrouble(string deviceId);
    
    /**
     * 获取室外控制与驱动通信故障
     */
    string getAirconOutdoorContrlDriveCommunicationTrouble(string deviceId);
    
    /**
     * 获取IPM模块过流保护
     */
    string getAirconIPMOvercurrentProtect(string deviceId);
    
    /**
     * 获取IPM模块过热保护
     */
    string getAirconIPMOverheatingProtect(string deviceId);
    
    /**
     * 获取交流电过电压保护
     */
    string getAirconAlternatingCurrentOvervoltageProtect(string deviceId);
    
    /**
     * 获取交流电欠电压保护
     */
    string getAirconAlternatingCurrentUndervoltageProtect(string deviceId);
    
    /**
     * 获取母线电压过电压保护
     */
    string getAirconBusbarVoltageOvervoltageProtect(string deviceId);
    
    /**
     * 获取
     */
    /*母线电压欠电压保护*/
    string getAirconBusbarVoltageUndervoltageProtect(string deviceId);
    
    /**
     * 获取PFC过电流保护
     */
    string getAirconPFCOvercurrentProtect(string deviceId);
    
    /**
     * 获取室外机最大电流保护
     */
    string getAirconOutdoorMaximumCurrentProtect(string deviceId);
    
    /**
     * 获取室外环境温度过低保护
     */
    string getAirconOutdooEnvironmentOvertemperatureProtect(string deviceId);
    
    /**
     * 获取排气温度过高保护
     */
    string getAirconExhaustOvertemperatureProtect(string deviceId);
    
    /**
     * 获取压缩机管壳温度保护
     */
    string getAirconCompressoPipeShellTemperatureProtect(string deviceId);
    
    /**
     * 获取室内防冻结或防过载保护
     */
    string getAirconIndoorAntiFreezingProtect(string deviceId);
    
    /**
     * 室外机PFC保护
     */
    string getAirconOutdoorPFCProtect(string deviceId);
    
    /**
     * 压缩机启动失败
     */
    string getAirconCompressoBootFail(string deviceId);
    
    /**
     * 获取压缩机失步
     */
    string getAirconCompressoStepOut(string deviceId);
    
    /**
     * 获取室外风机堵转
     */
    string getAirconOutdoorFanLockRotor(string deviceId);
    
    /**
     * 获取室外盘管防过载保护
     */
    string getAirconOutdoorPieOverloadProtect(string deviceId);
    
    /**
     * 获取冷媒泄漏
     */
    string getAirconRefrigerantLeakage(string deviceId);
    
    /**
     * 获取压缩机型号匹配错误
     */
    string getAirconCompressoModelMismatch(string deviceId);
    
    /**
     * 获取系统低频振动保护
     */
    string getAirconSystemLowFrequencyVibrationProtect(string deviceId);
    
    /**
     * 获取室外散热器温度过高保护
     */
    string getAirconOutdoorRadiatorOvertemperatureProtect(string deviceId);
    
    /**
     * 获取系统压力过高保护
     */
    string getAirconSystemHypertonusProtect(string deviceId);
    
    /**
     * 获取逆变器直流过电压故障
     */
    string getAirconInverterCocurrentOvervoltageTrouble(string deviceId);
    
    /**
     * 获取逆变器直流低电压故障
     */
    string getAirconInverterCocurrentUndervoltageTrouble(string deviceId);
    
    /**
     * 获取逆变器交流过电流故障
     */
    string getAirconInverterCocurrentOvercurrentTrouble(string deviceId);
    
    /**
     * 获取失步检出
     */
    string getAirconStepOutDetection(string deviceId);
    
    /**
     * 获取速度推定脉冲检出法检出欠相故障
     */
    string getAirconSpeedPulseFault(string deviceId);
    
    /**
     * 获取电流推定脉冲检出法检出欠相故障
     */
    string getAirconCurrentPulseFault(string deviceId);
    
    /**
     * 获取逆变器IPM故障-边沿
     */
    string getAirconInverterEdgeFault(string deviceId);
    
    /**
     * 获取逆变器IPM故障-电平
     */
    string getAirconInverterLevelFault(string deviceId);
    
    /**
     * 获取PFC_IPM故障-边沿
     */
    string getAirconPFC_IPMEdgeFault(string deviceId);
    
    /**
     * 获取PFC_IPM故障-电平
     */
    string getAirconPFC_IPMLevelFault(string deviceId);
    
    /**
     * 获取PFC停电检出故障
     */
    string getAirconPFCPowerCutFault(string deviceId);
    
    /**
     * 获取PFC过电流检出故障
     */
    string getAirconFCOvercurrentFault(string deviceId);
    
    /**
     * 获取直流电压检出异常
     */
    string getAirconDCVException(string deviceId);
    
    /**
     * 获取PFC低电压（有效值）检出故障
     */
    string getAirconPFCLowVoltageFault(string deviceId);
    
    /**
     * 获取AD偏置异常检出故障
     */
    string getAirconADOffsetAnomaliesFault(string deviceId);
    
    /**
     * 获取逆变器PWM逻辑设置故障
     */
    string getAirconInverterPWMLogicFault(string deviceId);
    
    /**
     * 获取逆变器PWM初始化故障
     */
    string getAirconInverterPWMInitFault(string deviceId);
    
    /**
     * 获取PFC_PWM逻辑设置故障
     */
    string getAirconPFCPWMLogicFault(string deviceId);
    
    /**
     * 获取PFC_PWM初始化故障
     */
    string getAirconPFC_PWMInitFault(string deviceId);
    
    /**
     * 获取温度异常
     */
    string getAirconTemperatureAnomaly(string deviceId);
    
    /**
     * 获取电流采样电阻不平衡调整故障
     */
    string getAirconCurrentSamplingFault(string deviceId);
    
    /**
     * 获取电机参数设置故障
     */
    string getAirconMotorDataFault(string deviceId);
    
    /**
     * 获取MCE故障
     */
    string getAirconMCEFault(string deviceId);
    
    /**
     * 获取驱动EEPROM故障
     */
    string getAirconEEPROMFault(string deviceId);
    
    /**
     * 获取室外盘管过载禁升频
     */
    string getAirconOutdoorCoilOverloadUpFrequency(string deviceId);
    
    /**
     * 获取室外盘管过载降频
     */
    string getAirconOutdoorCoilOverloadDownFrequency(string deviceId);
    
    /**
     * 获取室内盘管过载禁升频
     */
    string getAirconIndoorCoilOverloadUpFrequency(string deviceId);
    
    /**
     * 获取室内盘管过载降频
     */
    string getAirconIndoorCoilOverloadDownFrequency(string deviceId);
    
    /**
     * 获取压降排气过载禁升频
     */
    string getAirconPressureUpFrequency(string deviceId);
    
    /**
     * 获取压降排气过载降频
     */
    string getAirconPressureDownFrequency(string deviceId);
    
    /**
     * 获取室内盘管冻结禁升频
     */
    string getAirconIndoorCoilFreezingUpFrequency(string deviceId);
    
    /**
     * 获取室内盘管冻结降频
     */
    string getAirconIndoorCoilFreezingDownFrequency(string deviceId);
    
    /**
     * 获取室内外通信降频
     */
    string getAirconCommunicationDownFrequency(string deviceId);
    
    /**
     * 获取模块温度过载限频
     */
    string getAirconModuleTemperaturelimitFrequency(string deviceId);
    
    /**
     * 获取变调率限频
     */
    string getAirconModulationRatelimitFrequency(string deviceId);
    
    /**
     * 获取相电流限频
     */
    string getAirconPhaseCurrentlimitFrequency(string deviceId);
    
    /**
     * 获取并用节电保护禁升频
     */
    string getAirconPowerSaveUpFrequency(string deviceId);
    
    /**
     * 获取并用节电保护降频
     */
    string getAirconPowerSaveDownFrequency(string deviceId);
    
    /**
     * 获取过电流保护禁升频
     */
    string getAirconOvercurrentUpFrequency(string deviceId);
    
    /**
     * 获取过电流保护降频
     */
    string getAirconOvercurrentDownFrequency(string deviceId);
    
    /**
     * 获取室内风机转速xx
     */
    string getAirconIndoorFanSpeedH(string deviceId);
    
    /**
     * 获取室内风机转速00xx
     */
    string getAirconIndoorFanSpeed00L(string deviceId);
    
    /**
     * 获取有否PM2.5检测功能
     */
    string getAirconPM25(string deviceId);
    
    /**
     * 获取PM2.5污染程度
     */
    string getAirconPM25Level(string deviceId);
    
    /**
     * 获取空气PM2.5质量百分比表示
     */
    string getAirconPM25Percent(string deviceId);
    
    /**
     * 获取显示屏亮度值
     */
    string getAirconScreenLuminance(string deviceId);
    
    /**
     * 获取普通定时开关机有效
     */
    string getAirconGeneralTimingShutdown(string deviceId);
    
    
    /************************** function **************************/
    /**
     * 设置睡眠模式
     */
    int getAirconSleepModeFN(string deviceId);
    
    /**
     * 设置模式
     */
    int getAirconCoolModeFN(string deviceId);
    
    /**
     * 开/关机
     */
    int getAirconPowerFN(string deviceId);
    
    /**
     * 室内单个风向控制功能
     */
    int getAirconWindDirectionFN(string deviceId);
    
    /**
     * 设置温度
     */
    int getAirconTemperatureFN(string deviceId);
    
    /**
     * 设置湿度
     */
    int getAirconHumidityFN(string deviceId);
    
    /**
     * 体感控制,体感室内温度,体感室内温度补偿
     */
    int getAirconSomatosensoryRealityTemperatureFN(string deviceId);
    
    /**
     * 自动工作模式和除湿模式的温度补偿
     */
    int getAirconTemperatureCompensationFN(string deviceId);
    
    /**
     * 华氏/摄氏温度显示设置
     */
    int getAirconTemperatureValueSwitchFN(string deviceId);
    
    /**
     * 普通定时关机,普通定时关机时间
     */
    int getAirconGeneralTimingShutdownFN(string deviceId);
    
    /**
     * 实时开机控制,实时时钟的小时值,实时时钟的分钟值,实时开机小时,实时开机分钟
     */
    int getAirconRealityTimeFN(string deviceId);
    
    /**
     * 6位置可定室内风门位置控制
     */
    int getAirconVerticalWindModeNum(string deviceId);
    
    /**
     * 上下风门模式,上下风开停控制
     */
    int getAirconVerticalWindFN(string deviceId);
    
    /**
     * 左右风开停控制,左风摆,右风摆
     */
    int getAirconHorizontalWindFN(string deviceId);
    
    /**
     * 自然风开停
     */
    int getAirconNatureWindFN(string deviceId);
    
    /**
     * 设置电加热
     */
    int getAirconElectricalHeatingFN(string deviceId);
    
    /**
     * 除湿模式
     */
    int getAirconDehumidificationModeFN(string deviceId);
    
    /**
     * 设置节能
     */
    int getAirconEnergyConservationFN(string deviceId);
    
    /**
     * 设置并且节能
     */
    int getAirconShareFN(string deviceId);
    
    /**
     * 设置高效
     */
    int getAirconEfficientFN(string deviceId);
    
    /**
     * 设置双模
     */
    int getAirconDualModeFN(string deviceId);
    
    /**
     * 设置清新
     */
    int getAirconFreshnessFN(string deviceId);
    
    /**
     * 设置换风
     */
    int getAirconFreshAirFN(string deviceId);
    
    /**
     * 设置室内清洁
     */
    int getAirconClernIndoorFN(string deviceId);
    
    /**
     * 设置室外清洁
     */
    int getAirconClernOutdoorFN(string deviceId);
    
    /**
     * 设置室智能眼
     */
    int getAirconSmartEyeFN(string deviceId);
    
    /**
     * 设置室静音
     */
    int getAirconMuteFN(string deviceId);
    
    /**
     * 设置语音
     */
    int getAirconVoiceFN(string deviceId);
    
    /**
     * 设置除烟
     */
    int getAirconClernSmokeFN(string deviceId);
    
    /**
     * 背景灯
     */
    int getAirconBackgroundLampFN(string deviceId);
    
    /**
     * 显示屏发光
     */
    int getAirconScreenFN(string deviceId);
    
    /**
     * LED指示灯
     */
    int getAirconLEDFN(string deviceId);
    
    /**
     * 室内外温度切换显示
     */
    int getAirconIndoorOutdoorSwitchFN(string deviceId);
    
    /**
     * 室内过滤网清洁复位控制
     */
    int getAirconIndoorFilterClearFN(string deviceId);
    
    /**
     * 左风摆开停控制
     */
    int getAirconLeftFanContrlFN(string deviceId);
    
    /**
     * 右风摆开停控制
     */
    int getAirconRightFanContrlFN(string deviceId);
    
    /**
     * 控制规则
     */
    int getAirconContrlRate(string deviceId);
    
    /**************************  dehumidifierControl **************************/
    /**
     * 1.直接设置 开/关机
     * 取消普通定时,取消实时关机,取消快速冷热,取消睡眠,取消左右风,取消电热,取消节能,取消净化,取消双模,取消显示,取消亮度
     */
    string setDehumidifierDirctPower(string deviceId, int power, int manualOrnot);
    
    /**
     * 2.设置风速
     */
    string setDehumidifierWindSpeed(string deviceId, string speed, int manualOrnot);
    
    /**
     * 3.设置模式
     */
    string setDehumidifierMode(string deviceId, string mode, int manualOrnot);
    
    /**
     * 4.定时开关机
     */
    string setDehumidifierTimerControl(string deviceId, int enable, string time, int manualOrnot);
    
    /**
     * 5.设置湿度
     */
    string setDehumidifierHumidity(string deviceId, int humidity, int manualOrnot);
    
    /**
     * 6.设置温度
     */
    string setDehumidifierTemperature(string deviceId, int temperature, int manualOrnot);
    
    /**
     * 7.设置开关电源
     */
    string setDehumidifierPower(string deviceId, int power, int manualOrnot);
    
    /**
     * 8.设置开关电加热
     */
    string setDehumidifierEletricHeatControl(string deviceId, int isEletricHeatOn, int manualOrnot);
    
    /**
     * 9.设置开关水泵
     */
    string setDehumidifierWaterPumpControl(string deviceId, int enable, int manualOrnot);
    
    /**
     * 10.设置开关负离子
     */
    string setDehumidifierNegativeIonsControl(string deviceId, int enable, int manualOrnot);
    
    /**
     * 11.设置CSSBox
     */
    string setDehumidifierCSSBox(string deviceId, int on,string Mode,string WindSpeed_value,int humidity,int manualOrnot);
    
    /**
     * 智慧风
     */
    int getDehumidifierSmartWindFN(string deviceId);
    
    /**
     * 高风
     */
    int getDehumidifierHighWindFN(string deviceId);
    
    /**
     * 中风
     */
    int getDehumidifierMediumWindFN(string deviceId);
    
    /**
     * 低风
     */
    int getDehumidifierLowWindFN(string deviceId);
    
    /**
     * 运行模式 持续运行
     */
    int getDehumidifierContinueModeFN(string deviceId);
    
    /**
     * 运行模式 正常运行
     */
    int getDehumidifierNormalModeFN(string deviceId);
    
    /**
     * 运行模式 自动运行
     */
    int getDehumidifierAutoModeFN(string deviceId);
    
    /**
     * 定时
     */
    int getDehumidifierTimerControlFN(string deviceId);
    
    /**
     * 电加热
     */
    int getDehumidifierElectricHeatFN(string deviceId);
    
    /**
     * 电加热 温度
     */
    int getDehumidifierElectricHeatSetTemperatureFN(string deviceId);
    
    /**
     * 室内湿度
     */
    int getDehumidifierIndoorHumidityFN(string deviceId);
    
    /**
     * 水泵
     */
    int getDehumidifierWaterPumpFN(string deviceId);
    
    /**
     * 负离子
     */
    int getDehumidifierAnionFN(string deviceId);
    
    /**
     * 电量检测
     */
    int getDehumidifierElectronicDetectFN(string deviceId);
    
    /**
     * 开停机
     */
    int getDehumidifierPowerFN(string deviceId);
    
    /**
     * EEPROM可改写功能
     */
    int getDehumidifierEEPROMWriteFN(string deviceId);
    
    /**
     * 101#-0#第 7 字节预留位的控制功能
     */
    int getDehumidifier7ReserverdFN(string deviceId);
    
    /**
     * 101#-0#第 8 字节预留位的控制功能
     */
    int getDehumidifier8ReserverdFN(string deviceId);
    
    /**
     * 获取风速
     */
    string getDehumidifierWindSpeedStatus(string deviceId);
    
    /**
     * 获取模式
     */
    string getDehumidifierModeStatus(string deviceId);
    
    /**
     * 获取定时开关机控制
     */
    string getDehumidifierTimeStatus(string deviceId);
    
    /**
     * 获取定时开关机时间
     */
    string getDehumidifierTimerValue(string deviceId);
    
    /**
     * 获取设置湿度
     */
    string getDehumidifierSettingHumidityValue(string deviceId);
    
    /**
     * 获取电加热设定温度
     */
    string getDehumidifierEletricHeatingTempratureStatus(string deviceId);
    
    /**
     * 获取室内温度
     */
    string getDehumidifierIndoorTempStatus(string deviceId);
    
    /**
     * 获取除湿机电源开关状态
     */
    string getDehumidifierPower(string deviceId);
    
    /**
     * 获取电加热功能开关状态
     */
    string getDehumidifierEletricHeatingStatus(string deviceId);
    
    /**
     * 获取水泵开关状态
     */
    string getDehumidifierWaterPumpStatus(string deviceId);
    
    /**
     * 获取负离子开关状态
     */
    string getDehumidifierAnionStatus(string deviceId);
    
    /**
     * 本次命令之前有否红外和按键控制过
     */
    string getDehumidifierInfrarediKeypadControl(string deviceId);
    
    /**
     * 本次命令之前有否 WIFI 控制过
     */
    string getDehumidifierIsWifiControl(string deviceId);
    
    /**
     * 过滤网清洁告警
     */
    string getDehumidifierFilterNetCleanWarning(string deviceId);
    
    /**
     * 湿度传感器故障
     */
    string getDehumidifierHumidSensorError(string deviceId);
    
    /**
     *  管温传感器故障
     */
    string getDehumidifierPumpTempratureError(string deviceId);
    
    /**
     * 室内温度传感器故障
     */
    string getDehumidifierIndoorTempratureError(string deviceId);
    
    /**
     * 水满警告
     */
    string getDehumidifierWaterFullWarning(string deviceId);
    
    /**
     * 水泵故障
     */
    string getDehumidifierWaterPumpWarning(string deviceId);
    
    /**
     * 获取实际湿度
     */
    string getDehumidifierRealHumidityValue(string deviceId);
    
    /**************************  aircleaner  *************************/
    /************************************ 设备控制 **************************************/
    //1设置净化速度
    string setAircleanerWindSpeed(string deviceId, string speed, bool manualOrnot);
    
    //2设置模式
    string setAircleanerMode(string deviceId, string mode, bool manualOrnot);
    
    //定时开关机
    string setAircleanerTimerControl(string deviceId, bool enable, string time, bool manualOrnot);
    
    // 开关清新机电源
    string setAircleanerpower(string deviceId, bool power, bool manualOrnot);
    
    // 开关儿童锁
    string setAircleanerChildLock(string deviceId, bool power, bool manualOrnot);
    
    // 开关水离子
    string setAircleanerWaterIon(string deviceId, bool power, bool manualOrnot);
    
    // 开关加湿功能
    string setAircleanerHumidification(string deviceId, bool power, bool manualOrnot);
    
    // 加湿器湿度设置
    string setAircleanerHumidificationValue(string deviceId, int humidity_value, bool manualOrnot);
    
    // 盒子控制
    string setAircleanerSBox(string deviceId, bool power_on,string Mode,string WindSpeed_value,bool jsj_on,string humdity_value,bool manualOrnot);
    
    /************************************ 获取设备的各个状态 **************************************/
    // 0净化速度
    string getAircleanerSpeedStatus(string deviceId);
    
    // 1净化模式,
    string getAircleanerModeStatus(string deviceId);
    
    //2定时开关机控制,
    string getAircleanerTimeStatus(string deviceId);
    
    //3定时开关机时间,
    string getAircleanerTimerValue(string deviceId);
    
    //4风机转速,
    string getAircleanerMotorSpeed(string deviceId);
    
    // 5空气质量,
    string getAircleanerAirQuality(string deviceId);
    
    // 6空气质量百分比,
    string getAircleanerAirQualityPercent(string deviceId);
    
    // 7相对湿度,
    string getAircleanerRelativeHumidityValue(string deviceId);
    
    //8开停净化机,
    string getAircleanerPowerStatus(string deviceId);
    
    // 9儿童锁开关控制,
    string getAircleanerChildLockStatus(string deviceId);
    
    // 10水离子开停控制,
    string getAircleanerWaterionStatus(string deviceId);
    
    // 11加湿机开停控制,
    string getAircleanerHumidityStatus(string deviceId);
    
    // 12过滤网更换提示,
    string getAircleanerChangeFilter(string deviceId);
    
    // 13本次命令之前有否红外和按键控制过,
    string getAircleanerinfraredAndButtonBeforeCommand1(string deviceId);
    
    // 14本次命令之前有否红外和按键控制过,
    string getAircleanerinfraredAndButtonBeforeCommand2(string deviceId);
    
    // 15加湿转轮不动,
    string getAircleanerHumidityWheelError(string deviceId);
    
    // 16水箱空,
    string getAircleanerWaterSinkEmptyError(string deviceId);
    
    // 17水箱未装好,
    string getAircleanerWaterSinkNotSetup(string deviceId);
    
    // 18湿度传感器故障,
    string getAircleanerHumiditySensorError(string deviceId);
    // 19风机故障,
    string getAircleanerMotorError(string deviceId);
    
    // 20风尘传感器故障,
    string getAircleanerDustSensorError(string deviceId);
    
    // 21气味传感器故障，
    string getAircleanerSmellSensorError(string deviceId);
    
    //22机器倾斜故障
    string getAircleanerLeanError(string deviceId);
    
    //23湿度设置值
    string getAircleanerSettingHumid(string deviceId);
    
    /********************************** 获取功能使能状态 ****************************************/
    // 1净化速度状态-自动功能，
    int getAircleanerCleanSpeedAutoFN(string deviceId);
    
    // 2净化速度状态-净烟功能
    int getAircleanerCleanSpeedDelSmokeFN(string deviceId);
    
    // 3净化速度状态-高风功能
    int getAircleanerCleanSpeedHighFN(string deviceId);
    
    // 4净化速度状态-中风功能，
    int getAircleanerCleanSpeedMiddleFN(string deviceId);
    
    // 5净化速度状态-低风功能，
    int getAircleanerCleanSpeedLowFN(string deviceId);
    
    // 6净化模式状态-睡眠功能，
    int getAircleanerCleanModeSleepFN(string deviceId);
    
    // 7净化模式状态-静音功能，
    int getAircleanerCleanModeMuteFN(string deviceId);
    
    // 8净化模式状态-智能功能，
    int getAircleanerCleanModeSmartFN(string deviceId);
    
    // 9净化模式状态-除味功能，
    int getAircleanerCleanModeDelTasteFN(string deviceId);
    
    // 10净化模式状态-除烟功能，
    int getAircleanerCleanModeDelSmokeFN(string deviceId);
    
    // 11普通定时功能，
    int getAircleanerGeneralTimingFN(string deviceId);
    
    // 12儿童锁功能，
    int getAircleanerChildLockFN(string deviceId);
    
    // 13水离子开停，
    int getAircleanerWaterIonFN(string deviceId);
    
    // 14加湿机开停功能，
    int getAircleanerDehumidifierFN(string deviceId);
    
    // 15净化机开停功能
    int getAircleanerCleanMachineFN(string deviceId);
    
    // 16 EEPROM可改写功能,
    int getAircleanerEEpromReadWriteFN(string deviceId);
    
    // 17电量检测功能,
    int getAircleanerPowerDetectFN(string deviceId);
    
    // 101#-0#第5字节预留位的控制功能
    int getAircleaner5ReserverdFN(string deviceId);
    
    // 101#-0#第6字节预留位的控制功能
    int getAircleaner6ReserverdFN(string deviceId);
    
    /**************************  airFanControl  **************************/
    /**
     * 设置新风机风速
     */
    string setAirfanWindSpeed(string deviceId, string speed, int soundSet);
    
    /**
     * 设置新风机开关机状态
     */
    string setAirfanPower(string deviceId, int power, int soundSet);
    
    /**
     * 设置新风机模式
     */
    string setAirfanMode(string deviceId, string mode, int soundSet);
    
    /**
     * 设置新风机普通定时
     */
    string setAirfanTimingSwitchMachine(string deviceId, string hour, int isOpen, int soundSet);
    
    /**
     * 未知功能
     */
    string getStatus(string deviceId, int soundSet);
    
    /**
     * 设置盒子控制
     */
    string setAirfanHotFanSBox(string deviceId, int on,string  Mode,string  WindSpeed_value, int soundSet);
    
    /**
     * 获取新风机操作结果
     */
    string getAirfanResult(string deviceId);
    
    /**
     * 获取新风机风速
     */
    string getAirfanWindSpeed(string deviceId);
    
    /**
     * 获取新风机开关机状态
     */
    string getAirfanPower(string deviceId);
    
    /**
     * 获取新风机待机状态
     */
    string getAirfanSuspendMode(string deviceId);
    
    /**
     * 获取新风机模式
     */
    string getAirfanMode(string deviceId);
    
    /**
     * 获取新风机定时状态
     */
    string getAirfanIsTiming(string deviceId);
    
    /**
     * 获取新风机定时时间
     */
    string getAirfanTimingTime(string deviceId);
    
    /**
     * 获取新风机外部风扇转速
     */
    string getAirfanOuterFanSpeed(string deviceId);
    
    /**
     * 获取新风机内部风扇转速
     */
    string getAirfanInnerFanSpeed(string deviceId);
    
    /**
     * 获取新风机内部有效温度
     */
    string getAirfanInnerTempratureValid(string deviceId);
    
    /**
     * 获取新风机内部有效湿度
     */
    string getAirfanInnerHumidityValid(string deviceId);
    
    /**
     *  获取室内二氧化碳有效值
     */
    string getAirfanInnerco2DensityValid(string deviceId);
    
    /**
     * 获取新风机外部有效温度
     */
    string getAirfanOuterTempratureValid(string deviceId);
    
    /**
     * 获取新风机外部有效湿度
     */
    string getAirfanOuterHumidityValid(string deviceId);
    
    /**
     * 获取新风机室内温度
     */
    string getAirfanTemperatureIndoor(string deviceId);
    
    /**
     * 获取新风机室内湿度
     */
    string getAirfanHumidityIndoor(string deviceId);
    
    /**
     * 获取新风机室外温度
     */
    string getAirfanTemperatureOutdoor(string deviceId);
    
    /**
     * 获取新风机室外湿度
     */
    string getAirfanHumidityOutdoor(string deviceId);
    
    /**
     * 获取新风机室内二氧化碳浓度
     */
    string getAirfanCO2Indoor(string deviceId);
    
    /**
     * 获取新风机滤网复位状态
     */
    string getAirfanFilterIfReplace(string deviceId);
    
    /**
     * 获取新风机室外风扇故障
     */
    string getAirfanOuterFanIfFault(string deviceId);
    
    /**
     * 获取新风机室内风扇故障
     */
    string getAirfanInnerFanIfFault(string deviceId);
    
    /**
     * 获取新风机室外温度传感器故障
     */
    string getAirfanOuterTemperatureSensorIfFault(string deviceId);
    
    /**
     * 获取新风机室外湿度传感器故障
     */
    string getAirfanOuterHumiditySensorIfFault(string deviceId);
    
    /**
     * 获取新风机二氧化碳传感器故障
     */
    string getAirfanCo2SensorIfFault(string deviceId);
    
    /**
     * 获取新风机室内温度传感器故障
     */
    string getAirfanInnerTemperatureSensorFault(string deviceId);
    
    /**
     * 获取新风机室内湿度传感器故障
     */
    string getAirfanInnerHumiditySensorFault(string deviceId);
    
    /**
     * 获取新风机风量支持档位数使能
     */
    int getAirfanSpeedSupportNumberFN(string deviceId);
    
    /**
     * 获取新风机全热换气模式使能
     */
    int getAirfanfullheatModeFN(string deviceId);
    
    /**
     * 获取新风机直通换气模式使能
     */
    int getAirfanDirectModeFN(string deviceId);
    
    /**
     * 获取新风机室内回旋模式使能
     */
    int getAirfanIndoorModeFN(string deviceId);
    
    /**
     * 获取新风机普通定时模式使能
     */
    int getAirfanTiming(string deviceId);
    
    /**
     * 获取新风机开关机控制位使能
     */
    int getAirfanPowerFN(string deviceId);
    
    /**
     * 获取新风机是否升级EEPROM
     */
    int getAirfanIfUpdateEEPROM(string deviceId);
    
    /**
     * 获取新风机电量检测使能
     */
    int getAirfanBatteryIFdetection(string deviceId);
    
    /********************************* 设备控制 *********************************/
    /**
     * 开关机
     * @param set
     */
    string setSeedMachinePower(string deviceId, int set);
    
    /**
     *
     * @param curhour 当前时间小时（0~23）
     * @param curmin  当前时间分钟 （0~59）
     * @param set	  1 设置定时功能，0，取消设置定时功能
     * @param onOroff 哪种定时，1 为开灯定时，0这关灯定时
     * @param hour	  定时小时（0~23）
     * @param min	 定时分钟（0~59）
     * @param lights  which layer lights to be set. Just like set parameter in function setLight()
     */
    string setSeedMachineLightTimer(string deviceId, int curhour,int curmin,int set,int onOroff,int hour,int min,int lights);
    
    /**
     * 关闭报警
     * @param level 水位报警,pump 水泵报警，nutrition 营养液报警
     */
    string setSeedMachineDismissWarning(string deviceId, int level, int pump,int nutrition);
    
    /**
     * 设置灯开关：
     * 1 开灯，0 关灯
     */
    string setSeedMachineLight(string deviceId, int set);
    
    
    /**
     * 设置负离子开关：
     * 1 开，0 关
     */
    string setSeedMachineAnion(string deviceId, int set);
    
    /**
     * 设置音乐开关：
     * 1 开，0 关
     */
    string setSeedMachineMusic(string deviceId, int set);
    
    /**
     * 音量控制
     * @param volume 1：音量+; 0：音量减
     */
    string setSeedMachineVolume(string deviceId, int volume);
    
    /**
     * 设置PM2.5开关：如果有外接传感器的情况下才有此功能hasExtralSensor()方法可获得
     * 1 开，0 关
     */
    string setSeedMachinePm25(string deviceId, int set);
    
    /*************************** 获取设备状态接口 *************************/
    /**
     * 当前开关机状态
     */
    string getSeedMachinePowerStat(string deviceId);
    
    /**
     * 当前音乐状态
     */
    string getSeedMachineMusicStat(string deviceId);
    
    /**
     * 当前负离子状态
     */
    string getSeedMachineAnionStat(string deviceId);
    
    /**
     * 当前灯状态
     */
    string getSeedMachineLightStat(string deviceId);
    
    /**
     * 当前温度
     */
    string getSeedMachineCurTemp(string deviceId);
    
    /**
     * 当前湿度
     */
    string getSeedMachineCurHumi(string deviceId);
    
    /**
     * 是否有外接传感器
     */
    string getSeedMachineHasExtralSensor(string deviceId);
    
    /**
     * 获得外接温度值，只在外接传感器存在时有效
     */
    string getSeedMachineExtralTemp(string deviceId);
    
    /**
     * 获得外接湿度值，只在外接传感器存在时有效
     */
    string getSeedMachineExtralHumi(string deviceId);
    
    /**
     * 获得外接Pm2.5值，只在外接传感器存在时有效，单位ug/m3
     */
    string getSeedMachineExtralPm2_5(string deviceId);
    
    /**
     * 是否有灯报警
     */
    string getSeedMachineLightWarn(string deviceId);
    
    /**
     * 当前是第几层灯报警
     */
    string getSeedMachinLlightWarnInfo(string deviceId);
    
    /**
     * 是否有水位报警
     */
    string getSeedMachineWaterLevelWarn(string deviceId);
    
    /**
     * 是否有水泵报警
     */
    string getSeedMachinePumpWarn(string deviceId);
    
    /**
     * 营养液报警
     */
    string getSeedMachineNutritionWarn(string deviceId);
    
    /*************************************** sensor *************************************************/
    /************************** 控制 **************************/
    /** PM2.5开关设置 设置功能：power[1] */
    string setSensorPM2_5Power(string deviceId, int power);
    
    /** 传感器电源控制 切断 上电 电源控制：power[0/1] 传感器ID: [1 温度、2湿度、3 甲醛、4 PM2.5] */
    string  setSensorsPower(string deviceId, int power, int sensorID);
    
    /**
     * 主动上报频率设置 是否设置上报频率：responseFrequencyValid[0/1] 传感器ID responseID : [1 温度、2湿度、3 甲醛、4 PM2.5] 上报频率(单位
     * 秒)：responseFrequency
     */
    string  setSensorResponseFrequency(string deviceId ,int responseFrequencyValid, int responseID, int responseFrequency);
    
    /************************** 状态查询 **************************/
    /** 获取 温度传感器ID */
    string getSensorTemperatureSensorID(string deviceId);
    
    /** 获取 温度值是否有效 */
    string getSensorTemperatureValueValid(string deviceId);
    
    /** 获取 温度传感器电源状态 */
    string getSensorTemperatureSensorPowerStatus(string deviceId);
    
    /** 获取 上次读温度值时间 */
    string getSensorTemperatureInterval(string deviceId);
    
    /** 获取 温度值 */
    string getSensorTemperatureValue(string deviceId);
    
    /** 获取 湿度传感器ID */
    string getSensorHumiditySensorID(string deviceId);
    
    /** 获取 湿度值是否有效 */
    string getSensorHumidityValueValid(string deviceId);
    
    /** 获取 湿度传感器电源状态 */
    string getSensorHumiditySensorPowerStatus(string deviceId);
    
    /** 获取 上次读湿度值时间 */
    string getSensorHumidityInterval(string deviceId);
    
    /** 获取 湿度值 */
    string getSensorHumidityValue(string deviceId);
    
    /** 获取 甲醛传感器ID */
    string getSensorH2COSensorID(string deviceId);
    
    /** 获取 甲醛值是否有效 */
    string getSensorH2COValueValid(string deviceId);
    
    /** 获取 甲醛传感器电源状态 */
    string getSensorH2COSensorPowerStatus(string deviceId);
    
    /** 获取 上次读甲醛值时间 */
    string getSensorH2COInterval(string deviceId);
    
    /** 获取 甲醛值 */
    string getSensorH2COValue(string deviceId);
    
    /** 获取 PM2.5传感器ID */
    string getSensorPM2_5SensorID(string deviceId);
    
    /** 获取 PM2.5值是否有效 */
    string getSensorPM2_5ValueValid(string deviceId);
    
    /** 获取 PM2.5传感器电源状态 */
    string getSensorPM2_5SensorPowerStatus(string deviceId);
    
    /** 获取 上次读PM2.5值时间 */
    string getSensorPM2_5Interval(string deviceId);
    
    /** 获取 PM2.5值 */
    string getSensorPM2_5Value(string deviceId);
    
    /** 获取 CO2传感器ID */
    string getSensorCO2SensorID(string deviceId);
    
    /** 获取 CO2值是否有效 */
    string getSensorCO2ValueValid(string deviceId);
    
    /** 获取 CO2传感器电源状态 */
    string getSensorCO2SensorPowerStatus(string deviceId);
    
    /** 获取 上次读CO2值时间 */
    string getSensorCO2Interval(string deviceId);
    
    /** 获取 CO2值 */
    string getSensorCO2Value(string deviceId);
    
    /** 获取 转换板通信错误 */
    string getSensorIsPeripheralsCommunicationError(string deviceId);
    
    /*********************************** Smartlight *******************************************/
    /********************* 控制 *********************/
    /** 电源设置 此方法未实现 */
    string setSmartlightPower(string deviceId, int power);
    
    /** 亮度设置：0~100 */
    string setSmartlightBrightness(string deviceId, int brightnessValue);
    
    /** R G B 三元色设置 取值范围均为[0-255] */
    string setSmartlightRGB(string deviceId, int redValue, int greenValue, int blueValue);
    
    /** 空气状况 3 优、2 良、1 一般 */
    string setSmartlightAirQualityLevel(string deviceId, int airQualityLevel);
    
    /** 色温设置(0~65535) 此方法未实现 */
    string setSmartlightColorTemperature(string deviceId, int colorTemperatureValue);
    
    // 新增 2015.11.12
    /**
     * 设备状态 0 为正常，1 为掉线
     * @param deviceStatus 0 为正常，1 为掉线
     * @return byte[]
     */
    string setSmartlightDeviceStatus(string deviceId, int deviceStatus);
    
    /******************** 状态查询 *************************/
    /** 开关状态 此方法未实现 */
    string getSmartlightPower(string deviceId);
    
    /** RGB 值是否有效 */
    string getSmartlightRGBSetValid(string deviceId);
    
    /** 红色值 */
    string getSmartlightRedValue(string deviceId);
    
    /** 绿色值 */
    string getSmartlightGreenValue(string deviceId);
    
    /** 蓝色值 */
    string getSmartlightBlueValue(string deviceId);
    
    /** 色温值是否有效 此方法未实现 */
    string getSmartlightColorTemperatureValid(string deviceId);
    
    /** 色温值(0~65535) 此方法未实现 */
    string getSmartlightColorTemperatureValue(string deviceId);
    
    /** 亮度值是否有效 */
    string getSmartlightBrightnessValid(string deviceId);
    
    /** 亮度 */
    string getSmartlightBrightnessValue(string deviceId);
    
    // 新增状态查询 2015.11.12
    /**
     * 设备状态 0 为有效，1 为无效
     * @return  0 为有效，1 为无效
     */
    string getSmartlightDeviceStatusValid(string deviceId);
    
    /**
     * 设备状态 0 为正常，1 为掉线
     * @return 0 为正常，1 为掉线
     */
    string getSmartlightDeviceStatus(string deviceId);
    
    /**
     * 空气状况是否有效 0 为有效，1 为无效
     * @return 0 为有效，1 为无效
     */
    string getSmartlightAirStatusValid(string deviceId);
    
    /**
     * 空气状况 3 优、2 良、1 一般
     * @return  3 优、2 良、1 一般
     */
    string getSmartlightAirStatus(string deviceId);
    
    /**
     * 转换板通信错误
     * @return 0为正常，1为通信错误
     */
    string getSmartlightIsPeripheralsCommunicationError(string deviceId);
    
    /************************ SmartCurtain ***********************/
    /** 模式：Mode : 设置功能:0打开、1 关闭、2停止、3 重启 */
    string setSmartCurtainMode(string deviceId, int mode);
    
    /** 定点控制：Pos : 设置功能:设置的定点位置(0~16)，全开位置是0，中间闭合位置是16，每次设置位置间隔距离应大于等于4个单位 */
    string setSmartCurtainPosition(string deviceId,int position);
    
    /** Open or Close state 参数是否有效 */
    string getSmartCurtainPowerStatusParameterIsValid(string deviceId);
    
    /** Open or Close state 开关状态 */
    string getSmartCurtainPowerStatus(string deviceId);
    
    /** 点位置 参数是否有效 */
    string getSmartCurtainPositionParameterIsValid(string deviceId);
    
    /** 当前的定点位置 */
    string getSmartCurtainPositionStatus(string deviceId);
    
    /**
     * 转换板通信错误
     * @return 0为正常，1为通信错误
     */
    string getSmartCurtainIsPeripheralsCommunicationError(string deviceId);
    
    
    /*********************************** Voltameter *******************************************/
    /** 总的电源开关 */
    string setVoltameterPower(string deviceId, int power);
    
    /** 电量统计清0 1清零，0不清零 */
    string setVoltameterResetCount(string deviceId, int isResetCount);
    
    /** 总电源开关状态 */
    string getVoltameterPower(string deviceId);
    
    /** 电流值uA */
    string getVoltameterCurrentValue(string deviceId);
    
    /** 电压值mV */
    string getVoltameterVoltageValue(string deviceId);
    
    /** 电量值的统计 */
    string getVoltameterValue(string deviceId);
    
    /** 转换板通信错误 */
    string getVoltameterIsPeripheralsCommunicationError(string deviceId);
    
    
    /*********************************** Oven *******************************************/
    /****************** set ******************/
    // 烤箱开机
    string setOvenPowerOn(string deivceId, bool isPowerOn, bool manualOrnot,int flag);
    
    // 烤箱关机
    string setOvenPowerOff(string deivceId, bool isPowerOn, bool manualOrnot,int flag);
    
    // 风机开关
    string setOvenFS(string deivceId, long uid, bool isOpen, bool manualOrnot,int flag);
    
    // 转叉开关
    string setOvenZC(string deivceId, long uid, bool isOpen, bool manualOrnot,int flag);
    
    // 炉灯开关
    string setOvenD(string deivceId, long uid, bool isOpen,bool manualOrnot,int flag);
    
    // 上下管温度设置
    string setOvenUDTubeTemperature(string deivceId, long uid, int temperatureU, int temperatureM, int temperatureD ,bool manualOrnot,int flag);
    
    // 状态查询
    string getOvenStatus(string deivceId, bool manualOrnot,int flag);
    
    // 功能查询
    string getOvenGN(string deivceId, bool manualOrnot,int flag);
    
    // 设置菜单名字
    string setOvenMenuName(string deivceId, long uid, int menuNub, int sub_node, int time, string name, bool manualOrnot,int flag);
    
    /**
     * 1.9	设置菜单温度命令扩展	新增		不确定AT指令顺序是否正确
     *
     * 参数： 菜谱编号[0/1/2]，子节点[0-9]，时间-高位[0~0x46]，时间-低位[0~254]，
     * 上管温度-高位[暂时为 0], 上管温度-低位[40~230]， 下管温度-高位[暂时为 0], 下管温度-低位[40~230]，
     * 转叉开关[0/1],风机开关[0/1],提醒暂停[0/1], 时间有效设置位[0/1] ，
     * 上管温度有效设置位[0/1] ，下管温度有效设置位[0/1] ，转叉开关有效设置位[0/1]，
     * 风机开关有效设置位[0/1]，提醒暂停有效设置位[0/1]，提示声[0/1]，帧序号[0-254]
     * */
    string setOvenMenuTemperatureExtend(string deivceId, long uid, int menuNub, int sub_node, int time, int temperatureU, int temperatureM, int temperatureD, bool rotary_fork, bool fan_power, bool remind_suspend, bool time_effective, bool upper_tube_temperature_effective, bool middle_tube_temperature_effective, bool lower_tube_temperature_effective, bool rotary_fork_effective, bool fan_power_effective, bool remind_suspend_effective, int a_x, bool manualOrnot,int flag);
    
    /**
     * 	曲线完整性检查
     */
    string setOvenCheckCurveIntegrity(string deivceId, long uid, int menuNub,bool manualOrnot,int flag);
    
    /**
     * 	曲线执行命令
     */
    string setOvenExcuteCurveCmd(string deivceId, long uid, int menuNub,bool manualOrnot,int flag);
    
    /**
     *  获取菜单名字
     */
    string setOvenMenuName(string deivceId, int menuNub,bool manualOrnot,int flag);
    
    /**
     *   获取温度曲线扩展命令
     *   菜谱编号[0/1/2/3]，子节点[0-9]，提示声[0/1]，帧序号[0-254]
     */
    string setOvenMenuTemperatureExtend(string deivceId, int menuNub,int sub_node, int a_x ,bool manualOrnot,int flag);
    
    /**
     * 	曲线取消执行命令
     *  菜谱编号[0/1/2]，提示声[0/1]，帧序号[0]
     *
     */
    string setOvenCancelExcuteCurveCmd(string deivceId, long uid, int menuNub ,bool manualOrnot,int flag);
    
    /**
     * 	曲线暂停-继续操作命令
     *  菜谱编号[0/1/2]，暂停或继续[0/1],提示声[0/1]，帧序号[0]
     */
    string setOvenPauseOrContinueCurve(string deivceId, long uid, int menuNub,bool pause_or_continue, bool manualOrnot,int flag);
    
    /****************** getStatus ******************/
    // 获取烤箱uid
    long getOvenUid(string deivceId);
    
    // 预热状态
    bool getOvenStatuYR(string deivceId);
    
    // 整机开关状态
    bool getOvenStatuKJ(string deivceId);
    
    // 炉灯开关状态
    bool getOvenStatuD(string deivceId);
    
    // 转叉开关状态
    bool getOvenStatuZC(string deivceId);
    
    // 风机开关状态
    bool getOvenStatuFS(string deivceId);
    
    // 正在烘焙的曲线 （当前无烘焙返回 0xff）
    string  getOvenStatuMenuNub(string deivceId);
    
    // 已完成烘烤时间高位:秒
    string  getOvenCompletedtRoastTimeH(string deivceId);
    
    // 已完成烘烤时间低位:秒
    string  getOvenCompletedRoastTimeL(string deivceId);
    
    // 当前设置的上管温度-高位
    string  getOvenCurrentSettedUTTH(string deivceId);
    
    // 当前设置的上管温度-低位
    string  getOvenCurrentSettedUTTL(string deivceId);
    
    // 当前设置的上管温度-高位
    string  getOvenCurrentSettedMTTH(string deivceId);
    
    // 当前设置的上管温度-低位
    string  getOvenCurrentSettedMTTL(string deivceId);
    
    // 当前设置的下管温度-高位
    string  getOvenCurrentSettedLTTH(string deivceId);
    
    // 当前设置的下管温度-低位
    string  getOvenCurrentSettedLTTL(string deivceId);
    
    // 当前实际的上管温度-高位
    string  getOvenCurrentActualUTTH(string deivceId);
    
    // 当前实际的上管温度-低位
    string  getOvenCurrentActualUTTL(string deivceId);
    
    // 当前实际的中管温度-高位
    string  getOvenCurrentActualMTTH(string deivceId);
    
    // 当前实际的中管温度-低位
    string  getOvenCurrentActualMTTL(string deivceId);
    
    // 当前实际的下管温度-高位
    string  getOvenCurrentActualLTTH(string deivceId);
    
    // 当前实际的下管温度-低位
    string  getOvenCurrentActualLTTL(string deivceId);
    
    // 当前上管功率(0~100,表示 0~100%)
    string  getOvenCurrentUpperTubePower(string deivceId);
    
    // 当前中管功率(0~100,表示 0~100%)
    string  getOvenCurrentLowerTubePower(string deivceId);
    
    // 当前下管功率(0~100,表示 0~100%)
    string  getOvenCurrentMeddleTubePower(string deivceId);
    
    // 烤箱状态
    string  getOvenStatus(string deivceId);
    
    // 温度设置错误
    string  getOvenTemperatureSettedError(string deivceId);
    
    // 存储设备故障
    string  getOvenStorageDeviceError(string deivceId);
    
    // 烤箱发热装置故障
    string  getOvenHeatingDeviceError(string deivceId);
    
    // 温度传感器错误
    string  getOvenTemperatureSensorError(string deivceId);
    
    // I2C 设备错误
    string  getOvenI2CDeviceError(string deivceId);
    
    // 211-0 命令执行结果（当此项为 1 时，检查下面4 项的错误置位）
    string  getOven211_0CommandExecutedResult(string deivceId);
    
    // 菜单名称错误
    string  getOvenMenuNameError(string deivceId);
    
    // 总烧烤时间错误
    string  getOvenTotalRoastTimeError(string deivceId);
    
    // 曲线个数错误
    string  getOvenCurveNumbersError(string deivceId);
    
    // 菜单曲线错误
    string  getOvenMenuCurveError0(string deivceId);
    
    // 211-2命令执行结果（当此项为 1 时，检查下面 6 项的错误置位）
    string  getOven211_2CommandExecutedResult(string deivceId);
    
    // 设置时间错误
    string  getOvenSettedTimeError(string deivceId);
    
    // 上下管温度设置错误
    string  getOvenULTTSettedError(string deivceId);
    
    // 风机设置错误
    string  getOvenFanSettedError(string deivceId);
    
    // 转叉设置错误
    string  getOvenRotaryForkSettedError(string deivceId);
    
    // 曲线子节点过多
    string  getOvenCurveSubnodeMoreThanEnoughError(string deivceId);
    
    // 菜单曲线错误
    string  getOvenMenuCurveError2(string deivceId);
    
    // 211-3 命令执行结果（0：完整，1：不完整）
    string  getOven211_3CommandExecutedResult(string deivceId);
    
    // 211-4 命令执行结果（当此项为 1 时，检查下面 4 项的错误置位）
    string  getOven211_4CommandExecutedResult(string deivceId);
    
    // 曲线错误
    string  getOvenMenuCurveError4(string deivceId);
    
    // 该曲线不存在
    string  getOvenCurveNotExistError(string deivceId);
    
    // 烤箱未开机
    string  getOvenNotPowerOnError(string deivceId);
    
    // 烤箱正工作在烘焙程序中
    string  getOvenWorkingInRoastProcedureError(string deivceId);
    
    // 211-5 命令执行的返回： （0：曲线正确，1：曲线错误）
    string  getOven211_5CommandExecutedResult(string deivceId);
    
    // 211-7 命令执行结果（当此项为 1 时，检查下面2 项的错误置位）
    string  getOven211_7CommandExecutedResult(string deivceId);
    
    // 该曲线不存在
    string  getOvenCurveNotExistError7(string deivceId);
    
    // 曲线子节点不存在
    string  getOvenCurveSubnodeNotExistError(string deivceId);
    
    // 211-8 命令执行结果（曲线是否存在）
    string  getOven211_8CommandExecutedResult(string deivceId);
    
    // 211-9 命令执行结果（烤箱是否工作在烘焙曲线模式）
    string  getOven211_9CommandExecutedResult(string deivceId);
    
    // //已完成的烘焙时间
    int getOvenStatuRunTime(string deivceId);
    
    // //当前实际上管温度
    int getOvenStatuNowTemperature(string deivceId);
    
    /****************** getFN ******************/
    int getOvenHeatTubeNum(string deivceId);
    
    
    int getOvenOvenLampExitOrNot(string deivceId);
    
    
    int getOvenRotaryForkExitOrNot(string deivceId);
    
    
    int getOvenHeatAirCirculationOrNot(string deivceId);
    
    
    int getOvenSupportThawingModeOrNot(string deivceId);
    
    
    int getOvenSupportLowTemperatureFermentationOrNot(string deivceId);
    
    
    int getOvenSupportAlarmOrNot(string deivceId);
};

#endif /* XlfDeviceWrapper_h */
