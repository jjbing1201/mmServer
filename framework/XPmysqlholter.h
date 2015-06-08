#ifndef _XPMYSQLHOLTER_HEADER_H_
#define _XPMYSQLHOLTER_HEADER_H_

#include <iostream>
#include <map>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <mysql/mysql.h>

#include "SingleTon.h"

class LMYSQLHOLTER
{
private:
    enum { RESULT_BUF_SIZE = 50000 };
    char resultbuf[RESULT_BUF_SIZE];

protected:
    MYSQL mysql;
    MYSQL_RES *result;              /* used to store execute result. */

    /*
     *  @brief  : mysql start transaction when table support InnoDB
     *  @return : 0 for success, other for error.
    */
    int  mysql_start_transaction(void);
    /*
     *  @brief  : mysql stop transaction when all operation is over
     *  @return : NULL
    */
    void mysql_stop_transaction(void);
    /*
     *  @brief  : get execute result normal template
     *  @vars   : statements for cmd
     *          : char* for store result will be initialized outside.
     *  @returns : 0 for success, other for error. 
    */
    int  _get_execute_result(std::string &statements, char*);
    /*
     *  @brief  : transaction doing operation here.
     *  @vars   : input statements
     *  @returns : = 0 for success normally
     *             > 0 for success by lines record
     *             < 0 for error number of mysql self.
    */
    int  _transaction_operation(std::string &statements);

/* -------------------
    Initialized MySQL
 ---------------------*/
public:
    LMYSQLHOLTER();                       /* initialize mysql. */
    ~LMYSQLHOLTER();

    /* analyst connect info data. */
    std::map<std::string, std::string> dbconnectInfo(std::string & info); 
    /* constraint clean result.*/
    void cleaning_result();
    /* commit result. */
    void commit_result();
    /* test connect with database. */
    int test_connect();
    /* create connect with database. 
      if can create connect with return 0, -1 return is Error.*/
    bool create_connect(const std::string & ipaddress, \
                  int port, const std::string & username, \
                  const std::string & password, const std::string & dbname);
    /* close connect with database. */
    int close_connect();            
    /* search max line of table */
    int table_max_line(std::string & tablename);
    /* search table engines 
     * 0 => MyISAM
     * 1 => InnoDB */
    int search_table_engines(std::string &tablename);

/* -------------------
    MySQL With MyISAM 
    engine and do operation 
 ---------------------*/
public:
    /*
     *  @brief  : mysql doing execute.
     *  @usful  : this method user already care statement doing result
     *            & not care about doing returns.
     *  @return :  get return 0 is right. -1 Return is Error.
    */
    int   mysql_execute(std::string & statements); 
    /*
     *  @brief  : mysql doing execute with return data.
     *  @return : will return result to user, return information max 
     *            is RESULT_BUF_SIZE.
    */
    char* get_execute_result(std::string & statements); 
    /*
     *  @brief  : mysql doing execute with return data and charset search.
     *  @return : will return result to user, return information max 
     *            is RESULT_BUF_SIZE.
    */
    char* get_execute_result(std::string & statements, std::string &charset);

/* -------------------
    MySQL With InnoDB transaction 
    engine and do operation 
 ---------------------*/
public:
    /*
     *  @brief  : start global transaction here.
     *  @return : 0 for success, other for error.
    */ 
    int transaction_to_start(void);
    /*
     *  @brief  : mysql doing each operation here and get result to user.
     *          : include operation for three : 
                    => insert
                    => delete
                    => update
     *  @return : success part => 
                 = 0 : normal success
                 > 0 : count record for success
     *            error part   =>  
                     : -1 => table is not innodb
                     : -2 => start transaction failed.
                     : -3 => transaction doing failed. 
    */
    int  transaction_op_result(std::string &tablename, std::string &statements);
    /*
     *  @brief  : mysql doing all over from here and will put checkpoint
     *            to mysql by commit or rollback
     *  @vars   : 1 for commit, 2 for rollback
    */
    void transaction_finish(int);
};

#endif /* _XPMYSQLHOLTER_HEADER_H_ */

typedef SINGLETON<LMYSQLHOLTER> holtercon; // link -> Holter 

