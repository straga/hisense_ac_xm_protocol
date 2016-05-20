//
//  OvenLogic.cpp
//  TestWifiControl
//
//  Created by mozheyuan on 15/04/16.
//  Copyright (c) 2015年 zou weilong. All rights reserved.
//

#include "OvenLogic.h"
#include <sstream>
#include <stdlib.h>
#include "IOTConstants.h"
#include <iostream>
#include "IOTUtil.h"

OvenLogic::OvenLogic()
{
    At_QureyStatus = "OVSQ";
    At_QueryFuntion = "OVFQ";
    DEVICE_TYPE = 0x27;
    At_Status_Num = 57;
    At_Funtion_Num = 7;
    
    for(int i = 0; i < At_Funtion_Num; i++)
    {
        GN.push_back(0);
    }
    
    for(int i = 0; i < At_Status_Num; i++)
    {
        ZD.push_back("0");
    }
    
    for(int i = 0; i < At_Funtion_Num; i++)
    {
        if(GN[i]>0)
        {
            GN_EN.push_back(1);
        }
        else
        {
            GN_EN.push_back(0);
        }
    }
    
    //saveDevicesAllFun("0,0");
    
    //SetPowerStatus(false);
    
    //ovenMenuInfo = new OvenMenuInfo();
}

OvenLogic::~OvenLogic()
{
//    if(ovenMenuInfo)
//    {
//        delete ovenMenuInfo;
//    }
}

/**********************
 *
 * 功能设置
 *
 * *******************/

//setUid
string OvenLogic::setUid(long uid)
{
    string atcmd = IOTUtil::intToString((int) ((uid >> 24) & 0xff)) + IOTConstants::PARAM_VALUE_SPLIT
				+ IOTUtil::intToString((int) ((uid >> 16) & 0xff)) + IOTConstants::PARAM_VALUE_SPLIT
				+ IOTUtil::intToString((int) ((uid >> 8) & 0xff)) + IOTConstants::PARAM_VALUE_SPLIT
				+ IOTUtil::intToString((int) (uid & 0xff));
    return atcmd;
    //return createNetBytes(atcmd);
}

/**********************
 *
 * 功能设置
 *
 * *******************/
/**
 * 1.1	风机开关
 * */
string OvenLogic::setFS(long uid, bool isOpen, bool manualOrnot, int flag)
{
    string isOpenStr = IOTUtil::intToString(isOpen);
    ZD[8] = isOpenStr;
    string atcmd =  IOTConstants::CMD_AT_MARK + "OVFP" +
				IOTConstants::CMD_AT_EQUALS_SINGNAL + deviceId + IOTConstants::PARAM_VALUE_SPLIT +
				setUid(uid) + IOTConstants::PARAM_VALUE_SPLIT + isOpenStr + IOTConstants::PARAM_VALUE_SPLIT +
				IOTUtil::intToString(manualOrnot) + IOTConstants::CMD_AT_WRAP;
	if(flag == 2)
		return atcmd;
    return createNetBytes(atcmd);
}

/**
 * 	烤箱开机
 * */
string OvenLogic::setKJ(bool isOpen, bool manualOrnot,int flag)
{
    string isOpenStr = IOTUtil::intToString(isOpen);
    ZD[5] = isOpenStr;
    string atcmd = IOTConstants::CMD_AT_MARK + "KLKJ" +
				IOTConstants::CMD_AT_EQUALS_SINGNAL + deviceId +
				IOTConstants::PARAM_VALUE_SPLIT + isOpenStr  +
				IOTConstants::PARAM_VALUE_SPLIT +
				IOTUtil::intToString(manualOrnot) +
				IOTConstants::CMD_AT_WRAP;
	if(flag == 2)
		return atcmd;
    return createNetBytes(atcmd);
}

/**
 * 	烤箱关机
 * */
string OvenLogic::setGJ(bool isOpen, bool manualOrnot,int flag)
{
    string isOpenStr = IOTUtil::intToString(isOpen);
    ZD[5] = isOpenStr;
    string atcmd =  IOTConstants::CMD_AT_MARK + "KLGJ" +
				IOTConstants::CMD_AT_EQUALS_SINGNAL + deviceId +
				IOTConstants::PARAM_VALUE_SPLIT + isOpenStr  +
				IOTConstants::PARAM_VALUE_SPLIT +
				IOTUtil::intToString(manualOrnot) +
				IOTConstants::CMD_AT_WRAP;
	if(2 == flag)
		return atcmd;
    return createNetBytes(atcmd);
}

