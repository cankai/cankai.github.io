/*************************************************************************
	> File Name: DevBuss.h
	> Brief: 业务埋点上传【待完善】
	> Author: Chen Kai(chenkai878@pingan.com.cn)
	> Created Time: 五  5/12 16:14:05 2017
 ************************************************************************/
#ifndef _DEVBUSS_H
#include "HTTPRequest.h"
class DevBuss:public HTTPRequest
{
    public:
        DevBuss(const string& cmd_type);
        ~DevBuss();
        void doAssembleParam();
        int handle(json::Value& jsPara);

    private:
        string res;//属性列表
        string code;//数组类型，0：ok，1：继续上传res 内容，2：更新属性上传列表，3：更新恶意程度
        int evl;//恶意度
        DECL_LOGGER(logger);
};
#define _DEVBUSS_H
#endif

