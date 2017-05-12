#include "common/PGDBConnectionPool.h"
#include <errmsg.h>
#include <sys/time.h>
using namespace std;
IMPL_LOGGER (PGSQLDB, logger);
PGSQLDB::PGSQLDB (const std::string & port, const std::string & host,
    const std::string & user, const std::string & passwd,
    const std::string & dbname):m_port (port), m_host (host), m_user (user),
m_passwd (passwd), m_dbname (dbname), m_isuse (false), m_isinit (false)
{
    LOG4CPLUS_DEBUG (logger, "PGSQLDB: passwd " << m_passwd);
}

PGSQLDB::~PGSQLDB ()
{
    PQfinish (pg_sql);
    m_isuse = false;
    m_isinit = false;
}

bool PGSQLDB::reconnect ()
{
    PQfinish (pg_sql);

    pg_sql =
        PQsetdbLogin (m_host.c_str(), m_port.c_str (), NULL, NULL,
        m_dbname.c_str (), m_user.c_str (), m_passwd.c_str ());
    if (NULL == pg_sql)
    {
        LOG4CPLUS_ERROR (logger,
            "pgsql_real_connect err ret: " << get_errorinfo ());
        return false;
    }
    return true;
}

string PGSQLDB::get_errorinfo ()
{
    return PQerrorMessage (pg_sql);
}

bool PGSQLDB::Init ()
{
    m_isinit = true;
    LOG4CPLUS_DEBUG (logger, "PGSQLDB " << m_port << ":" << m_host);
    pg_sql =
        PQsetdbLogin (m_host.c_str(), m_port.c_str (), NULL, NULL,
        m_dbname.c_str (), m_user.c_str (), m_passwd.c_str ());
    if (NULL == pg_sql)
    {
        m_isinit = false;
        LOG4CPLUS_ERROR (logger,
            "pgsql_real_connect err ret: " << get_errorinfo ());
        return false;
    }
    else
    {
        LOG4CPLUS_DEBUG (logger, "PGSQLDB::Init ok");
    }
    int status = PQstatus (pg_sql);
    if (status != CONNECTION_OK)
        LOG4CPLUS_ERROR (logger,
            "pgsql_real_connect err ret: " << get_errorinfo ());
    return status == CONNECTION_OK;
}

bool PGSQLDB::Ensure_Connect ()
{
    if (!m_isinit)
    {
        bool flag = false;
        flag = Init ();
        LOG4CPLUS_DEBUG (logger,
            "after m_isinit: " << m_isinit << "flag:" << flag ? "true" :
            "false");
        if (flag == false) return false;
    }
    int status = PQstatus (pg_sql);
    if (status != CONNECTION_OK)
        LOG4CPLUS_ERROR (logger, "init error: " << get_errorinfo ());
    return status == CONNECTION_OK;
}

bool PGSQLDB::query (const char *buffer, RES_RESULT **result, bool need_read, unsigned repeattimes)
{
    if (repeattimes < 1)
    {
        repeattimes = RETRYTIMES;
    }
    bool ret_val = false;
    //for debug
    //return true;
    //for debug
    for (unsigned i = 0; i < repeattimes; i++)
    {
        PGresult* res = PQexec(pg_sql, buffer);
        if (NULL == res)
        {
            LOG4CPLUS_ERROR (logger,
                "SQL execute errror:" << buffer);
        }
        else
        {
            ExecStatusType exec_status = PQresultStatus(res);
            switch (exec_status)
            {
                case PGRES_COMMAND_OK:
                    {
                        PQclear(res);
                        return true;
                    }
                case PGRES_TUPLES_OK:
                    {
                        if (need_read)
                        {
                            *result = new RES_RESULT(res);
                        }
                        else PQclear(res);
                        return true;
                    }
                case PGRES_BAD_RESPONSE:
                case PGRES_NONFATAL_ERROR:
                case PGRES_FATAL_ERROR:
                    {
                            LOG4CPLUS_ERROR (logger,
                                "SQL execute errror, error code:" << exec_status << " " << PQresultErrorMessage(res));
                        break;
                    }
                default:
                    {
                            LOG4CPLUS_ERROR (logger,
                                "SQL execute default, error code:" << exec_status << "PGRES_TUPLES_OK" << PGRES_TUPLES_OK);
                        break;
                    }
            }
            PQclear(res);
        }
    }
    LOG4CPLUS_ERROR (logger,"SQL execute errror:" << buffer);
    return false;
}

////////
IMPL_LOGGER (PGDBConnectionPool, logger);

PGDBConnectionPool::PGDBConnectionPool (unsigned poolsize, 
                                        const std::string & port, 
                                        const std::string & host, 
                                        const std::string & user, 
                                        const std::string & passwd, 
                                        const std::string & dbname):m_port (port), m_host (host), m_user (user), m_passwd (passwd), m_dbname (dbname)
{
    pthread_mutex_init (&pg_sqlpool_lock, NULL);
    for (unsigned i = 0; i < poolsize; i++)
    {
        PGSQLDB *pgsql = new PGSQLDB (port, host, user, passwd, dbname);
        pg_sqlpool_list.push_back (pgsql);
    }
}

