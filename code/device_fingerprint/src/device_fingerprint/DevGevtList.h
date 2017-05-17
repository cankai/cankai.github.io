/*************************************************************************
	> File Name: DevGevtList.h
	> Brief: 事件上传列表获取
	> Author: Chen Kai(chenkai878@pingan.com.cn)
	> Created Time: 五  5/12 16:12:32 2017
 ************************************************************************/
#ifndef _DEVGEVTLIST_H
#define _DEVGEVTLIST_H
#include "HTTPRequest.h"
class DevGevtList:public HTTPRequest
{
    public:
        DevGevtList(const string& cmd_type);
        ~DevGevtList();
        void doAssembleParam();
        int handle(json::Value& jsPara);
        
    private:
        string code;
        string res;
        int evl;
        DECL_LOGGER(logger);
};
#endif

