#include	"xmlog.h"
#include	"xm_type.h"
#include    "protocol.h"

extern XM_AT_FUN at_cmd_kt[];
extern XM_AT_FUN at_cmd_kl[];
extern XM_AT_FUN at_cmd_jh[];
extern XM_AT_FUN at_cmd_cs[];
extern XM_AT_FUN at_cmd_qr[];
extern XM_AT_FUN at_cmd[];
extern XM_AT_FUN at_cmd_oven[];
extern XM_AT_FUN at_cmd_rsq[];
extern XM_AT_FUN at_cmd_rqz[];
struct para_desc{
	int offset;
	char *desc;
};
struct para_desc kt_set[]={
		{6,"风量[auto/strong/middle/weak]"},
		{14,"睡眠[off/aged/younger/child/general]"},
		{18,"模式[heat/auto/cool/dehumidify/blow]"},
		{20,"开机[0/1]"},		
		{22,"风向[0/1]"},
		{30,"设置温度[-64/64]"},
		{38,"设置湿度[0-100]"},
		{47,"体感室内温度[-64/64]"},
		{52,"体感室内温度补偿[0-32]"},
		{54,"体感控制[0/1]"},
		{59,"自动工作模式和除湿模式的温度补偿[0-16]"},
		{61,"提示声[0/1]"},
		{62,"华氏/摄氏温度显示设置[0/1]"},
		{70,"普通定时开关机[0.5h-23h]"},
		{76,"实时时钟的小时值[0-24]"},
		{85,"实时时钟的分钟值[0-60]"},
		{94,"实时开机控制[0/1]"},
		{92,"实时开机小时值[0-24]"},
		{101,"实时开机分钟值[0-60]"},
		{110,"实时关机控制[0/1]"},
		{108,"实时关机小时值[0-24]"},
		{117,"实时关机分钟值[0-60]"},
		{122,"除湿模式[auto/1#/2#/3#/4#/5#/6#/7#]"},
		{126,"上下风门模式[sweep/auto/1#/2#/3#/4#/5#/6#]"},
		{128,"上下风开停控制[0/1]"},
		{130,"左右风开停控制[0/1]"},
		{132,"自然风开停控制[0/1]"},
		{134,"电热[0/1]"},
		{138,"并用节电[0/1]"},
		{140,"高效[0/1]"},
		{142,"双模[0/1]"},
		{136,"节能[0/1]"},
		{144,"清新[0/1]"},
		{146,"换风[0/1]"},
		{148,"室内清洁[0/1]"},
		{150,"室外清洁[0/1]"},
		{152,"智慧眼[0/1]"},
		{154,"静音[0/1]"},
		{156,"语音[0/1]"},
		{158,"除烟[0/1]"},
		{160,"背景灯[0/1]"},
		{162,"显示屏发光[0/1]"},
		{164,"LED指示灯[0/1]"},
		{166,"室内外温度切换显示[0/1]"},
		{168,"室内过滤网清洁复位控制[0/1]"},
		{170,"左风摆[0/1]"},
		{172,"右风摆[0/1]"},
		{190,"显示屏亮度值0-255"}
};
struct para_desc kt_status[]={
		{6,"风量"},
		{14,"睡眠"},
		{19,"模式"},
		{20,"开机"},
		{22,"风向"},
		{31,"设置温度"},
		{55,"设置湿度"},
		{71,"体感室内温度"},
		{39,"室内实际温度"},
		{47,"室内盘管温度"},		
		{63,"室内实际湿度值"},
		{76,"体感室内温度补偿"},
		{78,"体感控制"},
		{83,"自动工作模式和除湿模式的温度补偿"},
		{86,"华氏/摄氏温度显示设置"},
		{94,"普通定时开关机"},
		{100,"实时时钟的小时值"},
		{109,"实时时钟的分钟值"},
		{118,"实时开机控制"},
		{116,"实时开机小时"},
		{125,"实时开机分钟"},
		{134,"实时关机控制"},
		{132,"实时关机小时"},
		{141,"实时关机分钟"},
		{146,"除湿模式"},
		{150,"上下风门模式"},
		{152,"上下风开停控制"},
		{153,"左右风开停控制"},
		{154,"自然风开停控制"},
		{155,"电热"},
		{156,"节能"},
		{157,"并用节电"},
		{158,"高效"},
		{159,"双模"},
		{160,"清新"},
		{161,"换风"},
		{162,"室内清洁"},
		{163,"室外清洁"},
		{164,"智慧眼"},
		{165,"静音"},
		{166,"语音"},
		{167,"除烟"},
		{168,"背景灯"},
		{169,"显示屏发光"},
		{170,"LED指示灯"},
		{171,"室内外温度切换显示"},
		{172,"室内过滤网清洁复位控制"},
		{173,"左风摆"},
		{174,"右风摆"},
		{175,"室内电量板"},
		{180,"本次命令之前是否有过红外遥控与按键控制过"},
		{181,"本次命令之前是否有过WIFI控制过"},
		{182,"空调正常机型与测试机型"},
		{183,"室内EEPROM在线升级"},
		{184,"室内温度传感器故障"},
		{185,"室内盘管温度传感器故障"},
		{186,"室内湿度传感器故障"},
		{187,"室内排水泵故障"},
		{188,"室内风机电机运转异常故障"},
		{189,"柜机格栅保护告警"},
		{190,"室内电压过零检测故障"},
		{191,"室内外通信故障"},
		{192,"室内控制板与显示板通信故障"},
		{193,"室内控制板与按键板通信故障"},
		{194,"WIFI控制板与室内控制板通信故障"},
		{195,"室内控制板与室内电量板通信故障"},
		{196,"室内控制板EEPROM出错"},
		{207,"运行频率"},
		{215,"目标频率"},
		{223,"发给驱动器的频率"},
		{231,"环境温度"},
		{239,"冷凝器温度"},
		{247,"排气温度"},
		{255,"目标排气温度"},
		{263,"室外电子膨胀阀开度"},
		{271,"UABH"},
		{279,"UABL"},
		{287,"UBCH"},
		{295,"UBCL"},
		{303,"UCAH"},
		{311,"UCAL"},
		{319,"IAB"},
		{327,"IBC"},
		{335,"CA"},
		{359,"IUV"},
		{343,"直流母线电压H"},
		{351,"直流母线电压L"},
		{363,"四通阀状态"},
		{364,"室外机实际工作状态"},
		{367,"风机运行状态"},
		{368,"室外机强制室内机风门位置"},
		{369,"室外机强制室内机风速"},
		{370,"室外机强制室内机停"},
		{371,"温控关机"},
		{372,"一拖多标志"},
		{373,"除湿阀标志"},
		{374,"室外机化霜"},
		{375,"室外旁通化霜"},
		{376,"回油标志"},
		{377,"室外故障显示标志"},
		{378,"室外机EEPROM在线下载标志"},
		{379,"室外机电量板"},
		{380,"压缩机电热带"},
		{381,"压缩机预加热"},
		{382,"补气增晗"},
		{384,"室内外机模式冲突"},
		{385,"室外EEPROM出错"},
		{386,"室外盘管温度传感器故障"},
		{387,"排气温度传感器故障"},
		{388,"室外环境温度传感器故障"},
		{389,"电压变压器故障"},
		{390,"电流互感器故障"},
		{391,"室外控制与驱动通信故障"},
		{392,"IPM模块过流保护"},
		{393,"IPM模块过热保护"},
		{394,"交流电过电压保护"},
		{395,"交流电欠电压保护"},
		{396,"母线电压过电压保护"},
		{397,"母线电压欠电压保护"},
		{398,"PFC过电流保护"},
		{399,"室外机最大电流保护"},
		{400,"室外环境温度过低保护"},
		{401,"排气温度过高保护"},
		{402,"压缩机管壳温度保护"},
		{403,"室内防冻结或防过载保护"},
		{404,"室外机PFC保护"},
		{405,"压缩机启动失败"},
		{406,"压缩机失步"},
		{407,"室外风机堵转"},
		{408,"室外盘管防过载保护"},
		{409,"冷媒泄漏"},
		{410,"压缩机型号匹配错误"},
		{411,"系统低频振动保护"},
		{412,"室外散热器温度过高保护"},
		{413,"系统压力过高保护"},
		{416,"逆变器直流过电压故障"},
		{417,"逆变器直流低电压故障"},
		{418,"逆变器交流过电流故障"},
		{419,"失步检出"},
		{420,"速度推定脉冲检出法检出欠相故障"},
		{421,"电流推定脉冲检出法检出欠相故障"},
		{422,"逆变器IPM故障-边沿"},
		{423,"逆变器IPM故障-电平"},
		{424,"PFC_IPM故障-边沿"},
		{425,"PFC_IPM故障-电平"},
		{426,"PFC停电检出故障"},
		{427,"PFC过电流检出故障"},
		{428,"直流电压检出异常"},
		{429,"PFC低电压（有效值）检出故障"},
		{430,"AD偏置异常检出故障"},
		{431,"逆变器PWM逻辑设置故障"},
		{432,"逆变器PWM初始化故障"},
		{433,"PFC_PWM逻辑设置故障"},
		{434,"PFC_PWM初始化故障"},
		{435,"温度异常"},
		{436,"电流采样电阻不平衡调整故障"},
		{437,"电机参数设置故障"},
		{438,"MCE故障"},
		{439,"驱动EEPROM故障"},
		{440,"室外盘管过载禁升频"},
		{441,"室外盘管过载降频"},
		{442,"室内盘管过载禁升频"},
		{443,"室内盘管过载降频"},
		{444,"压降排气过载禁升频"},
		{445,"压降排气过载降频"},
		{446,"室内盘管冻结禁升频"},
		{447,"室内盘管冻结降频"},
		{448,"室内外通信降频"},
		{449,"模块温度过载限频"},
		{450,"变调率限频"},
		{451,"相电流限频"},
		{452,"并用节电保护禁升频"},
		{453,"并用节电保护降频"},
		{454,"过电流保护禁升频"},
		{455,"过电流保护降频"},
		{463,"室内风机转速xx"},
		{471,"室内风机转速00xx"},
		{472,"有否PM2.5检测功能"},
		{479,"PM2.5污染程度"},
		{487,"空气PM2.5质量百分比表示"},
		{494,"显示屏亮度值"}
};

