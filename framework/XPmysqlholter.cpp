#include "XPmysqlholter.h"

LMYSQLHOLTER::LMYSQLHOLTER()
{
    mysql_init(&mysql);
    result = NULL;
}

LMYSQLHOLTER::~LMYSQLHOLTER()
{
    mysql_free_result(result);
    close_connect();
}

int  LMYSQLHOLTER::mysql_start_transaction()
{
    /* set auto commit to false. */
    int set_return = mysql_real_query(&mysql, \
          "SET AUTOCOMMIT = 0;", (unsigned int)strlen("SET AUTOCOMMIT = 0;"));
    if (set_return != 0)
    {
        return -1;
    }
    else
    {
        int start_return = mysql_real_query(&mysql,"Begin;",\
                                        (unsigned int)strlen("Begin;"));
        if (start_return != 0)
        {
            return -1;
        }
        else
        {
            return 0;
        }
    } 

    return 0;
}

void LMYSQLHOLTER::mysql_stop_transaction()
{
    mysql_real_query(&mysql, \
          "SET AUTOCOMMIT = 1;", (unsigned int)strlen("SET AUTOCOMMIT = 1;"));

    return;
}

int LMYSQLHOLTER::_get_execute_result(std::string &statements, char* resultbuf)
{
    /* initialize variable. */
    MYSQL_FIELD *field = NULL; /* line. */
    MYSQL_ROW row = NULL;      /* row. */

    /* store result sets. */
    mysql_query(&mysql, statements.c_str());
    result = mysql_store_result(&mysql);

    /* get result lines. */
    int fieldcount = mysql_num_fields(result);

    /* read field lines name. */
    std::string fieldline;
    for(int i = 0; i<fieldcount; i++)
    {
        field = mysql_fetch_field_direct(result, i);
        fieldline = fieldline + field->name + "\t\t";
    }
    fieldline += "\r\n";
    strcpy(resultbuf, fieldline.c_str()); /* put into return buf. */

    /* read each rows. */
    row = mysql_fetch_row(result);
    while(NULL != row)
    {
        std::string eachrow;
        for (int j = 0; j<fieldcount; j++)
        {
            eachrow = eachrow + row[j] + "\t\t";
        }
        eachrow += "\r\n";
        strcat(resultbuf, eachrow.c_str());
        row = mysql_fetch_row(result); /* using judge search finished. */
    }
    
    return 0;
}

int LMYSQLHOLTER::_transaction_operation(std::string &statements)
{
    /* statement about return and outside using. */
    MYSQL_RES *res;
    
    int _transaction_doing = mysql_real_query(&mysql,\
                statements.c_str(),(unsigned int)strlen(statements.c_str()));

    if(_transaction_doing)
    {
        /* Error id and context => 
           Error id         =>  %d : mysql_errno(mysql)
           Error context    =>  %s : mysql_error(mysql) 
        */
        return mysql_errno(&mysql);
    }
    else
    {
        res=mysql_store_result(&mysql);  
        mysql_free_result(res);
        return mysql_affected_rows(&mysql);
    }

    return 0;
}

std::map<std::string, std::string> LMYSQLHOLTER::dbconnectInfo(std::string & info)
{
    std::map<std::string, std::string> allmap;

    std::string::size_type loc_at = info.find("@");
    if (loc_at != std::string::npos)
    {
        std::string partone = info.substr(0, loc_at);
        std::string::size_type loc_colon = partone.find(":");
        if (loc_colon != std::string::npos)
        {
            allmap["username"] = partone.substr(0, loc_colon);
            allmap["password"] = partone.substr(loc_colon+1);
        }
        std::string parttwo = info.substr(loc_at+1);
        std::string::size_type loc_slash = parttwo.find("/");
        if (loc_slash != std::string::npos)
        {
            allmap["dbname"] = parttwo.substr(loc_slash+1);
            std::string::size_type loc_sub_colon = parttwo.substr(0, loc_slash).find(":");
            if (loc_sub_colon != std::string::npos)
            {
                allmap["ipaddress"] = parttwo.substr(0, loc_slash).substr(0,loc_sub_colon);
                allmap["port"] = parttwo.substr(0, loc_slash).substr(loc_sub_colon+1);
            }
        }
    }
    return allmap;
} 

int LMYSQLHOLTER::test_connect()
{
    return mysql_ping(&mysql);
}

/*
This method used to create connection with database
connection information resource : config.ini
if get information from config.ini will return 0, otherwise
will return -1 means error.
if return 0 and can not load config file will return default 
vairable: link : root:@localhost:3306/test

*/
bool LMYSQLHOLTER::create_connect(const std::string & ipaddress, int port, const std::string & username, const std::string & password, const std::string & dbname)
{

    try
    {
       /* create connection. */
        mysql_real_connect(&mysql, ipaddress.c_str(),
                                   username.c_str(),
                                   password.c_str(),
                                   dbname.c_str(),
                                   port,
                                   NULL, 0);
        return true;
    }catch(...){
        return false;
    }
}

