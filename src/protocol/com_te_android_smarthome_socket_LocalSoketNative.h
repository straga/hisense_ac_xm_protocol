/* DO NOT EDIT THIS FILE - it is machine generated */
/* Header for class com_te_android_smarthome_socket_LocalSoketNative */

#ifndef _Included_com_te_android_smarthome_socket_LocalSoketNative
#define _Included_com_te_android_smarthome_socket_LocalSoketNative
#ifdef __cplusplus
extern "C" {
#endif
JNIEXPORT jint JNICALL Java_com_te_android_smarthome_socket_LocalSoketNative_initServer
  (JNIEnv *, jclass, jstring);

JNIEXPORT jint JNICALL Java_com_te_android_smarthome_socket_LocalSoketNative_initClientIndex
  (JNIEnv *, jclass, jstring, jstring,jint,jint);

JNIEXPORT jint JNICALL Java_com_te_android_smarthome_socket_LocalSoketNative_initClient
  (JNIEnv *, jclass, jstring, jstring);

JNIEXPORT jint JNICALL Java_com_te_android_smarthome_socket_LocalSoketNative_initWithSocket
  (JNIEnv *, jclass, jint);

JNIEXPORT jint JNICALL Java_com_te_android_smarthome_socket_LocalSoketNative_configAppliance
  (JNIEnv *, jclass, jstring, jstring, jstring, jstring, jstring, jint, jint, jint, jint, jint, jint);

JNIEXPORT jint JNICALL Java_com_te_android_smarthome_socket_LocalSoketNative_exit
  (JNIEnv *, jclass);

JNIEXPORT jint JNICALL Java_com_te_android_smarthome_socket_LocalSoketNative_exitSocket
  (JNIEnv *, jclass,jint);

JNIEXPORT jstring JNICALL Java_com_te_android_smarthome_socket_LocalSoketNative_sendCommandIndex
  (JNIEnv *, jclass, jint, jstring);

JNIEXPORT jstring JNICALL Java_com_te_android_smarthome_socket_LocalSoketNative_sendCommand
  (JNIEnv *, jclass,  jstring);

JNIEXPORT jstring JNICALL Java_com_te_android_smarthome_socket_LocalSoketNative_getVersion
  (JNIEnv *, jclass);

JNIEXPORT jstring JNICALL Java_com_te_android_smarthome_socket_LocalSoketNative_crcData
  (JNIEnv *, jclass,jbyteArray,jint,jstring);

JNIEXPORT jstring JNICALL Java_com_te_android_smarthome_socket_LocalSoketNative_getPacket
  (JNIEnv *, jclass,jint);
  
JNIEXPORT jstring JNICALL Java_com_te_android_smarthome_socket_LocalSoketNative_getParse
  (JNIEnv *, jclass,jint);

JNIEXPORT jbyteArray JNICALL Java_com_te_android_smarthome_socket_LocalSoketNative_buildPacket
  (JNIEnv * , jclass ,jstring ,jint );

JNIEXPORT jbyteArray JNICALL Java_com_te_android_smarthome_socket_LocalSoketNative_buildPacketFrame
  (JNIEnv * , jclass ,jstring ,jint ,jint,jint );
JNIEXPORT jstring JNICALL Java_com_te_android_smarthome_socket_LocalSoketNative_buildParse
  (JNIEnv *, jclass,jstring,jbyteArray,jint);
  
JNIEXPORT jbyteArray JNICALL Java_com_te_android_smarthome_socket_LocalSoketNative_buildPara
(JNIEnv * , jclass ,jstring  );

JNIEXPORT jstring JNICALL Java_com_te_android_smarthome_socket_LocalSoketNative_parsePara
(JNIEnv *, jclass,jstring,jbyteArray,jint);

#ifdef __cplusplus
}
#endif
#endif
