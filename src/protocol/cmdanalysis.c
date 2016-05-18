#include	"xmlog.h"
#include	"xm_type.h"
#include    "protocol.h"
#include	"message.h"
#include	"hisense.h"
#include	"cmdanalysis.h"
#include	"air-condition_msg.h"
#include	"command.h"


/**************************************************
   *函数名称 HEX2BYTE
  *功能描述 单个十六进制字符转其对应的数值
  *返回值    转换后整数值
   *************************************************/
int HEX2BYTE(char  hex_ch)
{
    if (hex_ch >= '0' && hex_ch <= '9')
     {
        return hex_ch - '0';
    }

    if (hex_ch >= 'a'  && hex_ch <= 'f')
    {
        return hex_ch - 'a' +  10;
    }

    if (hex_ch >= 'A' && hex_ch <= 'F')
     {
        return hex_ch - 'A' + 10;
    }

    return 0x00;
}

/**************************************************



  *函数名称 HEX2BIN
   *功能描述 十六进制串转BIN串
  *返回值    转换后整数值
   *************************************************/
int HEX2BIN(char *  p_hexstr, char * p_binstr)
{
    int bin_len = 0;
    int hex_len =  strlen((char *)p_hexstr);
    int index = 0;

    if (hex_len % 2 ==  1)
    {
        hex_len -= 1;
    }

    bin_len = hex_len /  2;

    for(index = 0; index < hex_len; index+=2)
    {
         p_binstr[index/2] = ((HEX2BYTE(p_hexstr[index]) << 4) & 0xF0) +  HEX2BYTE(p_hexstr[index + 1]); 
    }

    return  bin_len;
}


 

 




#ifndef MIN
#define MIN(a,b)            (((a) < (b)) ? (a)  : (b))
#endif

#ifndef MAX
#define MAX(a,b)            (((a) <  (b)) ? (b) : (a))
#endif


#define BETWEEN(VAL, vmin, vmax) ((VAL)  >= (vmin) && (VAL) <= (vmax))
#define ISHEXCHAR(VAL)  (BETWEEN(VAL, '0', '9') || BETWEEN(VAL, 'A', 'F') || BETWEEN(VAL, 'a',  'f'))



/**************************************************
   *函数名称 BYTE2HEX
  *功能描述 将0X0-0xF的整数转换为对应的十六进制字符
  *返回值    转换后的十六进制字符
   *************************************************/
int BYTE2HEX(int  int_val)
{
    if (BETWEEN(int_val, 0, 9))
    {
        return  int_val + 0x30;
    }

    if (BETWEEN(int_val, 0xA, 0xF))
     {
        return (int_val - 0xA) + 'A';
    }

    return  '0';
}



/**************************************************
   *函数名称 BIN2HEX
  *功能描述 转BIN串串十六进制
  *返回值    转换后HEX长度
   *************************************************/
int BIN2HEX(char *  p_binstr, int bin_len, char * p_hexstr)
{
    int index   = 0;
     int hex_len = bin_len * 2;

    for (index = 0; index < bin_len;  index++)
    {    //XM_D("BIN2HEX:%s %s\r\n",p_binstr,p_hexstr);
        p_hexstr[index * 2] = BYTE2HEX((p_binstr[index]  >> 4) & 0x0F);
        p_hexstr[(index * 2) + 1] =  BYTE2HEX(p_binstr[index] & 0x0F);
		//XM_D("BIN2HEX:%d %s\r\n",index,p_hexstr);
    }
    
    return  hex_len;
}


uchar get_value(char *value,XM_Offset *parameter){
	int i=0;
	if(!value)
		return 0;
	if(parameter->textlen!=0 || parameter ){
#if DEBUG_CMD
		XM_D("get_value:%d %s\r\n",parameter->textlen,value);
#endif
		for(i=0;i<parameter->textlen;i++){
			if(!strncmp(value,parameter->text[i].str,strlen(parameter->text[i].str))){
#if DEBUG_CMD
				XM_D("get_value:Value %s %d\r\n",parameter->text[i].str,parameter->text[i].value);
#endif
				//pnode->xm_cmd->parameter=parameter;
				return parameter->text[i].value;
			}
		}
	}	
	return (uchar)atoi(value);
}

char *get_string(XM_PROTOCOL *pxm,XM_NODE *pnode,uchar value,XM_Offset *pOffset){
	int i=0;
	if(pOffset->textlen!=0 && pOffset){
#if DEBUG_CMD
		XM_D("get_string:%d %d\r\n",pOffset->textlen,value);
#endif
		for(i=0;i<pOffset->textlen;i++){
			if(value==pOffset->text[i].value){
#if DEBUG_CMD
				XM_D("get_string:Value %s %d\r\n",pOffset->text[i].str,pOffset->text[i].value);
#endif				
				return pOffset->text[i].str;
			}
		}
	}
	memset(pnode->xm_at.XM_At_Ret,'\0',XM_MAX_BUF);	
	snprintf((char *)pnode->xm_at.XM_At_Ret,XM_MAX_BUF,"%d",value);
#if DEBUG_CMD
	XM_D("get_string:Value %d %s\r\n",(int)strlen((char *)pnode->xm_at.XM_At_Ret),(char *)pnode->xm_at.XM_At_Ret);
#endif
	return (char *)pnode->xm_at.XM_At_Ret;
}

