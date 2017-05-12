/*************************************************************************
	> File Name: DevGtmList.cpp
	> Brief: 
	> Author: Chen Kai(chenkai878@pingan.com.cn)
	> Created Time: 五  5/12 15:31:59 2017
 ************************************************************************/
#include "DevGtmList.h"

IMPL_LOGGER(DevGtmList);
DevGtmList::DevGtmList(const string& cmd_type):HttpReuest(cmd_type)
{
    LOG4CPLUS_DEBUG(logger, __FUNCTION__ << "(" << this << ")");
}

DevGtmList::~DevGtmList()
{

}

void DevGtmList::doAssembleParam()
{

}

int DevGtmList::handle(json::Value& jsPara)
{
    return 0;
}


