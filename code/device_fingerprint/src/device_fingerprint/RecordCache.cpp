#include "RecordCache.h"
#include "common/ConfigReader.h"
#include "common/AutoSqlExecuter.h"
#include "common/Utility.h"
#include <unistd.h>


extern ConfigReader *g_config_reader;
IMPL_LOGGER(RecordCache, logger);

RecordCache * RecordCache::_instance = NULL;
Lock RecordCache::_instance_lock ;

RecordCache::RecordCache()
{
    device_fingerprint_info = new map<string, string>;//store all info no use
    device_fingerprint_info_update = new map<string, string>;//no use
    device_fingerprint_info_buffer = new map<string, string>;//data not in device_fingerprint_info not in redis not in pg
    device_fingerprint_info_latest = new map<string, string>;//store latest data,in 5 second the same data can not be store twice
    execute_sql = new vector<pair<string, int> >;
    account_service_db_pool.m_host = g_config_reader->get_string("account_service.db.host", "localhost");
    account_service_db_pool.m_port = g_config_reader->get_string("account_service.db.port", "3306");
    account_service_db_pool.m_dbname = g_config_reader->get_string("account_service.db.dbname", "account_service");
    account_service_db_pool.m_user = g_config_reader->get_string("account_service.db.user", "root");
    account_service_db_pool.m_passwd = g_config_reader->get_string("account_service.db.passwd", "mypw");
    _db_table_name = g_config_reader->get_string("account_service.db.tablename", "device_fingerprint");
    const int _device_fingerprint_info_connects = g_config_reader->get_int("account_service.db.connect.num",5);
    account_service_db_pool.set_size(_device_fingerprint_info_connects);

    //redis
    string redis_cluster_host = g_config_reader->get_string("account_service.redis.host.info", "10.33.47.51:6516,10.33.47.52:6518,10.33.47.53:6517");
    string redis_cluster_passwd = g_config_reader->get_string("account_service.redis.host.passwd", "paicH23G1234");
    int pool_size = g_config_reader->get_int("account_service.redis.connect.num", 5);
    int time_out = g_config_reader->get_int("account_service.redis.connect.timeout", 2000);
    int redis_sent_flag = g_config_reader->get_int("redis.sentinel.flag", 0);
    account_service_redis_pool = new RedisConnectionPool(redis_sent_flag,pool_size, redis_cluster_host, time_out, redis_cluster_passwd);
}

RecordCache * RecordCache::GetInstance()
{
    if(_instance == NULL){
        _instance_lock.lock();
        if(_instance == NULL){
            _instance = new RecordCache;
        }
        _instance_lock.unlock();
    }
    return _instance;
}

RecordCache::~RecordCache()
{
    delete device_fingerprint_info;
    device_fingerprint_info = NULL;
    delete device_fingerprint_info_update;
    device_fingerprint_info_update = NULL;
    delete device_fingerprint_info_buffer;
    device_fingerprint_info_buffer = NULL;
    delete device_fingerprint_info_latest;
    device_fingerprint_info_latest = NULL;
    delete execute_sql;
    execute_sql = NULL;
    delete account_service_redis_pool;
    account_service_redis_pool = NULL;
    LOG4CPLUS_DEBUG(logger, __FUNCTION__ << "(" << "destruction function" << ")");
}

bool RecordCache::setValue(const string &key, const string &value)
{
    if (!account_service_redis_pool->isActive())
    {
        LOG4CPLUS_WARN(logger,"redis is dead");
        return false;
    }
    CRedisClient *redis = account_service_redis_pool->get_redis_connect(true);
    if (!redis)
    {
        LOG4CPLUS_WARN(logger,"get redis connect error");
        return false;
    }
    bool set_rt = redis->set(key, value);
    account_service_redis_pool->release_connect(redis);
    return set_rt;
}

bool RecordCache::getValue(const string& key, string& value)
{
    LOG4CPLUS_DEBUG(logger,"get redis:"<<key);
    CRedisClient *redis = account_service_redis_pool->get_redis_connect(true);
    if (!redis)
    {
        LOG4CPLUS_WARN(logger,"get redis connect error");
        return false;
    }
    bool get_rt = redis->get(key, &value);
    account_service_redis_pool->release_connect(redis);
    return get_rt;
}
bool RecordCache::pgHasKey(const string& key, string &value)
{
    RecordCache *record_cache = RecordCache::GetInstance();
    stringstream sql_buf;
    sql_buf << "select data from " << record_cache->_db_table_name << " where deviceid='" << key << "'"; 
    AutoSqlExecuter query(&(record_cache->account_service_db_pool), sql_buf.str(), true);
    RES_RESULT * result = query.Records();
    while(result->next()){
        value = result->get_value_data();
        //no need mem cache
        //(*device_fingerprint_info)[key] = value;
        return true;
    }
    return false;
}