uchar parse_para(XM_PROTOCOL *pxm,XM_NODE *pnode,char *value,XM_Offset *pOffset,uchar isSend){
	uchar nValue,retlen=0;
	uint slen,i=0;
	uchar nByteOffset=0,nBitOffset,nMask;
	char * pRet;
#if DEBUG_CMD
	XM_D("parse_para: value %s len %d\r\n",value,pOffset->len);
#endif
	if(pOffset->len){
#if DEBUG_CMD
		XM_D("parse_para: pOffset %d\r\n",pOffset->offset);
#endif
		nBitOffset =7-pOffset->offset%8;
		nByteOffset=pOffset->offset/8;	
		nMask=(0xff>>(8-pOffset->len))<<nBitOffset;
#if DEBUG_CMD
		XM_D("parse_para:Offset 0x%02x\r\n",nBitOffset);	
		XM_D("parse_para:Byte 0x%02x\r\n",nByteOffset);
		XM_D("parse_para:nMask 0x%02x\r\n",nMask);
#endif
		if(isSend){//发送时
			if((pOffset->set && pnode->xm_set==XM_SEND_SETTING) || (pOffset->query && pnode->xm_set==XM_SEND_QUERY)|| (pOffset->support && pnode->xm_set==XM_SEND_SUPPORT)){
				if((pOffset->query && pnode->xm_set==XM_SEND_QUERY)|| (pOffset->support && pnode->xm_set==XM_SEND_SUPPORT))
					retlen=nByteOffset+1;
				if(pOffset->len<=8){
					if(pOffset->preset){
						nValue=pOffset->preset;
					}else{
						nValue=get_value(value,pOffset);
					}
					pnode->xm_at.XM_At_Ret[nByteOffset] |=nMask & (nValue<<nBitOffset);
#if DEBUG_CMD
					XM_D("Parse_Send:Value 0x%02x\r\n",nValue);
#endif			
#if DEBUG_CMD
					XM_D("Parse_Send:Set 0x%02x\r\n",(uchar )pnode->xm_at.XM_At_Ret[nByteOffset]);
#endif			
				}else{//大于一个字符，直接拷贝字符
					XM_D("value is %s\r\n",value);
					if(pOffset->offset != 0xff)
						nValue=HEX2BIN(value,(char *)&pnode->xm_at.XM_At_Ret[nByteOffset-(pOffset->len/8)+1]);
					else
						nValue=HEX2BIN(value,(char *)&pnode->xm_at.XM_At_Ret[0]);
#if 1
					XM_D("Parse_Send:buffer %d %s\r\n",nValue,value);
#endif			
				}
			}
			return retlen;
		}else {
#if DEBUG_CMD
			XM_D("Parse_Recv:s %d r %d set %d\r\n",pOffset->set,pOffset->query,pnode->xm_set);
#endif
			if((pOffset->set && pnode->xm_set==XM_SEND_SETTING) || (pOffset->query && pnode->xm_set==XM_SEND_QUERY)|| (pOffset->support && pnode->xm_set==XM_SEND_SUPPORT)){
				slen=strlen((char *)pnode->xm_at.XM_At_Buffer);
				if((pOffset->query && pnode->xm_set==XM_SEND_QUERY)|| (pOffset->support && pnode->xm_set==XM_SEND_SUPPORT))
					retlen=nByteOffset+1;
#if DEBUG_CMD
				XM_D("Parse_Recv:slen %d v %d plen %d\r\n",slen,pnode->xm_at.XM_At_Buffer[nByteOffset],pOffset->len);
#endif				
				if(pOffset->len<=8){
					nValue=(pxm->XM_Status_Buffer[nByteOffset] & nMask) >>nBitOffset;
#if DEBUG_CMD
					XM_D("Parse_Recv:nValue %d %d\r\n",nValue,pxm->XM_Status_Buffer[nByteOffset]);
#endif
					pRet=get_string(pxm,pnode,nValue,pOffset);
#if DEBUG_CMD
					XM_D("Parse_Recv:pRet %s\r\n",pRet);
#endif
					if(pRet && slen>0){
						pnode->xm_at.XM_At_Buffer[slen++]=',';
						pnode->xm_at.XM_At_Buffer[slen]='\0';
					}				
					snprintf((char *)pnode->xm_at.XM_At_Buffer+slen,XM_MAX_BUF-slen,"%s",pRet);
#if DEBUG_CMD
					XM_D("Parse_Recv :int Buffer %s\r\n",(char *)pnode->xm_at.XM_At_Buffer);
#endif
				}else{
				
						for (i=0;i<pOffset->len/8;i++)
							{
							if ((pxm->XM_Status_Buffer[(pOffset->offset+i*8-pOffset->len)/8]>=0x20 && pxm->XM_Status_Buffer[(pOffset->offset+i*8-pOffset->len)/8]<=0x7e)||(pxm->XM_Status_Buffer[(pOffset->offset+i*8-pOffset->len)/8]==0))
								{LOGD("Parse_Recv  String !!! pxm->XM_Status_Buffer[%d]=0x%x",i,pxm->XM_Status_Buffer[(pOffset->offset+i*8-pOffset->len)/8]);
								continue;							
								}
							else 	
								{
								LOGD("Parse_Recv  String ERROR!!! pxm->XM_Status_Buffer[%d]=0x%x",i,pxm->XM_Status_Buffer[(pOffset->offset+i*8-pOffset->len)/8]);
								pnode->errorid=XM_ERROR_MAX_CMD_IN_STRING_PARSE_ERROR;
								snprintf(pnode->xm_at.XM_At_Ret,XM_MAX_BUF,"+%s:%s,ERROR,%d",pnode->xm_cmd?pnode->xm_cmd->cmd:pnode->xm_at.getcmd,pnode->xm_id,pnode->errorid);
								XM_D("Parse_Recv  String ERROR!!: %s\r\n",pnode->xm_at.XM_At_Ret);
								goto error_exit;
								}
							}	
				
					if(slen>0){
						pnode->xm_at.XM_At_Buffer[slen++]=',';
						pnode->xm_at.XM_At_Buffer[slen]='\0';
					}					
					nValue=BIN2HEX((char *)&pxm->XM_Status_Buffer[(pOffset->offset+1-pOffset->len)/8],pOffset->len/8,(char *)pnode->xm_at.XM_At_Buffer+slen);
					pnode->xm_at.XM_At_Buffer[slen+nValue]='\0';
#if DEBUG_CMD
					XM_D("Parse_Recv:str Buffer %d %s\r\n",nValue,(char *)pnode->xm_at.XM_At_Buffer);
#endif
				}
			}
			return retlen;
		}
	}
error_exit:
	return retlen;
}
int Build_Send(XM_PROTOCOL *pxm,XM_NODE *pnode,uchar argc,char **argv){
	uchar i,ret=0,sendlen=0,argcproc=0;
#if DEBUG_CMD
	XM_D("Build_Send: argc %d set %d\r\n",argc,pnode->xm_set);
#endif
	memset(pnode->xm_at.XM_At_Ret,'\0',XM_MAX_BUF);
	for(i=0;i<pnode->xm_cmd->parameter->send_num ;i++){
#if DEBUG_CMD
			XM_D("Build_Send: parameter %d\r\n",i);
#endif
			
			if(((pnode->xm_cmd->parameter->send[i].set && pnode->xm_set==XM_SEND_SETTING) || (pnode->xm_cmd->parameter->send[i].query && pnode->xm_set==XM_SEND_QUERY)|| (pnode->xm_cmd->parameter->send[i].support && pnode->xm_set==XM_SEND_SUPPORT)) && !pnode->xm_cmd->parameter->send[i].preset){
				argcproc++;
#if DEBUG_CMD
				XM_D("Build_Send: argc %d\r\n",argcproc);
#endif
			}			
			if(argcproc<=argc){
				ret=parse_para(pxm,pnode,argcproc?argv[argcproc-1]:"0",&pnode->xm_cmd->parameter->send[i],1);
				if(ret>sendlen)
					sendlen=ret;
			}else{
				break;
			}
	}
#if DEBUG_CMD
	if(ret){
		printf_buf("Build_Send",(uchar *)pnode->xm_at.XM_At_Ret,pnode->xm_set==XM_SEND_SETTING?pnode->xm_cmd->parameter->set_len:sendlen);
	}
#endif
	return pnode->xm_set==XM_SEND_SETTING?pnode->xm_cmd->parameter->set_len:sendlen;
}
uchar  Build_Recv(XM_PROTOCOL *pxm,XM_NODE *pnode){
	uchar i;
	if(!pnode || !pnode->xm_cmd || !pnode->xm_cmd->parameter){
		return 0;
	}
#if DEBUG_CMD
	XM_D("Build_Recv: %s %d\r\n",pnode->xm_cmd->cmd,pnode->xm_set);
#endif
	memset(pnode->xm_at.XM_At_Buffer,'\0',XM_MAX_BUF);	
	for(i=0;i<pnode->xm_cmd->parameter->recv_num;i++){
#if DEBUG_CMD
		XM_D("Build_Recv: %d %d\r\n",i,pnode->xm_cmd->parameter->recv[i].query);
#endif
		parse_para(pxm,pnode,NULL,&pnode->xm_cmd->parameter->recv[i],0);
		if (pnode->errorid == XM_ERROR_MAX_CMD_IN_STRING_PARSE_ERROR)
			break;
	}
#if DEBUG_CMD
	printf_buf("At_Buffer",(uchar *)pnode->xm_at.XM_At_Buffer,strlen(pnode->xm_at.XM_At_Buffer));
#endif
	return strlen(pnode->xm_at.XM_At_Buffer);
}

int proc_append_node(XM_PROTOCOL *pxm,XM_NODE *pnode){
#if DEBUG_CMD
	XM_D("proc_append: socket %d node %p\r\n",pxm->xm_socket_client,pxm->node);
#endif
	
	if(pxm->node==NULL){
		time(&pxm->timeout);
		pxm->node=pnode;
	}else{
		XM_E("proc_append: socket %d node %p exist\r\n",pxm->xm_socket_client,pxm->node);
		return XM_ERROR_NODE;
	}
	return XM_SUCCESS;
}

