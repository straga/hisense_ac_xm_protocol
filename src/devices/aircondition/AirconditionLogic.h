//
//  AirconditionLogic.h
//  Devices
//
//  Created by 肖芳亮 on 16/2/24.
//  Copyright © 2016年 XLF. All rights reserved.
//

#ifndef AirconditionLogic_h
#define AirconditionLogic_h


#include "DeviceLogic.h"

class AirconditionLogic : public DeviceLogic
{
private:
    
    /*华氏转摄氏对应数组*/
    static const int fahrenheit[];
    
    static const int celsius[];
    
    static const int fahrenheitSwitch[];
    
    static const int celsiusSwitch[];
    
private:
    
    /**
     * 华氏转摄氏
     */
    int fahrenheitConvertToCelsius(int temperature);
    
    /**
     * 摄氏转华氏
     */
    int celsiusConvertToFahrenheit(int temperature);
    
    /**
     * 华氏切换摄氏显示温度
     */
    int fahrenheitSwitchCelsiusDisplay(int temperature);
    
    /**
     * 摄氏切换华氏显示温度
     */
    int celsiusSwitchFahrenheitDisplay(int temperature);
    
    /**
     * 华氏与摄氏切换显示
     */
    int temperatureSwitchDisplay(int temperatureDispaly);
    
    /**
     * 刷新功能表
     */
    void refreshFn();
    
    /**
     * 根据开关状态 设置默认状态
     */
    void setPowerStatus(int PowerOn);
    
    /**
     * 设置功能
     */
    void setKtFN(string value,int offset);
    
    /**
     * 获取功能
     */
    int getKtFN(int offset);
    
    /**
     * 解析返回的数据
     */
    bool parseAtCommand(string result);
    
    /**
     * 同步状态  不是控制指令
     */
    void syncPower();
    
public:
    
    AirconditionLogic();
    
    ~AirconditionLogic();
    
    /**************************************** 控制 ****************************************/
    /**
     * 设置风量
     */
    string setWindSpeed(string value,int manualOrnot);
    
    /**
     * 设置睡眠模式
     */
    string setSleepMode(string sleepMode,int manualOrnot);
    
    /**
     * 设置模式
     */
    string setMode(string Mode,int manualOrnot);
    
    /**
     * 设置开/关机
     */
    string setPower(int on,int manualOrnot);
    
    /**
     * 设置KTSBOX
     */
    string setKtSBox(int on,string Mode,string WindSpeed_value,int temperature,int IsMute,int manualOrnot);
    
    /**
     * 设置风向
     */
    string setWindDirection(int on,int manualOrnot);
    
    /**
     * 设置温度
     */
    string setTemperature(int temperature,int manualOrnot);
    
    /**
     * 设置湿度
     */
    string setHumidity(int humidity,int manualOrnot);
    
    /**
     * 体感控制,体感室内温度,体感室内温度补偿
     */
    string setSomatosensoryRealityTemperature(int on,int temperature,int compensation,int manualOrnot);
    
    /**
     * 自动工作模式和除湿模式的温度补偿
     */
    string setTemperatureCompensation(int compensation,int manualOrnot);
    
    /**
     * 华氏/摄氏温度显示设置
     */
    string setTemperatureValueSwitch(int Fahrenheit,int manualOrnot);
    
    /**
     * 普通定时关机,普通定时关机时间
     */
    string setGeneralTimingShutdown(int on,string hour,int manualOrnot);
    
    /**
     * 实时时钟的小时值,实时时钟的分钟值
     */
    string setRealityTime(string hour,string minute,int manualOrnot);
    
    /**
     * 实时开机控制,实时时钟的小时值,实时时钟的分钟值,实时开机小时,实时开机分钟
     */
    string setRealityTimeBoot(int on,string Realityhour,string Realityminute, string boothour,string bootminute, string remainingHour,string remainingMinute, int manualOrnot);
    
