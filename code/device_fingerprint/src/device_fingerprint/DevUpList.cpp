/*************************************************************************
	> File Name: DevUpList.cpp
	> Brief: 
	> Author: Chen Kai(chenkai878@pingan.com.cn)
	> Created Time: Fri 12 May 2017 10:52:19 AM CST
 ************************************************************************/

#include "DevUpList.h"
IMPL_LOGGER(DevUpList);

DevUpList::DevUpList(const string& cmd_type):HTTPRequest(cmd_type)
{
    LOG4CPLUS_DEBUG(logger, __FUNCTION__ << "(" << this << ")");
    std::map<std::string, std::pair<std::string, bool> > base_params = {
               {"os", std::make_pair(PARAM_TYPE_STRING, true)}, //操作系统
               {"sv", std::make_pair(PARAM_TYPE_STRING, true)}, //系统版本号
               {"nt", std::make_pair(PARAM_TYPE_STRING, true)} //网络类型
    };
    m_params.insert(base_params.begin(), base_params.end());

    tb_name = g_config_reader->get_string("dev_up_list.table");
}

/*************************************************************************
 * Brief: 根据 OS，版本号，网络类型返回需要采集的列表，移动网络采集列表跟全
 * Params:
 * Return: 返回采集列表，如果列表表示异常
 * Author: Chen Kai(chenkai878@pingan.com.cn)
 * Created Time:  Fri 12 May 2017 11:33:00 AM CST
 *************************************************************************/
string DevUpList::getRes(string& os, string& version, string& net_type)
{
    return "";
}

void DevUpList::doAssembleParam()
{

    HTTPRequest::doAssembleParam();
}

/*************************************************************************
 * Brief: 处理接收到的json数据
 * Params: post 过来的json
 * Return:处理结果;0 正常，非0异常
 * Author: Chen Kai(ischenkai.com)
 * Created Time:  五  5/12 17:49:55 2017
 *************************************************************************/
int DevUpList::handle(json::Value& jsPara)
{
    return 0;
}