int send_multi_cmd(XM_PROTOCOL *pxm){
	int sendlen=pxm->xm_waitsend>>8;
	uchar *pdata,*psend;
	XM_NODE *pnodeseek;
#if DEBUG_CMD
	XM_D("send_multi_cmd: %p\r\n",pxm);
#endif
	pnodeseek=pxm->node;
	if(pnodeseek && !pxm->xm_waitsend){		
		memset(pxm->XM_Setting_Buffer,'\0',XM_MAX_BUF);
		memset(pxm->XM_Status_Value,'\0',XM_MAX_BUF);
		snprintf((char *)pxm->XM_Status_Value,XM_MAX_BUF,"%d",pnodeseek->xm_sendlen);
	}	
#if DEBUG_CMD
	printf_buf("sendlen",(uchar *)pxm->XM_Status_Value,strlen((char *)pxm->XM_Status_Value));
#endif
	while(pnodeseek){
#if DEBUG_CMD
		XM_D("send_multi_cmd: socket %d cmd %s node %d len %d\r\n",pxm->xm_socket_client,pnodeseek->xm_cmd->cmd,pnodeseek->index,pnodeseek->xm_sendlen);
#endif
		sendlen=pnodeseek->xm_sendlen;
		pnodeseek->xm_sendready=1;		
		psend=(uchar *)(pxm->XM_Setting_Buffer);
		pdata=(uchar *)(pnodeseek->xm_at.XM_At_Ret);
#if DEBUG_CMD
		printf_buf("node send data",(uchar *)pnodeseek->xm_at.XM_At_Ret,pnodeseek->xm_sendlen);
#endif
		while(sendlen>0){
#if DEBUG_CMD
			XM_D("send_multi_cmd: sendlen %d\r\n",sendlen);
#endif
			*psend++|=*pdata++;
			sendlen-=sizeof(uchar);			
		}
		memset(pnodeseek->xm_at.XM_At_Ret,'\0',XM_MAX_BUF);
#if DEBUG_CMD
		XM_D("send_multi_cmd: copy %d\r\n",sendlen);
#endif
		sendlen=pnodeseek->xm_sendlen;
		pnodeseek=pnodeseek->end;
	}
	pnodeseek=pxm->node;
#if DEBUG_CMD
	XM_D("send_multi_cmd:%d",pxm->xm_send);
#endif
#if DEBUG_CMD
	if(pxm->xm_waitsend){
		sendlen=pxm->xm_waitsend>>8;
	}
	if(sendlen){
		printf_buf("multi_send",(uchar *)pxm->XM_Setting_Buffer,sendlen);
	}
#endif
	pxm->getparam[0]=(char *)pxm->XM_Status_Value;
	pxm->getparam[1]=(char *)pxm->XM_Setting_Buffer;
#if DEBUG_CMD
	XM_D("send_multi_cmd: ProcCmd\r\n");
#endif
#if DEBUG_THREAD
	XM_D("send_multi_cmd:wait lock node %d\r\n",pnodeseek->index);
#endif	
	if(ProcCmd(pxm,2,pxm->getparam)!=XM_SUCCESS){
		pxm->xm_send=0;
		pxm->xm_waitsend=0;	
		pxm->node=NULL;
		pxm->timeout=0;
		XM_E("send_multi_cmd: ProcCmd Fail\r\n");
#if DEBUG_THREAD
		XM_D("send_multi_cmd:proc unlock node %d index %d socket %d\r\n",pnodeseek->id,pxm->xm_index,pxm->xm_socket_client);
#endif
		pthread_mutex_unlock(&pxm->mutex);
		return XM_ERROR_CMD_TYPE;
	};   
#if DEBUG_THREAD
	XM_D("send_multi_cmd:sync lock\r\n");
#endif
	pnodeseek->is_wait=1;//标志在等待状态
	pnodeseek->errorid=XM_ERROR_SOCKET_EXIT;
	pnodeseek->sync.value=SEM_TIMEOUT;	
	pxm->xm_parse=1;
	pxm->xm_waitsend=0;	
	pxm->xm_sendready=1;
#if DEBUG_THREAD
	XM_D("send_multi_cmd:wait unlock node %d index %d socket %d\r\n",pnodeseek->id,pxm->xm_index,pxm->xm_socket_client);
#endif
	pthread_mutex_unlock(&pxm->mutex);
#if DEBUG_THREAD
	XM_D("send_multi_cmd:wait sem node %d index %d socket %d\r\n",pnodeseek->id,pnodeseek->index,pxm->xm_socket_client);
#endif
	xm_wait_sync((XM_SYNC *)pnodeseek);
	if(pnodeseek->sync.value==0 && pnodeseek->errorid==XM_SUCCESS){
		XM_E("Build_send:wait timeout %d\r\n",pnodeseek->index);
		pnodeseek->errorid=XM_ERROR_RECV_TIMEOUT;
	}
	return pnodeseek->errorid;
}

#if XM_APP
uchar ret_value(XM_PROTOCOL *pxm,XM_NODE *pnode,uchar * pbuf,uchar argc,char **argv)
{
	memset(pnode->xm_at.XM_At_Ret,'\0',XM_MAX_BUF);
#if DEBUG_AT
	XM_D("ret_value:node %p buf %p argc %d\r\n",pnode,pbuf,argc);
#endif
	if(argc>0){
#if DEBUG_AT
		printf_buf("argv0",(uchar *)argv[0],strlen(argv[0]));
#endif
		switch(argc){
			case 1:
				snprintf(pnode->xm_at.XM_At_Ret,XM_MAX_BUF,"%s",argv[0]);
			break;
			case 2:
				snprintf(pnode->xm_at.XM_At_Ret,XM_MAX_BUF,"%s,%s",argv[0],argv[1]);
			break;
			case 3:
				snprintf(pnode->xm_at.XM_At_Ret,XM_MAX_BUF,"%s,%s,%s",argv[0],argv[1],argv[2]);
			break;
			case 4:
				snprintf(pnode->xm_at.XM_At_Ret,XM_MAX_BUF,"%s,%s,%s,%s",argv[0],argv[1],argv[2],argv[3]);
			break;
			case 5:
				snprintf(pnode->xm_at.XM_At_Ret,XM_MAX_BUF,"%s,%s,%s,%s,%s",argv[0],argv[1],argv[2],argv[3],argv[4]);
			break;
			case 6:
				snprintf(pnode->xm_at.XM_At_Ret,XM_MAX_BUF,"%s,%s,%s,%s,%s,%s",argv[0],argv[1],argv[2],argv[3],argv[4],argv[5]);
			break;
			case 7:
				snprintf(pnode->xm_at.XM_At_Ret,XM_MAX_BUF,"%s,%s,%s,%s,%s,%s,%s",argv[0],argv[1],argv[2],argv[3],argv[4],argv[5],argv[6]);
			break;
			case 8:
				snprintf(pnode->xm_at.XM_At_Ret,XM_MAX_BUF,"%s,%s,%s,%s,%s,%s,%s,%s",argv[0],argv[1],argv[2],argv[3],argv[4],argv[5],argv[6],argv[7]);
			break;
			
		}		
		pnode->xm_at.XM_At_Ret[strlen(pnode->xm_at.XM_At_Ret)]='\0';
#if DEBUG_AT
		printf_buf("At_Ret",(uchar *)pnode->xm_at.XM_At_Ret,strlen(pnode->xm_at.XM_At_Ret));
#endif
	}
	else{
		snprintf(pnode->xm_at.XM_At_Ret,XM_MAX_BUF,"ERROR");
	}
#if DEBUG_AT
	printf_buf("ret",(uchar *)pnode->xm_at.XM_At_Ret,strlen((char *)pnode->xm_at.XM_At_Ret));
#endif
	return XM_SUCCESS;
}
uchar ret_ok(XM_PROTOCOL *pxm,XM_NODE *pnode,uchar * pbuf,uchar argc,char **argv)
{
	memset(pnode->xm_at.XM_At_Ret,'\0',XM_MAX_BUF);
	snprintf(pnode->xm_at.XM_At_Ret,XM_MAX_BUF,"SUCCEED");
	return XM_SUCCESS;
}
uchar ret_error(XM_PROTOCOL *pxm,XM_NODE *pnode,uchar * pbuf,uchar argc,char **argv)
{	
	memset(pnode->xm_at.XM_At_Ret,'\0',XM_MAX_BUF);
	if(argc==1){
		if(!strncmp(argv[0],"0",1)){
				snprintf(pnode->xm_at.XM_At_Ret,XM_MAX_BUF,"OK");
				return XM_SUCCESS;
		}
	}
	snprintf(pnode->xm_at.XM_At_Ret,XM_MAX_BUF,"ERROR");
	return XM_SUCCESS;
}
#endif
/*
WHO=//查询型号
XMV=//查询版本
XMA=//激活控制
XMR=//查询模块状态
XMMAC=//获取MAC 地址
XMWPS=//WPS连接
XMHB=//心跳包
XMDNS=//设置DNS地址
XMRS=//设置远程服务域名和端口
XMLS=//设置本地服务域名和端口
XMAP=//设置WIFI SSID 和密码
XMCR=//连接远程服务器
XMCL=//连接本地服务器
XMLC=//切换本地配置模式
XMBR=//设置模块串口通讯速率
XMMB=//开始多设置命令合并
XMME=//结束多设置命令合并
RET=//
OK=//
ERROR=//
*/


