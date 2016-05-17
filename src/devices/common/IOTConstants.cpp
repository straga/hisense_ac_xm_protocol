//
//  IOTConstants.cpp
//  devices
//
//  Created by 肖芳亮 on 14/12/4.
//  Copyright (c) 2014年 zou weilong. All rights reserved.
//

#include "IOTConstants.h"

const string IOTConstants::CMD_TYPE = "cmdType";
const int    IOTConstants::AT_COMMAND_MIN_LENGTH = 8;
const string IOTConstants::INTENT_PARAM_TIMER_TYPE = "timer_type";
const string IOTConstants::INTENT_PARAM_TIMER_ON_HOUR = "timer_on_hour";
const string IOTConstants::INTENT_PARAM_TIMER_ON_MINUTE = "timer_on_minute";
const string IOTConstants::INTENT_PARAM_TIMER_ON_POWER = "timer_on_power";
const string IOTConstants::INTENT_PARAM_TIMER_OFF_HOUR = "timer_off_hour";
const string IOTConstants::INTENT_PARAM_TIMER_OFF_MINUTE = "timer_off_minute";
const string IOTConstants::INTENT_PARAM_TIMER_OFF_POWER = "timer_off_power";
const bool   IOTConstants::CMD_MANUAL= true;
const string IOTConstants::AT_COMMAND_RETURN_SUCCESS = "SUCCEED";
const string IOTConstants::AT_COMMAND_RETURN_FAIL = "ERROR";
const string IOTConstants::CMD_AT_MARK = "AT+";
const string IOTConstants::CMD_AT_MARK_ADD = "+";
const string IOTConstants::CMD_AT_WRAP = "\r\n";
const string IOTConstants::CMD_AT_COLON = ":";
const string IOTConstants::CMD_AT_EQUALS_SINGNAL = "=";
const string IOTConstants::CMD_AT_GET_STATUS_MARK = "?";
const string IOTConstants::PARAM_VALUE_SPLIT = ",";
const string IOTConstants::PARAM_PATH_FILE = "file://";
const string IOTConstants::PARAM_PATH_TYPE_FILE = "file";
const string IOTConstants::PARAM_PATH_TYPE_CONTENT = "content";


const string IOTConstants::AT_PORTOCOL_SET_BOOLE_TRUE = "1";
const string IOTConstants::AT_PORTOCOL_SET_BOOLE_FALSE = "0";
const string IOTConstants::INTENT_PARAM_CDN_IP = "cdn_ip";
const string IOTConstants::INENT_PARAM_SCAN_CODE_RESULT = "barcode_result";
const string IOTConstants::AIRCON_CONTROL_TYPE_LOCAL = "local";
const string IOTConstants::AIRCON_CONTROL_TYPE_INTERNET = "cdn";
const string IOTConstants::INTENT_PARAM_CONTROL_TYPE = "control_type";
const string IOTConstants::INTENT_PARAM_APPLIANCE_ID = "appliance_id";
const string IOTConstants::INTENT_PARAM_APPLIANCE_MODEL = "appliance_model";
const string IOTConstants::INTENT_PARAM_APPLIANCE_IP = "appliance_ip";
const string IOTConstants::INTENT_PARAM_ROUTER_WIFI_NAME = "router_wifi_name";
const string IOTConstants::INTENT_PARAM_ONLINE = "appliance_online";
const string IOTConstants::INTENT_APPLIANCES_HOME_LIST = "action.appliance.home.list";
const string IOTConstants::INTENT_PARAM_WIND_MAGNITUDE = "wind_magnitude";
const string IOTConstants::INTENT_PARAM_SLEEP_MODE_POWER = "sleep_mode_power";
const string IOTConstants::INTENT_PARAM_SLEEP_MODE = "sleep_mode";
const string IOTConstants::INTENT_PARAM_WIND_DIRECT_UD_MODE = "direct_up_down_mode";
const string IOTConstants::INTENT_PARAM_WIND_DIRECT_LR_MODE = "direct_left_right_mode";
const string IOTConstants::INTENT_PARAM_MODEL_ID = "model_id";
const string IOTConstants::INTENT_PARAM_RUN_MODE = "run_mode";
const string IOTConstants::INTENT_PARAM_EXMINE_DATAS = "exmine_datas";
const string IOTConstants::INTENT_PARAM_EXMINE_RESULT = "exmine_result";