/**
 * 1.2	转叉开关
 * */
string OvenLogic::setZC(long uid, bool isOpen, bool manualOrnot,int flag)
{
    string isOpenStr = IOTUtil::intToString(isOpen);
    ZD[7] = isOpenStr;
    string atcmd =  IOTConstants::CMD_AT_MARK + "OVRF" +
				IOTConstants::CMD_AT_EQUALS_SINGNAL + deviceId +
				IOTConstants::PARAM_VALUE_SPLIT + setUid(uid) +
                IOTConstants::PARAM_VALUE_SPLIT + isOpenStr  +
                IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(manualOrnot) +
				IOTConstants::CMD_AT_WRAP;
	if(2 == flag)
		return atcmd;
    return createNetBytes(atcmd);
}

/**
 *  1.3	炉灯开关
 * */
string OvenLogic::setD(long uid, bool isOpen,bool manualOrnot,int flag)
{
    string isOpenStr = IOTUtil::intToString(isOpen);
    ZD[6] = isOpenStr;
    string atcmd =  IOTConstants::CMD_AT_MARK + "OVLAMP" +
				IOTConstants::CMD_AT_EQUALS_SINGNAL + deviceId +
                IOTConstants::PARAM_VALUE_SPLIT + setUid(uid) +
				IOTConstants::PARAM_VALUE_SPLIT + isOpenStr  +
				IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(manualOrnot) +
				IOTConstants::CMD_AT_WRAP;
	if(2 == flag)
		return atcmd;
    return createNetBytes(atcmd);
}

/**
 * 1.4	上下管温度设置	新增
 *
 * 设置功能: 上管温度-高位[暂时为 0], 上管温度-低位[40~230]，下管温度-高位[暂时为 0],
 * 下管温度-低位[40~230]，提示声[0/1]
 * */
string OvenLogic::setUDTubeTemperature(long uid, int temperatureUH, int temperatureUL, int temperatureMH, int temperatureML, int temperatureDH, int temperatureDL, bool manualOrnot,int flag)
{
    string atcmd =  IOTConstants::CMD_AT_MARK + "OVUDT" +
				IOTConstants::CMD_AT_EQUALS_SINGNAL + deviceId +
                IOTConstants::PARAM_VALUE_SPLIT + setUid(uid) +
				IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(temperatureUH) +
				IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(temperatureUL) +
                IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(temperatureMH) +
				IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(temperatureML) +
				IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(temperatureDH) +
				IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(temperatureDL) +
				IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(manualOrnot) +
				IOTConstants::CMD_AT_WRAP;
	if(2 == flag)
		return atcmd;
    return createNetBytes(atcmd);
}

/*	*//**
       * 1.5	设置菜谱标号	此条命令	已经被划去
       * *//*
            string OvenLogic::setMenuNub(int menuNub,bool manualOrnot){
            ZD[2] = string.valueOf(menuNub);
            return IOTConstants::CMD_AT_MARK + "OVMENUM" +
            IOTConstants::CMD_AT_EQUALS_SINGNAL + dev_applianceId +
            IOTConstants::PARAM_VALUE_SPLIT + menuNub  +
            IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::changeboolToString(manualOrnot) +
            IOTConstants::CMD_AT_WRAP;
            }*/
/**
 * 8.5	状态查询
 * */
string OvenLogic::getZD(bool manualOrnot,int flag)
{
    string atcmd =  IOTConstants::CMD_AT_MARK + "OVSQ" +
				IOTConstants::CMD_AT_EQUALS_SINGNAL + deviceId +
				IOTConstants::PARAM_VALUE_SPLIT +"?"  +
				IOTConstants::PARAM_VALUE_SPLIT +
				IOTUtil::intToString(manualOrnot) +
				IOTConstants::CMD_AT_WRAP;
	if(2 == flag)
		return atcmd;
    return createNetBytes(atcmd);
}