    /**
     * 实时关机控制,实时时钟的小时值,实时时钟的分钟值,实时关机小时,实时关机分钟
     */
    string setRealityTimeShutdown(int on,string Realityhour,string Realityminute, string shutdownhour,string shutdownminute, string remainingHour,string remainingMinute, int manualOrnot);
    
    /**
     * 设置除湿模式
     */
    string setDehumidificationMode(string mode,int manualOrnot);
    
    /**
     * 上下风门模式,上下风开停控制
     */
    string setVerticalWind(string mode,int on,int manualOrnot);
    
    /**
     * 左右风开停控制,左风摆,右风摆
     */
    string setHorizontalWind(int on,int left,int right,int manualOrnot);
    
    /**
     * 自然风开停
     */
    string setNatureWind(int on,int manualOrnot);
    
    /**
     * 设置电加热
     */
    string setElectricalHeating(int on,int manualOrnot);
    
    /**
     * 设置节能
     */
    string setEnergyConservation(int on,int manualOrnot);
    
    /**
     * 设置并用节电
     */
    string setShare(int on,int manualOrnot);
    
    /**
     * 设置高效
     */
    string setEfficient(int on,int manualOrnot);
    
    /**
     * 设置高效 OEM项目专用
     */
    string setEfficientOem(int on,int manualOrnot);
    
    /**
     * 设置双模
     */
    string setDualMode(int on,int manualOrnot);
    
    /**
     * 设置清新
     */
    string setFreshness(int on,int manualOrnot);
    
    /**
     * 设置换风
     */
    string setFreshAir(int on,int manualOrnot);
    
    /**
     * 设置室内清洁
     */
    string setClernIndoor(int on,int manualOrnot);
    
    /**
     * 设置室外清洁
     */
    string setClernOutdoor(int on,int manualOrnot);
    
    /**
     * 设置智慧眼
     */
    string setSmartEye(int on,int manualOrnot);
    
    /**
     * 设置室静音
     */
    string setMute(int on,int manualOrnot);
    
    /**
     * 设置语音
     */
    string setVoice(int on,int manualOrnot);
    
    /**
     * 设置除烟
     */
    string setClernSmoke(int on,int manualOrnot);
    
    /**
     * 设置背景灯
     */
    string setBackgroundLamp(int on,int manualOrnot);
    
    /**
     * 显示屏发光
     */
    string setScreen(int on,int manualOrnot);
    
    /**
     * LED指示灯
     */
    string setLED(int on,int manualOrnot);
    
    /**
     * 室内外温度切换显示
     */
    string setIndoorOutdoorSwitch(int on,int manualOrnot);
    
    /**
     * 室内过滤网清洁复位控制
     */
    string setIndoorFilterClear(int on,int manualOrnot);
    
    /**
     * 显示屏亮度值
     */
    string setScreenLuminance(int light,int manualOrnot);
    
    /**
     * 直接设置开/关机
     */
    string setDirctPower(string devid,int on,int manualOrnot);
    
    /**
     * 获取空调所有状态
     */
    string getAirConditionAllStatus(int manualOrnot);
    
    /**************************************** 状态 ****************************************/
    /**
     * 获取风量
     */
    string getWindSpeed();
    
    /**
     * 获取睡眠
     */
    string getSleepMode();
    
    /**
     * 获取xx
     */
    string getSleep();
    
    /**
     * 获取模式
     */
    string getMode();
    
    /**
     * 获取开机
     */
    string getPower();
    
    /**
     * 获取风量
     */
    /*风向*/
    string getWindDirection();
    
    /**
     * 获取设置温度
     */
    string getSetingTemperature();
    
    /**
     * 获取湿度
     */
    string getHumidity();
    
    /**
     * 获取体感室内温度
     */
    string getSomatosensoryRealityTemperature();
    
    /**
     * 获取室内实际温度
     */
    string getIndoorRealityTemperature();
    
    /**
     * 获取室内盘管温度
     */
    string getIndoorPipeTemperature();
    
