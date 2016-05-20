//
//  XlfDeviceManager.h
//  Devices
//
//  Created by 肖芳亮 on 16/2/24.
//  Copyright ? 2016年 XLF. All rights reserved.
//

#ifndef XlfDeviceManager_h
#define XlfDeviceManager_h

#include <stdio.h>
#include <map>
#include <vector>
#include "XlfDeviceInfo.h"
#include "DevicesControl.h"

class XlfDeviceManager
{
    
private:
    map<string,XlfDeviceInfo*> *deviceMap;
    vector<string> keys;
    
private:
    /** 单例 */
    XlfDeviceManager();
    
public:
    
    /**
     * 获取单例对象
     */
    static XlfDeviceManager &getInstance();
    
    /**
     * 创建设备控制信息类
     */
    bool initDeviceControl(const string &deviceId, int deviceType);
    
    /**
     *  删除单个设备控制信息类
     */
    bool deleteDeviceControl(const string &deviceId);
    
    /**
     *  获取单个设备控制信息类
     */
    XlfDeviceInfo* getDeviceInfo(const string &deviceId);
    
};

#endif /* XlfDeviceManager_h */