const int    IOTConstants::APPLIANCE_RESULT_EXMINE = 1100;
const string IOTConstants::APPLIANCE_RESULT_PARAM = "result";
const string IOTConstants::APPLIANCE_POWER_PARAM = "power";
const string IOTConstants::APPLIANCE_ONLINE_PARAM = "online";
const string IOTConstants::APPLIANCE_MODE_PARAM = "mode";
const string IOTConstants::APPLIANCE_LOCALIP_PARAM = "localip";
const string IOTConstants::APPLIANCE_APPLIANCE_ID = "appliance_id";
const string IOTConstants::APPLIANCE_APPLIANCE_CMD = "appliance_cmd";
const string IOTConstants::APPLIANCE_APPLIANCE_RESULT = "appliance_result";
const string IOTConstants::APPLIANCE_APPLIANCE_ERRORNO = "appliance_errorno";

const int IOTConstants::RESULT_SLEEP_MODE_CODE = 200;
const int IOTConstants::RESULT_WIND_MAGNITUDE_CODE = 201;
const int IOTConstants::RESULT_POWER_ON_TIMER = 202;
const int IOTConstants::RESULT_POWER_OFF_TIMER = 203;
const int IOTConstants::RESULT_IMAGE_CAPTURE = 204;
const int IOTConstants::RESULT_IMAGE_SELECT = 205;
const int IOTConstants::RESULT_WIND_DIRECT_UP_DOWN = 206;
const int IOTConstants::RESULT_WIND_DIRECT_LEFT_RIGHT = 207;
const int IOTConstants::RESULT_SCAN_MODEL_CODE = 208;
const int IOTConstants::RESULT_SCAN_APPLIANCE_ID = 209;

const int IOTConstants::RESULT_USERAGREE_CHECKBOX = 210;
const int IOTConstants::RESULT_USERAGREE_CHECKBOX_UN = 211;


const int IOTConstants::MSG_DELETE_APPLIANCE_FAIL = 101;
const int IOTConstants::MSG_DELETE_APPLIANCE_SUCCESS = 102;
const int IOTConstants::MSG_PROCESS_UNBIND_APPLIANCE = 103;
const int IOTConstants::MSG_SET_AIRCON_POWER_RESULT = 104;
const int IOTConstants::MSG_SET_AIRCON_RUNMODE_RESULT = 105;
const int IOTConstants::MSG_GET_AIRCON_STATUS_FAIL = 106;
const int IOTConstants::MSG_GET_AIRCON_ONLINE_RESULT = 107;
const int IOTConstants::MSG_AIRCON_INIT_ERROR = 108;
const int IOTConstants::MSG_GET_WEATHER_FAIL = 109;
const int IOTConstants::MSG_GET_WEATHER_SUCCESS = 110;
const int IOTConstants::MSG_REFRESH_LIST_DATA = 111;
const int IOTConstants::MSG_GET_AIRCON_INDOOR_TEMPRATURE_RESULT = 112;
const int IOTConstants::MSG_GET_ALL_STATUS_ERROR = 113;
const int IOTConstants::MSG_INIT_APK_UPDATE = 114;
const int IOTConstants::MSG_INIT_APK_UPDATE_COMPLETED = 115;
const int IOTConstants::MSG_GET_APPLIANCE_IP_RESULT = 116;
const int IOTConstants::MSG_SWITCH_APPLIANCE_TO_SERVER = 117;
const int IOTConstants::MSG_SEND_UDP_CMD = 118;
const int IOTConstants::MSG_RECEIVE_UDP_CMD = 119;
const int IOTConstants::MSG_CLEAR_WIFI_CONFIG_PARS = 120;
const int IOTConstants::MSG_USER_OPEN_WIFI = 121;
const int IOTConstants::MSG_SWITCH_AIRCON = 122;
const int IOTConstants::MSG_SWITCH_AIRCON_FAIL = 123;
const int IOTConstants::MSG_LISTVIEW_SET_TURE = 124;
const int IOTConstants::MSG_LISTVIEW_SET_FALSE = 125;
const int IOTConstants::MSG_GET_APPLIANCE_STATUS = 126;
const int IOTConstants::MSG_GET_APPLIANCE_STAT = 127;
const int IOTConstants::MSG_GET_APPLIANCE_RESULT = 128;
	
