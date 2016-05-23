//
//  XlfDeviceWrapper.cpp
//  Devices
//
//  Created by 肖芳亮 on 16/2/24.
//  Copyright ? 2016年 XLF. All rights reserved.
//

#include "XlfDeviceWrapper.h"
#include "XlfDeviceManager.h"

#define default_string  ""
#define default_int     -1
#define default_bool    false


int XlfDeviceWrapper::getDeviceType(const string &deviceId)
{
    if(NULL != devicesControlManager)
    {
        XlfDeviceInfo *deviceInfo = ((XlfDeviceManager *)devicesControlManager)->getDeviceInfo(deviceId);
        if(NULL != deviceInfo)
        {
        	return deviceInfo->getDeviceType();
        }
    }
	return -1;
}

XlfDeviceWrapper::XlfDeviceWrapper()
{
    devicesControlManager = &XlfDeviceManager::getInstance();
}

/**
 * 初始化设备的控制类
 */
bool XlfDeviceWrapper::initDevicesControl(const string &deviceId, int deviceType)
{
    if(NULL != devicesControlManager)
    {
        return ((XlfDeviceManager *)devicesControlManager)->initDeviceControl(deviceId, deviceType);
    }
    return default_bool;
}

/**
 *  删除单个设备的控制类
 */
bool XlfDeviceWrapper::delDevicesControl(const string &deviceId)
{
    if(NULL != devicesControlManager)
    {
        return ((XlfDeviceManager *)devicesControlManager)->deleteDeviceControl(deviceId);
    }
    return default_bool;
}

/**
 * 获取设备控制类
 */
void* XlfDeviceWrapper::getDeviceControl(const string &deviceId)
{
    if(NULL != devicesControlManager)
    {
        XlfDeviceInfo *deviceInfo = ((XlfDeviceManager *)devicesControlManager)->getDeviceInfo(deviceId);
        if(NULL != deviceInfo)
        {
            if(NULL != deviceInfo->deviceControl)
            {
                return deviceInfo->deviceControl;
            }
        }
    }
    return NULL;
}

/**
 * 获取wifi控制类
 */
void* XlfDeviceWrapper::getWifiControl(string deviceId)
{
    if(NULL != devicesControlManager)
    {
        XlfDeviceInfo *deviceInfo = ((XlfDeviceManager *)devicesControlManager)->getDeviceInfo(deviceId);
        if(NULL != deviceInfo)
        {
            if(NULL != deviceInfo->wifiControl)
            {
                return deviceInfo->wifiControl;
            }
        }
    }
    return NULL;
}

/**************************  deviceControl  **************************/
/**
 * 通用开、关机
 */
string XlfDeviceWrapper::setPowerCommon(string deviceId, int power, int soundSet)
{
    DeviceControl *devicesControl = (DeviceControl *)getDeviceControl(deviceId);
    if(NULL != devicesControl)
    {
        return devicesControl->setPowerCommon(power, soundSet);
    }
    return default_string;
}

/**
 * 查询设备所有状态
 */
string XlfDeviceWrapper::setQueryDeviceAllStatus(string deviceId, int soundSet)
{
    DeviceControl *devicesControl = (DeviceControl *)getDeviceControl(deviceId);
    if(NULL != devicesControl)
    {
        return devicesControl->setQueryDeviceAllStatus(soundSet);
    }
    return default_string;
}

/**
 * 查询设备功能列表
 */
string XlfDeviceWrapper::setQueryDeviceAllFunctions(string deviceId, int soundSet)
{
    DeviceControl *devicesControl = (DeviceControl *)getDeviceControl(deviceId);
    if(NULL != devicesControl)
    {
        return devicesControl->setQueryDeviceAllFunctions(soundSet);
    }
    return default_string;
}

/**
 * 查询设备型号信息
 */
string XlfDeviceWrapper::setQueryDeviceModle(string deviceId, int soundSet)
{
    DeviceControl *devicesControl = (DeviceControl *)getDeviceControl(deviceId);
    if(NULL != devicesControl)
    {
        return devicesControl->setQueryDeviceModle(soundSet);
    }
    return default_string;
}

/**
 * 查询设备类型
 */
string XlfDeviceWrapper::setQueryDeviceAddress(string deviceId, int soundSet)
{
    DeviceControl *devicesControl = (DeviceControl *)getDeviceControl(deviceId);
    if(NULL != devicesControl)
    {
        return devicesControl->setQueryDeviceAddress(soundSet);
    }
    return default_string;
}

// 查询固件版本
string XlfDeviceWrapper::sendQueryVersion(string deviceId,int flag)
{
    DeviceControl *devicesControl = (DeviceControl *)getDeviceControl(deviceId);
    if(NULL != devicesControl)
    {
        return devicesControl->sendQueryVersion(flag);
    }
    return default_string;
}

// 获取固件版本
string XlfDeviceWrapper::getSoftVersion(string deviceId)
{
    DeviceControl *devicesControl = (DeviceControl *)getDeviceControl(deviceId);
    if(NULL != devicesControl)
    {
        return devicesControl->getSoftVersion();
    }
    return default_string;
}

/**
 * 解析设备标识
 */
bool XlfDeviceWrapper::saveDeviceImformationCode(string deviceId, string resultText)
{
    DeviceControl *devicesControl = (DeviceControl *)getDeviceControl(deviceId);
    if(devicesControl != NULL)
    {
        return devicesControl->saveDeviceImformationCode(resultText);
    }
    return false;
}

/**
 * 更新设备所有状态
 */
bool XlfDeviceWrapper::setDeviceAllStatus(string deviceId, string allStauts)
{
    DeviceControl *devicesControl = (DeviceControl *)getDeviceControl(deviceId);
    if(devicesControl != NULL)
    {
        return devicesControl->setDeviceAllStatus(allStauts);
    }
    return false;
}

/**
 * 更新设备功能列表
 */
bool XlfDeviceWrapper::setDeviceFunction(string deviceId, string function)
{
    DeviceControl *devicesControl = (DeviceControl *)getDeviceControl(deviceId);
    if(devicesControl != NULL)
    {
        return devicesControl->setDeviceFunction(function);
    }
    return false;
}

/**
 *  获取设备型号信息
 */
string XlfDeviceWrapper::getDeviceModle(string deviceId)
{
    DeviceControl *devicesControl = (DeviceControl *)getDeviceControl(deviceId);
    if(devicesControl != NULL)
    {
        return devicesControl->getDeviceModle();
    }
    return default_string;
}

/**
 * 获取设备类型
 */
string XlfDeviceWrapper::getDeviceAddress(string deviceId)
{
    DeviceControl *devicesControl = (DeviceControl *)getDeviceControl(deviceId);
    if(devicesControl != NULL)
    {
        return devicesControl->getDeviceAddress();
    }
    return default_string;
}

/**
 * 获取控制类版本号
 */
string XlfDeviceWrapper::getVersionNumberOfDevicesControl(string deviceId)
{
    DeviceControl *devicesControl = (DeviceControl *)getDeviceControl(deviceId);
    if(devicesControl != NULL)
    {
        return devicesControl->getVersionNumberOfDevicesControl();
    }
    return default_string;
}

/**
 * 获取协议库版本号
 */
string XlfDeviceWrapper::getVersionNumberOfProtocolLibrary(string deviceId)
{
    DeviceControl *devicesControl = (DeviceControl *)getDeviceControl(deviceId);
    if(devicesControl != NULL)
    {
        return devicesControl->getVersionNumberOfProtocolLibrary();
    }
    return default_string;
}

/**
 * 获取获取wifi模块版本号
 */
string XlfDeviceWrapper::getVersionNumberOfWifiModule(string deviceId)
{
    DeviceControl *devicesControl = (DeviceControl *)getDeviceControl(deviceId);
    if(devicesControl != NULL)
    {
        return devicesControl->getVersionNumberOfWifiModule();
    }
    return default_string;
}

/**
 * 设置设备在线状态
 */
void XlfDeviceWrapper::setOnlineStatus(string deviceId, bool status)
{
    DeviceControl *devicesControl = (DeviceControl *)getDeviceControl(deviceId);
    if(NULL != devicesControl)
    {
        devicesControl->setOnlineStatus(status);
    }
}

/**
 * 获取设备在线状态
 */
string XlfDeviceWrapper::getOnlineStatus(string deviceId)
{
    DeviceControl *devicesControl = (DeviceControl *)getDeviceControl(deviceId);
    if(NULL != devicesControl)
    {
        if(devicesControl->getOnlineStatus())
        {
            return "1";
        }
    }
    return "0";
}

/**
 * 获取设备的受控状态
 */
string XlfDeviceWrapper::getSmartStatus(string deviceId)
{
    return "0";
}

/**
 * 解析返回结果
 */
string XlfDeviceWrapper::parseResult(const string &deviceId, const string &result)
{
    DeviceControl *devicesControl = (DeviceControl *)getDeviceControl(deviceId);
    if(devicesControl != NULL)
    {
        return devicesControl->parseResult(result);
    }
    return default_string;
}

/**************************  airconditionControl  **************************/

/**************************************** 控制 ****************************************/
/**
 * 设置风量
 */
string XlfDeviceWrapper::setAirconWindSpeed(string deviceId,string value,int soundSet)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->setWindSpeed(value,soundSet);
    }
    return default_string;
}

/**
 * 设置睡眠模式
 */
string XlfDeviceWrapper::setAirconSleepMode(string deviceId, string sleepMode,int soundSet)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->setSleepMode(sleepMode,soundSet);
    }
    return default_string;
}

/**
 * 设置模式
 */
string XlfDeviceWrapper::setAirconMode(string deviceId, string Mode,int soundSet)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->setMode(Mode,soundSet);
    }
    return default_string;
}

/**
 * 设置开/关机
 */
string XlfDeviceWrapper::setAirconPower(string deviceId, int on,int soundSet)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->setPower(on,soundSet);
    }
    return default_string;
}

/**
 * 设置KTSBOX
 */
string XlfDeviceWrapper::setAirconKtSBox(string deviceId, int on,string Mode,string WindSpeed_value,int temperature,int IsMute,int soundSet)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->setKtSBox(on,Mode,WindSpeed_value,temperature,IsMute,soundSet);
    }
    return default_string;
}

/**
 * 设置风向
 */
string XlfDeviceWrapper::setAirconWindDirection(string deviceId, int on,int soundSet)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->setWindDirection(on,soundSet);
    }
    return default_string;
}

/**
 * 设置温度
 */
string XlfDeviceWrapper::setAirconTemperature(string deviceId, int temperature,int soundSet)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->setTemperature(temperature,soundSet);
    }
    return default_string;
}

/**
 * 设置湿度
 */
string XlfDeviceWrapper::setAirconHumidity(string deviceId, int humidity,int soundSet)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->setHumidity(humidity,soundSet);
    }
    return default_string;
}

/**
 * 体感控制,体感室内温度,体感室内温度补偿
 */
string XlfDeviceWrapper::setAirconSomatosensoryRealityTemperature(string deviceId, int on,int temperature,int compensation,int soundSet)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->setSomatosensoryRealityTemperature(on,temperature,compensation,soundSet);
    }
    return default_string;
}

/**
 * 自动工作模式和除湿模式的温度补偿
 */
string XlfDeviceWrapper::setAirconTemperatureCompensation(string deviceId, int compensation,int soundSet)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->setTemperatureCompensation(compensation,soundSet);
    }
    return default_string;
}

/**
 * 华氏/摄氏温度显示设置
 */
string XlfDeviceWrapper::setAirconTemperatureValueSwitch(string deviceId, int Fahrenheit,int soundSet)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->setTemperatureValueSwitch(Fahrenheit,soundSet);
    }
    return default_string;
}

/**
 * 普通定时关机,普通定时关机时间
 */
string XlfDeviceWrapper::setAirconGeneralTimingShutdown(string deviceId, int on,string hour,int soundSet)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->setGeneralTimingShutdown(on,hour,soundSet);
    }
    return default_string;
}

/**
 * 实时时钟的小时值,实时时钟的分钟值
 */
string XlfDeviceWrapper::setAirconRealityTime(string deviceId, string hour,string minute,int soundSet)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->setRealityTime(hour,minute,soundSet);
    }
    return default_string;
}

/**
 * 实时开机控制,实时时钟的小时值,实时时钟的分钟值,实时开机小时,实时开机分钟
 */
string XlfDeviceWrapper::setAirconRealityTimeBoot(string deviceId, int on,string Realityhour,string Realityminute, string boothour,string bootminute, string remainingHour,string remainingMinute, int soundSet)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->setRealityTimeBoot(on,Realityhour,Realityminute,boothour,bootminute,remainingHour,remainingMinute,soundSet);
    }
    return default_string;
}

/**
 * 实时关机控制,实时时钟的小时值,实时时钟的分钟值,实时关机小时,实时关机分钟
 */
string XlfDeviceWrapper::setAirconRealityTimeShutdown(string deviceId, int on,string Realityhour,string Realityminute, string shutdownhour,string shutdownminute, string remainingHour,string remainingMinute, int soundSet)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->setRealityTimeShutdown(on,Realityhour,Realityminute,shutdownhour,shutdownminute,remainingHour,remainingMinute,soundSet);
    }
    return default_string;
}

/**
 * 设置除湿模式
 */
string XlfDeviceWrapper::setAirconDehumidificationMode(string deviceId,string mode,int soundSet)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->setDehumidificationMode(mode,soundSet);
    }
    return default_string;
}

/**
 * 上下风门模式,上下风开停控制
 */
string XlfDeviceWrapper::setAirconVerticalWind(string deviceId, string mode,int on,int soundSet)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->setVerticalWind(mode,on,soundSet);
    }
    return default_string;
}

/**
 * 左右风开停控制,左风摆,右风摆
 */
string XlfDeviceWrapper::setAirconHorizontalWind(string deviceId, int on,int left,int right,int soundSet)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->setHorizontalWind(on,left,right,soundSet);
    }
    return default_string;
}

/**
 * 自然风开停
 */
string XlfDeviceWrapper::setAirconNatureWind(string deviceId, int on,int soundSet)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->setNatureWind(on,soundSet);
    }
    return default_string;
}

/**
 * 设置电加热
 */
string XlfDeviceWrapper::setAirconElectricalHeating(string deviceId, int on,int soundSet)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->setElectricalHeating(on,soundSet);
    }
    return default_string;
}

/**
 * 设置节能
 */
string XlfDeviceWrapper::setAirconEnergyConservation(string deviceId, int on,int soundSet)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->setEnergyConservation(on,soundSet);
    }
    return default_string;
}

/**
 * 设置并用节电
 */
string XlfDeviceWrapper::setAirconShare(string deviceId, int on,int soundSet)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->setShare(on,soundSet);
    }
    return default_string;
}

/**
 * 设置高效
 */
string XlfDeviceWrapper::setAirconEfficient(string deviceId, int on,int soundSet)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->setEfficient(on,soundSet);
    }
    return default_string;
}

/**
 * 设置高效 OEM项目专用
 */
string XlfDeviceWrapper::setAirconEfficientOem(string deviceId, int on,int soundSet)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->setEfficientOem(on,soundSet);
    }
    return default_string;
}

/**
 * 设置双模
 */
string XlfDeviceWrapper::setAirconDualMode(string deviceId, int on,int soundSet)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->setDualMode(on,soundSet);
    }
    return default_string;
}

/**
 * 设置清新
 */
string XlfDeviceWrapper::setAirconFreshness(string deviceId, int on,int soundSet)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->setFreshness(on,soundSet);
    }
    return default_string;
}

/**
 * 设置换风
 */
string XlfDeviceWrapper::setAirconFreshAir(string deviceId, int on,int soundSet)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->setFreshAir(on,soundSet);
    }
    return default_string;
}

/**
 * 设置室内清洁
 */
string XlfDeviceWrapper::setAirconClernIndoor(string deviceId, int on,int soundSet)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->setClernIndoor(on,soundSet);
    }
    return default_string;
}

/**
 * 设置室外清洁
 */
string XlfDeviceWrapper::setAirconClernOutdoor(string deviceId, int on,int soundSet)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->setClernOutdoor(on,soundSet);
    }
    return default_string;
}

/**
 * 设置智慧眼
 */
string XlfDeviceWrapper::setAirconAirconditionSmartEye(string deviceId,int on,int soundSet)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->setSmartEye(on,soundSet);
    }
    return default_string;
}

/**
 * 设置室静音
 */
string XlfDeviceWrapper::setAirconMute(string deviceId, int on,int soundSet)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->setMute(on,soundSet);
    }
    return default_string;
}

/**
 * 设置语音
 */
string XlfDeviceWrapper::setAirconVoice(string deviceId, int on,int soundSet)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->setVoice(on,soundSet);
    }
    return default_string;
}

/**
 * 设置除烟
 */
string XlfDeviceWrapper::setAirconClernSmoke(string deviceId, int on,int soundSet)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->setClernSmoke(on,soundSet);
    }
    return default_string;
}

/**
 * 设置背景灯
 */
string XlfDeviceWrapper::setAirconBackgroundLamp(string deviceId, int on,int soundSet)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->setBackgroundLamp(on,soundSet);
    }
    return default_string;
}

/**
 * 显示屏发光
 */
string XlfDeviceWrapper::setAirconScreen(string deviceId, int on,int soundSet)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->setScreen(on,soundSet);
    }
    return default_string;
}

/**
 * LED指示灯
 */
string XlfDeviceWrapper::setAirconLED(string deviceId, int on,int soundSet)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->setLED(on,soundSet);
    }
    return default_string;
}

/**
 * 室内外温度切换显示
 */
string XlfDeviceWrapper::setAirconIndoorOutdoorSwitch(string deviceId, int on,int soundSet)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->setIndoorOutdoorSwitch(on,soundSet);
    }
    return default_string;
}

/**
 * 室内过滤网清洁复位控制
 */
string XlfDeviceWrapper::setAirconIndoorFilterClear(string deviceId, int on,int soundSet)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->setIndoorFilterClear(on,soundSet);
    }
    return default_string;
}

/**
 * 显示屏亮度值
 */
string XlfDeviceWrapper::setAirconScreenLuminance(string deviceId, int light,int soundSet)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->setScreenLuminance(light,soundSet);
    }
    return default_string;
}

/**
 * 直接设置开/关机
 */
string XlfDeviceWrapper::setAirconDirctPower(string deviceId, int on,int soundSet)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        //return airconditionControl->setDirctPower(on,soundSet);
    }
    return default_string;
}

/**
 * 获取空调所有状态
 */
string XlfDeviceWrapper::getAirconAllStatus(string deviceId, int soundSet)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        //return airconditionControl->getAllStatus(soundSet);
    }
    return default_string;
}

/**************************************** 状态 ****************************************/
/**
 * 获取风量
 */
string XlfDeviceWrapper::getAirconWindSpeed(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getWindSpeed();
    }
    return default_string;
}

/**
 * 获取睡眠
 */
string XlfDeviceWrapper::getAirconSleepMode(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getSleepMode();
    }
    return default_string;
}

/**
 * 获取xx
 */
string XlfDeviceWrapper::getAirconSleep(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getSleep();
    }
    return default_string;
}

/**
 * 获取模式
 */
string XlfDeviceWrapper::getAirconMode(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getMode();
    }
    return default_string;
}

/**
 * 获取开机
 */
string XlfDeviceWrapper::getAirconPower(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getPower();
    }
    return default_string;
}

/**
 * 获取风量
 */
/*风向*/
string XlfDeviceWrapper::getAirconWindDirection(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getWindDirection();
    }
    return default_string;
}

/**
 * 获取设置温度
 */
string XlfDeviceWrapper::getAirconSetingTemperature(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getSetingTemperature();
    }
    return default_string;
}

/**
 * 获取湿度
 */
string XlfDeviceWrapper::getAirconHumidity(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getHumidity();
    }
    return default_string;
}

/**
 * 获取体感室内温度
 */
string XlfDeviceWrapper::getAirconSomatosensoryRealityTemperature(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getSomatosensoryRealityTemperature();
    }
    return default_string;
}

/**
 * 获取室内实际温度
 */
string XlfDeviceWrapper::getAirconIndoorRealityTemperature(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getIndoorRealityTemperature();
    }
    return default_string;
}

/**
 * 获取室内盘管温度
 */
string XlfDeviceWrapper::getAirconIndoorPipeTemperature(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getIndoorPipeTemperature();
    }
    return default_string;
}

/**
 * 获取室内实际湿度值
 */
string XlfDeviceWrapper::getAirconIndoorRealityHumidity(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getIndoorRealityHumidity();
    }
    return default_string;
}

/**
 * 获取体感室内温度补偿
 */
string XlfDeviceWrapper::getAirconSomatosensoryCompensation(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getSomatosensoryCompensation();
    }
    return default_string;
}

/**
 * 获取体感控制
 */
string XlfDeviceWrapper::getAirconSomatosensoryContrl(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getSomatosensoryContrl();
    }
    return default_string;
}

/**
 * 获取自动工作模式和除湿模式的温度补偿
 */
string XlfDeviceWrapper::getAirconTemperatureCompensation(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getTemperatureCompensation();
    }
    return default_string;
}

/**
 * 获取华氏/摄氏温度显示设置
 */
string XlfDeviceWrapper::getAirconTemperatureValueSwitch(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getTemperatureValueSwitch();
    }
    return default_string;
}

/**
 * 获取普通定时开关机
 */
string XlfDeviceWrapper::getAirconGeneralTimingShutdownValue(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getGeneralTimingShutdownValue();
    }
    return default_string;
}

/**
 * 获取实时时钟的小时值
 */
