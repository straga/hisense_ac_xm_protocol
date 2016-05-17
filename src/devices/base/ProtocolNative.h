
/***************************************************************************
 *
 *  FileName: IProtocolNative.h
 *  Creator: mujian
 *  Date: 2014-12-03
 *  Comment: 设备传输接口的定义
 *
 ****************************************************************************/
#ifndef __ProtocolTest_ProtocolNative__
#define __ProtocolTest_ProtocolNative__

//#include "IProtocolNative.h"
#include <iostream>

using namespace std;

class ProtocolNative {//: public IProtocolNative
	private: 
	static const string TAG;
//	static {
//		System.loadLibrary("hisense");
//	}
  public :
    static string  Hisense_build(string applianceCmd,int moblie_type,int moblie_address,int device_type,int device_address);
    static string  Hisense_Parse(string applianceCmd,int device_type);

    
};

#endif /*__ProtocolTest_ProtocolNative__*/
    