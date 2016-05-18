/*
 *	this product supports three command ,and one status
 *	AT+CLNRWATEROUT=SSID,tmp
 *   AT+CLNRWATERSTOP=SSID,tmp
 *   AT+CLNRSTATQ=SSID,?
 *
 *	+CLNRSTAT:tmp,outH,outL,缺水异常,功率传感异常,泵温异常,进水标志,出水标志,all 31-24，all 23-16，15-8，7-6
 */

#include "xm_type.h"
#include "xmlog.h"
#include "vanword.h"
#include <ctype.h>
#define PROT_HEAD	0x92

typedef VANW_ITEM_T device_item_t;
#define ERROR_BODY	222

XM_Command xm_WFClean={
	14,
	12,
	14,
	14,
	0,
	101,
	0,
	102,
	0,
	0,
	0,
	{		
		{7,8,0,NULL,0,0,1,0x92},	//HEAD
		{15,8,0,NULL,0,0,1,0x0c},	//LEN
		{23,8,0,NULL,0,0,1,0},	//cmd
		{31,8,0,NULL,0,0,1,0},		// TEMP

		{39,8,0,NULL,0,0,1,0},	//vol high
		{47,8,0,NULL,0,0,1,0},	//vol low
		
		{55,8,0,NULL,0,0,1,0},		//status 1
		{63,8,0,NULL,0,0,1,0},		//status 2
		
		{71,8,0,NULL,0,0,1,0},		//all 3
		{79,8,0,NULL,0,0,1,0},		//all 2
		{87,8,0,NULL,0,0,1,0},		//all 1
		{95,8,0,NULL,0,0,1,0},		//all 0

		{103,8,0,NULL,0,0,1,1},		//reserve
		{111,8,0,NULL,0,0,1,1},		//check
//		{23,8,0,NULL,0,1,0,3},	//cmd

	},
	{
		
//		{7 ,8,0,NULL,0,1,0,0},		//head
//		{15,8,0,NULL,0,1,0,0},		//len
//		{23,8,0,NULL,0,1,0,0},		//cmd

		{31,8,0,NULL,0,0,1,0},	//温度
		
		{39,8,0,NULL,0,0,1,0},	//出水量高8位
		{47,8,0,NULL,0,0,1,0},	//出水量低8位

//		{55,8,0,NULL,0,1,0,0},	//状态1，预留
//		{58,3,0,NULL,0,1,0,0},	//状态2高三位预留
		{59,1,0,NULL,0,0,1,0},	//缺水异常
		{60,1,0,NULL,0,0,1,0},	//功率传感器异常
		{61,1,0,NULL,0,0,1,0},	//泵温标志
		{62,1,0,NULL,0,0,1,0},	//进水标志
		{63,1,0,NULL,0,0,1,0},	//出水标志
		
		{71,8,0,NULL,0,0,1,0},	//总水量31-24位
		{79,8,0,NULL,0,0,1,0},	//总水量23-16位
		{87,8,0,NULL,0,0,1,0},	//总水量15-8位
		{95,8,0,NULL,0,0,1,0},	//总水量7-0位
//		{79,8,0,NULL,0,0,0,0}	//预留，填0
	}
};


