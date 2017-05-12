/*************************************************************************
	> File Name: DevDevf.h
	> Brief: 
	> Author: Chen Kai(chenkai878@pingan.com.cn)
	> Created Time: Fri 12 May 2017 11:38:40 AM CST
 ************************************************************************/

#ifndef _DEVDEVF_H
#define _DEVDEVF_H
class DevDevf:public HTTPRequest
{
    public:
        DevDevf(const string& cmd_type);
        ~DevDevf();

        void doAssembleParam();
        int handle(json::Value& jsPara);
    private:
        string devf;
        string code;
        string res;
        int evi;
        DECL_LOGGER(logger);
}
#endif