XM_AT_FUN at_cmd[]={
		{"WHO",NULL,1,NULL},
		{"XMV",NULL,1,NULL},
		{"XMA",NULL,1,NULL},
		{"XMR",NULL,1,NULL},
		{"XMMAC",NULL,1,NULL},
		{"XMWPS",NULL,1,NULL},
		{"XMHB",NULL,1,NULL},
		{"XMDNS",NULL,1,NULL},
		{"XMRS",NULL,1,NULL},
		{"XMLS",NULL,1,NULL},
		{"XMAP",NULL,1,NULL},
		{"XMCR",NULL,1,NULL},
		{"XMCL",NULL,1,NULL},
		{"XMLC",NULL,1,NULL},
		{"XMBR",NULL,1,NULL},
		//add by mujian;
		{"XMID",NULL,1,NULL},
		{"XMSSID",NULL,1,NULL},
		{"XMOTA",NULL,1,NULL},
		{"XMLED",NULL,1,NULL},
		{"XMCLS",NULL,1,NULL},
		{"XMWIFI",NULL,1,NULL},
		{"XMCS",NULL,1,NULL},
		{"XMSIP",NULL,1,NULL},
		{"XMEXIT",NULL,1,NULL},		
		{"WFMOD",NULL,1,NULL},
		{"WFV",NULL,1,NULL},
		{"WFA",NULL,1,NULL},
		{"WFR",NULL,1,NULL},
		{"WFMAC",NULL,1,NULL},
		{"WFUID",NULL,1,NULL},
		{"WFHB",NULL,1,NULL},
		{"WFDNS",NULL,1,NULL},
		{"WFRS",NULL,1,NULL},
		{"WFLS",NULL,1,NULL},
		{"WFAP",NULL,1,NULL},
		{"WFCR",NULL,1,NULL},
		{"WFCL",NULL,1,NULL},
		{"WFLC",NULL,1,NULL},
		{"WFBR",NULL,1,NULL},
		//add by mujian;
		{"WFID",NULL,1,NULL},
		{"WFSSID",NULL,1,NULL},
		{"WFOTA",NULL,1,NULL},
		{"WFLED",NULL,1,NULL},
		{"WFCLS",NULL,1,NULL},
		{"WFDEV",NULL,1,NULL},
		{"WFCS",NULL,1,NULL},
		{"WFSIP",NULL,1,NULL},
		{"WFEXIT",NULL,1,NULL},
#if XM_APP
		{"RET",ret_value,2,NULL},
		{"OK",ret_ok,2,NULL},
		{"ERROR",ret_error,2,NULL}
#endif
};
extern XM_AT_FUN at_cmd_kt[];
extern XM_AT_FUN at_cmd_kl[];
extern XM_AT_FUN at_cmd_jh[];
extern XM_AT_FUN at_cmd_cs[];
extern XM_AT_FUN at_cmd_qr[];
extern XM_AT_FUN at_cmd_oven[];
extern XM_AT_FUN at_cmd_rsq[];
extern XM_AT_FUN at_cmd_rqz[];
//extern XM_AT_FUN at_cmd_clean[];
extern XM_AT_FUN at_cmd_DC[];
extern XM_AT_FUN at_cmd_Seed[9];


extern XM_AT_FUN at_cmd_senser[4];
extern XM_AT_FUN at_cmd_curtain[3];
extern XM_AT_FUN at_cmd_volta[2];
extern XM_AT_FUN at_cmd_smartLight[7];

XM_AT_LIST xm_at_list[]={
		{23,at_cmd_kl,0xFF,NULL},
		{59,at_cmd_kt,0x01,NULL},
		// add for mobile air conditioner
		{59,at_cmd_kt,0x36,NULL},
		{12,at_cmd_jh,0x18,NULL},			
		{12,at_cmd_cs,0x15,NULL},			
		{7,at_cmd_qr,0x19,NULL},
		{18,at_cmd_oven,0x27,NULL},
		{8,at_cmd_rsq,0x25,NULL},
		{5,at_cmd_rqz,0x22,NULL},
		// add by hetao
		{10,at_cmd_Seed,0x28,NULL},
		{5,at_cmd_DC,0x29,NULL},
		{4,at_cmd_senser,0x53,NULL},
		{3,at_cmd_curtain,0x55,NULL},
		{2,at_cmd_volta,0x11,NULL},
		{7,at_cmd_smartLight,0x52,NULL},

		{sizeof(at_cmd)/sizeof(at_cmd[0]),at_cmd,0xff}
};

