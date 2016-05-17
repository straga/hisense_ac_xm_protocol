/***************************************************************************
 *
 *  FileName: IProtocolNative.h
 *  Creator: mujian
 *  Date: 2014-12-03
 *  Comment: 设备传输接口的定义
 *
 ****************************************************************************/
#ifndef __ProtocolTest_IProtocolNative__
#define __ProtocolTest_IProtocolNative__

#include <string>

using namespace std;

class IProtocolNative {
	public:
		virtual ~IProtocolNative(){}
		virtual string  Hisense_build(string applianceCmd,int ntype,int address)=0;
	    virtual string  Hisense_Parse(string applianceCmd,int device_type)=0;
};

#endif /*__ProtocolTest_IProtocolNative__*/