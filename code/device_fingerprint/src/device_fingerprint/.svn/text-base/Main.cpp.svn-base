#include "fastcgi/fcgi_config.h"
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>
#include "fastcgi/fcgiapp.h"
#include "RecordCache.h"
#include "AppServer.h"
#include "common/ConfigReader.h"
#include "common/Logger.h"
#include <log4cplus/configurator.h>
#include <signal.h>
//#include "dc/dc.main.hpp"
using namespace log4cplus;


ConfigReader *g_config_reader;

int main(void)
{
    PropertyConfigurator::doConfigure("../conf/log4cpluscplus.properties");
    Logger logger = Logger::getInstance("main_logger");

    g_config_reader = new ConfigReader("../conf/svr.conf");
    if (!g_config_reader->load()){
        LOG4CPLUS_ERROR(logger, "config load failed");
        return -1;
    }

    int thread_count = 1;
    thread_count = g_config_reader->get_int("server.thread.num", 2);
    LOG4CPLUS_DEBUG(logger, "server start thread num:" << thread_count);

    //ignore
    signal(SIGHUP, SIG_IGN);
    signal(SIGPIPE, SIG_IGN);
    signal(SIGTTOU, SIG_IGN);
    signal(SIGTTIN, SIG_IGN);
    signal(SIGCHLD, SIG_IGN);
    //signal(SIGEMT, SIG_IGN);

    //debug
    //signal(SIGSEGV, AppServer::sign_t);

    //RecordCache::GetInstance()->LoadDB();
    RecordCache::GetInstance()->start();
    //dc
    //DC::GetInstance()->start();
    FCGX_Init();
    AppServer app_svr;
    app_svr.work(thread_count);
    app_svr.run(thread_count);

    return 0;
}

