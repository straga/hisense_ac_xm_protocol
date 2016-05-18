#include<stdio.h>
#include"vanword.h"
#include"xm_type.h"




#define FRAME_ERROR_PRE 0x1000
#define FRAME_ERROR_SIZE_TOOLAGER 0x1
#define NETWORK_ERROR_PRE 0x2000
#define TRANSFER_ERROR_PRE 0x3000
#define CRC_ERROR_PRE 0x4000
#define END_ERROR_PRE 0x5000
#define HEAD_ERROR_PRE 0x6000
#define HEAD_ERROR_DISCONNECT 0x7000
#define PACKET_MAX_LEN 255
#define ERROR_MSG_TIME_OUT 0xb
#define ERROR_MSG_TIME_OUT_MAX 0xc
#define MSG_TIME_OUT_SEND_COUNT 10


typedef unsigned char *puchar;

typedef 	struct	__access_version{
			u8	ver1;
			u8	ver2;
			u8	ver3;
			u8	ver4;
}access_version;
#define	VER1		0x00
#define	VER2		0x00
#define	VER3		0x00
#define	VER4		0x03
typedef struct __common_frame_head{
	access_version	 version;
	u16	frame_len;
	struct ctl_id	id;
}common_frame_head,*pcommon_frame_head;

typedef struct	__small_frame_head{
	common_frame_head	hh;
	u32	link_no;
}small_frame_head,*psmall_frame_head;

typedef struct	__big_frame_head{
	common_frame_head	hh;
	u16	link_no_len;
	u8	link_no;
}big_frame_head,*pbig_frame_head;
typedef union	 __dev_code_len{
	struct	__l_dev_code_len{
	u8	len_high;
	u8	len_low;
	}l_dev_code_len;
	u16	len;
}dev_code_len,*pdev_code_len;
#define	len_high	l_dev_code_len.len_high
#define	len_low		l_dev_code_len.len_low
typedef struct __p0_version_len{
		u8	high;
		u8	low;
}p0_version_len,*pp0_version_len;
typedef struct p0_version{
		u8	high;
		u8	low;

}p0_version,*pp0_version;
typedef struct	 __frame_magic{
		u8	high;
		u8	low;
}frame_magic,*pframe_magic;

typedef union __new_frame_crc{
	struct	__l_frame_crc{
		u8	crc_high;
		u8	crc_low;
	}l_frame_crc;
	u16	crc;
}new_frame_crc,*pnew_frame_crc;	 
#define crc_high	l_frame_crc.crc_high
#define	crc_low		l_frame_crc.crc_low

#pragma pack()
int BIN2HEX(char *  p_binstr, int bin_len, char * p_hexstr);
int HEX2BIN(char *  p_hexstr, char * p_binstr);

