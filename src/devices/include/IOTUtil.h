//
//  IOTUtil.h
//  devices
//
//  Created by 肖芳亮 on 15/9/15.
//  Copyright (c) 2015年 新联锋科技. All rights reserved.
//

#ifndef __Service__IOTUtil__
#define __Service__IOTUtil__

#include <stdio.h>
#include <string>
#include <vector>
#include <time.h>
#include <algorithm>
#include <cstring>
using namespace std;

typedef long long int64;

class IOTUtil
{
private:
    static const string TAG;
    static const bool debug;
    static char hex[16];
    static int parse(char c);
    
public:
    
    //获取当前系统时间
    static int64 getSystemTime();
    
    //输出日志
    static void printLog(string tag, string log);
    
    //把十六进制字符串转换成byte数组
    static vector<char> hexStringToBinary(string hexstr);
    
    static char* hexStringToBytes(string hexString);
    
    //把byte数组转换成十六进制字符串
    static string Bytes2HexString(unsigned char byte_arr[], int arr_len);
    
    //取子串
    static string subString(const string &src, int begin_pos, int end_pos);
    
    //字符串替换
    static string replace_all(string str,const string old_value,const string new_value);
    
    //string -> char *
    static char* stringToChar(string value);
    
    //截掉字符串两端的空白字符
    static void trim(string &str);
    
    //去掉字符串两边的空格
    static string trimString(string &s);
    
    //string -> int
    static int stringToInt(string str);
    
    //忽略大小写的比较
    static bool equalsIgnoreCase(string paramOne, string paramTwo);
    
    //获取当前时间
    static string getNowDateTime();
    
    //字符串转成小写
    static string toLowerCase(string strSource);
    
    //字符串转成大写
    static string toUpperCase(string strSource);
    
    //int -> string
    static string intToString(int value);
    
    static string floatToString(float value);
    
    //字符串分割
    static vector<string> split(string str,string pattern);
    
    //获取系统的秒数
    static int64 getMillisecondsNow();
    
    //把当前字符串 去掉所有的空格
    static string relAllSpace(string strSource);
};

#endif /* defined(__Service__IOTUtil__) */
