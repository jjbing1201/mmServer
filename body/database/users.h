#ifndef _DATABASE_USERS_
#define _DATABASE_USERS_

#include "include_db.h"

class MM_USERS 
{
private:
    std::string tablename;          // Person 
    std::string column_one;         // userid
    std::string column_two;         // username
    std::string column_three;       // password
    std::string column_four;        // userRealname
    std::string column_five;        // userSex
    std::string column_six;         // userAge
    std::string column_seven;       // userAvatar
    std::string column_eight;       // userDefImage
    std::string column_nine;        // userBelongOrgId
    std::string column_ten;         // userPriority
    std::string column_eleven;      // userLastLogin
    std::string column_twelve;      // userLoginType
    std::string column_thirteen;    // userBackupThree
    std::string column_fourteen;    // userBackupFour
    std::string column_fifteen;     // userBackupFive

public:
    MM_USERS();
    virtual ~MM_USERS() {}

    std::map<std::string, std::string> insert_USERS(std::string user_name, std::string password, std::string userRealname, std::string userSex, std::string userAge, std::string userAvatar, std::string userDefImage, std::string userBelongOrgId, std::string userPriority, std::string userLastLogin, std::string userLoginType="None", std::string userBackupThree="None", std::string userBackupFour="None", std::string userBackupFive="None");

    std::map<std::string, std::string> update_USERS(const std::string &user_id, std::string user_name, std::string password, std::string userRealname, std::string userSex, std::string userAge, std::string userAvatar, std::string userDefImage, std::string userBelongOrgId, std::string userPriority, std::string userLastLogin, std::string userLoginType="None", std::string userBackupThree="None", std::string userBackupFour="None", std::string userBackupFive="None");

    std::map<std::string, std::string> update_direct_USERS(const std::string &user_id, std::string which_column, std::string column_context);

    /* @brief
     * usage: select by userid. 
     * param: user_id to search each user.
    */
    std::map<std::string, std::string> select_by_userid(std::string user_id);

    /* @brief
     * usage: select by username.
     * param: user_name to search each user.
    */
    std::map<std::string, std::string> select_by_username(std::string user_name);

    /* @brief
     * usage: select by username & password to ensure.
     * param: user_name & user_pass to search each user
    */
    std::map<std::string, std::string> select_by_login(std::string user_name, std::string user_pass);
};

#endif /* _DATABASE_USERS_ */

