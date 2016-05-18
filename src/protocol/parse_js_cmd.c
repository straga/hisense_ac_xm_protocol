#include "common.h"
#include "js_type.h"

#define BYTLEN 8
#define ESCAPE_CHAR 0xf4


#define E_CMD_MAP 1
#define E_NO_SETLIST 2
int BIN2HEX(char * p_binstr,int bin_len,char * p_hexstr);

//------------------------------------------------------------------------

#if 0
static key_val_t kt_mapList[]={
	{"false",0},
	{"true",1},

	// add member above
	END_KEY_VAL
};
#endif

static pos_t tOn[]={	/*定时设置值*/
	{NULL,70,6,0,0},
	END_POS
};

static pos_t RTTimeSet[]={	/*实时时钟设置参数*/
	{NULL,87,1,0,1},	//实时分钟需要设置
	{NULL,85,6,0,0},	//实时分钟值
	END_POS
};

static pos_t RTPowerOn[]={	/*实时定时参数*/
	{NULL,93,1,0,1},	//实时开机小时需要设置预设为1
	{NULL,92,5,0,0},	//实时小时的小时值设置(0~23)
	{NULL,103,1,0,1},	//实时分钟设置值预设为1
	{NULL,101,6,0,0},	//实时分钟设置值(0~59)
	END_POS
};
static pos_t RTPowerOff[]={	/*实时定时参数*/
	{NULL,109,1,0,1},	//实时关机小时需要设置预设为1
	{NULL,108,5,0,0},	//实时小时的小时值设置(0~23)
	{NULL,119,1,0,1},	//实时分钟设置值预设为1
	{NULL,117,6,0,0},	//实时分钟设置值(0~59)
	END_POS
};

static cmd_map_t set_cmd[]={
	{"SoundSet",	
		NULL,
		{NULL,61,1,T_HEX,0},
		{NULL}
	},
	{"Power",	
		NULL,
		{NULL,20,1,T_STR,0},
		{NULL,21,1,T_HEX,1}
	},
	
	{"EHeating",
		NULL,
		{NULL,134,1,0,0},
		{NULL,135,1,0,1}
	},
	{"Turbo",
		NULL,
		{NULL,140,1,0,0},
		{NULL,141,1,0,1}
	},
	{"WindSpeed",
		NULL,
		{NULL,6,7,0,0},
		{NULL,7,1,0,1}
	},
	{"ECO",
		NULL,
		{NULL,136,1,0,0},
		{NULL,137,1,0,1}
	},
	{"Light",
		NULL,
		{NULL,162,1,0,0},
		{NULL,163,1,0,1}
	},
	{"SetTemp",
		NULL,
		{NULL,30,7,0,0},
		{NULL,31,1,0,1}
	},
	
	{"Mode",
		NULL,
		{NULL,18,3,0,0},
		{NULL,19,1,0,1}
	},

	{"HAirDeflector",
		NULL,
		{NULL,130,1,0,0},
		{NULL,131,1,0,1}
	},
	{"VAirDeflector",
		NULL,
		{NULL,126,3,0,0},
		{NULL,127,1,0,1}
	},
	{"VAirRunStop",
		NULL,
		{NULL,128,1,0,0},
		{NULL,129,1,0,1}
	},
	
	{"Mode",
		NULL,
		{NULL,18,3,0,0},
		{NULL,19,1,0,1}
	},
	
	{"Sleep",
		NULL,
		{NULL,14,7,0,0},
		{NULL,15,1,0,1}
	},
	{"RTSet",				/*实时时钟设置*/
		RTTimeSet,			/*其他设置的参数*/
		{NULL,76,5,0,0},	//小时值
		{NULL,79,1,0,1} 	/*小时设置标志*/
	},
	{"RTPowerOn",			/*实时开机*/
		RTPowerOn,				/*设置的参数*/
		{NULL,94,1,0,0},	/*取消开机还是设置开机*/
		{NULL,95,1,0,1} 	/*本次是否需要设置*/
	},
	{"RTPowerOff",			/*实时关机*/
		RTPowerOff,				/*设置的参数*/
		{NULL,110,1,0,0},	/*是否取消，设置*/
		{NULL,111,1,0,1} 	/*本次是否需要设置*/
	},
	/*普通定时功能需要看空调当前运行状态*/
	{"Timing",
		tOn,				/*设置的参数*/
		{NULL,64,1,0,0},	/*是否取消，设置*/
		{NULL,71,1,0,1}		/*本次是否需要设置*/
	},
	// add member above
	END_CMD_MAP
};