const int IOTConstants::MSG_UDP_BINDER_SMARTBOX = 130;
const int IOTConstants::MSG_UDP_BINDER_SA_TO_SMARTBOX = 131;
	
const int IOTConstants::MSG_START_EXPERTMODE = 10;
const int IOTConstants::MSG_STOP_EXPERTMODE = 11;
	
const string IOTConstants::CHECKBOX_MSG = "CheckBox_msg";
const string IOTConstants::APPLIANCE_OFF_LINE_ERROR = "NOSA";
const string IOTConstants::APPLIANCE_UPGRADE_ERROR = "UPGRADE";
const string IOTConstants::UNKNOW_PHOTOS_URL = "UNKNOW_PHOTOS";
const int IOTConstants::SWITCH_TO_ONLINE_STATUS_TYPE_LAN = 0;
const int IOTConstants::SWITCH_TO_ONLINE_STATUS_TYPE_DOMAIN = 1;
const int IOTConstants::Disable_local = 1;

const string IOTConstants::SA_SOCKET_SERVER_PORT = "8899";
const string IOTConstants::PHONE_SOCKET_SERVER_PORT = "9988";

const int IOTConstants::SENT_TO_CND = 0;
const int IOTConstants::SENT_TO_SA = 1;
const int IOTConstants::SENT_TO_PHONE = 2;

const int IOTConstants::CONNECT_TO_CND = 0;
const int IOTConstants::CONNECT_TO_SMARTBOX = 1;
const int IOTConstants::CONNECT_TO_SA = 2;

const int IOTConstants::SA_SOCKET_CONNECT_ERROR = 0;
const int IOTConstants::SA_SOCKET_READ_TIMEOUT = 1;
const int IOTConstants::PHONE_SOCKET_CONNECT_ERROR = 2;
const int IOTConstants::PHONE_SOCKET_READ_TIMEOUT = 3;
const int IOTConstants::CDN_SOCKET_CONNECT_ERROR = 4;
const int IOTConstants::CDN_SOCKET_READ_TIMEOUT = 5;

const int IOTConstants::AIRCON_TYPE = 0x01;
const int IOTConstants::DEHUMIDIFIER_TYPE = 0x15;
const int IOTConstants::PURIFY_TYPE = 0x18;
const int IOTConstants::HOTFAN_TYPE = 0x19;