string XlfDeviceWrapper::getAirconRealityHour(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getRealityHour();
    }
    return default_string;
}

/**
 * 获取实时时钟的分钟值
 */
string XlfDeviceWrapper::getAirconRealityMinute(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getRealityMinute();
    }
    return default_string;
}

/**
 * 获取实时开机控制
 */
string XlfDeviceWrapper::getAirconRealityBootContrl(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getRealityBootContrl();
    }
    return default_string;
}

/**
 * 获取实时开机小时
 */
string XlfDeviceWrapper::getAirconRealityBootHour(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getRealityBootHour();
    }
    return default_string;
}

/**
 * 获取实时开机分钟
 */
string XlfDeviceWrapper::getAirconRealityBootMinute(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getRealityBootMinute();
    }
    return default_string;
}

/**
 * 获取实时关机控制
 */
string XlfDeviceWrapper::getAirconRealityShutdownContrl(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getRealityShutdownContrl();
    }
    return default_string;
}

/**
 * 获取实时关机小时
 */
string XlfDeviceWrapper::getAirconRealityShutdownHour(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getRealityShutdownHour();
    }
    return default_string;
}

/**
 * 获取实时关机分钟
 */
string XlfDeviceWrapper::getAirconRealityShutdownMinute(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getRealityShutdownMinute();
    }
    return default_string;
}

/**
 * 获取除湿模式
 */
string XlfDeviceWrapper::getAirconDehumidificationMode(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getDehumidificationMode();
    }
    return default_string;
}

/**
 * 获取上下风门
 */
string XlfDeviceWrapper::getAirconVerticalWindMode(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getVerticalWindMode();
    }
    return default_string;
}

/**
 * 获取上下风开停控制
 */
string XlfDeviceWrapper::getAirconVerticalWindContrl(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getVerticalWindContrl();
    }
    return default_string;
}

/**
 * 获取左右风开停控制
 */
string XlfDeviceWrapper::getAirconHorizontalWindContrl(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getHorizontalWindContrl();
    }
    return default_string;
}

/**
 * 获取自然风开停控制
 */
string XlfDeviceWrapper::getAirconNatureWindContrl(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getNatureWindContrl();
    }
    return default_string;
}

/**
 * 获取电热
 */
string XlfDeviceWrapper::getAirconElectricalHeating(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getElectricalHeating();
    }
    return default_string;
}

/**
 * 获取节能
 */
string XlfDeviceWrapper::getAirconEnergyConservation(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getEnergyConservation();
    }
    return default_string;
}

/**
 * 获取并用节电
 */
string XlfDeviceWrapper::getAirconShare(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getShare();
    }
    return default_string;
}

/**
 * 获取高效
 */
string XlfDeviceWrapper::getAirconEfficient(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getEfficient();
    }
    return default_string;
}

/**
 * 获取双模
 */
string XlfDeviceWrapper::getAirconDualMode(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getDualMode();
    }
    return default_string;
}

/**
 * 获取清新
 */
string XlfDeviceWrapper::getAirconFreshness(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getFreshness();
    }
    return default_string;
}

/**
 * 获取换风
 */
string XlfDeviceWrapper::getAirconFreshAir(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getFreshAir();
    }
    return default_string;
}

/**
 * 获取室内清洁
 */
string XlfDeviceWrapper::getAirconClernIndoor(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getClernIndoor();
    }
    return default_string;
}

/**
 * 获取室外清洁
 */
string XlfDeviceWrapper::getAirconClernOutdoor(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getClernOutdoor();
    }
    return default_string;
}

/**
 * 获取智慧眼
 */
string XlfDeviceWrapper::getAirconSmartEye(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getSmartEye();
    }
    return default_string;
}

/**
 * 获取静音
 */
string XlfDeviceWrapper::getAirconMute(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getMute();
    }
    return default_string;
}

/**
 * 获取语音
 */
string XlfDeviceWrapper::getAirconVoice(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getVoice();
    }
    return default_string;
}

/**
 * 获取除烟
 */
string XlfDeviceWrapper::getAirconClernSmoke(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getClernSmoke();
    }
    return default_string;
}

/**
 * 获取背景灯
 */
string XlfDeviceWrapper::getAirconBackgroundLamp(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getBackgroundLamp();
    }
    return default_string;
}

/**
 * 获取显示屏发光
 */
string XlfDeviceWrapper::getAirconScreen(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getScreen();
    }
    return default_string;
}

/**
 * 获取LED指示灯
 */
string XlfDeviceWrapper::getAirconLED(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getLED();
    }
    return default_string;
}

/**
 * 获取室内外温度切换显示
 */
string XlfDeviceWrapper::getAirconIndoorOutdoorSwitch(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getIndoorOutdoorSwitch();
    }
    return default_string;
}

/**
 * 获取室内过滤网清洁复位控制
 */
string XlfDeviceWrapper::getAirconIndoorFilterClear(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getIndoorFilterClear();
    }
    return default_string;
}

/**
 * 获取左风摆
 */
string XlfDeviceWrapper::getAirconLeftWind(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getLeftWind();
    }
    return default_string;
}

/**
 * 获取右风摆
 */
string XlfDeviceWrapper::getAirconRightWind(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getRightWind();
    }
    return default_string;
}

/**
 * 获取室内电量板
 */
string XlfDeviceWrapper::getAirconChargeBorad (string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getChargeBorad();
    }
    return default_string;
}

/**
 * 获取本次命令之前是否有过红外遥控与按键控制过
 */
string XlfDeviceWrapper::getAirconHaveIRContrl(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getHaveIRContrl();
    }
    return default_string;
}

/**
 * 获取本次命令之前是否有过WIFI控制过
 */
string XlfDeviceWrapper::getAirconHaveWIFIContrl(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getHaveWIFIContrl();
    }
    return default_string;
}

/**
 * 获取空调正常机型与测试机型
 */
string XlfDeviceWrapper::getAirconModel(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getModel();
    }
    return default_string;
}

/**
 * 获取室内EEPROM在线升级
 */
string XlfDeviceWrapper::getAirconEEPROMUpdate(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getEEPROMUpdate();
    }
    return default_string;
}

/**
 * 获取室内温度传感器故障
 */
string XlfDeviceWrapper::getAirconIndoorTemperatureSensorTrouble(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getIndoorTemperatureSensorTrouble();
    }
    return default_string;
}

/**
 * 获取室内盘管温度传感器故障
 */
string XlfDeviceWrapper::getAirconIndoorPipeTemperatureSensorTrouble(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getIndoorPipeTemperatureSensorTrouble();
    }
    return default_string;
}

/**
 * 获取室内湿度传感器故障
 */
string XlfDeviceWrapper::getAirconIndoorHumiditySensorTrouble(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getIndoorHumiditySensorTrouble();
    }
    return default_string;
}

/**
 * 获取室内排水泵故障
 */
string XlfDeviceWrapper::getAirconIndoorDrainsWaterPumpTrouble(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getIndoorDrainsWaterPumpTrouble();
    }
    return default_string;
}

/**
 * 获取室内风机电机运转异常故障
 */
string XlfDeviceWrapper::getAirconIndoorFanMotorTrouble(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getIndoorFanMotorTrouble();
    }
    return default_string;
}

/**
 * 获取柜机格栅保护告警
 */
string XlfDeviceWrapper::getAirconPioneerGrillingProtectTrouble(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getPioneerGrillingProtectTrouble();
    }
    return default_string;
}

/**
 * 获取室内电压过零检测故障
 */
string XlfDeviceWrapper::getAirconIndoorVoltageZeroCrossDetectionTrouble(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getIndoorVoltageZeroCrossDetectionTrouble();
    }
    return default_string;
}

/**
 * 获取室内外通信故障
 */
string XlfDeviceWrapper::getAirconIndoorOutdoorCommunicationTrouble(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getIndoorOutdoorCommunicationTrouble();
    }
    return default_string;
}

/**
 * 获取室内控制板与显示板通信故障
 */
string XlfDeviceWrapper::getAirconIndoorContrlScreenCommunicationTrouble(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getIndoorContrlScreenCommunicationTrouble();
    }
    return default_string;
}

/**
 * 获取室内控制板与按键板通信故障
 */
string XlfDeviceWrapper::getAirconIndoorContrlKeypadCommunicationTrouble(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getIndoorContrlKeypadCommunicationTrouble();
    }
    return default_string;
}

/**
 * 获取WIFI控制板与室内控制板通信故障
 */
string XlfDeviceWrapper::getAirconIndoorContrlWIFICommunicationTrouble(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getIndoorContrlWIFICommunicationTrouble();
    }
    return default_string;
}

/**
 * 获取室内控制板与室内电量板通信故障
 */
string XlfDeviceWrapper::getAirconIndoorContrlChargeCommunicationTrouble(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getIndoorContrlChargeCommunicationTrouble();
    }
    return default_string;
}

/**
 * 获取室内控制板EEPROM出错
 */
string XlfDeviceWrapper::getAirconIndoorContrlEEPROMTrouble(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getIndoorContrlEEPROMTrouble();
    }
    return default_string;
}

/**
 * 获取运行频率
 */
string XlfDeviceWrapper::getAirconRunFrequency(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getRunFrequency();
    }
    return default_string;
}

/**
 * 获取目标频率
 */
string XlfDeviceWrapper::getAirconTargetFrequency(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getTargetFrequency();
    }
    return default_string;
}

/**
 * 获取发给驱动器的频率
 */
string XlfDeviceWrapper::getAirconDriveFrequency(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getDriveFrequency();
    }
    return default_string;
}

/**
 * 获取环境温度
 */
string XlfDeviceWrapper::getAirconEnvironmentTemperature(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getEnvironmentTemperature();
    }
    return default_string;
}

/**
 * 获取冷凝器温度
 */
string XlfDeviceWrapper::getAirconCondenserTemperature(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getCondenserTemperature();
    }
    return default_string;
}

/**
 * 获取排气温度
 */
string XlfDeviceWrapper::getAirconExhaustTemperature(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getExhaustTemperature();
    }
    return default_string;
}

/**
 * 获取目标排气温度
 */
string XlfDeviceWrapper::getAirconTargetExhaustTemperature(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getTargetExhaustTemperature();
    }
    return default_string;
}

/**
 * 获取室外电子膨胀阀开度
 */
string XlfDeviceWrapper::getAirconOutdoorElectronicExpansion(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getOutdoorElectronicExpansion();
    }
    return default_string;
}

/**
 * 获取UABH
 */
string XlfDeviceWrapper::getAirconUABH(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getUABH();
    }
    return default_string;
}

/**
 * 获取UABL
 */
string XlfDeviceWrapper::getAirconUABL(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getUABL();
    }
    return default_string;
}

/**
 * 获取UBCH
 */
string XlfDeviceWrapper::getAirconUBCH(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getUBCH();
    }
    return default_string;
}

/**
 * 获取UBCL
 */
string XlfDeviceWrapper::getAirconUBCL(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getUBCL();
    }
    return default_string;
}

/**
 * 获取UCAH
 */
string XlfDeviceWrapper::getAirconUCAH(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getUCAH();
    }
    return default_string;
}

/**
 * 获取UCAL
 */
string XlfDeviceWrapper::getAirconUCAL(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getUCAL();
    }
    return default_string;
}

/**
 * 获取IAB
 */
string XlfDeviceWrapper::getAirconIAB(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getIAB();
    }
    return default_string;
}

/**
 * 获取IBC
 */
string XlfDeviceWrapper::getAirconIBC(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getIBC();
    }
    return default_string;
}

/**
 * 获取ICA
 */
string XlfDeviceWrapper::getAirconICA(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getICA();
    }
    return default_string;
}

/**
 * 获取IUV
 */
string XlfDeviceWrapper::getAirconIUV(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getIUV();
    }
    return default_string;
}

/**
 * 获取直流母线电压H
 */
string XlfDeviceWrapper::getAirconCocurrentBusVoltageH(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getCocurrentBusVoltageH();
    }
    return default_string;
}

/**
 * 获取直流母线电压L
 */
string XlfDeviceWrapper::getAirconCocurrentBusVoltageL(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getCocurrentBusVoltageL();
    }
    return default_string;
}

/**
 * 获取四通阀状态
 */
string XlfDeviceWrapper::getAirconFourWayLimen(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getFourWayLimen();
    }
    return default_string;
}

/**
 * 获取室外机实际工作状态
 */
string XlfDeviceWrapper::getAirconOutdoorRealityRuning(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getOutdoorRealityRuning();
    }
    return default_string;
}

/**
 * 获取风机运行状态
 */
string getFanRuning();

/**
 * 获取室外机强制室内机风门位置
 */
string XlfDeviceWrapper::getAirconOutdoorForceIndoorWindPosition(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getOutdoorForceIndoorWindPosition();
    }
    return default_string;
}

/**
 * 获取室外机强制室内机风速
 */
string XlfDeviceWrapper::getAirconOutdoorForceIndoorWindSpeed(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getOutdoorForceIndoorWindSpeed();
    }
    return default_string;
}

/**
 * 获取室外机强制室内机停
 */
string XlfDeviceWrapper::getAirconOutdoorForceIndoorStop(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getOutdoorForceIndoorStop();
    }
    return default_string;
}

/**
 * 获取温控关机
 */
string XlfDeviceWrapper::getAirconShutdownByTemperatureContrl(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getShutdownByTemperatureContrl();
    }
    return default_string;
}

/**
 * 获取一拖多标志
 */
string XlfDeviceWrapper::getAirconOne4All(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getOne4All();
    }
    return default_string;
}

/**
 * 获取除湿阀标志
 */
string XlfDeviceWrapper::getAirconDehumidifierLimen(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getDehumidifierLimen();
    }
    return default_string;
}

/**
 * 获取室外机化霜
 */
string XlfDeviceWrapper::getAirconOutdoorDefrosting(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getOutdoorDefrosting();
    }
    return default_string;
}

/**
 * 获取室外旁通化霜
 */
string XlfDeviceWrapper::getAirconOutdoorBypassDefrosting(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getOutdoorBypassDefrosting();
    }
    return default_string;
}

/**
 * 获取回油标志
 */
string XlfDeviceWrapper::getAirconOilReturn(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getOilReturn();
    }
    return default_string;
}

/**
 * 获取室外故障显示标志
 */
string XlfDeviceWrapper::getAirconOutdoorTroubleDisplay(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getOutdoorTroubleDisplay();
    }
    return default_string;
}

/**
 * 获取室外机EEPROM在线下载标志
 */
string XlfDeviceWrapper::getAirconOutdoorEEPROMDownload(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getOutdoorEEPROMDownload();
    }
    return default_string;
}

/**
 * 获取室外机电量板
 */
string XlfDeviceWrapper::getAirconOutdoorChargeBoard(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getOutdoorChargeBoard();
    }
    return default_string;
}

/**
 * 获取压缩机电热带
 */
string XlfDeviceWrapper::getAirconcompressorRibbonHeater(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getcompressorRibbonHeater();
    }
    return default_string;
}

/**
 * 获取
 */
/*压缩机预加热*/
string XlfDeviceWrapper::getAirconcompressorBeforeHandheat(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getcompressorBeforeHandheat();
    }
    return default_string;
}

/**
 * 获取补气增晗
 */
string XlfDeviceWrapper::getAirconReinflation(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getReinflation();
    }
    return default_string;
}

/**
 * 获取室内外机模式冲突
 */
string XlfDeviceWrapper::getAirconOutdoorModeClash(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getOutdoorModeClash();
    }
    return default_string;
}

/**
 * 获取室外EEPROM出错
 */
string XlfDeviceWrapper::getAirconOutdoorEEPROMTrouble(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getOutdoorEEPROMTrouble();
    }
    return default_string;
}

/**
 * 获取室外盘管温度传感器故障
 */
string XlfDeviceWrapper::getAirconOutdoorPipeTemperatureSensorTrouble(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getOutdoorPipeTemperatureSensorTrouble();
    }
    return default_string;
}

/**
 * 获取排气温度传感器故障
 */
string XlfDeviceWrapper::getAirconOutdoorExhausTemperatureSensorTrouble(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getOutdoorExhausTemperatureSensorTrouble();
    }
    return default_string;
}

/**
 * 获取室外环境温度传感器故障
 */
string XlfDeviceWrapper::getAirconOutdoorEnvironmentTemperatureSensorTrouble(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getOutdoorEnvironmentTemperatureSensorTrouble();
    }
    return default_string;
}

/**
 * 获取电压变压器故障
 */
string XlfDeviceWrapper::getAirconVoltageTransformerTrouble(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getVoltageTransformerTrouble();
    }
    return default_string;
}

/**
 * 获取电流互感器故障
 */
string XlfDeviceWrapper::getAirconCurrentTransformerTrouble(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getCurrentTransformerTrouble();
    }
    return default_string;
}

/**
 * 获取室外控制与驱动通信故障
 */
string XlfDeviceWrapper::getAirconOutdoorContrlDriveCommunicationTrouble(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getOutdoorContrlDriveCommunicationTrouble();
    }
    return default_string;
}

/**
 * 获取IPM模块过流保护
 */
string XlfDeviceWrapper::getAirconIPMOvercurrentProtect(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getIPMOvercurrentProtect();
    }
    return default_string;
}

/**
 * 获取IPM模块过热保护
 */
string XlfDeviceWrapper::getAirconIPMOverheatingProtect(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getIPMOverheatingProtect();
    }
    return default_string;
}

/**
 * 获取交流电过电压保护
 */
string XlfDeviceWrapper::getAirconAlternatingCurrentOvervoltageProtect(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getAlternatingCurrentOvervoltageProtect();
    }
    return default_string;
}

/**
 * 获取交流电欠电压保护
 */
string XlfDeviceWrapper::getAirconAlternatingCurrentUndervoltageProtect(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getAlternatingCurrentUndervoltageProtect();
    }
    return default_string;
}

/**
 * 获取母线电压过电压保护
 */
string XlfDeviceWrapper::getAirconBusbarVoltageOvervoltageProtect(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getBusbarVoltageOvervoltageProtect();
    }
    return default_string;
}

/**
 * 获取
 */
/*母线电压欠电压保护*/
string XlfDeviceWrapper::getAirconBusbarVoltageUndervoltageProtect(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getBusbarVoltageUndervoltageProtect();
    }
    return default_string;
}

/**
 * 获取PFC过电流保护
 */
string XlfDeviceWrapper::getAirconPFCOvercurrentProtect(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getPFCOvercurrentProtect();
    }
    return default_string;
}

/**
 * 获取室外机最大电流保护
 */
string XlfDeviceWrapper::getAirconOutdoorMaximumCurrentProtect(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getOutdoorMaximumCurrentProtect();
    }
    return default_string;
}

/**
 * 获取室外环境温度过低保护
 */
string XlfDeviceWrapper::getAirconOutdooEnvironmentOvertemperatureProtect(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getOutdooEnvironmentOvertemperatureProtect();
    }
    return default_string;
}

/**
 * 获取排气温度过高保护
 */
string XlfDeviceWrapper::getAirconExhaustOvertemperatureProtect(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getExhaustOvertemperatureProtect();
    }
    return default_string;
}

/**
 * 获取压缩机管壳温度保护
 */
string XlfDeviceWrapper::getAirconCompressoPipeShellTemperatureProtect(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getCompressoPipeShellTemperatureProtect();
    }
    return default_string;
}

/**
 * 获取室内防冻结或防过载保护
 */
string XlfDeviceWrapper::getAirconIndoorAntiFreezingProtect(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getIndoorAntiFreezingProtect();
    }
    return default_string;
}

/**
 * 室外机PFC保护
 */
string XlfDeviceWrapper::getAirconOutdoorPFCProtect(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getOutdoorPFCProtect();
    }
    return default_string;
}

/**
 * 压缩机启动失败
 */
string XlfDeviceWrapper::getAirconCompressoBootFail(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getCompressoBootFail();
    }
    return default_string;
}

/**
 * 获取压缩机失步
 */
string XlfDeviceWrapper::getAirconCompressoStepOut(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getCompressoStepOut();
    }
    return default_string;
}

/**
 * 获取室外风机堵转
 */
string XlfDeviceWrapper::getAirconOutdoorFanLockRotor(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getOutdoorFanLockRotor();
    }
    return default_string;
}

/**
 * 获取室外盘管防过载保护
 */
string XlfDeviceWrapper::getAirconOutdoorPieOverloadProtect(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getOutdoorPieOverloadProtect();
    }
    return default_string;
}

/**
 * 获取冷媒泄漏
 */
string XlfDeviceWrapper::getAirconRefrigerantLeakage(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getRefrigerantLeakage();
    }
    return default_string;
}

/**
 * 获取压缩机型号匹配错误
 */
string XlfDeviceWrapper::getAirconCompressoModelMismatch(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getCompressoModelMismatch();
    }
    return default_string;
}

/**
 * 获取系统低频振动保护
 */
string XlfDeviceWrapper::getAirconSystemLowFrequencyVibrationProtect(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getSystemLowFrequencyVibrationProtect();
    }
    return default_string;
}

/**
 * 获取室外散热器温度过高保护
 */
string XlfDeviceWrapper::getAirconOutdoorRadiatorOvertemperatureProtect(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getOutdoorRadiatorOvertemperatureProtect();
    }
    return default_string;
}

/**
 * 获取系统压力过高保护
 */
string XlfDeviceWrapper::getAirconSystemHypertonusProtect(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getSystemHypertonusProtect();
    }
    return default_string;
}

/**
 * 获取逆变器直流过电压故障
 */
string XlfDeviceWrapper::getAirconInverterCocurrentOvervoltageTrouble(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getInverterCocurrentOvervoltageTrouble();
    }
    return default_string;
}

