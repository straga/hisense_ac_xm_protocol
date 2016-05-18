#ifndef _Included_cmdanalysis
#define _Included_cmdanalysis
/*
将二进制数组转成十六进制字符
参数:
p_binstr:二进制数组
bin_len:二进制数组长度
p_hexstr:生成后的十六进制字符串保存地址
返回:
返回十六进制字符串长度
*/
int BIN2HEX(char *  p_binstr, int bin_len, char * p_hexstr);
/*
将十六进制字符转成二进制数组
参数:
p_hexstr:十六进制字符串
p_binstr:二进制数组
返回:
二进制数组长度
*/
int HEX2BIN(char *  p_hexstr, char * p_binstr);
/*
处理数据 发送参数，生成数据和判断是否需要发送
参数:
pxm:socket 数据指针
pnode:发送节点
返回:
出错结果在发送节点结构中
*/
void proc_cmd(XM_PROTOCOL *pxm,XM_NODE *pnode);
/*
处理AT 命令字符串
参数:
pxm:socket 数据指针
pnode:发送节点
str:AT 命令字符串
strcnt:AT 命令字符串长度
返回:
无
*/
void strDividing(XM_PROTOCOL *pxm,XM_NODE *pnode,char * str,int strcnt);
/*
处理返回结果
参数:
pxm:socket 数据指针
pnode:发送节点
pmsg:额外的数据
code:出错码
返回:
出错码
*/
uchar build_at_ret(XM_PROTOCOL *pxm,XM_NODE *pnode,char *pmsg,uchar code);
/*
获取指定的设备设置命令结构
参数:
address:设备地址
cmd:命令字
sub:子命令
pbuf:设置数据
len:数据长度
返回:
命令结构的指针
*/
XM_Command * getcommand(uchar address,uchar cmd,uchar sub,char *pbuf,int len);
int Build_Send(XM_PROTOCOL *pxm,XM_NODE *pnode,uchar argc,char **argv);
#endif