static cmd_map_t query_cmd[]={
	{"GetAll",	
		NULL,
		{NULL,7,8,0,0},	/*手动或自动*/
		{NULL}
	},
	
	// add member above
	END_CMD_MAP
};

pro_cmd_t kt_cmd[]={
	{"KTSET",set_cmd,101,0,30,0,0x40,0},
	{"KTQUERY",query_cmd,102,0,1,62,0x40,0},

	//add member above
	END_PRO_CMD
};

pro_t produceList[]={
	{"KT",kt_cmd,0x01},

	// add product above		
	END_PRO
};


static pro_cmd_t *get_product_cmd(char *opt_cmd,pro_cmd_t *list){
	for(;list && list->opt_cmd;list++){
		if(0==memcmp(opt_cmd,list->opt_cmd,strlen(opt_cmd)+1))
			return list;
	}
	xlf_debug("Not find opt_cmd \n");
	return NULL;
}

static u8 match_text_list(char *str,key_val_t *text){
	for(;text && text->key;text++){
		if(memcmp(str,text->key,strlen(str)+1)==0)
			return text->val;
	}
	xlf_debug("did`t find text map %s \n",str);
	return 0;
}


static inline void set_val(u8 * const msg_start,u8 val ,u16 offset, u16 len){
	u8 bitOffset,nMask;
	u8 byte_pos;
	byte_pos =offset >>3;	// equal to offset/8
	bitOffset=7-(offset &7); // equal to offset %8
	nMask=(0xff>>(8-(len &7)))<<bitOffset;
	msg_start[byte_pos] |= nMask &(val <<bitOffset);
	xlf_debug("set CMD data: val =%d nByte =%d nBit =%d nMask=%#x\n",val,byte_pos+1,bitOffset,nMask);
}

/*
 * return 0,此位置不接受设置
 */
static u8 match_js_val(u8 * const msg_start,cJSON* item,pos_t * pos){
	u8 val=0;
	if(0==pos->takeLen) return 0;
	if(pos->preset){
		set_val(msg_start,pos->preset,pos->offset,pos->takeLen);
		return 0;
	}
	if(item->type == cJSON_Number){
		val=item->valueint;
		set_val(msg_start,val,pos->offset,pos->takeLen);
	}else if(item->type == cJSON_String){
		if(pos->takeLen<=8){
//			xlf_debug("takeLen=%d \n",pos->takeLen);
			if(pos->text){	
				val=match_text_list(item->valuestring,pos->text);
			}else{
				val=atoi(item->valuestring);
			}
			set_val(msg_start,val,pos->offset,pos->takeLen);
		}else{
			if(pos->type_value == T_STR){

			}
			else if(pos->type_value == T_BCD){

			}
		}
	}
	return 1;
}
static  void set_param_val(u8 * const msg_start,cJSON* item,cmd_map_t * map){
	pos_t *extral=NULL;
	// fill flag
	if(map->flag.preset){
		set_val(msg_start,map->flag.preset,map->flag.offset,map->flag.takeLen);
	}
	// fill set
	if(item->type == cJSON_Number ||item->type == cJSON_String ){
		match_js_val(msg_start,item,&map->set);
	}else if(item->type == cJSON_Array){	//has extral parameter
		item=item->child;	//先匹配第一个到set
		if(0==map->flag.preset){	//说明flag是接受配置的
			if(item && match_js_val(msg_start,item,&map->flag))
				item=item->next;
		}
		if(item && match_js_val(msg_start,item,&map->set))
			item=item->next;
		extral=map->set_extral;
		while(item && extral && extral->offset){
			if(match_js_val(msg_start,item,extral))
				item=item->next;
			extral++;	//next
		}
	}else{// type not support
		xlf_ebug("%s value type wrong\r\n",item->string);
	}
}