/**
 * 获取逆变器直流低电压故障
 */
string XlfDeviceWrapper::getAirconInverterCocurrentUndervoltageTrouble(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getInverterCocurrentUndervoltageTrouble();
    }
    return default_string;
}

/**
 * 获取逆变器交流过电流故障
 */
string XlfDeviceWrapper::getAirconInverterCocurrentOvercurrentTrouble(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getInverterCocurrentOvercurrentTrouble();
    }
    return default_string;
}

/**
 * 获取失步检出
 */
string XlfDeviceWrapper::getAirconStepOutDetection(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getStepOutDetection();
    }
    return default_string;
}

/**
 * 获取速度推定脉冲检出法检出欠相故障
 */
string XlfDeviceWrapper::getAirconSpeedPulseFault(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getSpeedPulseFault();
    }
    return default_string;
}

/**
 * 获取电流推定脉冲检出法检出欠相故障
 */
string XlfDeviceWrapper::getAirconCurrentPulseFault(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getCurrentPulseFault();
    }
    return default_string;
}

/**
 * 获取逆变器IPM故障-边沿
 */
string XlfDeviceWrapper::getAirconInverterEdgeFault(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getInverterEdgeFault();
    }
    return default_string;
}

/**
 * 获取逆变器IPM故障-电平
 */
string XlfDeviceWrapper::getAirconInverterLevelFault(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getInverterLevelFault();
    }
    return default_string;
}

/**
 * 获取PFC_IPM故障-边沿
 */
string XlfDeviceWrapper::getAirconPFC_IPMEdgeFault(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getPFC_IPMEdgeFault();
    }
    return default_string;
}

/**
 * 获取PFC_IPM故障-电平
 */
string XlfDeviceWrapper::getAirconPFC_IPMLevelFault(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getPFC_IPMLevelFault();
    }
    return default_string;
}

/**
 * 获取PFC停电检出故障
 */
string XlfDeviceWrapper::getAirconPFCPowerCutFault(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getPFCPowerCutFault();
    }
    return default_string;
}

/**
 * 获取PFC过电流检出故障
 */
string XlfDeviceWrapper::getAirconFCOvercurrentFault(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getPFCOvercurrentFault();
    }
    return default_string;
}

/**
 * 获取直流电压检出异常
 */
string XlfDeviceWrapper::getAirconDCVException(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getDCVException();
    }
    return default_string;
}

/**
 * 获取PFC低电压（有效值）检出故障
 */
string XlfDeviceWrapper::getAirconPFCLowVoltageFault(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getPFCLowVoltageFault();
    }
    return default_string;
}

/**
 * 获取AD偏置异常检出故障
 */
string XlfDeviceWrapper::getAirconADOffsetAnomaliesFault(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getADOffsetAnomaliesFault();
    }
    return default_string;
}

/**
 * 获取逆变器PWM逻辑设置故障
 */
string XlfDeviceWrapper::getAirconInverterPWMLogicFault(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getInverterPWMLogicFault();
    }
    return default_string;
}

/**
 * 获取逆变器PWM初始化故障
 */
string XlfDeviceWrapper::getAirconInverterPWMInitFault(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getInverterPWMInitFault();
    }
    return default_string;
}

/**
 * 获取PFC_PWM逻辑设置故障
 */
string XlfDeviceWrapper::getAirconPFCPWMLogicFault(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getPFCPWMLogicFault();
    }
    return default_string;
}

/**
 * 获取PFC_PWM初始化故障
 */
string XlfDeviceWrapper::getAirconPFC_PWMInitFault(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getPFC_PWMInitFault();
    }
    return default_string;
}

/**
 * 获取温度异常
 */
string XlfDeviceWrapper::getAirconTemperatureAnomaly(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getTemperatureAnomaly();
    }
    return default_string;
}

/**
 * 获取电流采样电阻不平衡调整故障
 */
string XlfDeviceWrapper::getAirconCurrentSamplingFault(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getCurrentSamplingFault();
    }
    return default_string;
}

/**
 * 获取电机参数设置故障
 */
string XlfDeviceWrapper::getAirconMotorDataFault(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getMotorDataFault();
    }
    return default_string;
}

/**
 * 获取MCE故障
 */
string XlfDeviceWrapper::getAirconMCEFault(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getMCEFault();
    }
    return default_string;
}

/**
 * 获取驱动EEPROM故障
 */
string XlfDeviceWrapper::getAirconEEPROMFault(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getEEPROMFault();
    }
    return default_string;
}

/**
 * 获取室外盘管过载禁升频
 */
string XlfDeviceWrapper::getAirconOutdoorCoilOverloadUpFrequency(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getOutdoorCoilOverloadUpFrequency();
    }
    return default_string;
}

/**
 * 获取室外盘管过载降频
 */
string XlfDeviceWrapper::getAirconOutdoorCoilOverloadDownFrequency(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getOutdoorCoilOverloadDownFrequency();
    }
    return default_string;
}

/**
 * 获取室内盘管过载禁升频
 */
string XlfDeviceWrapper::getAirconIndoorCoilOverloadUpFrequency(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getIndoorCoilOverloadUpFrequency();
    }
    return default_string;
}

/**
 * 获取室内盘管过载降频
 */
string XlfDeviceWrapper::getAirconIndoorCoilOverloadDownFrequency(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getIndoorCoilOverloadDownFrequency();
    }
    return default_string;
}

/**
 * 获取压降排气过载禁升频
 */
string XlfDeviceWrapper::getAirconPressureUpFrequency(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getPressureUpFrequency();
    }
    return default_string;
}

/**
 * 获取压降排气过载降频
 */
string XlfDeviceWrapper::getAirconPressureDownFrequency(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getPressureDownFrequency();
    }
    return default_string;
}

/**
 * 获取室内盘管冻结禁升频
 */
string XlfDeviceWrapper::getAirconIndoorCoilFreezingUpFrequency(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getIndoorCoilFreezingUpFrequency();
    }
    return default_string;
}

/**
 * 获取室内盘管冻结降频
 */
string XlfDeviceWrapper::getAirconIndoorCoilFreezingDownFrequency(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getIndoorCoilFreezingDownFrequency();
    }
    return default_string;
}

/**
 * 获取室内外通信降频
 */
string XlfDeviceWrapper::getAirconCommunicationDownFrequency(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getCommunicationDownFrequency();
    }
    return default_string;
}

/**
 * 获取模块温度过载限频
 */
string XlfDeviceWrapper::getAirconModuleTemperaturelimitFrequency(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getModuleTemperaturelimitFrequency();
    }
    return default_string;
}

/**
 * 获取变调率限频
 */
string XlfDeviceWrapper::getAirconModulationRatelimitFrequency(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getModulationRatelimitFrequency();
    }
    return default_string;
}

/**
 * 获取相电流限频
 */
string XlfDeviceWrapper::getAirconPhaseCurrentlimitFrequency(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getPhaseCurrentlimitFrequency();
    }
    return default_string;
}

/**
 * 获取并用节电保护禁升频
 */
string XlfDeviceWrapper::getAirconPowerSaveUpFrequency(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getPowerSaveUpFrequency();
    }
    return default_string;
}

/**
 * 获取并用节电保护降频
 */
string XlfDeviceWrapper::getAirconPowerSaveDownFrequency(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getPowerSaveDownFrequency();
    }
    return default_string;
}

/**
 * 获取过电流保护禁升频
 */
string XlfDeviceWrapper::getAirconOvercurrentUpFrequency(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getOvercurrentUpFrequency();
    }
    return default_string;
}

/**
 * 获取过电流保护降频
 */
string XlfDeviceWrapper::getAirconOvercurrentDownFrequency(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getOvercurrentDownFrequency();
    }
    return default_string;
}

/**
 * 获取室内风机转速xx
 */
string XlfDeviceWrapper::getAirconIndoorFanSpeedH(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getIndoorFanSpeedH();
    }
    return default_string;
}

/**
 * 获取室内风机转速00xx
 */
string XlfDeviceWrapper::getAirconIndoorFanSpeed00L(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getIndoorFanSpeed00L();
    }
    return default_string;
}

/**
 * 获取有否PM2.5检测功能
 */
string XlfDeviceWrapper::getAirconPM25(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getPM25();
    }
    return default_string;
}

/**
 * 获取PM2.5污染程度
 */
string XlfDeviceWrapper::getAirconPM25Level(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getPM25Level();
    }
    return default_string;
}

/**
 * 获取空气PM2.5质量百分比表示
 */
string XlfDeviceWrapper::getAirconPM25Percent(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getPM25Percent();
    }
    return default_string;
}

/**
 * 获取显示屏亮度值
 */
string XlfDeviceWrapper::getAirconScreenLuminance(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getScreenLuminance();
    }
    return default_string;
}

/**
 * 获取普通定时开关机有效
 */
string XlfDeviceWrapper::getAirconGeneralTimingShutdown(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getGeneralTimingShutdown();
    }
    return default_string;
}

/************************** function **************************/
/**
 * 设置睡眠模式
 */
int XlfDeviceWrapper::getAirconSleepModeFN(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getSleepModeFN();
    }
    return 0;
}

/**
 * 设置模式
 */
int XlfDeviceWrapper::getAirconCoolModeFN(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getCoolModeFN();
    }
    return 0;
}

/**
 * 开/关机
 */
int XlfDeviceWrapper::getAirconPowerFN(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getPowerFN();
    }
    return 0;
}

/**
 * 室内单个风向控制功能
 */
int XlfDeviceWrapper::getAirconWindDirectionFN(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getWindDirectionFN();
    }
    return 0;
}

/**
 * 设置温度
 */
int XlfDeviceWrapper::getAirconTemperatureFN(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getTemperatureFN();
    }
    return 0;
}

/**
 * 设置湿度
 */
int XlfDeviceWrapper::getAirconHumidityFN(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getHumidityFN();
    }
    return 0;
}

/**
 * 体感控制,体感室内温度,体感室内温度补偿
 */
int XlfDeviceWrapper::getAirconSomatosensoryRealityTemperatureFN(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getSomatosensoryRealityTemperatureFN();
    }
    return 0;
}

/**
 * 自动工作模式和除湿模式的温度补偿
 */
int XlfDeviceWrapper::getAirconTemperatureCompensationFN(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getTemperatureCompensationFN();
    }
    return 0;
}

/**
 * 华氏/摄氏温度显示设置
 */
int XlfDeviceWrapper::getAirconTemperatureValueSwitchFN(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getTemperatureValueSwitchFN();
    }
    return 0;
}

/**
 * 普通定时关机,普通定时关机时间
 */
int XlfDeviceWrapper::getAirconGeneralTimingShutdownFN(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getGeneralTimingShutdownFN();
    }
    return 0;
}

/**
 * 实时开机控制,实时时钟的小时值,实时时钟的分钟值,实时开机小时,实时开机分钟
 */
int XlfDeviceWrapper::getAirconRealityTimeFN(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getRealityTimeFN();
    }
    return 0;
}

/**
 * 6位置可定室内风门位置控制
 */
int XlfDeviceWrapper::getAirconVerticalWindModeNum(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getVerticalWindModeNum();
    }
    return 0;
}

/**
 * 上下风门模式,上下风开停控制
 */
int XlfDeviceWrapper::getAirconVerticalWindFN(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getVerticalWindFN();
    }
    return 0;
}

/**
 * 左右风开停控制,左风摆,右风摆
 */
int XlfDeviceWrapper::getAirconHorizontalWindFN(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getHorizontalWindFN();
    }
    return 0;
}

/**
 * 自然风开停
 */
int XlfDeviceWrapper::getAirconNatureWindFN(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getNatureWindFN();
    }
    return 0;
}

/**
 * 设置电加热
 */
int XlfDeviceWrapper::getAirconElectricalHeatingFN(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getElectricalHeatingFN();
    }
    return 0;
}

/**
 * 除湿模式
 */
int XlfDeviceWrapper::getAirconDehumidificationModeFN(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getDehumidificationModeFN();
    }
    return 0;
}

/**
 * 设置节能
 */
int XlfDeviceWrapper::getAirconEnergyConservationFN(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getEnergyConservationFN();
    }
    return 0;
}

/**
 * 设置并且节能
 */
int XlfDeviceWrapper::getAirconShareFN(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getShareFN();
    }
    return 0;
}

/**
 * 设置高效
 */
int XlfDeviceWrapper::getAirconEfficientFN(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getEfficientFN();
    }
    return 0;
}

/**
 * 设置双模
 */
int XlfDeviceWrapper::getAirconDualModeFN(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getDualModeFN();
    }
    return 0;
}

/**
 * 设置清新
 */
int XlfDeviceWrapper::getAirconFreshnessFN(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getFreshnessFN();
    }
    return 0;
}

/**
 * 设置换风
 */
int XlfDeviceWrapper::getAirconFreshAirFN(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getFreshAirFN();
    }
    return 0;
}

/**
 * 设置室内清洁
 */
int XlfDeviceWrapper::getAirconClernIndoorFN(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getClernIndoorFN();
    }
    return 0;
}

/**
 * 设置室外清洁
 */
int XlfDeviceWrapper::getAirconClernOutdoorFN(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getClernOutdoorFN();
    }
    return 0;
}

/**
 * 设置室智能眼
 */
int XlfDeviceWrapper::getAirconSmartEyeFN(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getSmartEyeFN();
    }
    return 0;
}

/**
 * 设置室静音
 */
int XlfDeviceWrapper::getAirconMuteFN(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getMuteFN();
    }
    return 0;
}

/**
 * 设置语音
 */
int XlfDeviceWrapper::getAirconVoiceFN(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getVoiceFN();
    }
    return 0;
}

/**
 * 设置除烟
 */
int XlfDeviceWrapper::getAirconClernSmokeFN(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getClernSmokeFN();
    }
    return 0;
}

/**
 * 背景灯
 */
int XlfDeviceWrapper::getAirconBackgroundLampFN(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getBackgroundLampFN();
    }
    return 0;
}

/**
 * 显示屏发光
 */
int XlfDeviceWrapper::getAirconScreenFN(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getScreenFN();
    }
    return 0;
}

/**
 * LED指示灯
 */
int XlfDeviceWrapper::getAirconLEDFN(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getLEDFN();
    }
    return 0;
}

/**
 * 室内外温度切换显示
 */
int XlfDeviceWrapper::getAirconIndoorOutdoorSwitchFN(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getIndoorOutdoorSwitchFN();
    }
    return 0;
}

/**
 * 室内过滤网清洁复位控制
 */
int XlfDeviceWrapper::getAirconIndoorFilterClearFN(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getIndoorFilterClearFN();
    }
    return 0;
}

/**
 * 左风摆开停控制
 */
int XlfDeviceWrapper::getAirconLeftFanContrlFN(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getLeftFanContrlFN();
    }
    return 0;
}

/**
 * 右风摆开停控制
 */
int XlfDeviceWrapper::getAirconRightFanContrlFN(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getRightFanContrlFN();
    }
    return 0;
}

/**
 * 控制规则
 */
int XlfDeviceWrapper::getAirconContrlRate(string deviceId)
{
    AirconditionControl *airconditionControl = (AirconditionControl *)getDeviceControl(deviceId);
    if(NULL != airconditionControl)
    {
        return airconditionControl->getContrlRate();
    }
    return 0;
}

/**************************  dehumidifierControl  **************************/
/**
 * 1.直接设置 开/关机
 * 取消普通定时,取消实时关机,取消快速冷热,取消睡眠,取消左右风,取消电热,取消节能,取消净化,取消双模,取消显示,取消亮度
 */
string XlfDeviceWrapper::setDehumidifierDirctPower(string deviceId, int power, int  soundSet)
{
    DehumidifierControl *dehumidifierControl = (DehumidifierControl *)getDeviceControl(deviceId);
    if(NULL != dehumidifierControl)
    {
        return dehumidifierControl->setDirctPower(power, soundSet);
    }
    return default_string;
}

/**
 * 2.设置风速
 */
string XlfDeviceWrapper::setDehumidifierWindSpeed(string deviceId, string speed, int soundSet)
{
    DehumidifierControl *dehumidifierControl = (DehumidifierControl *)getDeviceControl(deviceId);
    if(NULL != dehumidifierControl)
    {
        return dehumidifierControl->setWindSpeed(speed, soundSet);
    }
    return default_string;
}

/**
 * 3.设置模式
 */
string XlfDeviceWrapper::setDehumidifierMode(string deviceId, string mode, int soundSet)
{
    DehumidifierControl *dehumidifierControl = (DehumidifierControl *)getDeviceControl(deviceId);
    if(NULL != dehumidifierControl)
    {
        return dehumidifierControl->setMode(mode, soundSet);
    }
    return default_string;
}

/**
 * 4.定时开关机
 */
string XlfDeviceWrapper::setDehumidifierTimerControl(string deviceId, int enable, string time, int soundSet)
{
    DehumidifierControl *dehumidifierControl = (DehumidifierControl *)getDeviceControl(deviceId);
    if(NULL != dehumidifierControl)
    {
        return dehumidifierControl->setTimerControl(enable, time, soundSet);
    }
    return default_string;
}

/**
 * 5.设置湿度
 */
string XlfDeviceWrapper::setDehumidifierHumidity(string deviceId, int humidity, int soundSet)
{
    DehumidifierControl *dehumidifierControl = (DehumidifierControl *)getDeviceControl(deviceId);
    if(NULL != dehumidifierControl)
    {
        return dehumidifierControl->setHumidity(humidity, soundSet);
    }
    return default_string;
}

/**
 * 6.设置温度
 */
string XlfDeviceWrapper::setDehumidifierTemperature(string deviceId, int temperature, int soundSet)
{
    DehumidifierControl *dehumidifierControl = (DehumidifierControl *)getDeviceControl(deviceId);
    if(NULL != dehumidifierControl)
    {
        return dehumidifierControl->setTemperature(temperature, soundSet);
    }
    return default_string;
}

/**
 * 7.设置开关电源
 */
string XlfDeviceWrapper::setDehumidifierPower(string deviceId, int power, int soundSet)
{
    DehumidifierControl *dehumidifierControl = (DehumidifierControl *)getDeviceControl(deviceId);
    if(NULL != dehumidifierControl)
    {
        return dehumidifierControl->setPower(power, soundSet);
    }
    return default_string;
}

/**
 * 8.设置开关电加热
 */
string XlfDeviceWrapper::setDehumidifierEletricHeatControl(string deviceId, int isEletricHeatOn, int soundSet)
{
    DehumidifierControl *dehumidifierControl = (DehumidifierControl *)getDeviceControl(deviceId);
    if(NULL != dehumidifierControl)
    {
        return dehumidifierControl->setEletricHeatControl(isEletricHeatOn, soundSet);
    }
    return default_string;
}

/**
 * 9.设置开关水泵
 */
string XlfDeviceWrapper::setDehumidifierWaterPumpControl(string deviceId, int enable, int soundSet)
{
    DehumidifierControl *dehumidifierControl = (DehumidifierControl *)getDeviceControl(deviceId);
    if(NULL != dehumidifierControl)
    {
        return dehumidifierControl->setWaterPumpControl(enable, soundSet);
    }
    return default_string;
}

/**
 * 10.设置开关负离子
 */
string XlfDeviceWrapper::setDehumidifierNegativeIonsControl(string deviceId, int enable, int soundSet)
{
    DehumidifierControl *dehumidifierControl = (DehumidifierControl *)getDeviceControl(deviceId);
    if(NULL != dehumidifierControl)
    {
        return dehumidifierControl->setNegativeIonsControl(enable, soundSet);
    }
    return default_string;
}

/**
 * 11.设置CSSBox
 */
string XlfDeviceWrapper::setDehumidifierCSSBox(string deviceId, int on,string Mode,string WindSpeed_value,int humidity,int soundSet)
{
    DehumidifierControl *dehumidifierControl = (DehumidifierControl *)getDeviceControl(deviceId);
    if(NULL != dehumidifierControl)
    {
        return dehumidifierControl->setCSSBox(on, Mode,WindSpeed_value,humidity,soundSet);
    }
    return default_string;
}

/**
 * 智慧风
 */
int XlfDeviceWrapper::getDehumidifierSmartWindFN(string deviceId)
{
    DehumidifierControl *dehumidifierControl = (DehumidifierControl *)getDeviceControl(deviceId);
    if(NULL != dehumidifierControl)
    {
        return dehumidifierControl->getSmartWindFN();
    }
    return default_int;
}

/**
 * 高风
 */
int XlfDeviceWrapper::getDehumidifierHighWindFN(string deviceId)
{
    DehumidifierControl *dehumidifierControl = (DehumidifierControl *)getDeviceControl(deviceId);
    if(NULL != dehumidifierControl)
    {
        return dehumidifierControl->getHighWindFN();
    }
    return default_int;
}

/**
 * 中风
 */
int XlfDeviceWrapper::getDehumidifierMediumWindFN(string deviceId)
{
    DehumidifierControl *dehumidifierControl = (DehumidifierControl *)getDeviceControl(deviceId);
    if(NULL != dehumidifierControl)
    {
        return dehumidifierControl->getMediumWindFN();
    }
    return default_int;
}

/**
 * 低风
 */
int XlfDeviceWrapper::getDehumidifierLowWindFN(string deviceId)
{
    DehumidifierControl *dehumidifierControl = (DehumidifierControl *)getDeviceControl(deviceId);
    if(NULL != dehumidifierControl)
    {
        return dehumidifierControl->getLowWindFN();
    }
    return default_int;
}

/**
 * 运行模式 持续运行
 */
