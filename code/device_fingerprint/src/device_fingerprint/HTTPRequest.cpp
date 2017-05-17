#include "HTTPRequest.h"
#include "Defines.h"
#include "fastcgi/fcgi_lib.h"
#include "common/Json.hpp"
#include "RecordCache.h"
#include <cstdlib>

IMPL_LOGGER(HTTPRequest,logger);
HTTPRequest::HTTPRequest(const string &cmd_type)
:m_cmd_type(cmd_type)
{
    LOG4CPLUS_DEBUG(logger, __FUNCTION__ << "(" << this << ")");
    map<string, pair<string, bool> > base_params = {
               {"pr", make_pair(PARAM_TYPE_INT, true)}, //协议版本
               {"aid", make_pair(PARAM_TYPE_STRING, true)}, //应用标示
               {"eid", make_pair(PARAM_TYPE_STRING, true)}, //消息id
               {"tid", make_pair(PARAM_TYPE_STRING, true)}, //应用启动时生成/退出时结束
               {"skv", make_pair(PARAM_TYPE_STRING, true)} //sdk version
    };

    m_params.insert(base_params.begin(), base_params.end());

    //rt data
    pr = 0;
    aid = "";
    eid = "";
    tid = ""; 
    skv = "";
    status = HTTP_STATUS_SUCC;
    msg = HTTP_200_REASON_PHRASE;
    jsReturn = json::Deserialize("{}");
}

HTTPRequest::~HTTPRequest()
{
    LOG4CPLUS_DEBUG(logger, __FUNCTION__ << "(" << "destruction function" << ")");
}

void HTTPRequest::clear_status()
{
    //rt data
    pr = 0;
    aid = "";
    eid = "";
    tid = ""; 
    skv = "";
    status = HTTP_STATUS_SUCC;
    msg = HTTP_200_REASON_PHRASE;
    jsReturn = json::Deserialize("{}");
}

bool HTTPRequest::paraMatch(json::Value& jsPara)
{
    LOG4CPLUS_DEBUG(logger, __FUNCTION__ << "(" << this << ")");
    json::Object objPara = jsPara.ToObject();
    for (map<string, pair<string, bool> >::iterator it = m_params.begin(); 
         it != m_params.end(); ++it)
    {
        string key = it->first;
        string type = it->second.first;
        if(jsPara.HasKey(key))
        {
            json::Value value = objPara[key];
            //store all value as string include int and double
            //the front send all data value as string
            if (type.compare(PARAM_TYPE_STRING) == 0 && value.IsString())
            {
                urlParam[key] = value.ToString();
            }
            else if (type.compare(PARAM_TYPE_INT) == 0 && value.IsNumeric())
            {
                urlParam[key] = Utility::format(value.ToInt());
            }
            else if (type.compare(PARAM_TYPE_DOUBLE) == 0 && value.IsNumeric())
            {
                urlParam[key] = Utility::format(value.ToInt());
            }
            else if (type.compare(PARAM_TYPE_DOUBLE) == 0 && value.IsString())
            {
                urlParam[key] = value.ToString();
            }
            else if (type.compare(PARAM_TYPE_ARRAY) == 0 && value.IsArray())
            {
                urlParam[key] = value.ToArray().ToString();
            }
            else
            {
                LOG4CPLUS_DEBUG(logger, "key type error:" << key << value.IsNumeric() << value.IsString());
                return false;
            }

        }
        else//没有找到
        {
            if (it->second.second) //必选参数
            {
                LOG4CPLUS_DEBUG(logger, "required param key not found:" << key);
                return false;
            }
            else
            {
                if (type.compare(PARAM_TYPE_STRING) == 0 || type.compare(PARAM_TYPE_ARRAY) == 0)
                {
                    //LOG4CPLUS_DEBUG(logger, "required param key not found:" << key);
                    if(key.compare("cdata") == 0) urlParam[key] = "{}";
                    else if(key.compare("cararr") == 0) urlParam[key] = "{}";
                    else 
                    {
                        urlParam[key] = "";
                    }
                }
                else
                {
                    urlParam[key] = "-1";
                }
            }
        }
    }
    return true;
}

