#include <JSONObject.h>
#include <DeviceInterface.h>


int main(int argc,char **argv){
#if 0
	/*C 语言构造*/
	JSONObject root("{\"Cmd\":\"ACSET\",\"value\":5}");
	cout<< root.toString()<<endl;
	cout<<root.getNumber("value")<<" "<<root.getString("Cmd")<<endl;
	cout<< root.toString()<<endl;

	/*String 构造*/
	JSONObject root3(root.toString());
	cout<< root3.toString()<<endl;

	/*拷贝构造*/
	JSONObject root4(root3);
	cout<< root4.toString()<<endl;
	root4.putNumber("abc",60);
	root4.putString("keyi","hello");
	
	cout<< root4.toString()<<endl;
	
	cout<< root4.toString()<<endl;
	cout<<root4.getNumber("value")<<" "<<root4.getString("Cmd")<<endl;

	/*赋值构造*/
	JSONObject root5 = root4;
	cout<<root5.toString()<<endl;
	root5 = root3;
	cout<<root5<<endl;
	root5.putString("HELLO","world");
	cout<<"==============================="<<endl;
	cout<<root5<<endl;
#endif
	DeviceInterface *devInterface = DeviceInterface::getInstance();
	if(devInterface){
		devInterface->device_init("ABC",1);
		cout<<devInterface->device_parse("ABC","12345")<<endl;
		devInterface->device_set("ABC","{\"Cmd\":\"ACSET\"\"value\":5}"/*"{\"Key\":2346,\"cmd\":\"oooooooo\"}"*/);
	}
	cout<<string("")<<endl;
	
	return 0;
}


