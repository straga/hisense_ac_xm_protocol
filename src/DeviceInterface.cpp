#include "DeviceInterface.h"
#include "JSONObject.h"


string DeviceInterface::getInterfaceVersion()
{
	return INTERFACE_VERSION;
}
DeviceInterface* DeviceInterface::getInstance()
{
	if(instance == NULL)
		instance = new DeviceInterface();
	return instance;
}

int DeviceInterface::device_init(const string &deviceId, int type)
{
	return devWrapper.initDevicesControl(deviceId,type);
}
void DeviceInterface::device_delete(const string &deviceId)
{
	devWrapper.delDevicesControl(deviceId);
	cout<<deviceId<<endl;
}

DeviceInterface* DeviceInterface::instance = NULL;

DeviceInterface::~DeviceInterface()
{
	// Do nothing ...
}

string DeviceInterface::device_parse(const string &deviceId, const string &data)
{
	JSONObject jsonRet;
	return devWrapper.parseResult(deviceId,data);
	#if 0
	jsonRet.putString(RESULT_KEY,"OVENSET");
	jsonRet.putString(RESULT_KEY,"SUCCEED");
	#endif
	return jsonRet.toString();
}


string DeviceInterface::device_set(const string &deviceId,const string &jsonCmd)
{

	int deviceType = devWrapper.getDeviceType(deviceId);
	string deviceCmd = "";
//	cout <<deviceType<<endl;
	switch(deviceType){
	case T_AIRCONDITIONER:
		return "{Not support}";
	case T_OVEN:
		deviceCmd = handleOvenCmd(deviceId,jsonCmd);
	break;
	default:
		deviceCmd = "{Not support}";
	}
	return deviceCmd;
}

string DeviceInterface::device_get(const string &deviceId,const string &jsonCmd)
{
	JSONObject jsCmdObj(jsonCmd);
	JSONObject jsonRet;
	string versionStr;
	string funcStr = jsCmdObj.getString(FUNC_KEY);
	if(funcStr == "")
		return jsonRet.putString(VALUE_KEY,"function key not found").toString();
	if(funcStr == "getDeveiceVersion"){
		versionStr = devWrapper.getAirconHaveIRContrl(deviceId);
	}
	jsonRet.putString(VALUE_KEY,versionStr);
	return jsonRet.toString();
}