    /**
     * 获取室内实际湿度值
     */
    string getIndoorRealityHumidity();
    
    /**
     * 获取体感室内温度补偿
     */
    string getSomatosensoryCompensation();
    
    /**
     * 获取体感控制
     */
    string getSomatosensoryContrl();
    
    /**
     * 获取自动工作模式和除湿模式的温度补偿
     */
    string getTemperatureCompensation();
    
    /**
     * 获取华氏/摄氏温度显示设置
     */
    string getTemperatureValueSwitch();
    
    /**
     * 获取普通定时开关机
     */
    string getGeneralTimingShutdownValue();
    
    /**
     * 获取实时时钟的小时值
     */
    string getRealityHour();
    
    /**
     * 获取实时时钟的分钟值
     */
    string getRealityMinute();
    
    /**
     * 获取实时开机控制
     */
    string getRealityBootContrl();
    
    /**
     * 获取实时开机小时
     */
    string getRealityBootHour();
    
    /**
     * 获取实时开机分钟
     */
    string getRealityBootMinute();
    
    /**
     * 获取实时关机控制
     */
    string getRealityShutdownContrl();
    
    /**
     * 获取实时关机小时
     */
    string getRealityShutdownHour();
    
    /**
     * 获取实时关机分钟
     */
    string getRealityShutdownMinute();
    
    /**
     * 获取除湿模式
     */
    string getDehumidificationMode();
    
    /**
     * 获取上下风门
     */
    string getVerticalWindMode();
    
    /**
     * 获取上下风开停控制
     */
    string getVerticalWindContrl();
    
    /**
     * 获取左右风开停控制
     */
    string getHorizontalWindContrl();
    
    /**
     * 获取自然风开停控制
     */
    string getNatureWindContrl();
    
    /**
     * 获取电热
     */
    string getElectricalHeating();
    
    /**
     * 获取节能
     */
    string getEnergyConservation();
    
    /**
     * 获取并用节电
     */
    string getShare();
    
    /**
     * 获取高效
     */
    string getEfficient();
    
    /**
     * 获取双模
     */
    string getDualMode();
    
    /**
     * 获取清新
     */
    string getFreshness();
    
    /**
     * 获取换风
     */
    string getFreshAir();
    
    /**
     * 获取室内清洁
     */
    string getClernIndoor();
    
    /**
     * 获取室外清洁
     */
    string getClernOutdoor();
    
    /**
     * 获取智慧眼
     */
    string getSmartEye();
    
    /**
     * 获取静音
     */
    string getMute();
    
    /**
     * 获取语音
     */
    string getVoice();
    
    /**
     * 获取除烟
     */
    string getClernSmoke();
    
    /**
     * 获取背景灯
     */
    string getBackgroundLamp();
    
    /**
     * 获取显示屏发光
     */
    string getScreen();
    
    /**
     * 获取LED指示灯
     */
    string getLED();
    
    /**
     * 获取室内外温度切换显示
     */
    string getIndoorOutdoorSwitch();
    
    /**
     * 获取室内过滤网清洁复位控制
     */
    string getIndoorFilterClear();
    
    /**
     * 获取左风摆
     */
    string getLeftWind();
    
    /**
     * 获取右风摆
     */
    string getRightWind();
    
    /**
     * 获取室内电量板
     */
    string getChargeBorad ();
    
    /**
     * 获取本次命令之前是否有过红外遥控与按键控制过
     */
    string getHaveIRContrl();
    
    /**
     * 获取本次命令之前是否有过WIFI控制过
     */
    string getHaveWIFIContrl();
    
    /**
     * 获取空调正常机型与测试机型
     */
    string getModel();
    
    /**
     * 获取室内EEPROM在线升级
     */
    string getEEPROMUpdate();
    
    /**
     * 获取室内温度传感器故障
     */
    string getIndoorTemperatureSensorTrouble();
    