/**
 * 1.6 	功能查询(暂时不支持)
 * */
string OvenLogic::getGN(bool manualOrnot,int flag)
{
    string atcmd =  IOTConstants::CMD_AT_MARK + "OVFQ" +
           IOTConstants::CMD_AT_EQUALS_SINGNAL + deviceId +
           IOTConstants::PARAM_VALUE_SPLIT + "?" +
           IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(manualOrnot) +
           IOTConstants::CMD_AT_WRAP;
	if(2 == flag)
		return atcmd;
    return createNetBytes(atcmd);
}

/**
 * 1.7	设置菜单名字
 * 设置功能: 菜谱编号[0/1/2]，温度曲线个数[0-9]，总烧烤时间-高位，总烧烤时间-低位，
 * 菜单名字[字符对应的 ascii 码，最大 64 个字符],提示声[0/1]，帧序号[0]
 *
 * IOTConstants::PARAM_VALUE_SPLIT + device_fd + 	帧序号???
 * IOTConstants::PARAM_VALUE_SPLIT + "0" +			???
 * */
string OvenLogic::setMenuName(long uid, int nub ,int points, int timeA ,int timeB ,string nameASCII ,bool manualOrnot,int flag)
{
    string atcmd =  IOTConstants::CMD_AT_MARK + "OVSMN" +
				IOTConstants::CMD_AT_EQUALS_SINGNAL + deviceId +
                IOTConstants::PARAM_VALUE_SPLIT + setUid(uid) +
				IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(nub)  +
				IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(points) +
				IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(timeA) +
				IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(timeB) +
				IOTConstants::PARAM_VALUE_SPLIT + nameASCII +
				IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(manualOrnot) +
				IOTConstants::PARAM_VALUE_SPLIT + "0" +
				IOTConstants::CMD_AT_WRAP;
    if(2 == flag)
		return atcmd;
    return createNetBytes(atcmd);
}

/**
 * 1.9	设置菜单温度命令扩展	新增		不确定AT指令顺序是否正确
 *
 * 参数： 菜谱编号[0/1/2]，子节点[0-9]，时间-高位[0~0x46]，时间-低位[0~254]，
 * 上管温度-高位[暂时为 0], 上管温度-低位[40~230]， 下管温度-高位[暂时为 0], 下管温度-低位[40~230]，
 * 转叉开关[0/1],风机开关[0/1],提醒暂停[0/1], 时间有效设置位[0/1] ，
 * 上管温度有效设置位[0/1] ，下管温度有效设置位[0/1] ，转叉开关有效设置位[0/1]，
 * 风机开关有效设置位[0/1]，提醒暂停有效设置位[0/1]，提示声[0/1]，帧序号[0-254]
 * */
string OvenLogic::setMenuTemperatureExtend(long uid, int points, int sub_node, int timeA,int timeB, int temperatureUH, int temperatureUL,\
	int temperatureMH, int temperatureML, int temperatureDH, int temperatureDL, bool rotary_fork, bool fan_power, bool remind_suspend, \
	bool time_effective, bool upper_tube_temperature_effective, bool middle_tube_temperature_effective, \
	bool lower_tube_temperature_effective, bool rotary_fork_effective, bool fan_power_effective, bool remind_suspend_effective, \
	int a_x, bool manualOrnot,int flag)
{
    string atcmd =  IOTConstants::CMD_AT_MARK + "OVSMTEx" +
				IOTConstants::CMD_AT_EQUALS_SINGNAL + deviceId +
                IOTConstants::PARAM_VALUE_SPLIT + setUid(uid) +
				IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(points) +
				IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(sub_node) +
				IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(timeA) +
				IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(timeB) +
				IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(temperatureUH) +
				IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(temperatureUL) +
                IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(temperatureMH) +
				IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(temperatureML) +
				IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(temperatureDH) +
				IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(temperatureDL) +
				IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(rotary_fork) +
				IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(fan_power) +
				IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(remind_suspend) +
				IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(time_effective) +
				IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(upper_tube_temperature_effective) +
                IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(middle_tube_temperature_effective) +
				IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(lower_tube_temperature_effective) +
				IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(rotary_fork_effective) +
				IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(fan_power_effective) +
				IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(remind_suspend_effective) +
				IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(manualOrnot) +
				IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(a_x) +
				IOTConstants::CMD_AT_WRAP;
	if(2 == flag)
		return atcmd;
    return createNetBytes(atcmd);
}