int XlfDeviceWrapper::getDehumidifierContinueModeFN(string deviceId)
{
    DehumidifierControl *dehumidifierControl = (DehumidifierControl *)getDeviceControl(deviceId);
    if(NULL != dehumidifierControl)
    {
        return dehumidifierControl->getContinueModeFN();
    }
    return default_int;
}

/**
 * 运行模式 正常运行
 */
int XlfDeviceWrapper::getDehumidifierNormalModeFN(string deviceId)
{
    DehumidifierControl *dehumidifierControl = (DehumidifierControl *)getDeviceControl(deviceId);
    if(NULL != dehumidifierControl)
    {
        return dehumidifierControl->getNormalModeFN();
    }
    return default_int;
}

/**
 * 运行模式 自动运行
 */
int XlfDeviceWrapper::getDehumidifierAutoModeFN(string deviceId)
{
    DehumidifierControl *dehumidifierControl = (DehumidifierControl *)getDeviceControl(deviceId);
    if(NULL != dehumidifierControl)
    {
        return dehumidifierControl->getAutoModeFN();
    }
    return default_int;
}

/**
 * 定时
 */
int XlfDeviceWrapper::getDehumidifierTimerControlFN(string deviceId)
{
    DehumidifierControl *dehumidifierControl = (DehumidifierControl *)getDeviceControl(deviceId);
    if(NULL != dehumidifierControl)
    {
        return dehumidifierControl->getTimerControlFN();
    }
    return default_int;
}

/**
 * 电加热
 */
int XlfDeviceWrapper::getDehumidifierElectricHeatFN(string deviceId)
{
    DehumidifierControl *dehumidifierControl = (DehumidifierControl *)getDeviceControl(deviceId);
    if(NULL != dehumidifierControl)
    {
        return dehumidifierControl->getElectricHeatFN();
    }
    return default_int;
}

/**
 * 电加热 温度
 */
int XlfDeviceWrapper::getDehumidifierElectricHeatSetTemperatureFN(string deviceId)
{
    DehumidifierControl *dehumidifierControl = (DehumidifierControl *)getDeviceControl(deviceId);
    if(NULL != dehumidifierControl)
    {
        return dehumidifierControl->getElectricHeatSetTemperatureFN();
    }
    return default_int;
}

/**
 * 室内湿度
 */
int XlfDeviceWrapper::getDehumidifierIndoorHumidityFN(string deviceId)
{
    DehumidifierControl *dehumidifierControl = (DehumidifierControl *)getDeviceControl(deviceId);
    if(NULL != dehumidifierControl)
    {
        return dehumidifierControl->getIndoorHumidityFN();
    }
    return default_int;
}

/**
 * 水泵
 */
int XlfDeviceWrapper::getDehumidifierWaterPumpFN(string deviceId)
{
    DehumidifierControl *dehumidifierControl = (DehumidifierControl *)getDeviceControl(deviceId);
    if(NULL != dehumidifierControl)
    {
        return dehumidifierControl->getWaterPumpFN();
    }
    return default_int;
}

/**
 * 负离子
 */
int XlfDeviceWrapper::getDehumidifierAnionFN(string deviceId)
{
    DehumidifierControl *dehumidifierControl = (DehumidifierControl *)getDeviceControl(deviceId);
    if(NULL != dehumidifierControl)
    {
        return dehumidifierControl->getAnionFN();
    }
    return default_int;
}

/**
 * 电量检测
 */
int XlfDeviceWrapper::getDehumidifierElectronicDetectFN(string deviceId)
{
    DehumidifierControl *dehumidifierControl = (DehumidifierControl *)getDeviceControl(deviceId);
    if(NULL != dehumidifierControl)
    {
        return dehumidifierControl->getElectronicDetectFN();
    }
    return default_int;
}

/**
 * 开停机
 */
int XlfDeviceWrapper::getDehumidifierPowerFN(string deviceId)
{
    DehumidifierControl *dehumidifierControl = (DehumidifierControl *)getDeviceControl(deviceId);
    if(NULL != dehumidifierControl)
    {
        return dehumidifierControl->getPowerFN();
    }
    return default_int;
}

/**
 * EEPROM可改写功能
 */
int XlfDeviceWrapper::getDehumidifierEEPROMWriteFN(string deviceId)
{
    DehumidifierControl *dehumidifierControl = (DehumidifierControl *)getDeviceControl(deviceId);
    if(NULL != dehumidifierControl)
    {
        return dehumidifierControl->getEEPROMWriteFN();
    }
    return default_int;
}

/**
 * 101#-0#第 7 字节预留位的控制功能
 */
int XlfDeviceWrapper::getDehumidifier7ReserverdFN(string deviceId)
{
    DehumidifierControl *dehumidifierControl = (DehumidifierControl *)getDeviceControl(deviceId);
    if(NULL != dehumidifierControl)
    {
        return dehumidifierControl->get7ReserverdFN();
    }
    return default_int;
}

/**
 * 101#-0#第 8 字节预留位的控制功能
 */
int XlfDeviceWrapper::getDehumidifier8ReserverdFN(string deviceId)
{
    DehumidifierControl *dehumidifierControl = (DehumidifierControl *)getDeviceControl(deviceId);
    if(NULL != dehumidifierControl)
    {
        return dehumidifierControl->get8ReserverdFN();
    }
    return default_int;
}

/**
 * 获取风速
 */
string XlfDeviceWrapper::getDehumidifierWindSpeedStatus(string deviceId)
{
    DehumidifierControl *dehumidifierControl = (DehumidifierControl *)getDeviceControl(deviceId);
    if(NULL != dehumidifierControl)
    {
        return dehumidifierControl->getWindSpeedStatus();
    }
    return default_string;
}

/**
 * 获取模式
 */
string XlfDeviceWrapper::getDehumidifierModeStatus(string deviceId)
{
    DehumidifierControl *dehumidifierControl = (DehumidifierControl *)getDeviceControl(deviceId);
    if(NULL != dehumidifierControl)
    {
        return dehumidifierControl->getModeStatus();
    }
    return default_string;
}

/**
 * 获取定时开关机控制
 */
string XlfDeviceWrapper::getDehumidifierTimeStatus(string deviceId)
{
    DehumidifierControl *dehumidifierControl = (DehumidifierControl *)getDeviceControl(deviceId);
    if(NULL != dehumidifierControl)
    {
        return dehumidifierControl->getTimeStatus();
    }
    return default_string;
}

/**
 * 获取定时开关机时间
 */
string XlfDeviceWrapper::getDehumidifierTimerValue(string deviceId)
{
    DehumidifierControl *dehumidifierControl = (DehumidifierControl *)getDeviceControl(deviceId);
    if(NULL != dehumidifierControl)
    {
        return dehumidifierControl->getTimerValue();
    }
    return default_string;
}

/**
 * 获取设置湿度
 */
string XlfDeviceWrapper::getDehumidifierSettingHumidityValue(string deviceId)
{
    DehumidifierControl *dehumidifierControl = (DehumidifierControl *)getDeviceControl(deviceId);
    if(NULL != dehumidifierControl)
    {
        return dehumidifierControl->getSettingHumidityValue();
    }
    return default_string;
}

/**
 * 获取电加热设定温度
 */
string XlfDeviceWrapper::getDehumidifierEletricHeatingTempratureStatus(string deviceId)
{
    DehumidifierControl *dehumidifierControl = (DehumidifierControl *)getDeviceControl(deviceId);
    if(NULL != dehumidifierControl)
    {
        return dehumidifierControl->getEletricHeatingTempratureStatus();
    }
    return default_string;
}

/**
 * 获取室内温度
 */
string XlfDeviceWrapper::getDehumidifierIndoorTempStatus(string deviceId)
{
    DehumidifierControl *dehumidifierControl = (DehumidifierControl *)getDeviceControl(deviceId);
    if(NULL != dehumidifierControl)
    {
        return dehumidifierControl->getIndoorTempStatus();
    }
    return default_string;
}

/**
 * 获取除湿机电源开关状态
 */
string XlfDeviceWrapper::getDehumidifierPower(string deviceId)
{
    DehumidifierControl *dehumidifierControl = (DehumidifierControl *)getDeviceControl(deviceId);
    if(NULL != dehumidifierControl)
    {
        return dehumidifierControl->getPower();
    }
    return default_string;
}

/**
 * 获取电加热功能开关状态
 */
string XlfDeviceWrapper::getDehumidifierEletricHeatingStatus(string deviceId)
{
    DehumidifierControl *dehumidifierControl = (DehumidifierControl *)getDeviceControl(deviceId);
    if(NULL != dehumidifierControl)
    {
        return dehumidifierControl->getEletricHeatingStatus();
    }
    return default_string;
}

/**
 * 获取水泵开关状态
 */
string XlfDeviceWrapper::getDehumidifierWaterPumpStatus(string deviceId)
{
    DehumidifierControl *dehumidifierControl = (DehumidifierControl *)getDeviceControl(deviceId);
    if(NULL != dehumidifierControl)
    {
        return dehumidifierControl->getWaterPumpStatus();
    }
    return default_string;
}

/**
 * 获取负离子开关状态
 */
string XlfDeviceWrapper::getDehumidifierAnionStatus(string deviceId)
{
    DehumidifierControl *dehumidifierControl = (DehumidifierControl *)getDeviceControl(deviceId);
    if(NULL != dehumidifierControl)
    {
        return dehumidifierControl->getAnionStatus();
    }
    return default_string;
}

/**
 * 本次命令之前有否红外和按键控制过
 */
string XlfDeviceWrapper::getDehumidifierInfrarediKeypadControl(string deviceId)
{
    DehumidifierControl *dehumidifierControl = (DehumidifierControl *)getDeviceControl(deviceId);
    if(NULL != dehumidifierControl)
    {
        return dehumidifierControl->getInfrarediKeypadControl();
    }
    return default_string;
}

/**
 * 本次命令之前有否 WIFI 控制过
 */
string XlfDeviceWrapper::getDehumidifierIsWifiControl(string deviceId)
{
    DehumidifierControl *dehumidifierControl = (DehumidifierControl *)getDeviceControl(deviceId);
    if(NULL != dehumidifierControl)
    {
        return dehumidifierControl->getWifiControl();
    }
    return default_string;
}

/**
 * 过滤网清洁告警
 */
string XlfDeviceWrapper::getDehumidifierFilterNetCleanWarning(string deviceId)
{
    DehumidifierControl *dehumidifierControl = (DehumidifierControl *)getDeviceControl(deviceId);
    if(NULL != dehumidifierControl)
    {
        return dehumidifierControl->getFilterNetCleanWarning();
    }
    return default_string;
}

/**
 * 湿度传感器故障
 */
string XlfDeviceWrapper::getDehumidifierHumidSensorError(string deviceId)
{
    DehumidifierControl *dehumidifierControl = (DehumidifierControl *)getDeviceControl(deviceId);
    if(NULL != dehumidifierControl)
    {
        return dehumidifierControl->getHumidSensorError();
    }
    return default_string;
}

/**
 *  管温传感器故障
 */
string XlfDeviceWrapper::getDehumidifierPumpTempratureError(string deviceId)
{
    DehumidifierControl *dehumidifierControl = (DehumidifierControl *)getDeviceControl(deviceId);
    if(NULL != dehumidifierControl)
    {
        return dehumidifierControl->getPumpTempratureError();
    }
    return default_string;
}

/**
 * 室内温度传感器故障
 */
string XlfDeviceWrapper::getDehumidifierIndoorTempratureError(string deviceId)
{
    DehumidifierControl *dehumidifierControl = (DehumidifierControl *)getDeviceControl(deviceId);
    if(NULL != dehumidifierControl)
    {
        return dehumidifierControl->getIndoorTempratureError();
    }
    return default_string;
}

/**
 * 水满警告
 */
string XlfDeviceWrapper::getDehumidifierWaterFullWarning(string deviceId)
{
    DehumidifierControl *dehumidifierControl = (DehumidifierControl *)getDeviceControl(deviceId);
    if(NULL != dehumidifierControl)
    {
        return dehumidifierControl->getWaterFullWarning();
    }
    return default_string;
}

/**
 * 水泵故障
 */
string XlfDeviceWrapper::getDehumidifierWaterPumpWarning(string deviceId)
{
    DehumidifierControl *dehumidifierControl = (DehumidifierControl *)getDeviceControl(deviceId);
    if(NULL != dehumidifierControl)
    {
        return dehumidifierControl->getWaterPumpWarning();
    }
    return default_string;
}

/**
 * 获取实际湿度
 */
string XlfDeviceWrapper::getDehumidifierRealHumidityValue(string deviceId)
{
    DehumidifierControl *dehumidifierControl = (DehumidifierControl *)getDeviceControl(deviceId);
    if(NULL != dehumidifierControl)
    {
        return dehumidifierControl->getRealHumidityValue();
    }
    return default_string;
}

/**************************  aircleaner  *************************/
/************************************ 设备控制 **************************************/
//1设置净化速度
string XlfDeviceWrapper::setAircleanerWindSpeed(string deviceId, string speed, bool manualOrnot)
{
    AirCleanerControl *aircleanerControl = (AirCleanerControl *)getDeviceControl(deviceId);
    if(NULL != aircleanerControl)
    {
        return aircleanerControl->setWindSpeed(speed,manualOrnot);
    }
    return default_string;
}

//2设置模式
string XlfDeviceWrapper::setAircleanerMode(string deviceId, string mode, bool manualOrnot)
{
    AirCleanerControl *aircleanerControl = (AirCleanerControl *)getDeviceControl(deviceId);
    if(NULL != aircleanerControl)
    {
        return aircleanerControl->setMode(mode, manualOrnot);
    }
    return default_string;
}

//定时开关机
string XlfDeviceWrapper::setAircleanerTimerControl(string deviceId, bool enable, string time, bool manualOrnot)
{
    AirCleanerControl *aircleanerControl = (AirCleanerControl *)getDeviceControl(deviceId);
    if(NULL != aircleanerControl)
    {
        return aircleanerControl->setTimerControl(enable, time, manualOrnot);
    }
    return default_string;
}

// 开关清新机电源
string XlfDeviceWrapper::setAircleanerpower(string deviceId, bool power, bool manualOrnot)
{
    AirCleanerControl *aircleanerControl = (AirCleanerControl *)getDeviceControl(deviceId);
    if(NULL != aircleanerControl)
    {
        return aircleanerControl->setpower(power, manualOrnot);
    }
    return default_string;
}

// 开关儿童锁
string XlfDeviceWrapper::setAircleanerChildLock(string deviceId, bool power, bool manualOrnot)
{
    AirCleanerControl *aircleanerControl = (AirCleanerControl *)getDeviceControl(deviceId);
    if(NULL != aircleanerControl)
    {
        return aircleanerControl->setChildLock(power, manualOrnot);
    }
    return default_string;
}

// 开关水离子
string XlfDeviceWrapper::setAircleanerWaterIon(string deviceId, bool power, bool manualOrnot)
{
    AirCleanerControl *aircleanerControl = (AirCleanerControl *)getDeviceControl(deviceId);
    if(NULL != aircleanerControl)
    {
        return aircleanerControl->setWaterIon(power, manualOrnot);
    }
    return default_string;
}

// 开关加湿功能
string XlfDeviceWrapper::setAircleanerHumidification(string deviceId, bool power, bool manualOrnot)
{
    AirCleanerControl *aircleanerControl = (AirCleanerControl *)getDeviceControl(deviceId);
    if(NULL != aircleanerControl)
    {
        return aircleanerControl->setHumidification(power, manualOrnot);
    }
    return default_string;
}

// 加湿器湿度设置
string XlfDeviceWrapper::setAircleanerHumidificationValue(string deviceId, int humidity_value, bool manualOrnot)
{
    AirCleanerControl *aircleanerControl = (AirCleanerControl *)getDeviceControl(deviceId);
    if(NULL != aircleanerControl)
    {
        return aircleanerControl->Humidification_ValueSet(humidity_value, manualOrnot);
    }
    return default_string;
}

// 盒子控制
string XlfDeviceWrapper::setAircleanerSBox(string deviceId, bool power_on,string Mode,string WindSpeed_value,bool jsj_on,string humdity_value,bool manualOrnot)
{
    AirCleanerControl *aircleanerControl = (AirCleanerControl *)getDeviceControl(deviceId);
    if(NULL != aircleanerControl)
    {
        return aircleanerControl->SetAirCleanerSBox(power_on, Mode, WindSpeed_value, jsj_on, humdity_value, manualOrnot);
    }
    return default_string;
}

/************************************ 获取设备的各个状态 **************************************/
// 0净化速度
string XlfDeviceWrapper::getAircleanerSpeedStatus(string deviceId)
{
    AirCleanerControl *aircleanerControl = (AirCleanerControl *)getDeviceControl(deviceId);
    if(NULL != aircleanerControl)
    {
        return aircleanerControl->getSpeedStatus();
    }
    return default_string;
}

// 1净化模式,
string XlfDeviceWrapper::getAircleanerModeStatus(string deviceId)
{
    AirCleanerControl *aircleanerControl = (AirCleanerControl *)getDeviceControl(deviceId);
    if(NULL != aircleanerControl)
    {
        return aircleanerControl->getModeStatus();
    }
    return default_string;
}

//2定时开关机控制,
string XlfDeviceWrapper::getAircleanerTimeStatus(string deviceId)
{
    AirCleanerControl *aircleanerControl = (AirCleanerControl *)getDeviceControl(deviceId);
    if(NULL != aircleanerControl)
    {
        return aircleanerControl->getTimeStatus();
    }
    return default_string;
}

//3定时开关机时间,
string XlfDeviceWrapper::getAircleanerTimerValue(string deviceId)
{
    AirCleanerControl *aircleanerControl = (AirCleanerControl *)getDeviceControl(deviceId);
    if(NULL != aircleanerControl)
    {
        return aircleanerControl->getTimerValue();
    }
    return default_string;
}

//4风机转速,
string XlfDeviceWrapper::getAircleanerMotorSpeed(string deviceId)
{
    AirCleanerControl *aircleanerControl = (AirCleanerControl *)getDeviceControl(deviceId);
    if(NULL != aircleanerControl)
    {
        return aircleanerControl->getMotorSpeed();
    }
    return default_string;
}

// 5空气质量,
string XlfDeviceWrapper::getAircleanerAirQuality(string deviceId)
{
    AirCleanerControl *aircleanerControl = (AirCleanerControl *)getDeviceControl(deviceId);
    if(NULL != aircleanerControl)
    {
        return aircleanerControl->getAirQuality();
    }
    return default_string;
}

// 6空气质量百分比,
string XlfDeviceWrapper::getAircleanerAirQualityPercent(string deviceId)
{
    AirCleanerControl *aircleanerControl = (AirCleanerControl *)getDeviceControl(deviceId);
    if(NULL != aircleanerControl)
    {
        return aircleanerControl->getAirQualityPercent();
    }
    return default_string;
}

// 7相对湿度,
string XlfDeviceWrapper::getAircleanerRelativeHumidityValue(string deviceId)
{
    AirCleanerControl *aircleanerControl = (AirCleanerControl *)getDeviceControl(deviceId);
    if(NULL != aircleanerControl)
    {
        return aircleanerControl->getRelativeHumidityValue();
    }
    return default_string;
}

//8开停净化机,
string XlfDeviceWrapper::getAircleanerPowerStatus(string deviceId)
{
    AirCleanerControl *aircleanerControl = (AirCleanerControl *)getDeviceControl(deviceId);
    if(NULL != aircleanerControl)
    {
        return aircleanerControl->getPowerStatus();
    }
    return default_string;
}

// 9儿童锁开关控制,
string XlfDeviceWrapper::getAircleanerChildLockStatus(string deviceId)
{
    AirCleanerControl *aircleanerControl = (AirCleanerControl *)getDeviceControl(deviceId);
    if(NULL != aircleanerControl)
    {
        return aircleanerControl->getChildLockStatus();
    }
    return default_string;
}

// 10水离子开停控制,
string XlfDeviceWrapper::getAircleanerWaterionStatus(string deviceId)
{
    AirCleanerControl *aircleanerControl = (AirCleanerControl *)getDeviceControl(deviceId);
    if(NULL != aircleanerControl)
    {
        return aircleanerControl->getWaterionStatus();
    }
    return default_string;
}

// 11加湿机开停控制,
string XlfDeviceWrapper::getAircleanerHumidityStatus(string deviceId)
{
    AirCleanerControl *aircleanerControl = (AirCleanerControl *)getDeviceControl(deviceId);
    if(NULL != aircleanerControl)
    {
        return aircleanerControl->getHumidityStatus();
    }
    return default_string;
}

// 12过滤网更换提示,
string XlfDeviceWrapper::getAircleanerChangeFilter(string deviceId)
{
    AirCleanerControl *aircleanerControl = (AirCleanerControl *)getDeviceControl(deviceId);
    if(NULL != aircleanerControl)
    {
        return aircleanerControl->ChangeFilter();
    }
    return default_string;
}

// 13本次命令之前有否红外和按键控制过,
string XlfDeviceWrapper::getAircleanerinfraredAndButtonBeforeCommand1(string deviceId)
{
    AirCleanerControl *aircleanerControl = (AirCleanerControl *)getDeviceControl(deviceId);
    if(NULL != aircleanerControl)
    {
        return aircleanerControl->infraredAndButtonBeforeCommand1();
    }
    return default_string;
}

// 14本次命令之前有否红外和按键控制过,
string XlfDeviceWrapper::getAircleanerinfraredAndButtonBeforeCommand2(string deviceId)
{
    AirCleanerControl *aircleanerControl = (AirCleanerControl *)getDeviceControl(deviceId);
    if(NULL != aircleanerControl)
    {
        return aircleanerControl->infraredAndButtonBeforeCommand2();
    }
    return default_string;
}

