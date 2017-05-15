/*************************************************************************
	> File Name: DevLevt.h
	> Brief: 延时事件上传接口 
	> Author: Chen Kai(chenkai878@pingan.com.cn)
	> Created Time: 五  5/12 16:13:41 2017
 ************************************************************************/
#ifndef _DEVLEVT_H
#define _DEVLEVT_H
class DevLevt:public HTTPRequest
{
    public:
        DevLevt(const string& cmd_type);
        ~DevLevt();
        void doAssembleParam();
        int handle(json::Value& jsPara);

    private:
        string res;//属性列表
        string code;//数组类型，0：ok，1：继续上传res 内容，2：更新属性上传列表，3：更新恶意程度
        int evl;//恶意度
        DECL_LOGGER(logger);
}
#endif

