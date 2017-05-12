#include "RedisClass.h"
#include "RedisSentinel.h"
#include "Utility.h"
#include <string>
using namespace std;
 
IMPL_LOGGER(RedisConnectionPool, logger);
RedisConnectionPool::RedisConnectionPool(int sent_flag, unsigned poolsize, 
                                        const std::string & host, 
                                        const int & time_out,
                                        const std::string & pass_wd): m_host(host), m_timeout(time_out), m_passwd(pass_wd)
{
    pthread_mutex_init(&redispool_lock, NULL);
/*
 *redis sentinel
 *
 *sentinel info:10.2.133.13:6410,10.2.133.14:6410,10.2.133.15:6410
 *
 *to get real redis node,first to connetct to redis sentinel
 */
    if (sent_flag == 1)
    {
        LOG4CPLUS_DEBUG(logger, "redis sentinel");
        for(unsigned i = 0; i < poolsize; i++)
        {
            try
            {
                CRedisClient *redis_connect = new RedisSentinel(m_host, m_passwd, m_timeout);
                redis_connect->m_isuse = false;
                redispool_list.push_back(redis_connect);
            }
            catch(...)
            {
                LOG4CPLUS_WARN(logger, "redis connect error");
            }
        }
    /*
        vector<std::string> sentinel_info;
        std::string new_host;
        int senti_count = Utility::split(host, ",", sentinel_info);
        for(vector<std::string>::iterator sent_index = sentinel_info.begin();
                                     sent_index != sentinel_info.end();
                                     ++sent_index)
        {
            std::string redis_info = RedisSentinel::sentinel2node(*sent_index, time_out);
            if(redis_info.compare(":") != 0)
            {
                new_host += redis_info;
            }
            for(unsigned i = 0; i < poolsize; i++)
            {
                if(new_host.size() > 5)
                {
                    try
                    {
                        CRedisClient *redis_connect = new RedisSentinel(new_host, m_passwd, m_timeout);
                        redis_connect->m_isuse = false;
                        redispool_list.push_back(redis_connect);
                    }
                    catch(...)
                    {
                        LOG4CPLUS_WARN(logger, "redis connect error:" << redis_info);
                    }
                }
            }
        }
    */
    }
    else
    {
        for(unsigned i = 0; i < poolsize; i++)
        {
            try
            {
                CRedisClient *redis_connect = new CRedisClient(m_host, m_passwd, m_timeout);
                redis_connect->m_isuse = false;
                redispool_list.push_back(redis_connect);
            }
            catch(...)
            {
                LOG4CPLUS_WARN(logger, "redis connect error");
            }
        }
    }
    LOG4CPLUS_INFO(logger, "redis num is:" << redispool_list.size());
}

RedisConnectionPool::RedisConnectionPool(const RedisConnectionPool & redis_connect_pool)
{
    m_host = redis_connect_pool.m_host;
    m_timeout = redis_connect_pool.m_timeout;
    pthread_mutex_init(&redispool_lock, NULL);
    for(unsigned i = 0, size = redis_connect_pool.redispool_list.size(); i < size; i++)
    {
        CRedisClient *redis_connect = new CRedisClient(m_host, m_passwd, m_timeout);
        redispool_list.push_back(redis_connect);
    }
}

bool RedisConnectionPool::isActive()
{
    return redispool_list.size() > 0;
}
RedisConnectionPool::~RedisConnectionPool()
{
    int nsize = redispool_list.size();
    for(int i = 0; i < nsize; i++)
    {
        if(redispool_list[i] != NULL)
        {
            delete redispool_list[i];
            redispool_list[i] = NULL;
        }
    }
    redispool_list.clear();
    pthread_mutex_destroy(&redispool_lock);
}

void RedisConnectionPool::set_size(uint32_t size)
{
    for(unsigned i = 0; i < size; i++)
    {
        CRedisClient *redis_connect = new CRedisClient(m_host, m_passwd, m_timeout);
        redispool_list.push_back(redis_connect);
    }
}


CRedisClient *RedisConnectionPool::get_redis_connect(bool autocreate)
{
    LOG4CPLUS_DEBUG(logger,"");
    CRedisClient *redis = NULL;
    pthread_mutex_lock(&redispool_lock);
    bool is_connect_fail = false;
    try
    {
        for(unsigned i = 0; i < redispool_list.size(); i++)
        {
            if(redispool_list[i] != NULL && !redispool_list[i]->m_isuse)
            {
                if(redispool_list[i]->is_active())
                {
                    redispool_list[i]->m_isuse = true;
                    redis = redispool_list[i];
                    break;
                }
                else
                {
                    LOG4CPLUS_WARN(logger,
                        "redispool_list[" << i << "]" << redispool_list[i] <<
                        " failed to is_active");
                    is_connect_fail = true;
                    redis = NULL;
                }
            }
        }
    }
    catch(...)
    {
        LOG4CPLUS_WARN(logger, "redis error");
        redis = NULL;
    }
    // if not found, then re-establish a new connection
    if(redis == NULL && autocreate && !is_connect_fail)
    {
        LOG4CPLUS_WARN(logger, "get redis error;create a new connect");
        redis = new CRedisClient(m_host, m_passwd, m_timeout);
        bool flag = redis->is_active();
        if(flag)
        {
            redis->m_isuse = true;
            redispool_list.push_back(redis);
        }
        else
        {
            delete redis;
            redis = NULL;
        }
    }
    pthread_mutex_unlock(&redispool_lock);
    return redis;
}

void RedisConnectionPool::release_connect (CRedisClient * redis)
{
    pthread_mutex_lock (&redispool_lock);
    try
    {
        for (unsigned i = 0; i < redispool_list.size (); i++)
        {
            if (redispool_list[i] == redis)
            {
                redispool_list[i]->m_isuse = false;
                break;
            }
        }
    }
    catch (...)
    {
        LOG4CPLUS_WARN(logger, "redis release error");
    }
    pthread_mutex_unlock (&redispool_lock);
}

