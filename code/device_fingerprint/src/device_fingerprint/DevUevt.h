/*************************************************************************
	> File Name: DevUevt.h
	> Brief: 立即事件上传接口
	> Author: Chen Kai(chenkai878@pingan.com.cn)
	> Created Time: 五  5/12 16:13:10 2017
 ************************************************************************/
#ifndef _DEVUEVT_H
#define _DEVUEVT_H
#include "HTTPRequest.h"
class DevUevt:public HTTPRequest
{
    public:
        DevUevt(const string& cmd_type);
        ~DevUevt();
        void doAssembleParam();
        int handle(json::Value& jsPara);
        string getRes(string& os, string& version, string& net_type);

    private:
        string res;//属性列表
        string code;//数组类型，0：ok，1：继续上传res 内容，2：更新属性上传列表，3：更新恶意程度
        int evl;//恶意度
        DECL_LOGGER(logger);
};
#endif

