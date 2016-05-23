//
//  SeedMachineControlLogic.h
//  LiveHome
//
//  Created by administratiors on 15/12/15.
//  Copyright © 2015年 zou weilong. All rights reserved.
//

#ifndef SeedMachineControlLogic_h
#define SeedMachineControlLogic_h

#include <stdio.h>
#include "DeviceLogic.h"

class SeedMachineControlLogic :public DeviceLogic
{
    
public:
    
    bool isNeedUpdate;
    
    bool mark ;
    
private:
    static const string TAG;
    static const string CMD_AT_POWER;
    static const string CMD_AT_MUSIC;
    static const string CMD_AT_LIGHT;
    static const string CMD_AT_ANION;
    static const string CMD_AT_LIGHTTIMER;
    static const string CMD_AT_CURTIME;
    static const string CMD_AT_WARN_DISMISS;
    static const string CMD_AT_PM25;
    
public:
    
    //构造函数
    SeedMachineControlLogic();
    
    //析构函数
    ~SeedMachineControlLogic();
    
    bool GetNeedUpdateStatus();
    
    /*************************** 设备控制接口 *************************/
    /**
     * 电源开关
     */
    string setPower(int set,int flag);
    
    /**
     * 灯开关
     */
    string setLight(int set,int flag);
    
    /**
     * 音乐切换
     */
    string setMusic(int set,int flag);
    
    /**
     * 音量控制
     */
    string setVolume(int volume,int flag);
    
    /**
     * 负离子开关
     */
    string setAnion(int set,int flag);
    
    /**
     * 定时
     */
    string setLightTimer(int curhour,int curmin,int set,int onOroff,int hour,int min,int lights,int flag);
    
    /**
     * 关闭报警
     */
    string dismissWarning(int level, int pump,int nutrition,int flag);
    
    /**
     * 设置PM2.5开关：如果有外接传感器的情况下才有此功能hasExtralSensor()方法可获得
     * 1 开，0 关
     */
    string setPm25(int set,int flag);
    
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
    string getLightTimerStat();
    
    /**
     * 当前温度
     */
    string getLightStat();
    
    /**
     * 当前湿度
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
    string getExtralHumi();
    
    /**
     * 获得外接湿度值，只在外接传感器存在时有效
     */
    string getExtralTemp();
    
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
    
    /*************************** 解析接口 *************************/
    bool parseAtCommand(string result);
};

#endif /* SeedMachineControlLogic_h */