const string IOTConstants::SA_AIRCON_TYPE = "aircon";
const string IOTConstants::SA_DEHUMIDIFIER_TYPE = "dehumidifier";
const string IOTConstants::SA_PURIFY_TYPE = "purify";
const string IOTConstants::SA_HOTFAN_TYPE = "hotfan";
const string IOTConstants::BOOLEAN_TRUE = "1";
const string IOTConstants::BOOLEAN_FALSE = "0";
const string IOTConstants::CMD_TO_BOX = "AT+SBOX";
const string IOTConstants::CMD_TO_KTSBOX = "AT+KTSBOX";
const string IOTConstants::CMD_TO_BOX_GETALLSTATUS = "AT+SBOXSQ";
const string IOTConstants::CMD_TO_BOX_SETSMARTMODE = "AT+SBOXSSM";
const string IOTConstants::CMD_TO_BOX_SETMUTESWTICH = "AT+SBOXSMM";
const string IOTConstants::CMD_TO_BOX_SETPOWERSTATU = "AT+SBOXSPM";
const string IOTConstants::CMD_TO_BOX_SETTYPE = "AT+SBOXNTM";
const string IOTConstants::CMD_TO_BOX_CONFIGBOX = "AT+SBOXCONFIG";
const string IOTConstants::CMD_TO_BOX_SCENETEST_IN = "AT+SBOXSTI";
const string IOTConstants::CMD_TO_BOX_SCENETEST_OUT = "AT+SBOXSTO";
const string IOTConstants::CMD_TO_BOX_PRODUCT_TEST = "AT+SBOXPT";
const string IOTConstants::CMD_TO_BOX_UNBINDER = "AT+SBOXUNB";
const string IOTConstants::CMD_TO_BOX_SA_UNBINDER = "AT+SBOXSAUNB";
const string IOTConstants::CMD_TO_BOX_UPDATE_DIYCURVE = "AT+SBOXUDC";
const string IOTConstants::CMD_TO_BOX_ENTER_DEMO_MODE = "AT+SBOXEDM";
const string IOTConstants::CMD_TO_BOX_SET_SEASON = "AT+SBOXSES";
const string IOTConstants::CMD_TO_BOX_NOTIFYSMARTMODEJOIN= "AT+SBOXNBS";
const string IOTConstants::CMD_TO_BOX_BINDSASUCCEED= "AT+SBOXBSAS";

const string IOTConstants::BOX_RETURN_GETALLSTATUS = "+SBOXSQ:";
const string IOTConstants::BOX_RETURN_SETSMARTMODE = "+SBOXSSM:";
const string IOTConstants::BOX_RETURN_SETMUTESWTICH = "+SBOXSMM:";
const string IOTConstants::BOX_RETURN_SETPOWERSTATU = "+SBOXSPM:";
const string IOTConstants::BOX_RETURN_SETTYPE = "+SBOXNTM:";
const string IOTConstants::BOX_RETURN_CONFIGBOX = "+SBOXCONFIG:";
const string IOTConstants::BOX_RETURN_SCENETEST_IN = "+SBOXSTI:";
const string IOTConstants::BOX_RETURN_SCENETEST_OUT = "+SBOXSTO:";
const string IOTConstants::BOX_RETURN_PRODUCT_TEST = "+SBOXPT:";
const string IOTConstants::BOX_RETURN_SCENETEST = "+SBOXST:";
const string IOTConstants::BOX_RETURN_UNBINDER = "+SBOXUNB:";
const string IOTConstants::BOX_RETURN_SA_UNBINDER = "+SBOXSAUNB:";
const string IOTConstants::BOX_RETURN_UPDATE_DIYCURVE = "+SBOXUDC:";
const string IOTConstants::BOX_RETURN_ENTER_DEMO_MODE = "+SBOXEDM:";
const string IOTConstants::BOX_RETURN_SET_SEASON = "+SBOXSES:";
const string IOTConstants::CMD_TO_MOBILE_NOTIFYSMARTMODEQUIT = "+SBOXNQS:";
const string IOTConstants::BOX_RETURN_BINDSASUCCEED = "+SBOXBSAS:";

const string IOTConstants::NOSA_SA_MODE = "nosa";
const string IOTConstants::CONTROLLABLE_SA_MODE = "controllable";
const string IOTConstants::UNCONTROLLABLE_SA_MODE = "uncontrollable";

const string IOTConstants::STANDARD_SMART_MODE = "Normal";
const string IOTConstants::CHILDREN_SMART_MODE = "Child";
const string IOTConstants::ELDER_SMART_MODE = "Old";
const string IOTConstants::OFF_SMART_MODE = "Off";

const string IOTConstants::AIR_QUALITY_GOOD = "AIR_QUALITY_GOOD" ;
const string IOTConstants::AIR_QUALITY_GENERAL = "AIR_QUALITY_GENERAL" ;
const string IOTConstants::AIR_QUALITY_BAD = "AIR_QUALITY_BAD" ;

