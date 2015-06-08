#ifndef _DATABASE_INTERFACE_USING_
#define _DATABASE_INTERFACE_USING_

#include "include_db.h"

class MIWA_INTERFACE_USING 
{
private:
    std::string tablename;          // abb_interface_using
    std::string column_one;         // auto_id
    std::string column_two;         // interface_name
    std::string column_three;       // last_update_time
    std::string column_four;        // all_count

public:
    MIWA_INTERFACE_USING();
    virtual ~MIWA_INTERFACE_USING() {}

    std::map<std::string, std::string> insert_INTERFACE_USING(std::string interface_name, std::string last_update_time, std::string all_count);

    std::map<std::string, std::string> update_INTERFACE_USING(const std::string &user_id, std::string interface_name, std::string last_update_time, std::string all_count);

    std::map<std::string, std::string> select_by_autoid(std::string auto_id);

    /* select one at database. */
    std::map<std::string, std::string> select_one_interface(std::string interface_name);
    
    /* update one. */
    std::map<std::string, std::string> update_one_interface(std::string interface_name);
};

#endif /* _DATABASE_INTERFACE_USING_ */

