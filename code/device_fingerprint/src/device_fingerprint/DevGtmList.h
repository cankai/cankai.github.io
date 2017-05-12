/*************************************************************************
	> File Name: DevGtmList.h
	> Brief: 
	> Author: Chen Kai(chenkai878@pingan.com.cn)
	> Created Time: 五  5/12 15:32:09 2017
 ************************************************************************/
#ifndef _DEVGTMLIST_H
#define _DEVGTMLIST_H
class DevGtmList:public HTTPRequest
{
    public:
        DevGtmList();
        ~DevGtmList();
        void doAssembleParam();
        int handle(json::Value& jsPara);
    private:
        //rt
        string code;
        string res;
        //上传间隔，单位s
        int interval;
        DECL_LOGGER(logger);
}
#endif

