/*************************************************************************
	> File Name: DevTimer.h
	> Brief: 定时长传接口
	> Author: Chen Kai(chenkai878@pingan.com.cn)
	> Created Time: 五  5/12 16:04:30 2017
 ************************************************************************/
#ifndef _DEVTIMER_H
#define _DEVTIMER_H
#include "HTTPRequest.h"
class DevTimer:public HTTPRequest
{
    public:
        DevTimer(const string& cmd_type);
        ~DevTimer();
        void doAssembleParam();
        int handle(json::Value& jsPara);

    private:
        string code;//0 ok, 2 更新定时上传列表, 3 更新 evl
        string res;//属性列表
        int tv;//当 code等于2时出现
        int evl;
        DECL_LOGGER(logger);
};
#endif