const string IOTConstants::AIR_COMFORT_GOOD = "AIR_COMFORT_GOOD" ;
const string IOTConstants::AIR_COMFORT_GENERAL = "AIR_COMFORT_GENERAL" ;
const string IOTConstants::AIR_COMFORT_BAD = "AIR_COMFORT_BAD" ;

/*aircon*/
const string IOTConstants::AIRCONDITION_MODE_HEAT = "heat";
const string IOTConstants::AIRCONDITION_MODE_COOL = "cool";
const string IOTConstants::AIRCONDITION_MODE_DEHUMIDIFY = "dehumidify";
const string IOTConstants::AIRCONDITION_MODE_BLOW = "blow";
const string IOTConstants::AIRCONDITION_MODE_AUTO = "auto";
const string IOTConstants::AIRCONDITION_WIND_STRONG = "strong";
const string IOTConstants::AIRCONDITION_WIND_MIDDLE = "middle";
const string IOTConstants::AIRCONDITION_WIND_WEAK = "weak";
const string IOTConstants::AIRCONDITION_WIND_AUTO = "auto";
const string IOTConstants::AIRCONDITION_WIND_MUTE = "mute";
//aircon body check
//OutDoor
const string IOTConstants:: AIRCONDITION_BODY_CHECK_OutdoorEEPROMTrouble = "1";
const string IOTConstants::AIRCONDITION_BODY_CHECK_OutdoorPipeTemperatureSensorTrouble = "2";
const string IOTConstants::AIRCONDITION_BODY_CHECK_OutdoorExhausTemperatureSensorTrouble = "3";
const string IOTConstants::AIRCONDITION_BODY_CHECK_OutdoorEnvironmentTemperatureSensorTrouble = "4";
const string IOTConstants::AIRCONDITION_BODY_CHECK_OutdoorControlBoardTrouble = "5";
const string IOTConstants::AIRCONDITION_BODY_CHECK_AlternatingCurrentOvervoltageProtect = "6";
const string IOTConstants::AIRCONDITION_BODY_CHECK_AlternatingCurrentUndervoltageProtect = "7";
const string IOTConstants::AIRCONDITION_BODY_CHECK_OutdooEnvironmentOvertemperatureProtect = "8";
const string IOTConstants::AIRCONDITION_BODY_CHECK_OutdoorMachineTrouble  = "9";
const string IOTConstants::AIRCONDITION_BODY_CHECK_OutdoorBoardOrCompressorTrouble = "10";
//InDoor
const string IOTConstants::AIRCONDITION_BODY_CHECK_IndoorTemperatureSensorTrouble = "11";
const string IOTConstants::AIRCONDITION_BODY_CHECK_IndoorPipeTemperatureSensorTrouble = "12";
const string IOTConstants::AIRCONDITION_BODY_CHECK_IndoorHumiditySensorTrouble = "13";
const string IOTConstants::AIRCONDITION_BODY_CHECK_IndoorFanMotorTrouble = "14";
const string IOTConstants::AIRCONDITION_BODY_CHECK_PioneerGrillingProtectTrouble = "15";
const string IOTConstants::AIRCONDITION_BODY_CHECK_IndoorVoltageZeroCrossDetectionTrouble = "16";
const string IOTConstants::AIRCONDITION_BODY_CHECK_IndoorOutdoorCommunicationTrouble = "17";
const string IOTConstants::AIRCONDITION_BODY_CHECK_IndoorContrlScreenCommunicationTrouble = "18";
const string IOTConstants::AIRCONDITION_BODY_CHECK_IndoorContrlKeypadCommunicationTrouble = "19";
const string IOTConstants::AIRCONDITION_BODY_CHECK_IndoorContrlWIFICommunicationTrouble = "20";
const string IOTConstants::AIRCONDITION_BODY_CHECK_IndoorContrlChargeCommunicationTrouble = "21";
const string IOTConstants::AIRCONDITION_BODY_CHECK_IndoorContrlEEPROMTrouble = "22";
//Not Show
const string IOTConstants::AIRCONDITION_BODY_CHECK_OutdoorCoilOverloadUpFrequency = "23";
const string IOTConstants::AIRCONDITION_BODY_CHECK_OutdoorCoilOverloadDownFrequency = "24";
const string IOTConstants::AIRCONDITION_BODY_CHECK_IndoorCoilOverloadUpFrequency = "25";
const string IOTConstants::AIRCONDITION_BODY_CHECK_IndoorCoilOverloadDownFrequency = "26";
const string IOTConstants::AIRCONDITION_BODY_CHECK_PressureUpFrequency = "27";
const string IOTConstants::AIRCONDITION_BODY_CHECK_PressureDownFrequency = "28";
const string IOTConstants::AIRCONDITION_BODY_CHECK_IndoorCoilFreezingUpFrequency = "29";
const string IOTConstants::AIRCONDITION_BODY_CHECK_IndoorCoilFreezingDownFrequency = "30";
const string IOTConstants::AIRCONDITION_BODY_CHECK_CommunicationDownFrequency = "31";
const string IOTConstants::AIRCONDITION_BODY_CHECK_ModuleTemperaturelimitFrequency = "32";
const string IOTConstants::AIRCONDITION_BODY_CHECK_ModulationRatelimitFrequency = "33";
const string IOTConstants::AIRCONDITION_BODY_CHECK_PhaseCurrentlimitFrequency = "34";
const string IOTConstants::AIRCONDITION_BODY_CHECK_PowerSaveUpFrequency = "35";
const string IOTConstants::AIRCONDITION_BODY_CHECK_PowerSaveDownFrequency = "36";
const string IOTConstants::AIRCONDITION_BODY_CHECK_OvercurrentUpFrequency = "37";
const string IOTConstants::AIRCONDITION_BODY_CHECK_OvercurrentDownFrequency = "38";

