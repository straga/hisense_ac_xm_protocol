//
//  DeviceLogic.cpp
//  Devices
//
//  Created by 肖芳亮 on 16/2/24.
//  Copyright © 2016年 XLF. All rights reserved.
//

#include "DeviceLogic.h"
#include "ProtocolNative.h"
#include "IOTConstants.h"
#include "IOTUtil.h"

#define TAG  "\n<DeviceLogic>: "

DeviceLogic::DeviceLogic()
{
    errorInt = -1;
    errorstring = "";
}

DeviceLogic::~DeviceLogic()
{
    
}

string DeviceLogic::createNetBytes(string atCmd)
{
    //cout<<"atcmd = "<<atCmd<<endl;
    return ProtocolNative::Hisense_build(atCmd, DEVICE_TYPE, 0x01, 0xfe, 0x01);
}

// 通用开、关机
string DeviceLogic::setPowerCommon(int power, int soundSet)
{
    string atcmd = IOTConstants::CMD_AT_MARK  + "KLKJ" + IOTConstants::CMD_AT_EQUALS_SINGNAL + deviceId + IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(power) + IOTConstants::CMD_AT_WRAP;
    return createNetBytes(atcmd);
}

// 查询设备所有状态
string DeviceLogic::setQueryDeviceAllStatus(int soundSet)
{
    string atcmd = IOTConstants::CMD_AT_MARK  + At_QureyStatus + IOTConstants::CMD_AT_EQUALS_SINGNAL + deviceId + IOTConstants::PARAM_VALUE_SPLIT +  IOTConstants::CMD_AT_GET_STATUS_MARK + IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(soundSet) + IOTConstants::CMD_AT_WRAP;
    return createNetBytes(atcmd);
}

// 查询设备功能列表
string DeviceLogic::setQueryDeviceAllFunctions(int soundSet)
{
    return "";
}

//查询设备型号信息
string DeviceLogic::setQueryDeviceModle(int soundSet)
{
    return "";
}

//查询设备类型
string DeviceLogic::setQueryDeviceAddress(int soundSet)
{
    return "";
}

// 查询固件版本
string DeviceLogic::sendQueryVersion()
{
    string atcmd = IOTConstants::CMD_AT_MARK + "KLCXB" +
        IOTConstants::CMD_AT_EQUALS_SINGNAL + deviceId +
        IOTConstants::PARAM_VALUE_SPLIT +
        "0" + IOTConstants::CMD_AT_WRAP;
    return createNetBytes(atcmd);
}

// 获取固件版本
string DeviceLogic::getSoftVersion()
{
    return softVersion;
}

// 解析设备标识
bool DeviceLogic::saveDeviceImformationCode(string resultText)
{
    vector<string> tempstring;
    char* value_temp;
    
    if(resultText.length() != 0)
    {
        return false;
    }
    
    tempstring = IOTUtil::split(resultText,",");
    int temp = IOTUtil::stringToInt(tempstring[1]);
    int length = (temp & 0x1f);
    
    if(length != At_Modle_Num)
    {
        return false;
    }
 // 这里原来是关着的,为了编译通过让其初始化打开了   
    value_temp = IOTUtil::hexStringToBytes(tempstring[2]);
    
    for(int j = 0; j < At_Modle_Num; j++)
    {
        devicecode += value_temp[j];
    }
    
    return true;
}

// 更新设备所有状态
bool DeviceLogic::setDeviceAllStatus(string allStauts)
{
    if(allStauts.length() == 0 || At_Status_Num == 0 || ZD.empty())
    {
        return false;
    }
    
    int i,len,j=0;
    vector<string> temp;
    temp = IOTUtil::split(allStauts,",");
    
    if(!temp.empty())
    {
        len = (int)temp.size();
        
        if(len != At_Status_Num)
        {
            return false;
        }
        for(i = 0; i <At_Status_Num; i++)
        {
            ZD[j++] = temp[i];
        }
        
        return true;
    }
    
    return false;
}

// 更新设备功能列表
bool DeviceLogic::setDeviceFunction(string function)
{
    if(function.length() == 0|| At_Funtion_Num == 0 || GN.empty())
    {
        return false;
    }
    
    int i,len,j = 0;
    vector<string> tmp;
    
    tmp = IOTUtil::split(function,",");
    len = (int)tmp.size();
    
    if(len == At_Funtion_Num)
    {
        for(i = 0; i < len; i++, j++)
        {
            GN[j] = IOTUtil::stringToInt(tmp[i]);
            if(0 < GN[j])
            {
                GN_EN[j] = 1;
            }
            else
            {
                GN_EN[j] = 0;
            }
        }
        
        return true;
    }
    
    if((len - 1) == At_Funtion_Num)
    {
        for(i = 1; i < len; i++, j++)
        {
            GN[j]=IOTUtil::stringToInt(tmp[i]);
            if(0 < GN[j])
            {
                GN_EN[j]=1;
            }
            else
            {
                GN_EN[j]=0;
            }
        }
        return true;
    }
    
    return false;
}

// 获取设备型号信息
string DeviceLogic::getDeviceModle()
{
    return errorstring;
}

// 获取设备类型
string DeviceLogic::getDeviceAddress()
{
    return errorstring;
}

// 控制类版本号
string DeviceLogic::getVersionNumberOfDevicesControl()
{
    return errorstring;
}

// so库版本号
string DeviceLogic::getVersionNumberOfProtocolLibrary()
{
    return errorstring;
}

// 获取4004版本号
string DeviceLogic::getVersionNumberOfWifiModule()
{
    return errorstring;
}

// 设置在线状态
void DeviceLogic::setOnlineStatus(bool status)
{
    isOnline = status;
}

// 获取在线状态
bool DeviceLogic::getOnlineStatus()
{
    return isOnline;
}

// 解析 F4F5指令
string DeviceLogic::parseResult(string result)
{
    if(result.find("F4F5") == string::npos)
    {
        return "";
    }
    
    string tmp =  ProtocolNative::Hisense_Parse(result, DEVICE_TYPE);
    
    vector<string> temp;
    
    temp = IOTUtil::split(tmp,",");
    cout<<TAG<<"deviceId = "<<deviceId<<", deviceType = "<<deviceType<<"\nresult = "<<tmp<<endl;
    
    // 更新设备所有状态
    size_t pos = tmp.find(At_QureyStatus);
    if(pos != string::npos)
    {
        vector<string> retStatus = IOTUtil::split(temp.at(0),":");
        
        setDeviceAllStatus( IOTUtil::subString(tmp,2 + (int)At_QureyStatus.length(),(int)tmp.length()));
        
        string ret = retStatus.at(0);
        ret = IOTUtil::subString(ret,1,(int)ret.length());
        
        return ret + ":SUCCEED";
    }
    
    // 更新设备功能列表
    pos = tmp.find(At_QueryFuntion);
    if(pos != string::npos)
    {
        setDeviceFunction(result);
        return "";
    }
    
    pos = tmp.find("KLCXB");
    if(pos != string::npos)
    {
        vector<string> retVersion = IOTUtil::split(temp.at(0),":");

        softVersion = retVersion.at(1) + temp.at(1);
        return "";
    }
    
    // 控制状态返回
    tmp = IOTUtil::replace_all(tmp, "\r\n", "");
    return IOTUtil::subString(tmp,1,(int)tmp.length() - 2);
}

/**
 * 解析At 返回
 */
bool DeviceLogic::parseAtResult(string result)
{
    return false;
}

