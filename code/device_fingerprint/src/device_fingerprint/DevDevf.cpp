/*************************************************************************
	> File Name: DevDevf.cpp
	> Brief: 
	> Author: Chen Kai(chenkai878@pingan.com.cn)
	> Created Time: Fri 12 May 2017 11:38:30 AM CST
 ************************************************************************/

#include "DevDevf.h"
IMPL_LOGGER(DevDevf);
DevDevf::DevDevf(const string& cmd_type):HttpReuest(cmd_type)
{
    LOG4CPLUS_DEBUG(logger, __FUNCTION__ << "(" << this << ")");
}
DevDevf::~DevDevf()
{

}

void DevDevf::doAssembleParam()
{

}
int DevDevf::handle(json::Value& jsPara)
{

}