/* aircleaner*/
const string IOTConstants::AIRCLEANER_MODE_CLEARDUST = "cleardust";
const string IOTConstants::AIRCLEANER_MODE_CLEARSMELL = "clearsmell";
const string IOTConstants::AIRCLEANER_MODE_SMART = "smart";
const string IOTConstants::AIRCLEANER_MODE_MUTE= "mute";
const string IOTConstants::AIRCLEANER_MODE_SLEEP = "sleep";
const string IOTConstants::AIRCLEANER_WIND_STRONG = "strong";
const string IOTConstants::AIRCLEANER_WIND_MIDDLE = "middle";
const string IOTConstants::AIRCLEANER_WIND_WEAK = "weak";
const string IOTConstants::AIRCLEANER_WIND_AUTO = "auto";
const string IOTConstants::AIRCLEANER_WIND_CLEAR = "clear";
//aircleaner body check
const string IOTConstants:: AIRCLEANER_BODY_CHECK_MotorError = "1";
const string IOTConstants::AIRCLEANER_BODY_CHECK_LeanError = "2";
const string IOTConstants::AIRCLEANER_BODY_CHECK_ChangeFilter = "3";
const string IOTConstants::AIRCLEANER_BODY_CHECK_HumidityWheelError = "4";
const string IOTConstants::AIRCLEANER_BODY_CHECK_WaterSinkEmptyError = "5";
const string IOTConstants::AIRCLEANER_BODY_CHECK_WaterSinkNotSetup = "6";
const string IOTConstants::AIRCLEANER_BODY_CHECK_HumiditySensorError = "7";
const string IOTConstants::AIRCLEANER_BODY_CHECK_DustSensor = "8";
const string IOTConstants::AIRCLEANER_BODY_CHECK_SmellSensor = "9";

