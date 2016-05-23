//
//  DeviceControl.h
//  Devices
//
//  Created by 肖芳亮 on 16/2/24.
//  Copyright © 2016年 XLF. All rights reserved.
//

#ifndef DeviceControl_h
#define DeviceControl_h

#include <stdio.h>
#include <string>
#include <map>
#include "DeviceLogic.h"

class DeviceControl
{
    
protected:
    
    //逻辑类
    DeviceLogic *devicesLogic;
    
    // 错误情况返回
    int errorInt;
    string errorString;
    
public:
    
    DeviceControl();
    
    ~DeviceControl();
    
    // 通用开、关机
    string setPowerCommon(int power, int soundSet);
    
    // 查询设备所有状态
    string setQueryDeviceAllStatus(int soundSet);
    
    // 查询设备功能列表
    string setQueryDeviceAllFunctions(int soundSet);
    
    //查询设备型号信息
    string setQueryDeviceModle(int soundSet);
    
    //查询设备类型
    string setQueryDeviceAddress(int soundSet);
    
    // 查询固件版本
    string sendQueryVersion(int flag);
    
    // 获取固件版本
    string getSoftVersion();
    
    // 解析设备标识
    bool saveDeviceImformationCode(string resultText);
    
    // 更新设备所有状态
    bool setDeviceAllStatus(string allStauts);
    
    // 更新设备功能列表
    bool setDeviceFunction(string function);
    
    // 获取设备型号信息
    string getDeviceModle();
    
    // 获取设备类型
    string getDeviceAddress();
    
    // 获取控制类版本号
    string getVersionNumberOfDevicesControl();
    
    // 获取协议库版本号
    string getVersionNumberOfProtocolLibrary();
    
    // 获取获取wifi模块版本号
    string getVersionNumberOfWifiModule();
    
    // 设置在线状态
    void setOnlineStatus(bool status);
    
    // 获取在线状态
    bool getOnlineStatus();
    
    // 解析
    string parseResult(string recv);
};


#endif /* DeviceControl_h */
