#ifndef _Included_Flog
#define _Included_Flog
#ifdef PLAT_LINUX
#ifdef ANDROID
#define XM_FLIE_LOG 0
#else
#define XM_FLIE_LOG 0
#define XM_FLIE_TIME 1
#endif
#else
#define XM_FLIE_LOG 0
#endif

typedef struct _xm_log_map{
	int pid;
	char id[64];
	void *pLogFile;
	char *filename;
}XM_LOG_MAP;
void XmInitLog(int max_threads);
void XmLog(char *pszDebugStr,char *pszFormatStr,...);
void XmDelLog(void);
void XmSetLog(char *name,int id);
void XmExitLog(void);
void printf_buf(char * text,unsigned char *pbuf,int len);

#ifdef ANDROID
#include "android/log.h"

static const char *TAG="smarthome_protocol";
#define LOGI(fmt, args...) __android_log_print(ANDROID_LOG_INFO,  TAG, fmt, ##args)
#define LOGD(fmt, args...) __android_log_print(ANDROID_LOG_DEBUG, TAG, fmt, ##args)
#define LOGE(fmt, args...) __android_log_print(ANDROID_LOG_ERROR, TAG, fmt, ##args)
#define XM_E(fmt, args...) __android_log_print(ANDROID_LOG_ERROR, TAG, fmt, ##args)
#define XM_D(fmt, args...) __android_log_print(ANDROID_LOG_DEBUG, TAG, fmt, ##args)
#define XM_I(fmt, args...) __android_log_print(ANDROID_LOG_INFO,  TAG, fmt, ##args)
#define XM_V(fmt, args...) __android_log_print(ANDROID_LOG_INFO,"",fmt, ##args)
#else
#define LOGI(fmt, args...)
#define LOGD(fmt, args...)
#define LOGE(fmt, args...)
#define XM_E(fmt, args...) XmLog("XM_ERROR",fmt, ##args)
#define XM_D(fmt, args...) XmLog("XM_DEBUG",fmt, ##args)
#define XM_I(fmt, args...) XmLog("XM_INFO",fmt, ##args)
#define XM_V(fmt, args...) XmLog("",fmt, ##args)
#endif

#endif

