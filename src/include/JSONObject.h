/*
 * Author Kevin He
 * Created on 18th May,2016
 */

#ifndef JSON_OBJECT__H
#define JSON_OBJECT__H

#include "cJSON.h"
#include <iostream>
#include <string>
using namespace std;

#define NUMERROR -0xaa5555aa
class JSONObject{
	cJSON *root;
    string jsString;
    void flushString();
public:
    JSONObject();
	/*c_string ,C++ string 构造*/
	JSONObject(const string &jsStr);
	/*拷贝构造*/
	JSONObject(const JSONObject &in);
	
	~JSONObject();
    void clear();
    const string& toString()const;
	/*获取一个key对应的int值*/
	int getNumber(const string &key);
	/*获取一个key对应的string值*/
	string getString(const string &key);
	/*添加一个int key*/
	JSONObject& putNumber(const string &key,int value);
	/*添加一个string key*/
	JSONObject& putString(const string &key,const string &str);
	/*从JSON中删除一个key*/
	JSONObject& remove(const string &key);
	/*重载赋值运算*/
	JSONObject& operator = (const JSONObject &in);
    JSONObject& operator = (const string  &jsStr);
    friend ostream& operator <<(ostream &os,JSONObject &obj);
};

#endif



