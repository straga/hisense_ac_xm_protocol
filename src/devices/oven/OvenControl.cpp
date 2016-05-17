//
//  OvenControl.cpp
//  TestWifiControl
//
//  Created by mozheyuan on 15/04/16.
//  Copyright (c) 2015年 zou weilong. All rights reserved.
//

#include "OvenControl.h"
#include <sstream>
#include "IOTUtil.h"

OvenControl::OvenControl(string devid)
{
    manualOrnot = true;
    ovenControlLogic = new OvenLogic();
    ovenControlLogic->deviceId = devid;
    ovenControlLogic->deviceType = "oven";
    devicesLogic = ovenControlLogic;
}

OvenControl::~OvenControl()
{
    if(ovenControlLogic)
    {
        delete ovenControlLogic;
    }
}

string OvenControl::intToHexString(int nParam)
{
    std::string temp;
    std::stringstream ss;
    ss << std::hex << nParam;
    ss >> temp;
    
    return temp;
}

string OvenControl::stringToAscii(string value)
{
    string result = "";
    for(unsigned i = 0; i < value.length(); i++)
    {
        string hexString = intToHexString(value[i]);
        result += hexString;
    }
    
    cout << "ktd=" << result << endl;
    
    return result;
}


// 设置各个功能状态
//目前不支持烤箱开关机功能
//1烤箱开机
string OvenControl::setPowerOn(bool isPowerOn, bool manualOrnot)
{
    return ovenControlLogic->setKJ(isPowerOn, manualOrnot);
}

//2烤箱关机
string OvenControl::setPowerOff(bool isPowerOn, bool manualOrnot)
{
    return ovenControlLogic->setGJ(isPowerOn, manualOrnot);
}

/**
 * 1.1	风机开关
 * */
string OvenControl::setFS(long uid, bool isOpen, bool manualOrnot)
{
    return ovenControlLogic->setFS(uid, isOpen, manualOrnot);
}

/**
 * 1.2	转叉开关
 * */
string OvenControl::setZC(long uid, bool isOpen, bool manualOrnot)
{
    return ovenControlLogic->setZC(uid, isOpen, manualOrnot);
}
/**
 *  1.3	炉灯开关
 * */
string OvenControl::setD(long uid, bool isOpen,bool manualOrnot)
{
    return ovenControlLogic->setD(uid, isOpen, manualOrnot);
}
/**
 * 1.4	上下管温度设置	新增
 *
 * 设置功能: 上管温度-高位[暂时为 0], 上管温度-低位[40~230]，下管温度-高位[暂时为 0],
 * 下管温度-低位[40~230]，提示声[0/1]
 * */
string OvenControl::setUDTubeTemperature(long uid, int temperatureU, int temperatureM, int temperatureD ,bool manualOrnot){
    int tempU_H, tempU_L, tempD_H, tempD_L, tempM_H, tempM_L;
    tempU_H = temperatureU >> 8;
    tempU_L = temperatureU & 0xFF;
    tempD_H = temperatureD >> 8;
    tempD_L = temperatureD & 0xFF;
    tempM_H = temperatureM >> 8;
    tempM_L = temperatureM & 0xFF;
    
    return ovenControlLogic->setUDTubeTemperature(uid, tempU_H, tempU_L, tempM_H, tempM_L, tempD_H, tempD_L, manualOrnot);
}

/**
* 1.5	设置菜谱标号	已划掉
* *//*
    bool OvenControl::setMenuNub(int menuNub ,bool manualOrnot){
    bool b = ovenControlLogic==NULL?false:sendContrlCommand(ovenControlLogic->setMenuNub(menuNub, manualOrnot));
    return b;
    }*/

/**
 * 8.5	状态查询
 * */
string OvenControl::getStatus(bool manualOrnot)
{
    return ovenControlLogic->getZD(manualOrnot);
}

/**
* 1.6 	功能查询
* */
string OvenControl::getGN(bool manualOrnot)
{
    return ovenControlLogic->getGN(manualOrnot);
}

