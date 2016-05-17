//
//  IOTConstants.h
//  devices
//
//  Created by 肖芳亮 on 14/12/4.
//  Copyright (c) 2014年 zou weilong. All rights reserved.
//

#ifndef __LiveHome__IOTConstants__
#define __LiveHome__IOTConstants__

#include <stdio.h>
#include <string>

using namespace::std;

class IOTConstants
{
public:
    static const string CMD_TYPE;
    static const int    AT_COMMAND_MIN_LENGTH;
    static const string INTENT_PARAM_TIMER_TYPE;
    static const string INTENT_PARAM_TIMER_ON_HOUR;
    static const string INTENT_PARAM_TIMER_ON_MINUTE;
    static const string INTENT_PARAM_TIMER_ON_POWER;
    static const string INTENT_PARAM_TIMER_OFF_HOUR;
    static const string INTENT_PARAM_TIMER_OFF_MINUTE;
    static const string INTENT_PARAM_TIMER_OFF_POWER;
    static const bool   CMD_MANUAL;
    static const string AT_COMMAND_RETURN_SUCCESS;
    static const string AT_COMMAND_RETURN_FAIL;
    static const string CMD_AT_MARK;
    static const string CMD_AT_MARK_ADD;
    static const string CMD_AT_WRAP;
    static const string CMD_AT_COLON;
    static const string CMD_AT_EQUALS_SINGNAL;
    static const string CMD_AT_GET_STATUS_MARK;
    static const string PARAM_VALUE_SPLIT;
    static const string PARAM_PATH_FILE;
    static const string PARAM_PATH_TYPE_FILE;
    static const string PARAM_PATH_TYPE_CONTENT;
    
    
    static const string AT_PORTOCOL_SET_BOOLE_TRUE;
    static const string AT_PORTOCOL_SET_BOOLE_FALSE;
    static const string INTENT_PARAM_CDN_IP;
    static const string INENT_PARAM_SCAN_CODE_RESULT;
    static const string AIRCON_CONTROL_TYPE_LOCAL;
    static const string AIRCON_CONTROL_TYPE_INTERNET;
    static const string INTENT_PARAM_CONTROL_TYPE;
    static const string INTENT_PARAM_APPLIANCE_ID;
    static const string INTENT_PARAM_APPLIANCE_MODEL;
    static const string INTENT_PARAM_APPLIANCE_IP;
    static const string INTENT_PARAM_ROUTER_WIFI_NAME;
    static const string INTENT_PARAM_ONLINE;
    static const string INTENT_APPLIANCES_HOME_LIST;
    static const string INTENT_PARAM_WIND_MAGNITUDE;
    static const string INTENT_PARAM_SLEEP_MODE_POWER;
    static const string INTENT_PARAM_SLEEP_MODE;
    static const string INTENT_PARAM_WIND_DIRECT_UD_MODE;
    static const string INTENT_PARAM_WIND_DIRECT_LR_MODE;
    static const string INTENT_PARAM_MODEL_ID;
    static const string INTENT_PARAM_RUN_MODE;
    static const string INTENT_PARAM_EXMINE_DATAS;
    static const string INTENT_PARAM_EXMINE_RESULT;
    
    static const int    APPLIANCE_RESULT_EXMINE;
    static const string APPLIANCE_RESULT_PARAM;
    static const string APPLIANCE_POWER_PARAM;
    static const string APPLIANCE_ONLINE_PARAM;
    static const string APPLIANCE_MODE_PARAM;
    static const string APPLIANCE_LOCALIP_PARAM;
    static const string APPLIANCE_APPLIANCE_ID;
    static const string APPLIANCE_APPLIANCE_CMD;
    static const string APPLIANCE_APPLIANCE_RESULT;
    static const string APPLIANCE_APPLIANCE_ERRORNO;
    