/*
 * return :
 * -1 failed ,>=0 the cmd execute number
 * -2 JS ITEM "SETLIST" worong
 *
 */
static int create_msg_body(u8 * const msg_start,cJSON* root,cmd_map_t * const cmd_map){
	char *cmd_str=NULL;
	// 下面的c这个变量其实可以不用，直接用tmp进行操作
	cJSON *c,*tmp=NULL;
	cmd_map_t *map;
	u8 num=0;
	if(!cmd_map){
		xlf_debug("err:get cmd_map is null\r\n");
		return -E_CMD_MAP;
	}
#ifdef DEBUG
	cmd_str=cJSON_GetObjectItem(root,"ID")->valuestring;
	xlf_debug("get SSID %s\r\n",cmd_str);
#endif
	tmp=cJSON_GetObjectItem(root,"SETLIST");
	if((!tmp) || (tmp->type !=cJSON_Object)){
		xlf_ebug("\"SETLIST\" BAD !!!\n");
		return -E_NO_SETLIST;
	}
	xlf_debug("Find SETLIST\r\n");
	c=tmp->child;
	while(c){
		cmd_str=c->string;
		for(map=cmd_map;map&&map->cmd;map++){
			// strlen +1 is to check if the cmd is totally the same
			if(0==memcmp(map->cmd,cmd_str,strlen(map->cmd)+1)){
				num++;
				xlf_debug("\r\nCMD: %s\r\n",cmd_str);
				set_param_val(msg_start,c,map);
				break;
			}
		}
		#ifdef DEBUG
		if(NULL==map->cmd)
			xlf_debug("CMD para not support: %s\r\n",cmd_str);
		#endif
		c=c->next;
	}
	xlf_debug("\r\n");
	xlf_debug("get set parameter num %d\r\n",num);
	return num;
}
u16 get_ckeck_sum(u8 *pStart,u8 len){	
	u16 sum=0;	
	while(len){		
		sum += *pStart++;
		len--;	
	}	
	return sum;
}

#if 0
static void move_data(u8 * buf,int len,int offset){
	u8 * pEnd;
	pEnd=buf+len;
	while((pEnd-offset)>=buf){
		*pEnd=*(pEnd-offset);
		pEnd--;
	}
}
#endif
/*
 * 返回0，size overflow
*/
static u8 extend_buff(u8 *start,u8 len){
	u8 allLen=len;
	u8 i;	
	start +=2;	// escape f4 f5
	len-=2;
	// len>2 means don`t check the last two bytes 0xf4 0xfb
	for(;len>2;len--,start++){
		if(*start == ESCAPE_CHAR){
			allLen++;
			if(allLen >MAX_ARR_SIZE)
				return 0;
			i=len;
			while(i){
				start[i]=start[i-1];
				i--;
			}
			start++;
		}
	}
	return allLen;
}