/**
 * 1.10	曲线完整性检查	新增
 *
 * 设置功能: 菜谱编号[0/1/2]，提示声[0/1]，帧序号[0]
 * */
string OvenLogic::checkCurveIntegrity(long uid, int points,bool manualOrnot,int flag)
{
    string atcmd = IOTConstants::CMD_AT_MARK + "OVCIC" +
				IOTConstants::CMD_AT_EQUALS_SINGNAL + deviceId +
                IOTConstants::PARAM_VALUE_SPLIT + setUid(uid) +
				IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(points) +
				IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(manualOrnot) +
                IOTConstants::PARAM_VALUE_SPLIT + "0" +
				IOTConstants::CMD_AT_WRAP;
	if(2 == flag)
		return atcmd;
    return createNetBytes(atcmd);
}

/**
 * 1.11	曲线执行命令	新增
 *
 * 设置功能: 菜谱编号[0/1/2]，提示声[0/1]，帧序号[0]
 * */
string OvenLogic::excuteCurveCmd(long uid, int points,bool manualOrnot,int flag)
{
    string atcmd = IOTConstants::CMD_AT_MARK + "OVCEC" +
				IOTConstants::CMD_AT_EQUALS_SINGNAL + deviceId +
                IOTConstants::PARAM_VALUE_SPLIT + setUid(uid) +
				IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(points) +
				IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(manualOrnot) +
				IOTConstants::PARAM_VALUE_SPLIT + "0" +
				IOTConstants::CMD_AT_WRAP;
	if(2 == flag)
		return atcmd;
    return createNetBytes(atcmd);
}

/**
 * 1.13	获取菜单名字
 *
 * 设置功能: 菜谱编号[0/1/2]，提示声[0/1]，帧序号[0]
 *
 * 需要增加	帧序号[0]
 * */
string OvenLogic::getMenuName(int menuNub,bool manualOrnot,int flag)
{
//    ovenMenuInfo = new OvenMenuInfo();
    //ovenMenuInfo->setMenuNob(menuNub);
    string atcmd = IOTConstants::CMD_AT_MARK + "OVGMN" +
				IOTConstants::CMD_AT_EQUALS_SINGNAL + deviceId +
				IOTConstants::PARAM_VALUE_SPLIT + "?"  +
				IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(menuNub) +
				IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(manualOrnot) +
				IOTConstants::PARAM_VALUE_SPLIT + "0" +
				IOTConstants::CMD_AT_WRAP;
	if(2 == flag)
		return atcmd;
    return createNetBytes(atcmd);
}

/**
 * 1.15	获取温度曲线扩展命令	新增
 *
 * 设置功能: 菜谱编号[0/1/2/3]，子节点[0-9]，提示声[0/1]，帧序号[0-254]
 * */
string OvenLogic::getMenuTemperatureExtend(int menuNub,int sub_node, int a_x ,bool manualOrnot,int flag)
{
    string atcmd = IOTConstants::CMD_AT_MARK + "OVGTCEx" +
				IOTConstants::CMD_AT_EQUALS_SINGNAL + deviceId +
				IOTConstants::PARAM_VALUE_SPLIT + "?"  +
				IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(menuNub) +
				IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(sub_node) +
				IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(manualOrnot) +
    //				IOTConstants::PARAM_VALUE_SPLIT + device_fd +
				IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(a_x) +
				IOTConstants::CMD_AT_WRAP;
	if(2 == flag)
		return atcmd;
    return createNetBytes(atcmd);
}

/**
 * 1.16	曲线取消执行命令	新增
 *
 * 设置功能: 菜谱编号[0/1/2]，提示声[0/1]，帧序号[0]
 *
 * */
