//
//  SeedMachineControlLogic.cpp
//  LiveHome
//
//  Created by administratiors on 15/12/15.
//  Copyright © 2015年 zou weilong. All rights reserved.
//

#include "SeedMachineControlLogic.h"
#include "IOTConstants.h"
#include "IOTUtil.h"

const string SeedMachineControlLogic::TAG = "SeedMachine";
const string SeedMachineControlLogic::CMD_AT_POWER = "SEEDPSet";
const string SeedMachineControlLogic::CMD_AT_MUSIC="SEEDMSet";
const string SeedMachineControlLogic::CMD_AT_LIGHT = "SEEDLSet";
const string SeedMachineControlLogic::CMD_AT_ANION = "SEEDAnion";
const string SeedMachineControlLogic::CMD_AT_LIGHTTIMER="SEEDLTime";
const string SeedMachineControlLogic::CMD_AT_CURTIME="SEEDRTTime";
const string SeedMachineControlLogic::CMD_AT_WARN_DISMISS="SEEDCWarn";
const string SeedMachineControlLogic::CMD_AT_PM25="SEEDPm25";

//构造函数
SeedMachineControlLogic::SeedMachineControlLogic()
{
    At_QureyStatus = "SEEDStat";
    At_Status_Num = 23;
    At_QueryFuntion = "";
    isNeedUpdate = true;  
    mark = false;
    
    DEVICE_TYPE = 0x28;
    
    for(int i = 0; i < At_Status_Num; i++)
    {
        GN.push_back(0);
    }
    
    for(int i = 0; i < At_Status_Num; i++)
    {
        GN_EN.push_back(0);
    }
    
    for(int i = 0; i < At_Status_Num; i++)
    {
        ZD.push_back("0");
    }
}

//析构函数
SeedMachineControlLogic::~SeedMachineControlLogic()
{
    
}

bool SeedMachineControlLogic::GetNeedUpdateStatus()
{
    bool currentStatus = isNeedUpdate;
    isNeedUpdate = false;
    return currentStatus;
}

/**
 * 电源开关
 * @param set
 * @return
 */
string SeedMachineControlLogic::setPower(int set,int flag)
{
    ZD[0]=set >0 ?"1":"0";
    string atCmd = IOTConstants::CMD_AT_MARK + CMD_AT_POWER + IOTConstants::CMD_AT_EQUALS_SINGNAL + deviceId
				+ IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(set) + IOTConstants::CMD_AT_WRAP;
	if(2 == flag)
		return atCmd;
	return createNetBytes(atCmd);
}

/**
 * 灯开关
 * @param set
 * @return
 */
string SeedMachineControlLogic::setLight(int set,int flag)
{
     string atCmd = IOTConstants::CMD_AT_MARK + CMD_AT_LIGHT + IOTConstants::CMD_AT_EQUALS_SINGNAL + deviceId
				+ IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(set)+IOTConstants::CMD_AT_WRAP;
	 if(flag == 2)
	 	return atCmd;
	 return createNetBytes(atCmd);
}

/**
 * 音乐切换
 * @return
 */
string SeedMachineControlLogic::setMusic(int set,int flag)
{
    string atCmd = IOTConstants::CMD_AT_MARK + CMD_AT_MUSIC + IOTConstants::CMD_AT_EQUALS_SINGNAL + deviceId
				+ IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(set)
				+IOTConstants::CMD_AT_WRAP;
	 if(flag == 2)
	 	return atCmd;
	 return createNetBytes(atCmd);
}

/**
 * 音量控制
 * @param volume 1：音量+; 0：音量减
 * @return
 */
string SeedMachineControlLogic::setVolume(int volume,int flag)
{
    string atCmd = IOTConstants::CMD_AT_MARK + "SEEDVSet" + IOTConstants::CMD_AT_EQUALS_SINGNAL + deviceId
				+ IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(volume)
				+IOTConstants::CMD_AT_WRAP;
	 if(flag == 2)
	 	return atCmd;
	 return createNetBytes(atCmd);
}

