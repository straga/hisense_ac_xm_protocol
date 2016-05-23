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
	string resultStr = devWrapper.parseResult(deviceId,data);
	jsonRet.putString(RESULT_KEY,"OVENSET");
	jsonRet.putString(RESULT_KEY,"SUCCEED");
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
	case T_SEED_MACHINE:
		deviceCmd = handleSeedCmd(deviceId,jsonCmd);
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
	else if(funcStr == "getOvenStatuRunTime"){
		//»ñÈ¡ºæ¿¾Ê±¼ä
		versionStr = devWrapper.getOvenStatuRunTime(deviceId);
	}
	else if(funcStr == "getOvenStatuNowTemp"){
		//»ñÈ¡ºæ±ºÎÂ¶È
		versionStr = devWrapper.getOvenStatuNowTemperature(deviceId);
	}
	else if(funcStr == "getOvenStatuYR"){
		//»ñÈ¡Ô¤ÈÈ×´Ì¬
		versionStr = devWrapper.getOvenStatuYR(deviceId);
	}
	else if(funcStr == "getOvenUid"){
		//»ñÈ¡¿¾Ïäuid
		versionStr = devWrapper.getOvenUid(deviceId);
	}
	else if(funcStr == "getOvenStatuMenuNub"){
		//»ñÈ¡ÕýÔÚºæ±ºµÄÇúÏß
		versionStr = devWrapper.getOvenStatuMenuNub(deviceId);
	}
	else if(funcStr == "getOvenStatuKJ"){
		//»ñÈ¡¿¾Ïä¿ª¹Ø×´Ì¬
		versionStr = devWrapper.getOvenStatuKJ(deviceId);
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
	

	if(func == ""){
		return jsonRet.putString(RESULT_KEY,"cmd not found").toString();
	}
	
	manual = jsCmdObj.getNumber(SOUND_KEY) == 1 ? : 0;
	flag = (jsCmdObj.getNumber(FLAG_KEY)==1) ? 1:2;
	

	if("setOvenPowerOn" == func){
		return devWrapper.setOvenPowerOn(deviceId,1,manual,flag);
		
	}else if("setOvenPowerOff" == func){
		return devWrapper.setOvenPowerOff(deviceId,0,manual,flag);
		
	}else if("getOvenSoftVer" == func){
		//²éÑ¯£¨¹Ì¼þ£©°æ±¾ºÅ
		return devWrapper.sendQueryVersion(deviceId,flag);
		
	}else if("setOvenFS" == func){
		//·ç»ú¿ª¹Ø
		uid = jsCmdObj.getNumber("UID");
		int set = jsCmdObj.getNumber("FanPower");
		cout<<"UID :"<<uid<<",set:"<<set<<endl;
		return devWrapper.setOvenFS(deviceId,uid,set,manual,flag);
		
	}else if("setOvenZC" == func){
		//×ª²æ¿ª¹Ø
		uid = jsCmdObj.getNumber("UID");
		int RotaryFork = jsCmdObj.getNumber("RotaryFork");
		cout<<"UID :"<<uid<<",RotaryFork:"<<RotaryFork<<endl;
		return devWrapper.setOvenZC(deviceId, uid, RotaryFork, manual,flag);
		
	}else if("setOvenUDTubeTemp" == func){
		//ÉÏ¡¢ÖÐ¡¢ÏÂ¹ÜÎÂ¶ÈÉèÖÃ
		uid = jsCmdObj.getNumber("UID");
		int UpTemp = jsCmdObj.getNumber("UpTemp");
		int MidTemp = jsCmdObj.getNumber("MidTemp");
		int DownTemp = jsCmdObj.getNumber("DownTemp");
		
		cout<<"UID :"<<uid<<",UpTemp:"<<UpTemp<<",MidTemp:"<<MidTemp<<",DownTemp:"<<DownTemp<<endl;
		return devWrapper.setOvenUDTubeTemperature(deviceId,uid,UpTemp,MidTemp,DownTemp,manual,flag);
	}else if("getOvenStatus" == func){
		//×´Ì¬²éÑ¯
		return devWrapper.getOvenStatus(deviceId, manual,flag);

	}else if("getOvenGN" == func){
		//¹¦ÄÜ²éÑ¯
		return devWrapper.getOvenGN(deviceId, manual,flag);
		
	}else if("setOvenMenuName" == func){
		//ÉèÖÃ²Ëµ¥Ãû×Ö
		uid = jsCmdObj.getNumber("UID");
		int menuNub = jsCmdObj.getNumber("MenuIdx");
		int sub_node = jsCmdObj.getNumber("CurveNum");
		int time = jsCmdObj.getNumber("AllTime");
		string name = jsCmdObj.getString("MenuName");
			
		cout<<"UID :"<<uid<<",menuNub:"<<menuNub<<",sub_node:"<<sub_node<<",time:"<<time<<",name:"<<name<<endl;
		return devWrapper.setOvenMenuName(deviceId,uid,menuNub,sub_node,time,name,manual,flag);
		
	}else if("setOvenMenuTempExt" == func){
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
	
	}else if("OvenExcuteCurve" == func){
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
		
	}else if("getOvenMenuTempExt" == func){
		//»ñÈ¡ÎÂ¶ÈÇúÏßÀ©Õ¹ÃüÁî
		uid = jsCmdObj.getNumber("UID");
		int menuNub = jsCmdObj.getNumber("MenuIdx");
		int sub_node = jsCmdObj.getNumber("CurveIdx");
		int FrameNo = jsCmdObj.getNumber("FrameNo");
		
		cout<<"UID :"<<uid<<",menuNub:"<<menuNub<<endl;
		return devWrapper.setOvenMenuTemperatureExtend(deviceId,menuNub,sub_node,FrameNo,manual,flag);

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
		return jsonRet.putString(RESULT_KEY,"cmd not support\r\n").toString();
	}
	return "";
}


