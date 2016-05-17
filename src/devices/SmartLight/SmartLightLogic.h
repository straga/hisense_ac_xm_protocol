//
//  SmartLightLogic.h
//  devices
//
//  Created by administratiors on 15/12/15.
//  Copyright © 2015年 xiaofangliang. All rights reserved.
//

#ifndef SmartLightLogic_h
#define SmartLightLogic_h

#include "DeviceLogic.h"

class SmartLightLogic : public DeviceLogic
{
    
public:
    
    SmartLightLogic();
    
    ~SmartLightLogic();
    
    /******************************** 功能设置 ********************************************/
    /** 电源设置 此方法未实现 */
    string setPower(int power);
    
    /** 亮度设置：0~100 */
    string setBrightness(int brightnessValue);
    
    /** R G B 三元色设置 取值范围均为[0-255] */
    string setRGB(int redValue, int greenValue, int blueValue);
    
    /** 空气状况 3 优、2 良、1 一般 */
    string setAirQualityLevel(int airQualityLevel);
    
    /** 色温设置(0~65535) 此方法未实现 */
    string setColorTemperature(int colorTemperatureValue);
    
    // 新增 2015.11.12
    /**
     * 设备状态 0 为正常，1 为掉线
     * @param deviceStatus  0 为正常，1 为掉线
     * @return byte[]
     */
    string setDeviceStatus(int deviceStatus);
    
    /******************************** 状态查询 ********************************************/
    /** 开关状态 此方法未实现 */
    string getPower();
    
    /** RGB 值是否有效 */
    string getRGBSetValid();
    /** 红色值 */
    
    string getRedValue();
    
    /** 绿色值 */
    string getGreenValue();
    
    /** 蓝色值 */
    string getBlueValue();
    
    /** 色温值是否有效 此方法未实现 */
    string getColorTemperatureValid();
    
    /** 色温值(0~65535) 此方法未实现 */
    string getColorTemperatureValue();
    
    /** 亮度值是否有效 */
    string getBrightnessValid();
    
    /** 亮度 */
    string getBrightnessValue();
    
    // 新增状态查询 2015.11.12
    /**
     * 设备状态 0 为有效，1 为无效
     * @return 0 为有效，1 为无效
     */
    string getDeviceStatusValid();
    
    /**
     * 设备状态 0 为正常，1 为掉线
     * @return  0 为正常，1 为掉线
     */
    string getDeviceStatus();
    
    /**
     * 空气状况是否有效 0 为有效，1 为无效
     * @return  0 为有效，1 为无效
     */
    string getAirStatusValid();
    
    /**
     * 空气状况 3 优、2 良、1 一般
     * @return 3 优、2 良、1 一般
     */
    string getAirStatus();
    
    /**
     * 转换板通信错误
     * @return 0为正常，1为通信错误
     */
    string getIsPeripheralsCommunicationError();
};



#endif /* SmartLightLogic_h */