/**
 * 1.7	设置菜单名字
 *
 * 设置功能: 菜谱编号[0/1/2]，温度曲线个数[0-9]，总烧烤时间-高位，总烧烤时间-低位，
 * 菜单名字[字符对应的 ascii 码，最大 64 个字符],提示声[0/1]，帧序号[0]
 * */
string OvenControl::setMenuName(long uid, int menuNub, int sub_node, int time, string name, bool manualOrnot)
{
    int time_H, time_L;
    time_H = time >> 8;
    time_L = time & 0xFF;
    
    string menuName = stringToAscii(name);
    return ovenControlLogic->setMenuName(uid, menuNub, sub_node, time_H, time_L, menuName, manualOrnot);
}

/**
 * 1.9	设置菜单温度命令扩展	新增		不确定AT指令顺序是否正确
 * */
string OvenControl::setMenuTemperatureExtend(long uid, int menuNub, int sub_node, int time, int temperatureU, int temperatureM, int temperatureD, bool rotary_fork, bool fan_power, bool remind_suspend, bool time_effective, bool upper_tube_temperature_effective, bool middle_tube_temperature_effective, bool lower_tube_temperature_effective, bool rotary_fork_effective, bool fan_power_effective, bool remind_suspend_effective,int a_x, bool manualOrnot)
{
    int time_H, time_L;
    int tempU_H, tempU_L, tempD_H, tempD_L, tempM_H, tempM_L;

    time_H = time >> 8;
    time_L = time & 0xFF;

    tempU_H = temperatureU >> 8;
    tempU_L = temperatureU & 0xFF;
    tempM_H = temperatureM >> 8;
    tempM_L = temperatureM & 0xFF;
    tempD_H = temperatureD >> 8;
    tempD_L = temperatureD & 0xFF;

    return ovenControlLogic->setMenuTemperatureExtend(uid, menuNub, sub_node, time_H, time_L, tempU_H, tempU_L, tempM_H, tempM_L, tempD_H, tempD_L, rotary_fork, fan_power, remind_suspend, time_effective,
        upper_tube_temperature_effective, middle_tube_temperature_effective, lower_tube_temperature_effective,
        rotary_fork_effective, fan_power_effective, remind_suspend_effective, a_x, manualOrnot);
}
/**
 * 1.10	曲线完整性检查	新增
 * */
string OvenControl::checkCurveIntegrity(long uid, int menuNub,bool manualOrnot)
{
    return ovenControlLogic->checkCurveIntegrity(uid, menuNub, manualOrnot);
}
/**
 * 1.11	曲线执行命令	新增
 * */
string OvenControl::excuteCurveCmd(long uid, int menuNub,bool manualOrnot)
{
   return ovenControlLogic->excuteCurveCmd(uid, menuNub, manualOrnot);
}

/**
 * 1.13	获取菜单名字
 * */
string OvenControl::getMenuName(int menuNub,bool manualOrnot)
{
    return ovenControlLogic->getMenuName(menuNub,manualOrnot);
}


/**
 * 1.15	获取温度曲线扩展命令	新增	
 * */
string OvenControl::getMenuTemperatureExtend(int menuNub,int sub_node, int a_x ,bool manualOrnot)
{
    return ovenControlLogic->getMenuTemperatureExtend( menuNub, sub_node, a_x, manualOrnot);
}

/**
 * 1.16	曲线取消执行命令	新增	
 * 
 * 设置功能: 菜谱编号[0/1/2]，提示声[0/1]，帧序号[0]
 * 
 * */
string OvenControl::cancelExcuteCurveCmd(long uid, int menuNub ,bool manualOrnot)
{
    return ovenControlLogic->cancelExcuteCurveCmd(uid, menuNub, manualOrnot);
}
/**
 * 1.17	曲线暂停-继续操作命令	新增	
 * 
 *设置功能: 菜谱编号[0/1/2]，暂停或继续[0/1],提示声[0/1]，帧序号[0]
 * 
 * */
string OvenControl::pauseOrContinueCurve(long uid, int menuNub,bool pause_or_continue, bool manualOrnot){
    
    return ovenControlLogic->pauseOrContinueCurve(uid, menuNub, pause_or_continue,  manualOrnot);
}

