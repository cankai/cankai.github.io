#ifndef RECORD_CACHE__H
#define RECORD_CACHE__H
#include <map>
#include <string>
#include <vector>
#include "common/Thread.h"
#include "common/RedisClusterClient.h"
#include "common/RedisClass.h"
#include "common/Json.hpp"
#include "common/Logger.h"
#include "common/MutexLock.h"
#include "common/PGDBConnectionPool.h"

class RecordCache : public Thread{
    public:
        static RecordCache * GetInstance();
        void LoadDB();
        void ResetDeviceRedis();
        void ResetRedis();
        bool SaveToDB(const string&);
        int AddToCache(vector<string>& keys, string& key, string& rawData, string pno="", string cno="");
        int AddExecuteSql(const string& sql, int times=3);
        static void *syncDB(void* data);
        static bool deviceInfoChange(json::Value jsCache, json::Value jsIn);
        string getDeviceFingerprint(string &dataCrypt,string cno, string pno);
        int recordSize();
        ~RecordCache();
        Lock _db_lock;
    private:
        RecordCache();
        void run();
        static RecordCache * _instance;
        static Lock _instance_lock;
        map<string, string>  *device_fingerprint_info;
        map<string, string>  *device_fingerprint_info_update;
        map<string, string>  *device_fingerprint_info_buffer;
        map<string, string>  *device_fingerprint_info_latest;
        vector<pair<string, int> > *execute_sql;
        PGDBConnectionPool account_service_db_pool;
        bool setValue(const string &key, const string &val);
        bool getValue(const string& key, string& value);
        bool hasKey(const string& key, string &value);
        bool redisHasKey(const string& key, string &value);
        bool cacheHasKey(const string& key, string &value);
        bool pgHasKey(const string& key, string &value);
        bool delKey(const string& key);
        RedisConnectionPool *account_service_redis_pool;
        int pools_size;
        string  _db_table_name;
        DECL_LOGGER(logger);
};
#endif
