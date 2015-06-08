#ifndef _DATABASE_BASEDATA_
#define _DATABASE_BASEDATA_

#include "include_db.h"

class MM_BASEDATA 
{
private:
    std::string column_one;         // bid
    std::string column_two;         // nowTemp
    std::string column_three;       // hashId
    std::string column_four;        // deviceName
    std::string column_five;        // devicePart
    std::string column_six;         // serviceUUID
    std::string column_seven;       // lastTemp
    std::string column_eight;       // userName
    std::string column_nine;        // userID
    std::string column_ten;         // clientTime
    std::string column_eleven;      // serverTime
    std::string column_twelve;      // clientVersion
    std::string column_thirteen;    // screening
    std::string column_fourteen;    // screeningTime
    std::string column_fifteen;     // forgive

public:
    MM_BASEDATA();
    virtual ~MM_BASEDATA() {}

    std::map<std::string, std::string> insert_BASEDATA(std::string tablename, std::string nowTemp, std::string hashId, std::string deviceName, std::string devicePart, std::string serviceUUID, std::string lastTemp, std::string userName, std::string userID, std::string clientTime, std::string serverTime, std::string clientVersion, std::string screening, std::string screeningTime, std::string forgive="0");

    std::map<std::string, std::string> update_BASEDATA(const std::string &tablename, const std::string &bid, std::string nowTemp, std::string hashId, std::string deviceName, std::string devicePart, std::string serviceUUID, std::string lastTemp, std::string userName, std::string userID, std::string clientTime, std::string serverTime, std::string clientVersion, std::string screening, std::string screeningTime, std::string forgive="0");
};

#endif /* _DATABASE_BASEDATA_ */