uchar build_at_ret(XM_PROTOCOL *pxm,XM_NODE *pnode,char *pmsg,uchar code){
	XM_NODE *pnodeseek=NULL;
#if DEBUG_AT
	XM_D("build_at_ret:pxm %p node %p pmsg %p\r\n",pxm,pnode,pmsg);
#endif
	if(pnode){
		pnodeseek=pnode;
		memset(pnodeseek->xm_at.XM_At_Ret,'\0',XM_MAX_BUF);
	}else{
		pnodeseek=pxm->node;
		while(pnodeseek){
			memset(pnodeseek->xm_at.XM_At_Ret,'\0',XM_MAX_BUF);
			pnodeseek=pnodeseek->end;
		}
		pnodeseek=pxm->node;
	}
#if DEBUG_AT
	if(pnodeseek && pnodeseek->xm_cmd && pnodeseek->xm_cmd->parameter && pnodeseek->xm_set!=XM_SEND_SETTING){
		printf_buf("at_ret",pxm->XM_Status_Buffer,pnodeseek->xm_set==XM_SEND_SUPPORT?pnodeseek->xm_cmd->parameter->support_len:pnodeseek->xm_cmd->parameter->query_len);
	}
	if(pnodeseek && pnodeseek->xm_set==XM_SEND_CONFIG){
		printf_buf("config_ret",pxm->XM_Status_Buffer,(int)strlen((char *)pxm->XM_Status_Buffer));
	}
#endif
#if DEBUG_AT
	XM_D("build_at_ret:code %d node %p %d\r\n",code,pnodeseek,pnodeseek?pnodeseek->xm_sendready:-1);
#endif
#if DEBUG_RS
	if(pnodeseek && pnodeseek->xm_cmd ){
		XM_D("build_at_ret:code %d node %p cmd %s type %d send %d\r\n",code,pnodeseek,pnodeseek->xm_cmd->cmd,pnodeseek->xm_cmd->type,pnodeseek->xm_set);
	}
#endif
	
	if(code==XM_SUCCESS){
#if DEBUG_AT
		XM_D("build_at_ret: ok\r\n");
#endif
		if(pnodeseek->xm_set==XM_SEND_CONFIG){
			memcpy(pnodeseek->xm_at.XM_At_Ret,pxm->XM_Status_Buffer,strlen((char *)pxm->XM_Status_Buffer));			
		}else{
			while(pnodeseek){
				if(pmsg==NULL){
#if DEBUG_AT
					XM_D("build_at_ret: ok\r\n");
#endif
					if(Build_Recv(pxm,pnodeseek)==0){
#if DEBUG_CMD
						XM_D("build_at_ret: not value\r\n");
#endif
#if XM_APP
						snprintf(pnodeseek->xm_at.XM_At_Ret,XM_MAX_BUF,"AT+OK\r\n");
#else
#if XM_WITH_ID
						snprintf(pnodeseek->xm_at.XM_At_Ret,XM_MAX_BUF,"+%s:%s,SUCCEED",pnodeseek->xm_cmd?pnodeseek->xm_cmd->cmd:pnodeseek->xm_at.getcmd,pnodeseek->xm_id);
#else
						snprintf(pnodeseek->xm_at.XM_At_Ret,XM_MAX_BUF,"+%s:SUCCEED",pnodeseek->xm_cmd?pnodeseek->xm_cmd->cmd:pnodeseek->xm_at.getcmd);
#endif			
#endif
						pnodeseek->xm_at.XM_At_Ret[XM_MAX_BUF-1]='\0';
					}else{	
#if DEBUG_CMD
						XM_D("build_at_ret: have value\r\n");
#endif
						if (pnodeseek->errorid != XM_ERROR_MAX_CMD_IN_STRING_PARSE_ERROR)
						{
#if XM_APP
						snprintf(pnodeseek->xm_at.XM_At_Ret,XM_MAX_BUF,"AT+RET=%s\r\n",pnodeseek->xm_at.XM_At_Buffer);
#else
#if XM_WITH_ID
						snprintf(pnodeseek->xm_at.XM_At_Ret,XM_MAX_BUF,"+%s:%s,%s",pnodeseek->xm_cmd?pnodeseek->xm_cmd->cmd:pnodeseek->xm_at.getcmd,pnodeseek->xm_id,pnodeseek->xm_at.XM_At_Buffer);
#else
						snprintf(pnodeseek->xm_at.XM_At_Ret,XM_MAX_BUF,"+%s:%s",pnodeseek->xm_cmd?pnodeseek->xm_cmd->cmd:pnodeseek->xm_at.getcmd,pnodeseek->xm_at.XM_At_Buffer);
#endif
#endif
						pnodeseek->xm_at.XM_At_Ret[XM_MAX_BUF-1]='\0';
					}
					}
				}else{
#if DEBUG_CMD
					XM_D("build_at_ret: string\r\n");
#endif
#if XM_APP
					snprintf(pnodeseek->xm_at.XM_At_Ret,XM_MAX_BUF,"AT+RET=%s\r\n",pmsg);
#else
#if XM_WITH_ID
					snprintf(pnodeseek->xm_at.XM_At_Ret,XM_MAX_BUF,"+%s:%s,%s",pnodeseek->xm_cmd?pnodeseek->xm_cmd->cmd:pnodeseek->xm_at.getcmd,pnodeseek->xm_id,pmsg);
#else
					snprintf(pnodeseek->xm_at.XM_At_Ret,XM_MAX_BUF,"+%s:%s",pnodeseek->xm_cmd?pnodeseek->xm_cmd->cmd:pnodeseek->xm_at.getcmd,pmsg);
#endif
#endif
					pnodeseek->xm_at.XM_At_Ret[XM_MAX_BUF-1]='\0';
				}
#if DEBUG_CMD
				if (pxm->sendcmd > 210)
					{
					snprintf(pnodeseek->xm_at.XM_At_Ret,XM_MAX_BUF,"%s,%d,%d",pnodeseek->xm_at.XM_At_Ret,pxm->xm_frame,pxm->xm_sub_frame);
					}
				printf_buf("build_at_ret",(uchar *)pnodeseek->xm_at.XM_At_Ret,strlen(pnodeseek->xm_at.XM_At_Ret));
				XM_D("build_at_ret: %s\r\n",pnodeseek->xm_at.XM_At_Ret);

#endif

				pnodeseek=pnodeseek->end;
			}
			return XM_SUCCESS;
		}
		
	}else{
#if DEBUG_AT
		XM_D("build_at_ret: fail %d\r\n",code);
#endif
		if(pnodeseek->xm_set==XM_SEND_CONFIG){
			snprintf(pnodeseek->xm_at.XM_At_Ret,XM_MAX_BUF,"+%s:%d,ERROR",pnodeseek->xm_cmd?pnodeseek->xm_cmd->cmd:pnodeseek->xm_at.getcmd,code);
		}else{
			while(pnodeseek){
#if XM_APP
				snprintf(pnodeseek->xm_at.XM_At_Ret,XM_MAX_BUF,"AT+ERROR=%d\r\n",code);
#else
#if XM_WITH_ID
				snprintf(pnodeseek->xm_at.XM_At_Ret,XM_MAX_BUF,"+%s:%s,ERROR,%d",pnodeseek->xm_cmd?pnodeseek->xm_cmd->cmd:pnodeseek->xm_at.getcmd,pnodeseek->xm_id,code);
#else
				snprintf(pnodeseek->xm_at.XM_At_Ret,XM_MAX_BUF,"+%s:ERROR",pnodeseek->xm_cmd?pnodeseek->xm_cmd->cmd:pnodeseek->xm_at.getcmd);
#endif			
#endif
				pnodeseek->xm_at.XM_At_Ret[XM_MAX_BUF-1]='\0';
				pnodeseek=pnodeseek->end;
			}
		}
		return code;
	}
#if 0
	XM_D("build_at_ret:\r\n");
	for(i=0;i<XM_MAX_BUF;i++){
		XM_PRINTF("%02x ",pnode->xm_at.XM_At_Ret[i]);
	}
	XM_D("\r\n");
#endif
	return XM_SUCCESS;
}

