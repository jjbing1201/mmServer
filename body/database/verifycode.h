#ifndef _DATABASE_VERIFYCODE_
#define _DATABASE_VERIFYCODE_

#include "include_db.h"

class MM_VERIFYCODE 
{
private:
    std::string tablename;          // VerifyCode 
    std::string column_one;         // verifyId
    std::string column_two;         // verifyResource
    std::string column_three;       // verifyToUser
    std::string column_four;        // verifyNumber
    std::string column_five;        // verifyCreateTime
    std::string column_six;         // verifyDelay

public:
    MM_VERIFYCODE();
    virtual ~MM_VERIFYCODE() {}

    std::map<std::string, std::string> insert_VERIFYCODE(std::string verifyResource, std::string verifyToUser, std::string verifyNumber, std::string verifyCreateTime, std::string verifyDelay="60");

    std::map<std::string, std::string> update_VERIFYCODE(const std::string &verifyId, std::string verifyResource, std::string verifyToUser, std::string verifyNumber, std::string verifyCreateTime, std::string verifyDelay="60");

    std::map<std::string, std::string> update_direct_VERIFYCODE(const std::string &verifyId, std::string which_column, std::string column_context);

    /* @brief
     * usage: select by verifyId. 
     * param: verifyId to search each user's verifycode.
    */
    std::map<std::string, std::string> select_by_verifycodeid(std::string verifyId);

    /* @brief
     * usage: select by verifyResource & verifyToUser to ensure
     * param: verifyResource & verifyToUser to search each verifycode
    */
    std::map<std::string, std::string> select_by_send(std::string verifyResource, std::string verifyToUser);
};

#endif /* _DATABASE_VERIFYCODE_ */