    /**
     * 获取室内盘管温度传感器故障
     */
    string getIndoorPipeTemperatureSensorTrouble();
    
    /**
     * 获取室内湿度传感器故障
     */
    string getIndoorHumiditySensorTrouble();
    
    /**
     * 获取室内排水泵故障
     */
    string getIndoorDrainsWaterPumpTrouble();
    
    /**
     * 获取室内风机电机运转异常故障
     */
    string getIndoorFanMotorTrouble();
    
    /**
     * 获取柜机格栅保护告警
     */
    string getPioneerGrillingProtectTrouble();
    
    /**
     * 获取室内电压过零检测故障
     */
    string getIndoorVoltageZeroCrossDetectionTrouble();
    
    /**
     * 获取室内外通信故障
     */
    string getIndoorOutdoorCommunicationTrouble();
    
    /**
     * 获取室内控制板与显示板通信故障
     */
    string getIndoorContrlScreenCommunicationTrouble();
    
    /**
     * 获取室内控制板与按键板通信故障
     */
    string getIndoorContrlKeypadCommunicationTrouble();
    
    /**
     * 获取WIFI控制板与室内控制板通信故障
     */
    string getIndoorContrlWIFICommunicationTrouble();
    
    /**
     * 获取室内控制板与室内电量板通信故障
     */
    string getIndoorContrlChargeCommunicationTrouble();
    
    /**
     * 获取室内控制板EEPROM出错
     */
    string getIndoorContrlEEPROMTrouble();
    
    /**
     * 获取运行频率
     */
    string getRunFrequency();
    
    /**
     * 获取目标频率
     */
    string getTargetFrequency();
    
    /**
     * 获取发给驱动器的频率
     */
    string getDriveFrequency();
    
    /**
     * 获取环境温度
     */
    string getEnvironmentTemperature();
    
    /**
     * 获取冷凝器温度
     */
    string getCondenserTemperature();
    
    /**
     * 获取排气温度
     */
    string getExhaustTemperature();
    
    /**
     * 获取目标排气温度
     */
    string getTargetExhaustTemperature();
    
    /**
     * 获取室外电子膨胀阀开度
     */
    string getOutdoorElectronicExpansion();
    
    /**
     * 获取UABH
     */
    string getUABH();
    
    /**
     * 获取UABL
     */
    string getUABL();
    
    /**
     * 获取UBCH
     */
    string getUBCH();
    
    /**
     * 获取UBCL
     */
    string getUBCL();
    
    /**
     * 获取UCAH
     */
    string getUCAH();
    
    /**
     * 获取UCAL
     */
    string getUCAL();
    
    /**
     * 获取IAB
     */
    string getIAB();
    
    /**
     * 获取IBC
     */
    string getIBC();
    
    /**
     * 获取ICA
     */
    string getICA();
    
    /**
     * 获取IUV
     */
    string getIUV();
    
    /**
     * 获取直流母线电压H
     */
    string getCocurrentBusVoltageH();
    
    /**
     * 获取直流母线电压L
     */
    string getCocurrentBusVoltageL();
    
    /**
     * 获取四通阀状态
     */
    string getFourWayLimen();
    
    /**
     * 获取室外机实际工作状态
     */
    string getOutdoorRealityRuning();
    
    /**
     * 获取风机运行状态
     */
    string getFanRuning();
    
    /**
     * 获取室外机强制室内机风门位置
     */
    string getOutdoorForceIndoorWindPosition();
    
    /**
     * 获取室外机强制室内机风速
     */
    string getOutdoorForceIndoorWindSpeed();
    
    /**
     * 获取室外机强制室内机停
     */
    string getOutdoorForceIndoorStop();
    
    /**
     * 获取温控关机
     */
    string getShutdownByTemperatureContrl();
    
    /**
     * 获取一拖多标志
     */
    string getOne4All();
    
    /**
     * 获取除湿阀标志
     */
    string getDehumidifierLimen();
    
