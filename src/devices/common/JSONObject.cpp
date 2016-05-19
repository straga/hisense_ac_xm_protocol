
#include "../../include/JSONObject.h"

JSONObject::JSONObject(const string &jsStr){
	root = cJSON_Parse(jsStr.c_str());
}

JSONObject :: JSONObject(const JSONObject &in){
	root = cJSON_Parse(in.toString().c_str());
}

JSONObject :: ~JSONObject(){
	cJSON_Delete(root);
	root = NULL;
}
string JSONObject::toString()const
{
	char *c_str = NULL;
	string str;
#ifdef DEBUG
	c_str = cJSON_Print(root);
#else
	c_str = cJSON_PrintUnformatted(root);
#endif
	str = c_str;
	cJSON_free(c_str);
	return str;
}

void JSONObject::clear(void)
{
	cJSON_Delete(root);
	root = NULL;
}

void JSONObject::putNumber(const string key,int value){
	if(root){
		cJSON_AddNumberToObject(root,key.c_str(),value);
	}
}

void JSONObject::putString(const string key,const string str){
	if(root){
		cJSON_AddStringToObject(root,key.c_str(),str.c_str());
	}
}

int JSONObject:: getNumber(const string key){
	cJSON *item = cJSON_GetObjectItem(root,key.c_str());
	if(item)
		return item->valueint;
	return 0;
}
string JSONObject:: getString(const string key){
	cJSON *item = cJSON_GetObjectItem(root,key.c_str());
	if(item)
		return item->valuestring;
	return NULL;
}

JSONObject& JSONObject ::operator= (const JSONObject &in){
	if(this == &in) //¼ì²é×Ô¸³Öµ
		return *this;
	if(root){
		cJSON_Delete(root);
	}
	root = cJSON_Parse(in.toString().c_str());
	return *this;
}

ostream& operator <<(ostream &os,JSONObject &obj)
{
	return os<<obj.toString();
}

JSONObject& JSONObject::remove(const string key)
{
	if(root){
		cJSON_DeleteItemFromObject(root,key.c_str());
	}
	return *this;
}