string DeviceInterface::handleSeedCmd(const string &deviceId,const string &jsonCmd)
{
	string cmdVersion,func,reusltStr;
	int manual,flag=0;
	JSONObject jsCmdObj(jsonCmd);
	JSONObject jsonRet;
	
	func = jsCmdObj.getString(FUNC_KEY);
	

	if(func == ""){
		return jsonRet.putString(RESULT_KEY,"cmd not found\r\n").toString();
	}
	
	manual = jsCmdObj.getNumber(SOUND_KEY) == 1 ? : 0;
	flag = (jsCmdObj.getNumber(FLAG_KEY)==1) ? 1:2;
	

	if("setSeedPower" == func){
		//¿ª¹Ø»ú
		int set = jsCmdObj.getNumber("Power");

		return devWrapper.setSeedMachinePower(deviceId,set,flag);
		
	}else if("setSeedLightTimer" == func){
		//ÊµÊ±¶¨Ê±
		int curhour = jsCmdObj.getNumber("RTSetHour");
		int curmin = jsCmdObj.getNumber("RTSetMins");
		int set = jsCmdObj.getNumber("TimingSet");
		int onOroff = jsCmdObj.getNumber("LTiming");
		int hour = jsCmdObj.getNumber("TimingH");
		int min = jsCmdObj.getNumber("TimingM");
		int lights = jsCmdObj.getNumber("LightNUM");
		

		return devWrapper.setSeedMachineLightTimer(deviceId,curhour,curmin,set,
			onOroff,hour,min,lights,flag);
		
	}else if("disMissWarn" == func){
		//¹Ø±Õ±¨¾¯
		int num = jsCmdObj.getNumber("CancelWarning");
		int level=0,pump=0,nutrition=0;
		
		if(num&0x1)
			nutrition=1;
		if(num&0x2)
			pump=1;
		if(num&0x4)
			level=1;
		
		return devWrapper.setSeedMachineDismissWarning(deviceId,level,pump,nutrition,flag);
		
	}else if("setSeedLight" == func){
		//ÉèÖÃµÆ¿ª¹Ø
		int set = jsCmdObj.getNumber("Light");
		
		return devWrapper.setSeedMachineLight(deviceId,set,flag);

	}else if("setSeedAnion" == func){
		//ÉèÖÃ¸ºÀë×Ó¿ª¹Ø
		int set = jsCmdObj.getNumber("Anion");
		
		return devWrapper.setSeedMachineAnion(deviceId,set,flag);
	
	}else if("setSeedMusic" == func){
		//ÉèÖÃÒôÀÖ¿ª¹Ø
		int set = jsCmdObj.getNumber("Music");
		
		return devWrapper.setSeedMachineMusic(deviceId,set,flag);
		
	}else if("setSeedVolume" == func){
		//ÒôÁ¿¿ØÖÆ
		int set = jsCmdObj.getNumber("Volume");
		
		return devWrapper.setSeedMachineVolume(deviceId,set,flag);
			
	}else if("setSeedPm25" == func){
		//ÉèÖÃPM2.5¿ª¹Ø
		int set = jsCmdObj.getNumber("SetPm25");
		
		return devWrapper.setSeedMachinePm25(deviceId,set,flag);
									
	}else{
		return jsonRet.putString(RESULT_KEY,"cmd not support\r\n").toString();
	}
	return "";
}