void proc_cmd(XM_PROTOCOL *pxm,XM_NODE *pnode){
	int sendcmd=0,sendsub=0,i;	
	uchar *pdata,*psend;
#if DEBUG_CMD
	//int i;
#endif
	if(!pxm || !pnode){
		pnode->errorid=XM_ERROR_AT_PRAR;
#if DEBUG_THREAD
		XM_D("proc_cmd:prar unlock node %d index %d socket %d\r\n",pnode->id,pxm->xm_index,pxm->xm_socket_client);
#endif
		pthread_mutex_unlock(&pxm->mutex);
		return;
	}
#if DEBUG_CMD
	XM_D("proc_cmd:argc %d\r\n",pnode->argc);
	for(i=0;i<pnode->argc;i++){
		XM_D("proc_cmd:argc %d %s\r\n",i,pnode->xm_at.getparam[i]);
	}
#endif
#if DEBUG_CMD
	XM_D("proc_cmd:param %p\r\n",pnode->xm_at.getparam[1]);
#endif
	if(pnode->xm_cmd->type==0){
		if(pnode->argc){
			for( i=0;i<pnode->argc;i++){
			if(strncmp(pnode->xm_at.getparam[i],"?",1)==0){
				pnode->xm_set=XM_SEND_QUERY;
				sendcmd=pnode->xm_cmd->parameter->query_cmd;
				sendsub=pnode->xm_cmd->parameter->query_sub;
	#if DEBUG_CMD
				XM_D("proc_cmd:XM_SEND_QUERY!!\r\n");
	#endif
				break;
			}else if(strncmp(pnode->xm_at.getparam[i],"*",1)==0){
				pnode->xm_set=XM_SEND_SUPPORT;				
				sendcmd=pnode->xm_cmd->parameter->support_cmd;
				sendsub=pnode->xm_cmd->parameter->support_sub;
	#if DEBUG_CMD
				XM_D("proc_cmd:XM_SEND_SUPPORT!!\r\n");
	#endif				
				break;
			}else{
				pnode->xm_set=XM_SEND_SETTING;				
				sendcmd=pnode->xm_cmd->parameter->set_cmd;
				sendsub=pnode->xm_cmd->parameter->set_sub;
	#if DEBUG_CMD
				XM_D("proc_cmd:XM_SEND_SETTING!!\r\n");
	#endif				
			}
			}
		}
		else{
			pnode->xm_set=XM_SEND_SETTING;
			sendcmd=pnode->xm_cmd->parameter->set_cmd;
			sendsub=pnode->xm_cmd->parameter->set_sub;
		}
		/*对于102 0 或者102 64命令在无设置的情况下使用缓存的数据*/
		/*对于102 0 命令之外的查询命令执行后也需要重新取数据*/
#if DEBUG_RS
		XM_D("proc_cmd:cmd %d sub %d wait %d\r\n",pxm->sendcmd,pxm->sendsub,pxm->xm_waitsend);
#endif
		//决断当前的socket 是否有效
		if(!pxm->xm_exit && pxm->xm_socket_client!=-1){
			pxm->xm_seting=1;
#if DEBUG_CMD
			XM_D("proc_cmd:cmd %d sub %d wait %d\r\n",pxm->sendcmd,pxm->sendsub,pxm->xm_waitsend);
#endif
#if DEBUG_CMD
			XM_D("proc_cmd:xm_set %d\r\n",pnode->xm_set);
#endif
			
#if XM_WITH_ID
			if(pnode->argc<2){
				XM_E("proc_cmd:ERROR AT PRAR\r\n");
				pnode->errorid=XM_ERROR_AT_PRAR;
#if DEBUG_THREAD
				XM_D("proc_cmd:argc unlock node %d index %d socket %d\r\n",pnode->id,pxm->xm_index,pxm->xm_socket_client);
#endif
				pthread_mutex_unlock(&pxm->mutex);
				return;
			}
			if(pnode->xm_set==XM_SEND_SETTING)
				pnode->xm_sendlen=Build_Send(pxm,pnode,pnode->argc-1,&pnode->xm_at.getparam[1]);
			else
				pnode->xm_sendlen=Build_Send(pxm,pnode,pnode->argc-2,&pnode->xm_at.getparam[2]);
#else
			pnode->xm_sendlen=Build_Send(pxm,pnode,pnode->argc,pnode->xm_at.getparam);
#endif
#if DEBUG_CMD
			XM_D("proc_cmd:sendlen %d\r\n",pnode->xm_sendlen);
#endif
#if DEBUG_THREAD
			XM_D("proc_cmd:socket %d proc finish\r\n",pxm->xm_socket_client);
#endif
			if(pxm->xm_waitsend==0){
				pnode->errorid=proc_append_node(pxm,pnode);
				if(pnode->errorid==XM_SUCCESS){
					pxm->sendcmd=sendcmd;
					pxm->sendsub=sendsub;
					pnode->errorid=send_multi_cmd(pxm);			
				}else{
					XM_E("proc_cmd:append node fail\r\n");
#if DEBUG_THREAD
					XM_D("proc_cmd:append unlock node %d index %d socket %d\r\n",pnode->id,pxm->xm_index,pxm->xm_socket_client);
#endif
					pthread_mutex_unlock(&pxm->mutex);
				}			
			}else{
				pxm->xm_waitsend=pnode->xm_sendlen<<8|1;
#if DEBUG_CMD
				XM_D("proc_cmd:waitsend  0x%04x\r\n",pxm->xm_waitsend);
#endif
#if DEBUG_CMD
				printf_buf("pnode\r\n",(uchar *)pnode->xm_at.XM_At_Ret,pnode->xm_sendlen);
#endif
				psend=(uchar *)(pxm->XM_Setting_Buffer);
				pdata=(uchar *)(pnode->xm_at.XM_At_Ret);
				while(pnode->xm_sendlen>0){
#if DEBUG_CMD
					XM_D("proc_cmd:waitsend sendlen %d\r\n",pnode->xm_sendlen);
#endif
					*psend++|=*pdata++;
					pnode->xm_sendlen-=sizeof(uchar);
				}			
				memset(pnode->xm_at.XM_At_Ret,'\0',XM_MAX_BUF);
#if DEBUG_CMD
				printf_buf("waitsend",(uchar *)pxm->XM_Setting_Buffer,pxm->xm_waitsend>>8);
#endif
#if DEBUG_CMD
				XM_D("proc_cmd:waitsend copy %d\r\n",pnode->xm_sendlen);
#endif
				pxm->sendcmd=sendcmd;
				pxm->sendsub=sendsub;
				pnode->errorid=XM_ERROR_WAIT_MOER;
#if DEBUG_THREAD
				XM_D("proc_cmd:waitsend unlock node %d index %d socket %d\r\n",pnode->id,pxm->xm_index,pxm->xm_socket_client);
#endif
				pthread_mutex_unlock(&pxm->mutex);
			}
		}else{
			XM_E("ERROR proc_cmd:socket is exited or vail\r\n");
			pnode->errorid=XM_ERROR_VAIL;
#if DEBUG_THREAD
			XM_D("proc_cmd:vail unlock node %d index %d socket %d\r\n",pnode->id,pxm->xm_index,pxm->xm_socket_client);
#endif
			pthread_mutex_unlock(&pxm->mutex);
		}
		return;
	}else  if(pnode->xm_cmd->type==1){
		if(pxm->xm_exit==0){
			memset(pxm->XM_Frame_Buffer,0,XM_MAX_BUF);			
			switch(pnode->argc){
				case 0:				
					snprintf((char *)pxm->XM_Frame_Buffer,XM_MAX_BUF,"%s",pnode->xm_at.XM_At_Buffer);
					break;
				case 1:
#if XM_WITH_ID
					snprintf((char *)pxm->XM_Frame_Buffer,XM_MAX_BUF,"%s",pnode->xm_at.XM_At_Buffer);
#else
					snprintf((char *)pxm->XM_Frame_Buffer,XM_MAX_BUF,"%s=%s",pnode->xm_at.XM_At_Buffer,pnode->xm_at.getparam[0]);
#endif
				break;
				case 2:
#if XM_WITH_ID
					snprintf((char *)pxm->XM_Frame_Buffer,XM_MAX_BUF,"%s=%s",pnode->xm_at.XM_At_Buffer,pnode->xm_at.getparam[1]);
#else
					snprintf((char *)pxm->XM_Frame_Buffer,XM_MAX_BUF,"%s=%s,%s",pnode->xm_at.XM_At_Buffer,pnode->xm_at.getparam[0],pnode->xm_at.getparam[1]);
#endif
				break;
				case 3:
#if XM_WITH_ID
					snprintf((char *)pxm->XM_Frame_Buffer,XM_MAX_BUF,"%s=%s,%s",pnode->xm_at.XM_At_Buffer,pnode->xm_at.getparam[1],pnode->xm_at.getparam[2]);
#else
					snprintf((char *)pxm->XM_Frame_Buffer,XM_MAX_BUF,"%s=%s,%s,%s",pnode->xm_at.XM_At_Buffer,pnode->xm_at.getparam[0],pnode->xm_at.getparam[1],pnode->xm_at.getparam[2]);
#endif
				break;
				case 4:
#if XM_WITH_ID
					snprintf((char *)pxm->XM_Frame_Buffer,XM_MAX_BUF,"%s=%s,%s,%s",pnode->xm_at.XM_At_Buffer,pnode->xm_at.getparam[1],pnode->xm_at.getparam[2],pnode->xm_at.getparam[3]);
#else
					snprintf((char *)pxm->XM_Frame_Buffer,XM_MAX_BUF,"%s=%s,%s,%s,%s",pnode->xm_at.XM_At_Buffer,pnode->xm_at.getparam[0],pnode->xm_at.getparam[1],pnode->xm_at.getparam[2],pnode->xm_at.getparam[3]);
#endif
				case 5:
#if XM_WITH_ID
					snprintf((char *)pxm->XM_Frame_Buffer,XM_MAX_BUF,"%s=%s,%s,%s,%s",pnode->xm_at.XM_At_Buffer,pnode->xm_at.getparam[1],pnode->xm_at.getparam[2],pnode->xm_at.getparam[3],pnode->xm_at.getparam[4]);
#else
					snprintf((char *)pxm->XM_Frame_Buffer,XM_MAX_BUF,"%s=%s,%s,%s,%s",pnode->xm_at.XM_At_Buffer,pnode->xm_at.getparam[0],pnode->xm_at.getparam[1],pnode->xm_at.getparam[2],pnode->xm_at.getparam[3],pnode->xm_at.getparam[4]);
#endif
				case 6:
#if XM_WITH_ID
					snprintf((char *)pxm->XM_Frame_Buffer,XM_MAX_BUF,"%s=%s,%s,%s,%s,%s",pnode->xm_at.XM_At_Buffer,pnode->xm_at.getparam[1],pnode->xm_at.getparam[2],pnode->xm_at.getparam[3],pnode->xm_at.getparam[4],pnode->xm_at.getparam[5]);
#else
					snprintf((char *)pxm->XM_Frame_Buffer,XM_MAX_BUF,"%s=%s,%s,%s,%s,%s",pnode->xm_at.XM_At_Buffer,pnode->xm_at.getparam[0],pnode->xm_at.getparam[1],pnode->xm_at.getparam[2],pnode->xm_at.getparam[3],pnode->xm_at.getparam[4],pnode->xm_at.getparam[5]);
#endif
				case 7:
#if XM_WITH_ID
					snprintf((char *)pxm->XM_Frame_Buffer,XM_MAX_BUF,"%s=%s,%s,%s,%s,%s,%s",pnode->xm_at.XM_At_Buffer,pnode->xm_at.getparam[1],pnode->xm_at.getparam[2],pnode->xm_at.getparam[3],pnode->xm_at.getparam[4],pnode->xm_at.getparam[5],pnode->xm_at.getparam[6]);
#else
					snprintf((char *)pxm->XM_Frame_Buffer,XM_MAX_BUF,"%s=%s,%s,%s,%s,%s,%s",pnode->xm_at.XM_At_Buffer,pnode->xm_at.getparam[0],pnode->xm_at.getparam[1],pnode->xm_at.getparam[2],pnode->xm_at.getparam[3],pnode->xm_at.getparam[4],pnode->xm_at.getparam[5],pnode->xm_at.getparam[6]);
#endif
			}
			pnode->xm_sendlen=pxm->xm_send=strlen((char *)pxm->XM_Frame_Buffer);
			if(pxm->xm_send){				
				pnode->errorid=proc_append_node(pxm,pnode);
				if(pnode->errorid==XM_SUCCESS){
					pnode->xm_sendready=1;
					pxm->xm_sendready=1;
					pxm->xm_parse=0;
					pxm->sendcmd=0;
					pxm->sendsub=0;
					pxm->xm_seting=1;
					pnode->errorid=XM_SUCCESS;
					pnode->xm_set=XM_SEND_CONFIG;
					memset(pxm->XM_Status_Buffer,0,XM_MAX_BUF);
#if DEBUG_THREAD
					XM_D("proc_cmd:config unlock node %d index %d socket %d\r\n",pnode->id,pxm->xm_index,pxm->xm_socket_client);
#endif
					pthread_mutex_unlock(&pxm->mutex);
#if DEBUG_THREAD
					XM_D("proc_cmd:ProcConfig wait sem node %d index %d socket %d\r\n",pnode->id,pnode->index,pxm->xm_socket_client);
#endif
					xm_wait_sync((XM_SYNC *)pnode);
				}else{
#if DEBUG_THREAD
					XM_D("proc_cmd:config append unlock node %d index %d socket %d\r\n",pnode->id,pxm->xm_index,pxm->xm_socket_client);
#endif
					pthread_mutex_unlock(&pxm->mutex);
				}
			}else{
				pnode->errorid=XM_ERROR_VAIL;
				XM_E("proc_cmd:ProcConfig data build fail socket %d\r\n",pxm->xm_socket_client);	
#if DEBUG_THREAD
				XM_D("proc_cmd:config vail unlock node %d index %d socket %d\r\n",pnode->id,pxm->xm_index,pxm->xm_socket_client);
#endif
				pthread_mutex_unlock(&pxm->mutex);
			}
#if DEBUG_RS
			printf_buf("Config",pxm->XM_Frame_Buffer,pxm->xm_send);
#endif
		}else{
			pnode->errorid=XM_ERROR_VAIL;
			XM_E("proc_cmd:ProcConfig socket is exit\r\n");	
#if DEBUG_THREAD
			XM_D("proc_cmd:config exit unlock node %d index %d socket %d\r\n",pnode->id,pxm->xm_index,pxm->xm_socket_client);
#endif
			pthread_mutex_unlock(&pxm->mutex);
		}
		pxm->xm_seting=0;
	}else{ 
#if DEBUG_CMD
		XM_D("proc_cmd:Ret %p %s\r\n",pnode->xm_cmd->set,pnode->xm_cmd->cmd);
#endif
		pnode->errorid=XM_SUCCESS;
		if(pxm->xm_exit==0){
			if(pnode->xm_cmd->set != NULL){
				pnode->errorid=pnode->xm_cmd->set(pxm,pnode,NULL,pnode->argc,pnode->xm_at.getparam);
			}
			if(!pnode->xm_sendready){
				pnode->errorid=XM_ERROR_WAIT_MOER;
			}
		}else{
			pnode->errorid=XM_ERROR_VAIL;
		}
		pxm->xm_seting=0;
#if DEBUG_THREAD
		XM_D("proc_cmd:other unlock node %d index %d socket %d\r\n",pnode->id,pxm->xm_index,pxm->xm_socket_client);
#endif
		pthread_mutex_unlock(&pxm->mutex);
	}
#if DEBUG_CMD
	XM_D("proc_cmd:Finish\r\n");
#endif
}