XM_Command xm_CLEANSTAT={
	14,
	12,
	14,
	14,
	0,
	101,
	0,
	102,
	0,
	0,
	0,
	{		
		{7,8,0,NULL,0,1,0,0x92},	//HEAD
		{15,8,0,NULL,0,1,0,0x0c},	//LEN
		{23,8,0,NULL,0,1,0,3},	//cmd
		{31,8,0,NULL,0,1,0,0xff},		// TEMP

		{39,8,0,NULL,0,1,0,0xff},	//vol high
		{47,8,0,NULL,0,1,0,0xff},	//vol low
		
		{55,8,0,NULL,0,1,0,0xff},		//status 1
		{63,8,0,NULL,0,1,0,0xff},		//status 2
		
		{71,8,0,NULL,0,1,0,0xff},		//all 3
		{79,8,0,NULL,0,1,0,0xff},		//all 2
		{87,8,0,NULL,0,1,0,0xff},		//all 1
		{95,8,0,NULL,0,1,0,0xff},		//all 0

		{103,8,0,NULL,0,1,0,0xff},		//reserve
		{111,8,0,NULL,0,1,0,1},		//check

	},
	{
		
//		{7 ,8,0,NULL,0,1,0,0},		//head
//		{15,8,0,NULL,0,1,0,0},		//len
//		{23,8,0,NULL,0,1,0,0},		//cmd

		{31,8,0,NULL,0,1,0,0},	//温度
		
		{39,8,0,NULL,0,1,0,0},	//出水量高8位
		{47,8,0,NULL,0,1,0,0},	//出水量低8位

//		{55,8,0,NULL,0,1,0,0},	//状态1，预留
//		{58,3,0,NULL,0,1,0,0},	//状态2高三位预留
		{59,1,0,NULL,0,1,0,0},	//缺水异常
		{60,1,0,NULL,0,1,0,0},	//功率传感器异常
		{61,1,0,NULL,0,1,0,0},	//泵温标志
		{62,1,0,NULL,0,1,0,0},	//进水标志
		{63,1,0,NULL,0,1,0,0},	//出水标志
		
		{71,8,0,NULL,0,1,0,0},	//总水量31-24位
		{79,8,0,NULL,0,1,0,0},	//总水量23-16位
		{87,8,0,NULL,0,1,0,0},	//总水量15-8位
		{95,8,0,NULL,0,1,0,0},	//总水量7-0位
//		{79,8,0,NULL,0,0,0,0}	//预留，填0
	}
};



XM_AT_FUN at_cmd_clean[2]={
	{"CLEANSET",NULL,0,&xm_WFClean},//设置
	{"CLEANSTAT",NULL,0,&xm_CLEANSTAT}
};

XM_AT_RET at_cmd_ret_clean[2]={
	{"CLEANSTAT",XM_SEND_QUERY,102,0,&xm_CLEANSTAT},
	{"CLEANSET",XM_SEND_SETTING,101,0,&xm_WFClean}
};


static int memicmp(const void *s1,const void *s2,int n){
	int i=0,ret=0;
	while(i<n){
		ret=toupper(*((u8 *)s1++))-toupper(*((u8 *)s2++));
		if(0==ret);
		else break;
		i++;
	}
	return ret;
}

u8 xor_check(u8 *info,u8 len){
	u8 i=0;
	/* anything xor 0 = anything ,So tmp initialized to 0 */
	u8 tmp=0;
	for(i=0;i<len;i++){
		tmp=tmp ^ info[i];
	}
	return tmp;
}


extern int xlf_packet_build(char *sendbuf,char *buf,int buflen,int device_type,int device_address,int moblie_type,int moblie_address);
extern int xlf_packet_pasre(char *retbuf,char *pbuf,int len,int address);
extern void	xlf_crc(uchar * pbuf,uchar len,struct frame_crc * crc_buf);
extern int BIN2HEX(char *  p_binstr, int bin_len, char * p_hexstr);
extern 	int HEX2BIN(char *	p_hexstr, char * p_binstr);
int xlf_wifi_clean_build(char *sendbuf,char *buf,int buflen,int moblie_type,int moblie_address,int device_type,int device_address){
	u8 binStr[256];
	u8 *msgBody=NULL;
	u8 checkLen=0;
	struct frame_crc crcData;
	xlf_debug("meg xlf_wifi_clean_build!!!\n");
	int len = xlf_packet_build(sendbuf,buf,buflen,device_type,device_address,moblie_type,moblie_address);
	if(memicmp(sendbuf,"F4F5",strlen("F4F5")))
		return len;
	memset(binStr,0,sizeof(binStr));
	/* transfer it to bin array*/
	len=HEX2BIN(sendbuf,(char *)binStr);
	msgBody =(u8 *)binStr+16;
	
	//set reserve data to 0
	*(msgBody+12)=0;
	*(msgBody+13)=xor_check(msgBody+1,12);
	checkLen=*(binStr+4)+3;
	xlf_crc(binStr+2,checkLen,&crcData);
	memcpy(binStr+2+checkLen,&crcData,sizeof(struct frame_crc));
	BIN2HEX((char *)binStr,len,sendbuf);
	len=strlen(sendbuf);xlf_debug("meg xlf_wifi_clean_build\n");
	printf_buf("xlf_wifi_clean_build :",(uchar *)sendbuf,len);
	sendbuf[len-2]='\r';
	sendbuf[len-1]='\n';
	sendbuf[len]='\0';
	return len;
}