bool RecordCache::cacheHasKey(const string& key, string &value)
{
    //no reed to use mem cache
    return false;
#if 0
    map<string, string>::iterator infoCacheIt = device_fingerprint_info->find(key);
    if (infoCacheIt != device_fingerprint_info->end())
    {
        value = infoCacheIt->second;
        return true;
    }
    else
    {
        return false;
    }
#endif
}

bool RecordCache::redisHasKey(const string& key, string &value)
{
    /*
    CRedisClient *redis = account_service_redis_pool->get_redis_connect(true);
    if (!redis)
    {
        LOG4CPLUS_WARN(logger,"get redis connect error");
        return false;
    }
    */
    bool get_rt = getValue(key, value);
    //account_service_redis_pool->release_connect(redis);
    return get_rt;
}

bool RecordCache::hasKey(const string& key, string &value)
{
    if (account_service_redis_pool->isActive())
    {
    //for accout service,the key in the db and the pg is different
        string key_prefix = "account_";
        return cacheHasKey(key, value) || redisHasKey(key_prefix+key, value);
    }
    else
    {
        return cacheHasKey(key, value) || pgHasKey(key, value);
    }
}

bool RecordCache::delKey(const string& key)
{
    //no need mem cache
    //device_fingerprint_info->erase(key);
    if (account_service_redis_pool->isActive())
    {
        CRedisClient *redis = account_service_redis_pool->get_redis_connect(true);
        if (!redis)
        {
            LOG4CPLUS_WARN(logger,"get redis connect error");
            return false;
        }
        bool del_rt = redis->del(key);
        account_service_redis_pool->release_connect(redis);
        return del_rt;
    }
    else
    {
        return false;
    }
}

int RecordCache::recordSize()
{
    return device_fingerprint_info->size() + device_fingerprint_info_buffer->size();
}

bool RecordCache::deviceInfoChange(json::Value jsCache, json::Value jsIn)
{
    json::Object objCache = jsCache.ToObject();
    json::Object objIn = jsIn.ToObject();
    //if ads.id is change but token is not change
    return false;
}

int RecordCache::AddExecuteSql(const string& sql, int times)
{
    //for debug
    //return 1;
    //for debug
    _instance_lock.lock();
    execute_sql->push_back(make_pair(sql, times));
    _instance_lock.unlock();
    return 1;
}
int RecordCache::AddToCache(vector<string>& keys, string& key, string& rawData, string cno, string pno)
{
    LOG4CPLUS_DEBUG(logger,"AddToCache run");
    bool find = false;
    string cacheDeviceInfo = "";
    vector<string>::iterator it = keys.begin();
    for(; it != keys.end(); ++it)
    {
        if(hasKey(*it, cacheDeviceInfo))
        {
            //get data
            LOG4CPLUS_DEBUG(logger,"totoaly old device:"<< *it);
            //same
            //json::Value jsCache = json::Deserialize(cacheDeviceInfo);
            //json::Value jsIn = json::Deserialize(rawData);
            //bool infoChange = deviceInfoChange(jsCache, jsIn);
            find = true;
            key = *it;
            break;
        }
    }

    if(!find)
        key = keys[0];
#if 0

    if(device_fingerprint_info_latest->find(key) != device_fingerprint_info_latest->end())
    {
        //5 second
        return 1;
    }
    else
    {
        (*device_fingerprint_info_latest)[key] = rawData;
    }
#endif

    if(!find)
    {
        //no need mem cache
        //(*device_fingerprint_info)[key] = rawData;
        //create sql
        string dataTmp = rawData;
        Utility::replace_all(dataTmp, "'" , "''");
        stringstream dfSql;
        //dfSql << "INSERT INTO " << _db_table_name << "(deviceid,data,cno,pno,insert_date) values('" << key << "','" << dataTmp << "','" << cno << "','" << pno << "', now())";
        dfSql << "INSERT INTO " << _db_table_name << "(deviceid,data,cno,pno,insert_date) values('" << key << "','" << dataTmp << "','" << cno << "','" << pno << "', '" << Utility::get_local_datestring() << "')";
        LOG4CPLUS_DEBUG(logger,"totoaly new device:"<< dfSql.str());
        if(AddExecuteSql(dfSql.str()))
        {
            LOG4CPLUS_DEBUG(logger,"totoaly new device insert into key val");
            //setValue(key, rawData); no need to set data
            string key_prefix = "account_";
            setValue(key_prefix+key, "v");
        }
        else
        {
            return -1;
        }
    }
    return 0;
}

