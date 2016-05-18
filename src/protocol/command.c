/*
 * Copyright 2009-2011 Cedric Priscal
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include	"xmlog.h"
#include	"xm_type.h"
#include	"message.h"
#include	"hisense.h"
#include	"air-condition_msg.h"
#include	"command.h"
#include    "protocol.h"


uchar ProcCmd(XM_PROTOCOL *pxm,uchar argc,char **argv){
	uchar ret=XM_ERROR_NOT_INIT;	
	if(pxm && argc==2){
		statusInit(pxm);
#if DEBUG_CMD
		XM_D("ProcCmd:cmd %d sub %d\r\n",pxm->sendcmd,pxm->sendsub);
#endif
		ret=New_Msg_Head(pxm,(uchar *)pxm->XM_Status_Value,pxm->sendcmd,pxm->sendsub,(uchar *)argv[1],atoi(argv[0]));
		if(ret){
#if DEBUG_CMD
			XM_D("ProcCmd:Parse_Send len %d\r\n",ret);
#endif
			pxm->xm_send=Parse_Send(pxm->XM_Frame_Buffer,(uchar *)pxm->XM_Status_Value,ret,pxm->xm_addres_1,pxm->xm_addres_2,pxm->xm_addres_3,pxm->xm_addres_4,pxm->xm_addres_5,pxm->xm_addres_count,pxm->xm_addres_all,pxm->xm_addres_type,pxm->xm_addres_struct,pxm->xm_encryption_type,pxm->xm_crc_type,0,0,0,0,0,0);
#if DEBUG_CMD
			XM_D("ProcCmd:Parse_Send ret %d\r\n",pxm->xm_send);
#endif
			memset(pxm->XM_Status_Buffer,0,XM_MAX_BUF);
			if(pxm->xm_send){
				ret=XM_SUCCESS;				
			}else{
				ret=XM_ERROR_BUILD_PACKET_FAIL;
			}
		}else{
			XM_E("ProcCmd:cmd type error\r\n");
			ret=XM_ERROR_CMD_TYPE;
		}
#if DEBUG_CMD
		XM_D("ProcCmd:finish %d\r\n",ret);
#endif
	}
	return ret;	
}