#undef DBG
void	upload_data_with_dev_code(pcommon_frame_head phd,p0_t *pbd);
void	parse_p0(pcommon_frame_head phd,u8 p0_off,p0_t *pbd);
int vanw_build_allstr(char *sendbuf,build_info_t* pinfo){
	puchar	pbuf=NULL;
	uchar		tmp_buf[1024];
	u8		off=0;
	u16		ctrl_id;
	pbuf=tmp_buf;
	pcommon_frame_head	pfh=NULL;
	psmall_frame_head	psfh=NULL;
	pbig_frame_head	pbfh=NULL;

	pfh=(pcommon_frame_head)pbuf;
	pfh->version.ver1=VER1;
	pfh->version.ver2=VER2;
	pfh->version.ver3=VER3;
	pfh->version.ver4=VER4;
	
	ctrl_id=(pinfo->id.dataH<<8)|(pinfo->id.dataL);
	#if VANW_DEBUG
	printf("%02x %02x\n",pinfo->id.dataH,pinfo->id.dataL);
	#endif
	switch(ctrl_id){
		case  0x0301:
					  psfh=(psmall_frame_head)pbuf;
						off=4+sizeof(pfh->id);
						psfh->link_no=htonl(pinfo->conNUM);
						
						#if VANW_DEBUG
						printf("%x\n",psfh->link_no);
						#endif
						break;
		case 0x0302:
					pbfh=(pbig_frame_head)pbuf;
					xlf_debug("cmd_id with %04x have not support\r\n",ctrl_id);
					return 0;
					break;
		case 0x0306:
						off=0+sizeof(pfh->id);
					xlf_debug("cmd_id with %04x have not support\r\n",ctrl_id);
					break;
		default:
					xlf_debug("cmd_id with %04x have not support\r\n",ctrl_id);
				break;
			
	} 
	pfh->id=pinfo->id;
	pfh->frame_len=htons(off+pinfo->len);
	pbuf=(puchar)(&pfh->id)+off;
	

	memcpy(pbuf,pinfo->bodyHex,pinfo->len);
	pbuf+=pinfo->len;
	return BIN2HEX((char *)tmp_buf,pbuf-tmp_buf,(char *)sendbuf);
}
void vanw_parse_head(p0_t *pbd,char *hexstr){
		uchar	bin_str[1024];
		puchar	pbuf=NULL;	
		u8 	size;
		u8	max_size;
		int i;
		u32	*pu32=NULL;
		pcommon_frame_head phd=NULL;
		u16	ctrl_id;
		
		max_size=PACKET_MAX_LEN-sizeof(common_frame_head);

	  	size=HEX2BIN((char *)hexstr,(char *)bin_str);
		pbuf=bin_str;
		if( size<PACKET_MIN_LEN){
			pbd->error=FRAME_ERROR_PRE;
				xlf_debug("%s","packet len is too small\n");
				#if VANW_DEBUG
				for(i=0;i<size;i++){
					printf("%02x ",bin_str[i]);
				}
					printf("\n");
				#endif

				return ;
		}
/**
 * search the access version
 */
		for(i=0;i<size;i++){
			pu32=(u32 *)&pbuf[i];
			if(htonl(*pu32)==0x03){
					break;
			}
		}/*for*/
		if(i>=size){
			pbd->error=FRAME_ERROR_PRE;
			xlf_debug("can not find acess version 0x00000003\r\n");
			return;
		}
		size=size-i;
		pbuf=&pbuf[i];
	

	if( size<PACKET_MIN_LEN){
			pbd->error=FRAME_ERROR_PRE;
			xlf_debug("%s","packet len is too small\n");
				#if VANW_DEBUG
				for(;i<i+size;i++){
					printf("%02x ",bin_str[i]);
				}
				printf("\n");
				#endif
				return ;
		}
/*find	the 0xAAAA which is the  frame magic */
		phd=(pcommon_frame_head)pbuf;
		ctrl_id=(phd->id.dataH<<8)|(phd->id.dataL);
		switch(ctrl_id){
			case 0x0305:
				parse_p0(phd,sizeof(phd->id),pbd);
						break;
			case 0x0307:
				upload_data_with_dev_code(phd,pbd);
					break;
			default:
					pbd->error=FRAME_ERROR_CTRLID;
					xlf_debug("have  not support comunication id 0x%02x-0x%02x\n",phd->id.dataH,phd->id.dataL);

		}

		return ;
		
}

void	parse_p0(pcommon_frame_head phd,u8 p0_off,p0_t *pbd){
		puchar	pbuf=NULL;
		pframe_magic pfma=NULL;
		u8	p0_len=0;
		pnew_frame_crc pcrc_data;
		new_frame_crc crc_cmp;
	

		pbd->id=phd->id;

		/*
 *		trying finding  the 0xAAAA which is the frame magic
 */
		pbuf=(puchar)&phd->id+p0_off;
		pfma=(pframe_magic)pbuf;
		if(!(pfma->high==0xAA&&
			 pfma->low==0xAA)){
			pbd->error=HEAD_ERROR_PRE;
			xlf_debug("can not find frame head mark 0xAAAA,the real mark is,0x%02x-0x%02x\n",pfma->high,pfma->low);
			return ;
		}

	/*
 *	check crc result
 */
	p0_len=htons(phd->frame_len)-p0_off-sizeof(new_frame_crc);
	pbuf+=p0_len;
	pcrc_data=(pnew_frame_crc)pbuf;
	xlf_crc((puchar)pfma,p0_len,(struct frame_crc *)&crc_cmp);
	if(crc_cmp.crc!=pcrc_data->crc){
			pbd->error=CRC_ERROR_PRE;
			xlf_debug("Verification_frame_crc:0x%x 0x%x pakcet_frame_crc:0x%x 0x%x\r\n",crc_cmp.crc_high,crc_cmp.crc_low,pcrc_data->crc_high,pcrc_data->crc_low);
			return;
	}
/**
 *	evertthing goes well
 */
	pbd->len=p0_len;
	memcpy(pbd->p0_data,(puchar)pfma,p0_len);
}


void	upload_data_with_dev_code(pcommon_frame_head phd,p0_t *pbd){
			pdev_code_len	p_len=NULL;			
			pp0_version_len	pv_len=NULL;
			pp0_version	pv=NULL;
			puchar	pbuf=NULL;
			puchar  pcode=NULL;
			
			pbd->id=phd->id;
	
			pbuf=(puchar)&phd->id;
			pbuf+=sizeof(phd->id);
			p_len=(pdev_code_len)pbuf;

			pbuf+=sizeof(dev_code_len);
			pcode=pbuf;
		
			pbuf+=htons(p_len->len);
			pv_len=(pp0_version_len)pbuf;

			pbuf+=sizeof(pp0_version_len);
			pv=(pp0_version)pbuf;
		
			pbuf+=sizeof(p0_version);

			pbd->headDataLen=htons(p_len->len);
			memcpy(pbd->p0_data,pcode,pbd->headDataLen);
}
