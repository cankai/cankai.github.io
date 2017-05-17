#ifndef _HTTPREQUESTPOOL_H
#define _HTTPREQUESTPOOL_H
#include <string>
#include <vector>
#include <common/Exception.h>
#include "DevBuss.h"
#include "DevDevf.h"
#include "DevGevtList.h"
#include "DevGtmList.h"
#include "DevLevt.h"
#include "DevTimer.h"
#include "DevUevt.h"
#include "DevUpList.h"
#include <sys/time.h>
#include <map>
#include <vector>

#include "common/Logger.h"
using namespace std;

class HTTPRequestPool {
  public:
    HTTPRequestPool() {
        pthread_mutex_init(&http_pool_lock, NULL);
    } 
    HTTPRequestPool(unsigned poolsize);
    void set_size (uint32_t size);
    HTTPRequestPool(const HTTPRequestPool & dbc_pool);
    virtual ~ HTTPRequestPool();

    //get HTTPRequest from pool
    HTTPRequest* createHTTPRequest(const string& cmd_type);
    HTTPRequest *get_http_request(string cmd_type, bool autocreate = true);
    //return HTTPRequest to pool
    void release_http_request(HTTPRequest * http);
    void release_request_pool(vector<pair<HTTPRequest*,bool> >*);
    
    vector<pair<HTTPRequest*, bool> >dev_up_list;
    vector<pair<HTTPRequest*, bool> >dev_devf;
    vector<pair<HTTPRequest*, bool> >dev_gtm_list;
    vector<pair<HTTPRequest*, bool> >dev_timer;
    vector<pair<HTTPRequest*, bool> >dev_gevlist;
    vector<pair<HTTPRequest*, bool> >dev_uevt;
    vector<pair<HTTPRequest*, bool> >dev_levt;
    vector<pair<HTTPRequest*, bool> >dev_buss;
    
    //lock
    pthread_mutex_t http_pool_lock;
    DECL_LOGGER(logger);
};
#endif
