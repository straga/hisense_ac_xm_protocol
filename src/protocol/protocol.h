#ifndef _Included_Protocol
#define _Included_Protocol
#define XM_VER_MID 3
#define XM_VER_SID 2
#define XM_VER_LID 6

/*
v2.0 :
1.支持102 64读取
2.KTFL/KTSM指令支持 *  判断是否支持
3.线程数为32 同时支持数为128
V2.1:
1.修改同步方式
2.线程数为64 同时支持数为256
3.为提高本地测试通过率，在超时向socket 发送1字节的数据
4.增加删除指定的socket
5.增加老接口兼容
V2.2:
1.完成所有设备对102 64 支持判断
V2.3:
1.增加exitSocket接口
2.对于102_0/102_64使用本地缓存数据
V2.4:
1.更新指令说明
2.修复部分参数
3.更新指令输出样式
4.兼容设备新固件多返回三个字节的处理
V2.5:
1.修复配置命令参数丢失问题
2.修复查询命令多出数据的错误
3.修复虚拟服务参数处理错误
4.临时修复线程死锁问题
V3.0:
1.支持ID
2.不再处理返回值
3.优化线程模型
V3.0.1:
1.修改版本号，支持"%d.%d.%d"格式
2.修改同时支持的最大命令数
3.增加XMID,XMSSID命令
V3.0.2
1.解决无效指令处理异常
2.解决查询指令结果处理结果不对
3.解决多次查询时发多次命令
4.修改命令执行返回值
5.修改配置命令返回时等待错误
6.修复超时错误未返回
7.修复退出线程处理错误
8.等待上次命令完成
9.修改命令发送失败时的重发次数(5-->1)
10.修改命令超时的等待时间(5-->1)
V3.0.3:
1.部分指令增加参数，兼容多指令拼包
2.修改睡眠时间值
3.增加锁信息打印
4.修复命令列表长度错误
5.修正命令发送失败后，其它查询命令未发数据
6.修正多个命令组合的问题，增加socket退出时清除发送节点
7.修正一个死锁问题
8.增加crc接口
9.支持xcode编译
10.增加OTA指令
11.修改线程退出机制
v3.1.0
1.代码结构调整，功能细化
2.恢复锁机制
3.增加节点等待状态标志
v3.1.1
1.增加获取报文接口
2.修复部分命令错误
3.增加获取命令参数接口
4.修复异常退出
5.修复KTZD命令错误
v3.1.2
1.支持虚拟服务
2.检查返回数据地址
3.检查返回的数据与发送的命令是否一致
4.切换cron方式同步
5.发送失败时不在改变socket
6.检查返回的数据是否大于参数要求
v3.1.3
1.去掉对科龙空调101指令错误兼容
2.增加指令发送间隔200ms
v3.1.4
1.更改返回错误码格式
2.去掉发送时的延时处理
3.更改地址错误的处理位置
4.解决jni时内存泄漏
v3.1.5
1.解决查询命令参数处理
2.删除设置命令的查询
3.协议版本更新到0620
v3.1.6
1.增加KTSS命令
2.增加除湿机，交换机的声音位
3.修改一些命令参数错误
4.修改jni的内存泄漏
5.修改命令约束条件
6.解决风量显示
7.关机时不取消亮度
8.修正了上下风显示不正确的问题
v3.1.7
1.修改了框架，增加了socket锁和node锁的使用，以及监控线程，解决了部分死锁的问题；
2.解决发送速度的问题；
3.解决XM_NODE死锁的问题；
4.修复一些死锁问题，不需要使用监控线程来解决死锁；
v3.1.8
1.解决了关机后并用节电没取消的问题；
2.解决了上下风门返回值错误的问题；
3.解决了设置定时关机后无响声的问题；
4.并用节电增加高效控制位，使上层在控制并用节电时可关高效；
5.解决了上下风门auto和sweep模式颠倒的问题；
6.增加了XMCLS命令；
7.修改了风量的返回值；
8.增加了全热交换机的手动/自动命令位，同步到全热0616协议；
v3.1.9
1.增加了传递形参的个数，扩展到7个，支持at命令的多个参数；
2.增加XMWIFI命令；
3.增加静音与静音风速的绑定控制；
4.解决了parse_data函数调用出错的问题；
5.在风量返回时，如果同时返回静音和自动位，以静音位优先；
6.根据新的约束条件修改了KTKJ,KTYX,KTGX的参数；
7.在不支持ktgn的查询时，返回8号错误；
v3.2.0
1.同步ios版本；
2.解决apk进入本地so库退出后无法再进入的问题；
v3.2.1
1.当空调返回通信失败的错误(error=0),把错误码转换成非0错误；
2.增加 XMCS XMSIP 命令
3.对返回字符串进行判断，不合法字符返回错误码XM_ERROR_MAX_CMD_IN_STRING_PARSE_ERROR;
v3.2.2
1.增加顺德科龙的jni及编译
v 3.2.3
1 在本地调用so库使用so库的socket连接时，修改参数退出时关闭socket
2,回退socket关闭代码
v 3.2.4
1 增加XMEXIT命令，通知WIFI退出socket连接
2 修改build_packet函数，在传入非设备的指令时，原样返回对应的字符串；
3 修改睡眠模式顺序
v3.2.5
1 增加了除湿机的模式参数；
2 增加了全热交换机的zd提示音位；
3 在发指令timeout时，再重发2次；
4 增加新的wifi控制指令，保留老的指令用于兼容；
v3.2.6
1  为smartbox增加对应设备的指令，该指令一次控制设备多个操作；
2  增加净化器的湿度设置功能；
*/