struct para_desc kt_fun[]={
		{7,"室内风量支持档位数KTFL"},
		{15,"睡眠模式支持数量KTSM"},
		{16,"表示单冷/冷暖机型KTDR"},
		{17,"开关机控制位KTKJ"},
		{18,"室内单个风向控制功能KTFX"},
		{19,"室内温度设置KTWD"},
		{20,"室内湿度设置KTSD"},
		{21,"室内体感温度接收允许KTTGCZ"},
		{22,"室内温度体感补偿控制KTTGBC"},
		{23,"自动和除湿温度补偿KTWDBC"},
		{31,"体感温度补偿值（绝对值）"},
		{39,"自动和除湿温度补偿值（绝对值）"},
		{40,"华氏/摄氏温度显示转换KTHS"},
		{41,"普通定时开关机KTGTT"},
		{42,"实时定时开关机KTGT KTKT"},
		{43,"6位置可定室内风门位置控制KTVFM"},
		{44,"上下风门控制KTVFC"},
		{45,"左右风门控制KTHFC"},
		{46,"自然风控制KTZRF"},
		{47,"电热开停控制KTDR"},
		{55,"除湿模式数量KTCS"},
		{56,"节能控制KTJN"},
		{57,"并用节电控制KTBY"},
		{58,"高效（强力）控制KTGX"},
		{59,"双模切换控制KTDM"},
		{60,"清新控制KTQS"},
		{61,"换风控制KTHF"},
		{62,"室内清洁控制KTQJ"},
		{63,"室外清洁控制KTSWQJ"},
		{64,"智慧眼控制KTZN"},
		{65,"静音模式控制KTJY"},
		{66,"语音控制KTYY"},
		{67,"除烟控制KTCY"},
		{68,"背景灯控制KTBJD"},
		{69,"显示屏发光显示控制KTXSP"},
		{70,"LED指示灯控制KTLED"},
		{71,"室内外温度切换显示控制KTSRW"},
		{72,"室内过滤网清洁复位控制KTGLW"},
		{73,"左风摆开停控制KTZFC"},
		{74,"右风摆开停控制KTYFC"},
		{75,"101#-0#第22字节BIT1、BIT0预留位的控制功能"},
		{76,"101#-0#第11字节BIT1、BIT0预留位的控制功能"},
		{77,"101#-0#第10字节BIT2~BIT0预留位的控制功能"},
		{78,"海信/科龙控制规则"},
		{87,"101#-0#第23字节预留位的控制功能"},
		{95,"101#-0#第25字节预留位的控制功能"},
		{103,"101#-0#第26字节预留位的控制功能"},
		{111,"101#-0#第27字节预留位的控制功能"},
		{119,"101#-0#第28字节预留位的控制功能"},
		{127,"101#-0#第29字节预留位的控制功能"},
		{135,"101#-0#第30字节预留位的控制功能"}
};

