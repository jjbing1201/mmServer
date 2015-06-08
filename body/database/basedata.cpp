#include "basedata.h"

MM_BASEDATA::MM_BASEDATA()
{
     column_one = "bid";
     column_two = "nowTemp";
     column_three = "hashId";
     column_four = "deviceName";
     column_five = "devicePart";
     column_six = "serviceUUID";
     column_seven = "lastTemp";
     column_eight = "userName";
     column_nine = "userID";
     column_ten = "clientTime";
     column_eleven = "serverTime";
     column_twelve = "clientVersion";
     column_thirteen = "screening";
     column_fourteen = "screeningTime";
     column_fifteen = "forgive";
}

std::map<std::string, std::string> MM_BASEDATA::insert_BASEDATA(std::string tablename, std::string nowTemp, std::string hashId, std::string deviceName, std::string devicePart, std::string serviceUUID, std::string lastTemp, std::string userName, std::string userID, std::string clientTime, std::string serverTime, std::string clientVersion, std::string screening, std::string screeningTime, std::string forgive)
{
    /* 1. using bottom to get insert cmd. */
    std::map<std::string, std::string> result;

    /* 1.1 statement bottom using. */
    DAL_Bottom bottom;
    std::map<int, std::string> cmd;

    /* 1.2 combine vars. */
    std::vector<std::string> tmp;
    tmp.push_back("0");
    tmp.push_back(nowTemp);
    tmp.push_back(hashId);
    tmp.push_back(deviceName);
    tmp.push_back(devicePart);
    tmp.push_back(serviceUUID);
    tmp.push_back(lastTemp);
    tmp.push_back(userName);
    tmp.push_back(userID);
    tmp.push_back(clientTime);
    tmp.push_back(serverTime);
    tmp.push_back(clientVersion);
    tmp.push_back(screening);
    tmp.push_back(screeningTime);
    tmp.push_back(forgive);

    cmd = bottom.insert_Bottom(tablename, tmp.size(), tmp);

    /* 2. get return of execute. */
    if (cmd[0] == "false")
    {
        result["Status"] = "failed";
        result["Info"] = "409";
        result["body"] = "<<< cmd >>> combine Error -> USERS INSERT.";
    }else{
        int getdo = holtercon::GetInstance().mysql_execute(cmd[1]);
        if (getdo == 0)
        {
            result["Status"] = "success";
            result["Info"] = "200";
            result["body"] = "success";
            holtercon::GetInstance().commit_result();
        }else{
            result["Status"] = "failed";
            result["Info"] = "408";
            result["body"] = "<<< cmd >>> Doing Failed -> USERS INSERT.";
        }
    }
    return result;
}

std::map<std::string, std::string> MM_BASEDATA::update_BASEDATA(const std::string &tablename, const std::string &bid, std::string nowTemp, std::string hashId, std::string deviceName, std::string devicePart, std::string serviceUUID, std::string lastTemp, std::string userName, std::string userID, std::string clientTime, std::string serverTime, std::string clientVersion, std::string screening, std::string screeningTime, std::string forgive)
{
    /* 1. statement return result. */
    std::map<std::string, std::string> result;

    /* 2. statement bottom using. */
    DAL_Bottom bottom;
            
    /* 3. combine cmd. */
    std::map<int, std::string> cmd;
        
    std::map<std::string, std::string> changevar;
    changevar[column_two] = nowTemp;
    changevar[column_three] = hashId;
    changevar[column_four] = deviceName;
    changevar[column_five] = devicePart;
    changevar[column_six] = serviceUUID;
    changevar[column_seven] = lastTemp;
    changevar[column_eight] = userName;
    changevar[column_nine] = userID;
    changevar[column_ten] = clientTime;
    changevar[column_eleven] = serverTime;
    changevar[column_twelve] = clientVersion;
    changevar[column_thirteen] = screening;
    changevar[column_fourteen] = screeningTime;
    changevar[column_fifteen] = forgive;
    
    std::map<std::string, std::string> cmdvar;
    cmdvar[column_one] = bid;
    
    cmd = bottom.update_direct_Bottom(tablename, changevar, "None", cmdvar);

    /* 4. get return. */
    if (cmd[0] == "false")
    {   
        result["Status"] = "failed";
        result["Info"] = "409";
        result["body"] = "<<< cmd >>> combine Error -> USERS UPDATE Single by doingid.";
    }else{
        int getdo = holtercon::GetInstance().mysql_execute(cmd[1]);
        if (getdo == 0)
        {   
            result["Status"] = "success";
            result["Info"] = "200";
            result["body"] = "success";
            holtercon::GetInstance().commit_result();
        }else{
            result["Status"] = "failed";
            result["Info"] = "408";
            result["body"] = "<<< cmd >>> Doing Failed -> USERS UPDATE.";
        }   
    }       
        
    return result;
}

