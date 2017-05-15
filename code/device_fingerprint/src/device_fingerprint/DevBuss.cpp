/*************************************************************************
	> File Name: DevBuss.cpp
	> Brief: 
	> Author: Chen Kai(chenkai878@pingan.com.cn)
	> Created Time: 五  5/12 16:14:08 2017
 ************************************************************************/
#include "DevBuss.h"
IMPL_LOGGER(DevBuss);

DevBuss::DevBuss(const string& cmd_type):HTTPRequest(cmd_type)
{
    LOG4CPLUS_DEBUG(logger, __FUNCTION__ << "(" << this << ")");
    std::map<std::string, std::pair<std::string, bool> > base_params = {
               {"in", std::make_pair(PARAM_TYPE_STRING, true)}, //采集数据
               {"dev", std::make_pair(PARAM_TYPE_STRING, true)}, //设备指纹
    };
    m_params.insert(base_params.begin(), base_params.end());

    tb_name = g_config_reader->get_string("dev_buss.table");
 }
 DevBuss::~DevBuss()
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
void DevBuss::doAssembleParam()
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
int DevBuss::handle(json::Value& jsPara)
{
    return 0;
}
