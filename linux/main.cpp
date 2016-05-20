#include <JSONObject.h>
#include <DeviceInterface.h>


int main(int argc,char **argv){
	/*C 语言构造*/
	JSONObject root("{\"Cmd\":\"ACSET\",\"value\":5}");
	cout<< "root"<<root.toString()<<endl;
	
#if 0
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
#if 1
	string deviceId = "ABC";
	string retResult = "F4F50140290100FE01270101006600010000000000FF0000000000000000001C0000001C000000000000000000000331F4FB";
	DeviceInterface *devInterface = DeviceInterface::getInstance();
	if(devInterface){
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

	}
	cout<<string("")<<endl;
#endif	
	return 0;
}


