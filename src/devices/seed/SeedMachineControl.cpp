//
//  SeedMachineControl.cpp
//  LiveHome
//
//  Created by administratiors on 15/12/15.
//  Copyright © 2015年 zou weilong. All rights reserved.
//

#include "SeedMachineControl.h"

SeedMachineControl::SeedMachineControl(string deviceId, string deviceType)
{
    seedControlLogic = new SeedMachineControlLogic();
    seedControlLogic->deviceId = deviceId;
    seedControlLogic->deviceType = deviceType;
    devicesLogic = seedControlLogic;
}

SeedMachineControl::~SeedMachineControl()
{
    
}

/**
 * 开关机
 */
string SeedMachineControl::setPower(int set)
{
    return seedControlLogic->setPower(set);
}

/**
 * 定时
 */
string SeedMachineControl::setLightTimer(int curhour,int curmin,int set,int onOroff,int hour,int min,int lights)
{
    return seedControlLogic->setLightTimer(curhour,curmin,set,onOroff,hour,min,lights);
}

/**
 * 关闭报警
 */
string SeedMachineControl::dismissWarning(int level, int pump,int nutrition)
{
    return seedControlLogic->dismissWarning(nutrition,pump,level);
}

/**
 * 设置灯开关
 */
string SeedMachineControl::setLight(int set)
{
    return seedControlLogic->setLight(set);
}

/**
 * 设置负离子开关
 */
string SeedMachineControl::setAnion(int set)
{
    return seedControlLogic->setAnion(set);
}

/*
 * 设置音乐开关
 */
string SeedMachineControl::setMusic(int set)
{
    return seedControlLogic->setMusic(set);
}

/**
 * 音量控制
 */
string SeedMachineControl::setVolume(int volume)
{
    return seedControlLogic->setVolume(volume);
}

/**
 * 设置PM2.5开关
 */
string SeedMachineControl::setPm25(int set)
{
    return seedControlLogic->setPm25(set);
}

/********************************* 状态获取 *********************************/
/**
 * 当前开关机状态
 */
string SeedMachineControl::getPowerStat()
{
    return seedControlLogic->getPowerStat();
}

/**
 * 当前音乐状态
 */
string SeedMachineControl::getMusicStat()
{
    return seedControlLogic->getMusicStat();
}

/**
 * 当前负离子状态
 */
string SeedMachineControl::getAnionStat()
{
    return seedControlLogic->getAnionStat() ;
}

/**
 * 当前灯状态
 */
string SeedMachineControl::getLightStat()
{
    return seedControlLogic->getLightStat();
}

/**
 * 当前温度
 */
string SeedMachineControl::getCurTemp()
{
    return seedControlLogic->getCurTemp();
}

/**
 * 当前湿度
 */
string SeedMachineControl::getCurHumi()
{
    return seedControlLogic->getCurHumi();
}

/**
 * 是否有外接传感器
 */
string SeedMachineControl::hasExtralSensor()
{
    return seedControlLogic->hasExtralSensor();
}

/**
 * 获得外接温度值，只在外接传感器存在时有效
 */
string SeedMachineControl::getExtralTemp()
{
    return seedControlLogic->getExtralTemp();
}

/**
 * 获得外接湿度值，只在外接传感器存在时有效
 */
string SeedMachineControl::getExtralHumi()
{
    return seedControlLogic->getExtralHumi();
}

/**
 * 获得外接Pm2.5值，只在外接传感器存在时有效，单位ug/m3
 */
string SeedMachineControl::getExtralPm2_5()
{
    return seedControlLogic->getExtralPm2_5();
}

/**
 * 是否有灯报警
 */
string SeedMachineControl::lightWarn()
{
    return seedControlLogic->lightWarn();
}

/**
 * 当前是第几层灯报警
 */
string SeedMachineControl::lightWarnInfo()
{
    return seedControlLogic->lightWarnInfo();
}

/**
 * 是否有水位报警
 */
string SeedMachineControl::waterLevelWarn()
{
    return seedControlLogic->waterLevelWarn();
}

/**
 * 是否有水泵报警
 */
string SeedMachineControl::pumpWarn()
{
    return seedControlLogic->pumpWarn();
}

/**
 * 营养液报警
 */
string SeedMachineControl::nutritionWarn()
{
    return seedControlLogic->nutritionWarn();
}
