/*************************************************************************
	> File Name: DevGtmList.cpp
	> Brief: 定时上传列表获取
	> Author: Chen Kai(chenkai878@pingan.com.cn)
	> Created Time: 五  5/12 15:31:59 2017
 ************************************************************************/
#include "DevGtmList.h"

IMPL_LOGGER(DevGtmList);
DevGtmList::DevGtmList(const string& cmd_type):HttpReuest(cmd_type)
{
    LOG4CPLUS_DEBUG(logger, __FUNCTION__ << "(" << this << ")");
    std::map<std::string, std::pair<std::string, bool> > base_params = {
               {"net", std::make_pair(PARAM_TYPE_STRING, true)}, //info
               {"os", std::make_pair(PARAM_TYPE_STRING, true)}, //android,ios linux,windows
               {"ver", std::make_pair(PARAM_TYPE_STRING, true)}, //version
    };
    m_params.insert(base_params.begin(), base_params.end());

    tb_name = g_config_reader->get_string("dev_gtmlist.table");
}

DevGtmList::~DevGtmList()
{
    LOG4CPLUS_DEBUG(logger, __FUNCTION__ << "(" << this << ")");
}

/*************************************************************************
 * Brief: 组装返回json
 * Params:
 * Return:
 * Author: Chen Kai(ischenkai.com)
 * Created Time:  一  5/15 15:32:55 2017
 *************************************************************************/
void DevGtmList::doAssembleParam()
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
int DevGtmList::handle(json::Value& jsPara)
{
    return 0;
}