struct para_desc jh_set[]={
		{6,"风量[weak/middle/strong/clear/auto]"},
		{8,"发音[0/1]"},
		{14,"模式[cleardust/clearsmell/smart/mute/sleep]"},
		{22,"普通定时开关机[0.5h-23h]"},		
		{24,"开机[0/1]"},
		{26,"儿童锁[0/1]"},
		{28,"水离子开关[0/1]"},
		{30,"加湿机开关[0/1]"}
};
struct para_desc jh_status[]={
		{6,"净化速度"},
		{14,"净化模式"},
		{16,"定时开关机控制"},
		{22,"定时开关机时间"},
		{31,"风机转速"},
		{39,"空气质量"},
		{47,"空气质量百分比"},
		{55,"相对湿度"},
		{56,"开停净化机"},
		{57,"儿童锁开关控制"},		
		{58,"水离子开停控制"},
		{59,"加湿机开停控制"},
		{60,"过滤网更换提示"},
		{61,"本次命令之前有否红外和按键控制过"},
		{62,"本次命令之前有否红外和按键控制过"},
		{64,"加湿转轮不动"},
		{65,"水箱空"},
		{66,"水箱未装好"},
		{67,"湿度传感器故障"},
		{68,"风机故障"},
		{70,"风尘传感器故障"},
		{71,"机器倾斜故障"}
};