    /**
     * 获取室外机化霜
     */
    string getOutdoorDefrosting();
    
    /**
     * 获取室外旁通化霜
     */
    string getOutdoorBypassDefrosting();
    
    /**
     * 获取回油标志
     */
    string getOilReturn();
    
    /**
     * 获取室外故障显示标志
     */
    string getOutdoorTroubleDisplay();
    
    /**
     * 获取室外机EEPROM在线下载标志
     */
    string getOutdoorEEPROMDownload();
    
    /**
     * 获取室外机电量板
     */
    string getOutdoorChargeBoard();
    
    /**
     * 获取压缩机电热带
     */
    string getcompressorRibbonHeater();
    
    /**
     * 获取
     */
    /*压缩机预加热*/
    string getcompressorBeforeHandheat();
    
    /**
     * 获取补气增晗
     */
    string getReinflation();
    
    /**
     * 获取室内外机模式冲突
     */
    string getOutdoorModeClash();
    
    /**
     * 获取室外EEPROM出错
     */
    string getOutdoorEEPROMTrouble();
    
    /**
     * 获取室外盘管温度传感器故障
     */
    string getOutdoorPipeTemperatureSensorTrouble();
    
    /**
     * 获取排气温度传感器故障
     */
    string getOutdoorExhausTemperatureSensorTrouble();
    
    /**
     * 获取室外环境温度传感器故障
     */
    string getOutdoorEnvironmentTemperatureSensorTrouble();
    
    /**
     * 获取电压变压器故障
     */
    string getVoltageTransformerTrouble();
    
    /**
     * 获取电流互感器故障
     */
    string getCurrentTransformerTrouble();
    
    /**
     * 获取室外控制与驱动通信故障
     */
    string getOutdoorContrlDriveCommunicationTrouble();
    
    /**
     * 获取IPM模块过流保护
     */
    string getIPMOvercurrentProtect();
    
    /**
     * 获取IPM模块过热保护
     */
    string getIPMOverheatingProtect();
    
    /**
     * 获取交流电过电压保护
     */
    string getAlternatingCurrentOvervoltageProtect();
    
    /**
     * 获取交流电欠电压保护
     */
    string getAlternatingCurrentUndervoltageProtect();
    
    /**
     * 获取母线电压过电压保护
     */
    string getBusbarVoltageOvervoltageProtect();
    
    /**
     * 获取
     */
    /*母线电压欠电压保护*/
    string getBusbarVoltageUndervoltageProtect();
    
    /**
     * 获取PFC过电流保护
     */
    string getPFCOvercurrentProtect();
    
    /**
     * 获取室外机最大电流保护
     */
    string getOutdoorMaximumCurrentProtect();
    
    /**
     * 获取室外环境温度过低保护
     */
    string getOutdooEnvironmentOvertemperatureProtect();
    
    /**
     * 获取排气温度过高保护
     */
    string getExhaustOvertemperatureProtect();
    
    /**
     * 获取压缩机管壳温度保护
     */
    string getCompressoPipeShellTemperatureProtect();
    
    /**
     * 获取室内防冻结或防过载保护
     */
    string getIndoorAntiFreezingProtect();
    
    /**
     * 室外机PFC保护
     */
    string getOutdoorPFCProtect();
    
    /**
     * 压缩机启动失败
     */
    string getCompressoBootFail();
    
    /**
     * 获取压缩机失步
     */
    string getCompressoStepOut();
    
    /**
     * 获取室外风机堵转
     */
    string getOutdoorFanLockRotor();
    
    /**
     * 获取室外盘管防过载保护
     */
    string getOutdoorPieOverloadProtect();
    
    /**
     * 获取冷媒泄漏
     */
    string getRefrigerantLeakage();
    
    /**
     * 获取压缩机型号匹配错误
     */
    string getCompressoModelMismatch();
    
    /**
     * 获取系统低频振动保护
     */
    string getSystemLowFrequencyVibrationProtect();
    
