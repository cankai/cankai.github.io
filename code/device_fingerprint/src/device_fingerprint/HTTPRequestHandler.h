#ifndef _HTTP_REQUEST_HANDLER_
#define _HTTP_REQUEST_HANDLER_
#include "common/Logger.h"
#include "HTTPRequest.h"
#include "HTTPRequestPool.h"

#include <string>


class HTTPRequestHandler {
public:
    HTTPRequestHandler();

    ~HTTPRequestHandler();
    int process(FCGX_Request* request);
    int render(FCGX_Request* request, HTTPRequest* http_req);
    string get_request_cmd(FCGX_Request* request);
    HTTPRequestPool http_request_pool;
    void set_size(int size);

private:
    HTTPRequest* create(FCGX_Request* request);

private:
    DECL_LOGGER(logger);
};

#endif //_HTTP_REQUEST_HANDLER_