struct para_desc jh_fun[]={
		{3,"净化速度状态-自动功能"},
		{4,"净化速度状态-净烟功能"},
		{5,"净化速度状态-高风功能"},
		{6,"净化速度状态-中风功能"},
		{7,"净化速度状态-低风功能	"},	
		{11,"净化模式状态-睡眠功能"},	
		{12,"净化模式状态-静音功能"},	
		{13,"净化模式状态-智能功能"},	
		{14,"净化模式状态-除味功能"},	
		{15,"净化模式状态-	除烟功能"},	
		{16,"普通定时功能"},
		{17,"儿童锁功能"},
		{18,"水离子开停"},
		{19,"加湿机开停功能"},
		{20,"净化机开停功能"},
		{22,"EEPROM可改写功能"},
		{23,"电量检测功能"},
		{24,"101#-0#第5字节预留位的控制功能"},
		{32,"101#-0#第6字节预留位的控制功能"}
};

struct para_desc cs_set[]={
		{6,"风量[weak/strong/auto]"},
		{8,"发音[0/1]"},
		{14,"模式[continue/normal/auto/heat]"},
		{22,"普通定时开关机[0.5h-23h]"},
		{30,"湿度[0-100]"},		
		{40,"开机[0/1]"},
		{42,"电加热[0/1]"},
		{44,"水泵[0/1]"},
		{46,"负离子[0/1]"}
};

struct para_desc cs_status[]={
		{6,"风速"},
		{14,"模式"},
		{16,"定时开关机控制"},
		{22,"定时开关机时间"},
		{31,"湿度"},
		{39,"电加热设定温度"},
		{47,"室内温度"},
		{48,"除湿机开关"},
		{49,"电加热开关"},
		{50,"水泵开关"},		
		{51,"负离子开关"},
		{52,"本次命令之前有否红外和按键控制过"},
		{53,"本次命令之前有否WIFI控制过"},
		{56,"过滤网清洁告警"},
		{57,"湿度传感器故障"},
		{58,"管温传感器故障"},
		{59,"室温传感器故障"},
		{60,"水满告警"},
		{61,"水泵故障"}
};