// 15加湿转轮不动,
string XlfDeviceWrapper::getAircleanerHumidityWheelError(string deviceId)
{
    AirCleanerControl *aircleanerControl = (AirCleanerControl *)getDeviceControl(deviceId);
    if(NULL != aircleanerControl)
    {
        return aircleanerControl->getHumidityWheelError();
    }
    return default_string;
}

// 16水箱空,
string XlfDeviceWrapper::getAircleanerWaterSinkEmptyError(string deviceId)
{
    AirCleanerControl *aircleanerControl = (AirCleanerControl *)getDeviceControl(deviceId);
    if(NULL != aircleanerControl)
    {
        return aircleanerControl->getWaterSinkEmptyError();
    }
    return default_string;
}

// 17水箱未装好,
string XlfDeviceWrapper::getAircleanerWaterSinkNotSetup(string deviceId)
{
    AirCleanerControl *aircleanerControl = (AirCleanerControl *)getDeviceControl(deviceId);
    if(NULL != aircleanerControl)
    {
        return aircleanerControl->getWaterSinkNotSetup();
    }
    return default_string;
}

// 18湿度传感器故障,
string XlfDeviceWrapper::getAircleanerHumiditySensorError(string deviceId)
{
    AirCleanerControl *aircleanerControl = (AirCleanerControl *)getDeviceControl(deviceId);
    if(NULL != aircleanerControl)
    {
        return aircleanerControl->getHumiditySensorError();
    }
    return default_string;
}

// 19风机故障,
string XlfDeviceWrapper::getAircleanerMotorError(string deviceId)
{
    AirCleanerControl *aircleanerControl = (AirCleanerControl *)getDeviceControl(deviceId);
    if(NULL != aircleanerControl)
    {
        return aircleanerControl->getMotorError();
    }
    return default_string;
}

// 20风尘传感器故障,
string XlfDeviceWrapper::getAircleanerDustSensorError(string deviceId)
{
    AirCleanerControl *aircleanerControl = (AirCleanerControl *)getDeviceControl(deviceId);
    if(NULL != aircleanerControl)
    {
        return aircleanerControl->getDustSensorError();
    }
    return default_string;
}

// 21气味传感器故障，
string XlfDeviceWrapper::getAircleanerSmellSensorError(string deviceId)
{
    AirCleanerControl *aircleanerControl = (AirCleanerControl *)getDeviceControl(deviceId);
    if(NULL != aircleanerControl)
    {
        return aircleanerControl->geSmellSensorError();
    }
    return default_string;
}

//22机器倾斜故障
string XlfDeviceWrapper::getAircleanerLeanError(string deviceId)
{
    AirCleanerControl *aircleanerControl = (AirCleanerControl *)getDeviceControl(deviceId);
    if(NULL != aircleanerControl)
    {
        return aircleanerControl->getLeanError();
    }
    return default_string;
}

//23湿度设置值
string XlfDeviceWrapper::getAircleanerSettingHumid(string deviceId)
{
    AirCleanerControl *aircleanerControl = (AirCleanerControl *)getDeviceControl(deviceId);
    if(NULL != aircleanerControl)
    {
        return aircleanerControl->getSettingHumid();
    }
    return default_string;
}

/********************************** 获取功能使能状态 ****************************************/
// 1净化速度状态-自动功能，
int XlfDeviceWrapper::getAircleanerCleanSpeedAutoFN(string deviceId)
{
    AirCleanerControl *aircleanerControl = (AirCleanerControl *)getDeviceControl(deviceId);
    if(NULL != aircleanerControl)
    {
        return aircleanerControl->GetCleanSpeedAutoFN();
    }
    return default_int;
}

// 2净化速度状态-净烟功能
int XlfDeviceWrapper::getAircleanerCleanSpeedDelSmokeFN(string deviceId)
{
    AirCleanerControl *aircleanerControl = (AirCleanerControl *)getDeviceControl(deviceId);
    if(NULL != aircleanerControl)
    {
        return aircleanerControl->GetCleanSpeedDelSmokeFN();
    }
    return default_int;
}

// 3净化速度状态-高风功能
int XlfDeviceWrapper::getAircleanerCleanSpeedHighFN(string deviceId)
{
    AirCleanerControl *aircleanerControl = (AirCleanerControl *)getDeviceControl(deviceId);
    if(NULL != aircleanerControl)
    {
        return aircleanerControl->GetCleanSpeedHighFN();
    }
    return default_int;
}

// 4净化速度状态-中风功能，
int XlfDeviceWrapper::getAircleanerCleanSpeedMiddleFN(string deviceId)
{
    AirCleanerControl *aircleanerControl = (AirCleanerControl *)getDeviceControl(deviceId);
    if(NULL != aircleanerControl)
    {
        return aircleanerControl->GetCleanSpeedMiddleFN();
    }
    return default_int;
}

// 5净化速度状态-低风功能，
int XlfDeviceWrapper::getAircleanerCleanSpeedLowFN(string deviceId)
{
    AirCleanerControl *aircleanerControl = (AirCleanerControl *)getDeviceControl(deviceId);
    if(NULL != aircleanerControl)
    {
        return aircleanerControl->GetCleanSpeedLowFN();
    }
    return default_int;
}

// 6净化模式状态-睡眠功能，
int XlfDeviceWrapper::getAircleanerCleanModeSleepFN(string deviceId)
{
    AirCleanerControl *aircleanerControl = (AirCleanerControl *)getDeviceControl(deviceId);
    if(NULL != aircleanerControl)
    {
        return aircleanerControl->GetCleanModeSleepFN();
    }
    return default_int;
}

// 7净化模式状态-静音功能，
int XlfDeviceWrapper::getAircleanerCleanModeMuteFN(string deviceId)
{
    AirCleanerControl *aircleanerControl = (AirCleanerControl *)getDeviceControl(deviceId);
    if(NULL != aircleanerControl)
    {
        return aircleanerControl->GetCleanModeMuteFN();
    }
    return default_int;
}

// 8净化模式状态-智能功能，
int XlfDeviceWrapper::getAircleanerCleanModeSmartFN(string deviceId)
{
    AirCleanerControl *aircleanerControl = (AirCleanerControl *)getDeviceControl(deviceId);
    if(NULL != aircleanerControl)
    {
        return aircleanerControl->GetCleanModeSmartFN();
    }
    return default_int;
}

// 9净化模式状态-除味功能，
int XlfDeviceWrapper::getAircleanerCleanModeDelTasteFN(string deviceId)
{
    AirCleanerControl *aircleanerControl = (AirCleanerControl *)getDeviceControl(deviceId);
    if(NULL != aircleanerControl)
    {
        return aircleanerControl->GetCleanModeDelTasteFN();
    }
    return default_int;
}

// 10净化模式状态-除烟功能，
int XlfDeviceWrapper::getAircleanerCleanModeDelSmokeFN(string deviceId)
{
    AirCleanerControl *aircleanerControl = (AirCleanerControl *)getDeviceControl(deviceId);
    if(NULL != aircleanerControl)
    {
        return aircleanerControl->GetCleanModeDelSmokeFN();
    }
    return default_int;
}

// 11普通定时功能，
int XlfDeviceWrapper::getAircleanerGeneralTimingFN(string deviceId)
{
    AirCleanerControl *aircleanerControl = (AirCleanerControl *)getDeviceControl(deviceId);
    if(NULL != aircleanerControl)
    {
        return aircleanerControl->GetGeneralTimingFN();
    }
    return default_int;
}

// 12儿童锁功能，
int XlfDeviceWrapper::getAircleanerChildLockFN(string deviceId)
{
    AirCleanerControl *aircleanerControl = (AirCleanerControl *)getDeviceControl(deviceId);
    if(NULL != aircleanerControl)
    {
        return aircleanerControl->GetChildLockFN();
    }
    return default_int;
}

// 13水离子开停，
int XlfDeviceWrapper::getAircleanerWaterIonFN(string deviceId)
{
    AirCleanerControl *aircleanerControl = (AirCleanerControl *)getDeviceControl(deviceId);
    if(NULL != aircleanerControl)
    {
        return aircleanerControl->GetWaterIonFN();
    }
    return default_int;
}

// 14加湿机开停功能，
int XlfDeviceWrapper::getAircleanerDehumidifierFN(string deviceId)
{
    AirCleanerControl *aircleanerControl = (AirCleanerControl *)getDeviceControl(deviceId);
    if(NULL != aircleanerControl)
    {
        return aircleanerControl->GetDehumidifierFN();
    }
    return default_int;
}

// 15净化机开停功能
int XlfDeviceWrapper::getAircleanerCleanMachineFN(string deviceId)
{
    AirCleanerControl *aircleanerControl = (AirCleanerControl *)getDeviceControl(deviceId);
    if(NULL != aircleanerControl)
    {
        return aircleanerControl->GetCleanMachineFN();
    }
    return default_int;
}

// 16 EEPROM可改写功能,
int XlfDeviceWrapper::getAircleanerEEpromReadWriteFN(string deviceId)
{
    AirCleanerControl *aircleanerControl = (AirCleanerControl *)getDeviceControl(deviceId);
    if(NULL != aircleanerControl)
    {
        return aircleanerControl->GetEEpromReadWriteFN();
    }
    return default_int;
}

// 17电量检测功能,
int XlfDeviceWrapper::getAircleanerPowerDetectFN(string deviceId)
{
    AirCleanerControl *aircleanerControl = (AirCleanerControl *)getDeviceControl(deviceId);
    if(NULL != aircleanerControl)
    {
        return aircleanerControl->GetPowerDetectFN();
    }
    return default_int;
}

// 101#-0#第5字节预留位的控制功能
int XlfDeviceWrapper::getAircleaner5ReserverdFN(string deviceId)
{
    AirCleanerControl *aircleanerControl = (AirCleanerControl *)getDeviceControl(deviceId);
    if(NULL != aircleanerControl)
    {
        return aircleanerControl->Get5ReserverdFN();
    }
    return default_int;
}

// 101#-0#第6字节预留位的控制功能
int XlfDeviceWrapper::getAircleaner6ReserverdFN(string deviceId)
{
    AirCleanerControl *aircleanerControl = (AirCleanerControl *)getDeviceControl(deviceId);
    if(NULL != aircleanerControl)
    {
        return aircleanerControl->Get6ReserverdFN();
    }
    return default_int;
}

/**************************  airFanControl  **************************/
/**
 * 设置新风机风速
 */
string XlfDeviceWrapper::setAirfanWindSpeed(string deviceId, string speed, int soundSet)
{
    AirFanControl *airfanControl = (AirFanControl *)getDeviceControl(deviceId);
    if(NULL != airfanControl)
    {
        return airfanControl->setSpeed(speed, soundSet);
    }
    return default_string;
}

/**
 * 设置新风机开关机状态
 */
string XlfDeviceWrapper::setAirfanPower(string deviceId, int power, int soundSet)
{
    AirFanControl *airfanControl = (AirFanControl *)getDeviceControl(deviceId);
    if(NULL != airfanControl)
    {
        return airfanControl->setpowerOn(power, soundSet);
    }
    return default_string;
}

/**
 * 设置新风机模式
 */
string XlfDeviceWrapper::setAirfanMode(string deviceId, string mode, int soundSet)
{
    AirFanControl *airfanControl = (AirFanControl *)getDeviceControl(deviceId);
    if(NULL != airfanControl)
    {
        return airfanControl->setMode(mode, soundSet);
    }
    return default_string;
}

/**
 * 设置新风机普通定时
 */
string XlfDeviceWrapper::setAirfanTimingSwitchMachine(string deviceId, string hour, int isOpen, int soundSet)
{
    AirFanControl *airfanControl = (AirFanControl *)getDeviceControl(deviceId);
    if(NULL != airfanControl)
    {
        return airfanControl->setTiming(hour, isOpen, soundSet);
    }
    return default_string;
}


string XlfDeviceWrapper::getStatus(string deviceId, int soundSet)
{
    AirFanControl *airfanControl = (AirFanControl *)getDeviceControl(deviceId);
    if(NULL != airfanControl)
    {
        return airfanControl->getStatus(soundSet);
    }
    return default_string;
}

string XlfDeviceWrapper::setAirfanHotFanSBox(string deviceId, int on, string  mode, string  WindSpeed_value, int soundSet)
{
    AirFanControl *airfanControl = (AirFanControl *)getDeviceControl(deviceId);
    if(NULL != airfanControl)
    {
        return airfanControl->SetHotFanSBox(on, mode, WindSpeed_value, soundSet);
    }
    return default_string;
}

/**
 * 获取新风机操作结果
 */
string XlfDeviceWrapper::getAirfanResult(string deviceId)
{
    AirFanControl *airfanControl = (AirFanControl *)getDeviceControl(deviceId);
    if(NULL != airfanControl)
    {
        //return airfanControl->getWindSpeed();
    }
    return default_string;
}

/**
 * 获取新风机风速
 */
string XlfDeviceWrapper::getAirfanWindSpeed(string deviceId)
{
    AirFanControl *airfanControl = (AirFanControl *)getDeviceControl(deviceId);
    if(NULL != airfanControl)
    {
        return airfanControl->getSpeed();
    }
    return default_string;
}

/**
 * 获取新风机开关机状态
 */
string XlfDeviceWrapper::getAirfanPower(string deviceId)
{
    AirFanControl *airfanControl = (AirFanControl *)getDeviceControl(deviceId);
    if(NULL != airfanControl)
    {
        return airfanControl->getPower();
    }
    return default_string;
}

/**
 * 获取新风机待机状态
 */
string XlfDeviceWrapper::getAirfanSuspendMode(string deviceId)
{
    AirFanControl *airfanControl = (AirFanControl *)getDeviceControl(deviceId);
    if(NULL != airfanControl)
    {
        return airfanControl->getSuspendMode();
    }
    return default_string;
}

/**
 * 获取新风机模式
 */
string XlfDeviceWrapper::getAirfanMode(string deviceId)
{
    AirFanControl *airfanControl = (AirFanControl *)getDeviceControl(deviceId);
    if(NULL != airfanControl)
    {
        return airfanControl->getMode();
    }
    return default_string;
}

/**
 * 获取新风机定时状态
 */
string XlfDeviceWrapper::getAirfanIsTiming(string deviceId)
{
    AirFanControl *airfanControl = (AirFanControl *)getDeviceControl(deviceId);
    if(NULL != airfanControl)
    {
        return airfanControl->getIsTiming();
    }
    return default_string;
}

/**
 * 获取新风机定时时间
 */
string XlfDeviceWrapper::getAirfanTimingTime(string deviceId)
{
    AirFanControl *airfanControl = (AirFanControl *)getDeviceControl(deviceId);
    if(NULL != airfanControl)
    {
        return airfanControl->getTimingTime();
    }
    return default_string;
}

/**
 * 获取新风机外部风扇转速
 */
string XlfDeviceWrapper::getAirfanOuterFanSpeed(string deviceId)
{
    AirFanControl *airfanControl = (AirFanControl *)getDeviceControl(deviceId);
    if(NULL != airfanControl)
    {
        return airfanControl->getOuterFanSpeed();
    }
    return default_string;
}

/**
 * 获取新风机内部风扇转速
 */
string XlfDeviceWrapper::getAirfanInnerFanSpeed(string deviceId)
{
    AirFanControl *airfanControl = (AirFanControl *)getDeviceControl(deviceId);
    if(NULL != airfanControl)
    {
        return airfanControl->getInnerFanSpeed();
    }
    return default_string;
}

/**
 * 获取新风机内部有效温度
 */
string XlfDeviceWrapper::getAirfanInnerTempratureValid(string deviceId)
{
    AirFanControl *airfanControl = (AirFanControl *)getDeviceControl(deviceId);
    if(NULL != airfanControl)
    {
        return airfanControl->getInnerTempratureValid();
    }
    return default_string;
}

/**
 * 获取新风机内部有效湿度
 */
string XlfDeviceWrapper::getAirfanInnerHumidityValid(string deviceId)
{
    AirFanControl *airfanControl = (AirFanControl *)getDeviceControl(deviceId);
    if(NULL != airfanControl)
    {
        return airfanControl->getInnerHumidityValid();
    }
    return default_string;
}

/**
 *  获取室内二氧化碳有效值
 */
string XlfDeviceWrapper::getAirfanInnerco2DensityValid(string deviceId)
{
    AirFanControl *airfanControl = (AirFanControl *)getDeviceControl(deviceId);
    if(NULL != airfanControl)
    {
        return airfanControl->getInnerco2DensityValid();
    }
    return default_string;
}

/**
 * 获取新风机外部有效温度
 */
string XlfDeviceWrapper::getAirfanOuterTempratureValid(string deviceId)
{
    AirFanControl *airfanControl = (AirFanControl *)getDeviceControl(deviceId);
    if(NULL != airfanControl)
    {
        return airfanControl->getOuterTempratureValid();
    }
    return default_string;
}

/**
 * 获取新风机外部有效湿度
 */
string XlfDeviceWrapper::getAirfanOuterHumidityValid(string deviceId)
{
    AirFanControl *airfanControl = (AirFanControl *)getDeviceControl(deviceId);
    if(NULL != airfanControl)
    {
        return airfanControl->getOuterHumidityValid();
    }
    return default_string;
}

/**
 * 获取新风机室内温度
 */
string XlfDeviceWrapper::getAirfanTemperatureIndoor(string deviceId)
{
    AirFanControl *airfanControl = (AirFanControl *)getDeviceControl(deviceId);
    if(NULL != airfanControl)
    {
        return airfanControl->getInnerTemprature();
    }
    return default_string;
}

/**
 * 获取新风机室内湿度
 */
string XlfDeviceWrapper::getAirfanHumidityIndoor(string deviceId)
{
    AirFanControl *airfanControl = (AirFanControl *)getDeviceControl(deviceId);
    if(NULL != airfanControl)
    {
        return airfanControl->getInnerRelativeHumidity();
    }
    return default_string;
}

/**
 * 获取新风机室外温度
 */
string XlfDeviceWrapper::getAirfanTemperatureOutdoor(string deviceId)
{
    AirFanControl *airfanControl = (AirFanControl *)getDeviceControl(deviceId);
    if(NULL != airfanControl)
    {
        return airfanControl->getOuterTemprature();
    }
    return default_string;
}

/**
 * 获取新风机室外湿度
 */
string XlfDeviceWrapper::getAirfanHumidityOutdoor(string deviceId)
{
    AirFanControl *airfanControl = (AirFanControl *)getDeviceControl(deviceId);
    if(NULL != airfanControl)
    {
        return airfanControl->getOuterRelativeHumidity();
    }
    return default_string;
}

/**
 * 获取新风机室内二氧化碳浓度
 */
string XlfDeviceWrapper::getAirfanCO2Indoor(string deviceId)
{
    AirFanControl *airfanControl = (AirFanControl *)getDeviceControl(deviceId);
    if(NULL != airfanControl)
    {
        return airfanControl->getInnerCo2Solubility();
    }
    return default_string;
}

/**
 * 获取新风机滤网复位状态
 */
string XlfDeviceWrapper::getAirfanFilterIfReplace(string deviceId)
{
    AirFanControl *airfanControl = (AirFanControl *)getDeviceControl(deviceId);
    if(NULL != airfanControl)
    {
        return airfanControl->getFilterIfReplace();
    }
    return default_string;
}

/**
 * 获取新风机室外风扇故障
 */
string XlfDeviceWrapper::getAirfanOuterFanIfFault(string deviceId)
{
    AirFanControl *airfanControl = (AirFanControl *)getDeviceControl(deviceId);
    if(NULL != airfanControl)
    {
        return airfanControl->getOuterFanIfFault();
    }
    return default_string;
}

/**
 * 获取新风机室内风扇故障
 */
string XlfDeviceWrapper::getAirfanInnerFanIfFault(string deviceId)
{
    AirFanControl *airfanControl = (AirFanControl *)getDeviceControl(deviceId);
    if(NULL != airfanControl)
    {
        return airfanControl->getInnerFanIfFault();
    }
    return default_string;
}

/**
 * 获取新风机室外温度传感器故障
 */
string XlfDeviceWrapper::getAirfanOuterTemperatureSensorIfFault(string deviceId)
{
    AirFanControl *airfanControl = (AirFanControl *)getDeviceControl(deviceId);
    if(NULL != airfanControl)
    {
        return airfanControl->getOuterTemperatureSensorIfFault();
    }
    return default_string;
}

/**
 * 获取新风机室外湿度传感器故障
 */
string XlfDeviceWrapper::getAirfanOuterHumiditySensorIfFault(string deviceId)
{
    AirFanControl *airfanControl = (AirFanControl *)getDeviceControl(deviceId);
    if(NULL != airfanControl)
    {
        return airfanControl->getOuterHumiditySensorIfFault();
    }
    return default_string;
}

/**
 * 获取新风机二氧化碳传感器故障
 */
string XlfDeviceWrapper::getAirfanCo2SensorIfFault(string deviceId)
{
    AirFanControl *airfanControl = (AirFanControl *)getDeviceControl(deviceId);
    if(NULL != airfanControl)
    {
        return airfanControl->getCo2SensorIfFault();
    }
    return default_string;
}

/**
 * 获取新风机室内温度传感器故障
 */
string XlfDeviceWrapper::getAirfanInnerTemperatureSensorFault(string deviceId)
{
    AirFanControl *airfanControl = (AirFanControl *)getDeviceControl(deviceId);
    if(NULL != airfanControl)
    {
        return airfanControl->getInnerTemperatureSensorFault();
    }
    return default_string;
}

