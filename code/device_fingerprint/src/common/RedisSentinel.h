#ifndef _REDIS_SENTINEL_H
#define _REDIS_SENTINEL_H
#include <string>
#include <vector>
#include "Logger.h"
#include "RedisClusterClient.h"
class RedisSentinel:public CRedisClient
{
public:
    std::string sentinel2node(std::string sentinel_info, const int time_out);
    RedisSentinel(const std::string& nodes, const std::string& password="", int connect_timeout_milliseconds=CONNECT_TIMEOUT_MILLISECONDS) throw (CRedisException);
    virtual ~RedisSentinel()
    {
    }
    virtual bool set(const std::string& key, const std::string& value, std::pair<std::string, uint16_t>* which=NULL) throw (CRedisException);
    virtual bool get(const std::string& key, std::string* value, std::pair<std::string, uint16_t>* which=NULL) throw (CRedisException);
    virtual bool del(const std::string& key, std::pair<std::string, uint16_t>* which=NULL) throw (CRedisException);
    virtual bool expire(const std::string& key, uint32_t seconds, std::pair<std::string, uint16_t>* which=NULL) throw (CRedisException);
    virtual bool is_active(std::pair<std::string, uint16_t>* which=NULL) throw (CRedisException);
    CRedisClient *get_redis_connect(const std::string &key);
    DECL_LOGGER(logger);
private:
    std::vector<CRedisClient*> redis_clients;
    std::vector<std::pair<std::string, uint16_t> > _nodes;
};

#endif