int xlf_wifi_clean_pasre(char *retbuf,char *pbuf,int len,int address){
	int length;
	u8 binbuf[512];	
	u8 index=0;
	u8 *msgBody=NULL;
	u8 *frame=NULL;
	int error=0;
	memset(binbuf,0,sizeof(binbuf));
	
	length=HEX2BIN(pbuf,(char *)binbuf);
	while(index < length-10 ){	// skip head ,.....
		if(binbuf[index] == 0xf4 && binbuf[index+1]==0xf5) break;
		index++;
	}
	frame=binbuf+index;
	msgBody =frame+16;
	xlf_debug("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ %#x %#x %#x %#x\n",msgBody[0],msgBody[1],msgBody[13],xor_check(msgBody+1,12));
	if(msgBody[0] != 0x92 || msgBody[1] !=0xc || msgBody[13] != xor_check(msgBody+1,12)){
//		xlf_debug("meg body frame wrong\n");
		error=ERROR_BODY;
	}
	length=xlf_packet_pasre(retbuf,pbuf,len,address);
	if(error){
		msgBody=(u8 *)strchr(retbuf,':');
		if(msgBody){
			sprintf((char *)msgBody+1,"ERROR,%d",error);
			length=strlen(retbuf);
		}else{
			sprintf(retbuf,"+MSG BODY:ERROR,%d\r\n",error);
			length=strlen(retbuf);
		}
	}
	return length;
}


#if 0
typedef struct {
	char *at;	//AT指令头
	u32	 cmdCode;	//if the package is returned from wifi module,then this field useful
	device_item_t *item;
}dev_at_t;

typedef struct {
	int error;
	dev_at_t *xm_cmd;
	char xm_id[XM_ID_MAX];//解析出的设备ID
	u8 argc;
	u8 xm_set;		//表示命令操作类型, 分别是设置，查询状态，查询功能
	u8 xm_sendlen;
	XM_AT xm_at;

}parse_info_t;

extern void xlf_parse_hex(char *retbuf,char *at,u8 *value,XM_Offset *pOffset);
////////////////////////////////////////////////////////////////////////////////////////////

static device_item_t device_stat={
	12,
	12,
	0,
	{
		{7 ,8,0,NULL,0,1,0,0},	//温度
		
		{15,8,0,NULL,0,1,0,0},	//出水量高8位
		{23,8,0,NULL,0,1,0,0},	//出水量低8位

//		{31,8,0,NULL,0,1,0,0},	//状态1，预留
//		{34,3,0,NULL,0,1,0,0},	//状态2高三位预留
		{35,1,0,NULL,0,1,0,0},	//缺水异常
		{36,1,0,NULL,0,1,0,0},	//功率传感器异常
		{37,1,0,NULL,0,1,0,0},	//泵温标志
		{38,1,0,NULL,0,1,0,0},	//进水标志
		{39,1,0,NULL,0,1,0,0},	//出水标志
		
		{47,8,0,NULL,0,1,0,0},	//总水量31-24位
		{55,8,0,NULL,0,1,0,0},	//总水量23-16位
		{63,8,0,NULL,0,1,0,0},	//总水量15-8位
		{71,8,0,NULL,0,1,0,0},	//总水量7-0位
//		{79,8,0,NULL,0,0,0,0}	//预留，填0
	}
};

static device_item_t device_set={
	9,
	0,
	3,
	{
	
		{7,8,0,NULL,0,0,1,0},	//温度
		{15,8,0,NULL,0,0,1,0},	//出水量高8位
		{23,8,0,NULL,0,0,1,0},	//出水量低8位
		{31,8,0,NULL,0,1,0,0},
		{39,8,0,NULL,0,1,0,0},
		{47,8,0,NULL,0,1,0,0},
		{55,8,0,NULL,0,1,0,0},
		{63,8,0,NULL,0,1,0,0},
		{71,8,0,NULL,0,1,0,0},
	}
};

static dev_at_t device_set_map[]={
	{"CLNRWATEROUT",outWater,&device_set},
	{"CLNRWATERSTOP",stopWater,&device_set},
	{"CLNRSTATQ",statQuer,&device_stat}
};

static dev_at_t device_ret_map[]={
	{"CLNRSTATR",statRet,&device_stat}
};