int HTTPRequest::handle(FCGX_Request* request)
{
    LOG4CPLUS_DEBUG(logger, __FUNCTION__ << "(" << this << ")");
    char* params = get_params(*request);
    unescape_url(params);
    try{
        json::Value jsPara = json::Deserialize(params);
        if(params)
        {
            free(params);
            params = NULL;
        }
        if (paraMatch(jsPara))
        {
            return handle(jsPara);
        }
        else
        {
            status = HTTP_STATUS_PROTOCAL_ERROR;
            msg = HTTP_416_REASON_PHRASE;
            LOG4CPLUS_DEBUG(logger, "para un match");
            return -2;
        }
    }
    catch (exception& e)
    {
        status = HTTP_STATUS_SVR_SIE;
        msg = HTTP_500_REASON_PHRASE;
        LOG4CPLUS_ERROR(logger, "Thread exception: "<<e.what());
        if(params)
        {
            free(params);
            params = NULL;
        }
        return -1;
    }
    catch(...)
    {
        status = HTTP_STATUS_SVR_SIE;
        msg = HTTP_500_REASON_PHRASE;
        LOG4CPLUS_ERROR(logger, "Unknown exception in thread");
        if(params)
        {
            free(params);
            params = NULL;
        }
        return -1;
    }
    if(params)
    {
        free(params);
        params = NULL;
    }
    return 1;
}

int HTTPRequest::handle(json::Value& jsPara) {
    LOG4CPLUS_DEBUG(logger, __FUNCTION__ << "(" << this << ")");
    try{
        msg = "";
        status = 200;
        return 0;
    }
    catch (exception& e)
    {
        status = HTTP_STATUS_SVR_SIE;
        msg = HTTP_500_REASON_PHRASE;
        LOG4CPLUS_ERROR(logger, "Thread exception: "<<e.what());
        return -1;
    }
    catch(...)
    {
        status = HTTP_STATUS_SVR_SIE;
        msg = HTTP_500_REASON_PHRASE;
        LOG4CPLUS_ERROR(logger, "Unknown exception in thread");
        return -1;
    }
    return 0;
}
void HTTPRequest::doAssembleParam()
{
    jsReturn["eid"] = eid;
    jsReturn["status"] = status;
    jsReturn["msg"] = msg;
    jsReturn["tid"] = tid;
}
int HTTPRequest::doAssembleSql()
{
    //urlParam
    try{
        string keys;
        string values;
        for(map<string, string>::iterator it = urlParam.begin();
                                                         it != urlParam.end(); ++it)
        {
            string key = it->first;
            string value = it->second;
            if(key.compare("from")==0)
            {
                keys.append("channel").append(",");
            }
            else
            {
                keys.append(key).append(",");
            }
    
            string type;
            if(m_params.find(key) != m_params.end())
            {
                type = m_params[key].first;
            }
            else
            {
                //type = (*m_optinal_params)[key];
                continue;
            }
            //if (it->second.second && (((key.compare(key_sp1) == 0) || (key.compare(key_sp2) == 0)) && proc_sp == true)) //必选参数
            if(type.compare(PARAM_TYPE_STRING) == 0)
            {
                Utility::replace_all(value, "'" , "''");
                values.append("'").append(value).append("',");
            }
            else if(type.compare(PARAM_TYPE_INT) == 0)
            {
        int tmpProc = atoi(it->second.c_str());
                values.append(Utility::format(tmpProc)).append(",");
            }
            else if(type.compare(PARAM_TYPE_DOUBLE) == 0)
            {
                values.append(it->second).append(",");
            }
            else if (type.compare(PARAM_TYPE_ARRAY) == 0)
            {
                values.append("'").append(value).append("',");
            }
            else;
        }
    
        stringstream sql_buff;

        sql_buff << "INSERT INTO " << tb_name << "(" << keys << "createtime)" << "VALUES(" << values << "'" << Utility::get_local_datestring() << "')";
        RecordCache::GetInstance()->AddExecuteSql(sql_buff.str());
        return 0;
    }
    catch (exception& e)
    {
        status = HTTP_STATUS_SVR_SIE;
        msg = HTTP_500_REASON_PHRASE;
        LOG4CPLUS_ERROR(logger, "Thread exception: "<<e.what());
        return -1;
    }
    catch(...)
    {
        status = HTTP_STATUS_SVR_SIE;
        msg = HTTP_500_REASON_PHRASE;
        LOG4CPLUS_ERROR(logger, "Unknown exception in thread");
        return -1;

    }
}
