#include "messagelist.h"

MM_MESSAGELIST::MM_MESSAGELIST()
{
     tablename = "MessageList";
     column_one = "mid";
     column_two = "libraryId";
     column_three = "ruleId";
     column_four = "mContext";
     column_five = "userId";
     column_six = "userName";
     column_seven = "createTime";
     column_eight = "nowStatus";
     column_nine = "hashId";
     column_ten = "mTitle";
}

std::map<std::string, std::string> MM_MESSAGELIST::insert_MESSAGELIST(std::string libraryId, std::string ruleId, std::string mContext, std::string userId, std::string userName, std::string createTime, std::string nowStatus, std::string hashId, std::string mTitle)
{
    /* 1. using bottom to get insert cmd. */
    std::map<std::string, std::string> result;

    /* 1.1 statement bottom using. */
    DAL_Bottom bottom;
    std::map<int, std::string> cmd;

    /* 1.2 combine vars. */
    std::vector<std::string> tmp;
    tmp.push_back("0");
    tmp.push_back(libraryId);
    tmp.push_back(ruleId);
    tmp.push_back(mContext);
    tmp.push_back(userId);
    tmp.push_back(userName);
    tmp.push_back(createTime);
    tmp.push_back(nowStatus);
    tmp.push_back(hashId);
    tmp.push_back(mTitle);

    cmd = bottom.insert_Bottom(tablename, tmp.size(), tmp);

    /* 2. get return of execute. */
    if (cmd[0] == "false")
    {
        result["Status"] = "failed";
        result["Info"] = "409";
        result["body"] = "<<< cmd >>> combine Error -> USERS INSERT.";
    }else{
        int getdo = messagecon::GetInstance().mysql_execute(cmd[1]);
        if (getdo == 0)
        {
            result["Status"] = "success";
            result["Info"] = "200";
            result["body"] = "success";
            messagecon::GetInstance().commit_result();
        }else{
            result["Status"] = "failed";
            result["Info"] = "408";
            result["body"] = "<<< cmd >>> Doing Failed -> USERS INSERT.";
        }
    }
    return result;
}

std::map<std::string, std::string> MM_MESSAGELIST::update_MESSAGELIST(const std::string &mid, std::string libraryId, std::string ruleId, std::string mContext, std::string userId, std::string userName, std::string createTime, std::string nowStatus, std::string hashId, std::string mTitle)
{
    /* 1. statement return result. */
    std::map<std::string, std::string> result;

    /* 2. statement bottom using. */
    DAL_Bottom bottom;
            
    /* 3. combine cmd. */
    std::map<int, std::string> cmd;
        
    std::map<std::string, std::string> changevar;
    changevar[column_two] = libraryId;
    changevar[column_three] = ruleId;
    changevar[column_four] = mContext;
    changevar[column_five] = userId;
    changevar[column_six] = userName;
    changevar[column_seven] = createTime;
    changevar[column_eight] = nowStatus;
    changevar[column_nine] = hashId;
    changevar[column_ten] = mTitle;
    
    std::map<std::string, std::string> cmdvar;
    cmdvar[column_one] = mid;
    
    cmd = bottom.update_direct_Bottom(tablename, changevar, "None", cmdvar);

    /* 4. get return. */
    if (cmd[0] == "false")
    {   
        result["Status"] = "failed";
        result["Info"] = "409";
        result["body"] = "<<< cmd >>> combine Error -> USERS UPDATE Single by doingid.";
    }else{
        int getdo = messagecon::GetInstance().mysql_execute(cmd[1]);
        if (getdo == 0)
        {   
            result["Status"] = "success";
            result["Info"] = "200";
            result["body"] = "success";
            messagecon::GetInstance().commit_result();
        }else{
            result["Status"] = "failed";
            result["Info"] = "408";
            result["body"] = "<<< cmd >>> Doing Failed -> USERS UPDATE.";
        }   
    }       
        
    return result;
}

std::map<std::string, std::string> MM_MESSAGELIST::update_direct_MESSAGELIST(const std::string &mid, std::string which_column, std::string column_context)
{
    /* 1. statement return result. */
    std::map<std::string, std::string> result;

    /* 2. statement bottom using. */
    DAL_Bottom bottom;

    /* 3. combine cmd. */
    std::map<int, std::string> cmd;
    std::string get_judge_column;
    if (which_column == "2")
        get_judge_column = column_three;
    else if (which_column == "3")
        get_judge_column = column_four;
    else if (which_column == "4")
        get_judge_column = column_five;
    else if (which_column == "5")
        get_judge_column = column_six;
    else if (which_column == "6")
        get_judge_column = column_seven;
    else if (which_column == "7")
        get_judge_column = column_eight;
    else if (which_column == "8")
        get_judge_column = column_nine;
    else if (which_column == "9")
        get_judge_column = column_ten;
     
    cmd[0] = "success";
    cmd[1] = "update "+tablename+" set "+get_judge_column+" = "+
              column_context+" where "+column_one+" = "+mid+";";


    /* 4. get return. */
    if (cmd[0] == "false")
    {
        result["Status"] = "failed";
        result["Info"] = "409";
        result["body"] = "<<< cmd >>> combine Error -> USERS UPDATE Single by doingid.";
    }else{
        int getdo = messagecon::GetInstance().mysql_execute(cmd[1]);
        if (getdo == 0)
        {
            result["Status"] = "success";
            result["Info"] = "200";
            result["body"] = "success";
            messagecon::GetInstance().commit_result();
        }else{
            result["Status"] = "failed";
            result["Info"] = "408";
            result["body"] = "<<< cmd >>> Doing Failed -> USERS UPDATE.";
        }
    }

    return result;
}