PGDBConnectionPool::PGDBConnectionPool (const PGDBConnectionPool & dbc_pool)
{
    m_port = dbc_pool.m_port;
    m_host = dbc_pool.m_host;
    m_user = dbc_pool.m_user;
    m_passwd = dbc_pool.m_passwd;
    m_dbname = dbc_pool.m_dbname;
    pthread_mutex_init (&pg_sqlpool_lock, NULL);
    for (unsigned i = 0, size = dbc_pool.pg_sqlpool_list.size (); i < size; i++)
    {
        PGSQLDB *pgsql =
            new PGSQLDB (dbc_pool.getport (), dbc_pool.gethost (),
            dbc_pool.getuser (), dbc_pool.getpwd (), dbc_pool.getdbname ());
        pg_sqlpool_list.push_back (pgsql);
    }
}

PGDBConnectionPool::~PGDBConnectionPool ()
{
    int nsize = pg_sqlpool_list.size ();
    for (int i = 0; i < nsize; i++)
    {
        if (pg_sqlpool_list[i] != NULL)
        {
            delete pg_sqlpool_list[i];
            pg_sqlpool_list[i] = NULL;
        }
    }
    pg_sqlpool_list.clear ();
    pthread_mutex_destroy (&pg_sqlpool_lock);
}

void PGDBConnectionPool::set_size (uint32_t size)
{
    for (unsigned i = 0; i < size; i++)
    {
        pg_sqlpool_list.push_back (new PGSQLDB (m_port, m_host, m_user, m_passwd,
                m_dbname));
    }
}

bool PGDBConnectionPool::Init ()
{
    bool can_connect = false;
    for (unsigned i = 0; i < pg_sqlpool_list.size (); i++)
    {
        if (pg_sqlpool_list[i] != NULL && pg_sqlpool_list[i]->Init ())
        {
            can_connect = true;
        }
    }
    return can_connect;
}

PGSQLDB *PGDBConnectionPool::get_sql (bool autocreate)
{
    PGSQLDB *pg_sql = NULL;
    pthread_mutex_lock (&pg_sqlpool_lock);
    bool is_connect_fail = false;
    try
    {
        for (unsigned i = 0; i < pg_sqlpool_list.size (); i++)
        {
            if (pg_sqlpool_list[i] != NULL && !pg_sqlpool_list[i]->m_isuse)
            {
                if (pg_sqlpool_list[i]->Ensure_Connect ())
                {
                    pg_sqlpool_list[i]->m_isuse = true;
                    pg_sql = pg_sqlpool_list[i];
                    break;
                }
                else
                {
                    LOG4CPLUS_ERROR (logger,
                        "pg_sqlpool_list[" << i << "]" << pg_sqlpool_list[i] <<
                        " failed to Ensure_Connect");
                    is_connect_fail = true;
                    pg_sql = NULL;
                }
            }
        }
    }
    catch (...)
    {
        pg_sql = NULL;
    }
    // if not found, then re-establish a new connection
    if (pg_sql == NULL && autocreate && !is_connect_fail)
    {
        pg_sql = new PGSQLDB (m_port, m_host, m_user, m_passwd, m_dbname);
        bool flag = pg_sql->Init ();
        if (flag)
        {
            pg_sql->m_isuse = true;
            pg_sqlpool_list.push_back (pg_sql);
        }
        else
        {
            delete pg_sql;
            pg_sql = NULL;
        }
    }
    pthread_mutex_unlock (&pg_sqlpool_lock);
    return pg_sql;
}

void PGDBConnectionPool::release_sql (PGSQLDB * sql)
{
    pthread_mutex_lock (&pg_sqlpool_lock);
    try
    {
        for (unsigned i = 0; i < pg_sqlpool_list.size (); i++)
        {
            if (pg_sqlpool_list[i] == sql)
            {
                pg_sqlpool_list[i]->m_isuse = false;
                break;
            }
        }
    }
    catch (...)
    {
    }
    pthread_mutex_unlock (&pg_sqlpool_lock);
}

/////////
IMPL_LOGGER (RES_RESULT, logger);
RES_RESULT::~RES_RESULT()
{
    release();
}


RES_RESULT::RES_RESULT(PGresult* result)
{
    m_result = result;
    //LOG4CPLUS_DEBUG(logger, "before:" << m_result);
    m_max_num_rows = PQntuples(result);
    m_max_num_fields = PQnfields(result);
    m_row = 0;
    m_fields_pos = 0;
}

bool RES_RESULT::is_Null()
{
   if(m_result == NULL || m_max_num_rows == 0 || m_max_num_fields == 0)
   {
       return true;
   }
   return false;
}

void RES_RESULT::release()
{
    LOG4CPLUS_DEBUG (logger,"");
    if(m_result != NULL)
    {
        PQclear(m_result);
        m_result = NULL;
    }
}

bool RES_RESULT::next()
{
    //LOG4CPLUS_DEBUG (logger, "m_max_num_rows:" << m_max_num_rows << " m_row:" << m_row);
    m_fields_pos = 0;
    if (m_result == NULL || m_row >= m_max_num_rows) return false;
    else
    {
        ++m_row;
        return true;
    }
}

char* RES_RESULT::get_value_data()
{
    //LOG4CPLUS_DEBUG (logger, "max_field:" << m_max_num_fields << " field:" << m_fields_pos << " max_rows:" << m_max_num_rows << " row:" << m_row);
    if (m_fields_pos <= m_max_num_fields - 1)
    {
       return PQgetvalue(m_result, m_row-1, m_fields_pos++);
    }
    else
    {
        return NULL;
    }
}
