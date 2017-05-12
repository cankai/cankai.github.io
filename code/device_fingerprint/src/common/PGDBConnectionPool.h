#ifndef _PGDBCONNECTIONPOOL_H
#define _PGDBCONNECTIONPOOL_H
#include <string>
#include <vector>
#include <common/Exception.h>
#include <libpq-fe.h>
#include "common/Logger.h"
#define RETRYTIMES 3
using namespace std;
class RES_RESULT;
class PGSQLDB {
  public:PGSQLDB(const std::string & port, const std::string & host,
            const std::string & user, const std::string & passwd,
            const std::string & dbname);
    PGSQLDB();
    ~PGSQLDB();
    bool Ensure_Connect();
    bool Init();
    bool query(const char *buffer, RES_RESULT **, bool need_read, unsigned repeattime = RETRYTIMES);

    PGconn *get_mysql() {
        return pg_sql;
    }
    std::string getHost() {
        return m_host;
    }
    std::string get_errorinfo();
  private:
    //reconnect this server
    bool reconnect();
  private:void _init();
    std::string m_port;
    std::string m_host;
    std::string m_user;
    std::string m_passwd;
    std::string m_dbname;
  public:
    bool m_isuse;
    bool m_isinit;
    PGconn *pg_sql;
    DECL_LOGGER(logger);
};

class PGDBConnectionPool {
  public:PGDBConnectionPool() {
        pthread_mutex_init(&pg_sqlpool_lock, NULL);
    }
    PGDBConnectionPool(unsigned poolsize, const std::string & port,
                       const std::string & host, const std::string & user,
                       const std::string & passwd,
                       const std::string & dbname);
    PGDBConnectionPool(const PGDBConnectionPool & dbc_pool);
    virtual ~ PGDBConnectionPool();

    //init this connect pool
    bool Init();
    void set_size(uint32_t size);

    //get sql's connection from connnect pool
    PGSQLDB *get_sql(bool autocreate = true);

    //return back sql's connection to connnect pool
    void release_sql(PGSQLDB * sql);
    std::string gethost()const {
        return m_host;
    }
    std::string getuser() const {
        return m_user;
    }
    std::string getpwd() const {
        return m_passwd;
    }
    std::string getdbname() const {
        return m_dbname;
    }
    std::string getport() const {
        return m_port;
    }
    std::string m_port;
    std::string m_host;
    std::string m_user;
    std::string m_passwd;
    std::string m_dbname;
    std::vector < PGSQLDB * >pg_sqlpool_list;
    pthread_mutex_t pg_sqlpool_lock;
    DECL_LOGGER(logger);
};

class RES_RESULT
{
  public:
    ~RES_RESULT();
    RES_RESULT(PGresult*);
    bool is_Null();
    bool next();
    void release();
    char* get_value_data();
    PGresult*   m_result;
    unsigned    m_row;
    unsigned    m_fields_pos;
    unsigned    m_max_num_rows;
    unsigned    m_max_num_fields;
  private:
    DECL_LOGGER(logger);
};

#endif
