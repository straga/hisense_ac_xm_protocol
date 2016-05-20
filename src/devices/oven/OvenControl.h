//
//  OvenControl.h
//  devices
//
//  Created by mozheyuan on 15/04/16.
//  Copyright (c) 2015年 zou weilong. All rights reserved.
//

#ifndef __TestWifiControl__OvenControl__
#define __TestWifiControl__OvenControl__

#include <stdio.h>
#include "DeviceControl.h"
#include "OvenLogic.h"

class OvenControl : public DeviceControl
{
private:
    bool manualOrnot;
    OvenLogic* ovenControlLogic;
    
private:
    string intToHexString(int nParam);
    string stringToAscii(string value);
    
public:
    static const string SYS_CODE;
    
public:
    
    OvenControl(string deviceId);
    
    ~OvenControl();
    
    string setPowerOn(bool isPowerOn, bool manualOrnot,int flag);
    string setPowerOff(bool isPowerOn, bool manualOrnot,int flag);
    string setFS(long uid, bool isOpen, bool manualOrnot,int flag);
    string setZC(long uid, bool isOpen, bool manualOrnot,int flag);
    string setD(long uid, bool isOpen,bool manualOrnot,int flag);
    string setUDTubeTemperature(long uid, int temperatureU, int temperatureM, int temperatureD ,bool manualOrnot,int flag);
    string getStatus(bool manualOrnot,int flag);
    string getGN(bool manualOrnot,int flag);
    string setMenuName(long uid, int menuNub, int sub_node, int time, string name, bool manualOrnot,int flag);
    string setMenuTemperatureExtend(long uid, int menuNub, int sub_node, int time, int temperatureU, int temperatureM, int temperatureD, bool rotary_fork, bool fan_power, bool remind_suspend, bool time_effective, bool upper_tube_temperature_effective, bool middle_tube_temperature_effective, bool lower_tube_temperature_effective, bool rotary_fork_effective, bool fan_power_effective, bool remind_suspend_effective, int a_x, bool manualOrnot,int flag);
    string checkCurveIntegrity(long uid, int menuNub,bool manualOrnot,int flag);
    string excuteCurveCmd(long uid, int menuNub,bool manualOrnot,int flag);
    string getMenuName(int menuNub,bool manualOrnot,int flag);
    string getMenuTemperatureExtend(int menuNub,int sub_node, int a_x ,bool manualOrnot,int flag);
    string cancelExcuteCurveCmd(long uid, int menuNub ,bool manualOrnot,int flag);
    string pauseOrContinueCurve(long uid, int menuNub,bool pause_or_continue, bool manualOrnot,int flag);

    long getUid();
    bool getStatuYR();
    bool getStatuKJ();
    bool getStatuD();
    bool getStatuZC();
    bool getStatuFS();
    string  getStatuMenuNub();
    string  geCompletedtRoastTimeH();
    string  getCompletedRoastTimeL();
    string  getCurrentSettedUTTH();
    string  getCurrentSettedUTTL();
    string  getCurrentSettedMTTH();
    string  getCurrentSettedMTTL();
    string  getCurrentSettedLTTH();
    string  getCurrentSettedLTTL();
    string  getCurrentActualUTTH();
    string  getCurrentActualUTTL();
    string  getCurrentActualMTTH();
    string  getCurrentActualMTTL();
    string  getCurrentActualLTTH();
    string  getCurrentActualLTTL();
    string  getCurrentUpperTubePower();
    string  getCurrentLowerTubePower();
    string  getCurrentMeddleTubePower();
    string  getOvenStatus();
    string  getTemperatureSettedError();
    string  getStorageDeviceError();
    string  getHeatingDeviceError();
    string  getTemperatureSensorError();
    string  getI2CDeviceError();
    string  get211_0CommandExecutedResult();
    string  getMenuNameError();
    string  getTotalRoastTimeError();
    string  getCurveNumbersError();
    string  getMenuCurveError0();
    string  get211_2CommandExecutedResult();
    string  getSettedTimeError();
    string  getULTTSettedError();
    string  getFanSettedError();
    string  getRotaryForkSettedError();
    string  getCurveSubnodeMoreThanEnoughError();
    string  getMenuCurveError2();
    string  get211_3CommandExecutedResult();
    string  get211_4CommandExecutedResult();
    string  getMenuCurveError4();
    string  getCurveNotExistError();
    string  getNotPowerOnError();
    string  getWorkingInRoastProcedureError();
    string  get211_5CommandExecutedResult();
    string  get211_7CommandExecutedResult();
    string  getCurveNotExistError7();
    string  getCurveSubnodeNotExistError();
    string  get211_8CommandExecutedResult();
    string  get211_9CommandExecutedResult();
    int getHeatTubeNum();
    int getOvenLampExitOrNot();
    int getRotaryForkExitOrNot();
    int getHeatAirCirculationOrNot();
    int getSupportThawingModeOrNot();
    int getSupportLowTemperatureFermentationOrNot();
    int getSupportAlarmOrNot();
    int  getStatuRunTime();
    int  getStatuNowTemperature();
    //OvenMenuInfo* getOvenMenuInfos();
    bool ParseResult(string result);
};

#endif /* defined(__TestWifiControl__OvenControl__) */
