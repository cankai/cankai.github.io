/*************************************************************************
	> File Name: DevGevtLit.cpp
	> Brief: 
	> Author: Chen Kai(chenkai878@pingan.com.cn)
	> Created Time: 五  5/12 16:12:36 2017
 ************************************************************************/


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