    /**
     * 获取室外散热器温度过高保护
     */
    string getOutdoorRadiatorOvertemperatureProtect();
    
    /**
     * 获取系统压力过高保护
     */
    string getSystemHypertonusProtect();
    
    /**
     * 获取逆变器直流过电压故障
     */
    string getInverterCocurrentOvervoltageTrouble();
    
    /**
     * 获取逆变器直流低电压故障
     */
    string getInverterCocurrentUndervoltageTrouble();
    
    /**
     * 获取逆变器交流过电流故障
     */
    string getInverterCocurrentOvercurrentTrouble();
    
    /**
     * 获取失步检出
     */
    string getStepOutDetection();
    
    /**
     * 获取速度推定脉冲检出法检出欠相故障
     */
    string getSpeedPulseFault();
    
    /**
     * 获取电流推定脉冲检出法检出欠相故障
     */
    string getCurrentPulseFault();
    
    /**
     * 获取逆变器IPM故障-边沿
     */
    string getInverterEdgeFault();
    
    /**
     * 获取逆变器IPM故障-电平
     */
    string getInverterLevelFault();
    
    /**
     * 获取PFC_IPM故障-边沿
     */
    string getPFC_IPMEdgeFault();
    
    /**
     * 获取PFC_IPM故障-电平
     */
    string getPFC_IPMLevelFault();
    
    /**
     * 获取PFC停电检出故障
     */
    string getPFCPowerCutFault();
    
    /**
     * 获取PFC过电流检出故障
     */
    string getPFCOvercurrentFault();
    
    /**
     * 获取直流电压检出异常
     */
    string getDCVException();
    
    /**
     * 获取PFC低电压（有效值）检出故障
     */
    string getPFCLowVoltageFault();
    
    /**
     * 获取AD偏置异常检出故障
     */
    string getADOffsetAnomaliesFault();
    
    /**
     * 获取逆变器PWM逻辑设置故障
     */
    string getInverterPWMLogicFault();
    
    /**
     * 获取逆变器PWM初始化故障
     */
    string getInverterPWMInitFault();
    
    /**
     * 获取PFC_PWM逻辑设置故障
     */
    string getPFCPWMLogicFault();
    
    /**
     * 获取PFC_PWM初始化故障
     */
    string getPFC_PWMInitFault();
    
    /**
     * 获取温度异常
     */
    string getTemperatureAnomaly();
    
    /**
     * 获取电流采样电阻不平衡调整故障
     */
    string getCurrentSamplingFault();
    
    /**
     * 获取电机参数设置故障
     */
    string getMotorDataFault();
    
    /**
     * 获取MCE故障
     */
    string getMCEFault();
    
    /**
     * 获取驱动EEPROM故障
     */
    string getEEPROMFault();
    
    /**
     * 获取室外盘管过载禁升频
     */
    string getOutdoorCoilOverloadUpFrequency();
    
    /**
     * 获取室外盘管过载降频
     */
    string getOutdoorCoilOverloadDownFrequency();
    
    /**
     * 获取室内盘管过载禁升频
     */
    string getIndoorCoilOverloadUpFrequency();
    
    /**
     * 获取室内盘管过载降频
     */
    string getIndoorCoilOverloadDownFrequency();
    
    /**
     * 获取压降排气过载禁升频
     */
    string getPressureUpFrequency();
    
    /**
     * 获取压降排气过载降频
     */
    string getPressureDownFrequency();
    
    /**
     * 获取室内盘管冻结禁升频
     */
    string getIndoorCoilFreezingUpFrequency();
    
    /**
     * 获取室内盘管冻结降频
     */
    string getIndoorCoilFreezingDownFrequency();
    
    /**
     * 获取室内外通信降频
     */
    string getCommunicationDownFrequency();
    
    /**
     * 获取模块温度过载限频
     */
    string getModuleTemperaturelimitFrequency();
    