std::map<std::string, std::string> MM_MESSAGELIST::select_by_messageid(std::string mid)
{
    /* 1. statement return result. */
    std::map<std::string, std::string> result;

    /* 2. statement bottom using. */
    BASE base;
    DAL_Bottom bottom;

    /* 3. combine cmd. */
    std::map<int, std::string> cmd;
    std::map<std::string, std::string> cmdvar;
    cmdvar[column_one]=mid;

    cmd = bottom.select_direct_Bottom(tablename, "None", cmdvar);

    /* 4. get return. */
    if (cmd[0] == "false")
    {
        result["Status"] = "failed";
        result["Info"] = "409";
        result["body"] = "<<< cmd >>> combine Error -> MM_MESSAGELIST SELECT Single by id";
    }else{
        std::string getcmddoing = messagecon::GetInstance().get_execute_result(cmd[1]);
        int check_getcmddoing = base.doingjudge(getcmddoing);
        if (check_getcmddoing == 1)
        {
            result["Status"] = "failed";
            result["Info"] = "408";
            result["body"] = "<<< cmd >>> doing Error -> USERS SELECT Single by id";
        }else{
            result["Status"] = "success";
            result["Info"] = "200";
            result["body"] = getcmddoing;
        }
    }

    return result;
}

std::map<std::string, std::string> MM_MESSAGELIST::select_by_username(std::string userName)
{
    /* 1. statement return result. */
    std::map<std::string, std::string> result;
    
    /* 2. statement bottom using. */
    BASE base;
    DAL_Bottom bottom;
    
    /* 3. combine cmd. */
    std::map<int, std::string> cmd;
    std::map<std::string, std::string> cmdvar;
    cmdvar[column_two]=userName;
    
    cmd[0] = "success";
    cmd[1] = "select count(*) from "+tablename+" where "+column_six+" = \""+userName+"\" and "+column_eight+" = 0;";
    
    /* 4. get return. */
    if (cmd[0] == "false")
    {
        result["Status"] = "failed";
        result["Info"] = "409";
        result["body"] = "<<< cmd >>> combine Error -> MM_MESSAGELIST SELECT Single by id"; 
    }else{
        std::string getcmddoing = messagecon::GetInstance().get_execute_result(cmd[1]);    
        int check_getcmddoing = base.doingjudge(getcmddoing);
        if (check_getcmddoing == 1)
        {
            result["Status"] = "failed";
            result["Info"] = "408";
            result["body"] = "<<< cmd >>> doing Error -> USERS SELECT Single by id";        
        }else{
            result["Status"] = "success";
            result["Info"] = "200";
            result["body"] = getcmddoing;
        }   
    }   
    
    return result;
}

std::map<std::string, std::string> MM_MESSAGELIST::select_by_messageList(std::string userName, std::string start_lo, std::string end_lo)
{
    /* 1. statement return result. */
    std::map<std::string, std::string> result;

    /* 2. statement bottom using. */
    BASE base;
    DAL_Bottom bottom;

    /* 3. combine cmd. */
    std::map<int, std::string> cmd;
    std::map<std::string, std::string> cmdvar;
    cmd[0] = "success";
    cmd[1] = "select * from "+tablename+" where "+column_six+" = \""+userName
            +"\" and "+column_eight+" = 0 order by "+column_seven+" desc limit "+start_lo+","+end_lo+";";

    /* 4. get return. */
    if (cmd[0] == "false")
    {
        result["Status"] = "failed";
        result["Info"] = "409";
        result["body"] = "<<< cmd >>> combine Error -> MIWA_BBS_THREAD SELECT Single by id";
    }else{
        std::string getcmddoing = messagecon::GetInstance().get_execute_result(cmd[1]);
        int check_getcmddoing = base.doingjudge(getcmddoing);
        if (check_getcmddoing == 1)
        {
            result["Status"] = "failed";
            result["Info"] = "408";
            result["body"] = "<<< cmd >>> doing Error -> USERS SELECT Single by id";
        }else{
            result["Status"] = "success";
            result["Info"] = "200";
            result["body"] = getcmddoing;
        }
    }

    return result;
}
