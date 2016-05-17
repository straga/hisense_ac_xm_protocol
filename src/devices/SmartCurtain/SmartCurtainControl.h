//
//  SmartCurtainControl.h
//  devices
//
//  Created by administratiors on 15/12/15.
//  Copyright © 2015年 xiaofangliang. All rights reserved.
//

#ifndef SmartCurtainControl_h
#define SmartCurtainControl_h

#include "DeviceControl.h"
#include "SmartCurtainLogic.h"

class SmartCurtainControl : public DeviceControl
{
    
private:
    
    /** 逻辑类 */
    SmartCurtainLogic *smartCurtainLogic;
    
public:
    
    SmartCurtainControl(string deviceId);
    
    ~SmartCurtainControl();
    
    /*********************************** 功能设置 *******************************************/
    /** 模式：Mode : 设置功能:0打开、1 关闭、2停止、3 重启 */
    string setMode(int mode);
    
    /** 定点控制：Pos : 设置功能:设置的定点位置(0~16)，全开位置是0，中间闭合位置是16，每次设置位置间隔距离应大于等于4个单位 */
    string setPosition(int position);
    
    /*********************************** 状态查询 *******************************************/
    /** Open or Close state 参数是否有效 */
    string getPowerStatusParameterIsValid();
    
    /** Open or Close state 开关状态 */
    string getPowerStatus();
    
    /** 点位置 参数是否有效 */
    string getPositionParameterIsValid();
    
    /** 当前的定点位置 */
    string getPositionStatus();
    
    /**
     * 转换板通信错误
     * @return 0为正常，1为通信错误
     */
    string getIsPeripheralsCommunicationError();
};

#endif /* SmartCurtainControl_h */
