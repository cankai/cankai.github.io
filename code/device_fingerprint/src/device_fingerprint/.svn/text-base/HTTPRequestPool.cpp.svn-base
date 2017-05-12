#include "HTTPRequestPool.h"
#include <errmsg.h>
#include <sys/time.h>
using namespace std;

IMPL_LOGGER (HTTPRequestPool, logger);

HTTPRequestPool::HTTPRequestPool (unsigned poolsize)
{
    pthread_mutex_init (&http_pool_lock, NULL);
    HTTPRequest *http_request = NULL;
    for (unsigned i = 0; i < poolsize; i++)
    {
        //reg
        http_request = new AccountReg(ACCOUNT_REG);
        account_reg.push_back(make_pair(http_request, false));
        //reg_fb
        http_request = new AccountRegFeedback(ACCOUNT_REG_FEEDBACK);
        account_reg_feedback.push_back(make_pair(http_request, false));
        //reg_valid_fb
        http_request = new AccountRegValidFB(ACCOUNT_REG_VALID_FB);
        account_reg_valid_fb.push_back(make_pair(http_request, false));
        //login
        http_request = new AccountLogin(ACCOUNT_LOGIN);
        account_login.push_back(make_pair(http_request, false));
        //login fb
        http_request = new AccountLoginFB(ACCOUNT_LOGIN_FB);
        account_login_fb.push_back(make_pair(http_request, false));
        //login valid fb
        http_request = new AccountLoginValidFB(ACCOUNT_LOGIN_VALID_FB);
        account_login_valid_fb.push_back(make_pair(http_request, false));
        //card bind
        http_request = new AccountCardBind(ACCOUNT_CARD_BIND);
        account_card_bind.push_back(make_pair(http_request, false));
        //card bind fb
        http_request = new AccountCardBindFB(ACCOUNT_CARD_BIND);
        account_card_bind.push_back(make_pair(http_request, false));
        //card unbind
        http_request = new AccountCardUnbind(ACCOUNT_CARD_UNBIND);
        account_card_unbind.push_back(make_pair(http_request, false));
        //card unbind fb
        http_request = new AccountCardUnbindFB(ACCOUNT_CARD_UNBIND);
        account_card_unbind.push_back(make_pair(http_request, false));
        //pay
        http_request = new AccountPay(ACCOUNT_PAY);
        account_pay.push_back(make_pair(http_request, false));
        //pay fb
        http_request = new AccountPay(ACCOUNT_PAY_FB);
        account_pay_fb.push_back(make_pair(http_request, false));
    }
}

void HTTPRequestPool::set_size (uint32_t poolsize)
{
    HTTPRequest *http_request = NULL;
    for (unsigned i = 0; i < poolsize; i++)
    {
        //reg
        http_request = new AccountReg(ACCOUNT_REG);
        account_reg.push_back(make_pair(http_request, false));
        //reg_fb
        http_request = new AccountRegFeedback(ACCOUNT_REG_FEEDBACK);
        account_reg_feedback.push_back(make_pair(http_request, false));
        //reg_valid_fb
        http_request = new AccountRegValidFB(ACCOUNT_REG_VALID_FB);
        account_reg_valid_fb.push_back(make_pair(http_request, false));
        //login
        http_request = new AccountLogin(ACCOUNT_LOGIN);
        account_login.push_back(make_pair(http_request, false));
        //login fb
        http_request = new AccountLoginFB(ACCOUNT_LOGIN_FB);
        account_login_fb.push_back(make_pair(http_request, false));
        //login valid fb
        http_request = new AccountLoginValidFB(ACCOUNT_LOGIN_VALID_FB);
        account_login_valid_fb.push_back(make_pair(http_request, false));
        //card bind
        http_request = new AccountCardBind(ACCOUNT_CARD_BIND);
        account_card_bind.push_back(make_pair(http_request, false));
        //card bind fb
        http_request = new AccountCardBindFB(ACCOUNT_CARD_BIND);
        account_card_bind.push_back(make_pair(http_request, false));
        //card unbind
        http_request = new AccountCardUnbind(ACCOUNT_CARD_UNBIND);
        account_card_unbind.push_back(make_pair(http_request, false));
        //card unbind fb
        http_request = new AccountCardUnbindFB(ACCOUNT_CARD_UNBIND);
        account_card_unbind.push_back(make_pair(http_request, false));
        //pay
        http_request = new AccountPay(ACCOUNT_PAY);
        account_pay.push_back(make_pair(http_request, false));
        //pay fb
        http_request = new AccountPay(ACCOUNT_PAY_FB);
        account_pay_fb.push_back(make_pair(http_request, false));
    }
}

