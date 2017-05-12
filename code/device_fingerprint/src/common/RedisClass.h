#ifndef REDISCLASS_H
#define REDISCLASS_H
 
#include <hiredis.h>
#include <string>
#include <vector>
#include "Logger.h"
#include "RedisClusterClient.h"
using namespace std;
 
class RedisConnectionPool {
  public:
    RedisConnectionPool() {
        pthread_mutex_init(&redispool_lock, NULL);
    } 
    RedisConnectionPool(int sent_flag, unsigned poolsize,
                       const std::string & host, const int & time_out, const std::string& passwd);
    RedisConnectionPool(const RedisConnectionPool &);
    virtual ~ RedisConnectionPool();

    bool Init();
    void set_size(uint32_t size);

    CRedisClient *get_redis_connect(bool autocreate = true);
    void release_connect(CRedisClient * redis);
    bool isActive();
    std::string gethost()const {
        return m_host;
    }

    int gettimeout() const {
        return m_timeout;
    }
    std::string m_host;
    std::string m_passwd;
    int m_timeout;
    std::vector < CRedisClient * >redispool_list;
    pthread_mutex_t redispool_lock;
    DECL_LOGGER(logger);
};

#endif
