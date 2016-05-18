#include    <sys/types.h>
#include    <sys/stat.h>
#include    <sys/syscall.h>
#include    <fcntl.h>
#include    <stdarg.h>
#ifdef PLAT_LINUX
#include    <linux/unistd.h>
#endif
#include	<stdio.h>
#include	<stdlib.h>
#include    <string.h>
#include    <pthread.h>
#include    <errno.h>
#include	<assert.h>
#include	"xmlog.h"

#define LOG_FILE_MAX_LINE_NUM 10000
#define LOG_TIME_MAX_NUM 128
#define LOG_FILE_NAME_MAX_NUM 256
pthread_mutex_t log_mutex;

pid_t gettid(void){
#if defined(PLAT_LINUX) && !defined(ANDROID)
    return syscall(SYS_gettid);
#else
	return pthread_self();
#endif
}  
static int g_max_threads=0;
static XM_LOG_MAP *xm_map=NULL;

char * XmGetId(int pid){ 
	int i;
	if(xm_map!=NULL){
		for(i=0;i<g_max_threads;i++){
			if(xm_map[i].pid==pid){
				return xm_map[i].id;
			}
		}
	}
	return NULL;
}

FILE * XmGetFile(int pid){ 
	int i;
	if(xm_map!=NULL){
		for(i=0;i<g_max_threads;i++){
			if(xm_map[i].pid==pid){
				return (FILE *)xm_map[i].pLogFile;
			}
		}
	}
	return NULL;
}
char * XmGetFileName(int pid){ 
	int i;
	if(xm_map!=NULL){
		for(i=0;i<g_max_threads;i++){
			if(xm_map[i].pid==pid){
				return xm_map[i].filename;
			}
		}
	}
	return NULL;
}

void XmInitLog(int maxthreads){
	int i;
	if(xm_map==NULL){
	g_max_threads=2*maxthreads;
	xm_map=malloc(g_max_threads*sizeof(XM_LOG_MAP));
	assert (xm_map != NULL); 
    memset(xm_map,0,g_max_threads*sizeof(XM_LOG_MAP));
	if(xm_map!=NULL){
		for(i=0;i<g_max_threads;i++){
			xm_map[i].filename=NULL;
			xm_map[i].pLogFile=NULL;
		}
	}
	pthread_mutex_init(&log_mutex, NULL);
	}
}

void GetXmLogFileName(char * pFileName){ 
	/*definition*/ 
	pid_t xm_pid=gettid();
	char *pcid=XmGetId(xm_pid);
	/*initializing*/ 
	memset(pFileName,0,LOG_FILE_NAME_MAX_NUM);
	if(pcid){
		sprintf(pFileName,"xm_%s_%08x.log",pcid,(unsigned int)xm_pid);
	}else{
		sprintf(pFileName,"xm_%08x.log",(unsigned int)xm_pid);
	}
	//printf("[INFO][Log.c][GetPrtLogFileName()] 成功组成文件名：%s\r\n",szFileName);
}
 
char * InitXmLogFile(){ 
	/*definition*/ 
	/*日志文件路径*/ 
	char szFilePath[LOG_FILE_NAME_MAX_NUM]; 
	char *szFileName=(char *)malloc(LOG_FILE_NAME_MAX_NUM);	  
	assert (szFileName != NULL); 
	/*initializing*/ 
	memset(szFilePath,0,sizeof(szFilePath)); 
	memset(szFileName,0,sizeof(szFilePath)); 
	/*获取HOME环境变量*/
	if(getenv("HOME")){ 
		/*log日志文件夹路径位于$HOME/log*/ 
		sprintf(szFilePath,"%s/log",getenv("HOME")); 
		//printf("组成路径：%s\r\n",szFilePath); 
		/*在指定目录下创建文件夹*/ 
			if((mkdir(szFilePath,S_IRUSR|S_IWUSR|S_IXUSR)==-1)&&(errno!=EEXIST)){ 
			printf("[ERRORS][Log.c][InitPtrLogFile()] mkdir() failed!\r\n"); 
			return NULL; 
		}
		//printf("[INFO][Log.c][InitPtrLogFile()] log文件夹创建成功！\r\n");
		GetXmLogFileName(szFilePath);
		sprintf(szFileName,"%s/log/%s",getenv("HOME"),szFilePath ); 
		//printf("[INFO][Log.c][InitPrtLogFile()] 路径和文件名获取成功：%s\r\n",szFileName); 
	}else{ 
		printf("[ERRORS][Log.c][InitPtrLogFile()] getenv() failed!\r\n"); 
		return NULL;
	} 
	return szFileName; 
}

void XmSetLog(char *name,int id){ 
	int i;
	pid_t xm_pid;
	pthread_mutex_lock(&(log_mutex));	
	xm_pid=gettid();
	if(xm_map!=NULL){
		for(i=0;i<g_max_threads;i++){
			if(xm_map[i].pid==0){
				xm_map[i].pid=xm_pid;
				snprintf(xm_map[i].id,64,"%s%08x",name,id);
#if XM_FLIE_LOG				
				xm_map[i].filename=InitXmLogFile(); 
				xm_map[i].pLogFile=xm_map[i].filename?(void *)fopen(xm_map[i].filename,"a+"):NULL;
#endif
				pthread_mutex_unlock(&(log_mutex)); 
				return;
			}
		}   
	}
	pthread_mutex_unlock(&(log_mutex));	
}

