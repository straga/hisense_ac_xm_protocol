/********************* xlf_crc.h ***********************
Author:		TaoHe
Create On: 10-08-2015
Modified : 10-13-2015
Info: call crc with initialized value.
**********************************************************/


#ifndef XLF_CRC__H
#define XLF_CRC__H

/** CRC8 暂不可用*/
unsigned char do_crc8(const unsigned char *message, unsigned int len,unsigned char crc_reg);

/** CRC16 1021
 * @param message 需要进行校验的数据起始地址
 * @param len 要校验的数据长度
 * @param crc_reg 初始的CRC值，第一次调用该值为0，如果分多次校验一个很长的数据，可以直接将
 *        前面的得到的CRC值放入。
 */
unsigned short do_crc16_1021(const void *msg, unsigned int len,unsigned short crc_reg) ;

/** CRC32 04C11DB7
 * @param message 需要进行校验的数据起始地址
 * @param len 要校验的数据长度
 * @param crc_reg 初始的CRC值，第一次调用该值为0，如果分多次校验一个很长的数据，可以直接将
 *        前面的得到的CRC值放入。
 */
unsigned int do_crc32_04C11DB7(const void *msg, unsigned int len,unsigned int crc_reg) ;

#endif // End of xlf_crc.h


