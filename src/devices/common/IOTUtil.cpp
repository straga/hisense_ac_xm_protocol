//
//  IOTUtil.cpp
//  devices
//
//  Created by 肖芳亮 on 15/9/15.
//  Copyright (c) 2015年 新联锋科技. All rights reserved.
//

#include "IOTUtil.h"
#include <iostream>
#include <vector>
#include <netdb.h>
#include <sstream>
#include <cstring>

const string IOTUtil::TAG = "IOTUtil";
const bool IOTUtil::debug = false;
char IOTUtil::hex[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 'A', 'B', 'C', 'D', 'E', 'F'};

//获取当前系统时间
int64 IOTUtil::getSystemTime()
{
    struct timeval tv;
    //获取一个时间结构
    //gettimeofday(&tv, NULL);
    //获取当前时间
    int64 t = tv.tv_sec;
    t *=1000;
    t +=tv.tv_usec/1000;
    return  t;
}

void IOTUtil::printLog(string tag, string log)
{
    if(debug)
    {
        cout << tag + "==================" + log + "==================" << endl;
    }
}

/**
 * 把十六进制字符串转换成byte数组
 * @return
 */

vector<char> IOTUtil::hexStringToBinary(string hexstr)
{
    long len = hexstr.length() / 2;
    vector<char> result;
    for(int i = 0; i < len; i++)
    {
        char ch0 = hexstr[2 * i];
        char ch1 = hexstr[2 * i + 1];
        char temp = (char)((parse(ch0) << 4) | parse(ch1));
        result.push_back(temp);
    }
    
    return result;
}

/**
 * 十六进制转byte数组
 */
char* IOTUtil::hexStringToBytes(string hexString)
{
    
    long sz = hexString.length();
    char *ret = new char[sz/2];
    for (int i=0 ; i <sz ; i+=2) {
        ret[i/2] = (char) ((hexString.at(i) << 4)
                           | hexString.at(i+1));
    }
    return ret;
}

/**
 * 把byte数组转换成十六进制字符串
 * @return
 */
string IOTUtil::Bytes2HexString(unsigned char byte_arr[], int arr_len)
{
    string hexstr;
    for (int i=0;i<arr_len;i++)
    {
        char hex1;
        char hex2;
        int value=byte_arr[i];
        int v1=value/16;
        int v2=value % 16;
        
        if (v1>=0&&v1<=9)
            hex1=(char)(48+v1);
        else
            hex1=(char)(55+v1);
        
        
        if (v2>=0&&v2<=9)
            hex2=(char)(48+v2);
        else
            hex2=(char)(55+v2);
        
        hexstr=hexstr+hex1+hex2;
    }
    return hexstr;
}

string IOTUtil::subString(const string &src, int begin_pos, int end_pos)
{
    string sub = src.substr(begin_pos, end_pos - begin_pos);
    return sub;
}

string IOTUtil::replace_all(string str,const string old_value,const string new_value)
{
    while(true)   {
        string::size_type   pos(0);
        if(   (pos=str.find(old_value))!=string::npos   )
            str.replace(pos,old_value.length(),new_value);
        else   break;
    }
    return   str;
}

int IOTUtil::parse(char c)
{
    if('a' <= c)
    {
        return (c - 'a' + 10) & 0x0f;
    }
    
    if('A' <= c)
    {
        return (c - 'A' + 10) & 0x0f;
    }
    
    return (c - '0') & 0x0f;
}

/***************************************************************************
 *
 * @brief string to char *
 * @param 要转换的字符串string
 * @return char*形式的字符串
 *
 ****************************************************************************/
char* IOTUtil::stringToChar(string aString)
{
    int size = (int)aString.size();
    char *content = new char[size + 1];
    strcpy(content, aString.c_str());
    content[size] = '\0';
    
    return content;
}

/***************************************************************************
 *
 * @brief 截掉字符串两端的空白字符
 * @param 源字符串
 * @return char*形式的字符串
 *
 ****************************************************************************/
void IOTUtil::trim(string &str)
{
    //left
    str.erase(str.begin(), find_if(str.begin(), str.end(), not1(ptr_fun<int, int>(isspace))));
    
    //right
    str.erase(std::find_if(str.rbegin(), str.rend(), not1(ptr_fun<int, int>(isspace))).base(), str.end());
}

/*去掉字符串两边的空格*/
string IOTUtil::trimString(string &s)
{
    //left
    s.erase(s.begin(), find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace))));
    
    //right
    s.erase(std::find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(), s.end());
    return s;
}

/***************************************************************************
 *
 * @brief string to int
 * @param 要转为数值的字符串
 * @return 返回数值
 *
 ****************************************************************************/
int IOTUtil::stringToInt(string str)
{
    return atoi(str.c_str());
}

bool IOTUtil::equalsIgnoreCase(string paramOne, string paramTwo)
{
    transform(paramOne.begin(), paramOne.end(), paramOne.begin(), ::toupper);
    transform(paramTwo.begin(), paramTwo.end(), paramTwo.begin(), ::toupper);
    if(paramTwo == paramOne)
    {
        return true;
    }
    
    return false;
}

string IOTUtil::toLowerCase(string strSource)
{
    transform(strSource.begin(), strSource.end(), strSource.begin(), ::tolower);
    
    return strSource;
}

string IOTUtil::toUpperCase(string strSource)
{
    transform(strSource.begin(), strSource.end(), strSource.begin(), ::toupper);
    return strSource;
}

string IOTUtil::intToString(int value)
{
    string result;
    
    stringstream stream;
    stream << value;
    stream >> result;
    
    return result;
}

string IOTUtil::floatToString(float value)
{
    string result;
    
    stringstream stream;
    stream << value;
    stream >> result;
    
    return result;
}

vector<string> IOTUtil::split(string str,string pattern)
{
    string::size_type pos;
    vector<string> result;
    str += pattern;
    string::size_type size = str.size();
    for(string::size_type i = 0; i < size; i++)
    {
        pos = str.find(pattern, i);
        if(pos < size)
        {
            string s = str.substr(i, pos - i);
            result.push_back(s);
            i = pos + pattern.length() - 1;
        }
    }
    
    return result;
}

int64 IOTUtil::getMillisecondsNow()
{
    struct timeval tp;
    //gettimeofday(&tp, NULL);
    int64 ms = (int64) tp.tv_sec * 1000 + (int64)tp.tv_usec / 1000;
    
    return ms;
}

//把当前字符串 去掉所有的空格
string IOTUtil::relAllSpace(string strSource)
{
    int num=0;
    basic_string<char>::size_type index=0;
    while ((index=strSource.find(" ",index))!=string::npos)
    {
        index++;
        num++;
    }
    for (int i=0; i<num; i++) {
        size_t iPos=strSource.find(" ");
        string headStr=strSource.substr(0,iPos);
        string tailStr=strSource.substr(iPos+1,strSource.length()-iPos-1);
        strSource=headStr+tailStr;
    }
    return strSource;
}