/*
This method used to close connect with database
return 0 is normally close, -1 return is Error.
*/
int LMYSQLHOLTER::close_connect()
{
    try
    {
        mysql_close(&mysql);
        return 0;
    }catch(...){
        return -1;
    }
}

/*
This method used to commit result for search.
*/
void LMYSQLHOLTER::commit_result()
{
    mysql_commit(&mysql);
}

/*
This method used to clean result enforce.
when use this method carefully.
*/
void LMYSQLHOLTER::cleaning_result()
{
    mysql_free_result(result);
}

/*
This method used to search max line of table.
need input tablename and return max line (int)
*/
int LMYSQLHOLTER::table_max_line(std::string & tablename)
{
    /* line count for all : linecount */
    int linecount;

    /* combine select sqlcmd. */
    std::string sql="select * from "+tablename;

    /* clean result first. */
    cleaning_result();

    mysql_query(&mysql, sql.c_str());

    result = mysql_store_result(&mysql);

    /* counting lines. */
    linecount = mysql_num_rows(result);

    return linecount;
}

int LMYSQLHOLTER::search_table_engines(std::string &tablename)
{
    /* combine select sqlcmd. */
    std::string sql="show create table "+tablename;

    /* clean result. */
    cleaning_result();

    /* clean select buf. */
    char buf[1024];
    memset(buf, 0, 1024); 

    int get_doing_return = _get_execute_result(sql, buf);
    if (get_doing_return != 0)
    {
        return -1;
    }
    else
    {
        if ( (strstr(buf, "MyISAM")) == NULL )
            if ( (strstr(buf, "InnoDB")) == NULL )
                return -1;
            else
                return 1;
        else
            return 0;
    }

    return -1;
}

/*
This method used to doing Execute statement when user give
variable is very inportant.
method will return 0 for right, -1 return is Error.
*/
int LMYSQLHOLTER::mysql_execute(std::string & statements)
{
    /* using temp variable to check statement is right. */
    int check;
    check = mysql_real_query(&mysql, statements.c_str(), strlen(statements.c_str()));
    if (check == 0)
    {
        return 0;
    }else{
        return -1;
    }
}

/*
This method used to doing Execute statement 
and return result to user.
*/
char * LMYSQLHOLTER::get_execute_result(std::string & statements)
{
    /* clean result. */
    cleaning_result();

    /* clean select buf. */
    memset(resultbuf, 0, RESULT_BUF_SIZE);

    _get_execute_result(statements, resultbuf);

    return resultbuf;
}

char * LMYSQLHOLTER::get_execute_result(std::string & statements, std::string &charset)
{
    /* clean result. */
    cleaning_result();

    /* clean select buf. */
    memset(resultbuf, 0, RESULT_BUF_SIZE);

    /* initialize variable. */
    MYSQL_FIELD *field = NULL; /* line. */
    MYSQL_ROW row = NULL;      /* row. */

    /* store result sets. */
    mysql_query(&mysql, charset.c_str());
    mysql_query(&mysql, statements.c_str());
    result = mysql_store_result(&mysql);

    /* get result lines. */
    int fieldcount = mysql_num_fields(result);

    /* read field lines name. */
    std::string fieldline;
    for(int i = 0; i<fieldcount; i++)
    {
        field = mysql_fetch_field_direct(result, i);
        fieldline = fieldline + field->name + "\t\t";
    }
    fieldline += "\r\n";
    strcpy(resultbuf, fieldline.c_str()); /* put into return buf. */

    /* read each rows. */
    row = mysql_fetch_row(result);
    while(NULL != row)
    {
        std::string eachrow;
        for (int j = 0; j<fieldcount; j++)
        {
            eachrow = eachrow + row[j] + "\t\t";
        }
        eachrow += "\r\n";
        strcat(resultbuf, eachrow.c_str());
        row = mysql_fetch_row(result); /* using judge search finished. */
    }

    return resultbuf;
}

int LMYSQLHOLTER::transaction_to_start(void)
{
    int _start_return = mysql_start_transaction();
    if (_start_return != 0)
    {
        mysql_stop_transaction();
        return -1;
    }

    return 0;
}

int LMYSQLHOLTER::transaction_op_result(std::string &tablename, \
                                  std::string &statements)
{
    int _transaction_go = _transaction_operation(statements);
    if (_transaction_go != 0)
    {
        return _transaction_go;
    }

    return 0;
}

void LMYSQLHOLTER::transaction_finish(int op)
{
    if (op == 1)
        mysql_real_query(&mysql,"COMMIT;",(unsigned int)strlen("COMMIT;"));
    else if(op == 2)
        mysql_real_query(&mysql,"ROLLBACK;",(unsigned int)strlen("ROLLBACK;"));

    mysql_stop_transaction();

    return;
}