void  RecordCache::ResetDeviceRedis()
{
    LOG4CPLUS_DEBUG(logger, "reset redis");
    char sql_buf[2048];
    RecordCache *record_cache = RecordCache::GetInstance();
    AutoLock  lock_inst(record_cache->_db_lock.raw_lock_ptr());
    snprintf(sql_buf,sizeof(sql_buf),"SELECT  count(*) FROM device_fingerprint_json");
    LOG4CPLUS_DEBUG(logger, "sql:" << sql_buf);
    int total_records_num=0;
    {
         AutoSqlExecuter query(&(record_cache->account_service_db_pool), string(sql_buf), true);
         if (query.Good())
         {
             RES_RESULT * result = query.Records();
             while(result->next()){
                 total_records_num = atoi(result->get_value_data());
             }
         }
         else
         {
             LOG4CPLUS_WARN(logger, "query error:" << sql_buf);
             return;
         }
    }
    int load_every_time = g_config_reader->get_int("account_service.db.load.everytime", 100);
    int load_every_time_begin = 0;
    int load_every_time_end = load_every_time;
    LOG4CPLUS_DEBUG(logger, "load data " << total_records_num << " every time:" << load_every_time);

    while(total_records_num>0)
    {
        snprintf(sql_buf,sizeof(sql_buf),"select deviceid from device_fingerprint_json limit %d offset %d",load_every_time, load_every_time_begin);
        load_every_time_begin +=  load_every_time;
        load_every_time_end += load_every_time;
        total_records_num -= load_every_time;
        LOG4CPLUS_DEBUG(logger, "load data sql " << sql_buf);

        AutoSqlExecuter query(&(record_cache->account_service_db_pool), string(sql_buf), true);

        RES_RESULT * result = query.Records();
        while(result->next()){
            string deviceid = result->get_value_data();
            setValue(deviceid, "v");
        }
    }
    LOG4CPLUS_DEBUG(logger, "reset data total: " << recordSize());
}

void  RecordCache::ResetRedis()
{
    LOG4CPLUS_DEBUG(logger, "reset redis");
    char sql_buf[2048];
    RecordCache *record_cache = RecordCache::GetInstance();
    AutoLock  lock_inst(record_cache->_db_lock.raw_lock_ptr());
    snprintf(sql_buf,sizeof(sql_buf),"SELECT  count(*) FROM %s",record_cache->_db_table_name.c_str());
    LOG4CPLUS_DEBUG(logger, "sql:" << sql_buf);
    int total_records_num=0;
    {
         AutoSqlExecuter query(&(record_cache->account_service_db_pool), string(sql_buf), true);
         if (query.Good())
         {
             RES_RESULT * result = query.Records();
             while(result->next()){
                 total_records_num = atoi(result->get_value_data());
             }
         }
         else
         {
             LOG4CPLUS_WARN(logger, "query error:" << sql_buf);
             return;
         }
    }
    int load_every_time = g_config_reader->get_int("account_service.db.load.everytime", 100);
    int load_every_time_begin = 0;
    int load_every_time_end = load_every_time;
    LOG4CPLUS_DEBUG(logger, "load data " << total_records_num << " every time:" << load_every_time);

    while(total_records_num>0)
    {
        snprintf(sql_buf,sizeof(sql_buf),"select deviceid from %s limit %d offset %d",  record_cache->_db_table_name.c_str(), load_every_time, load_every_time_begin);
        load_every_time_begin +=  load_every_time;
        load_every_time_end += load_every_time;
        total_records_num -= load_every_time;
        LOG4CPLUS_DEBUG(logger, "load data sql " << sql_buf);

        AutoSqlExecuter query(&(record_cache->account_service_db_pool), string(sql_buf), true);

        RES_RESULT * result = query.Records();
        while(result->next()){
            string deviceid = result->get_value_data();
            string key_prefix = "account_";
            delKey(deviceid);
            setValue(key_prefix+deviceid, "v");
        }
    }
    LOG4CPLUS_DEBUG(logger, "reset data total: " << recordSize());
}

