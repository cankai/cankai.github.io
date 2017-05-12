/*************************************************************************
	> File Name: DevTime.h
	> Brief: 
	> Author: Chen Kai(chenkai878@pingan.com.cn)
	> Created Time: 五  5/12 16:04:30 2017
 ************************************************************************/
#ifndef _DEVTIMER_H
#define _DEVTIMER_H
class DevTimer:public HTTPRequest
{
    public:
        DevTimer(const string& cmd_type);
    private:
        string code;
        string res;
        string interval;
}
#endif