static int atAnalyze(parse_info_t *pnode){
	char *cmdStr=pnode->xm_at.XM_At_Buffer;
	int paramIdx=0;
	xlf_debug("\nanalyze:%s\r\n",pnode->xm_at.XM_At_Buffer); 
	
	if(*cmdStr == 'A' && *(cmdStr + 1) == 'T'){
			// 三个关键字符'+' '=' ','
		 while(*cmdStr != '\0'){
			switch(*cmdStr){
				case '+':
				{
					pnode->xm_at.getcmd=++cmdStr;
					while(*cmdStr != '='  && *cmdStr != '\0' /*&& *cmdStr != '\r' && *cmdStr != '\n'*/){
						cmdStr++;
					}	
					xlf_debug("gcmd:%s\r\n",pnode->xm_at.getcmd);
					break;
				}	
				case '=':/*full through*/
				case ',':
				{
					*cmdStr='\0';
					pnode->xm_at.getparam[paramIdx++]=++cmdStr;
					xlf_debug("gparam:%d %s\r\n",paramIdx,pnode->xm_at.getparam[paramIdx-1]);
					break;
				}
				default:
					cmdStr++;
			}/*end of switch*/ 
			
		}/*end of while*/
	}

	xlf_debug("there paramIdx =%d \n",paramIdx);
	return paramIdx;
}

static void build_at_cmd(parse_info_t *pnode,int argc){
	int k=0;
	dev_at_t *pat_cmd=NULL;
	xlf_debug("exec at:cmd  %s argc %d\r\n",pnode->xm_at.getcmd,argc);
	memset(pnode->xm_id,'\0',XM_ID_MAX);
	snprintf(pnode->xm_id,XM_ID_MAX,"%s",pnode->xm_at.getparam[0]);
		
	pnode->error=XM_ERROR_CMD_NOT_SUPPORT;
	for(k=0;k<ARRAY_SIZE(device_set_map);k++){
		pat_cmd = device_set_map+k;
		if(!memcmp(pat_cmd->at,pnode->xm_at.getcmd,strlen(pat_cmd->at) > strlen(pnode->xm_at.getcmd)?\
			(int)strlen(pat_cmd->at):(int)strlen(pnode->xm_at.getcmd))){
			xlf_debug("found at list:%s VS %s\n",pat_cmd->at,pnode->xm_at.getcmd);
			pnode->error=XM_SUCCESS;
			pnode->xm_cmd=pat_cmd;
			pnode->argc=argc;

			return;
		}
	}
	xlf_debug("ERROR:at cmd not matched\n");
	return;
}

static void dividing_str(parse_info_t *pnode){
	int paraNum=0;
	memset(pnode->xm_at.getparam,0,MAX_CMD_PARAM_NUM);
	xlf_debug("\nstrDividing:%s\r\n",pnode->xm_at.XM_At_Buffer);
	paraNum = atAnalyze(pnode);
	build_at_cmd(pnode,paraNum);
}

static u8 device_get_value(char *value,XM_Offset *item){
	int i=0;
	if(!value)
		return 0;
	if(item->textlen!=0 || item ){
		xlf_debug("get_value:%d %s\r\n",item->textlen,value);
		for(i=0;i<item->textlen;i++){
				// 比较参数，说明AT参数要和text.str中的一致
			if(!memcmp(value,item->text[i].str,strlen(item->text[i].str))){
				xlf_debug("get_value:Value %s %d\r\n",item->text[i].str,item->text[i].value);
				//pnode->xm_cmd->parameter=parameter;
				return item->text[i].value;
			}
		}
	}	
	return (u8)atoi(value);
}

static u8 xlf_device_parse_para(parse_info_t *pnode,char *copyStart,char *value,XM_Offset *pOffset){
	u8 nValue,retlen=0;
	u8 nByteOffset=0,nBitOffset,nMask;
	xlf_debug("parse_para: value %s len %d\r\n",value,pOffset->len);

	if(pOffset->len){
		xlf_debug("parse_para: pOffset %d\r\n",pOffset->offset);
		nBitOffset =7-pOffset->offset%8;
		nByteOffset=pOffset->offset/8;	
		nMask=(0xff>>(8-pOffset->len))<<nBitOffset;
		
		xlf_debug("parse_para:Offset 0x%02x\r\n",nBitOffset);	
		xlf_debug("parse_para:Byte 0x%02x\r\n",nByteOffset);
		xlf_debug("parse_para:nMask 0x%02x\r\n",nMask);
		retlen++;
		if(pOffset->len<=8){
			if(pOffset->preset){
				nValue=1;
			}else{
				nValue=device_get_value(value,pOffset);
			}
			/*这里是关键,把得到的值与放到相应的位置，并不影响其他数据*/
			copyStart[nByteOffset] |=nMask & (nValue<<nBitOffset);
			xlf_debug("Parse_Send:Value 0x%02x\r\n",nValue);
			xlf_debug("Parse_Send:Set 0x%02x\r\n",copyStart[nByteOffset]);
		}else{//大于一个字符，直接拷贝字符
			nValue=HEX2BIN(value,&copyStart[nByteOffset+1-(pOffset->len/8)]);
			xlf_debug("Parse_Send:buffer %d %s\r\n",nValue,value);
		}
		 return retlen;
	} 
	return 0;
}


