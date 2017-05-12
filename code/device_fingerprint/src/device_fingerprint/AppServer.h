#ifndef APPSERVER_H
#define APPSERVER_H
#include "fastcgi/fcgi_config.h"
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>
#include "fastcgi/fcgiapp.h"
#include "common/Utility.h"
#include "common/Logger.h"
#include "common/Queue.h"
#include "HTTPRequestHandler.h"
#include <string>
#include <vector>
class AppServer
{
    public:
        AppServer();
        ~AppServer();
        void run(int thread_count);
        int processRequest(FCGX_Request* request);
        static void *doit(void*);
        static void *process(void*);
        void work(int thread_count);
        static void sign_t(int sign);

    private:
        HTTPRequestHandler* m_request_handler;
        Queue<FCGX_Request*> *tasks;
        DECL_LOGGER(logger);
};
#endif