    static const int RESULT_SLEEP_MODE_CODE;
    static const int RESULT_WIND_MAGNITUDE_CODE;
    static const int RESULT_POWER_ON_TIMER;
    static const int RESULT_POWER_OFF_TIMER;
    static const int RESULT_IMAGE_CAPTURE;
    static const int RESULT_IMAGE_SELECT;
    static const int RESULT_WIND_DIRECT_UP_DOWN;
    static const int RESULT_WIND_DIRECT_LEFT_RIGHT;
    static const int RESULT_SCAN_MODEL_CODE;
    static const int RESULT_SCAN_APPLIANCE_ID;
    
    static const int RESULT_USERAGREE_CHECKBOX;
    static const int RESULT_USERAGREE_CHECKBOX_UN;
    
    
    static const int MSG_DELETE_APPLIANCE_FAIL;
    static const int MSG_DELETE_APPLIANCE_SUCCESS;
    static const int MSG_PROCESS_UNBIND_APPLIANCE;
    static const int MSG_SET_AIRCON_POWER_RESULT;
    static const int MSG_SET_AIRCON_RUNMODE_RESULT;
    static const int MSG_GET_AIRCON_STATUS_FAIL;
    static const int MSG_GET_AIRCON_ONLINE_RESULT;
    static const int MSG_AIRCON_INIT_ERROR;
    static const int MSG_GET_WEATHER_FAIL;
    static const int MSG_GET_WEATHER_SUCCESS;
    static const int MSG_REFRESH_LIST_DATA;
    static const int MSG_GET_AIRCON_INDOOR_TEMPRATURE_RESULT;
    static const int MSG_GET_ALL_STATUS_ERROR;
    static const int MSG_INIT_APK_UPDATE;
    static const int MSG_INIT_APK_UPDATE_COMPLETED;
    static const int MSG_GET_APPLIANCE_IP_RESULT;
    static const int MSG_SWITCH_APPLIANCE_TO_SERVER;
    static const int MSG_SEND_UDP_CMD;
    static const int MSG_RECEIVE_UDP_CMD;
    static const int MSG_CLEAR_WIFI_CONFIG_PARS;
    static const int MSG_USER_OPEN_WIFI;
    static const int MSG_SWITCH_AIRCON;
    static const int MSG_SWITCH_AIRCON_FAIL;
    static const int MSG_LISTVIEW_SET_TURE;
    static const int MSG_LISTVIEW_SET_FALSE;
    static const int MSG_GET_APPLIANCE_STATUS;
    static const int MSG_GET_APPLIANCE_STAT;
    static const int MSG_GET_APPLIANCE_RESULT;
    
    static const int MSG_UDP_BINDER_SMARTBOX;
    static const int MSG_UDP_BINDER_SA_TO_SMARTBOX;
    
    static const int MSG_START_EXPERTMODE;
    static const int MSG_STOP_EXPERTMODE;
    
    static const string CHECKBOX_MSG;
    static const string APPLIANCE_OFF_LINE_ERROR;
    static const string APPLIANCE_UPGRADE_ERROR;
    static const string UNKNOW_PHOTOS_URL;
    static const int    SWITCH_TO_ONLINE_STATUS_TYPE_LAN;
    static const int    SWITCH_TO_ONLINE_STATUS_TYPE_DOMAIN;
    static const int    Disable_local;
    
    static const string SA_SOCKET_SERVER_PORT;
    static const string PHONE_SOCKET_SERVER_PORT;
    
    static const int SENT_TO_CND;
    static const int SENT_TO_SA;
    static const int SENT_TO_PHONE;
    
    static const int CONNECT_TO_CND;
    static const int CONNECT_TO_SMARTBOX;
    static const int CONNECT_TO_SA;
    
    static const int SA_SOCKET_CONNECT_ERROR;
    static const int SA_SOCKET_READ_TIMEOUT;
    static const int PHONE_SOCKET_CONNECT_ERROR;
    static const int PHONE_SOCKET_READ_TIMEOUT;
    static const int CDN_SOCKET_CONNECT_ERROR;
    static const int CDN_SOCKET_READ_TIMEOUT;
    
