/* DO NOT EDIT THIS FILE - it is machine generated */
/* Header for class com_xinlianfeng_android_livehome_hisense_ProtocolNative */

#ifndef _Included_com_xinlianfeng_android_livehome_hisense_ProtocolNative
#define _Included_com_xinlianfeng_android_livehome_hisense_ProtocolNative
#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT jstring JNICALL Java_com_xinlianfeng_android_livehome_hisense_ProtocolNative_crcData
  (JNIEnv * , jclass ,jbyteArray ,jint ,jstring );

JNIEXPORT jbyteArray JNICALL Java_com_xinlianfeng_android_livehome_hisense_ProtocolNative_buildPacket
  (JNIEnv * , jclass ,jstring ,jint,jint );

JNIEXPORT jstring JNICALL Java_com_xinlianfeng_android_livehome_hisense_ProtocolNative_buildParse
  (JNIEnv *, jclass, jstring,jint,jint);

JNIEXPORT jstring JNICALL Java_com_xinlianfeng_android_livehome_hisense_ProtocolNative_buildPara
  (JNIEnv * , jclass ,jstring,jint,jint,jint,jint);
JNIEXPORT jstring JNICALL Java_com_xinlianfeng_android_livehome_hisense_ProtocolNative_jsonBuildPara
  (JNIEnv * , jclass ,jstring,jint,jint,jint,jint);

JNIEXPORT jstring JNICALL Java_com_xinlianfeng_android_livehome_hisense_ProtocolNative_buildParaFrame
  (JNIEnv * , jclass ,jstring,jint,jint,jint,jint,jint,jint);

JNIEXPORT jstring JNICALL Java_com_xinlianfeng_android_livehome_hisense_ProtocolNative_parsePara
  (JNIEnv * , jclass ,jstring,jint);

JNIEXPORT jstring JNICALL Java_com_xinlianfeng_android_livehome_hisense_ProtocolNative_getSourceDeviceType
  (JNIEnv * , jclass ,jstring );

JNIEXPORT jstring JNICALL Java_com_xinlianfeng_android_livehome_hisense_ProtocolNative_getSourceDeviceAddress
  (JNIEnv * , jclass ,jstring );

JNIEXPORT jstring JNICALL Java_com_xinlianfeng_android_livehome_hisense_ProtocolNative_getDestinationDeviceType
  (JNIEnv * , jclass ,jstring );

JNIEXPORT jstring JNICALL Java_com_xinlianfeng_android_livehome_hisense_ProtocolNative_getDestinationDeviceAddress
  (JNIEnv * , jclass ,jstring );

JNIEXPORT jstring JNICALL Java_com_xinlianfeng_android_livehome_hisense_ProtocolNative_getDeviceAddress
  (JNIEnv * , jclass ,jstring );
#ifdef __cplusplus
}
#endif
#endif