static int device_Build_Send(parse_info_t *pnode,short argc,char **argv){
	u8 i,ret=0,argcproc=0;
	char *msgSatar;
	memset(pnode->xm_at.XM_At_Ret,'\0',XM_MAX_BUF);
	pnode->xm_at.XM_At_Ret[0]=0x92;
	pnode->xm_at.XM_At_Ret[LENPOS]=0xc;
	pnode->xm_at.XM_At_Ret[CMDPOS]=pnode->xm_cmd->cmdCode;
	xlf_debug("cmdCode:%#x\n",pnode->xm_at.XM_At_Ret[2]);
	msgSatar=pnode->xm_at.XM_At_Ret+3;
	xlf_debug("Build_Send: argc %d set %d\r\n",argc,pnode->xm_set);
	
	if(pnode->xm_cmd->item){
		for(i=0;i<pnode->xm_cmd->item->num ;i++){
			xlf_debug("Build_Send: parameter %d item->num:%d xm_set:%d \r\n",i,pnode->xm_cmd->item->num,pnode->xm_set);
			if(argcproc > pnode->xm_cmd->item->setNum) //如果超过了结构中定义的发送数据的个数不再填充数据
				break;
			if(pnode->xm_cmd->item->cmdArry[i].set){
				argcproc++;
				argc--;
				ret=xlf_device_parse_para(pnode,msgSatar,argc>=0?argv[argcproc-1]:"0",&pnode->xm_cmd->item->cmdArry[i]);
			}
		}
	}
	
	xlf_debug("left argc is %d ,set argcproc is %d \n",argc,argcproc);
	return pnode->xm_at.XM_At_Ret[1];
}
/*****************************************************************************************************************************************************************/

int xlf_device_pasre(char * retbuf,char *hexstr,u8 device_type){
	retbuf[0]=0;
	u8 binbuf[256];
//	u8 checkSum=0; 
	int error=XM_ERROR_FRAME_HEAD,i,j;
	int binLen,index;
	dev_at_t *pat_cmd=NULL;
	XM_Offset *pOffset=NULL;
	char *frameStart=NULL;

	xlf_debug("hexstr:%s\n",hexstr);
	memset(binbuf,0,sizeof(binbuf));
	binLen=HEX2BIN(hexstr,binbuf);
	
//	printf_buf("test",binbuf,binLen);
	for(index=0;index<binLen-1;index++){
		if(binbuf[index] == 0x92 && binbuf[index+1] == 0xc){
			frameStart=binbuf+index;
			error=XM_SUCCESS;
			break;
		}
	}
	xlf_debug("error:%d binLen %d index=%d\n",error,binLen,index);
	if(error || binLen-index<14 || xor_check((u8*)frameStart+LENPOS,12) != *(frameStart+CHECKPOS)){
		xlf_debug("the frame package %s is illegal\n",hexstr);
		printf_buf("Package ERR:",binbuf,binLen);
		return 0;
	}
	
	for(i=0;i<ARRAY_SIZE(device_ret_map);i++){
		pat_cmd=device_ret_map+i;
		if(frameStart[CMDPOS] == 0x4){
			xlf_debug("found AT CMD\n");
			snprintf(retbuf,XM_MAX_BUF,"+%s:",pat_cmd->at);

			for(j=0;j<pat_cmd->item->num;j++){
				pOffset=&pat_cmd->item->cmdArry[j];
				// 前提是cmdArry 要存在
				if(pOffset->query)
					xlf_parse_hex(retbuf,pat_cmd->at,(u8*)frameStart+3,pOffset);
			}
		}
	}
	if(strlen(retbuf)){
		retbuf[strlen(retbuf)-1]='\r';
		retbuf[strlen(retbuf)]='\n';
	}
	xlf_debug("parse at cmd:%s\n",retbuf);
	return strlen(retbuf);
}