/**
 * 获取新风机室内湿度传感器故障
 */
string XlfDeviceWrapper::getAirfanInnerHumiditySensorFault(string deviceId)
{
    AirFanControl *airfanControl = (AirFanControl *)getDeviceControl(deviceId);
    if(NULL != airfanControl)
    {
        return airfanControl->getInnerHumiditySensorFault();
    }
    return default_string;
}

/**
 * 获取新风机风量支持档位数使能
 */
int XlfDeviceWrapper::getAirfanSpeedSupportNumberFN(string deviceId)
{
    AirFanControl *airfanControl = (AirFanControl *)getDeviceControl(deviceId);
    if(NULL != airfanControl)
    {
        return airfanControl->getGNspeed();
    }
    return default_int;
}

/**
 * 获取新风机全热换气模式使能
 */
int XlfDeviceWrapper::getAirfanfullheatModeFN(string deviceId)
{
    AirFanControl *airfanControl = (AirFanControl *)getDeviceControl(deviceId);
    if(NULL != airfanControl)
    {
        return airfanControl->getGNfullheat();
    }
    return default_int;
}

/**
 * 获取新风机直通换气模式使能
 */
int XlfDeviceWrapper::getAirfanDirectModeFN(string deviceId)
{
    AirFanControl *airfanControl = (AirFanControl *)getDeviceControl(deviceId);
    if(NULL != airfanControl)
    {
        return airfanControl->getGNdirect();
    }
    return default_int;
}

/**
 * 获取新风机室内回旋模式使能
 */
int XlfDeviceWrapper::getAirfanIndoorModeFN(string deviceId)
{
    AirFanControl *airfanControl = (AirFanControl *)getDeviceControl(deviceId);
    if(NULL != airfanControl)
    {
        return airfanControl->getGNindoor();
    }
    return default_int;
}

/**
 * 获取新风机普通定时模式使能
 */
int XlfDeviceWrapper::getAirfanTiming(string deviceId)
{
    AirFanControl *airfanControl = (AirFanControl *)getDeviceControl(deviceId);
    if(NULL != airfanControl)
    {
        return airfanControl->getGNtiming();
    }
    return default_int;
}

/**
 * 获取新风机开关机控制位使能
 */
int XlfDeviceWrapper::getAirfanPowerFN(string deviceId)
{
    AirFanControl *airfanControl = (AirFanControl *)getDeviceControl(deviceId);
    if(NULL != airfanControl)
    {
        return airfanControl->getGNpower();
    }
    return default_int;
}

/**
 * 获取新风机是否升级EEPROM
 */
int XlfDeviceWrapper::getAirfanIfUpdateEEPROM(string deviceId)
{
    AirFanControl *airfanControl = (AirFanControl *)getDeviceControl(deviceId);
    if(NULL != airfanControl)
    {
        return airfanControl->getGNifUpdateEEPROM();
    }
    return default_int;
}

/**
 * 获取新风机电量检测使能
 */
int XlfDeviceWrapper::getAirfanBatteryIFdetection(string deviceId)
{
    AirFanControl *airfanControl = (AirFanControl *)getDeviceControl(deviceId);
    if(NULL != airfanControl)
    {
        return airfanControl->getGNbatteryIFdetection();
    }
    return default_int;
}

/********************************* 设备控制 *********************************/
/**
 * 开关机
 * @param set
 */
string XlfDeviceWrapper::setSeedMachinePower(string deviceId, int set,int flag)
{
    SeedMachineControl *seedControl = (SeedMachineControl *)getDeviceControl(deviceId);
    if(NULL != seedControl)
    {
        return seedControl->setPower(set,flag);
    }
    return default_string;
}

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
string XlfDeviceWrapper::setSeedMachineLightTimer(string deviceId, int curhour,int curmin,int set,int onOroff,int hour,int min,int lights,int flag)
{
    SeedMachineControl *seedControl = (SeedMachineControl *)getDeviceControl(deviceId);
    if(NULL != seedControl)
    {
        return seedControl->setLightTimer(curhour, curmin, set, onOroff, hour, min, lights,flag);
    }
    return default_string;
}

/**
 * 关闭报警
 * @param level 水位报警,pump 水泵报警，nutrition 营养液报警
 */
string XlfDeviceWrapper::setSeedMachineDismissWarning(string deviceId, int level, int pump,int nutrition,int flag)
{
    SeedMachineControl *seedControl = (SeedMachineControl *)getDeviceControl(deviceId);
    if(NULL != seedControl)
    {
        return seedControl->dismissWarning(level, pump, nutrition,flag);
    }
    return default_string;
}

/**
 * 设置灯开关：
 * 1 开灯，0 关灯
 */
string XlfDeviceWrapper::setSeedMachineLight(string deviceId, int set,int flag)
{
    SeedMachineControl *seedControl = (SeedMachineControl *)getDeviceControl(deviceId);
    if(NULL != seedControl)
    {
        return seedControl->setLight(set,flag);
    }
    return default_string;
}


/**
 * 设置负离子开关：
 * 1 开，0 关
 */
string XlfDeviceWrapper::setSeedMachineAnion(string deviceId, int set,int flag)
{
    SeedMachineControl *seedControl = (SeedMachineControl *)getDeviceControl(deviceId);
    if(NULL != seedControl)
    {
        return seedControl->setAnion(set,flag);
    }
    return default_string;
}

/**
 * 设置音乐开关：
 * 1 开，0 关
 */
string XlfDeviceWrapper::setSeedMachineMusic(string deviceId, int set,int flag)
{
    SeedMachineControl *seedControl = (SeedMachineControl *)getDeviceControl(deviceId);
    if(NULL != seedControl)
    {
        return seedControl->setMusic(set,flag);
    }
    return default_string;
}

/**
 * 音量控制
 * @param volume 1：音量+; 0：音量减
 */
string XlfDeviceWrapper::setSeedMachineVolume(string deviceId, int volume,int flag)
{
    SeedMachineControl *seedControl = (SeedMachineControl *)getDeviceControl(deviceId);
    if(NULL != seedControl)
    {
        return seedControl->setVolume(volume,flag);
    }
    return default_string;
}

/**
 * 设置PM2.5开关：如果有外接传感器的情况下才有此功能hasExtralSensor()方法可获得
 * 1 开，0 关
 */
string XlfDeviceWrapper::setSeedMachinePm25(string deviceId, int set,int flag)
{
    SeedMachineControl *seedControl = (SeedMachineControl *)getDeviceControl(deviceId);
    if(NULL != seedControl)
    {
        return seedControl->setPm25(set,flag);
    }
    return default_string;
}

/*************************** 获取设备状态接口 *************************/
/**
 * 当前开关机状态
 */
string XlfDeviceWrapper::getSeedMachinePowerStat(string deviceId)
{
    SeedMachineControl *seedControl = (SeedMachineControl *)getDeviceControl(deviceId);
    if(NULL != seedControl)
    {
        return seedControl->getPowerStat();
    }
    return default_string;
}

/**
 * 当前音乐状态
 */
string XlfDeviceWrapper::getSeedMachineMusicStat(string deviceId)
{
    SeedMachineControl *seedControl = (SeedMachineControl *)getDeviceControl(deviceId);
    if(NULL != seedControl)
    {
        return seedControl->getMusicStat();
    }
    return default_string;
}

/**
 * 当前负离子状态
 */
string XlfDeviceWrapper::getSeedMachineAnionStat(string deviceId)
{
    SeedMachineControl *seedControl = (SeedMachineControl *)getDeviceControl(deviceId);
    if(NULL != seedControl)
    {
        return seedControl->getAnionStat();
    }
    return default_string;
}

/**
 * 当前灯状态
 */
string XlfDeviceWrapper::getSeedMachineLightStat(string deviceId)
{
    SeedMachineControl *seedControl = (SeedMachineControl *)getDeviceControl(deviceId);
    if(NULL != seedControl)
    {
        return seedControl->getLightStat();
    }
    return default_string;
}

/**
 * 当前温度
 */
string XlfDeviceWrapper::getSeedMachineCurTemp(string deviceId)
{
    SeedMachineControl *seedControl = (SeedMachineControl *)getDeviceControl(deviceId);
    if(NULL != seedControl)
    {
        return seedControl->getCurTemp();
    }
    return default_string;
}

/**
 * 当前湿度
 */
string XlfDeviceWrapper::getSeedMachineCurHumi(string deviceId)
{
    SeedMachineControl *seedControl = (SeedMachineControl *)getDeviceControl(deviceId);
    if(NULL != seedControl)
    {
        return seedControl->getCurHumi();
    }
    return default_string;
}

/**
 * 是否有外接传感器
 */
string XlfDeviceWrapper::getSeedMachineHasExtralSensor(string deviceId)
{
    SeedMachineControl *seedControl = (SeedMachineControl *)getDeviceControl(deviceId);
    if(NULL != seedControl)
    {
        return seedControl->hasExtralSensor();
    }
    return default_string;
}

/**
 * 获得外接温度值，只在外接传感器存在时有效
 */
string XlfDeviceWrapper::getSeedMachineExtralTemp(string deviceId)
{
    SeedMachineControl *seedControl = (SeedMachineControl *)getDeviceControl(deviceId);
    if(NULL != seedControl)
    {
        return seedControl->getExtralTemp();
    }
    return default_string;
}

/**
 * 获得外接湿度值，只在外接传感器存在时有效
 */
string XlfDeviceWrapper::getSeedMachineExtralHumi(string deviceId)
{
    SeedMachineControl *seedControl = (SeedMachineControl *)getDeviceControl(deviceId);
    if(NULL != seedControl)
    {
        return seedControl->getExtralHumi();
    }
    return default_string;
}

/**
 * 获得外接Pm2.5值，只在外接传感器存在时有效，单位ug/m3
 */
string XlfDeviceWrapper::getSeedMachineExtralPm2_5(string deviceId)
{
    SeedMachineControl *seedControl = (SeedMachineControl *)getDeviceControl(deviceId);
    if(NULL != seedControl)
    {
        return seedControl->getExtralPm2_5();
    }
    return default_string;
}

/**
 * 是否有灯报警
 */
string XlfDeviceWrapper::getSeedMachineLightWarn(string deviceId)
{
    SeedMachineControl *seedControl = (SeedMachineControl *)getDeviceControl(deviceId);
    if(NULL != seedControl)
    {
        return seedControl->lightWarn();
    }
    return default_string;
}

/**
 * 当前是第几层灯报警
 */
string XlfDeviceWrapper::getSeedMachinLlightWarnInfo(string deviceId)
{
    SeedMachineControl *seedControl = (SeedMachineControl *)getDeviceControl(deviceId);
    if(NULL != seedControl)
    {
        return seedControl->lightWarnInfo();
    }
    return default_string;
}

/**
 * 是否有水位报警
 */
string XlfDeviceWrapper::getSeedMachineWaterLevelWarn(string deviceId)
{
    SeedMachineControl *seedControl = (SeedMachineControl *)getDeviceControl(deviceId);
    if(NULL != seedControl)
    {
        return seedControl->waterLevelWarn();
    }
    return default_string;
}

/**
 * 是否有水泵报警
 */
string XlfDeviceWrapper::getSeedMachinePumpWarn(string deviceId)
{
    SeedMachineControl *seedControl = (SeedMachineControl *)getDeviceControl(deviceId);
    if(NULL != seedControl)
    {
        return seedControl->waterLevelWarn();
    }
    return default_string;
}

/**
 * 营养液报警
 */
string XlfDeviceWrapper::getSeedMachineNutritionWarn(string deviceId)
{
    SeedMachineControl *seedControl = (SeedMachineControl *)getDeviceControl(deviceId);
    if(NULL != seedControl)
    {
        return seedControl->nutritionWarn();
    }
    return default_string;
}


/*************************************** sensor *************************************************/
/************************** 控制 **************************/
/** PM2.5开关设置 设置功能：power[1] */
string XlfDeviceWrapper::setSensorPM2_5Power(string deviceId, int power)
{
    SensorsFourInOneControl *sensorControl = (SensorsFourInOneControl *)getDeviceControl(deviceId);
    if(NULL != sensorControl)
    {
        return sensorControl->setPM2_5Power(power);
    }
    return default_string;
}

/** 传感器电源控制 切断 上电 电源控制：power[0/1] 传感器ID: [1 温度、2湿度、3 甲醛、4 PM2.5] */
string XlfDeviceWrapper::setSensorsPower(string deviceId, int power, int sensorID)
{
    SensorsFourInOneControl *sensorControl = (SensorsFourInOneControl *)getDeviceControl(deviceId);
    if(NULL != sensorControl)
    {
        return sensorControl->setSensorsPower(power,sensorID);
    }
    return default_string;
}

/**
 * 主动上报频率设置 是否设置上报频率：responseFrequencyValid[0/1] 传感器ID responseID : [1 温度、2湿度、3 甲醛、4 PM2.5] 上报频率(单位
 * 秒)：responseFrequency
 */
string XlfDeviceWrapper::setSensorResponseFrequency(string deviceId ,int responseFrequencyValid, int responseID, int responseFrequency)
{
    SensorsFourInOneControl *sensorControl = (SensorsFourInOneControl *)getDeviceControl(deviceId);
    if(NULL != sensorControl)
    {
        return sensorControl->setResponseFrequency(responseFrequencyValid,responseID,responseFrequency);
    }
    return default_string;
}

/************************** 状态查询 **************************/
/** 获取 温度传感器ID */
string XlfDeviceWrapper::getSensorTemperatureSensorID(string deviceId)
{
    SensorsFourInOneControl *sensorControl = (SensorsFourInOneControl *)getDeviceControl(deviceId);
    if(NULL != sensorControl)
    {
        return sensorControl->getTemperatureSensorID();
    }
    return default_string;
}

/** 获取 温度值是否有效 */
string XlfDeviceWrapper::getSensorTemperatureValueValid(string deviceId)
{
    SensorsFourInOneControl *sensorControl = (SensorsFourInOneControl *)getDeviceControl(deviceId);
    if(NULL != sensorControl)
    {
        return sensorControl->getTemperatureValueValid();
    }
    return default_string;
}

/** 获取 温度传感器电源状态 */
string XlfDeviceWrapper::getSensorTemperatureSensorPowerStatus(string deviceId)
{
    SensorsFourInOneControl *sensorControl = (SensorsFourInOneControl *)getDeviceControl(deviceId);
    if(NULL != sensorControl)
    {
        return sensorControl->getTemperatureSensorPowerStatus();
    }
    return default_string;
}

/** 获取 上次读温度值时间 */
string XlfDeviceWrapper::getSensorTemperatureInterval(string deviceId)
{
    SensorsFourInOneControl *sensorControl = (SensorsFourInOneControl *)getDeviceControl(deviceId);
    if(NULL != sensorControl)
    {
        return sensorControl->getTemperatureInterval();
    }
    return default_string;
}

/** 获取 温度值 */
string XlfDeviceWrapper::getSensorTemperatureValue(string deviceId)
{
    SensorsFourInOneControl *sensorControl = (SensorsFourInOneControl *)getDeviceControl(deviceId);
    if(NULL != sensorControl)
    {
        return sensorControl->getTemperatureValue();
    }
    return default_string;
}

/** 获取 湿度传感器ID */
string XlfDeviceWrapper::getSensorHumiditySensorID(string deviceId)
{
    SensorsFourInOneControl *sensorControl = (SensorsFourInOneControl *)getDeviceControl(deviceId);
    if(NULL != sensorControl)
    {
        return sensorControl->getHumiditySensorID();
    }
    return default_string;
}

/** 获取 湿度值是否有效 */
string XlfDeviceWrapper::getSensorHumidityValueValid(string deviceId)
{
    SensorsFourInOneControl *sensorControl = (SensorsFourInOneControl *)getDeviceControl(deviceId);
    if(NULL != sensorControl)
    {
        return sensorControl->getHumidityValueValid();
    }
    return default_string;
}

/** 获取 湿度传感器电源状态 */
string XlfDeviceWrapper::getSensorHumiditySensorPowerStatus(string deviceId)
{
    SensorsFourInOneControl *sensorControl = (SensorsFourInOneControl *)getDeviceControl(deviceId);
    if(NULL != sensorControl)
    {
        return sensorControl->getHumiditySensorPowerStatus();
    }
    return default_string;
}

/** 获取 上次读湿度值时间 */
string XlfDeviceWrapper::getSensorHumidityInterval(string deviceId)
{
    SensorsFourInOneControl *sensorControl = (SensorsFourInOneControl *)getDeviceControl(deviceId);
    if(NULL != sensorControl)
    {
        return sensorControl->getHumidityInterval();
    }
    return default_string;
}

/** 获取 湿度值 */
string XlfDeviceWrapper::getSensorHumidityValue(string deviceId)
{
    SensorsFourInOneControl *sensorControl = (SensorsFourInOneControl *)getDeviceControl(deviceId);
    if(NULL != sensorControl)
    {
        return sensorControl->getHumidityValue();
    }
    return default_string;
}

/** 获取 甲醛传感器ID */
string XlfDeviceWrapper::getSensorH2COSensorID(string deviceId)
{
    SensorsFourInOneControl *sensorControl = (SensorsFourInOneControl *)getDeviceControl(deviceId);
    if(NULL != sensorControl)
    {
        return sensorControl->getH2COSensorID();
    }
    return default_string;
}

/** 获取 甲醛值是否有效 */
string XlfDeviceWrapper::getSensorH2COValueValid(string deviceId)
{
    SensorsFourInOneControl *sensorControl = (SensorsFourInOneControl *)getDeviceControl(deviceId);
    if(NULL != sensorControl)
    {
        return sensorControl->getH2COValueValid();
    }
    return default_string;
}

/** 获取 甲醛传感器电源状态 */
string XlfDeviceWrapper::getSensorH2COSensorPowerStatus(string deviceId)
{
    SensorsFourInOneControl *sensorControl = (SensorsFourInOneControl *)getDeviceControl(deviceId);
    if(NULL != sensorControl)
    {
        return sensorControl->getH2COSensorPowerStatus();
    }
    return default_string;
}

/** 获取 上次读甲醛值时间 */
string XlfDeviceWrapper::getSensorH2COInterval(string deviceId)
{
    SensorsFourInOneControl *sensorControl = (SensorsFourInOneControl *)getDeviceControl(deviceId);
    if(NULL != sensorControl)
    {
        return sensorControl->getH2COInterval();
    }
    return default_string;
}

/** 获取 甲醛值 */
string XlfDeviceWrapper::getSensorH2COValue(string deviceId)
{
    SensorsFourInOneControl *sensorControl = (SensorsFourInOneControl *)getDeviceControl(deviceId);
    if(NULL != sensorControl)
    {
        return sensorControl->getH2COValue();
    }
    return default_string;
}

/** 获取 PM2.5传感器ID */
string XlfDeviceWrapper::getSensorPM2_5SensorID(string deviceId)
{
    SensorsFourInOneControl *sensorControl = (SensorsFourInOneControl *)getDeviceControl(deviceId);
    if(NULL != sensorControl)
    {
        return sensorControl->getPM2_5SensorID();
    }
    return default_string;
}

/** 获取 PM2.5值是否有效 */
string XlfDeviceWrapper::getSensorPM2_5ValueValid(string deviceId)
{
    SensorsFourInOneControl *sensorControl = (SensorsFourInOneControl *)getDeviceControl(deviceId);
    if(NULL != sensorControl)
    {
        return sensorControl->getPM2_5ValueValid();
    }
    return default_string;
}

/** 获取 PM2.5传感器电源状态 */
string XlfDeviceWrapper::getSensorPM2_5SensorPowerStatus(string deviceId)
{
    SensorsFourInOneControl *sensorControl = (SensorsFourInOneControl *)getDeviceControl(deviceId);
    if(NULL != sensorControl)
    {
        return sensorControl->getPM2_5SensorPowerStatus();
    }
    return default_string;
}

/** 获取 上次读PM2.5值时间 */
string XlfDeviceWrapper::getSensorPM2_5Interval(string deviceId)
{
    SensorsFourInOneControl *sensorControl = (SensorsFourInOneControl *)getDeviceControl(deviceId);
    if(NULL != sensorControl)
    {
        return sensorControl->getPM2_5Interval();
    }
    return default_string;
}

/** 获取 PM2.5值 */
string XlfDeviceWrapper::getSensorPM2_5Value(string deviceId)
{
    SensorsFourInOneControl *sensorControl = (SensorsFourInOneControl *)getDeviceControl(deviceId);
    if(NULL != sensorControl)
    {
        return sensorControl->getPM2_5Value();
    }
    return default_string;
}

/** 获取 CO2传感器ID */
string XlfDeviceWrapper::getSensorCO2SensorID(string deviceId)
{
    SensorsFourInOneControl *sensorControl = (SensorsFourInOneControl *)getDeviceControl(deviceId);
    if(NULL != sensorControl)
    {
        return sensorControl->getCO2SensorID();
    }
    return default_string;
}

/** 获取 CO2值是否有效 */
string XlfDeviceWrapper::getSensorCO2ValueValid(string deviceId)
{
    SensorsFourInOneControl *sensorControl = (SensorsFourInOneControl *)getDeviceControl(deviceId);
    if(NULL != sensorControl)
    {
        return sensorControl->getCO2ValueValid();
    }
    return default_string;
}

/** 获取 CO2传感器电源状态 */
string XlfDeviceWrapper::getSensorCO2SensorPowerStatus(string deviceId)
{
    SensorsFourInOneControl *sensorControl = (SensorsFourInOneControl *)getDeviceControl(deviceId);
    if(NULL != sensorControl)
    {
        return sensorControl->getCO2SensorPowerStatus();
    }
    return default_string;
}