void  RecordCache::LoadDB()
{
    LOG4CPLUS_DEBUG(logger, "load data run");
    return;
    char sql_buf[2048];
    RecordCache *record_cache = RecordCache::GetInstance();
    AutoLock  lock_inst(record_cache->_db_lock.raw_lock_ptr());

    snprintf(sql_buf,sizeof(sql_buf),"SELECT  count(*) FROM %s",record_cache->_db_table_name.c_str());
    LOG4CPLUS_DEBUG(logger, "sql:" << sql_buf);
    int total_records_num=0;
    {
         AutoSqlExecuter query(&(record_cache->account_service_db_pool), string(sql_buf), true);
         if (query.Good())
         {
             RES_RESULT * result = query.Records();
             while(result->next()){
                 total_records_num = atoi(result->get_value_data());
             }
         }
         else
         {
             LOG4CPLUS_WARN(logger, "query error:" << sql_buf);
             return;
         }
    }

    int load_every_time = g_config_reader->get_int("account_service.db.load.everytime", 100);
    int load_every_time_begin = 0;
    int load_every_time_end = load_every_time;
    LOG4CPLUS_DEBUG(logger, "load data " << total_records_num << " every time:" << load_every_time);

    while(total_records_num>0)
    {
        snprintf(sql_buf,sizeof(sql_buf),"select id,deviceid,data from %s limit %d offset %d",  record_cache->_db_table_name.c_str(), load_every_time, load_every_time_begin);
        load_every_time_begin +=  load_every_time;
        load_every_time_end += load_every_time;
        total_records_num -= load_every_time;
        LOG4CPLUS_DEBUG(logger, "load data sql " << sql_buf);

        AutoSqlExecuter query(&(record_cache->account_service_db_pool), string(sql_buf), true);

        RES_RESULT * result = query.Records();
        while(result->next()){
            int id = atol(result->get_value_data());
            string deviceid = result->get_value_data();
            string data = result->get_value_data();
            (*device_fingerprint_info)[deviceid] = data;
            //setValue(deviceid, data); no need to set data
            string key_prefix = "account_";
            setValue(key_prefix+deviceid, "v");
        }
    }
    LOG4CPLUS_DEBUG(logger, "load data total: " << recordSize());
}

bool RecordCache::SaveToDB(const string& sql_buf)
{
    //if exist in df db then return true
    #if 0
    string tbName = sql_buf.substr(12,18);
    if (tbName == "device_fingerprint")
    {
        vector<string> vstr;
        int r = Utility::split(sql_buf, "'", vstr);
        if (r >= 3)
        {
            const string df = vstr[1];
            string dbData;
            if(pgHasKey(df, dbData))
            {
                return true;
            }
        }
    }
    #endif
    //for debug
    //return true;
    //for debug
    AutoSqlExecuter query(&account_service_db_pool, string(sql_buf), false); 
    if (!query.Good())
    {
        LOG4CPLUS_DEBUG(logger,"insert error:" << sql_buf);
        return false;
    }
    return true;
}

void RecordCache::run()
{
    LOG4CPLUS_DEBUG(logger, "record cache run");
    static const int32_t RECORD_FLUSH_SEC = g_config_reader->get_int("account_service.db.record.flush.sec", 5);
    while(true){
        //flush data to database
        //copy data to map tmp,copy data to total,clear map,start a new thread to save data to db
        //lock
        LOG4CPLUS_DEBUG(logger, "sql size:" << execute_sql->size());
        if (execute_sql->size() > 0)
        {
            _instance_lock.lock();
            try
            {
                vector<pair<string, int> >*sql = new vector<pair<string, int> >(*execute_sql);
                if(sql)
                {
                    //sql->insert(execute_sql->begin(), execute_sql->end());
                    execute_sql->clear();
                    //unlock
                    _instance_lock.unlock();
                    pthread_t tid;
                    int pret = pthread_create(&tid, NULL, syncDB, (void*)(sql));
                    if(pret != 0){
                        delete sql;
                        LOG4CPLUS_ERROR(logger, "Create thread error!");
                        exit (1);
                    }
                }
                else
                {
                    _instance_lock.unlock();
                    LOG4CPLUS_ERROR(logger, "new failed");
                    exit(1);
                }
            }
        
            catch (exception& e)
            {
                _instance_lock.unlock();
                LOG4CPLUS_ERROR(logger, "Thread exception: "<<e.what());
            }
            catch(...)
            {
                _instance_lock.unlock();
                LOG4CPLUS_ERROR(logger, "Unknown exception in thread");
            }
        }
        sleep(RECORD_FLUSH_SEC);
    }
}