/**
 * 负离子开关
 * @param set
 * @return
 */
string SeedMachineControlLogic::setAnion(int set,int flag)
{
    string atCmd = IOTConstants::CMD_AT_MARK + CMD_AT_ANION + IOTConstants::CMD_AT_EQUALS_SINGNAL + deviceId
				+ IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(set)+IOTConstants::CMD_AT_WRAP;
	if(flag == 2)
	 	return atCmd;
	return createNetBytes(atCmd);
}

/**
 *
 * @param curhour 当前时间小时（0~23）
 * @param curmin  当前时间分钟 （0~59）
 * @param set	  1 设置定时功能，0，取消设置定时功能
 * @param onOroff 哪种定时，1 为开灯定时，0这关灯定时
 * @param hour	  定时小时（0~23）
 * @param min	 定时分钟（0~59）
 * @param lights
 * @return
 */
string SeedMachineControlLogic::setLightTimer(int curhour,int curmin,int set,int onOroff,int hour,int min,int lights,int flag)
{
	
     string atCmd = IOTConstants::CMD_AT_MARK + CMD_AT_LIGHTTIMER + IOTConstants::CMD_AT_EQUALS_SINGNAL + deviceId
				+ IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(curhour)
				+ IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(curmin)
				+ IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(set)
				+ IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(onOroff)
				+ IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(hour)
				+ IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(min)
				+ IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(lights)
				+IOTConstants::CMD_AT_WRAP;
	 if(flag == 2)
		return atCmd;
	 return createNetBytes(atCmd);
}

//string SeedMachineControlLogic::cancelTimer()
//{
//    return IOTConstants::CMD_AT_MARK + CMD_AT_LIGHTTIMER + IOTConstants::CMD_AT_EQUALS_SINGNAL + deviceId
//            + IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(true)
//            +IOTConstants::CMD_AT_WRAP;
//}
// 
//string SeedMachineControlLogic::setCurTime(int hour,int min)
//{
//    return IOTConstants::CMD_AT_MARK + CMD_AT_CURTIME + IOTConstants::CMD_AT_EQUALS_SINGNAL + deviceId
//            + IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(hour)
//            + IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(min)
//            +IOTConstants::CMD_AT_WRAP;
//}

string SeedMachineControlLogic::dismissWarning(int level, int pump,int nutrition,int flag)
{
    if(nutrition !=0 ) nutrition =1;
    if(pump !=0 ) pump =1;
    if(level !=0 ) level =1;
    string atCmd = IOTConstants::CMD_AT_MARK + CMD_AT_WARN_DISMISS + IOTConstants::CMD_AT_EQUALS_SINGNAL + deviceId
				+ IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(level)
				+ IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(pump)
				+ IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(nutrition)
				+IOTConstants::CMD_AT_WRAP;
	 if(flag == 2)
		return atCmd;
	 return createNetBytes(atCmd);
}


string SeedMachineControlLogic::setPm25(int set,int flag)
{
    string atCmd = IOTConstants::CMD_AT_MARK + CMD_AT_PM25 + IOTConstants::CMD_AT_EQUALS_SINGNAL + deviceId
				+ IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(set)
				+IOTConstants::CMD_AT_WRAP;
	 if(flag == 2)
		return atCmd;
	 return createNetBytes(atCmd);
}

/*************************** 获取设备状态接口 *************************/
/**
 * 当前开关机状态
 */

string SeedMachineControlLogic::getPowerStat()
{
    return ZD[0];
}

/**
 * 当前音乐状态
 */

string SeedMachineControlLogic::getMusicStat()
{
    return ZD[1];
}

/**
 * 当前负离子状态
 */

string SeedMachineControlLogic::getAnionStat()
{
    return ZD[2];
}

/**
 * 当前灯状态
 */
string SeedMachineControlLogic::getLightTimerStat()
{
    return ZD[3];
}

