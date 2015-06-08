#ifndef _DATABASE_MESSAGELIST_
#define _DATABASE_MESSAGELIST_

#include "include_db.h"

class MM_MESSAGELIST 
{
private:
    std::string tablename;          // MessageList
    std::string column_one;         // mid
    std::string column_two;         // libraryId
    std::string column_three;       // ruleId
    std::string column_four;        // mContext
    std::string column_five;        // userId
    std::string column_six;         // userName
    std::string column_seven;       // createTime
    std::string column_eight;       // nowStatus
    std::string column_nine;        // hashId

public:
    MM_MESSAGELIST();
    virtual ~MM_MESSAGELIST() {}

    std::map<std::string, std::string> insert_MESSAGELIST(std::string libraryId, std::string ruleId, std::string mContext, std::string userId, std::string userName, std::string createTime, std::string nowStatus, std::string hashId="None");

    std::map<std::string, std::string> update_MESSAGELIST(const std::string &mid, std::string libraryId, std::string ruleId, std::string mContext, std::string userId, std::string userName, std::string createTime, std::string nowStatus, std::string hashId="None");

    std::map<std::string, std::string> update_direct_MESSAGELIST(const std::string &mid, std::string which_column, std::string column_context);

    /* @brief
     * usage: select by message. 
     * param: mid to search each message.
    */
    std::map<std::string, std::string> select_by_messageid(std::string mid);

    /* @brief
     * usage: select by username.
     * param: user_name to search message unread count.
    */
    std::map<std::string, std::string> select_by_username(std::string userName);

    /* @brief
     * usage: select by username & page to ensure.
     * param: user_name & page to search each user
    */
    std::map<std::string, std::string> select_by_messageList(std::string userName, std::string start_lo, std::string end_lo);
};

#endif /* _DATABASE_MESSAGELIST_ */