/*at 到十六进制字符串的转换*/
/* sendbuf:将要返回的目标字符串
 * buf: at指令
 * device_type:哪种产品
 */
int xlf_device_build(char *sendbuf ,char *buf,u8 device_type){
	char *str=buf;
	int retlen=strlen(buf);
	int i=0;
	parse_info_t pnode;
	/*** find the AT head ***/
	while((retlen >XM_AT_MIN) && (*str != 'A' || *(str + 1) != 'T')) {
		str++; 
		retlen--;
	}
	memset(pnode.xm_at.XM_At_Buffer,0,XM_MAX_BUF);
	/*  免得多分配一个变量，暂用一下i  */
	while(*str  != '\0' && *str  != '\r' && *str  != '\n' && retlen > 0 && i < 250)
	{
		if(*str  != ' '  && *str != '\t'){			
			pnode.xm_at.XM_At_Buffer[i++] = *str;
		}
		str++;
		retlen--;	
	}
	if(i <= XM_AT_MIN){
		snprintf(sendbuf,1024,"%s",buf);	//出错，原样返回发给模块
		xlf_debug("at CMD lenght error\n");
		return strlen(buf);
	}
	/*
	 * 如果是这样的指令则直接透传
	 */
	if((memcmp(buf,"AT+XM",5)==0)||(memcmp(buf,"AT+WHO",6)==0)||(memcmp(buf,"AT+WF",5)==0)){			
		snprintf(sendbuf,1024,"%s",pnode.xm_at.XM_At_Buffer);
		retlen=strlen(sendbuf);
		XM_D("WIFICOMMAND STRING! %s\r\n",sendbuf);
		return retlen;
	}
	dividing_str(&pnode);
	if(pnode.xm_cmd==NULL){
		xlf_debug("the given cmd:%s not found\n",pnode.xm_at.getcmd);
		snprintf(sendbuf,1024,"%s",pnode.xm_at.XM_At_Buffer);
		return strlen(sendbuf);
	}

	if(pnode.argc){	//这是参数的个数，说明已经找到对应的At指令
		for(i=0;i<pnode.argc;i++){
			if(strncmp(pnode.xm_at.getparam[i],"?",1)==0){
				pnode.xm_set=XM_SEND_QUERY;
				break;
			}else if(strncmp(pnode.xm_at.getparam[i],"*",1)==0){
				pnode.xm_set=XM_SEND_SUPPORT;
				xlf_debug("xlf_packet_build:XM_SEND_SUPPORT!!\r\n");
				break;
			}else{
				pnode.xm_set=XM_SEND_SETTING;
				xlf_debug("xlf_packet_build:XM_SEND_SETTING!!\r\n");
			}
		}
	}else{		// 如果参数个数为0
		pnode.xm_set=XM_SEND_SETTING;
	}	
	xlf_debug("pnode.error = %d \n",pnode.error);

#if XM_WITH_ID
	if(pnode.argc<1||(pnode.error!=XM_SUCCESS)){
		xlf_debug("UNPACKETD STRING\r\n");
		pnode.error=XM_ERROR_AT_PRAR;	
		snprintf(sendbuf,1024,"%s",pnode.xm_at.XM_At_Buffer);
		retlen=strlen(sendbuf);
		xlf_debug("UNPACKETD STRING!ERROR %s\r\n",sendbuf);
		return retlen;
	}
	if(pnode.xm_set==XM_SEND_SETTING)
		pnode.xm_sendlen=device_Build_Send(&pnode,pnode.argc-1,&pnode.xm_at.getparam[1]);
	else
		pnode.xm_sendlen=device_Build_Send(&pnode,pnode.argc-2,&pnode.xm_at.getparam[2]);
#else
	pnode.xm_sendlen=device_Build_Send(&pnode,pnode.argc,pnode.xm_at.getparam);
#endif
	pnode.xm_at.XM_At_Ret[CHECKPOS]=xor_check((u8*)pnode.xm_at.XM_At_Ret+LENPOS,12);

	xlf_debug("checkSum is %#x\n",pnode.xm_at.XM_At_Ret[CHECKPOS]);
	BIN2HEX(pnode.xm_at.XM_At_Ret,14,sendbuf);
	sendbuf[2*14]=0;
	return strlen(sendbuf);
}
#endif
