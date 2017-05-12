#ifndef AUTO_SQL_EXECUTER__H
#define AUTO_SQL_EXECUTER__H
#include "common/PGDBConnectionPool.h"
#include "common/Utility.h"
#include <mysql.h>

class AutoSqlExecuter{
public:
    AutoSqlExecuter(PGDBConnectionPool * pool, const string & sql, bool read=true)
    {
        _pool = pool;
        _records = NULL;
        _code = 0;
        _need_read = read;
        Execute(sql);
    }

    ~AutoSqlExecuter()
    {
        if(_records){
            _records->release();
            delete _records;
            _records = NULL;
        }
        if(_pool && _pgsql){
            _pool->release_sql(_pgsql);
        }
    }

    bool Good() const
    {
        return _code == 0;
    }

    bool Empty()const
    {
	return _records->is_Null();
    }
	
    int Code() const
    {
        return _code;
    }
    
    RES_RESULT * Records() 
    {
        return _records;
    }
    static int EscapeString (string &str)
    {
        if (str.size()==0) return 0;
        char *buff= new char[str.size()*2+1];
        mysql_escape_string (buff, str.c_str(), str.size());
        str= buff;
        delete[] buff;
        return 0;
    }
 
private:
    PGDBConnectionPool * _pool;
    int _code;
    RES_RESULT * _records;
    PGSQLDB * _pgsql;
    bool _need_read;

    void Execute(const string & sql)
    {
        _pgsql = _pool->get_sql(true);
        if(!_pgsql){
            _code = -1;
            return;
        }
        //dealling the string contains nul
        //*
        std::string nul(" ");
        nul[0] = '\0';
        std::string replaced_sql = sql;
        Utility::replace_all(replaced_sql, nul, "0X00");
        if(_pgsql->query(replaced_sql.c_str(), &_records, _need_read)){
        //*/
        //if(_pgsql->query(sql.c_str(), &_records, _need_read)){
            _code = 0;
            return;
        }
        else{
            _code = -2;
            return;
        }
    }
};

#endif