    /**
     * 获取变调率限频
     */
    string getModulationRatelimitFrequency();
    
    /**
     * 获取相电流限频
     */
    string getPhaseCurrentlimitFrequency();
    
    /**
     * 获取并用节电保护禁升频
     */
    string getPowerSaveUpFrequency();
    
    /**
     * 获取并用节电保护降频
     */
    string getPowerSaveDownFrequency();
    
    /**
     * 获取过电流保护禁升频
     */
    string getOvercurrentUpFrequency();
    
    /**
     * 获取过电流保护降频
     */
    string getOvercurrentDownFrequency();
    
    /**
     * 获取室内风机转速xx
     */
    string getIndoorFanSpeedH();
    
    /**
     * 获取室内风机转速00xx
     */
    string getIndoorFanSpeed00L();
    
    /**
     * 获取有否PM2.5检测功能
     */
    string getPM25();
    
    /**
     * 获取PM2.5污染程度
     */
    string getPM25Level();
    
    /**
     * 获取空气PM2.5质量百分比表示
     */
    string getPM25Percent();
    
    /**
     * 获取显示屏亮度值
     */
    string getScreenLuminance();
    
    /**
     * 获取普通定时开关机有效
     */
    string getGeneralTimingShutdown();
    
    /**************************************** 功能 ****************************************/
    /**
     * 获取命令支持状态
     */
    int getWindSpeedNum();
    
    /**
     * 设置睡眠模式
     */
    int getSleepModeFN();
    
    /**
     * 设置模式
     */
    int getCoolModeFN();
    
    /**
     * 开/关机
     */
    int getPowerFN();
    
    /**
     * 室内单个风向控制功能
     */
    int getWindDirectionFN();
    
    /**
     * 设置温度
     */
    int getTemperatureFN();
    
    /**
     * 设置湿度
     */
    int getHumidityFN();
    
    /**
     * 体感控制,体感室内温度,体感室内温度补偿
     */
    int getSomatosensoryRealityTemperatureFN();
    
    /**
     * 自动工作模式和除湿模式的温度补偿
     */
    int getTemperatureCompensationFN();
    
    /**
     * 华氏/摄氏温度显示设置
     */
    int getTemperatureValueSwitchFN();
    
    /**
     * 普通定时关机,普通定时关机时间
     */
    int getGeneralTimingShutdownFN();
    
    /**
     * 实时开机控制,实时时钟的小时值,实时时钟的分钟值,实时开机小时,实时开机分钟
     */
    int getRealityTimeFN();
    
    /**
     * 6位置可定室内风门位置控制
     */
    int getVerticalWindModeNum();
    
    /**
     * 上下风门模式,上下风开停控制
     */
    int getVerticalWindFN();
    
    /**
     * 左右风开停控制,左风摆,右风摆
     */
    int getHorizontalWindFN();
    
    /**
     * 自然风开停
     */
    int getNatureWindFN();
    
    /**
     * 设置电加热
     */
    int getElectricalHeatingFN();
    
    /**
     * 除湿模式
     */
    int getDehumidificationModeFN();
    
    /**
     * 设置节能
     */
    int getEnergyConservationFN();
    
    /**
     * 设置并且节能
     */
    int getShareFN();
    
    /**
     * 设置高效
     */
    int getEfficientFN();
    
    /**
     * 设置双模
     */
    int getDualModeFN();
    
    /**
     * 设置清新
     */
    int getFreshnessFN();
    
    /**
     * 设置换风
     */
    int getFreshAirFN();
    
    /**
     * 设置室内清洁
     */
    int getClernIndoorFN();
    
    /**
     * 设置室外清洁
     */
    int getClernOutdoorFN();
    
    /**
     * 设置室智能眼
     */
    int getSmartEyeFN();
    
    /**
     * 设置室静音
     */
    int getMuteFN();
    
    /**
     * 设置语音
     */
    int getVoiceFN();
    
    /**
     * 设置除烟
     */
    int getClernSmokeFN();
    
