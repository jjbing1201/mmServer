#ifndef _DATABASE_HELPMAIN_
#define _DATABASE_HELPMAIN_

#include "include_db.h"

class MM_HELPMAIN 
{
private:
    std::string tablename;          // HelpMain
    std::string column_one;         // helpId
    std::string column_two;         // helpTitle
    std::string column_three;       // helpContext
    std::string column_four;        // helpTimestamp
    std::string column_five;        // helpDelete

public:
    MM_HELPMAIN();
    virtual ~MM_HELPMAIN() {}

    std::map<std::string, std::string> insert_HELPMAIN(std::string helpTitle, std::string helpContext, std::string helpTimestamp, std::string helpDelete="0");

    std::map<std::string, std::string> update_HELPMAIN(const std::string &helpId, std::string helpTitle, std::string helpContext, std::string helpTimestamp, std::string helpDelete="0");

    std::map<std::string, std::string> update_direct_HELPMAIN(const std::string &helpId, std::string which_column, std::string column_context);

    /* @brief
     * usage: select by helpmain for all table. 
     * param: .
    */
    std::map<std::string, std::string> select_all_table();
   
    std::map<std::string, std::string> select_by_helpList(std::string start_lo, std::string end_lo);    
};

#endif /* _DATABASE_HELPMAIN_ */

