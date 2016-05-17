//
//  WifiControl.h
//  devices
//
//  Created by 肖芳亮 on 16/1/7.
//  Copyright © 2016年 xiaofangliang. All rights reserved.
//

#ifndef WifiControl_h
#define WifiControl_h

#include <stdio.h>
#include "DeviceControl.h"
#include "Qca4004Cmd.h"

class WifiControl :public DeviceControl
{
    
private:
    
    Qca4004Cmd *wifiControlLogic;//逻辑类
    
public:
    
    
    WifiControl();
    
    WifiControl(string deviceId);
    
    ~WifiControl();
    
};

#endif /* WifiControl_h */