    /**
     * 背景灯
     */
    int getBackgroundLampFN();
    
    /**
     * 显示屏发光
     */
    int getScreenFN();
    
    /**
     * LED指示灯
     */
    int getLEDFN();
    
    /**
     * 室内外温度切换显示
     */
    int getIndoorOutdoorSwitchFN();
    
    /**
     * 室内过滤网清洁复位控制
     */
    int getIndoorFilterClearFN();
    
    /**
     * 左风摆开停控制
     */
    int getLeftFanContrlFN();
    
    /**
     * 右风摆开停控制
     */
    int getRightFanContrlFN();
    
    /**
     * 控制规则
     */
    int getContrlRate();
    
    /********* 设置功能 ********/
    /**
     * 设置睡眠模式
     */
    void setWindSpeedFN(string value);
    
    /**
     *
     */
    void setSleepModeFN(string value);
    
    /**
     * 设置模式
     */
    void setModeFN(string value);
    
    /**
     * 开/关机
     */
    void setPowerFN(string value);
    
    /**
     * 设置温度
     */
    void setTemperatureFN(string value);
    
    /**
     * 设置湿度
     */
    void setHumidityFN(string value);
    
    /**
     * 体感控制,体感室内温度,体感室内温度补偿
     */
    void setSomatosensoryRealityTemperatureFN(string value);
    
    /**
     * 自动工作模式和除湿模式的温度补偿
     */
    void setTemperatureCompensationFN(string value);
    
    /**
     * 华氏/摄氏温度显示设置
     */
    void setTemperatureValueSwitchFN(string value);
    
    /**
     * 普通定时关机,普通定时关机时间
     */
    void setGeneralTimingShutdownFN(string value);
    
    /**
     * 实时开机控制,实时时钟的小时值,实时时钟的分钟值,实时开机小时,实时开机分钟
     */
    void setRealityTimeFN(string value);
    
    /**
     * 上下风门模式,上下风开停控制
     */
    void setVerticalWindFN(string value);
    
    /**
     * 左右风开停控制,左风摆,右风摆
     */
    void setHorizontalWindFN(string value);
    
    /**
     * 自然风开停
     */
    void setNatureWindFN(string value);
    
    /**
     * 设置电加热
     */
    void setElectricalHeatingFN(string value);
    
    /**
     * 除湿模式
     */
    void setDehumidificationModeFN(string value);
    
    /**
     * 设置节能
     */
    void setEnergyConservationFN(string value);
    
    /**
     * 设置并且节能
     */
    void setShareFN(string value);
    
    /**
     * 设置高效
     */
    void setEfficientFN(string value);
    
    /**
     * 设置双模
     */
    void setDualModeFN(string value);
    
    /**
     * 设置清新
     */
    void setFreshnessFN(string value);
    
    /**
     * 设置换风
     */
    void setFreshAirFN(string value);
    
    /**
     * 设置室内清洁
     */
    void setClernIndoorFN(string value);
    
    /**
     * 设置室外清洁
     */
    void setClernOutdoorFN(string value);
    
    /**
     * 设置室智能眼
     */
    void setSmartEyeFN(string value);
    
    /**
     * 设置室静音
     */
    void setMuteFN(string value);
    
    /**
     * 设置语音
     */
    void setVoiceFN(string value);
    
    /**
     * 设置除烟
     */
    void setClernSmokeFN(string value);
    
    /**
     * 背景灯
     */
    void setBackgroundLampFN(string value);
    
    /**
     * 显示屏发光
     */
    void setScreenFN(string value);
    
    /**
     * LED指示灯
     */
    void setLEDFN(string value);
    
    /**
     * 室内外温度切换显示
     */
    void setIndoorOutdoorSwitchFN(string value);
    
    /**
     * 室内过滤网清洁复位控制
     */
    void setIndoorFilterClearFN(string value);
};

#endif /* AirconditionLogic_h */
