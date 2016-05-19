#ifndef JSON_OBJECT__H
#define JSON_OBJECT__H

#include "cJSON.h"
#include <iostream>
#include <string>
using namespace std;

class JSONObject{
	cJSON *root;
public:
	/*c_string ,C++ string 构造*/
	JSONObject(const string &jsStr);
	/*拷贝构造*/
	JSONObject(const JSONObject &in);
	
	~JSONObject();
    void clear();
	string toString()const;
	/*获取一个key对应的int值*/
	int getNumber(const string key);
	/*获取一个key对应的string值*/
	string getString(const string key);
	/*添加一个int key*/
	void putNumber(const string key,int value);
	/*添加一个string key*/
	void putString(const string key,const string str);
	/*从JSON中删除一个key*/
	JSONObject& remove(const string key);
	/*重载赋值运算*/
	JSONObject& operator = (const JSONObject &in);
    friend ostream& operator <<(ostream &os,JSONObject &obj);
};

#endif



