//
//  VoltameterControl.h
//  devices
//
//  Created by administratiors on 15/12/15.
//  Copyright © 2015年 xiaofangliang. All rights reserved.
//

#ifndef VoltameterControl_h
#define VoltameterControl_h

#include "DeviceControl.h"
#include "VoltameterLogic.h"

class VoltameterControl : public DeviceControl
{
    
private:
    
    VoltameterLogic *voltameterLogic;
    
public:
    
    VoltameterControl(string deviceId);
    
    ~VoltameterControl();
    
    /** 总的电源开关 */
    string setPower(int power);
    
    /** 电量统计清0 1清零，0不清零 */
    string setResetCount(int isResetCount);
    
    /** 总电源开关状态 */
    string getPower();
    
    /** 电流值uA */
    string getCurrentValue();
    
    /** 电压值mV */
    string getVoltageValue();
    
    /** 电量值的统计 */
    string getVoltameterValue();
    
    /** 转换板通信错误 */
    string getIsPeripheralsCommunicationError();
    
};

#endif /* VoltameterControl_h */