string OvenLogic::cancelExcuteCurveCmd(long uid, int points, bool manualOrnot,int flag)
{
    string atcmd = IOTConstants::CMD_AT_MARK + "OVCCE" +
				IOTConstants::CMD_AT_EQUALS_SINGNAL + deviceId +
                IOTConstants::PARAM_VALUE_SPLIT + setUid(uid) +
				IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(points) +
				IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(manualOrnot) +
				IOTConstants::PARAM_VALUE_SPLIT + "0" +
				IOTConstants::CMD_AT_WRAP;
	if(2 == flag)
		return atcmd;
    return createNetBytes(atcmd);
}
/**
 * 1.17	曲线暂停-继续操作命令	新增
 *
 *设置功能: 菜谱编号[0/1/2]，暂停或继续[0/1],提示声[0/1]，帧序号[0]
 *
 * */
string OvenLogic::pauseOrContinueCurve(long uid, int points,bool pause_or_continue, bool manualOrnot,int flag)
{
    string atcmd = IOTConstants::CMD_AT_MARK + "OVPCC" +
				IOTConstants::CMD_AT_EQUALS_SINGNAL + deviceId +
                IOTConstants::PARAM_VALUE_SPLIT + setUid(uid) +
				IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(points) +
				IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(pause_or_continue) +
				IOTConstants::PARAM_VALUE_SPLIT + IOTUtil::intToString(manualOrnot) +
				IOTConstants::PARAM_VALUE_SPLIT + "0" +
				IOTConstants::CMD_AT_WRAP;
	if(2 == flag)
		return atcmd;
    return createNetBytes(atcmd);
}


/********************
 *
 * 状态查询
 *
 *********************/

long OvenLogic::getUid()
{
    return (IOTUtil::stringToInt(ZD[0]) << 24) | (IOTUtil::stringToInt(ZD[1]) << 16)
				| (IOTUtil::stringToInt(ZD[2]) << 8) | (IOTUtil::stringToInt(ZD[3]));
}

string OvenLogic::getStatuYR(){
    return ZD[4];//0	预热状态
}

string OvenLogic::getStatuKJ(){
    return ZD[5];//1	整机开关状态
}

string OvenLogic::getStatuD(){
    return ZD[6];//2	炉灯开关状态
}

string OvenLogic::getStatuZC(){
    return ZD[7];//3	转叉开关状态
}

string OvenLogic::getStatuFS(){
    return ZD[8];//4	风机开关状态
}

string OvenLogic::getStatuMenuNub(){
    return ZD[9];//5	正在烘焙的曲线 （当前无烘焙返回 0xff）
}

string OvenLogic::geCompletedtRoastTimeH(){
    return ZD[10];//6	已完成烘烤时间高位:秒
}

string OvenLogic::getCompletedRoastTimeL(){
    return ZD[11];//7	已完成烘烤时间低位:秒
}

string OvenLogic::getCurrentSettedUTTH(){
    return ZD[12];//8	 当前设置的上管温度-高位
}

string OvenLogic::getCurrentSettedUTTL(){
    return ZD[13];//9	当前设置的上管温度-低位
}

string OvenLogic::getCurrentSettedMTTH(){
    return ZD[14];//8	 当前设置的上管温度-高位
}

string OvenLogic::getCurrentSettedMTTL(){
    return ZD[15];//9	当前设置的上管温度-低位
}

string OvenLogic::getCurrentSettedLTTH(){
    return ZD[16];//10	当前设置的下管温度-高位
}

string OvenLogic::getCurrentSettedLTTL(){
    return ZD[17];//11	当前设置的下管温度-低位
}

string OvenLogic::getCurrentActualUTTH(){
    return ZD[18];//12	 当前实际的上管温度-高位
}

string OvenLogic::getCurrentActualUTTL(){
    return ZD[19];//13	 当前实际的上管温度-低位
}

string OvenLogic::getCurrentActualMTTH(){
    return ZD[20];//20	 当前实际的中管温度-高位
}

string OvenLogic::getCurrentActualMTTL(){
    return ZD[21];//21	 当前实际的中管温度-低位
}

string OvenLogic::getCurrentActualLTTH(){
    return ZD[22];//14	 当前实际的下管温度-高位
}

string OvenLogic::getCurrentActualLTTL(){
    return ZD[23];//15	 当前实际的下管温度-低位
}

string OvenLogic::getCurrentUpperTubePower(){
    return ZD[24];//16	 当前上管功率(0~100,表示 0~100%)
}