void execATCommand(XM_PROTOCOL *pxm,XM_NODE *pnode,int argc)
{
	int k=0,i = 0,j=0,funcNum;
	XM_AT_FUN *pat_cmd;
	pnode->errorid=XM_ERROR_CMD_NOT_SUPPORT;
#if DEBUG_AT
	XM_D("exec at:cmd  %d argc %d\r\n",strlen(pnode->xm_at.getcmd),argc);
#endif

#if DEBUG_AT
	XM_D("exec at:cmd group %d\r\n",(int)sizeof(xm_at_list)/sizeof(xm_at_list[0]));
#endif
	pnode->xm_cmd=NULL;
#if XM_WITH_ID
	memset(pnode->xm_id,'\0',XM_ID_MAX);
	snprintf(pnode->xm_id,XM_ID_MAX,"%s",pnode->xm_at.getparam[0]);
#endif
	for(k=0;k<sizeof(xm_at_list)/sizeof(xm_at_list[0]);k++){
		pat_cmd = xm_at_list[k].funlist;
		funcNum = xm_at_list[k].listnum;
#if DEBUG_AT
	//	XM_D("exec at:%d %d %p\r\n",k,funcNum,pat_cmd);
#endif		
		for(i=0;i < funcNum; i++){
#if DEBUG_AT
		//	XM_D("exec at:%d %s %d %s\r\n",strlen(pat_cmd->cmd),pat_cmd->cmd,strlen(pnode->xm_at.getcmd),pnode->xm_at.getcmd);
#endif
			if(!strncmp(pat_cmd->cmd,pnode->xm_at.getcmd,strlen(pat_cmd->cmd)>strlen(pnode->xm_at.getcmd)?(int)strlen(pat_cmd->cmd):(int)strlen(pnode->xm_at.getcmd)))
			{
#if DEBUG_AT
				XM_D("execATCommand: %d %d\r\n",pat_cmd->type,argc);
#endif
				pnode->errorid=XM_SUCCESS;
				pnode->xm_cmd=pat_cmd;
				pnode->argc=argc;

				if (k>0 && k<(sizeof(xm_at_list)/sizeof(xm_at_list[0])-1))
					pxm->xm_addres=xm_at_list[k].type;								
				//add by mujian for temp 205;when use new architect(send String F4F5.. directly),del codes below;
				if (pnode->xm_cmd->parameter!=NULL ){
					if (((pnode->xm_cmd->parameter->set_cmd>200 )|| pnode->xm_cmd->parameter->set_cmd == 1 || (pnode->xm_cmd->parameter->query_cmd>200))&&pxm->xm_sub_frame==255){//210 change to 200
					#if DEBUG_AT
					XM_D("execATCommand!!!: %d %d\r\n",pat_cmd->type,argc);
					
					for (j=1;j<argc;j++)
						{
						XM_D("params[%d]=%d \r\n",j,(uchar)atoi(pnode->xm_at.getparam[j]));
						}
					#endif
					pxm->xm_frame=(uchar)atoi(pnode->xm_at.getparam[argc-2]);
					pxm->xm_sub_frame=(uchar)atoi(pnode->xm_at.getparam[argc-1]);
					// modified by Tao He
					pnode->argc -=2;
					pxm->frame_flag = 1;
					#if DEBUG_CMD
					XM_D("execATCommand:!pxm->xm_frame=%d pxm->xm_sub_frame=%d argc=%d\r\n",pxm->xm_frame,pxm->xm_sub_frame,argc);
					#endif
					}}
				//add by mujian for temp 205;when use new architect,del codes below;
				goto cmd_exit;
			}else{
				pat_cmd++;
			}
		}
#if DEBUG_AT
		XM_D("execATCommand:next %d\r\n",k);
#endif
	}
cmd_exit:	
	return ;
}

