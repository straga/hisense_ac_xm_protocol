/*
 * Author Kevin He
 * Created on 18th May,2016
 */

#include "../../include/JSONObject.h"

void JSONObject::flushString()
{
	char *c_str;
	if(root){
		c_str = cJSON_PrintUnformatted(root);
		jsString=c_str;
		free(c_str);
	}else{
		jsString = "";
	}
}

JSONObject::JSONObject()
{
	root = cJSON_CreateObject();
	flushString();
}


JSONObject::JSONObject(const string &jsStr)
{
	root = cJSON_Parse(jsStr.c_str());
	if(root == NULL){
		cout<<"Json:\""<<jsStr<<"\" is wrong"<<endl;
	}
	flushString();
}

JSONObject :: JSONObject(const JSONObject &in)
{
	root = cJSON_Parse(in.toString().c_str());
	if(root == NULL){
		cout<<"Json:\""<<in.toString()<<"\" is wrong"<<endl;
	}
	flushString();
}

JSONObject :: ~JSONObject()
{
//	cout<<"~JSONObject"<<endl;
	clear();
}

const string& JSONObject::toString()const
{
	return jsString;
}

void JSONObject::clear(void)
{
//	cout<<"clear"<<endl;
	cJSON_Delete(root);
	root = NULL;
	flushString();
}

JSONObject& JSONObject::putNumber(const string &key,int value)
{
	if(root){
		cJSON_AddNumberToObject(root,key.c_str(),value);
	}
	flushString();
	return *this;
}

JSONObject& JSONObject::putString(const string &key,const string &str)
{
	if(root){
		cJSON_AddStringToObject(root,key.c_str(),str.c_str());
	}
	flushString();
	return *this;
}

int JSONObject:: getNumber(const string &key){
	cJSON *item ;
	if(root){
		item = cJSON_GetObjectItem(root,key.c_str());
		if(item)
			return item->valueint;
	}
	return NUMERROR;
}
string JSONObject:: getString(const string &key){
	cJSON *item;
	if(root){
		item = cJSON_GetObjectItem(root,key.c_str());
		if(item)
			return item->valuestring;
	}
	return "";
}

JSONObject& JSONObject ::operator= (const JSONObject &in)
{
	if(this == &in) //¼ì²é×Ô¸³Öµ
		return *this;
	clear();
	root = cJSON_Parse(in.toString().c_str());
	if(root == NULL){
		cout<<"Json:\""<<in.toString()<<"\" is wrong"<<endl;
	}
	flushString();
	return *this;
}

JSONObject& JSONObject::operator = (const string  &jsStr){
	clear();
	root = cJSON_Parse(jsStr.c_str());
	if(root == NULL){
		cout<<"Json:\""<<jsStr<<"\" is wrong"<<endl;
	}
	flushString();
	return *this;
}

ostream& operator <<(ostream &os,JSONObject &obj)
{
	return os<<obj.toString();
}

JSONObject& JSONObject::remove(const string &key)
{
	if(root){
		cJSON_DeleteItemFromObject(root,key.c_str());
	}
	flushString();
	return *this;
}







