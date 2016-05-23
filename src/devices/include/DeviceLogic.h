//
//  DeviceLogic.h
//  Devices
//
//  Created by 肖芳亮 on 16/2/24.
//  Copyright © 2016年 XLF. All rights reserved.
//

#ifndef DeviceLogic_h
#define DeviceLogic_h

#include <stdio.h>
#include <iostream>
#include <vector>
#include "CByte.h"

using namespace::std;

class DeviceLogic
{
    
protected:
    
    string createNetBytes(string atCmd);
    
public:
    
    // 子设备id  由子类填写
    string deviceId;
    
    // 子设备类型(string)  aircon -> 空调
    string deviceType;
    
    // 子设备类型(int)  0x01 -> 空调
    int DEVICE_TYPE;
    
    // 保存状态的数组
    vector<string>ZD;
    
    // 保存状态的数组的长度
    int At_Status_Num;
    
    // 保存功能的数组
    vector<int> GN;
    
    //保存功能的数组的长度
    int At_Funtion_Num;
    
    // 保存使能的数组
    vector<int>GN_EN;
    
    int At_Modle_Num;
    
    // "KTZD" 表示是空调的状态
    string At_QureyStatus;
    
    // "KTGN" 表示是空调的功能列表
    string At_QueryFuntion;
    
    // "CSSET" 表示是除湿机的控制指令
    string At_Setting;
    
    string devicecode;
    
    // 固件版本
    string softVersion;
    
    // 错误情况返回
    int errorInt;
    string errorstring;
    
    bool isOnline;
    
public:
    
    DeviceLogic();
    
    ~DeviceLogic();
    
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
    
    // 解析 F4F5指令  错误情况下返回""  状态解析返回 "KTZD:SUCCEED"  功能解析返回 "KTGN:SUCCEED"  控制解析返回 "KTSET:SUCCEED" 或者 "KTSET:ERROR"
    string parseResult(string result);
    
    virtual bool parseAtResult(string result);
    
};

#endif /* DeviceLogic_h */