/** 获取 上次读CO2值时间 */
string XlfDeviceWrapper::getSensorCO2Interval(string deviceId)
{
    SensorsFourInOneControl *sensorControl = (SensorsFourInOneControl *)getDeviceControl(deviceId);
    if(NULL != sensorControl)
    {
        return sensorControl->getCO2Interval();
    }
    return default_string;
}

/** 获取 CO2值 */
string XlfDeviceWrapper::getSensorCO2Value(string deviceId)
{
    SensorsFourInOneControl *sensorControl = (SensorsFourInOneControl *)getDeviceControl(deviceId);
    if(NULL != sensorControl)
    {
        return sensorControl->getCO2Value();
    }
    return default_string;
}

/** 获取 转换板通信错误 */
string XlfDeviceWrapper::getSensorIsPeripheralsCommunicationError(string deviceId)
{
    SensorsFourInOneControl *sensorControl = (SensorsFourInOneControl *)getDeviceControl(deviceId);
    if(NULL != sensorControl)
    {
        return sensorControl->getIsPeripheralsCommunicationError();
    }
    return default_string;
}

/*********************************** Smartlight *******************************************/
/********************* 控制 *********************/
/** 电源设置 此方法未实现 */
string XlfDeviceWrapper::setSmartlightPower(string deviceId, int power)
{
    SmartLightControl *lightControl = (SmartLightControl *)getDeviceControl(deviceId);
    if(NULL != lightControl)
    {
        return lightControl->setPower(power);
    }
    return default_string;
}

/** 亮度设置：0~100 */
string XlfDeviceWrapper::setSmartlightBrightness(string deviceId, int brightnessValue)
{
    SmartLightControl *lightControl = (SmartLightControl *)getDeviceControl(deviceId);
    if(NULL != lightControl)
    {
        return lightControl->setBrightness(brightnessValue);
    }
    return default_string;
}

/** R G B 三元色设置 取值范围均为[0-255] */
string XlfDeviceWrapper::setSmartlightRGB(string deviceId, int redValue, int greenValue, int blueValue)
{
    SmartLightControl *lightControl = (SmartLightControl *)getDeviceControl(deviceId);
    if(NULL != lightControl)
    {
        return lightControl->setRGB(redValue,greenValue,blueValue);
    }
    return default_string;
}

/** 空气状况 3 优、2 良、1 一般 */
string XlfDeviceWrapper::setSmartlightAirQualityLevel(string deviceId, int airQualityLevel)
{
    SmartLightControl *lightControl = (SmartLightControl *)getDeviceControl(deviceId);
    if(NULL != lightControl)
    {
        return lightControl->setAirQualityLevel(airQualityLevel);
    }
    return default_string;
}

/** 色温设置(0~65535) 此方法未实现 */
string XlfDeviceWrapper::setSmartlightColorTemperature(string deviceId, int colorTemperatureValue)
{
    SmartLightControl *lightControl = (SmartLightControl *)getDeviceControl(deviceId);
    if(NULL != lightControl)
    {
        return lightControl->setColorTemperature(colorTemperatureValue);
    }
    return default_string;
}

// 新增 2015.11.12
/**
 * 设备状态 0 为正常，1 为掉线
 * @param deviceStatus 0 为正常，1 为掉线
 * @return byte[]
 */
string XlfDeviceWrapper::setSmartlightDeviceStatus(string deviceId, int deviceStatus)
{
    SmartLightControl *lightControl = (SmartLightControl *)getDeviceControl(deviceId);
    if(NULL != lightControl)
    {
        return lightControl->setDeviceStatus(deviceStatus);
    }
    return default_string;
}

/******************** 状态查询 *************************/
/** 开关状态 此方法未实现 */
string XlfDeviceWrapper::getSmartlightPower(string deviceId)
{
    SmartLightControl *lightControl = (SmartLightControl *)getDeviceControl(deviceId);
    if(NULL != lightControl)
    {
        return lightControl->getPower();
    }
    return default_string;
}

/** RGB 值是否有效 */
string XlfDeviceWrapper::getSmartlightRGBSetValid(string deviceId)
{
    SmartLightControl *lightControl = (SmartLightControl *)getDeviceControl(deviceId);
    if(NULL != lightControl)
    {
        return lightControl->getRGBSetValid();
    }
    return default_string;
}

/** 红色值 */
string XlfDeviceWrapper::getSmartlightRedValue(string deviceId)
{
    SmartLightControl *lightControl = (SmartLightControl *)getDeviceControl(deviceId);
    if(NULL != lightControl)
    {
        return lightControl->getRedValue();
    }
    return default_string;
}

/** 绿色值 */
string XlfDeviceWrapper::getSmartlightGreenValue(string deviceId)
{
    SmartLightControl *lightControl = (SmartLightControl *)getDeviceControl(deviceId);
    if(NULL != lightControl)
    {
        return lightControl->getGreenValue();
    }
    return default_string;
}

/** 蓝色值 */
string XlfDeviceWrapper::getSmartlightBlueValue(string deviceId)
{
    SmartLightControl *lightControl = (SmartLightControl *)getDeviceControl(deviceId);
    if(NULL != lightControl)
    {
        return lightControl->getBlueValue();
    }
    return default_string;
}

/** 色温值是否有效 此方法未实现 */
string XlfDeviceWrapper::getSmartlightColorTemperatureValid(string deviceId)
{
    SmartLightControl *lightControl = (SmartLightControl *)getDeviceControl(deviceId);
    if(NULL != lightControl)
    {
        return lightControl->getColorTemperatureValid();
    }
    return default_string;
}

/** 色温值(0~65535) 此方法未实现 */
string XlfDeviceWrapper::getSmartlightColorTemperatureValue(string deviceId)
{
    SmartLightControl *lightControl = (SmartLightControl *)getDeviceControl(deviceId);
    if(NULL != lightControl)
    {
        return lightControl->getColorTemperatureValue();
    }
    return default_string;
}

/** 亮度值是否有效 */
string XlfDeviceWrapper::getSmartlightBrightnessValid(string deviceId)
{
    SmartLightControl *lightControl = (SmartLightControl *)getDeviceControl(deviceId);
    if(NULL != lightControl)
    {
        return lightControl->getBrightnessValid();
    }
    return default_string;
}

/** 亮度 */
string XlfDeviceWrapper::getSmartlightBrightnessValue(string deviceId)
{
    SmartLightControl *lightControl = (SmartLightControl *)getDeviceControl(deviceId);
    if(NULL != lightControl)
    {
        return lightControl->getBrightnessValue();
    }
    return default_string;
}

// 新增状态查询 2015.11.12
/**
 * 设备状态 0 为有效，1 为无效
 * @return  0 为有效，1 为无效
 */
string XlfDeviceWrapper::getSmartlightDeviceStatusValid(string deviceId)
{
    SmartLightControl *lightControl = (SmartLightControl *)getDeviceControl(deviceId);
    if(NULL != lightControl)
    {
        return lightControl->getDeviceStatusValid();
    }
    return default_string;
}

/**
 * 设备状态 0 为正常，1 为掉线
 * @return 0 为正常，1 为掉线
 */
string XlfDeviceWrapper::getSmartlightDeviceStatus(string deviceId)
{
    SmartLightControl *lightControl = (SmartLightControl *)getDeviceControl(deviceId);
    if(NULL != lightControl)
    {
        return lightControl->getDeviceStatus();
    }
    return default_string;
}

/**
 * 空气状况是否有效 0 为有效，1 为无效
 * @return 0 为有效，1 为无效
 */
string XlfDeviceWrapper::getSmartlightAirStatusValid(string deviceId)
{
    SmartLightControl *lightControl = (SmartLightControl *)getDeviceControl(deviceId);
    if(NULL != lightControl)
    {
        return lightControl->getAirStatusValid();
    }
    return default_string;
}

/**
 * 空气状况 3 优、2 良、1 一般
 * @return  3 优、2 良、1 一般
 */
string XlfDeviceWrapper::getSmartlightAirStatus(string deviceId)
{
    SmartLightControl *lightControl = (SmartLightControl *)getDeviceControl(deviceId);
    if(NULL != lightControl)
    {
        return lightControl->getAirStatus();
    }
    return default_string;
}

/**
 * 转换板通信错误
 * @return 0为正常，1为通信错误
 */
string XlfDeviceWrapper::getSmartlightIsPeripheralsCommunicationError(string deviceId)
{
    SmartLightControl *lightControl = (SmartLightControl *)getDeviceControl(deviceId);
    if(NULL != lightControl)
    {
        return lightControl->getIsPeripheralsCommunicationError();
    }
    return default_string;
}

/************************ SmartCurtain ***********************/
/** 模式：Mode : 设置功能:0打开、1 关闭、2停止、3 重启 */
string XlfDeviceWrapper::setSmartCurtainMode(string deviceId, int mode)
{
    SmartCurtainControl *curtainControl = (SmartCurtainControl *)getDeviceControl(deviceId);
    if(NULL != curtainControl)
    {
        return curtainControl->setMode(mode);
    }
    return default_string;
}

/** 定点控制：Pos : 设置功能:设置的定点位置(0~16)，全开位置是0，中间闭合位置是16，每次设置位置间隔距离应大于等于4个单位 */
string XlfDeviceWrapper::setSmartCurtainPosition(string deviceId,int position)
{
    SmartCurtainControl *curtainControl = (SmartCurtainControl *)getDeviceControl(deviceId);
    if(NULL != curtainControl)
    {
        return curtainControl->setPosition(position);
    }
    return default_string;
}

/** Open or Close state 参数是否有效 */
string XlfDeviceWrapper::getSmartCurtainPowerStatusParameterIsValid(string deviceId)
{
    SmartCurtainControl *curtainControl = (SmartCurtainControl *)getDeviceControl(deviceId);
    if(NULL != curtainControl)
    {
        return curtainControl->getPowerStatusParameterIsValid();
    }
    return default_string;
}

/** Open or Close state 开关状态 */
string XlfDeviceWrapper::getSmartCurtainPowerStatus(string deviceId)
{
    SmartCurtainControl *curtainControl = (SmartCurtainControl *)getDeviceControl(deviceId);
    if(NULL != curtainControl)
    {
        return curtainControl->getPowerStatus();
    }
    return default_string;
}

/** 点位置 参数是否有效 */
string XlfDeviceWrapper::getSmartCurtainPositionParameterIsValid(string deviceId)
{
    SmartCurtainControl *curtainControl = (SmartCurtainControl *)getDeviceControl(deviceId);
    if(NULL != curtainControl)
    {
        return curtainControl->getPositionParameterIsValid();
    }
    return default_string;
}

/** 当前的定点位置 */
string XlfDeviceWrapper::getSmartCurtainPositionStatus(string deviceId)
{
    SmartCurtainControl *curtainControl = (SmartCurtainControl *)getDeviceControl(deviceId);
    if(NULL != curtainControl)
    {
        return curtainControl->getPositionStatus();
    }
    return default_string;
}

/**
 * 转换板通信错误
 * @return 0为正常，1为通信错误
 */
string XlfDeviceWrapper::getSmartCurtainIsPeripheralsCommunicationError(string deviceId)
{
    SmartCurtainControl *curtainControl = (SmartCurtainControl *)getDeviceControl(deviceId);
    if(NULL != curtainControl)
    {
        return curtainControl->getIsPeripheralsCommunicationError();
    }
    return default_string;
}

/*********************************** Voltameter *******************************************/
/** 总的电源开关 */
string XlfDeviceWrapper::setVoltameterPower(string deviceId, int power)
{
    VoltameterControl *voltameterControl = (VoltameterControl *)getDeviceControl(deviceId);
    if(NULL != voltameterControl)
    {
        return voltameterControl->setPower(power);
    }
    return default_string;
}

/** 电量统计清0 1清零，0不清零 */
string XlfDeviceWrapper::setVoltameterResetCount(string deviceId, int isResetCount)
{
    VoltameterControl *voltameterControl = (VoltameterControl *)getDeviceControl(deviceId);
    if(NULL != voltameterControl)
    {
        return voltameterControl->setResetCount(isResetCount);
    }
    return default_string;
}

/** 总电源开关状态 */
string XlfDeviceWrapper::getVoltameterPower(string deviceId)
{
    VoltameterControl *voltameterControl = (VoltameterControl *)getDeviceControl(deviceId);
    if(NULL != voltameterControl)
    {
        return voltameterControl->getPower();
    }
    return default_string;
}

/** 电流值uA */
string XlfDeviceWrapper::getVoltameterCurrentValue(string deviceId)
{
    VoltameterControl *voltameterControl = (VoltameterControl *)getDeviceControl(deviceId);
    if(NULL != voltameterControl)
    {
        return voltameterControl->getCurrentValue();
    }
    return default_string;
}

/** 电压值mV */
string XlfDeviceWrapper::getVoltameterVoltageValue(string deviceId)
{
    VoltameterControl *voltameterControl = (VoltameterControl *)getDeviceControl(deviceId);
    if(NULL != voltameterControl)
    {
        return voltameterControl->getVoltageValue();
    }
    return default_string;
}

/** 电量值的统计 */
string XlfDeviceWrapper::getVoltameterValue(string deviceId)
{
    VoltameterControl *voltameterControl = (VoltameterControl *)getDeviceControl(deviceId);
    if(NULL != voltameterControl)
    {
        return voltameterControl->getVoltameterValue();
    }
    return default_string;
}

/** 转换板通信错误 */
string XlfDeviceWrapper::getVoltameterIsPeripheralsCommunicationError(string deviceId)
{
    VoltameterControl *voltameterControl = (VoltameterControl *)getDeviceControl(deviceId);
    if(NULL != voltameterControl)
    {
        return voltameterControl->getIsPeripheralsCommunicationError();
    }
    return default_string;
}


/*********************************** Oven *******************************************/
/****************** set ******************/
// 烤箱开机
string XlfDeviceWrapper::setOvenPowerOn(string deviceId, bool isPowerOn, bool manualOrnot,int flag)
{
    OvenControl *ovenControl = (OvenControl *)getDeviceControl(deviceId);
    if(NULL != ovenControl)
    {
        return ovenControl->setPowerOn(isPowerOn, manualOrnot,flag);
    }
    return default_string;
}

// 烤箱关机
string XlfDeviceWrapper::setOvenPowerOff(string deviceId, bool isPowerOn, bool manualOrnot,int flag)
{
    OvenControl *ovenControl = (OvenControl *)getDeviceControl(deviceId);
    if(NULL != ovenControl)
    {
        return ovenControl->setPowerOff(isPowerOn, manualOrnot,flag);
    }
    return default_string;
}

// 风机开关
string XlfDeviceWrapper::setOvenFS(string deviceId, long uid, bool isOpen, bool manualOrnot,int flag)
{	
    OvenControl *ovenControl = (OvenControl *)getDeviceControl(deviceId);
    if(NULL != ovenControl)
    {
        return ovenControl->setFS(uid, isOpen, manualOrnot,flag);
    }
    return default_string;
}

// 转叉开关
string XlfDeviceWrapper::setOvenZC(string deviceId, long uid, bool isOpen, bool manualOrnot,int flag)
{
    OvenControl *ovenControl = (OvenControl *)getDeviceControl(deviceId);
    if(NULL != ovenControl)
    {
        return ovenControl->setZC(uid, isOpen, manualOrnot,flag);
    }
    return default_string;
}

// 炉灯开关
string XlfDeviceWrapper::setOvenD(string deviceId, long uid, bool isOpen,bool manualOrnot,int flag)
{
    OvenControl *ovenControl = (OvenControl *)getDeviceControl(deviceId);
    if(NULL != ovenControl)
    {
        return ovenControl->setD(uid, isOpen, manualOrnot,flag);
    }
    return default_string;
}

// 上下管温度设置
string XlfDeviceWrapper::setOvenUDTubeTemperature(string deviceId, long uid, int temperatureU, int temperatureM, int temperatureD ,bool manualOrnot,int flag)
{
    OvenControl *ovenControl = (OvenControl *)getDeviceControl(deviceId);
    if(NULL != ovenControl)
    {
        return ovenControl->setUDTubeTemperature(uid, temperatureU, temperatureM, temperatureD, manualOrnot,flag);
    }
    return default_string;
}

// 状态查询
string XlfDeviceWrapper::getOvenStatus(string deviceId, bool manualOrnot,int flag)
{
    OvenControl *ovenControl = (OvenControl *)getDeviceControl(deviceId);
    if(NULL != ovenControl)
    {
        return ovenControl->getStatus(manualOrnot,flag);
    }
    return default_string;
}

// 功能查询
string XlfDeviceWrapper::getOvenGN(string deviceId, bool manualOrnot,int flag)
{
    OvenControl *ovenControl = (OvenControl *)getDeviceControl(deviceId);
    if(NULL != ovenControl)
    {
        return ovenControl->getGN(manualOrnot,flag);
    }
    return default_string;
}

// 设置菜单名字
string XlfDeviceWrapper::setOvenMenuName(string deviceId, long uid, int menuNub, int sub_node, int time, string name, bool manualOrnot,int flag)
{
    OvenControl *ovenControl = (OvenControl *)getDeviceControl(deviceId);
    if(NULL != ovenControl)
    {
        return ovenControl->setMenuName(uid, menuNub, sub_node, time, name, manualOrnot,flag);
    }
    return default_string;
}

/**
 * 1.9	设置菜单温度命令扩展	新增		不确定AT指令顺序是否正确
 *
 * 参数： 菜谱编号[0/1/2]，子节点[0-9]，时间-高位[0~0x46]，时间-低位[0~254]，
 * 上管温度-高位[暂时为 0], 上管温度-低位[40~230]， 下管温度-高位[暂时为 0], 下管温度-低位[40~230]，
 * 转叉开关[0/1],风机开关[0/1],提醒暂停[0/1], 时间有效设置位[0/1] ，
 * 上管温度有效设置位[0/1] ，下管温度有效设置位[0/1] ，转叉开关有效设置位[0/1]，
 * 风机开关有效设置位[0/1]，提醒暂停有效设置位[0/1]，提示声[0/1]，帧序号[0-254]
 * */
string XlfDeviceWrapper::setOvenMenuTemperatureExtend(string deviceId, long uid, int menuNub, int sub_node, int time, int temperatureU, int temperatureM,\
	int temperatureD, bool rotary_fork, bool fan_power, bool remind_suspend, bool time_effective, bool upper_tube_temperature_effective,\
	bool middle_tube_temperature_effective, bool lower_tube_temperature_effective, bool rotary_fork_effective, \
	bool fan_power_effective, bool remind_suspend_effective, int a_x, bool manualOrnot,int flag)
{
    OvenControl *ovenControl = (OvenControl *)getDeviceControl(deviceId);
    if(NULL != ovenControl)
    {
        return ovenControl->setMenuTemperatureExtend(uid, menuNub,sub_node,time,temperatureU,temperatureM,temperatureD,rotary_fork,fan_power,\
			remind_suspend,time_effective,upper_tube_temperature_effective,middle_tube_temperature_effective,lower_tube_temperature_effective,\
		rotary_fork_effective,fan_power_effective,remind_suspend_effective,a_x,manualOrnot,flag);
    }
    return default_string;
}

/**
 * 	曲线完整性检查
 */
string XlfDeviceWrapper::setOvenCheckCurveIntegrity(string deviceId, long uid, int menuNub,bool manualOrnot,int flag)
{
    OvenControl *ovenControl = (OvenControl *)getDeviceControl(deviceId);
    if(NULL != ovenControl)
    {
        return ovenControl->checkCurveIntegrity(uid, menuNub, manualOrnot,flag);
    }
    return default_string;
}

/**
 * 	曲线执行命令
 */
string XlfDeviceWrapper::setOvenExcuteCurveCmd(string deviceId, long uid, int menuNub,bool manualOrnot,int flag)
{
    OvenControl *ovenControl = (OvenControl *)getDeviceControl(deviceId);
    if(NULL != ovenControl)
    {
        return ovenControl->excuteCurveCmd(uid, menuNub, manualOrnot,flag);
    }
    return default_string;
}

/**
 *  获取菜单名字
 */
string XlfDeviceWrapper::setOvenMenuName(string deviceId, int menuNub,bool manualOrnot,int flag)
{
    OvenControl *ovenControl = (OvenControl *)getDeviceControl(deviceId);
    if(NULL != ovenControl)
    {
        return ovenControl->getMenuName(menuNub, manualOrnot,flag);
    }
    return default_string;
}

/**
 *   获取温度曲线扩展命令
 *   菜谱编号[0/1/2/3]，子节点[0-9]，提示声[0/1]，帧序号[0-254]
 */
string XlfDeviceWrapper::setOvenMenuTemperatureExtend(string deviceId, int menuNub,int sub_node, int a_x ,bool manualOrnot,int flag)
{
    OvenControl *ovenControl = (OvenControl *)getDeviceControl(deviceId);
    if(NULL != ovenControl)
    {
        return ovenControl->getMenuTemperatureExtend(menuNub, sub_node, a_x, manualOrnot,flag);
    }
    return default_string;
}

/**
 * 	曲线取消执行命令
 *  菜谱编号[0/1/2]，提示声[0/1]，帧序号[0]
 *
 */
string XlfDeviceWrapper::setOvenCancelExcuteCurveCmd(string deviceId, long uid, int menuNub ,bool manualOrnot,int flag)
{
    OvenControl *ovenControl = (OvenControl *)getDeviceControl(deviceId);
    if(NULL != ovenControl)
    {
        return ovenControl->cancelExcuteCurveCmd(uid, menuNub, manualOrnot,flag);
    }
    return default_string;
}

