#include "AppServer.h"
#include "fastcgi/fcgi_lib.h"
#include "fastcgi/fcgiapp.h"
#include "fastcgi/fcgio.h"
#include "common/CryptTask.hpp"
#include "common/Json.hpp"
#include <iostream>
#include <pthread.h>
#include <stdlib.h>
using namespace std;

IMPL_LOGGER(AppServer, logger);

AppServer::AppServer()
{
    tasks = new Queue<FCGX_Request*>(100);
    m_request_handler = new HTTPRequestHandler();
    m_request_handler->set_size(100);
    LOG4CPLUS_DEBUG(logger, __FUNCTION__ << "(" << this << ")");
}


AppServer::~AppServer()
{
    delete m_request_handler;
    m_request_handler = NULL;
    delete tasks;
    tasks = NULL;
    LOG4CPLUS_DEBUG(logger, __FUNCTION__ << "(" << this << ")");
}


void AppServer::run(int thread_count)
{
    pthread_t *id_list = (pthread_t*)malloc(thread_count * sizeof(pthread_t));
    for (int i = 1; i < thread_count; i++)
        pthread_create(&id_list[i], NULL, doit, (void*)this);
    doit(this);
}

void AppServer::work(int thread_count)
{
    pthread_t *id_list = (pthread_t*)malloc(thread_count * sizeof(pthread_t));
    for (int i = 0; i < thread_count; i++)
        pthread_create(&id_list[i], NULL, process, (void*)this);
}

void* AppServer::process(void* para)
{
    AppServer* svr = (AppServer*)para;
    for (;;)
    {
        FCGX_Request *request = NULL;
        if(!svr->tasks->pop(request,20))
        {
            continue;
        }
        LOG4CPLUS_DEBUG(logger, "pop succed");
        int prt =  svr->processRequest(request);

    delete request;
        LOG4CPLUS_DEBUG(logger, "process:" << pthread_self() << " rt:" << prt);
    }
    return NULL;
}

void* AppServer::doit(void* para)
{
    int rc;
    AppServer* svr = (AppServer*)para;
    for (;;)
    {
        FCGX_Request *request = new FCGX_Request;
        FCGX_InitRequest(request, 0, 0);
        static pthread_mutex_t accept_mutex = PTHREAD_MUTEX_INITIALIZER;
        pthread_mutex_lock(&accept_mutex);
        rc = FCGX_Accept_r(request);
        pthread_mutex_unlock(&accept_mutex);

        if (rc < 0)
            break;

        if(!svr->tasks->push(request,20))
        {
            LOG4CPLUS_DEBUG(logger, "process:" << pthread_self());
        }
        LOG4CPLUS_DEBUG(logger, "getCapacity:" << svr->tasks->getCapacity() << " getSize:"<<svr->tasks->getSize());
    }

    return NULL;
}

int AppServer::processRequest(FCGX_Request* request)
{
    return m_request_handler->process(request);
}

void AppServer::sign_t(int sign)
{
    LOG4CPLUS_ERROR(logger, "error!! in thread:" << pthread_self());
    abort();
}