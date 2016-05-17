//
//  DeviceControl.cpp
//  Devices
//
//  Created by 肖芳亮 on 16/2/24.
//  Copyright © 2016年 XLF. All rights reserved.
//

#include "DeviceControl.h"

DeviceControl::DeviceControl()
{
    
}

DeviceControl::~DeviceControl()
{
    
}

// 通用开、关机
string DeviceControl::setPowerCommon(int power, int soundSet)
{
    if(devicesLogic!= NULL)
    {
        return devicesLogic->setPowerCommon(power, soundSet);
    }
    return NULL;
}

// 查询设备所有状态
string DeviceControl::setQueryDeviceAllStatus(int soundSet)
{
    if(devicesLogic!= NULL)
    {
        return devicesLogic->setQueryDeviceAllStatus(soundSet);
    }
    return "";
}

// 查询设备功能列表
string DeviceControl::setQueryDeviceAllFunctions(int soundSet)
{
    if(devicesLogic!= NULL)
    {
        return devicesLogic->setQueryDeviceAllFunctions(soundSet);
    }
    return "";
}

//查询设备型号信息
string DeviceControl::setQueryDeviceModle(int soundSet)
{
    if(devicesLogic!= NULL)
    {
        return devicesLogic->setQueryDeviceModle(soundSet);
    }
    return "";
}

//查询设备类型
string DeviceControl::setQueryDeviceAddress(int soundSet)
{
    if(devicesLogic!= NULL)
    {
        return devicesLogic->setQueryDeviceAddress(soundSet);
    }
    return "";
}

// 查询固件版本
string DeviceControl::sendQueryVersion()
{
    if(devicesLogic!= NULL)
    {
        return devicesLogic->sendQueryVersion();
    }
    return "";
}

// 获取固件版本
string DeviceControl::getSoftVersion()
{
    if(devicesLogic!= NULL)
    {
        return devicesLogic->getSoftVersion();
    }
    return "";
}

// 解析设备标识
bool DeviceControl::saveDeviceImformationCode(string resultText)
{
    if(devicesLogic!= NULL)
    {
        return devicesLogic->saveDeviceImformationCode(resultText);
    }
    return false;
}

// 更新设备所有状态
bool DeviceControl::setDeviceAllStatus(string allStauts)
{
    if(devicesLogic!= NULL)
    {
        return devicesLogic->setDeviceAllStatus(allStauts);
    }
    return false;
}

// 设置设备功能列表
bool DeviceControl::setDeviceFunction(string function)
{
    if(devicesLogic!= NULL)
    {
        return devicesLogic->setDeviceFunction(function);
    }
    return false;
}

// 获取设备型号信息
string DeviceControl::getDeviceModle()
{
    if(devicesLogic!= NULL)
    {
        return devicesLogic->getDeviceModle();
    }
    return errorString;
}

// 获取设备类型
string DeviceControl::getDeviceAddress()
{
    if(devicesLogic!= NULL)
    {
        return devicesLogic->getDeviceAddress();
    }
    return errorString;
}

// 控制类版本号
string DeviceControl::getVersionNumberOfDevicesControl()
{
    if(devicesLogic!= NULL)
    {
        return devicesLogic->getVersionNumberOfDevicesControl();
    }
    return errorString;
}

// so库版本号
string DeviceControl::getVersionNumberOfProtocolLibrary()
{
    if(devicesLogic!= NULL)
    {
        return devicesLogic->getVersionNumberOfProtocolLibrary();
    }
    return errorString;
}

// 获取4004版本号
string DeviceControl::getVersionNumberOfWifiModule()
{
    if(devicesLogic!= NULL)
    {
        return devicesLogic->getVersionNumberOfWifiModule();
    }
    return errorString;
}

// 设置在线状态
void DeviceControl::setOnlineStatus(bool status)
{
    if(devicesLogic!= NULL)
    {
        devicesLogic->setOnlineStatus(status);
    }
}

// 获取在线状态
bool DeviceControl::getOnlineStatus()
{
    if(devicesLogic!= NULL)
    {
        return devicesLogic->getOnlineStatus();
    }
    return false;
}

// 解析
string DeviceControl::parseResult(string recv)
{
    if(devicesLogic!= NULL)
    {
        return devicesLogic->parseResult(recv);
    }
    return errorString;
}