    static const int AIRCON_TYPE;
    static const int DEHUMIDIFIER_TYPE;
    static const int PURIFY_TYPE;
    static const int HOTFAN_TYPE;
     static const string SA_AIRCON_TYPE;
     static const string SA_DEHUMIDIFIER_TYPE;
     static const string SA_PURIFY_TYPE;
     static const string SA_HOTFAN_TYPE;
     static const string BOOLEAN_TRUE;
     static const string BOOLEAN_FALSE;
     static const string CMD_TO_BOX;
     static const string CMD_TO_KTSBOX;
     static const string CMD_TO_BOX_GETALLSTATUS;
     static const string CMD_TO_BOX_SETSMARTMODE;
     static const string CMD_TO_BOX_SETMUTESWTICH ;
     static const string CMD_TO_BOX_SETPOWERSTATU;
     static const string CMD_TO_BOX_SETTYPE;
     static const string CMD_TO_BOX_CONFIGBOX ;
     static const string CMD_TO_BOX_SCENETEST_IN ;
     static const string CMD_TO_BOX_SCENETEST_OUT;
     static const string CMD_TO_BOX_PRODUCT_TEST ;
     static const string CMD_TO_BOX_UNBINDER ;
     static const string CMD_TO_BOX_SA_UNBINDER ;
     static const string CMD_TO_BOX_UPDATE_DIYCURVE;
     static const string CMD_TO_BOX_ENTER_DEMO_MODE;
     static const string CMD_TO_BOX_SET_SEASON;
     static const string CMD_TO_BOX_NOTIFYSMARTMODEJOIN;
     static const string CMD_TO_BOX_BINDSASUCCEED;
    
     static const string BOX_RETURN_GETALLSTATUS;
     static const string BOX_RETURN_SETSMARTMODE;
     static const string BOX_RETURN_SETMUTESWTICH;
     static const string BOX_RETURN_SETPOWERSTATU;
     static const string BOX_RETURN_SETTYPE;
     static const string BOX_RETURN_CONFIGBOX;
     static const string BOX_RETURN_SCENETEST_IN;
     static const string BOX_RETURN_SCENETEST_OUT;
     static const string BOX_RETURN_PRODUCT_TEST;
     static const string BOX_RETURN_SCENETEST;
     static const string BOX_RETURN_UNBINDER ;
     static const string BOX_RETURN_SA_UNBINDER;
     static const string BOX_RETURN_UPDATE_DIYCURVE;
     static const string BOX_RETURN_ENTER_DEMO_MODE;
     static const string BOX_RETURN_SET_SEASON;
     static const string CMD_TO_MOBILE_NOTIFYSMARTMODEQUIT;
     static const string BOX_RETURN_BINDSASUCCEED;
    
     static const string NOSA_SA_MODE;
     static const string CONTROLLABLE_SA_MODE ;
     static const string UNCONTROLLABLE_SA_MODE ;
    
     static const string STANDARD_SMART_MODE;
     static const string CHILDREN_SMART_MODE;
     static const string ELDER_SMART_MODE;
     static const string OFF_SMART_MODE;
    
     static const string AIR_QUALITY_GOOD ;
     static const string AIR_QUALITY_GENERAL  ;
     static const string AIR_QUALITY_BAD ;
    
     static const string AIR_COMFORT_GOOD;
     static const string AIR_COMFORT_GENERAL  ;
     static const string AIR_COMFORT_BAD ;
    