/* dehumidifier*/
const string IOTConstants::DEHUMIDIFIER_MODE_CONTINUE = "continue";
const string IOTConstants::DEHUMIDIFIER_MODE_NORMAL = "normal";
const string IOTConstants::DEHUMIDIFIER_MODE_AUTO = "auto";
const string IOTConstants::DEHUMIDIFIER_MODE_HEAT  = "heat";
const string IOTConstants::DEHUMIDIFIER_WIND_STRONG = "strong";
const string IOTConstants::DEHUMIDIFIER_WIND_WEAK = "weak";
const string IOTConstants::DEHUMIDIFIER_WIND_AUTO = "auto";
//dehumidifier body check
const string IOTConstants:: DEHUMIDIFIER_BODY_CHECK_FilterNetCleanWarning = "1";
const string IOTConstants::  DEHUMIDIFIER_BODY_CHECK_HumidSensorError = "2";
const string IOTConstants::DEHUMIDIFIER_BODY_CHECK_PumpTempratureError = "3";
const string IOTConstants::DEHUMIDIFIER_BODY_CHECK_IndoorTempratureError = "4";
const string IOTConstants::DEHUMIDIFIER_BODY_CHECK_WaterPumpWarning = "5";
const string IOTConstants::DEHUMIDIFIER_BODY_CHECK_WaterFullWarning = "6";

/*hotfan*/
const string IOTConstants::HOTFAN_MODE_FULLHEAT = "fullheat";
const string IOTConstants::HOTFAN_MODE_DIRECT = "direct";
const string IOTConstants::HOTFAN_MODE_INDOOR = "indoor";
const string IOTConstants::HOTFAN_MODE_AUTO = "auto";
const string IOTConstants::HOTFAN_WIND_STRONG = "strong";
const string IOTConstants::HOTFAN_WIND_MIDDLE = "middle";
const string IOTConstants::HOTFAN_WIND_WEAK = "weak";
const string IOTConstants::HOTFAN_WIND_AUTO = "auto";

const string IOTConstants::BATTERY_STATUS_UNKNOWN = "unknown";
const string IOTConstants::BATTERY_STATUS_CHARGING = "charging";
const string IOTConstants::BATTERY_STATUS_DISCHARGING = "discharg";
const string IOTConstants::BATTERY_STATUS_FULL = "full";

const string IOTConstants::BRODCAST_REFRESH_UI = "com.android.smartbox.REFRESH_UI_BROADCAST";
const string IOTConstants::BRODCAST_CHANGE_SMARTMODE = "com.android.smartbox.CHANGE_SMARTMODE_BROADCAST";
const string IOTConstants::BRODCAST_REFRESH_SMARTMODE = "com.android.smartbox.REFRESH_SMARTMODE_BROADCAST";
const string IOTConstants::BRODCAST_SMARTBOX_UPDATE_DIYCURVE  = "com.android.smartbox.UPDATE_DIYCURVE_BROADCAST";

const string IOTConstants::BRODCAST_SMARTBOX_MUTE_STOP = "com.android.smartbox.MUTE_STOP_BROADCAST";
const string IOTConstants::BRODCAST_SMARTBOX_MUTE_START = "com.android.smartbox.MUTE_START_BROADCAST";
const string IOTConstants::BRODCAST_SMARTBOX_POWER_STOP = "com.android.smartbox.POWER_STOP_BROADCAST";
const string IOTConstants::BRODCAST_SMARTBOX_POWER_START = "com.android.smartbox.POWER_START_BROADCAST";
const string IOTConstants::BRODCAST_SMARTBOX_UPDATE_SAINFO = "com.android.smartbox.UPDATE_SAINFO_BROADCAST";
	
	
	/*WIFI ״̬*/
const string IOTConstants::WIFI_STATUS_UNKNOWN = "unknown";
const string IOTConstants::WIFI_STATUS_CONNECTED = "connected";
const string IOTConstants::WIFI_STATUS_CONNECTING = "connecting";
const string IOTConstants::WIFI_STATUS_UNCONNECT = "unconnected";
const string IOTConstants::WIFI_STATUS_AP = "ap";