string OvenLogic::getCurrentMeddleTubePower(){
    return ZD[25];//25	 当前中管功率(0~100,表示 0~100%)
}

string OvenLogic::getCurrentLowerTubePower(){
    return ZD[26];//17	当前下管功率(0~100,表示 0~100%)
}

string OvenLogic::getOvenStatus(){
    return ZD[27];//18	烤箱状态
}

string OvenLogic::getTemperatureSettedError(){
    return ZD[28];//19	温度设置错误
}

string OvenLogic::getStorageDeviceError(){
    return ZD[29];//20	存储设备故障
}

string OvenLogic::getHeatingDeviceError(){
    return ZD[30];//21 	烤箱发热装置故障
}

string OvenLogic::getTemperatureSensorError(){
    return ZD[31];//22	 温度传感器错误
}

string OvenLogic::getI2CDeviceError(){
    return ZD[32];//23	 I2C 设备错误
}

string OvenLogic::get211_0CommandExecutedResult(){
    return ZD[33];//24	211-0 命令执行结果（当此项为 1 时，检查下面4 项的错误置位）
    // 	菜单名称错误，总烧烤时间错误，曲线个数错误，菜单曲线错误
}

string OvenLogic::getMenuNameError(){
    return ZD[34];//25	菜单名称错误
}

string OvenLogic::getTotalRoastTimeError(){
    return ZD[35];//26	总烧烤时间错误
}

string OvenLogic::getCurveNumbersError(){
    return ZD[36];//27	曲线个数错误
}

string OvenLogic::getMenuCurveError0(){
    return ZD[37];//28	菜单曲线错误
}

string OvenLogic::get211_2CommandExecutedResult(){
    return ZD[38];//29	211-2命令执行结果（当此项为 1 时，检查下面 6 项的错误置位）
    //	设置时间错误，上下管温度设置错误，风机设置错误, 转叉设置错误, 曲线子节点过多, 菜单曲线错误
}

string OvenLogic::getSettedTimeError(){
    return ZD[39];//30	设置时间错误
}

string OvenLogic::getULTTSettedError(){
    return ZD[40];//31	上下管温度设置错误
}

string OvenLogic::getFanSettedError(){
    return ZD[41];//32	风机设置错误
}

string OvenLogic::getRotaryForkSettedError(){
    return ZD[42];//33	转叉设置错误
}

string OvenLogic::getCurveSubnodeMoreThanEnoughError(){
    return ZD[43];//34	曲线子节点过多
}

string OvenLogic::getMenuCurveError2(){
    return ZD[44];//35	菜单曲线错误
}

string OvenLogic::get211_3CommandExecutedResult(){
    return ZD[45];//36	211-3 命令执行结果（0：完整，1：不完整）
}

string OvenLogic::get211_4CommandExecutedResult(){
    return ZD[46];//37	211-4 命令执行结果（当此项为 1 时，检查下面 4 项的错误置位）
    //	曲线错误, 该曲线不存在, 烤箱未开机, 烤箱正工作在烘焙程序中
}

string OvenLogic::getMenuCurveError4(){
    return ZD[47];//38	曲线错误
}

string OvenLogic::getCurveNotExistError(){
    return ZD[48];//39	 该曲线不存在
}

string OvenLogic::getNotPowerOnError(){
    return ZD[49];//40	 烤箱未开机
}

string OvenLogic::getWorkingInRoastProcedureError(){
    return ZD[50];//41	 烤箱正工作在烘焙程序中
}

string OvenLogic::get211_5CommandExecutedResult(){
    return ZD[51];//42	 211-5 命令执行的返回： （0：曲线正确，1：曲线错误）
}

string OvenLogic::get211_7CommandExecutedResult(){
    return ZD[52];//43	 211-7 命令执行结果（当此项为 1 时，检查下面2 项的错误置位）
}

string OvenLogic::getCurveNotExistError7(){
    return ZD[53];//44	 该曲线不存在
}

string OvenLogic::getCurveSubnodeNotExistError(){
    return ZD[54];//45	  曲线子节点不存在
}