HTTPRequestPool::HTTPRequestPool (const HTTPRequestPool & http_pool)
{
    pthread_mutex_init (&http_pool_lock, NULL);
    //reg
    for (unsigned i = 0, size = http_pool.account_reg.size(); i < size; i++)
    {
        HTTPRequest *http_request = new AccountReg(http_pool.account_reg[i].first->m_cmd_type);
        account_reg.push_back(make_pair(http_request, false));
    }
    for (unsigned i = 0, size = http_pool.account_reg_feedback.size(); i < size; i++)
    {
        HTTPRequest *http_request = new AccountRegFeedback(http_pool.account_reg_feedback[i].first->m_cmd_type);
        account_reg_feedback.push_back(make_pair(http_request, false));
    }
    for (unsigned i = 0, size = http_pool.account_reg_valid_fb.size(); i < size; i++)
    {
        HTTPRequest *http_request = new AccountRegValidFB(http_pool.account_reg_valid_fb[i].first->m_cmd_type);
        account_reg_valid_fb.push_back(make_pair(http_request, false));
    }
    //login
    for (unsigned i = 0, size = http_pool.account_login.size(); i < size; i++)
    {
        HTTPRequest *http_request = new AccountLogin(http_pool.account_login[i].first->m_cmd_type);
        account_login.push_back(make_pair(http_request, false));
    }
    for (unsigned i = 0, size = http_pool.account_login_fb.size(); i < size; i++)
    {
        HTTPRequest *http_request = new AccountLoginFB(http_pool.account_login_fb[i].first->m_cmd_type);
        account_login_fb.push_back(make_pair(http_request, false));
    }
    for (unsigned i = 0, size = http_pool.account_login_valid_fb.size(); i < size; i++)
    {
        HTTPRequest *http_request = new AccountLoginValidFB(http_pool.account_login_valid_fb[i].first->m_cmd_type);
        account_login_valid_fb.push_back(make_pair(http_request, false));
    }
    //cardbind
    for (unsigned i = 0, size = http_pool.account_card_bind.size(); i < size; i++)
    {
        HTTPRequest *http_request = new AccountCardBind(http_pool.account_card_bind[i].first->m_cmd_type);
        account_card_bind.push_back(make_pair(http_request, false));
    }
    for (unsigned i = 0, size = http_pool.account_card_bind_fb.size(); i < size; i++)
    {
        HTTPRequest *http_request = new AccountCardBindFB(http_pool.account_card_bind_fb[i].first->m_cmd_type);
        account_card_bind_fb.push_back(make_pair(http_request, false));
    }
    //cardunbind
    for (unsigned i = 0, size = http_pool.account_card_unbind.size(); i < size; i++)
    {
        HTTPRequest *http_request = new AccountCardUnbind(http_pool.account_card_unbind[i].first->m_cmd_type);
        account_card_unbind.push_back(make_pair(http_request, false));
    }
    for (unsigned i = 0, size = http_pool.account_card_unbind_fb.size(); i < size; i++)
    {
        HTTPRequest *http_request = new AccountCardUnbindFB(http_pool.account_card_unbind_fb[i].first->m_cmd_type);
        account_card_unbind_fb.push_back(make_pair(http_request, false));
    }
    //pay
    for (unsigned i = 0, size = http_pool.account_pay.size(); i < size; i++)
    {
        HTTPRequest *http_request = new AccountPay(http_pool.account_pay[i].first->m_cmd_type);
        account_pay.push_back(make_pair(http_request, false));
    }
    for (unsigned i = 0, size = http_pool.account_pay_fb.size(); i < size; i++)
    {
        HTTPRequest *http_request = new AccountPayFB(http_pool.account_pay_fb[i].first->m_cmd_type);
        account_pay_fb.push_back(make_pair(http_request, false));
    }
}


