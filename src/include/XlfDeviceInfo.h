//
//  XlfDeviceInfo.h
//  Devices
//
//  Created by 肖芳亮 on 16/2/24.
//  Copyright ? 2016年 XLF. All rights reserved.
//

#ifndef XlfDeviceInfo_h
#define XlfDeviceInfo_h

#include <stdio.h>
#include <string>
#include "../devices/wifiControl/WifiControl.h"

using namespace::std;

class XlfDeviceInfo
{
    
    const int deviceType;
public:
    XlfDeviceInfo(int deviceType = 0):deviceType(deviceType){}
    DeviceControl *deviceControl;
    WifiControl *wifiControl;
    string deviceId;
    int getDeviceType(){return deviceType;};
};

#endif /* XlfDeviceInfo_h */