    /*aircon*/
     static const string AIRCONDITION_MODE_HEAT ;
     static const string AIRCONDITION_MODE_COOL;
     static const string AIRCONDITION_MODE_DEHUMIDIFY;
     static const string AIRCONDITION_MODE_BLOW ;
     static const string AIRCONDITION_MODE_AUTO ;
     static const string AIRCONDITION_WIND_STRONG ;
     static const string AIRCONDITION_WIND_MIDDLE;
     static const string AIRCONDITION_WIND_WEAK ;
     static const string AIRCONDITION_WIND_AUTO ;
     static const string AIRCONDITION_WIND_MUTE ;
    //aircon body check
    //OutDoor
     static const string  AIRCONDITION_BODY_CHECK_OutdoorEEPROMTrouble ;
     static const string AIRCONDITION_BODY_CHECK_OutdoorPipeTemperatureSensorTrouble ;
     static const string AIRCONDITION_BODY_CHECK_OutdoorExhausTemperatureSensorTrouble;
     static const string AIRCONDITION_BODY_CHECK_OutdoorEnvironmentTemperatureSensorTrouble ;
     static const string AIRCONDITION_BODY_CHECK_OutdoorControlBoardTrouble;
     static const string AIRCONDITION_BODY_CHECK_AlternatingCurrentOvervoltageProtect;
     static const string AIRCONDITION_BODY_CHECK_AlternatingCurrentUndervoltageProtect ;
     static const string AIRCONDITION_BODY_CHECK_OutdooEnvironmentOvertemperatureProtect ;
     static const string AIRCONDITION_BODY_CHECK_OutdoorMachineTrouble ;
     static const string AIRCONDITION_BODY_CHECK_OutdoorBoardOrCompressorTrouble;
    //InDoor
     static const string AIRCONDITION_BODY_CHECK_IndoorTemperatureSensorTrouble ;
     static const string AIRCONDITION_BODY_CHECK_IndoorPipeTemperatureSensorTrouble;
     static const string AIRCONDITION_BODY_CHECK_IndoorHumiditySensorTrouble ;
     static const string AIRCONDITION_BODY_CHECK_IndoorFanMotorTrouble;
     static const string AIRCONDITION_BODY_CHECK_PioneerGrillingProtectTrouble;
     static const string AIRCONDITION_BODY_CHECK_IndoorVoltageZeroCrossDetectionTrouble;
     static const string AIRCONDITION_BODY_CHECK_IndoorOutdoorCommunicationTrouble;
     static const string AIRCONDITION_BODY_CHECK_IndoorContrlScreenCommunicationTrouble ;
     static const string AIRCONDITION_BODY_CHECK_IndoorContrlKeypadCommunicationTrouble;
     static const string AIRCONDITION_BODY_CHECK_IndoorContrlWIFICommunicationTrouble ;
     static const string AIRCONDITION_BODY_CHECK_IndoorContrlChargeCommunicationTrouble ;
     static const string AIRCONDITION_BODY_CHECK_IndoorContrlEEPROMTrouble ;
    //Not Show
     static const string AIRCONDITION_BODY_CHECK_OutdoorCoilOverloadUpFrequency;
     static const string AIRCONDITION_BODY_CHECK_OutdoorCoilOverloadDownFrequency ;
     static const string AIRCONDITION_BODY_CHECK_IndoorCoilOverloadUpFrequency;
     static const string AIRCONDITION_BODY_CHECK_IndoorCoilOverloadDownFrequency;
     static const string AIRCONDITION_BODY_CHECK_PressureUpFrequency ;
     static const string AIRCONDITION_BODY_CHECK_PressureDownFrequency;
     static const string AIRCONDITION_BODY_CHECK_IndoorCoilFreezingUpFrequency ;
     static const string AIRCONDITION_BODY_CHECK_IndoorCoilFreezingDownFrequency ;
     static const string AIRCONDITION_BODY_CHECK_CommunicationDownFrequency;
     static const string AIRCONDITION_BODY_CHECK_ModuleTemperaturelimitFrequency;
     static const string AIRCONDITION_BODY_CHECK_ModulationRatelimitFrequency ;
     static const string AIRCONDITION_BODY_CHECK_PhaseCurrentlimitFrequency ;
     static const string AIRCONDITION_BODY_CHECK_PowerSaveUpFrequency ;
     static const string AIRCONDITION_BODY_CHECK_PowerSaveDownFrequency ;
     static const string AIRCONDITION_BODY_CHECK_OvercurrentUpFrequency ;
     static const string AIRCONDITION_BODY_CHECK_OvercurrentDownFrequency;
    
