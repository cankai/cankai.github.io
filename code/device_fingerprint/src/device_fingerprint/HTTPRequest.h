#ifndef _HTTP_REQUEST_H_
#define _HTTP_REQUEST_H_

#include "common/Logger.h"
#include <stdint.h>
#include "common/Json.hpp"
#include "common/Utility.h"
#include "fastcgi/fcgiapp.h"
#include "common/ConfigReader.h"
#include "common/MutexLock.h"
#include "Defines.h"
#include "string"
#include <map>
using namespace std;

extern ConfigReader *g_config_reader;
class HTTPRequest
{
public:
    HTTPRequest(const std::string &cmd_type);
    HTTPRequest(){}

    virtual ~HTTPRequest();
    void clear_status();
    virtual int handle(FCGX_Request* request);
    virtual int handle(json::Value& jsPara);
    bool paraMatch(json::Value& jsPara);
    virtual void doAssembleParam();
    int doAssembleSql();
    std::string m_cmd_type;
    
    //para
    std::map<std::string, std::pair<std::string, bool> > m_params;

    std::map<std::string, std::string> urlParam;//request params map
    json::Value jsReturn;
    json::Value wrapperJsReturn;
    //tb
    std::string tb_name;
    std::string store_sql;

    int status;//200 or 500 表示服务状态
private:
    
    //rt 
    int pr;//协议版本
    std::string aid;//应用标识
    std::string eid;//消息id
    std::string tid;//应用启动时生产，退出时结束
    std::string msg;//提示描述信息

    DECL_LOGGER(logger);
};
#endif //_HTTP_REQUEST_H_