string OvenLogic::get211_8CommandExecutedResult(){
    return ZD[55];//46	  211-8 命令执行结果（曲线是否存在）
}

string OvenLogic::get211_9CommandExecutedResult(){
    return ZD[56];//47	 211-9 命令执行结果（烤箱是否工作在烘焙曲线模式）
}


int OvenLogic::getStatuRunTime(){
    int zd10, zd11;

    stringstream ss;
    ss << ZD[10];
    ss >> zd10;

    ss << ZD[11];
    ss >> zd11;

    return (zd10<<8) + zd11;//已完成的烘焙时间
}

int OvenLogic::getStatuNowTemperature(){
    int zd12, zd13;
    
    stringstream ss;
    ss << ZD[12];
    ss >> zd12;
    
    ss << ZD[13];
    ss >> zd13;
    
    return (zd12<<8) + zd13;//当前实际上管温度
}


/********************
 *
 * 功能查询
 *
 *********************/
int OvenLogic::getHeatTubeNum(){
    return GN[0];
}

int OvenLogic::getOvenLampExitOrNot(){
    return GN[1];
}

int OvenLogic::getRotaryForkExitOrNot(){
    return GN[2];
}

int OvenLogic::getHeatAirCirculationOrNot(){
    return GN[3];
}

int OvenLogic::getSupportThawingModeOrNot(){
    return GN[4];
}

int OvenLogic::getSupportLowTemperatureFermentationOrNot(){
    return GN[5];
}

int OvenLogic::getSupportAlarmOrNot(){
    return GN[6];
}

/*int OvenLogic::getGNbatteryIFdetection(){
    return GN[7];
}*/

//OvenMenuInfo* OvenLogic::getOvenMenuInfos()
//{
//    return ovenMenuInfo;
//}

string OvenLogic::intToHexString(int nParam)
{
    std::string temp;
    std::stringstream ss;
    ss << std::hex << nParam;
    ss >> temp;
    
    return temp;
}