void *RecordCache::syncDB(void* data)
{
    pthread_detach(pthread_self());//set thread to unjoinable,so that it can realase resource after exit
    vector<pair<string, int> > *sqls = (vector<pair<string, int> >*)data;
    LOG4CPLUS_DEBUG(logger, "sync db size:" << sqls->size());
    RecordCache *record_cache = RecordCache::GetInstance();
    try
    {
        for(vector<pair<string, int> >::iterator it=sqls->begin(); it!=sqls->end(); ++it)
        {
            //if save false, then add it to execute_sql
            if(!record_cache->SaveToDB(it->first))
            {
                if(it->second > 1)
                    record_cache->AddExecuteSql(it->first, --it->second);
            }
        }
    }

    catch (exception& e)
    {
        LOG4CPLUS_ERROR(logger, "Thread exception: "<<e.what());
    }
    catch(...)
    {
        LOG4CPLUS_ERROR(logger, "Unknown exception in thread");
    }
    delete sqls;
    return (void*)NULL;
}


string RecordCache::getDeviceFingerprint(string &dataCrypt,string cno, string pno)
{
    string deviceID="";
    vector<string> vDeviceID;
    json::Value js = json::Deserialize(dataCrypt);
    json::Object obj = js.ToObject();
    if(js.HasKey("ads.id"))
    {
        string tmp = obj["ads.id"].ToString();
        if(!(tmp=="") && !(tmp.length() <=8))
        {
            deviceID = "df-ads.id-" + obj["ads.id"].ToString();
            vDeviceID.push_back(deviceID);
        }
    }
    if(js.HasKey("token"))
    {
        string tmp = obj["token"].ToString();
        if(!(tmp=="") && !(tmp.length() <=8))
        {
            deviceID = "df-token-"+obj["token"].ToString();
            vDeviceID.push_back(deviceID);
        }
    }
    if(vDeviceID.size() == 0)
    {
         LOG4CPLUS_WARN(logger, "can not find token or ads.id or other:"<<dataCrypt);
    }
    else
    {
        //unzip clientSensorInfo
        //array how to assign?
#if 0
        json::Value jsData = json::Deserialize(dataCrypt);
        json::Object objData = jsData.ToObject();
        if(jsData.HasKey("clientSensorInfo"))
        {
            string clientSensorInfo = objData["clientSensorInfo"].ToString();
            if(clientSensorInfo.size() > 1)
            {
                LOG4CPLUS_ERROR(logger, "before unzip:"<<clientSensorInfo<<":end");
                string unzipSensorInfo = Utility::decompress(clientSensorInfo);
                LOG4CPLUS_ERROR(logger, "after unzip:"<<unzipSensorInfo<<":end");
                if(unzipSensorInfo.size() > 2)
                {
                    jsData["clientSensorInfo"] = unzipSensorInfo;
                }
            }
        }
        if(objData.HasKey("clientAppList"))
        {

            string clientAppList = objData["clientAppList"].ToString();
            if(clientAppList.size() > 0)
            {
                string unzipAppList = Utility::decompress(clientAppList);
                if(unzipAppList.size() > 2)
                {
                    jsData["clientAppList"] = unzipAppList;
                }
            }
        }
        //int store_rt = AddToCache(vDeviceID, deviceID, dataCrypt);
        //string unzipData = json::Serialize(jsData);
        dataCrypt = json::Serialize(jsData);
        string dataTmp = dataCrypt;
        LOG4CPLUS_ERROR(logger,"data:"<<dataCrypt);
        Utility::replace_all(dataTmp, "\"[" , "[");
        LOG4CPLUS_ERROR(logger,"data:"<<dataCrypt);
        Utility::replace_all(dataTmp, "]\"" , "]");
        LOG4CPLUS_ERROR(logger,"data:"<<dataCrypt);
#endif
        int store_rt = AddToCache(vDeviceID, deviceID, dataCrypt, cno, pno);
        if(store_rt == 0)//ok
        {
            //LOG4CPLUS_ERROR(logger, "get device fingerprint error"<<dataCrypt);
            return deviceID;
        }
    }
    LOG4CPLUS_DEBUG(logger, "get device fingerprint "<<deviceID);
    return deviceID;
}