/**
 * 当前温度
 */
string SeedMachineControlLogic::getLightStat()
{
    return ZD[4];
}

/**
 * 当前湿度
 */
string SeedMachineControlLogic::getCurTemp()
{
    int ret = IOTUtil::stringToInt(ZD[5]) +  (float)(IOTUtil::stringToInt(ZD[6]))/100.0;
    return IOTUtil::intToString(ret);
}

/**
 * 当前湿度
 */
string SeedMachineControlLogic::getCurHumi()
{
    int ret = IOTUtil::stringToInt(ZD[7]) +  (float)(IOTUtil::stringToInt(ZD[8]))/100.0;
    return IOTUtil::intToString(ret);
}

/**
 * 是否有外接传感器
 */
string SeedMachineControlLogic::hasExtralSensor()
{
    return ZD[9];
}

/**
 * 获得外接温度值，只在外接传感器存在时有效
 */
string SeedMachineControlLogic::getExtralHumi()
{
    return IOTUtil::intToString((((IOTUtil::stringToInt(ZD[14])) << 8) | IOTUtil::stringToInt(ZD[15]))/10.0);
}

/**
 * 获得外接湿度值，只在外接传感器存在时有效
 */
string SeedMachineControlLogic::getExtralTemp()
{
    return IOTUtil::intToString((((IOTUtil::stringToInt(ZD[16])<<8) | IOTUtil::stringToInt(ZD[17]))-500)/10.0);
}

/**
 * 获得外接Pm2.5值，只在外接传感器存在时有效，单位ug/m3
 */
string SeedMachineControlLogic::getExtralPm2_5()
{
    int pm2_5;
    long val=(IOTUtil::stringToInt(ZD[10])<<24) | (IOTUtil::stringToInt(ZD[11])<<16)
				|(IOTUtil::stringToInt(ZD[12])<<8) | IOTUtil::stringToInt(ZD[13]);
    pm2_5=(int)(val*15/100000);
    return IOTUtil::intToString(pm2_5);
}

/**
 * 是否有灯报警
 */
string SeedMachineControlLogic::lightWarn()
{
    return ZD[18];
}

/**
 * 当前是第几层灯报警
 */
string SeedMachineControlLogic::lightWarnInfo()
{
    return ZD[19];
}

/**
 * 是否有水位报警
 */
string SeedMachineControlLogic::waterLevelWarn()
{
    return ZD[21];
}

/**
 * 是否有水泵报警
 */
string SeedMachineControlLogic::pumpWarn()
{
    return ZD[22];
}

/**
 * 营养液报警
 */
string SeedMachineControlLogic::nutritionWarn()
{
    return ZD[13];
}

bool SeedMachineControlLogic::parseAtCommand(string result)
{
    if("" == result)
        return false;
    
    if(parseAtCommand(result))
        return true;
    
    int indexAdd = (int)result.find(IOTConstants::CMD_AT_MARK_ADD);
    
    if(-1 == indexAdd) {
        return false;
    }
    
    int indexColon = (int)result.find(IOTConstants::CMD_AT_COLON);
    
    if(-1 == indexColon) {
        return false;
    }
    
    string cmdType = IOTUtil::subString(result,indexAdd + 1, indexColon);
    string cmdParams = IOTUtil::subString(result,indexColon + 1,(int)result.length());
    
    cmdParams=IOTUtil::replace_all(cmdParams,IOTConstants::CMD_AT_WRAP, "");
    
    vector<string> params = IOTUtil::split(cmdParams,IOTConstants::PARAM_VALUE_SPLIT);
    
    string ssid = params[0];
    string resultValue = params[1];
    resultValue = IOTUtil::replace_all(resultValue,IOTConstants::CMD_AT_WRAP, "");
    
    string sub=IOTUtil::subString(cmdType,0,2);
    if(((strncmp(cmdType.c_str(),"CS",2)==0))) {
    	   return true;
    }
    return false;
}

