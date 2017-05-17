/*************************************************************************
	> File Name: DevGevtList.cpp
	> Brief: 事件上传列表获取,包括及时上传时间，限时上传时间
	> Author: Chen Kai(ischenkai@qq.com)
	> Home: http://www.chenkai.me
	> Created Time: 一  5/15 16:32:10 2017
 ************************************************************************/
#include "DevGevtList.h"
IMPL_LOGGER(DevGevtList, logger);

DevGevtList::DevGevtList(const string& cmd_type):HTTPRequest(cmd_type)
{
    LOG4CPLUS_DEBUG(logger, __FUNCTION__ << "(" << this << ")");
    map<string, pair<string, bool> > base_params = {
               {"in", make_pair(PARAM_TYPE_STRING, true)}, //采集数据
               {"dev", make_pair(PARAM_TYPE_STRING, true)}, //设备指纹
    };
    m_params.insert(base_params.begin(), base_params.end());

    tb_name = g_config_reader->get_string("dev_gevt_list.table");
 }
 DevGevtList::~DevGevtList()
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
void DevGevtList::doAssembleParam()
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
int DevGevtList::handle(json::Value& jsPara)
{
    return 0;
}