void XmExitLog(void){ 
	int i;
	pthread_mutex_lock(&(log_mutex));	
	for(i=0;i<g_max_threads;i++){
#if XM_FLIE_LOG				
		if(xm_map[i].filename!=NULL){
			free(xm_map[i].filename);
			xm_map[i].filename=NULL;
		}
		if(xm_map[i].pLogFile!=NULL){
			fclose(xm_map[i].pLogFile);
			xm_map[i].pLogFile=NULL;
		}
#endif
	}
	if(xm_map!=NULL){
		free(xm_map);
		xm_map=NULL;
	}
	pthread_mutex_unlock(&(log_mutex));
	pthread_mutex_destroy(&(log_mutex));	
}

void DelXmLogFile(){ 
	/*definition*/ 
	/*日志文件路径*/ 
#if XM_FLIE_LOG
	int i;
	pid_t xm_pid=gettid();
	pthread_mutex_lock(&(log_mutex));	
	if(xm_map!=NULL){
		for(i=0;i<g_max_threads;i++){
			if(xm_pid==xm_map[i].pid){
				printf("DelXmLogFile:%p %s!\r\n",xm_map[i].pLogFile,xm_map[i].filename);
				if(xm_map[i].pLogFile!=NULL){
					fclose(xm_map[i].pLogFile);
					xm_map[i].pLogFile=NULL;
				}			
				if(xm_map[i].filename!=NULL){
					remove(xm_map[i].filename);
					free(xm_map[i].filename);
					xm_map[i].filename=NULL;
				}
				xm_map[i].pid=0;
			}
		}
	}
	pthread_mutex_unlock(&(log_mutex));
#endif
}
char *GetSystemTime(){
	struct tm struTmNow;
	time_t struTimeNow;
	static char szSystemTime[128];
	memset(szSystemTime,'\0',sizeof(szSystemTime));
	if(time(&struTimeNow)==(time_t)-1){
		printf("[ERRORS][Log.c][SystemTime()] time() failed!\r\n");
		return NULL;
	}
	/*转换成本地时间*/
	localtime_r(&struTimeNow,&struTmNow);
	snprintf(szSystemTime,127,"%04d%02d%02d",struTmNow.tm_year+1900,struTmNow.tm_mon+1,struTmNow.tm_mday);
	return szSystemTime;
} 
void XmLog(char *pszDebugStr,char *pszFormatStr,...){ 
      /*definition*/ 
      va_list listArg; 
#if XM_FLIE_LOG
	  FILE *pLogFile=NULL; 
	  pid_t xm_pid=gettid();
	  pLogFile=XmGetFile(xm_pid);
      if(pLogFile!=NULL){ 
            va_start(listArg,pszFormatStr); 
			fprintf(pLogFile,"[%s]%s\n\t",GetSystemTime(),pszDebugStr);
            /*将日志内容写入日志文件*/ 
            vfprintf(pLogFile,pszFormatStr,listArg); 
            va_end(listArg); 
            /*将内存缓冲中的数据回写到硬盘*/ 
            fflush(pLogFile); 
      }
#else	
	va_start(listArg,pszFormatStr); 
	vprintf(pszFormatStr,listArg);	
	va_end(listArg); 
#endif
}
void XmDelLog(void){ 
     DelXmLogFile();
}
void printf_buf(char * text,unsigned char *pbuf,int len){
	int i,j,k;
	if(len<=0)
		return ;
#ifdef ANDROID
	char strlog[64];
	XM_D("%s:%d\r\n",text,len);
	memset(strlog,0,32);
	for(i=0;i<len;i++){	
		if(i%8==0 && i){	
			snprintf(strlog+strlen(strlog),64-strlen(strlog)," :%c%c%c%c%c%c%c%c\r\n",pbuf[i-8],pbuf[i-7],pbuf[i-6],pbuf[i-5],pbuf[i-4],pbuf[i-3],pbuf[i-2],pbuf[i-1]);
			XM_D("%s",strlog);
			memset(strlog,0,32);
		}
		snprintf(strlog+strlen(strlog),64-strlen(strlog),"%02x ",pbuf[i]);
	}
	j=8-len%8;
	//printf("\t j=%d\r\n",j);
	if(j==8){
		i=len-8;
	}else{
		i=len/8*8;
	}
	while(j!=8 && j){
		snprintf(strlog+strlen(strlog),64-strlen(strlog),"   ");
		j--;
	}
	snprintf(strlog+strlen(strlog),64-strlen(strlog)," :");
	for(;i<len;i++){
		snprintf(strlog+strlen(strlog),64-strlen(strlog),"%c",pbuf[i]);
	}
	snprintf(strlog+strlen(strlog),64-strlen(strlog),"\r\n");
	XM_D("%s",strlog);	
#else
	XM_D("%s:%d\r\n",text,len);
	for(i=0;i<len;i++){	
		if(i%8==0 && i){
			XM_D(" :");
			for(k=8;k>0;k--){	
				XM_D("%c",(pbuf[i-k]>='0' && pbuf[i-k]<='Z')?pbuf[i-k]:' ');
			}
			//XM_D(" :%c%c%c%c%c%c%c%c",pbuf[i-8]>='0'&&pbuf[i-8]<='0',pbuf[i-7],pbuf[i-6],pbuf[i-5],pbuf[i-4],pbuf[i-3],pbuf[i-2],pbuf[i-1]);
			XM_D("\r\n");
		}
		XM_D("%02x ",pbuf[i]);
	}
	j=8-len%8;
	//printf("\t j=%d\r\n",j);
	if(j==8){
		i=len-8;
	}else{
		i=len/8*8;
	}
	while(j!=8 && j){
		XM_D("   ");
		j--;
	}
	XM_D(" :");	
	for(;i<len;i++){	
		XM_D("%c",pbuf[i]);
	}
	XM_D("\r\n");
	XM_D("\r\n");
#endif
}