string DeviceInterface::handleOvenCmd(const string &deviceId,const string &jsonCmd)
{
//	cout <<"handleOvenCmd :"<<endl;

	string cmdVersion,func,reusltStr;
	int manual,flag=0;
	JSONObject jsCmdObj(jsonCmd);
	JSONObject jsonRet;
	unsigned uid;
	func = jsCmdObj.getString(FUNC_KEY);
	
	cout <<FUNC_KEY<<"is:"<<func<<endl;
	if(func == ""){
		return jsonRet.putString(RESULT_KEY,"cmd not found").toString();
	}
	
	// flag = jsCmdObj.getNumber(FLAG_KEY);
	manual = jsCmdObj.getNumber(SOUND_KEY) == 1 ? : 0;
	flag = (jsCmdObj.getNumber(FLAG_KEY)==1) ? 1:2;
	
	cout <<SOUND_KEY <<manual<<endl;
	if("setOvenPowerOn" == func){
		//return devWrapper.setOvenPowerOn(deviceId,1,manual);
		return devWrapper.setOvenPowerOn(deviceId,1,manual,flag);
		
	}else if("setOvenPowerOff" == func){
		//return devWrapper.setOvenPowerOn(deviceId,0,manual);
		return devWrapper.setOvenPowerOff(deviceId,0,manual,flag);
		
	}else if("setOvenFS" == func){
		//·ç»ú¿ª¹Ø
		uid = jsCmdObj.getNumber("UID");
		int set = jsCmdObj.getNumber("FanPower");
		cout<<"UID :"<<uid<<",set:"<<set<<endl;
		return devWrapper.setOvenFS(deviceId,uid,set,manual,flag);
		
	}else if("setOvenMenuName" == func){
		//ÉèÖÃ²Ëµ¥Ãû×Ö
		uid = jsCmdObj.getNumber("UID");
		int menuNub = jsCmdObj.getNumber("MenuIdx");
		int sub_node = jsCmdObj.getNumber("CurveNum");
		int time = jsCmdObj.getNumber("AllTime");
		string name = jsCmdObj.getString("MenuName");
			
		cout<<"UID :"<<uid<<",menuNub:"<<menuNub<<",sub_node:"<<sub_node<<",time:"<<time<<",name:"<<name<<endl;
		return devWrapper.setOvenMenuName(deviceId,uid,menuNub,sub_node,time,name,manual,flag);
		
	}else if("setOvenFS" == func){
		//ÉèÖÃ²Ëµ¥ÎÂ¶ÈÃüÁîÀ©Õ¹
		uid = jsCmdObj.getNumber("UID");
		int menuNub = jsCmdObj.getNumber("MenuIdx");
		int sub_node = jsCmdObj.getNumber("CurveIdx");

		int time = jsCmdObj.getNumber("AllTime");
		int UpTemp = jsCmdObj.getNumber("UpTemp");
		int MidTemp = jsCmdObj.getNumber("MidTemp");

		int DownTemp = jsCmdObj.getNumber("DownTemp");
		int RotaryFork = jsCmdObj.getNumber("RotaryFork");
		int FanPower = jsCmdObj.getNumber("FanPower");

		int ReSuspend = jsCmdObj.getNumber("ReSuspend");
		int AllTime_valid = jsCmdObj.getNumber("AllTime_valid");
		int UpTemp_valid = jsCmdObj.getNumber("UpTemp_valid");

		int MidTemp_valid = jsCmdObj.getNumber("MidTemp_valid");
		int DownTemp_valid = jsCmdObj.getNumber("DownTemp_valid");
		int RotaryFork_valid = jsCmdObj.getNumber("RotaryFork_valid");

		int FanPower_valid = jsCmdObj.getNumber("FanPower_valid");
		int ReSuspend_valid = jsCmdObj.getNumber("ReSuspend_valid");
		int FrameNo = jsCmdObj.getNumber("FrameNo");
		
		cout<<"UID :"<<uid<<",menuNub:"<<menuNub<<",sub_node:"<<sub_node<<endl;
		cout<<"time :"<<time<<",UpTemp:"<<UpTemp<<",MidTemp:"<<MidTemp<<endl;
		cout<<"DownTemp :"<<DownTemp<<",RotaryFork:"<<RotaryFork<<",FanPower:"<<FanPower<<endl;
		cout<<"ReSuspend:"<<ReSuspend<<",AllTime_valid:"<<AllTime_valid<<",UpTemp_valid:"<<UpTemp_valid<<endl;
		cout<<"MidTemp_valid :"<<MidTemp_valid<<",DownTemp_valid:"<<DownTemp_valid<<",RotaryFork_valid:"<<RotaryFork_valid<<endl;
		cout<<"FanPower_valid:"<<FanPower_valid<<",ReSuspend_valid:"<<ReSuspend_valid<<",FrameNo:"<<FrameNo<<endl;
		return devWrapper.setOvenMenuTemperatureExtend(
			deviceId, uid, menuNub, sub_node, 
			time, UpTemp, MidTemp, DownTemp, 
			RotaryFork, FanPower, ReSuspend, AllTime_valid, 
			UpTemp_valid, MidTemp_valid, 
			DownTemp_valid, RotaryFork_valid, 
			FanPower_valid, ReSuspend_valid, 
			FrameNo, manual,flag);
	
	}else if("OvenCheckCurve" == func){
		//ÇúÏßÍêÕûÐÔ¼ì²é
		uid = jsCmdObj.getNumber("UID");
		int menuNub = jsCmdObj.getNumber("MenuIdx");
		
		cout<<"UID :"<<uid<<",menuNub:"<<menuNub<<endl;
		return devWrapper.setOvenCheckCurveIntegrity(deviceId,uid,menuNub,manual,flag);
	
	}else if("setOvenFS" == func){
		//Ô¤ÈÈ¿¾Ïä,ÇúÏßÖ´ÐÐÃüÁî
		uid = jsCmdObj.getNumber("UID");
		int menuNub = jsCmdObj.getNumber("MenuIdx");
		
		cout<<"UID :"<<uid<<",menuNub:"<<menuNub<<endl;
		return devWrapper.setOvenExcuteCurveCmd(deviceId,uid,menuNub,manual,flag);
	
	}else if("setOvenD" == func){
		//ºæ±ºÊ±Ç¿ÖÆ¿ªµÆ,Â¯µÆ¿ª¹Ø
		uid = jsCmdObj.getNumber("UID");
		int LampSet = jsCmdObj.getNumber("LampSet");
		
		cout<<"UID :"<<uid<<",LampSet:"<<LampSet<<endl;
		return devWrapper.setOvenD(deviceId,uid,LampSet,manual,flag);

	}else if("OvenPOrCCurve" == func){
		//ÇúÏßÔÝÍ£
		uid = jsCmdObj.getNumber("UID");
		int menuNub = jsCmdObj.getNumber("MenuIdx");
		
		cout<<"UID :"<<uid<<",menuNub:"<<menuNub<<endl;
		return devWrapper.setOvenCancelExcuteCurveCmd(deviceId,uid,menuNub,manual,flag);
	
	}else if("OvenCancelExcuteCurve" == func){
		//ÇúÏßÈ¡ÏûÖ´ÐÐÃüÁî
		uid = jsCmdObj.getNumber("UID");
		int menuNub = jsCmdObj.getNumber("MenuIdx");
		
		cout<<"UID :"<<uid<<",menuNub:"<<menuNub<<endl;
		return devWrapper.setOvenCancelExcuteCurveCmd(deviceId,uid, menuNub ,manual,flag);
	
	}else if("getOvenMenuName" == func){
		//»ñÈ¡²Ëµ¥Ãû×Ö
		uid = jsCmdObj.getNumber("UID");
		int menuNub = jsCmdObj.getNumber("MenuIdx");
		
		cout<<"UID :"<<uid<<",menuNub:"<<menuNub<<endl;
		return devWrapper.setOvenMenuName(deviceId, menuNub,manual,flag);
	
	}else{
	//	return jsonRet.putString(RESULT_KEY,"cmd not support").toString();
	}
	return "";
}