struct para_desc cs_fun[]={
		{4,"智慧风"},
		{5,"高风"},
		{6,"中风"},
		{7,"低风"},		
		{13,"持续运行模式"},
		{14,"正常运行模式"},
		{15,"自动运行模式"},
		{16,"普通定时功能"},
		{17,"电加热功能"},
		{18,"电加热温度设置"},
		{19,"室内湿度设置"},
		{20,"水泵开停控制"},
		{21,"负离子开停控制"},
		{22,"电量检测功能"},
		{23,"开停机功能"},
		{24,"EEPROM可改写功能"},
		{39,"101#-0#第7字节预留位的控制功能"},
		{47,"101#-0#第8字节预留位的控制功能"}
};

struct para_desc qr_set[]={
		{6,"风量[weak/middle/strong/auto]"},
		{10,"开机[0/1]"},
		{14,"模式[fullheat/direct/indoor/auto]"},
		{22,"普通定时开关机[0.5h-23h]"}
};
struct para_desc qr_status[]={
		{6,"净化速度"},
		{10,"开机"},
		{14,"净化模式"},
		{16,"定时开关机控制"},
		{22,"定时开关机时间"},
		{31,"室外风机转速"},
		{39,"室内风机转速"},
		{47,"室外侧温度"},
		{55,"室外侧相对湿度"},
		{63,"室内侧二氧化碳浓度高位"},
		{71,"室内侧二氧化碳浓度低位"},		
		{72,"过滤器更换提示"},
		{73,"室外风机故障"},
		{74,"室内风机故障"},
		{75,"室外侧温度传感器故障"},
		{76,"室外侧湿度传感器故障"},
		{77,"二氧化碳传感器故障"},
		{78,"室内侧温度传感器故障"},
		{79,"室内侧湿度传感器故障"}
};

struct para_desc qr_fun[]={
		{7,"风量支持档位数"},
		{12,"全热换气模式"},
		{13,"直通换气模式"},
		{14,"回风换气模式"},
		{16,"普通定时功能"},
		{17,"开关机控制位"},
		{22,"EEPROM可改写功能"},
		{23,"电量检测功能"}
};


XM_AT_LIST xm_at_test[]={
#if XM_APP
		{48,at_cmd,0xff,"模块控制"},
#else
		{48,at_cmd,0xff,"模块控制"},
#endif
		{23,at_cmd_kl,0xff,"科龙通用"},
		{53,at_cmd_kt,0x01,"科龙空调"},
		{11,at_cmd_jh,0x18,"科龙空气净化器"},
		{12,at_cmd_cs,0x15,"科龙除湿机"},
		{7,at_cmd_qr,0x19,"科龙全热交换机"},
		{15,at_cmd_oven,0x27,"新联锋烤箱"},
		{6,at_cmd_rsq,0x25,"方太热水器"},
		{5,at_cmd_rqz,0x22,"方太燃气灶"},
};

		

char *getdesc(uchar offest,struct para_desc *pdesc,int size){
	int i;
	for(i=0;i<size;i++){
		if(pdesc[i].offset==offest)
			return pdesc[i].desc;
	}
	return NULL;
};

char *getktfun(uchar offest){
	int size=sizeof(kt_fun)/sizeof(kt_fun[0]);
	return getdesc(offest,kt_fun,size);
};
char *getktstatus(uchar offest){
	int size=sizeof(kt_status)/sizeof(kt_status[0]);
	return getdesc(offest,kt_status,size);
};
char *getktset(uchar offest){
	int size=sizeof(kt_set)/sizeof(kt_set[0]);
	return getdesc(offest,kt_set,size);
};

