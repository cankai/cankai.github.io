#include "fastcgi/fcgi_config.h"
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>
#include "fastcgi/fcgiapp.h"
#include "common/ConfigReader.h"
#include "common/Logger.h"
#include "account_service/HTTPRequest.h"
#include "account_service/AccountLogin.h"
#include <log4cplus/configurator.h>
#include <signal.h>
using namespace log4cplus;


ConfigReader *g_config_reader;
int g_thread_count = 1;

int main(void)
{
    PropertyConfigurator::doConfigure("../conf/log4cpluscplus.properties");
    Logger logger = Logger::getInstance("main_logger");

    g_config_reader = new ConfigReader("../conf/svr.conf");
    if (!g_config_reader->load()){
        LOG4CPLUS_ERROR(logger, "config load failed");
        return -1;
    }
    FCGX_Request request;
    FCGX_InitRequest(&request, 0, 0);
    for (int i = 0; i <= 1000000; ++i)
    {
        HTTPRequest* http_req = NULL;
        http_req  = new AccountLogin("login", &request);
        delete http_req;
    }
    return 0;
}