HTTPRequestPool::~HTTPRequestPool ()
{
    release_request_pool(&account_reg);
    release_request_pool(&account_reg_feedback);
    release_request_pool(&account_reg_valid_fb);
    release_request_pool(&account_login);
    release_request_pool(&account_login_fb);
    release_request_pool(&account_login_valid_fb);
    release_request_pool(&account_card_bind);
    release_request_pool(&account_card_bind_fb);
    release_request_pool(&account_card_unbind);
    release_request_pool(&account_card_unbind_fb);
    release_request_pool(&account_pay);
    release_request_pool(&account_pay_fb);
    pthread_mutex_destroy (&http_pool_lock);
}

void HTTPRequestPool::release_request_pool(std::vector<pair<HTTPRequest*,bool> >*http_request_pool)
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

HTTPRequest *HTTPRequestPool::get_http_request (std::string cmd_type,bool autocreate)
{
    HTTPRequest *http_request = NULL;
    std::vector<pair<HTTPRequest*,bool> >*http_request_pool = NULL;
    pthread_mutex_lock (&http_pool_lock);
    try
    {
        if (Utility::is_end_with(cmd_type, ACCOUNT_REG))
        {
            http_request_pool = &account_reg;
        }
        else if (Utility::is_end_with(cmd_type, ACCOUNT_REG_FEEDBACK))
        {
            http_request_pool = &account_reg_feedback;
        }
        else if (Utility::is_end_with(cmd_type, ACCOUNT_REG_VALID_FB))
        {
            http_request_pool = &account_reg_valid_fb;
        }
        else if (Utility::is_end_with(cmd_type, ACCOUNT_LOGIN))
        {
            http_request_pool = &account_login;
        }
        else if (Utility::is_end_with(cmd_type, ACCOUNT_LOGIN_FB))
        {
            http_request_pool = &account_login_fb;
        }
        else if (Utility::is_end_with(cmd_type, ACCOUNT_LOGIN_VALID_FB))
        {
            http_request_pool = &account_login_valid_fb;
        }
        else if (Utility::is_end_with(cmd_type, ACCOUNT_CARD_BIND))
        {
            http_request_pool = &account_card_bind;
        }
        else if (Utility::is_end_with(cmd_type, ACCOUNT_CARD_BIND_FB))
        {
            http_request_pool = &account_card_bind_fb;
        }
        else if (Utility::is_end_with(cmd_type, ACCOUNT_CARD_UNBIND))
        {
            http_request_pool = &account_card_unbind;
        }
        else if (Utility::is_end_with(cmd_type, ACCOUNT_CARD_UNBIND_FB))
        {
            http_request_pool = &account_card_unbind_fb;
        }
        else if (Utility::is_end_with(cmd_type, ACCOUNT_PAY))
        {
            http_request_pool = &account_pay;
        }
        else if (Utility::is_end_with(cmd_type, ACCOUNT_PAY_FB))
        {
            http_request_pool = &account_pay_fb;
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
        if (Utility::is_end_with(cmd_type, ACCOUNT_REG))
        {
            http_request = new AccountReg(cmd_type);
        }
        else if (Utility::is_end_with(cmd_type, ACCOUNT_REG_FEEDBACK))
        {
            http_request = new AccountRegFeedback(cmd_type);
        }
        else if (Utility::is_end_with(cmd_type, ACCOUNT_REG_VALID_FB))
        {
            http_request = new AccountRegValidFB(cmd_type);
        }
        else if (Utility::is_end_with(cmd_type, ACCOUNT_LOGIN))
        {
            http_request = new AccountLogin(cmd_type);
        }
        else if (Utility::is_end_with(cmd_type, ACCOUNT_LOGIN_FB))
        {
            http_request = new AccountLoginFB(cmd_type);
        }
        else if (Utility::is_end_with(cmd_type, ACCOUNT_LOGIN_VALID_FB))
        {
            http_request = new AccountLoginValidFB(cmd_type);
        }
        else if (Utility::is_end_with(cmd_type, ACCOUNT_CARD_BIND))
        {
            http_request = new AccountCardBind(cmd_type);
        }
        else if (Utility::is_end_with(cmd_type, ACCOUNT_CARD_BIND_FB))
        {
            http_request = new AccountCardBindFB(cmd_type);
        }
        else if (Utility::is_end_with(cmd_type, ACCOUNT_CARD_UNBIND))
        {
            http_request = new AccountCardUnbind(cmd_type);
        }
        else if (Utility::is_end_with(cmd_type, ACCOUNT_CARD_UNBIND_FB))
        {
            http_request = new AccountCardUnbindFB(cmd_type);
        }
        else if (Utility::is_end_with(cmd_type, ACCOUNT_PAY))
        {
            http_request = new AccountPay(cmd_type);
        }
        else if (Utility::is_end_with(cmd_type, ACCOUNT_PAY_FB))
        {
            http_request = new AccountPayFB(cmd_type);
        }
        else
        {
            LOG4CPLUS_ERROR(logger, "Unknow cmd:" << cmd_type);
            return NULL;
        }
        http_request_pool->push_back(make_pair(http_request,true));
    }
    pthread_mutex_unlock (&http_pool_lock);
    return http_request;
}

void HTTPRequestPool::release_http_request(HTTPRequest * http_request)
{
    pthread_mutex_lock (&http_pool_lock);

    try
    {
        std::vector<pair<HTTPRequest*,bool> >*http_request_pool = NULL;
        std::string cmd_type = http_request->m_cmd_type;
        if (Utility::is_end_with(cmd_type, ACCOUNT_REG))
        {
            http_request_pool = &account_reg;
        }
        else if (Utility::is_end_with(cmd_type, ACCOUNT_REG_FEEDBACK))
        {
            http_request_pool = &account_reg_feedback;
        }
        else if (Utility::is_end_with(cmd_type, ACCOUNT_REG_VALID_FB))
        {
            http_request_pool = &account_reg_valid_fb;
        }
        else if (Utility::is_end_with(cmd_type, ACCOUNT_LOGIN))
        {
            http_request_pool = &account_login;
        }
        else if (Utility::is_end_with(cmd_type, ACCOUNT_LOGIN_FB))
        {
            http_request_pool = &account_login_fb;
        }
        else if (Utility::is_end_with(cmd_type, ACCOUNT_LOGIN_VALID_FB))
        {
            http_request_pool = &account_login_valid_fb;
        }
        else if (Utility::is_end_with(cmd_type, ACCOUNT_CARD_BIND))
        {
            http_request_pool = &account_card_bind;
        }
        else if (Utility::is_end_with(cmd_type, ACCOUNT_CARD_BIND_FB))
        {
            http_request_pool = &account_card_bind_fb;
        }
        else if (Utility::is_end_with(cmd_type, ACCOUNT_CARD_UNBIND))
        {
            http_request_pool = &account_card_unbind;
        }
        else if (Utility::is_end_with(cmd_type, ACCOUNT_CARD_UNBIND_FB))
        {
            http_request_pool = &account_card_unbind_fb;
        }
        else if (Utility::is_end_with(cmd_type, ACCOUNT_PAY))
        {
            http_request_pool = &account_pay;
        }
        else if (Utility::is_end_with(cmd_type, ACCOUNT_PAY_FB))
        {
            http_request_pool = &account_pay_fb;
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