/********************
 *
 * 状态查询
 *
 *********************/

long OvenControl::getUid()
{
    return ovenControlLogic->getUid();
}

//1	预热状态
bool OvenControl::getStatuYR(){
    bool b =  IOTUtil::stringToInt(ovenControlLogic->getStatuYR());
    return b;
}

//2	整机开关状态
bool OvenControl::getStatuKJ(){
    bool b = IOTUtil::stringToInt(ovenControlLogic->getStatuKJ()) ;
    return b;
}

//2	炉灯开关状态
bool OvenControl::getStatuD(){
    bool b = IOTUtil::stringToInt(ovenControlLogic->getStatuD()) ;
    return b;
}

//3	转叉开关状态
bool OvenControl::getStatuZC(){
    bool b = IOTUtil::stringToInt(ovenControlLogic->getStatuZC()) ;
    return b;
}

//4	风机开关状态
bool OvenControl::getStatuFS(){
    bool b = IOTUtil::stringToInt(ovenControlLogic->getStatuZC()) ;
    return b;
}

//5	正在烘焙的曲线 （当前无烘焙返回 0xff）
string OvenControl::getStatuMenuNub(){
    string s = ovenControlLogic->getStatuMenuNub() ;
    return s;
}

//6	已完成烘烤时间高位:秒
string OvenControl::geCompletedtRoastTimeH(){
    string s = ovenControlLogic->geCompletedtRoastTimeH() ;
    return s;
}

//7	已完成烘烤时间低位:秒
string OvenControl::getCompletedRoastTimeL(){
    string s = ovenControlLogic->getCompletedRoastTimeL() ;
    return s;
}

//8	 当前设置的上管温度-高位
string OvenControl::getCurrentSettedUTTH(){
    string s = ovenControlLogic->getCurrentSettedUTTH() ;
    return s;
}

//9	当前设置的上管温度-低位
string OvenControl::getCurrentSettedUTTL(){
    string s = ovenControlLogic->getCurrentSettedUTTL() ;
    return s;
}

//当前设置的中管温度-高位
string OvenControl::getCurrentSettedMTTH()
{
    string s = ovenControlLogic->getCurrentSettedMTTH();
    
    return s;
}

//当前设置的中管温度-低位
string OvenControl::getCurrentSettedMTTL()
{
    string s = ovenControlLogic->getCurrentSettedMTTL();
    
    return s;
}

//10	当前设置的下管温度-高位
string OvenControl::getCurrentSettedLTTH(){
    string s = ovenControlLogic->getCurrentSettedLTTH() ;
    return s;
}

//11	当前设置的下管温度-低位
string OvenControl::getCurrentSettedLTTL(){
    string s = ovenControlLogic->getCurrentSettedLTTL() ;
    return s;
}

//12	 当前实际的上管温度-高位
string OvenControl::getCurrentActualUTTH(){
    string s = ovenControlLogic->getCurrentActualUTTH() ;
    return s;
}

//13	 当前实际的上管温度-低位
string OvenControl::getCurrentActualUTTL(){
    string s = ovenControlLogic->getCurrentActualUTTL() ;
    return s;
}

//当前实际的中管温度-高位
string OvenControl::getCurrentActualMTTH()
{
    string s = ovenControlLogic->getCurrentActualMTTH();
    
    return s;
}

//当前实际的中管温度-低位
string OvenControl::getCurrentActualMTTL()
{
    string s = ovenControlLogic->getCurrentActualMTTL();
    
    return s;
}

//14	 当前实际的下管温度-高位
string OvenControl::getCurrentActualLTTH(){
    string s = ovenControlLogic->getCurrentActualLTTH() ;
    return s;
}

//15	 当前实际的下管温度-低位
string OvenControl::getCurrentActualLTTL(){
    string s = ovenControlLogic->getCurrentActualLTTL() ;
    return s;
}

//16	 当前上管功率(0~100,表示 0~100%)
string OvenControl::getCurrentUpperTubePower(){
    string s = ovenControlLogic->getCurrentUpperTubePower() ;
    return s;
}

