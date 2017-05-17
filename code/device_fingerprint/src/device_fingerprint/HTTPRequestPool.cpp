#include "HTTPRequestPool.h"
#include <errmsg.h>
#include <sys/time.h>
using namespace std;

IMPL_LOGGER (HTTPRequestPool, logger);

const string support_cmd[] = {DEV_UP_LIST,DEV_INIT,DEV_GET_TIME_LIST,DEV_TIMER,DEV_GET_EVENT_LIST,DEV_UP_EVENT,DEV_LATER_EVENT,DEV_BUSSINESS};

HTTPRequestPool::HTTPRequestPool (unsigned poolsize)
{
    pthread_mutex_init (&http_pool_lock, NULL);
    HTTPRequest *http_request = NULL;
    set_size(poolsize);
}

HTTPRequest* HTTPRequestPool::createHTTPRequest(const string& cmd_type)
{
    HTTPRequest *http_request = NULL;
    if (Utility::is_end_with(cmd_type, DEV_UP_LIST))
    {
        http_request = new DevUpList(cmd_type);
        dev_up_list.push_back(make_pair(http_request, false));
    }
    else if (Utility::is_end_with(cmd_type, DEV_INIT))
    {
        http_request = new DevDevf(cmd_type);
        dev_devf.push_back(make_pair(http_request, false));
    }
    else if (Utility::is_end_with(cmd_type, DEV_GET_TIME_LIST))
    {
        http_request = new DevGtmList(cmd_type);
        dev_gtm_list.push_back(make_pair(http_request, false));
    }
    else if (Utility::is_end_with(cmd_type, DEV_TIMER))
    {
        http_request = new DevTimer(cmd_type);
        dev_timer.push_back(make_pair(http_request, false));
    }
    else if (Utility::is_end_with(cmd_type, DEV_GET_EVENT_LIST))
    {
        http_request = new DevGevtList(cmd_type);
        dev_gevt_list.push_back(make_pair(http_request, false));
    }
    else if (Utility::is_end_with(cmd_type, DEV_UP_EVENT))
    {
        http_request = new DevUevt(cmd_type);
        dev_uevt.push_back(make_pair(http_request, false));
    }
    else if (Utility::is_end_with(cmd_type, DEV_LATER_EVENT))
    {
        http_request = new DevLevt(cmd_type);
        dev_levt.push_back(make_pair(http_request, false));
    }
    else if (Utility::is_end_with(cmd_type, DEV_BUSSINESS))
    {
        http_request = new DevBuss(cmd_type);
        dev_buss.push_back(make_pair(http_request, false));
    }
    else
    {
        LOG4CPLUS_ERROR(logger,"unspourt cmd:" << cmd_type);
    }
    return http_request;
}

void HTTPRequestPool::set_size (uint32_t poolsize)
{
    HTTPRequest *http_request = NULL;
    for (unsigned i = 0; i < poolsize; i++)
    {
        for(unsigned j = 0; j < sizeof(support_cmd)/sizeof(support_cmd[0]); j++)
        {
            createHTTPRequest(support_cmd[j]);
        }
    }
}

HTTPRequestPool::HTTPRequestPool (const HTTPRequestPool & http_pool)
{
    pthread_mutex_init (&http_pool_lock, NULL);
    for (unsigned i = 0, size = http_pool.dev_up_list.size(); i < size; i++)
    {
        createHTTPRequest(http_poll.dev_up_list[i].first->m_cmd_type);
    }
    for (unsigned i = 0, size = http_pool.dev_devf.size(); i < size; i++)
    {
        createHTTPRequest(http_poll.dev_devf[i].first->m_cmd_type);
    }
    for (unsigned i = 0, size = http_pool.dev_gtm_list.size(); i < size; i++)
    {
        createHTTPRequest(http_poll.dev_gtm_list[i].first->m_cmd_type);
    }
    for (unsigned i = 0, size = http_pool.dev_timer.size(); i < size; i++)
    {
        createHTTPRequest(http_poll.dev_timer[i].first->m_cmd_type);
    }
    for (unsigned i = 0, size = http_pool.dev_gevt_list.size(); i < size; i++)
    {
        createHTTPRequest(http_poll.dev_gevt_list[i].first->m_cmd_type);
    }
    for (unsigned i = 0, size = http_pool.dev_uevt.size(); i < size; i++)
    {
        createHTTPRequest(http_poll.dev_uevt[i].first->m_cmd_type);
    }
    for (unsigned i = 0, size = http_pool.dev_levt.size(); i < size; i++)
    {
        createHTTPRequest(http_poll.dev_levt[i].first->m_cmd_type);
    }
    for (unsigned i = 0, size = http_pool.dev_buss.size(); i < size; i++)
    {
        createHTTPRequest(http_poll.dev_buss[i].first->m_cmd_type);
    }
}


