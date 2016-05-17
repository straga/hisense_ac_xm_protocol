//
//  SeedMachineControl.h
//  LiveHome
//
//  Created by administratiors on 15/12/15.
//  Copyright © 2015年 zou weilong. All rights reserved.
//

#ifndef SeedMachineControl_h
#define SeedMachineControl_h

#include <stdio.h>
#include "DeviceControl.h"
#include "SeedMachineControlLogic.h"

class SeedMachineControl : public DeviceControl
{
    
private:
    
    SeedMachineControlLogic *seedControlLogic;
    
public:
    
    SeedMachineControl(string deviceId, string deviceType);
    
    ~SeedMachineControl();
    
    /********************************* 设备控制 *********************************/
    /**
     * 开关机
     * @param set
     */
    string setPower(int set);
    
    /**
     *
     * @param curhour 当前时间小时（0~23）
     * @param curmin  当前时间分钟 （0~59）
     * @param set	  1 设置定时功能，0，取消设置定时功能
     * @param onOroff 哪种定时，1 为开灯定时，0这关灯定时
     * @param hour	  定时小时（0~23）
     * @param min	 定时分钟（0~59）
     * @param lights  which layer lights to be set. Just like set parameter in function setLight()
     */
    string setLightTimer(int curhour,int curmin,int set,int onOroff,int hour,int min,int lights);
    
    /**
     * 关闭报警
     * @param level 水位报警,pump 水泵报警，nutrition 营养液报警
     */
    string dismissWarning(int level, int pump,int nutrition);
    
    /**
     * 设置灯开关：
     * 1 开灯，0 关灯
     */
    string setLight(int set);
    
    
    /**
     * 设置负离子开关：
     * 1 开，0 关
     */
    string setAnion(int set);
    
    /**
     * 设置音乐开关：
     * 1 开，0 关
     */
    string setMusic(int set);
    
    /**
     * 音量控制
     * @param volume 1：音量+; 0：音量减
     */
    string setVolume(int volume);
    
    /**
     * 设置PM2.5开关：如果有外接传感器的情况下才有此功能hasExtralSensor()方法可获得
     * 1 开，0 关
     */
    string setPm25(int set);
    
    /*************************** 获取设备状态接口 *************************/
    /**
     * 当前开关机状态
     */
    string getPowerStat();
    
    /**
     * 当前音乐状态
     */
    string getMusicStat();
    
    /**
     * 当前负离子状态
     */
    string getAnionStat();
    
    /**
     * 当前灯状态
     */
    string getLightStat();
    
    /**
     * 当前温度
     */
    string getCurTemp();
    
    /**
     * 当前湿度
     */
    string getCurHumi();
    
    /**
     * 是否有外接传感器
     */
    string hasExtralSensor();
    
    /**
     * 获得外接温度值，只在外接传感器存在时有效
     */
    string getExtralTemp();
    
    /**
     * 获得外接湿度值，只在外接传感器存在时有效
     */
    string getExtralHumi();
    
    /**
     * 获得外接Pm2.5值，只在外接传感器存在时有效，单位ug/m3
     */
    string getExtralPm2_5();
    
    /**
     * 是否有灯报警
     */
    string lightWarn();
    
    /**
     * 当前是第几层灯报警
     */
    string lightWarnInfo();
                             
    /**
     * 是否有水位报警
     */
    string waterLevelWarn();
    
    /**
     * 是否有水泵报警
     */
    string pumpWarn();
    
    /**
     * 营养液报警
     */
    string nutritionWarn();
};

#endif /* SeedMachineControl_h */
