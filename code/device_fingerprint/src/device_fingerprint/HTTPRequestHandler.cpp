#include "HTTPRequestHandler.h"
#include "Defines.h"
#include "DevBuss.h"
#include "DevDevf.h"
#include "DevGevtList.h"
#include "DevGtmList.h"
#include "DevLevt.h"
#include "DevTimer.h"
#include "DevUevt.h"
#include "DevUpList.h"
#include "fastcgi/fcgi_lib.h"
#include <sys/time.h>

IMPL_LOGGER(HTTPRequestHandler, logger);

HTTPRequestHandler::HTTPRequestHandler()
{
    LOG4CPLUS_DEBUG(logger, __FUNCTION__ << "(" << this << ")");
}


HTTPRequestHandler::~HTTPRequestHandler()
{
    LOG4CPLUS_DEBUG(logger, __FUNCTION__ << "(" << this << ")");
}

void HTTPRequestHandler::set_size(int size)
{
    http_request_pool.set_size(size);
}


string HTTPRequestHandler::get_request_cmd(FCGX_Request* request)
{
    char *request_method = FCGX_GetParam("SCRIPT_NAME", request->envp);
    return string(request_method);
}

int HTTPRequestHandler::process(FCGX_Request* request)
{
    struct timeval tBegin,tEnd;
    gettimeofday(&tBegin, NULL);
    HTTPRequest* http_req = create(request);
    if (http_req)
    {
        if (http_req->handle(request) != 0)
        {
            gettimeofday(&tEnd, NULL);
            LOG4CPLUS_WARN(logger, "handle cmd_type:" << http_req->m_cmd_type << " failed");
            LOG4CPLUS_INFO(logger, "cmd:" << http_req->m_cmd_type << " status:" << false << " time:" << (tEnd.tv_sec-tBegin.tv_sec)*1000000+(tEnd.tv_usec - tBegin.tv_usec));
        }
        else
        {
            gettimeofday(&tEnd, NULL);
            LOG4CPLUS_INFO(logger, "cmd:" << http_req->m_cmd_type << " status:" << true << " time:" << (tEnd.tv_sec-tBegin.tv_sec)*1000000+(tEnd.tv_usec - tBegin.tv_usec));
        }
    }
    else
    {
        gettimeofday(&tEnd, NULL);
        LOG4CPLUS_INFO(logger, "cmd:" << get_request_cmd(request) << " status:" << true << " time:" << (tEnd.tv_sec-tBegin.tv_sec)*1000000+(tEnd.tv_usec - tBegin.tv_usec));
    }
    return render(request, http_req);
}

int HTTPRequestHandler::render(FCGX_Request* request, HTTPRequest* http_req)
{
    LOG4CPLUS_DEBUG(logger, __FUNCTION__ << "(" << this << ")");

    if (http_req)
    {
        json::Object jsObj = http_req->jsReturn.ToObject();

        http_req->doAssembleParam();
        FCGX_FPrintF(request->out,
            JSON_HTTP_HTML_HEADER
            "{\"ret\":%d,\"msg\":\"%s\",\"data\":%s}",http_req->status,http_req->msg.c_str(),json::Serialize(http_req->jsReturn).c_str());
        http_request_pool.release_http_request(http_req);
        FCGX_Finish_r(request);
    }
    else
    {
        FCGX_FPrintF(request->out,
            JSON_HTTP_HTML_HEADER
            "{\"ret\":%d,\"msg\":\"%s\",\"data\":%s}",1,"404, not found","");
        FCGX_Finish_r(request);
    }
}

HTTPRequest* HTTPRequestHandler::create(FCGX_Request* request)
{
    string cmd_type = get_request_cmd(request);
    HTTPRequest* http_req = NULL;
    return http_request_pool.get_http_request(cmd_type);
}