int js_build_cmd(char *sendbuf,char *buf,int device_type,int device_address,int moblie_type,int moblie_address)
{
	u8 *msg_start=NULL;
	char *str=NULL;
	cJSON* root=NULL,*tmp=NULL;
	pro_t *product=NULL;
	pro_cmd_t *pro_cmd=NULL;
	cmd_map_t *cmd_map=NULL;
	int retlen;
	u16 check_sum=0;
	u8 frame_buf[MAX_ARR_SIZE];
	memset(frame_buf,0,sizeof(frame_buf));
	if(buf==NULL || *buf==0) {
		snprintf(sendbuf,1024,"null CMD give me\r\n");	
		return strlen(sendbuf);
	}
	if(!memcmp(buf,"AT+WF",strlen("AT+WF"))|| !memcmp(buf,"AT+WHO",strlen("AT+WHO")) || !memcmp(buf,"AT+XM",strlen("AT+AT"))){
		xlf_debug("get WIFI CMD\r\n");
		snprintf(sendbuf,1024,"%s",buf);
		return strlen(sendbuf);
	}
	// Step 1: find product
	for(product=produceList;product->cmdList;product++){
		if(device_type == product->deviceType) break;
	}
	if(NULL==product->cmdList){
		xlf_ebug("product type: %d not found\n",device_type);
		snprintf(sendbuf,1024,"product type: %d not found \r\n",device_type);
		return strlen(sendbuf);	
	}
	xlf_debug("find product:%s\n",product->proName);
	
	frame_buf[0]=0xf4;
	frame_buf[1]=0xf5;
	frame_buf[7]=device_type;
	frame_buf[8]=device_address;
	frame_buf[9]=moblie_type;
	frame_buf[10]=moblie_address;
	
	root = cJSON_Parse(buf);	//注意要释放
	if( !root) {
		xlf_ebug("Json Frame Format wrong !!!\r\nthe json:\r\n%s\n",buf);
		snprintf(sendbuf,1024,"Json Frame Format wrong \r\n");
		return strlen(sendbuf);
	}//check root
	// step 2 : get CMD
	tmp=cJSON_GetObjectItem(root,"CMD");
	if((!tmp) || (!tmp->valuestring) ||(tmp->type !=cJSON_String)){
		snprintf(sendbuf,1024,"\"CMD\" not found\r\n");
		xlf_ebug("%s",sendbuf);
		cJSON_Delete(root);
		return strlen(sendbuf);

	}
	str=tmp->valuestring;
	xlf_debug("get CMD %s\n",str);
	
	// setp 3: find pro_cmd
	pro_cmd = get_product_cmd(str,product->cmdList);
	if(!pro_cmd){
		snprintf(sendbuf,1024,"\"pro_cmd\"not found\r\n");
		xlf_ebug("%s",sendbuf);
		cJSON_Delete(root);
		return strlen(sendbuf);
	}
	xlf_debug("Find pro_cmd\r\n");
	// set link_flag
	frame_buf[3]=pro_cmd->link_flag;

//	if(0x40 == pro_cmd->link_flag){
		frame_buf[4]=pro_cmd->set_num + 11;
		frame_buf[13]=pro_cmd->cmd_type;
		frame_buf[14]=pro_cmd->cmd_subtype;
		msg_start =frame_buf+16;
//	}
	cmd_map=pro_cmd->cmd_map;
	retlen=create_msg_body(msg_start,root,cmd_map);
	if(retlen <= 0){
		snprintf(sendbuf,1024,"ERROR:library STURCT err is %d\r\n",retlen);
		xlf_ebug("%s",sendbuf);
		cJSON_Delete(root);
		return strlen(sendbuf);
	}
	// free memory
	cJSON_Delete(root);

	// get check sum
	check_sum=get_ckeck_sum(frame_buf+2,frame_buf[4]+3);
	msg_start[pro_cmd->set_num]=check_sum >>8;
	msg_start[pro_cmd->set_num+1]=check_sum & 0xff;
	msg_start[pro_cmd->set_num+2]=0xf4;
	msg_start[pro_cmd->set_num+3]=0xfb;
	
	retlen=frame_buf[4]+9;
	retlen=extend_buff(frame_buf,retlen);
	if(retlen==0){
		snprintf(sendbuf,1024,"ERROR:SIZE OVER FLOW\r\n");
		xlf_ebug("%s",sendbuf);	
		return strlen(sendbuf);
	}
	
	retlen= BIN2HEX((char *)frame_buf,retlen,sendbuf);
	if(retlen){
		sendbuf[retlen]='\r';
		sendbuf[retlen+1]='\n';
		retlen+=2;
	}
	return retlen;
}


