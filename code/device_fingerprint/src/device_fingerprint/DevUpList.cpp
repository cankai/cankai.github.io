/*************************************************************************
	> File Name: DevUpList.cpp
	> Brief: 初始化上报信息查询接口
             根据上报的信息操作系统，系统版本，网络类型，返回采集列表
	> Author: Chen Kai(chenkai878@pingan.com.cn)
	> Created Time: Fri 12 May 2017 10:52:19 AM CST
 ************************************************************************/

#include "DevUpList.h"
IMPL_LOGGER(DevUpList, logger);

DevUpList::DevUpList(const string& cmd_type):HTTPRequest(cmd_type)
{
    LOG4CPLUS_DEBUG(logger, __FUNCTION__ << "(" << this << ")");
    map<string, pair<string, bool> > base_params = {
               {"os", make_pair(PARAM_TYPE_STRING, true)}, //操作系统
               {"sv", make_pair(PARAM_TYPE_STRING, true)}, //系统版本号
               {"nt", make_pair(PARAM_TYPE_STRING, true)} //网络类型
    };
    m_params.insert(base_params.begin(), base_params.end());

    tb_name = g_config_reader->get_string("dev_up_list.table");
}

DevUpList::~DevUpList()
{
}

/*************************************************************************
 * Brief: 组装返回参数
 * Params:
 * Return:
 * Author: Chen Kai(ischenkai.com)
 * Created Time:  一  5/15 15:23:59 2017
 *************************************************************************/
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
