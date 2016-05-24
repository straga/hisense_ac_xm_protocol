#include <JSONObject.h>
#include <DeviceInterface.h>


#define TEST_JSONOBJ 0
#define TEST_SEED  0
#define TEST_OVEN  0
#define TEST_AC    1
int main(int argc,char **argv){
	
	DeviceInterface *devInterface = DeviceInterface::getInstance();
#if TEST_JSONOBJ
	JSONObject root("{\"Cmd\":\"ACSET\",\"value\":5}");
	cout<< "root"<<root.toString()<<endl;
	cout<<root.getNumber("value")<<" "<<root.getString("Cmd")<<endl;

	/*String 构造*/
	JSONObject root1(root.toString());
	cout<< root1.toString()<<endl;

	/*拷贝构造*/
	JSONObject root2(root1);
	cout<< root2.toString()<<endl;
	root2.putNumber("abc",60);
	root2.putString("keyi","hello");
	cout<< root2.toString()<<endl;

	cout<<root2.getNumber("value")<<" "<<root2.getString("Cmd")<<endl;

	/*赋值构造*/
	JSONObject root3 = root2;
	cout<<root3.toString()<<endl;
	root3 = root1;
	cout<<root3<<endl;
	root3.putString("HELLO","world");
	cout<<"==============================="<<endl;
	cout<<root3<<endl;
	root3="{}";
	cout<<root3<<endl;
#endif
	string deviceId = "ABC";
	string retResult = "F4F50140290100FE01270101006600010000000000FF0000000000000000001C0000001C000000000000000000000331F4FB";
	if(devInterface == NULL )
		return -1;
#if TEST_OVEN
	
	devInterface->device_init(deviceId,0x27);
//		cout<<devInterface->device_parse("ABC","12345")<<endl;
	cout<<devInterface->device_set(deviceId,"{\"ver\":\"1.0\",\"Func\":\"setOvenD\",\"LampSet\":1,\"UID\":12345,\"SoundSet\":1,\"Flag\":1}");
	cout<<devInterface->device_set(deviceId,"{\"Ver\":\"1.0\",\"Func\":\"setOvenPowerOn\",\"Cmd\": \"PowerOn\", \"SoundSet\": 1 , \"Flag\": 1}");
	cout<<devInterface->device_set(deviceId,"{\"Ver\" : \"1.0\" , \"Func\" : \"setOvenPowerOff\" , \"Cmd\" : \"PowerOff\" , \"SoundSet\" : 1 , \"Flag\" : 1}");
	
	cout<<devInterface->device_set(deviceId,"{\"Ver\" : \"1.0\" , \"Func\" : \"setOvenFS\" , \"Cmd\" : \"OvenSet\" , \"UID\" : 605031248, \"FanPower\" : 1, \"SoundSet\" : 1 , \"Flag\" : 1}");
	cout<<devInterface->device_set(deviceId,"{\"Ver\" : \"1.0\", \"Func\" : \"setOvenMenuName\" , \"Cmd\" : \"OVSMN\" , \"UID\" : 605031248, \"MenuIdx\" : 2 , \"CurveNum\" : 9 , \"AllTime\" : 300 , \"MenuName\" : \"XLF-OVEN-MENE-CAKE-1\" , \"SoundSet\" : 1 , \"Flag\" : 1}");
	cout<<devInterface->device_set(deviceId,"{\"Ver\" : \"1.0\", \"Func\" : \"setOvenMenuTempExt\" , \"Cmd\" : \"OVSMTEx\" , \"UID\" : 657895623 , \"MenuIdx\" : 0 , \"CurveIdx\" : 9 , \"AllTime\" : 300 , \"UpTemp\" : 100 , \"MidTemp\" : 120 , \"DownTemp\" : 105 , \"RotaryFork\" : 1 , \"FanPower\" : 1 , \"ReSuspend\" : 1 , \"AllTime_valid\" : 1 , \"UpTemp _valid\" : 1 , \"MidTemp _valid\" : 1 , \"DownTemp _valid\" : 1 , \"RotaryFork _valid\" : 1 , \"FanPower_valid\" : 1 , \"ReSuspend _valid\" : 1 , \"FrameNo\" : 1, \" SoundSet\" : 1 , \"Flag\" : 1}");
	
	cout<<devInterface->device_set(deviceId,"{\"Ver\" : \"1.0\", \"Func\" : \"OvenCheckCurve\" , \"Cmd\" : \"OVCIC\" , \"UID\" : 657895623  , \"MenuIdx\" : 0 , \"SoundSet\" : 1 , \"Flag\" : 1}");
	cout<<devInterface->device_set(deviceId,"{\"Ver\" : \"1.0\", \"Func\" : \"OvenExcuteCurve\" , \"Cmd\" : \"OVCEC\" , \"UID\" : 657895623  , \"MenuIdx\" : 0 , \"SoundSet\" : 1 , \"Flag\" : 1}");
	cout<<devInterface->device_set(deviceId,"{\"Ver\" : \"1.0\", \"Func\" : \"OvenPOrCCurve\" , \"Cmd\" : \"OVCIC\" , \"UID\" : 657895623 , \"MenuIdx\" : 0 , \"RunSuspend\" : 0 , \"SoundSet\" : 1 , \"Flag\" : 1}");

	cout<<devInterface->device_set(deviceId,"{\"Ver\" : \"1.0\", \"Func\" : \"OvenCancelExcuteCurve\" , \"Cmd\" : \"OVCCE\" , \"UID\" : 657895623 , \"MenuIdx\" : 0 , \"SoundSet\" : 1 , \"Flag\" : 1}");
	cout<<devInterface->device_set(deviceId,"{\"Ver\" : \"1.0\", \"Func\" : \"getOvenMenuName\" , \"Cmd\" : \"OVGMN\" , \"MenuIdx\" : 0 , \"SoundSet\" : 1 , \"Flag\" : 1}");
#endif

#if TEST_SEED
	deviceId = "SEEDMACHINE";
	devInterface->device_init(deviceId,0x28);
	cout<<devInterface->device_set(deviceId,"{\"Ver\" : \"1.0\", \"Func\" : \"setSeedMachinePower\" ,\"Flag\" : 1}");
#endif 

#if TEST_AC

	deviceId = "AirConditioner";
	devInterface->device_init(deviceId,1);
	devInterface->device_parse(deviceId,"F4F50140490100FE010101010066000101006A1A1E1C8080800002000000000000000080008005000000000000000000000000000000000000000000000000000000000000000000000000000000053AF4FB0D0A");

	cout <<devInterface->device_get(deviceId,"{\"Func\":\"getAirconditionPower\",\"ver\":\"1.0\"}")<<endl;
	cout <<devInterface->device_get(deviceId,"{\"Func\":\"getAirconditionWindSpeed\",\"ver\":\"1.0\"}")<<endl;
	cout <<devInterface->device_get(deviceId,"{\"Func\":\"getAirconditionMode\",\"ver\":\"1.0\"}")<<endl;
	cout <<devInterface->device_get(deviceId,"{\"Func\":\"getAirconditionSleepMode\",\"ver\":\"1.0\"}")<<endl;
	cout <<devInterface->device_get(deviceId,"{\"Func\":\"getAirconditionSetTemperature\",\"ver\":\"1.0\"}")<<endl;
	cout <<devInterface->device_get(deviceId,"{\"Func\":\"getAirconditionTemperatureIndoor\",\"ver\":\"1.0\"}")<<endl;
	cout <<devInterface->device_get(deviceId,"{\"Func\":\"getAirconditionTemperatureOutdoor\",\"ver\":\"1.0\"}")<<endl;
	cout <<devInterface->device_get(deviceId,"{\"Func\":\"getAirconditionMute\",\"ver\":\"1.0\"}")<<endl;
	cout <<devInterface->device_get(deviceId,"{\"Func\":\"getAirconditionHighEfficient\",\"ver\":\"1.0\"}")<<endl;
	cout <<devInterface->device_get(deviceId,"{\"Func\":\"getAirconditionAirDoorPosition\",\"ver\":\"1.0\"}")<<endl;
	cout <<devInterface->device_get(deviceId,"{\"Func\":\"getAirconditionWindDirection\",\"ver\":\"1.0\"}")<<endl;
	cout <<devInterface->device_get(deviceId,"{\"Func\":\"getAirconditionVerticalWindMode\",\"ver\":\"1.0\"}")<<endl;
	cout <<devInterface->device_get(deviceId,"{\"Func\":\"getAirconditionHorizontalWindContrl\",\"ver\":\"1.0\"}")<<endl;
	cout <<devInterface->device_get(deviceId,"{\"Func\":\"getAirconditionElectricalHeating\",\"ver\":\"1.0\"}")<<endl;
	cout <<devInterface->device_get(deviceId,"{\"Func\":\"getAirconditionEnergyConservation\",\"ver\":\"1.0\"}")<<endl;
	cout <<devInterface->device_get(deviceId,"{\"Func\":\"getAirconditionShare\",\"ver\":\"1.0\"}")<<endl;
	cout <<devInterface->device_get(deviceId,"{\"Func\":\"getAirconditionDualMode\",\"ver\":\"1.0\"}")<<endl;
	cout <<devInterface->device_get(deviceId,"{\"Func\":\"getAirconditionBackgroundLamp\",\"ver\":\"1.0\"}")<<endl;
	cout <<devInterface->device_get(deviceId,"{\"Func\":\"getAirconditionScreen\",\"ver\":\"1.0\"}")<<endl;
	cout <<devInterface->device_get(deviceId,"{\"Func\":\"getAirconditionLED\",\"ver\":\"1.0\"}")<<endl;
	cout <<devInterface->device_get(deviceId,"{\"Func\":\"getAirconditionLeftWind\",\"ver\":\"1.0\"}")<<endl;
	cout <<devInterface->device_get(deviceId,"{\"Func\":\"getAirconditionRightWind\",\"ver\":\"1.0\"}")<<endl;
	cout <<devInterface->device_get(deviceId,"{\"Func\":\"getAirconditionScreenLuminance\",\"ver\":\"1.0\"}")<<endl;


	cout<<devInterface->device_set(deviceId,"{\"ver\":\"1.0\",\"func\":\"setAirconditionPower\",\"deviceId\":\"AIH-W401-xxx\",\"power\":1,\"sound\":1,\"flag\":1}");
	cout<<devInterface->device_set(deviceId,"{\"ver\":\"1.0\",\"func\":\"setAirconditionMode\",\"deviceId\":\"AIH-W401-xxx\",\"mode\":\"cool\", \"sound\":1,\"flag\":1}");
	cout<<devInterface->device_set(deviceId,"{\"ver\":\"1.0\",\"func\":\"setAirconditionTemperature\",\"deviceId\":\"AIH-W401-xxx\",\"temperature\":26,\"sound\":1,\"flag\":1}");
	cout<<devInterface->device_set(deviceId,"{\"ver\":\"1.0\",\"func\":\"setAirconditionWindSpeed\",\"deviceId\":\"AIH-W401-xxx\",\"speed\":\"auto\",\"sound\":1,\"flag\":1}");

	cout<<devInterface->device_set(deviceId,"{\"ver\":\"1.0\",\"func\":\"setAirconditionHorizontalWind\",\"deviceId\":\"AIH-W401-xxx\",\"windControl\":1,\"leftWindSwing\":1, \"rightWindSwing\":1, \"sound\":1,\"flag\":1}");
	cout<<devInterface->device_set(deviceId,"{\"ver\":\"1.0\",\"func\":\"setAirconVerticalWind\",\"deviceId\":\"AIH-W401-xxx\",\"airDoorControl\":1,\"airDoorPosition\":\"auto\",\"sound\":1,\"flag\":1}");
	cout<<devInterface->device_set(deviceId,"{\"ver\":\"1.0\",\"func\":\"setAirconditionSleepMode\",\"deviceId\":\"AIH-W401-xxx\",\"sleepMode\":\"yonger\",\"sound\":1,\"flag\":1}");
	cout<<devInterface->device_set(deviceId,"{\"ver\":\"1.0\",\"func\":\"setAirconditionEnergySaving\",\"deviceId\":\"AIH-W401-xxx\",\"energySaving\":1,\"sound\":1,\"flag\":1}");


	cout<<devInterface->device_set(deviceId,"{\"ver\":\"1.0\",\"func\":\"setAirconditionBackgroundLight\",\"deviceId\":\"AIH-W401-xxx\",\"light\":1,\"sound\":1,\"flag\":1}");
	cout<<devInterface->device_set(deviceId,"{\"ver\":\"1.0\",\"func\":\"setAirconditionScreenLight\",\"deviceId\":\"AIH-W401-xxx\",\"light\":1,\"sound\":1,\"flag\":1}");
	cout<<devInterface->device_set(deviceId,"{\"ver\":\"1.0\",\"func\":\"setAirconditionLEDLight\",\"deviceId\":\"AIH-W401-xxx\",\"light\":1,\"sound\":1,\"flag\":1}");
	cout<<devInterface->device_set(deviceId,"{\"ver\":\"1.0\",\"func\":\"setAirconditionElectricalHeating\",\"deviceId\":\"AIH-W401-xxx\",\"electricalHeating\":1,\"sound\":1,\"flag\":1}");


	cout<<devInterface->device_set(deviceId,"{\"ver\":\"1.0\",\"func\":\"setAirconditionEfficient\",\"deviceId\":\"AIH-W401-xxx\",\"fastCooling\":1,\"sound\":1,\"flag\":1}");
	cout<<devInterface->device_set(deviceId,"{\"Ver\":\"1.0\",\"Func\":\"setAirconditionRealTimePowerOn\",\"RTPowerOn\":1,\"RTHour\":\"8\",\"RTMins\":\"30\",\"RTPowerOnHour\":\"10\",\"RTPowerOnMins\":\"0\",\"flag\":1}");
	cout<<devInterface->device_set(deviceId,"{\"Ver\":\"1.0\",\"Func\":\"setAirconditionRealTimePowerOff\",\"RTPowerOff\":1,\"RTHour\":\"8\",\"RTMins\":\"30\",\"RTPowerOffHour\":\"10\",\"RTPowerOffMins\":\"0\",\"flag\":1}");
	cout<<devInterface->device_set(deviceId,"{\"ver\":\"1.0\",\"func\":\"setAirconditionMuteMode\",\"deviceId\":\"AIH-W401-xxx\",\"isMuteModeOn\":1,\"sound\":1,\"flag\":1}");



	cout<<devInterface->device_set(deviceId,"{\"ver\":\"1.0\",\"func\":\"setAirconditionDualMode\",\"deviceId\":\"AIH-W401-xxx\",\"isDualMode\":1,\"sound\":1,\"flag\":1}");
	cout<<devInterface->device_set(deviceId,"{\"ver\":\"1.0\",\"func\":\"setAirconditionBrightness\",\"deviceId\":\"AIH-W401-xxx\",\"brightness\":100,\"sound\":1,\"flag\":1}");
	cout<<devInterface->device_set(deviceId,"{\"ver\":\"1.0\",\"func\":\"setAirconditionGetStatusAll\",\"deviceId\":\"AIH-W401-xxx\",\"sound\":0,\"flag\":1}");
	cout<<devInterface->device_set(deviceId,"{\"ver\":\"1.0\",\"func\":\"setOvenGetFunctionList\",\"deviceId\":\"AIH-W401-xxx\",\"sound\":0,\"flag\":1}");



	
#endif
	return 0;
}


