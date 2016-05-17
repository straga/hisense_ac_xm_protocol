//
//  VoltameterLogic.h
//  devices
//
//  Created by administratiors on 15/12/15.
//  Copyright © 2015年 xiaofangliang. All rights reserved.
//

#ifndef VoltameterLogic_h
#define VoltameterLogic_h

#include "DeviceLogic.h"

class VoltameterLogic : public DeviceLogic
{
public:
    
    VoltameterLogic();
    
    ~VoltameterLogic();
    
    /******************************** 功能设置 ********************************************/
    /** 总的电源开关 */
   string  setPower(int power);
    
    /** 电量统计清0 1清零，0不清零 */
   string  setResetCount(int isResetCount);

    /******************************** 状态查询 ********************************************/
    /** 总电源开关状态 */
    string  getPower();
    
    /** 电流值uA */
    string  getCurrentValue();
    
    /** 电压值mV */
    string  getVoltageValue();
    
    /** 电量值的统计 */
    string getVoltameterValue();
    
    /** 当前电量累计的高32bit值焦尔 */
    string  getCountHValue();
    
    /** 当前电量累计的低32bit值焦尔 */
    string  getCountLValue();
    
    /** 转换板通信错误 */
    string  getIsPeripheralsCommunicationError();
};


#endif /* VoltameterLogic_h */
