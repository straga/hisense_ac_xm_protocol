/*
 *
 */

#ifndef XLF_DEVICE_INTERFACE__H
#define XLF_DEVICE_INTERFACE__H

#include <XlfDeviceWrapper.h>
#include <iostream>
using namespace std;


#define INTERFACE_VERSION "V1.0.0"

#define FLAG_KEY "Flag"
#define RESULT_KEY "Result"
#define VERSION "ver"
#define CMD_KEY "Cmd"
#define SOUND_KEY "SoundSet"
#define FUNC_KEY "Func"
#define VALUE_KEY "Value"

class DeviceInterface{
    enum {
        T_AIRCONDITIONER=1,
        T_OVEN=0x27
    };
    static DeviceInterface *instance;
    DeviceInterface()  {}
    DeviceInterface(const DeviceInterface & a)  {}
    ~DeviceInterface();
    DeviceInterface& operator=(const DeviceInterface &)  {return *this;}
    XlfDeviceWrapper devWrapper;


    string handleOvenCmd(const string &deviceId,const string &jsonCmd);
public:   
    static DeviceInterface* getInstance();
   /**
       * Init one specified deives control object.
       * @param deviceId,the unique divice ID which is binded to a physical device.
       * @param type, specify the device`s type ,such as air-conditioner.
       * return zero means operating succeed,ohterwise operating failed.
       */
   int device_init(const string &deviceId, int type);

   /**
      * Parsing the device`s answer data .the data is like string "F4F501...F4FB"
      * @param deviceId, the same with device_init function paramter.
      * @param data,the device answer data.
      * return , an json string like {"CMD":"KTZD","result":"SUCCEED" ... }
      */
   string device_parse(const string &deviceId,const string &data);

   /**
       * Setting the command to device using json string as paramter.different device shoud 
       * it`s own supporting command. 
       * @param deviceId, as mentioned above
       * @param jsonCmd,the json format command string
       * return the string "F4F5" for devices command or "AT+ ... " string
       */
   string device_set(const string &deviceId,const string &jsonCmd);

   /**
       * get device information. include device version or device`s status 
       * @param deviceId, as mentioned above.
       * @jsonCmd , the information want to get.
       * return jsons string withh "value":...
       */
   string device_get(const string &deviceId,const string &jsonCmd);

    /**
        * delete one device from ,when device is offline or by user who wants to delete the device.
        * @param deviceId, as mentioned above.
        */
   void device_delete(const string &deviceId);

   string getInterfaceVersion(); 
};

#endif

