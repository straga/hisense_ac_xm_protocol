#ifndef XLF_COMMON__H
#define XLF_COMMON__H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//#define DEBUG

#define MAX_ARR_SIZE 256

#ifdef ANDROID
#include "android/log.h"

/* for android */
#define TAG "smarthome_protocol"
#define xlf_ibug(fmt,args...) __android_log_print(ANDROID_LOG_INFO, TAG, fmt, ##args)
#define xlf_ebug(fmt,args...) __android_log_print(ANDROID_LOG_ERROR, TAG, fmt, ##args)

#ifdef DEBUG
#define xlf_debug(fmt,args...) __android_log_print(ANDROID_LOG_DEBUG, TAG, fmt, ##args)
#else
#define xlf_debug(fmt,args...)
#endif

#else
/* for linux */
#define xlf_ibug(fmt,args...) printf(fmt,##args)
#define xlf_ebug(fmt,args...) printf("ERROR:[%s] Line:%d"fmt,__FUNCTION__,__LINE__,##args)
#ifdef DEBUG
#define xlf_debug(fmt,args...) printf("[%s] Line:%d "fmt,__FUNCTION__,__LINE__,##args)
#else
#define xlf_debug(fmt,args...)
#endif
#endif


#define ARRAY_SIZE(s) (sizeof(s)/sizeof(s[0]))
#define STR(s) #s

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef char s8;
typedef short s16;
typedef int s32;

#ifdef __cplusplus
}
#endif
#endif //COMMON.H
