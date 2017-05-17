/*************************************************************************
	> File Name: DevGtmList.h
	> Brief: 定时上传列表获 
	> Author: Chen Kai(chenkai878@pingan.com.cn)
	> Created Time: 五  5/12 15:32:09 2017
 ************************************************************************/
#ifndef _DEVGTMLIST_H
#define _DEVGTMLIST_H
#include "HTTPRequest.h"
class DevGtmList:public HTTPRequest
{
    public:
        DevGtmList(const string&);
        ~DevGtmList();
        void doAssembleParam();
        int handle(json::Value& jsPara);

    private:
        //rt
        string code;
        string res;
        //上传间隔，单位s
        int tv;
        DECL_LOGGER(logger);
};
#endif

