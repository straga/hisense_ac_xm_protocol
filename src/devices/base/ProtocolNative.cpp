
/***************************************************************************
 *
 *  FileName: ProtocolNative.cpp
 *  Creator: mujian
 *  Date: 2014-12-03
 *  Comment: 设备传输接口的实现
 *
 ****************************************************************************/
 
#include "IProtocolNative.h"
#include "ProtocolNative.h"
#include <iostream>
#include <string>
#include <cstring>



//#include "protocol.h"


using namespace std;

#ifdef __cplusplus
extern "C" {               // 告诉编译器下列代码要以C链接约定的模式进行链接
#endif
    
    extern int xlf_packet_build(char *sendbuf,char *buf,int buflen,int moblie_type,int moblie_address,int device_type,int device_address);
    extern int xlf_packet_pasre(char *retbuf,char *pbuf,int len,int address);
#ifdef __cplusplus
}
#endif
const string ProtocolNative::TAG = "ProtocolNative";  
string ProtocolNative ::Hisense_build(string applianceCmd,int moblie_type,int moblie_address,int device_type,int device_address){
        char retbuf[1024];
        int len=0;
        memset(retbuf,0,1024);
        len=xlf_packet_build(retbuf,(char *)(applianceCmd.c_str()),applianceCmd.length(),moblie_type,moblie_address,device_type,device_address);
        if(len){
            return retbuf;
        }else{
            return "";
        }
        return "";
    }
string  ProtocolNative ::Hisense_Parse(string applianceCmd,int device_type){
        char retbuf[1024];
        int len=0;    memset(retbuf,0,1024);
        len=xlf_packet_pasre(retbuf,(char *)applianceCmd.c_str(),applianceCmd.length(),device_type);
        if(len>0){
            return retbuf;
        }else{
            return "";
        }
        return "";
    }

    