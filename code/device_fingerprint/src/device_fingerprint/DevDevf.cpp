/*************************************************************************
	> File Name: DevDevf.cpp
	> Brief: 初始化接口
	> Author: Chen Kai(chenkai878@pingan.com.cn)
	> Created Time: Fri 12 May 2017 11:38:30 AM CST
 ************************************************************************/

#include "DevDevf.h"
IMPL_LOGGER(DevDevf, logger);

DevDevf::DevDevf(const string& cmd_type):HTTPRequest(cmd_type)
{
    LOG4CPLUS_DEBUG(logger, __FUNCTION__ << "(" << this << ")");
    map<string, pair<string, bool> > base_params = {
               {"info", make_pair(PARAM_TYPE_ARRAY, true)}, //info
    };
    m_params.insert(base_params.begin(), base_params.end());

    tb_name = g_config_reader->get_string("dev_devf.table");
}

DevDevf::~DevDevf()
{
    LOG4CPLUS_DEBUG(logger, __FUNCTION__ << "(" << this << ")");
}

/*************************************************************************
 * Brief: 组装返回参数
 * Params:
 * Return:
 * Author: Chen Kai(ischenkai.com)
 * Created Time:  一  5/15 15:23:59 2017
 *************************************************************************/
void DevDevf::doAssembleParam()
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
int DevDevf::handle(json::Value& jsPara)
{
    return 0;
}