    /* aircleaner*/
     static const string AIRCLEANER_MODE_CLEARDUST ;
     static const string AIRCLEANER_MODE_CLEARSMELL ;
     static const string AIRCLEANER_MODE_SMART;
     static const string AIRCLEANER_MODE_MUTE;
     static const string AIRCLEANER_MODE_SLEEP ;
     static const string AIRCLEANER_WIND_STRONG ;
     static const string AIRCLEANER_WIND_MIDDLE ;
     static const string AIRCLEANER_WIND_WEAK ;
     static const string AIRCLEANER_WIND_AUTO ;
     static const string AIRCLEANER_WIND_CLEAR;
    //aircleaner body check
     static const string  AIRCLEANER_BODY_CHECK_MotorError ;
     static const string AIRCLEANER_BODY_CHECK_LeanError ;
     static const string AIRCLEANER_BODY_CHECK_ChangeFilter;
     static const string AIRCLEANER_BODY_CHECK_HumidityWheelError ;
     static const string AIRCLEANER_BODY_CHECK_WaterSinkEmptyError ;
     static const string AIRCLEANER_BODY_CHECK_WaterSinkNotSetup ;
     static const string AIRCLEANER_BODY_CHECK_HumiditySensorError ;
     static const string AIRCLEANER_BODY_CHECK_DustSensor;
     static const string AIRCLEANER_BODY_CHECK_SmellSensor ;
    
    /* dehumidifier*/
     static const string DEHUMIDIFIER_MODE_CONTINUE ;
     static const string DEHUMIDIFIER_MODE_NORMAL ;
     static const string DEHUMIDIFIER_MODE_AUTO ;
     static const string DEHUMIDIFIER_MODE_HEAT  ;
     static const string DEHUMIDIFIER_WIND_STRONG ;
     static const string DEHUMIDIFIER_WIND_WEAK ;
     static const string DEHUMIDIFIER_WIND_AUTO ;
    //dehumidifier body check
     static const string  DEHUMIDIFIER_BODY_CHECK_FilterNetCleanWarning ;
     static const string   DEHUMIDIFIER_BODY_CHECK_HumidSensorError ;
     static const string DEHUMIDIFIER_BODY_CHECK_PumpTempratureError ;
     static const string DEHUMIDIFIER_BODY_CHECK_IndoorTempratureError ;
     static const string DEHUMIDIFIER_BODY_CHECK_WaterPumpWarning ;
     static const string DEHUMIDIFIER_BODY_CHECK_WaterFullWarning ;
    
    /*hotfan*/
     static const string HOTFAN_MODE_FULLHEAT ;
     static const string HOTFAN_MODE_DIRECT ;
     static const string HOTFAN_MODE_INDOOR ;
     static const string HOTFAN_MODE_AUTO ;
     static const string HOTFAN_WIND_STRONG ;
     static const string HOTFAN_WIND_MIDDLE ;
     static const string HOTFAN_WIND_WEAK ;
     static const string HOTFAN_WIND_AUTO ;
    
     static const string BATTERY_STATUS_UNKNOWN ;
     static const string BATTERY_STATUS_CHARGING ;
     static const string BATTERY_STATUS_DISCHARGING ;
     static const string BATTERY_STATUS_FULL ;
    
     static const string BRODCAST_REFRESH_UI ;
     static const string BRODCAST_CHANGE_SMARTMODE ;
     static const string BRODCAST_REFRESH_SMARTMODE ;
     static const string BRODCAST_SMARTBOX_UPDATE_DIYCURVE ;
    
     static const string BRODCAST_SMARTBOX_MUTE_STOP ;
     static const string BRODCAST_SMARTBOX_MUTE_START ;
     static const string BRODCAST_SMARTBOX_POWER_STOP ;
     static const string BRODCAST_SMARTBOX_POWER_START ;
     static const string BRODCAST_SMARTBOX_UPDATE_SAINFO;
    
     /*wifi*/
     static const string WIFI_STATUS_UNKNOWN;
     static const string WIFI_STATUS_CONNECTED;
     static const string WIFI_STATUS_CONNECTING;
     static const string WIFI_STATUS_UNCONNECT;
     static const string WIFI_STATUS_AP;
};
#endif /* defined(__LiveHome__IOTConstants__) */
