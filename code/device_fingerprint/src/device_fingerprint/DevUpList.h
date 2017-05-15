/*************************************************************************
	> File Name: DevUpList.h
	> Brief: 初始化上报信息查询接口
	> Author: Chen Kai(chenkai878@pingan.com.cn)
	> Created Time: Fri 12 May 2017 10:52:27 AM CST
 ************************************************************************/

#ifndef _DEVUPLIST_H
#define _DEVUPLIST_H
#include "HTTPRequest.h"
class DevUpList:public HTTPRequest
{
    public:
        DevUpList(const string& cmd_type);
        ~DevUpList();
        void doAssembleParam();
        int handle(json::Value& jsPara);
        string getRes(string& os, string& version, string& net_type);

    private:
        string res;
        int code;
        DECL_LOGGER(logger);
}
#endif