bool OvenLogic::parseAtCommand(string result) {
    
//    if(HisenseDevicesLogic::parseAtCommand(result))
//    {
//        return true;
//    }
//    
//    if(result == "")
//    {
//        return false;
//    }
//    
//    size_t indexAdd = result.find(IOTConstants::CMD_AT_MARK_ADD);
//    if(indexAdd == string::npos)
//    {
//        return false;
//    }
//    
//    size_t indexColon = result.find(IOTConstants::CMD_AT_COLON);
//    if(indexColon == string::npos)
//    {
//        return false;
//    }
//    
//    size_t indexSplite = result.find(IOTConstants::PARAM_VALUE_SPLIT);
//    if(indexSplite == string::npos)
//    {
//        return false;
//    }
//    
//    string cmdType = result.substr(indexAdd + 1, indexColon - indexAdd - 1);
//    string cmdParams = result.substr(indexColon + 1, result.length() - indexColon - 1);
//    vector<string> params = IOTUtil::split(result, IOTConstants::PARAM_VALUE_SPLIT);
//    string ssid = params[0];
//    string resultValue = params[1];
//    resultValue = IOTUtil::replace_all(resultValue, IOTConstants::CMD_AT_WRAP, "");
//    
////    /* SSID 不同 */
////    if(ssid != "" && !(ssid == dev_applianceId))
////    {
////        return false;
////    }
//    
//    if("ERROR" == ssid) {
//    	   cout << "OvenLogic parseAtCommand   ERROR result=" << result <<endl;
//    	   AtResult =IOTConstants::AT_COMMAND_RETURN_FAIL;
//   		   AtErrorNo ="0";
//    	   return true;
//    }
//    
//    if("OVSMN" == cmdType) {//设置菜单名字
//    	   cout << "OvenLogic parseAtCommand  OVSMN（设置菜单名字）  result=" << result <<endl;
//    	   return true;
//    }
//    
//    if("OVSMTEx" == cmdType) {//设置菜单温度
//    	   cout << "OvenLogic parseAtCommand  OVSMT（设置菜单温度）  result=" << result <<endl;
//    	   return true;
//    }
//    
//    if("OVCIC" == cmdType) {//曲线完整性检查
//    	   cout << "OvenLogic parseAtCommand  OVCIC（曲线完整性检查）  result=" << result << endl;
//    	   return true;
//    }
//    
//    if("OVCEC" == cmdType) {//曲线执行
//    	   cout << "OvenLogic parseAtCommand  OVCIC（曲线执行）  result=" << result << endl;
//    	   return true;
//    }
//    
//    if("OVSTC" == cmdType) {//设置菜单温度
//    	   cout << "OvenLogic parseAtCommand  OVSTC（设置菜单温度）  result=" << result <<endl;
//    	   return true;
//    }
//    
//    if("OVGTC" == cmdType) {//获取菜单温度
//        cout << "OvenLogic parseAtCommand  OVGTC（获取菜单温度）  result=" << result <<endl;
//        string temp = IOTUtil::replace_all(params[4], "\r\n", "");
//        int t1 = IOTUtil::stringToInt(temp);
//        
//        temp = IOTUtil::replace_all(params[5], "\r\n", "");
//        int t2 = IOTUtil::stringToInt(temp);
//        
//        string t = intToHexString(t1) + intToHexString(t2);
//        int tHex = IOTUtil::stringToInt(t);
//        
//        temp = IOTUtil::replace_all(params[2], "\r\n", "");
//        int d1 = IOTUtil::stringToInt(temp);
//        
//        temp = IOTUtil::replace_all(params[3], "\r\n", "");
//        int d2 = IOTUtil::stringToInt(temp);
//        
//        string d = intToHexString(d1) + intToHexString(d2);
//        int dHex = IOTUtil::stringToInt(d);
//        
//        cout << "***********Hex dHex:" << dHex << "  tHex:" << tHex << endl;
//        temp = IOTUtil::replace_all(params[0], "\r\n", "");
//        ovenMenuInfo->setMenuNob(IOTUtil::stringToInt(temp));
//        temp = IOTUtil::replace_all(params[7], "\r\n", "");
//        
//        temp = IOTUtil::replace_all(params[7], "\r\n", "");
//        int position = IOTUtil::stringToInt(temp);
//        ovenMenuInfo->getSetDates()[position] = dHex;
//        
//        ovenMenuInfo->getSetTemperatures()[position] = tHex;
//        if(ovenMenuInfo->getPoints() != ovenMenuInfo->getSetDates().size())
//        {
//            return false;
//        }
//        
//        return true;
//    }
//    
//    if("OVGFD" == cmdType) {//获取设备描述符
//    	   cout << "OvenLogic parseAtCommand  OVGFD（获取设备描述符）  result=" << result <<endl;
////    	   device_fd=(params[0]).replace("\r\n", "");
//    	   return true;
//    }
//    
//    if("OVGMN" == cmdType) {//获取菜单名
//        string temp = IOTUtil::replace_all(params[1], "\r\n", "");
//        ovenMenuInfo->setPoints(IOTUtil::stringToInt(temp));
//    	   
//        temp = IOTUtil::replace_all(params[2], "\r\n", "");
//        int t1 = IOTUtil::stringToInt(temp);
//        
//        temp = IOTUtil::replace_all(params[3], "\r\n", "");
//        int t2 = IOTUtil::stringToInt(temp);
//        
//        string t = intToHexString(t1) + intToHexString(t2);
//        int tHex = IOTUtil::stringToInt(t);
//        ovenMenuInfo->setRoastTime(tHex);
//    	   
//        temp = IOTUtil::replace_all(params[4], "\r\n", "");
//        ovenMenuInfo->setName(temp);
//        
//        //temp = IOTUtil::replace_all(params[7], "\r\n", "");
//        //cout << "OvenLongic  OVGMN tHex:" << tHex << "Name:" << temp << endl;
//        
//        return true;
//    }
//    
//    if("OVFQ" == cmdType)
//    {
//        for(int i = 0; i < At_Funtion_Num && i < params.size(); i++)
//        {
//            GN[i] = IOTUtil::stringToInt(params[i]);
//        }
//        
//        return true;
//    }
//    
//    if("KT" == cmdType)
//    {
//        return true;
//    }
//    
//    /*string sub = cmdType.substr(0, 2);
//    if ("OV" == cmdType)
//    {
//        return true;
//    }*/
    
    return false;
}