char *getjhfun(uchar offest){
	int size=sizeof(jh_fun)/sizeof(jh_fun[0]);
	return getdesc(offest,jh_fun,size);
};
char *getjhstatus(uchar offest){
	int size=sizeof(jh_status)/sizeof(jh_status[0]);
	return getdesc(offest,jh_status,size);
};
char *getjhset(uchar offest){
	int size=sizeof(jh_set)/sizeof(jh_set[0]);
	return getdesc(offest,jh_set,size);
};

char *getcsfun(uchar offest){
	int size=sizeof(cs_fun)/sizeof(cs_fun[0]);
	return getdesc(offest,cs_fun,size);
};
char *getcsstatus(uchar offest){
	int size=sizeof(cs_status)/sizeof(cs_status[0]);
	return getdesc(offest,cs_status,size);
};
char *getcsset(uchar offest){
	int size=sizeof(cs_set)/sizeof(cs_set[0]);
	return getdesc(offest,cs_set,size);
};

char *getqrfun(uchar offest){
	int size=sizeof(qr_fun)/sizeof(qr_fun[0]);
	return getdesc(offest,qr_fun,size);
};
char *getqrstatus(uchar offest){
	int size=sizeof(qr_status)/sizeof(qr_status[0]);
	return getdesc(offest,qr_status,size);
};
char *getqrset(uchar offest){
	int size=sizeof(qr_set)/sizeof(qr_set[0]);
	return getdesc(offest,qr_set,size);
};