HTTPRequestPool::~HTTPRequestPool ()
{
    release_request_pool(&dev_up_list);
    release_request_pool(&dev_devf);
    release_request_pool(&dev_gtm_list);
    release_request_pool(&dev_timer);
    release_request_pool(&dev_gevt);
    release_request_pool(&dev_uevt);
    release_request_pool(&dev_levt);
    release_request_pool(&dev_buss);
    pthread_mutex_destroy (&http_pool_lock);
}

void HTTPRequestPool::release_request_pool(vector<pair<HTTPRequest*,bool> >*http_request_pool)
{
    for (unsigned i = 0, size = http_request_pool->size(); i < size; i++)
    {
        if ((*http_request_pool)[i].first != NULL)
        {
            delete (*http_request_pool)[i].first;
            (*http_request_pool)[i].first = NULL;
        }
    }
    http_request_pool->clear();
}

HTTPRequest *HTTPRequestPool::get_http_request (string cmd_type,bool autocreate)
{
    HTTPRequest *http_request = NULL;
    vector<pair<HTTPRequest*,bool> >*http_request_pool = NULL;
    pthread_mutex_lock (&http_pool_lock);
    try
    {
        if (Utility::is_end_with(cmd_type, DEV_UP_LIST))
        {
            http_request_pool = &dev_up_list;
        }
        else
        {
            LOG4CPLUS_ERROR(logger, "Unknow cmd:" << cmd_type);
            return NULL;
        }
        LOG4CPLUS_DEBUG(logger, "" << cmd_type << " pool size is:" << http_request_pool->size());
        for (unsigned i = 0; i < http_request_pool->size(); i++)
        {
            //found a unused http request
            if ((*http_request_pool)[i].first != NULL && (*http_request_pool)[i].second == false)
            {
                (*http_request_pool)[i].second = true;
                http_request = (*http_request_pool)[i].first;
                break;
            }
        }
    }
    catch (...)
    {
        LOG4CPLUS_ERROR(logger, "Exception found");
        http_request = NULL;
    }
    // if not found, then create a new HTTPRequest
    if (http_request == NULL && autocreate)
    {
        LOG4CPLUS_DEBUG(logger, "HTTPRequest not found and create a new one:" << cmd_type);
        http_request = createHTTPRequest(cmd_type);
    }
    pthread_mutex_unlock (&http_pool_lock);
    return http_request;
}

void HTTPRequestPool::release_http_request(HTTPRequest * http_request)
{
    pthread_mutex_lock (&http_pool_lock);

    try
    {
        vector<pair<HTTPRequest*,bool> >*http_request_pool = NULL;
        string cmd_type = http_request->m_cmd_type;
        if (Utility::is_end_with(cmd_type, DEV_UP_LIST))
        {
            http_request_pool = &dev_up_list;
        }
        else if (Utility::is_end_with(cmd_type, DEV_INIT))
        {
            http_request_pool = &dev_devf;
        }
        else if (Utility::is_end_with(cmd_type, DEV_GET_TIME_LIST))
        {
            http_request_pool = &dev_gtm_list;
        }
        else if (Utility::is_end_with(cmd_type, DEV_TIMER))
        {
            http_request_pool = &dev_timer;
        }
        else if (Utility::is_end_with(cmd_type, DEV_GET_EVENT_LIST))
        {
            http_request_pool = &dev_gevt_list;
        }
        else if (Utility::is_end_with(cmd_type, DEV_UP_EVENT))
        {
            http_request_pool = &dev_uevt;
        }
        else if (Utility::is_end_with(cmd_type, DEV_LATER_EVENT))
        {
            http_request_pool = &dev_levt;
        }
        else if (Utility::is_end_with(cmd_type, DEV_BUSSINESS))
        {
            http_request_pool = &dev_buss;
        }
        else
        {
            LOG4CPLUS_ERROR(logger, "Unknow cmd:" << cmd_type);
        }
        for (unsigned i = 0; i < http_request_pool->size(); i++)
        {
            if ((*http_request_pool)[i].first == http_request)
            {
                (*http_request_pool)[i].first->clear_status();
                (*http_request_pool)[i].second = false;
                break;
            }
        }
    }
    catch (...)
    {
        LOG4CPLUS_ERROR(logger, "Exception found");
    }
    pthread_mutex_unlock (&http_pool_lock);
}