#ifdef PLAT_LINUX
#include <jni.h>
#else
#ifndef JavaVM
#define JavaVM void
#endif
#endif



// 初始化虚拟服务
int xm_init_servsr(char * server_port,int connect);
// 停止虚拟服务
void xm_stop_servsr(void);
// 获取当前 命令的报文
char * xm_get_packet(int index);
// 获取当前 命令的网络返回内容
char * xm_get_parse(int index);
// 初始化socket 数组和发送节点
void xm_init_index(JavaVM *pjvm,int connect_num,int send_num,int max_wait_node);
// 兼容原来接口
void xm_init(JavaVM *pjvm);
// 兼容原来接口，指定为空调
int xm_init_withsocket(int socket);
// 使用传入的socket 
int xm_init_withsocket_index(int socketfd,int id);
// 兼容原来接口，指定为空调
int init_socket_client(char * server_ip,char * server_port);
// 建立socket 
int xm_init_socket_index(char * server_ip,char * server_port,int id,int reset);
// 退出所有线程和关闭所有socket
int xm_exit(void);
// 关闭指定socket
int xm_exit_socket(int socketfd);
// 发送AT 指令
char * xm_send_index(int index,char *psend,int sendlen);
// 兼容原来接口
char * xm_send(char *psend);
// 获取版本号
char * xm_get_version(void);
//测试用接口
int xm_init_flag(char * server_ip,char * server_port,int id,char cflag);
//测试用接口, 服务程序返回模拟值
int xm_init_virtual(char * server_ip,char * server_port,int id);
//获得socket 数组的socket 句柄
int xm_get_socket(int index);
//连接指定服务器，生成socket 数组内容
int init_socket_client(char * server_ip,char * server_port);
//用指定的socket 句柄生成socket 数组内容
int xm_init_flag_withsocket(int socket_fd,int id,char cflag);
//对数据进行crc 验证
char * crc_data(char *buf,int len,char * strcrc);
//对上次发送的报文
char * xm_get_packet(int index);
//对上次返回的报文
char * xm_get_parse(int index);
//生成报文
char *xm_build_packet(char *pbuf,int *len,int address);
//解析报文
char * xm_parse_data(char *cmdpbuf,int cmdlen,char *pbuf,int len);
//生成命令的参数
char *xm_build_para(char *pbuf,int *len);
//解析命令的参数
char *xm_parse_para(char *cmdpbuf,int cmdlen,char *pbuf,int len);
/*
生成返回的报文
参数:
status:状态保存长度不低1k
pbuf:接收到报文
len:报文长度
返回:
字符串
*/
char* xm_ret_cmd (char * status,char *pbuf,int *len);
int xlf_packet_build(int type_checksum,char sequence,char *sendbuf,char *buf,int buflen,int moblie_type,int moblie_address,int device_type,int device_address);
int js_build_cmd(char *sendbuf,char *buf,int device_type,int device_address,int moblie_type,int moblie_address);
int xlf_packet_pasre(char *retbuf,char *pbuf,int len,int address);

#endif