/**
 * 	曲线暂停-继续操作命令
 *  菜谱编号[0/1/2]，暂停或继续[0/1],提示声[0/1]，帧序号[0]
 */
string XlfDeviceWrapper::setOvenPauseOrContinueCurve(string deviceId, long uid, int menuNub,bool pause_or_continue, bool manualOrnot,int flag)
{
    OvenControl *ovenControl = (OvenControl *)getDeviceControl(deviceId);
    if(NULL != ovenControl)
    {
        return ovenControl->pauseOrContinueCurve(uid, menuNub, pause_or_continue, manualOrnot,flag);
    }
    return default_string;
}

/****************** getStatus ******************/
// 获取烤箱uid
long XlfDeviceWrapper::getOvenUid(string deviceId)
{
    OvenControl *ovenControl = (OvenControl *)getDeviceControl(deviceId);
    if(NULL != ovenControl)
    {
        return ovenControl->getUid();
    }
    return 0;
}

// 预热状态
bool XlfDeviceWrapper::getOvenStatuYR(string deviceId)
{
    OvenControl *ovenControl = (OvenControl *)getDeviceControl(deviceId);
    if(NULL != ovenControl)
    {
        return ovenControl->getStatuYR();
    }
    return 0;
}

// 整机开关状态
bool XlfDeviceWrapper::getOvenStatuKJ(string deviceId)
{
    OvenControl *ovenControl = (OvenControl *)getDeviceControl(deviceId);
    if(NULL != ovenControl)
    {
        return ovenControl->getStatuKJ();
    }
    return 0;
}

// 炉灯开关状态
bool XlfDeviceWrapper::getOvenStatuD(string deviceId)
{
    OvenControl *ovenControl = (OvenControl *)getDeviceControl(deviceId);
    if(NULL != ovenControl)
    {
        return ovenControl->getStatuD();
    }
    return 0;
}

// 转叉开关状态
bool XlfDeviceWrapper::getOvenStatuZC(string deviceId)
{
    OvenControl *ovenControl = (OvenControl *)getDeviceControl(deviceId);
    if(NULL != ovenControl)
    {
        return ovenControl->getStatuZC();
    }
    return 0;
}

// 风机开关状态
bool XlfDeviceWrapper::getOvenStatuFS(string deviceId)
{
    OvenControl *ovenControl = (OvenControl *)getDeviceControl(deviceId);
    if(NULL != ovenControl)
    {
        return ovenControl->getStatuFS();
    }
    return 0;
}

// 正在烘焙的曲线 （当前无烘焙返回 0xff）
string  XlfDeviceWrapper::getOvenStatuMenuNub(string deviceId)
{
    OvenControl *ovenControl = (OvenControl *)getDeviceControl(deviceId);
    if(NULL != ovenControl)
    {
        return ovenControl->getStatuMenuNub();
    }
    return default_string;
}

// 已完成烘烤时间高位:秒
string  XlfDeviceWrapper::getOvenCompletedtRoastTimeH(string deviceId)
{
    OvenControl *ovenControl = (OvenControl *)getDeviceControl(deviceId);
    if(NULL != ovenControl)
    {
        return ovenControl->geCompletedtRoastTimeH();
    }
    return default_string;
}

// 已完成烘烤时间低位:秒
string  XlfDeviceWrapper::getOvenCompletedRoastTimeL(string deviceId)
{
    OvenControl *ovenControl = (OvenControl *)getDeviceControl(deviceId);
    if(NULL != ovenControl)
    {
        return ovenControl->getCompletedRoastTimeL();
    }
    return default_string;
}

// 当前设置的上管温度-高位
string  XlfDeviceWrapper::getOvenCurrentSettedUTTH(string deviceId)
{
    OvenControl *ovenControl = (OvenControl *)getDeviceControl(deviceId);
    if(NULL != ovenControl)
    {
        return ovenControl->getCurrentSettedUTTH();
    }
    return default_string;
}

// 当前设置的上管温度-低位
string  XlfDeviceWrapper::getOvenCurrentSettedUTTL(string deviceId)
{
    OvenControl *ovenControl = (OvenControl *)getDeviceControl(deviceId);
    if(NULL != ovenControl)
    {
        return ovenControl->getCurrentSettedUTTL();
    }
    return default_string;
}

// 当前设置的上管温度-高位
string  XlfDeviceWrapper::getOvenCurrentSettedMTTH(string deviceId)
{
    OvenControl *ovenControl = (OvenControl *)getDeviceControl(deviceId);
    if(NULL != ovenControl)
    {
        return ovenControl->getCurrentSettedMTTH();
    }
    return default_string;
}

// 当前设置的上管温度-低位
string  XlfDeviceWrapper::getOvenCurrentSettedMTTL(string deviceId)
{
    OvenControl *ovenControl = (OvenControl *)getDeviceControl(deviceId);
    if(NULL != ovenControl)
    {
        return ovenControl->getCurrentSettedMTTL();
    }
    return default_string;
}

// 当前设置的下管温度-高位
string  XlfDeviceWrapper::getOvenCurrentSettedLTTH(string deviceId)
{
    OvenControl *ovenControl = (OvenControl *)getDeviceControl(deviceId);
    if(NULL != ovenControl)
    {
        return ovenControl->getCurrentSettedLTTH();
    }
    return default_string;
}

// 当前设置的下管温度-低位
string  XlfDeviceWrapper::getOvenCurrentSettedLTTL(string deviceId)
{
    OvenControl *ovenControl = (OvenControl *)getDeviceControl(deviceId);
    if(NULL != ovenControl)
    {
        return ovenControl->getCurrentSettedLTTL();
    }
    return default_string;
}

// 当前实际的上管温度-高位
string  XlfDeviceWrapper::getOvenCurrentActualUTTH(string deviceId)
{
    OvenControl *ovenControl = (OvenControl *)getDeviceControl(deviceId);
    if(NULL != ovenControl)
    {
        return ovenControl->getCurrentActualUTTH();
    }
    return default_string;
}

// 当前实际的上管温度-低位
string  XlfDeviceWrapper::getOvenCurrentActualUTTL(string deviceId)
{
    OvenControl *ovenControl = (OvenControl *)getDeviceControl(deviceId);
    if(NULL != ovenControl)
    {
        return ovenControl->getCurrentActualUTTL();
    }
    return default_string;
}

// 当前实际的中管温度-高位
string  XlfDeviceWrapper::getOvenCurrentActualMTTH(string deviceId)
{
    OvenControl *ovenControl = (OvenControl *)getDeviceControl(deviceId);
    if(NULL != ovenControl)
    {
        return ovenControl->getCurrentActualMTTH();
    }
    return default_string;
}

// 当前实际的中管温度-低位
string  XlfDeviceWrapper::getOvenCurrentActualMTTL(string deviceId)
{
    OvenControl *ovenControl = (OvenControl *)getDeviceControl(deviceId);
    if(NULL != ovenControl)
    {
        return ovenControl->getCurrentActualMTTL();
    }
    return default_string;
}

// 当前实际的下管温度-高位
string  XlfDeviceWrapper::getOvenCurrentActualLTTH(string deviceId)
{
    OvenControl *ovenControl = (OvenControl *)getDeviceControl(deviceId);
    if(NULL != ovenControl)
    {
        return ovenControl->getCurrentActualLTTH();
    }
    return default_string;
}

// 当前实际的下管温度-低位
string  XlfDeviceWrapper::getOvenCurrentActualLTTL(string deviceId)
{
    OvenControl *ovenControl = (OvenControl *)getDeviceControl(deviceId);
    if(NULL != ovenControl)
    {
        return ovenControl->getCurrentActualLTTL();
    }
    return default_string;
}

// 当前上管功率(0~100,表示 0~100%)
string  XlfDeviceWrapper::getOvenCurrentUpperTubePower(string deviceId)
{
    OvenControl *ovenControl = (OvenControl *)getDeviceControl(deviceId);
    if(NULL != ovenControl)
    {
        return ovenControl->getCurrentUpperTubePower();
    }
    return default_string;
}

// 当前中管功率(0~100,表示 0~100%)
string  XlfDeviceWrapper::getOvenCurrentLowerTubePower(string deviceId)
{
    OvenControl *ovenControl = (OvenControl *)getDeviceControl(deviceId);
    if(NULL != ovenControl)
    {
        return ovenControl->getCurrentLowerTubePower();
    }
    return default_string;
}

// 当前下管功率(0~100,表示 0~100%)
string  XlfDeviceWrapper::getOvenCurrentMeddleTubePower(string deviceId)
{
    OvenControl *ovenControl = (OvenControl *)getDeviceControl(deviceId);
    if(NULL != ovenControl)
    {
        return ovenControl->getCurrentMeddleTubePower();
    }
    return default_string;
}

// 烤箱状态
string  XlfDeviceWrapper::getOvenStatus(string deviceId)
{
    OvenControl *ovenControl = (OvenControl *)getDeviceControl(deviceId);
    if(NULL != ovenControl)
    {
        return ovenControl->getOvenStatus();
    }
    return default_string;
}

// 温度设置错误
string  XlfDeviceWrapper::getOvenTemperatureSettedError(string deviceId)
{
    OvenControl *ovenControl = (OvenControl *)getDeviceControl(deviceId);
    if(NULL != ovenControl)
    {
        return ovenControl->getTemperatureSettedError();
    }
    return default_string;
}

// 存储设备故障
string  XlfDeviceWrapper::getOvenStorageDeviceError(string deviceId)
{
    OvenControl *ovenControl = (OvenControl *)getDeviceControl(deviceId);
    if(NULL != ovenControl)
    {
        return ovenControl->getStorageDeviceError();
    }
    return default_string;
}

// 烤箱发热装置故障
string  XlfDeviceWrapper::getOvenHeatingDeviceError(string deviceId)
{
    OvenControl *ovenControl = (OvenControl *)getDeviceControl(deviceId);
    if(NULL != ovenControl)
    {
        return ovenControl->getHeatingDeviceError();
    }
    return default_string;
}

// 温度传感器错误
string  XlfDeviceWrapper::getOvenTemperatureSensorError(string deviceId)
{
    OvenControl *ovenControl = (OvenControl *)getDeviceControl(deviceId);
    if(NULL != ovenControl)
    {
        return ovenControl->getTemperatureSensorError();
    }
    return default_string;
}

// I2C 设备错误
string  XlfDeviceWrapper::getOvenI2CDeviceError(string deviceId)
{
    OvenControl *ovenControl = (OvenControl *)getDeviceControl(deviceId);
    if(NULL != ovenControl)
    {
        return ovenControl->getI2CDeviceError();
    }
    return default_string;
}

// 211-0 命令执行结果（当此项为 1 时，检查下面4 项的错误置位）
string  XlfDeviceWrapper::getOven211_0CommandExecutedResult(string deviceId)
{
    OvenControl *ovenControl = (OvenControl *)getDeviceControl(deviceId);
    if(NULL != ovenControl)
    {
        return ovenControl->get211_0CommandExecutedResult();
    }
    return default_string;
}

// 菜单名称错误
string  XlfDeviceWrapper::getOvenMenuNameError(string deviceId)
{
    OvenControl *ovenControl = (OvenControl *)getDeviceControl(deviceId);
    if(NULL != ovenControl)
    {
        return ovenControl->getMenuNameError();
    }
    return default_string;
}

// 总烧烤时间错误
string  XlfDeviceWrapper::getOvenTotalRoastTimeError(string deviceId)
{
    OvenControl *ovenControl = (OvenControl *)getDeviceControl(deviceId);
    if(NULL != ovenControl)
    {
        return ovenControl->getTotalRoastTimeError();
    }
    return default_string;
}

// 曲线个数错误
string  XlfDeviceWrapper::getOvenCurveNumbersError(string deviceId)
{
    OvenControl *ovenControl = (OvenControl *)getDeviceControl(deviceId);
    if(NULL != ovenControl)
    {
        return ovenControl->getCurveNumbersError();
    }
    return default_string;
}

// 菜单曲线错误
string  XlfDeviceWrapper::getOvenMenuCurveError0(string deviceId)
{
    OvenControl *ovenControl = (OvenControl *)getDeviceControl(deviceId);
    if(NULL != ovenControl)
    {
        return ovenControl->getMenuCurveError0();
    }
    return default_string;
}

// 211-2命令执行结果（当此项为 1 时，检查下面 6 项的错误置位）
string  XlfDeviceWrapper::getOven211_2CommandExecutedResult(string deviceId)
{
    OvenControl *ovenControl = (OvenControl *)getDeviceControl(deviceId);
    if(NULL != ovenControl)
    {
        return ovenControl->get211_2CommandExecutedResult();
    }
    return default_string;
}

// 设置时间错误
string  XlfDeviceWrapper::getOvenSettedTimeError(string deviceId)
{
    OvenControl *ovenControl = (OvenControl *)getDeviceControl(deviceId);
    if(NULL != ovenControl)
    {
        return ovenControl->getSettedTimeError();
    }
    return default_string;
}

// 上下管温度设置错误
string  XlfDeviceWrapper::getOvenULTTSettedError(string deviceId)
{
    OvenControl *ovenControl = (OvenControl *)getDeviceControl(deviceId);
    if(NULL != ovenControl)
    {
        return ovenControl->getULTTSettedError();
    }
    return default_string;
}

// 风机设置错误
string  XlfDeviceWrapper::getOvenFanSettedError(string deviceId)
{
    OvenControl *ovenControl = (OvenControl *)getDeviceControl(deviceId);
    if(NULL != ovenControl)
    {
        return ovenControl->getFanSettedError();
    }
    return default_string;
}

// 转叉设置错误
string  XlfDeviceWrapper::getOvenRotaryForkSettedError(string deviceId)
{
    OvenControl *ovenControl = (OvenControl *)getDeviceControl(deviceId);
    if(NULL != ovenControl)
    {
        return ovenControl->getRotaryForkSettedError();
    }
    return default_string;
}

// 曲线子节点过多
string  XlfDeviceWrapper::getOvenCurveSubnodeMoreThanEnoughError(string deviceId)
{
    OvenControl *ovenControl = (OvenControl *)getDeviceControl(deviceId);
    if(NULL != ovenControl)
    {
        return ovenControl->getCurveSubnodeMoreThanEnoughError();
    }
    return default_string;
}

// 菜单曲线错误
string  XlfDeviceWrapper::getOvenMenuCurveError2(string deviceId)
{
    OvenControl *ovenControl = (OvenControl *)getDeviceControl(deviceId);
    if(NULL != ovenControl)
    {
        return ovenControl->getMenuCurveError2();
    }
    return default_string;
}

// 211-3 命令执行结果（0：完整，1：不完整）
string  XlfDeviceWrapper::getOven211_3CommandExecutedResult(string deviceId)
{
    OvenControl *ovenControl = (OvenControl *)getDeviceControl(deviceId);
    if(NULL != ovenControl)
    {
        return ovenControl->get211_3CommandExecutedResult();
    }
    return default_string;
}

// 211-4 命令执行结果（当此项为 1 时，检查下面 4 项的错误置位）
string  XlfDeviceWrapper::getOven211_4CommandExecutedResult(string deviceId)
{
    OvenControl *ovenControl = (OvenControl *)getDeviceControl(deviceId);
    if(NULL != ovenControl)
    {
        return ovenControl->get211_4CommandExecutedResult();
    }
    return default_string;
}

// 曲线错误
string  XlfDeviceWrapper::getOvenMenuCurveError4(string deviceId)
{
    OvenControl *ovenControl = (OvenControl *)getDeviceControl(deviceId);
    if(NULL != ovenControl)
    {
        return ovenControl->getMenuCurveError4();
    }
    return default_string;
}

// 该曲线不存在
string  XlfDeviceWrapper::getOvenCurveNotExistError(string deviceId)
{
    OvenControl *ovenControl = (OvenControl *)getDeviceControl(deviceId);
    if(NULL != ovenControl)
    {
        return ovenControl->getCurveNotExistError();
    }
    return default_string;
}

// 烤箱未开机
string  XlfDeviceWrapper::getOvenNotPowerOnError(string deviceId)
{
    OvenControl *ovenControl = (OvenControl *)getDeviceControl(deviceId);
    if(NULL != ovenControl)
    {
        return ovenControl->getNotPowerOnError();
    }
    return default_string;
}

// 烤箱正工作在烘焙程序中
string  XlfDeviceWrapper::getOvenWorkingInRoastProcedureError(string deviceId)
{
    OvenControl *ovenControl = (OvenControl *)getDeviceControl(deviceId);
    if(NULL != ovenControl)
    {
        return ovenControl->getWorkingInRoastProcedureError();
    }
    return default_string;
}

// 211-5 命令执行的返回： （0：曲线正确，1：曲线错误）
string  XlfDeviceWrapper::getOven211_5CommandExecutedResult(string deviceId)
{
    OvenControl *ovenControl = (OvenControl *)getDeviceControl(deviceId);
    if(NULL != ovenControl)
    {
        return ovenControl->get211_5CommandExecutedResult();
    }
    return default_string;
}

// 211-7 命令执行结果（当此项为 1 时，检查下面2 项的错误置位）
string  XlfDeviceWrapper::getOven211_7CommandExecutedResult(string deviceId)
{
    OvenControl *ovenControl = (OvenControl *)getDeviceControl(deviceId);
    if(NULL != ovenControl)
    {
        return ovenControl->get211_7CommandExecutedResult();
    }
    return default_string;
}

// 该曲线不存在
string  XlfDeviceWrapper::getOvenCurveNotExistError7(string deviceId)
{
    OvenControl *ovenControl = (OvenControl *)getDeviceControl(deviceId);
    if(NULL != ovenControl)
    {
        return ovenControl->getCurveNotExistError7();
    }
    return default_string;
}

// 曲线子节点不存在
string  XlfDeviceWrapper::getOvenCurveSubnodeNotExistError(string deviceId)
{
    OvenControl *ovenControl = (OvenControl *)getDeviceControl(deviceId);
    if(NULL != ovenControl)
    {
        return ovenControl->getCurveSubnodeNotExistError();
    }
    return default_string;
}

// 211-8 命令执行结果（曲线是否存在）
string  XlfDeviceWrapper::getOven211_8CommandExecutedResult(string deviceId)
{
    OvenControl *ovenControl = (OvenControl *)getDeviceControl(deviceId);
    if(NULL != ovenControl)
    {
        return ovenControl->get211_8CommandExecutedResult();
    }
    return default_string;
}

// 211-9 命令执行结果（烤箱是否工作在烘焙曲线模式）
string  XlfDeviceWrapper::getOven211_9CommandExecutedResult(string deviceId)
{
    OvenControl *ovenControl = (OvenControl *)getDeviceControl(deviceId);
    if(NULL != ovenControl)
    {
        return ovenControl->get211_9CommandExecutedResult();
    }
    return default_string;
}

// //已完成的烘焙时间
int XlfDeviceWrapper::getOvenStatuRunTime(string deviceId)
{
    OvenControl *ovenControl = (OvenControl *)getDeviceControl(deviceId);
    if(NULL != ovenControl)
    {
        return ovenControl->getStatuRunTime();
    }
    return default_int;
}

// //当前实际上管温度
int XlfDeviceWrapper::getOvenStatuNowTemperature(string deviceId)
{
    OvenControl *ovenControl = (OvenControl *)getDeviceControl(deviceId);
    if(NULL != ovenControl)
    {
        return ovenControl->getStatuNowTemperature();
    }
    return default_int;
}

/****************** getFN ******************/
int XlfDeviceWrapper::getOvenHeatTubeNum(string deviceId)
{
    OvenControl *ovenControl = (OvenControl *)getDeviceControl(deviceId);
    if(NULL != ovenControl)
    {
        return ovenControl->getHeatTubeNum();
    }
    return default_int;
}


int XlfDeviceWrapper::getOvenOvenLampExitOrNot(string deviceId)
{
    OvenControl *ovenControl = (OvenControl *)getDeviceControl(deviceId);
    if(NULL != ovenControl)
    {
        return ovenControl->getOvenLampExitOrNot();
    }
    return default_int;
}


int XlfDeviceWrapper::getOvenRotaryForkExitOrNot(string deviceId)
{
    OvenControl *ovenControl = (OvenControl *)getDeviceControl(deviceId);
    if(NULL != ovenControl)
    {
        return ovenControl->getRotaryForkExitOrNot();
    }
    return default_int;
}


int XlfDeviceWrapper::getOvenHeatAirCirculationOrNot(string deviceId)
{
    OvenControl *ovenControl = (OvenControl *)getDeviceControl(deviceId);
    if(NULL != ovenControl)
    {
        return ovenControl->getHeatAirCirculationOrNot();
    }
    return default_int;
}


int XlfDeviceWrapper::getOvenSupportThawingModeOrNot(string deviceId)
{
    OvenControl *ovenControl = (OvenControl *)getDeviceControl(deviceId);
    if(NULL != ovenControl)
    {
        return ovenControl->getSupportThawingModeOrNot();
    }
    return default_int;
}


int XlfDeviceWrapper::getOvenSupportLowTemperatureFermentationOrNot(string deviceId)
{
    OvenControl *ovenControl = (OvenControl *)getDeviceControl(deviceId);
    if(NULL != ovenControl)
    {
        return ovenControl->getSupportLowTemperatureFermentationOrNot();
    }
    return default_int;
}


int XlfDeviceWrapper::getOvenSupportAlarmOrNot(string deviceId)
{
    OvenControl *ovenControl = (OvenControl *)getDeviceControl(deviceId);
    if(NULL != ovenControl)
    {
        return ovenControl->getSupportAlarmOrNot();
    }
    return default_int;
}