//17	当前下管功率(0~100,表示 0~100%)
string OvenControl::getCurrentLowerTubePower(){
    string s = ovenControlLogic->getCurrentLowerTubePower() ;
    return s;
}

//当前中管功率(0~100,表示 0~100%)
string OvenControl::getCurrentMeddleTubePower()
{
    string s = ovenControlLogic->getCurrentMeddleTubePower();
    
    return s;
}

//18	烤箱状态
string OvenControl::getOvenStatus(){
    string s = ovenControlLogic->getOvenStatus() ;
    return s;
}

//19	温度设置错误
string OvenControl::getTemperatureSettedError(){
    string s = ovenControlLogic->getTemperatureSettedError() ;
    return s;
}

//20	存储设备故障
string OvenControl::getStorageDeviceError(){
    string s = ovenControlLogic->getStorageDeviceError() ;
    return s;
}

//21 	烤箱发热装置故障
string OvenControl::getHeatingDeviceError(){
    string s = ovenControlLogic->getHeatingDeviceError() ;
    return s;
}

//22	 温度传感器错误
string OvenControl::getTemperatureSensorError(){
    string s = ovenControlLogic->getTemperatureSensorError() ;
    return s;
}

//23	 I2C 设备错误
string OvenControl::getI2CDeviceError(){
    string s = ovenControlLogic->getI2CDeviceError() ;
    return s;
}

//24	211-0 命令执行结果（当此项为 1 时，检查下面4 项的错误置位）
// 	菜单名称错误，总烧烤时间错误，曲线个数错误，菜单曲线错误
string OvenControl::get211_0CommandExecutedResult(){
    string s = ovenControlLogic->get211_0CommandExecutedResult() ;
    return s;
}

//25	菜单名称错误
string OvenControl::getMenuNameError(){
    string s = ovenControlLogic->getMenuNameError() ;
    return s;
}

//26	总烧烤时间错误
string OvenControl::getTotalRoastTimeError(){
    string s = ovenControlLogic->getTotalRoastTimeError() ;
    return s;
}

//27	曲线个数错误
string OvenControl::getCurveNumbersError(){
    string s = ovenControlLogic->getCurveNumbersError() ;
    return s;
}

//28	菜单曲线错误
string OvenControl::getMenuCurveError0(){
    string s = ovenControlLogic->getMenuCurveError0() ;
    return s;
}


//29	211-2命令执行结果（当此项为 1 时，检查下面 6 项的错误置位）
//	设置时间错误，上下管温度设置错误，风机设置错误, 转叉设置错误, 曲线子节点过多, 菜单曲线错误

string OvenControl::get211_2CommandExecutedResult(){
    string s = ovenControlLogic->get211_2CommandExecutedResult() ;
    return s;
}

//30	设置时间错误
string OvenControl::getSettedTimeError(){
    string s = ovenControlLogic->getSettedTimeError() ;
    return s;
}

//31	上下管温度设置错误
string OvenControl::getULTTSettedError(){
    string s = ovenControlLogic->getULTTSettedError() ;
    return s;
}

//32	风机设置错误
string OvenControl::getFanSettedError(){
    string s = ovenControlLogic->getFanSettedError() ;
    return s;
}

//33	转叉设置错误
string OvenControl::getRotaryForkSettedError(){
    string s = ovenControlLogic->getRotaryForkSettedError() ;
    return s;
}

//34	曲线子节点过多
string OvenControl::getCurveSubnodeMoreThanEnoughError(){
    string s = ovenControlLogic->getCurveSubnodeMoreThanEnoughError() ;
    return s;
}

//35	菜单曲线错误
string OvenControl::getMenuCurveError2(){
    string s = ovenControlLogic->getMenuCurveError2() ;
    return s;
}

//36	211-3 命令执行结果（0：完整，1：不完整）
string OvenControl::get211_3CommandExecutedResult(){
    string s = ovenControlLogic->get211_3CommandExecutedResult() ;
    return s;
}


//37	211-4 命令执行结果（当此项为 1 时，检查下面 4 项的错误置位）
//		曲线错误, 该曲线不存在, 烤箱未开机, 烤箱正工作在烘焙程序中

