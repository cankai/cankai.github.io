#ifndef _DEFINES_H_
#define _DEFINES_H_

// HTML
#define HTTP_HTML_HEADER "Content-type: text/html; charset=utf-8\r\n\r\n"
// JSON
#define JSON_HTTP_HTML_HEADER "Content-type: application/json; charset=utf-8\r\n\r\n"

#define HTTP_STATUS_SUCC           200
#define HTTP_STATUS_INALID         404
#define HTTP_STATUS_PROTOCAL_ERROR 416
#define HTTP_STATUS_SVR_SIE        500

#define HTTP_200_REASON_PHRASE     "OK"
#define HTTP_404_REASON_PHRASE     "Not Found"
#define HTTP_416_REASON_PHRASE     "Protocal Error"
#define HTTP_500_REASON_PHRASE     "Internal Server Error"

#define DEV_UP_LIST                 "/dev/uplist" //初始化上报信息查询接口
#define DEV_INIT                    "/dev/devf"   //初始化接口
#define DEV_GET_TIME_LIST           "/dev/gtmlist"//定时上传列表获取
#define DEV_TIMER                   "/dev/timer"  //定时上传接口
#define DEV_GET_EVENT_LIST          "/dev/gevlist"//事件上传列表获取
#define DEV_UP_EVENT                "/dev/uevt"   //延立即事件上接口
#define DEV_LATER_EVENT             "/dev/levt"   //延时事件上传接口
#define DEV_BUSSINESS               "/dev/buss"   //业务埋点上传

#define ACCOUNT_ACCEPT             "accept"
#define ACCOUNT_REFUSE             "refuse"
#define ACCOUNT_REVIEW             "review"

#define PARAM_TYPE_STRING          "Ss"
#define PARAM_TYPE_INT             "i"
#define PARAM_TYPE_DOUBLE          "d"
#define PARAM_TYPE_ARRAY           "a"


#endif