/*
 * 函数作用：获取AT+“”后的命令
 * 函数输入：AT命令字符串,提取到的命令字符串指针 
 *           命令存放于 char *gcmd,
 *           参数存放于 char (*gparam)[MAX_CMD_STR_NUM]
 * 
 * 函数返回：*gparam中参数的个数 
 */
int cmdAnalyze(XM_PROTOCOL *pxm,XM_NODE *pnode)
{
	char *cmdStr=pnode->xm_at.XM_At_Buffer;
	int paramIdx = 0;
#if DEBUG_AT
	 XM_D("analyze:%s\r\n",pnode->xm_at.XM_At_Buffer); 
#endif	 /*单条指令解析后参数*/ 
	 if(*cmdStr == 'A' && *(cmdStr + 1) == 'T')
	 {
		 while(*cmdStr != '\0')
		 {
			switch(*cmdStr)
			{
				case '+':
				{
					pnode->xm_at.getcmd=++cmdStr;
					while(*cmdStr != '=' && *cmdStr != '\r' && *cmdStr != '\n' && *cmdStr != '\0')
					{
#if DEBUG_AT
						XM_D("cmdStr:%c\r\n",*cmdStr);
#endif
						cmdStr++;

					}	
#if DEBUG_AT
					XM_D("gcmd:%s\r\n",pnode->xm_at.getcmd);
#endif
					break;
				}	
				case '=':/*full through*/
				case ',':
				{
					*cmdStr='\0';

					pnode->xm_at.getparam[paramIdx++]=++cmdStr;
#if DEBUG_AT
					XM_D("gparam:%d %s\r\n",paramIdx,pnode->xm_at.getparam[paramIdx-1]);
#endif
					break;
				}
				default:
					cmdStr++;
			}/*end of switch*/ 
			
	 	}/*end of while*/
	 }
	 /* 大小写转换 */
	 //cmdStr=pnode->xm_at.getcmd;
	 //while(*cmdStr!='\0'){
		//if(*cmdStr>='a' && *cmdStr <='z'){
			//*cmdStr=*cmdStr+('A'-'a');
		//}
	//}
 	return paramIdx;
}

/*
函数作用：按照AT格式分割命令字符串 ，并在命令末尾添加'\0'
函数输入：新输入的长字符串
函数输出：无 
*/

void strDividing(XM_PROTOCOL *pxm,XM_NODE *pnode,char * str,int strcnt){
	int strIdx = 0;
	int paraNum = 0;
	//int cmdlen=0;
#if DEBUG_RS
	XM_D("cmd:%d %d %s\r\n",strlen(str),strcnt,str);
#endif
	memset(pnode->xm_at.XM_At_Buffer,'\0',XM_MAX_BUF);	
	if(strcnt <=XM_AT_MIN ){
		XM_E("at cmd too short %d\r\n",strcnt);
		pnode->errorid=XM_ERROR_CMD_NOT_SUPPORT;
		return ;
	}
	/*起始处理*/
	while((strcnt >2) && (*str != 'A' || *(str + 1) != 'T')) /*首位不是 AT开头*/
	{
		//XM_D("cmd:%c %c %d %s\r\n",*str,*(str + 1),strcnt,str);
		strcnt--;
		str++;
	};
#if DEBUG_RS
	XM_D("cmd:%d %s\r\n",strcnt,str);
#endif
	if(strcnt <=XM_AT_MIN ){
		XM_E("at cmd too short %d\r\n",strcnt);
		pnode->errorid=XM_ERROR_CMD_NOT_SUPPORT;
		return ;
	}	
	/*非特殊处理*/ 
	while(*str  != '\0' && *str  != '\r' && *str  != '\n' && strcnt != 0 && strIdx < XM_MAX_BUF)
	{
		/* 过滤空格 */
		if(*str  != ' '){			
			pnode->xm_at.XM_At_Buffer[strIdx++] = *str;
		}
		strcnt--;str++;
	}
	if(strIdx <=XM_AT_MIN ){
		XM_E("at cmd data too short %d\r\n",strcnt);
		pnode->errorid=XM_ERROR_CMD_NOT_SUPPORT;
		return ;
	}
#if DEBUG_CMD
	XM_D("strDividing:%s %d\r\n",pnode->xm_at.XM_At_Buffer,strIdx);
#endif
	pnode->xm_at.XM_At_Buffer[strIdx] = '\0';
	paraNum = cmdAnalyze(pxm,pnode);
	execATCommand(pxm,pnode,paraNum);
}
XM_Command * getcommand(uchar address,uchar cmd,uchar sub,char *pbuf,int len){
	XM_AT_FUN *pat_cmd;
	int funcNum,k,i,j,MaxOffset=len*8,isHavePre=0,nMask;	
#if DEBUG_CMD
	printf_buf("getcommand",(uchar *)pbuf,len);
#endif
	for(k=0;k<sizeof(xm_at_list)/sizeof(xm_at_list[0]);k++){
#if DEBUG_CMD
		XM_D("getcommand:command %d %p %d %d\r\n", k,xm_at_list[k].funlist,xm_at_list[k].listnum,xm_at_list[k].type);
#endif
		if(xm_at_list[k].funlist && xm_at_list[k].type==address){
			pat_cmd = xm_at_list[k].funlist;
			funcNum = xm_at_list[k].listnum;			
			for(i=0;i<funcNum;i++){
				if(pat_cmd[i].parameter->set_cmd==cmd && pat_cmd[i].parameter->set_sub==sub && pat_cmd[i].parameter){
					isHavePre=0;
					for(j=0;j<pat_cmd[i].parameter->send_num;j++){
#if DEBUG_CMD
						XM_D("getcommand:parameter c %s p %d o %d i %d\r\n", pat_cmd[i].cmd,pat_cmd[i].parameter->send[j].preset,pat_cmd[i].parameter->send[j].offset,j);
#endif
						if(pat_cmd[i].parameter->send[j].preset==1 && pat_cmd[i].parameter->send[j].offset<MaxOffset ){
#if DEBUG_CMD
							XM_D("getcommand:offset %d %d\r\n", pat_cmd[i].parameter->send[j].offset,pbuf[pat_cmd[i].parameter->send[j].offset/8]);
#endif
							isHavePre=1;
							if(pbuf[pat_cmd[i].parameter->send[j].offset/8] & (1<<(7-pat_cmd[i].parameter->send[j].offset%8))){
#if DEBUG_CMD
								XM_D("getcommand:%s\r\n", pat_cmd[i].cmd);
#endif
								return pat_cmd[i].parameter;
							}
						}
					}
#if DEBUG_CMD
					XM_D("getcommand:Pre %d send num %d\r\n", isHavePre,pat_cmd[i].parameter->send_num);
#endif
					if(!isHavePre && pat_cmd[i].parameter->send_num){
						/*需要判断相应位有数据*/
						for(j=0;j<pat_cmd[i].parameter->send_num;j++){
							if(pat_cmd[i].parameter->send[j].preset!=1 && pat_cmd[i].parameter->send[j].offset<MaxOffset ){
								nMask=(0xff>>(8-pat_cmd[i].parameter->send[j].len))<<(7-pat_cmd[i].parameter->send[j].offset%8);
								if(pbuf[pat_cmd[i].parameter->send[j].offset/8] & (1<<(7-pat_cmd[i].parameter->send[j].offset%8))){
#if DEBUG_CMD
									XM_D("getcommand:not pre set %s\r\n", pat_cmd[i].cmd);
#endif
									return pat_cmd[i].parameter;			
								}
							}
						}
					}
				}
			}
		}
	}
	return NULL;
}