int main(int argc,char *args[]){
#ifdef XM_MEM_DEBUG
	mtrace();
#endif
	FILE * fp;
    char buffer[512];
	int j=0,k=0,i=0,s1=0,funcNum,first=0,isset=0,id;
	XM_AT_FUN *pat_cmd;
	char cmdstr[255];
	char * pret;
	XmInitLog(8);
	XmSetLog("cmd",0);
	for(k=0;k<sizeof(xm_at_test)/sizeof(xm_at_test[0]);k++){
		pat_cmd = xm_at_test[k].funlist;
		funcNum = xm_at_test[k].listnum;
		id = xm_at_test[k].type;
#if DEBUG_AT
		XM_V("main at:%d %d %p\r\n",k,funcNum,pat_cmd);
#endif
		XM_V("%d:%s\r\n",k+2,xm_at_test[k].cmddesc);
		s1=1;
		for(i=0;i < funcNum; i++){	
			isset=0;
			
			if(pat_cmd->cmd){
#if XM_APP
				if(strncmp(pat_cmd->cmd,"RET",3)==0 ||  strncmp(pat_cmd->cmd,"OK",2)==0 ||strncmp(pat_cmd->cmd,"ERROR",5)==0 )
					continue;
#endif
				memset(cmdstr,0,255);
				memset(buffer,0,512);
				snprintf(cmdstr,255,"./getcmd.sh %s",pat_cmd->cmd);
				fp=popen(cmdstr,"r");
				fgets(buffer,sizeof(buffer),fp);
			    printf("%s",buffer);
			    pclose(fp);
				
				if(pat_cmd->parameter && strlen(buffer)>2){
					if(pat_cmd->parameter->set_cmd || pat_cmd->parameter->set_sub){
						if(strlen(buffer)>2){
							XM_V("	%d.%d:%s\r\n",k+2,s1,buffer);
							XM_V("		命令:%s\r\n",pat_cmd->cmd);
						}
						s1++;
						XM_V("		设置功能:");
						first=0;
						isset=1;					
						for(j=0;j<pat_cmd->parameter->send_num;j++){
								if(pat_cmd->parameter->send[j].set && !pat_cmd->parameter->send[j].preset){
									if(first==0){
										first=1;
									}else{
										XM_V(",");
									}
									switch(id){
										case 1:
										XM_V("%s",getktset(pat_cmd->parameter->send[j].offset));
										//XM_V("%d字节",pat_cmd->parameter->send[j].len/8?pat_cmd->parameter->send[j].len/8:1);
										break;
										case 0x18:
										XM_V("%s",getjhset(pat_cmd->parameter->send[j].offset));
										//XM_V("%d字节",pat_cmd->parameter->send[j].len/8?pat_cmd->parameter->send[j].len/8:1);
										break;
										case 0x15:
										XM_V("%s",getcsset(pat_cmd->parameter->send[j].offset));
										//XM_V("%d字节",pat_cmd->parameter->send[j].len/8?pat_cmd->parameter->send[j].len/8:1);
										break;
										case 0x19:
										XM_V("%s",getqrset(pat_cmd->parameter->send[j].offset));
										//XM_V("%d字节",pat_cmd->parameter->send[j].len/8?pat_cmd->parameter->send[j].len/8:1);
										break;
									}	
								}
						}
						if(first==0){
							XM_V("无参数");
						}
						XM_V("\r\n");
						XM_V("		设置返回:");
						first=0;
						for(j=0;j<pat_cmd->parameter->recv_num;j++){
							if(pat_cmd->parameter->recv[j].set){
								if(first==0){
									first=1;
								}else{
									XM_V(",");
								}
								switch(id){
									case 1:
										XM_V("%s",getktstatus(pat_cmd->parameter->recv[j].offset));
										//XM_V("%d字节",pat_cmd->parameter->recv[j].len/8?pat_cmd->parameter->recv[j].len/8:1);
									break;
									case 0x18:
										XM_V("%s",getjhstatus(pat_cmd->parameter->recv[j].offset));
										//XM_V("%d字节",pat_cmd->parameter->recv[j].len/8?pat_cmd->parameter->recv[j].len/8:1);
									break;
									case 0x15:
										XM_V("%s",getcsstatus(pat_cmd->parameter->recv[j].offset));
										//XM_V("%d字节",pat_cmd->parameter->recv[j].len/8?pat_cmd->parameter->recv[j].len/8:1);
									break;
									case 0x19:
										XM_V("%s",getqrstatus(pat_cmd->parameter->recv[j].offset));
										//XM_V("%d字节",pat_cmd->parameter->recv[j].len/8?pat_cmd->parameter->recv[j].len/8:1);
									break;
								}	
							}
						}
						if(first==0){
							XM_V("执行结果");
						}
						XM_V("\r\n");
					}
					
					if((pat_cmd->parameter->query_cmd || pat_cmd->parameter->query_sub) && !isset && (pat_cmd->parameter->recv_num > pat_cmd->parameter->query_len)){
						if(strlen(buffer)>2){
							XM_V("	%d.%d:%s\r\n",k+2,s1,buffer);
							XM_V("		命令:%s\r\n",pat_cmd->cmd);
						}
						s1++;
						XM_V("		查询状态:?\r\n");
						XM_V("		状态返回:");
						first=0;
						for(j=0;j<pat_cmd->parameter->recv_num;j++){
							if(pat_cmd->parameter->recv[j].query ){
								if(first==0){
									first=1;
								}else{
									XM_V(",");
								}								
								if(pat_cmd->parameter->query_cmd==102 && pat_cmd->parameter->query_sub==64){									
									switch(id){
										case 1:
											pret=getktfun(pat_cmd->parameter->recv[j].offset);									
										break;
										case 0x18:
											pret=getjhfun(pat_cmd->parameter->recv[j].offset);									
										break;
										case 0x15:
											pret=getcsfun(pat_cmd->parameter->recv[j].offset);									
										break;
										case 0x19:
											pret=getqrfun(pat_cmd->parameter->recv[j].offset);									
										break;
									}	
								}else{
									switch(id){
										case 1:
											pret=getktstatus(pat_cmd->parameter->recv[j].offset);
										break;
										case 0x18:
											pret=getjhstatus(pat_cmd->parameter->recv[j].offset);
										break;
										case 0x15:
											pret=getcsstatus(pat_cmd->parameter->recv[j].offset);
										break;
										case 0x19:
											pret=getqrstatus(pat_cmd->parameter->recv[j].offset);
										break;
									}	
								}
								XM_V("%s",pret==NULL?"保留":pret);
								//XM_V("%d字节",pat_cmd->parameter->recv[j].len/8?pat_cmd->parameter->recv[j].len/8:1);
							}
						}
						if(first==0){
							XM_V("无参数");
						}
						XM_V("\r\n");
					}
					
				}
				XM_V("\r\n");
			}
			pat_cmd++;
		}
	}
}


