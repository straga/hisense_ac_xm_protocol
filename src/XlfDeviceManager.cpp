//
//  XlfDeviceManager.cpp
//  Devices
//
//  Created by 肖芳亮 on 16/2/24.
//  Copyright ? 2016年 XLF. All rights reserved.
//

#include "XlfDeviceManager.h"

#define TAG "<XLF_DEVICE> : "

XlfDeviceManager::XlfDeviceManager()
{
    if(NULL == deviceMap)
    {
        deviceMap = new map<string, XlfDeviceInfo*>();
    }
}

/**
 * 获取单例对象
 */
XlfDeviceManager &XlfDeviceManager::getInstance()
{
    static XlfDeviceManager instance;
    return instance;
}

/**
 * 创建设备控制信息类
 */
bool XlfDeviceManager::initDeviceControl(const string &deviceId, int deviceType)
{
    try
    {
        if(deviceId == "")
        {
            cout << TAG << "init deviceControl failed, deviceId or deviceType is nil!" <<endl;
            return false;
        }
        XlfDeviceInfo *deviceInfo = this->getDeviceInfo(deviceId);

        if(NULL == deviceInfo)
        {
            deviceInfo = new XlfDeviceInfo(deviceType);
            if(deviceType == 0x01)
            {
                deviceInfo->deviceControl = new AirconditionControl(deviceId);// 空调
                deviceInfo->deviceId = deviceId;
            }
            else if(deviceType == 0x15)
            {
                deviceInfo->deviceControl = new DehumidifierControl(deviceId);// 除湿机
                deviceInfo->deviceId = deviceId;
            }
            else if(deviceType == 0x18)
            {
                deviceInfo->deviceControl = new AirCleanerControl(deviceId);// 空气净化器
                deviceInfo->deviceId = deviceId;
            }
            else if(deviceType == 0x25)
            {
                deviceInfo->deviceControl = new AirFanControl(deviceId);// 新风机
                deviceInfo->deviceId = deviceId;
            }
            else if(deviceType == 0x28)
            {
                deviceInfo->deviceControl = new SeedMachineControl(deviceId, "seed");// 种植机
                deviceInfo->deviceId = deviceId;
            }
            else if(deviceType == 0x53)
            {
                deviceInfo->deviceControl = new SensorsFourInOneControl(deviceId);// 传感器
                deviceInfo->deviceId = deviceId;
            }
            else if(deviceType == 0x52)
            {
                deviceInfo->deviceControl = new SmartLightControl(deviceId);// 氛围灯
                deviceInfo->deviceId = deviceId;
            }
            else if(deviceType == 0x55)
            {
                deviceInfo->deviceControl = new SmartCurtainControl(deviceId);// 窗帘
                deviceInfo->deviceId = deviceId;
            }
            else if(deviceType == 0x11)
            {
                deviceInfo->deviceControl = new VoltameterControl(deviceId);// 电量计
                deviceInfo->deviceId = deviceId;
            }
            else if(deviceType == 0x27)
            {
                deviceInfo->deviceControl = new OvenControl(deviceId);// 电量计
                deviceInfo->deviceId = deviceId;
            }
            else
            {
            	delete deviceInfo;
                cout<< TAG << "init deviceControl failed,no device with type " <<deviceType  <<endl;
                return false;
            }
            
            deviceInfo->wifiControl = new WifiControl(deviceId);
            keys.push_back(deviceId);
            deviceMap->insert(pair<string, XlfDeviceInfo*>(deviceId, deviceInfo));
            
            cout<< TAG <<"init deviceControl succeed,deviceId =  "<< deviceId <<endl;
            return true;
        }
        else
        {
            cout<< TAG << "init deviceControl failed,Id for " << deviceId <<"device is exist!" <<endl;
            return false;
        }
    }
    catch (exception &ex)
    {
        cout<< TAG << ex.what() <<endl;
        return false;
    }
}

/**
 *  删除设备控制信息类
 */
bool XlfDeviceManager::deleteDeviceControl(const string &deviceId)
{
    try
    {
        XlfDeviceInfo *deviceInfo = this->getDeviceInfo(deviceId);
        if(deviceInfo != NULL)
        {
            delete deviceInfo->deviceControl;
            deviceInfo->deviceControl = NULL;
            
            delete deviceInfo->wifiControl;
            deviceInfo->wifiControl = NULL;
            
            deviceMap->erase(deviceId);
            
            cout << TAG << "delete deviceControl succeed,deviceId = " << deviceId <<endl;
            return false;
        }
        else
        {
            cout << TAG <<"delete deviceControl failed,Id for " << deviceId <<"device is not exist!" <<endl;
            return false;
        }
    }
    catch (exception &ex)
    {
        cout << ex.what() << endl;
        return false;
    }
}

/**
 *  获取单个设备控制信息类
 */
XlfDeviceInfo* XlfDeviceManager::getDeviceInfo(const string &deviceId)
{
    try
    {
        if(deviceMap->size() > 0 && deviceId != "")
        {
            map<string, XlfDeviceInfo *>::iterator it;
            it = deviceMap->find(deviceId);
            if(it != deviceMap->end())
            {
                return it->second;
            }
        }
    }
    catch (exception &ex)
    {
        cout<< ex.what() <<endl;
    }
    return NULL;
}


