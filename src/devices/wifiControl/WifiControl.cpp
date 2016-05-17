//
//  WifiControl.cpp
//  devices
//
//  Created by 肖芳亮 on 16/1/7.
//  Copyright © 2016年 xiaofangliang. All rights reserved.
//

#include "WifiControl.h"

WifiControl::WifiControl()
{
    wifiControlLogic = new Qca4004Cmd();
    devicesLogic = wifiControlLogic;
}

WifiControl::WifiControl(string deviceId)
{
    wifiControlLogic = new Qca4004Cmd();
    wifiControlLogic->deviceId = deviceId;
    devicesLogic = wifiControlLogic;
}

WifiControl::~WifiControl()
{
    if(wifiControlLogic)
    {
        delete wifiControlLogic;
    }
}