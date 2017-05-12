#include "RedisSentinel.h"
#include <hiredis/hiredis.h>
#include "Utility.h"
IMPL_LOGGER(RedisSentinel, logger);

std::string RedisSentinel::sentinel2node(std::string sentinel_info, const int connet_timeout)
{
    LOG4CPLUS_DEBUG(logger,"");
    std::vector<std::string> sentinel_host;
    int senti_count = Utility::split(sentinel_info, ":", sentinel_host);
    int errcode;
    std::string errmsg;
    std::string redis_ip;
    std::string redis_port;
    //the format is ip:port:name
    if (senti_count == 3)
    {
        std::string host_ip = sentinel_host[0];
        int host_port = atoi(sentinel_host[1].c_str());
        std::string host_name = sentinel_host[2];
        redisReply* redis_reply = NULL;
        redisContext* redis_context = NULL;
        if (connet_timeout <= 0)
        {
            redis_context = redisConnect(host_ip.c_str(), host_port);
        }
        else
        {
            struct timeval connect_timeout;
            connect_timeout.tv_sec = connet_timeout / 1000;
            connect_timeout.tv_usec = (connet_timeout % 1000) * 1000;
            redis_context = redisConnectWithTimeout(host_ip.c_str(), host_port, connect_timeout);
        }
        if (NULL == redis_context)
        {
            LOG4CPLUS_ERROR(logger,"connect node error: " << sentinel_info);
            return ":";
        }
        else if (redis_context->err != 0)
        {
            errcode = redis_context->err;
            errmsg = redis_context->errstr;
            redisFree(redis_context);
            redis_context = NULL;
    
            LOG4CPLUS_WARN(logger,"connect node error,error code:" << errcode << "err message:" << errmsg);
            return ":";
        }
        LOG4CPLUS_DEBUG(logger,"connected " << host_ip << ":" << host_port);
        //set redis command
        char redis_command[128] = {0};
        sprintf(redis_command, "SENTINEL master %s",sentinel_host[2].c_str());
        redis_reply = (redisReply*)redisCommand(redis_context, redis_command);

        if (NULL == redis_reply)
        {
            errcode = -3;
            errmsg = "redis get sentinel error";
            LOG4CPLUS_DEBUG(logger,"connected " << host_ip << ":" << host_port << ",error:" << errcode << ":" << errmsg << ":" << redis_context->err << ":" << redis_context->errstr);
            redisFree(redis_context);
            redis_context = NULL;
            return ":";
        }
        else if (redis_reply->type == REDIS_REPLY_ARRAY)
        {
            for(int i = 0; i != redis_reply->elements; ++i)
            {
                //find ip, then next element is ip
                if(strcmp(redis_reply->element[i]->str,"ip") == 0)
                {
                    redis_ip = redis_reply->element[++i]->str;
                }
                //find port, then next element is ip
                if(strcmp(redis_reply->element[i]->str,"port") == 0)
                {
                    redis_port = redis_reply->element[++i]->str;
                }
            }
        }
        else
        {
            LOG4CPLUS_DEBUG(logger, "get real port and ip failed:" << sentinel_info);
        }
    }
    else
    {
        LOG4CPLUS_ERROR(logger,"Sentinel info is error,the right format is host:port:name,the source is:" << sentinel_info << " count:" << senti_count);
        return ":";
    }
    LOG4CPLUS_DEBUG(logger, "get real ip " << redis_ip << " port " << redis_port);
    return redis_ip+":"+redis_port;
}

RedisSentinel::RedisSentinel(const std::string& host, const std::string& passwd, int timeout) throw (CRedisException)
{
    LOG4CPLUS_DEBUG(logger,"");
    std::vector<std::string> sentinel_info;
    int senti_count = Utility::split(host, ",", sentinel_info);
    for(std::vector<std::string>::iterator sent_index = sentinel_info.begin();
                                 sent_index != sentinel_info.end();
                                 ++sent_index)
    {
        std::string redis_info = sentinel2node(*sent_index, timeout);
        if(redis_info.compare(":") != 0)
        {
            try
            {
                CRedisClient *redis_connect = new CRedisClient(redis_info, passwd, timeout);
                redis_connect->m_isuse = false;
                redis_clients.push_back(redis_connect);
            }
            catch(...)
            {
                LOG4CPLUS_WARN(logger, "redis connect error:" << redis_info);
            }
        }
    }
}

CRedisClient *RedisSentinel::get_redis_connect(const std::string &key)
{
    CRedisClient *redis = NULL;
    int key_hash = Utility::hash(key.c_str());
    int key_index = key_hash%redis_clients.size();
    try
    {
        if(redis_clients[key_index]->is_active())
        {
            redis = redis_clients[key_index];
            return redis;
        }
        else
        {
            LOG4CPLUS_WARN(logger,
                "redispool_list[" << key_index << "]" << redis_clients[key_index] <<
                " failed to is_active");
            return NULL;
        }
    }
    catch(...)
    {
        LOG4CPLUS_WARN(logger, "redis error");
        redis = NULL;
    }
    return redis;
}

bool RedisSentinel::set(const std::string& key, const std::string& value, std::pair<std::string, uint16_t>* which) throw (CRedisException)
{
    LOG4CPLUS_DEBUG(logger,"");
    CRedisClient *redis = get_redis_connect(key);
    if(!redis)
    {
        LOG4CPLUS_WARN(logger,"get redis error");
        return false;
    }
    return redis->set(key, value);
}

bool RedisSentinel::get(const std::string& key, std::string* value, std::pair<std::string, uint16_t>* which) throw (CRedisException)
{
    LOG4CPLUS_DEBUG(logger,"get:" << key);
    CRedisClient *redis = get_redis_connect(key);
    if(!redis)
    {
        LOG4CPLUS_WARN(logger,"get redis error");
        return false;
    }
    return redis->get(key, value);
}

bool RedisSentinel::del(const std::string& key, std::pair<std::string, uint16_t>* which) throw (CRedisException)
{
    LOG4CPLUS_DEBUG(logger,"");
    CRedisClient *redis = get_redis_connect(key);
    if(!redis)
    {
        LOG4CPLUS_WARN(logger,"get redis error");
        return false;
    }
    return redis->del(key);
}

bool RedisSentinel::expire(const std::string& key, uint32_t seconds, std::pair<std::string, uint16_t>* which) throw (CRedisException)
{
    LOG4CPLUS_DEBUG(logger,"");
    CRedisClient *redis = get_redis_connect(key);
    if(!redis)
    {
        LOG4CPLUS_WARN(logger,"get redis error");
        return false;
    }
    return redis->expire(key, seconds);
}

bool RedisSentinel::is_active(std::pair<std::string, uint16_t>* which) throw (CRedisException)
{
    bool active  = false;
    LOG4CPLUS_DEBUG(logger,"");
    for(std::vector<CRedisClient*>::iterator redis_index = redis_clients.begin();
                                    redis_index != redis_clients.end(); ++redis_index)
    {
        CRedisClient* redis = *redis_index;
        active = redis->is_active();
        if(!active) return false;
    }
    return active;
}
