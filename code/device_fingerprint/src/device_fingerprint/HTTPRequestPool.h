#ifndef _HTTPREQUESTPOOL_H
#define _HTTPREQUESTPOOL_H
#include <string>
#include <vector>
#include <common/Exception.h>
#include "AccountReg.h"
#include "AccountRegFeedback.h"
#include "AccountRegValidFB.h"
#include "AccountLogin.h"
#include "AccountLoginFB.h"
#include "AccountLoginValidFB.h"
#include "AccountCardBind.h"
#include "AccountCardBindFB.h"
#include "AccountCardUnbind.h"
#include "AccountCardUnbindFB.h"
#include "AccountPay.h"
#include "AccountPayFB.h"
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
    HTTPRequest *get_http_request(std::string cmd_type, bool autocreate = true);
    //return HTTPRequest to pool
    void release_http_request(HTTPRequest * http);
    void release_request_pool(std::vector<pair<HTTPRequest*,bool> >*);
    
    //reg
    //std::vector<pair<AccountReg*,bool> >account_reg;
    //std::vector<pair<AccountRegFeedback*,bool> >account_reg_feedback;
    //std::vector<pair<AccountRegValidFB*,bool> >account_reg_valid_fb;
    //login
    //std::vector<pair<AccountLogin*,bool> >account_login;
    //std::vector<pair<AccountLoginFB*,bool> >account_login_fb;
    //std::vector<pair<AccountLoginValidFB*,bool> >account_login_valid_fb;
    //card_bind
    //std::vector<pair<AccountCardBind*,bool> >account_card_bind;
    //std::vector<pair<AccountCardBindFB*,bool> >account_card_bind_fb;
    //card_unbind
    //std::vector<pair<AccountCardUnbind*,bool> >account_card_unbind;
    //std::vector<pair<AccountCardUnbindFB*,bool> >account_card_unbind_fb;
    //pay
    //std::vector<pair<AccountPay*,bool> >account_pay;
    //std::vector<pair<AccountPayFB*,bool> >account_pay_fb;
    //reg
    std::vector<pair<HTTPRequest*,bool> >account_reg;
    std::vector<pair<HTTPRequest*,bool> >account_reg_feedback;
    std::vector<pair<HTTPRequest*,bool> >account_reg_valid_fb;
    //login
    std::vector<pair<HTTPRequest*,bool> >account_login;
    std::vector<pair<HTTPRequest*,bool> >account_login_fb;
    std::vector<pair<HTTPRequest*,bool> >account_login_valid_fb;
    //card_bind
    std::vector<pair<HTTPRequest*,bool> >account_card_bind;
    std::vector<pair<HTTPRequest*,bool> >account_card_bind_fb;
    //card_unbind
    std::vector<pair<HTTPRequest*,bool> >account_card_unbind;
    std::vector<pair<HTTPRequest*,bool> >account_card_unbind_fb;
    //pay
    std::vector<pair<HTTPRequest*,bool> >account_pay;
    std::vector<pair<HTTPRequest*,bool> >account_pay_fb;
    //lock
    pthread_mutex_t http_pool_lock;
    DECL_LOGGER(logger);
};
#endif
