//
//  OvenLogic.h
//  TestWifiControl
//
//  Created by mozheyuan on 15/04/16.
//  Copyright (c) 2015年 zou weilong. All rights reserved.
//

#ifndef __TestWifiControl__OvenLogic__
#define __TestWifiControl__OvenLogic__

#include <stdio.h>
#include "DeviceLogic.h"

class OvenLogic : public DeviceLogic
{
    
private:
    string intToHexString(int nParam);
    
public:

    //OvenMenuInfo *ovenMenuInfo;
    
public:
    
    OvenLogic();
    
    ~OvenLogic();
    
    int getHeatTubeNum();
    int getOvenLampExitOrNot();
    int getRotaryForkExitOrNot();
    int getHeatAirCirculationOrNot();
    int getSupportThawingModeOrNot();
    int getSupportLowTemperatureFermentationOrNot();
    int getGNifUpdateEEPROM();
    int getSupportAlarmOrNot();
    //OvenMenuInfo* getOvenMenuInfos();
    int getGNbatteryIFdetection();

    long getUid();
    string setUid(long uid);
    string getStatuYR();
    string getStatuKJ();
    string getStatuD();
    string getStatuZC();
    string getStatuFS();
    string getStatuMenuNub();
    string geCompletedtRoastTimeH();
    string getCompletedRoastTimeL();
    string getCurrentSettedUTTH();
    string getCurrentSettedUTTL();
    string getCurrentSettedMTTH();
    string getCurrentSettedMTTL();
    string getCurrentSettedLTTH();
    string getCurrentSettedLTTL();
    string getCurrentActualUTTH();
    string getCurrentActualUTTL();
    string getCurrentActualMTTH();
    string getCurrentActualMTTL();
    string getCurrentActualLTTH();
    string getCurrentActualLTTL();
    string getOuterRelativeHumidity();
    string getCurrentUpperTubePower();
    string getCurrentMeddleTubePower();
    string getCurrentLowerTubePower();
    string getOvenStatus();
    string getTemperatureSettedError();
    string getStorageDeviceError();
    string getHeatingDeviceError();
    string getTemperatureSensorError();
    string getI2CDeviceError();
    string get211_0CommandExecutedResult();
    string getMenuNameError();
    string getTotalRoastTimeError();
    string getCurveNumbersError();
    string getMenuCurveError0();
    string get211_2CommandExecutedResult();
    string getSettedTimeError();
    string getULTTSettedError();
    string getFanSettedError();
    string getRotaryForkSettedError();
    string getCurveSubnodeMoreThanEnoughError();
    string getMenuCurveError2();
    string get211_3CommandExecutedResult();
    string get211_4CommandExecutedResult();
    string getMenuCurveError4();
    string getCurveNotExistError();
    string getNotPowerOnError();
    string getWorkingInRoastProcedureError();
    string get211_5CommandExecutedResult();
    string get211_7CommandExecutedResult();
    string getCurveNotExistError7();
    string getCurveSubnodeNotExistError();
    string get211_8CommandExecutedResult();
    string get211_9CommandExecutedResult();
    
    int getStatuRunTime();
    int getStatuNowTemperature();
    
    string setFS(long uid, bool isOpen, bool manualOrnot,int flag);
    string setKJ(bool isOpen, bool manualOrnot,int flag);
    string setGJ(bool isOpen, bool manualOrnot,int flag);
    string setZC(long uid, bool isOpen, bool manualOrnot,int flag);
    string setD(long uid, bool isOpen, bool manualOrnot,int flag);
    string setUDTubeTemperature(long uib, int temperatureUH, int temperatureUL, int temperatureMH, int temperatureML, int temperatureDH, int temperatureDL, bool manualOrnot,int flag);
    string getZD(bool manualOrnot,int flag);
    string getGN(bool manualOrnot,int flag);
    string setMenuName(long uid, int nub ,int points, int timeA ,int timeB ,string nameASCII ,bool manualOrnot,int flag);
    string setMenuTemperatureExtend(long uid, int points, int sub_node, int timeA,int timeB, int temperatureUH, \
        int temperatureUL, int temperatureMH, int temperatureML, int temperatureDH, int temperatureDL, bool rotary_fork,\
        bool fan_power, bool remind_suspend, bool time_effective, bool upper_tube_temperature_effective, bool middle_tube_temperature_effective,\
        bool lower_tube_temperature_effective, bool rotary_fork_effective, bool fan_power_effective, bool remind_suspend_effective, int a_x, bool manualOrnot,int flag);
    string checkCurveIntegrity(long uid, int points,bool manualOrnot,int flag);
    string excuteCurveCmd(long uid, int points,bool manualOrnot,int flag);
    string getMenuName(int menuNub,bool manualOrnot,int flag);
    string getMenuTemperatureExtend(int menuNub,int sub_node, int a_x ,bool manualOrnot,int flag);
    string cancelExcuteCurveCmd(long uid, int points,bool manualOrnot,int flag);
    string pauseOrContinueCurve(long uid, int points,bool pause_or_continue, bool manualOrnot,int flag);
    
    bool parseAtCommand(string result);
};

#endif /* defined(__TestWifiControl__OvenLogic__) */