string OvenControl::get211_4CommandExecutedResult(){
    string s = ovenControlLogic->get211_4CommandExecutedResult() ;
    return s;
}

//38	曲线错误
string OvenControl::getMenuCurveError4(){
    string s = ovenControlLogic->getMenuCurveError4() ;
    return s;
}

//39	 该曲线不存在
string OvenControl::getCurveNotExistError(){
    string s = ovenControlLogic->getCurveNotExistError() ;
    return s;
}

//40	 烤箱未开机
string OvenControl::getNotPowerOnError(){
    string s = ovenControlLogic->getNotPowerOnError() ;
    return s;
}

//41	 烤箱正工作在烘焙程序中
string OvenControl::getWorkingInRoastProcedureError(){
    string s = ovenControlLogic->getWorkingInRoastProcedureError() ;
    return s;
}

//42	 211-5 命令执行的返回： （0：曲线正确，1：曲线错误）
string OvenControl::get211_5CommandExecutedResult(){
    string s = ovenControlLogic->get211_5CommandExecutedResult() ;
    return s;
}

//43	 211-7 命令执行结果（当此项为 1 时，检查下面2 项的错误置位）
string OvenControl::get211_7CommandExecutedResult(){
    string s = ovenControlLogic->get211_7CommandExecutedResult() ;
    return s;
}

//44	 该曲线不存在
string OvenControl::getCurveNotExistError7(){
    string s = ovenControlLogic->getCurveNotExistError7() ;
    return s;
}

//45	  曲线子节点不存在
string OvenControl::getCurveSubnodeNotExistError(){
    string s = ovenControlLogic->getCurveSubnodeNotExistError() ;
    return s;
}

//46	  211-8 命令执行结果（曲线是否存在）
string OvenControl::get211_8CommandExecutedResult(){
    string s = ovenControlLogic->get211_8CommandExecutedResult() ;
    return s;
}

//47	 211-9 命令执行结果（烤箱是否工作在烘焙曲线模式）
string OvenControl::get211_9CommandExecutedResult(){
    string s = ovenControlLogic->get211_9CommandExecutedResult() ;
    return s;
}

/********************
 *
 * 功能查询
 *
 *********************/
//1	加热管个数
int OvenControl::getHeatTubeNum()
{
    return ovenControlLogic->getHeatTubeNum();
}

//2	炉灯是否存在，
int OvenControl::getOvenLampExitOrNot()
{
    return ovenControlLogic->getOvenLampExitOrNot();
}

//3	转叉功能是否存在
int OvenControl::getRotaryForkExitOrNot()
{
    return ovenControlLogic->getRotaryForkExitOrNot();
}

//4	是否有热风循环
int OvenControl::getHeatAirCirculationOrNot()
{
    return ovenControlLogic->getHeatAirCirculationOrNot();
}

//5	是否支持解冻模式
int OvenControl::getSupportThawingModeOrNot()
{
    return ovenControlLogic->getSupportThawingModeOrNot();
}

//6	是否支持低温发酵功能
int OvenControl::getSupportLowTemperatureFermentationOrNot()
{
    return ovenControlLogic->getSupportLowTemperatureFermentationOrNot();
}

//7	是否有报警功能
int OvenControl::getSupportAlarmOrNot()
{
    return ovenControlLogic->getSupportAlarmOrNot();
}

int OvenControl::getStatuRunTime(){
    return ovenControlLogic->getStatuRunTime();
}

int OvenControl::getStatuNowTemperature(){
    return ovenControlLogic->getStatuNowTemperature();
}

//OvenMenuInfo* OvenControl::getOvenMenuInfos()
//{
//    return ovenControlLogic->getOvenMenuInfos();
//}

/* 分析返回结果 */
bool OvenControl::ParseResult(string result)
{
//    cout << "-------------result:" << result << endl;
//    bool bresult = DevicesControl::ParseResult(result);
//    if(!bresult)
//    {
//        if(ovenControlLogic != NULL)
//        {
//            bresult = ovenControlLogic->parseAtCommand(result);
//            if(bresult)
//            {
//                messageResult();
//            }
//        }
//    }
    
    return false;
}
