#include "verifycode.h"

MM_VERIFYCODE::MM_VERIFYCODE()
{
     tablename = "VerifyCode";
     column_one = "verifyId";
     column_two = "verifyResource";
     column_three = "verifyToUser";
     column_four = "verifyNumber";
     column_five = "verifyCreateTime";
     column_six = "verifyDelay";
}

std::map<std::string, std::string> MM_VERIFYCODE::insert_VERIFYCODE(std::string verifyResource, std::string verifyToUser, std::string verifyNumber, std::string verifyCreateTime, std::string verifyDelay)
{
    /* 1. using bottom to get insert cmd. */
    std::map<std::string, std::string> result;

    /* 1.1 statement bottom using. */
    DAL_Bottom bottom;
    std::map<int, std::string> cmd;

    /* 1.2 combine vars. */
    std::vector<std::string> tmp;
    tmp.push_back("0");
    tmp.push_back(verifyResource);
    tmp.push_back(verifyToUser);
    tmp.push_back(verifyNumber);
    tmp.push_back(verifyCreateTime);
    tmp.push_back(verifyDelay);

    cmd = bottom.insert_Bottom(tablename, tmp.size(), tmp);

    /* 2. get return of execute. */
    if (cmd[0] == "false")
    {
        result["Status"] = "failed";
        result["Info"] = "409";
        result["body"] = "<<< cmd >>> combine Error -> USERS INSERT.";
    }else{
        int getdo = datacon::GetInstance().mysql_execute(cmd[1]);
        if (getdo == 0)
        {
            result["Status"] = "success";
            result["Info"] = "200";
            result["body"] = "success";
            datacon::GetInstance().commit_result();
        }else{
            result["Status"] = "failed";
            result["Info"] = "408";
            result["body"] = "<<< cmd >>> Doing Failed -> USERS INSERT.";
        }
    }
    return result;
}

std::map<std::string, std::string> MM_VERIFYCODE::update_VERIFYCODE(const std::string &verifyId, std::string verifyResource, std::string verifyToUser, std::string verifyNumber, std::string verifyCreateTime, std::string verifyDelay)
{
    /* 1. statement return result. */
    std::map<std::string, std::string> result;

    /* 2. statement bottom using. */
    DAL_Bottom bottom;
            
    /* 3. combine cmd. */
    std::map<int, std::string> cmd;
        
    std::map<std::string, std::string> changevar;
    changevar[column_two] = verifyResource;
    changevar[column_three] = verifyToUser;
    changevar[column_four] = verifyNumber;
    changevar[column_five] = verifyCreateTime;
    changevar[column_six] = verifyDelay;
    
    std::map<std::string, std::string> cmdvar;
    cmdvar[column_one] = verifyId;
    
    cmd = bottom.update_direct_Bottom(tablename, changevar, "None", cmdvar);

    /* 4. get return. */
    if (cmd[0] == "false")
    {   
        result["Status"] = "failed";
        result["Info"] = "409";
        result["body"] = "<<< cmd >>> combine Error -> USERS UPDATE Single by doingid.";
    }else{
        int getdo = datacon::GetInstance().mysql_execute(cmd[1]);
        if (getdo == 0)
        {   
            result["Status"] = "success";
            result["Info"] = "200";
            result["body"] = "success";
            datacon::GetInstance().commit_result();
        }else{
            result["Status"] = "failed";
            result["Info"] = "408";
            result["body"] = "<<< cmd >>> Doing Failed -> USERS UPDATE.";
        }   
    }       
        
    return result;
}

std::map<std::string, std::string> MM_VERIFYCODE::update_direct_VERIFYCODE(const std::string &verifyId, std::string which_column, std::string column_context)
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
     
    cmd[0] = "success";
    cmd[1] = "update "+tablename+" set "+get_judge_column+" = "+
              column_context+" where "+column_one+" = "+verifyId+";";


    /* 4. get return. */
    if (cmd[0] == "false")
    {
        result["Status"] = "failed";
        result["Info"] = "409";
        result["body"] = "<<< cmd >>> combine Error -> USERS UPDATE Single by doingid.";
    }else{
        int getdo = datacon::GetInstance().mysql_execute(cmd[1]);
        if (getdo == 0)
        {
            result["Status"] = "success";
            result["Info"] = "200";
            result["body"] = "success";
            datacon::GetInstance().commit_result();
        }else{
            result["Status"] = "failed";
            result["Info"] = "408";
            result["body"] = "<<< cmd >>> Doing Failed -> USERS UPDATE.";
        }
    }

    return result;
}

std::map<std::string, std::string> MM_VERIFYCODE::select_by_verifycodeid(std::string verifyId)
{
    /* 1. statement return result. */
    std::map<std::string, std::string> result;

    /* 2. statement bottom using. */
    BASE base;
    DAL_Bottom bottom;

    /* 3. combine cmd. */
    std::map<int, std::string> cmd;
    std::map<std::string, std::string> cmdvar;
    cmdvar[column_one]=verifyId;

    cmd = bottom.select_direct_Bottom(tablename, "None", cmdvar);

    /* 4. get return. */
    if (cmd[0] == "false")
    {
        result["Status"] = "failed";
        result["Info"] = "409";
        result["body"] = "<<< cmd >>> combine Error -> MM_VERIFYCODE SELECT Single by id";
    }else{
        std::string getcmddoing = datacon::GetInstance().get_execute_result(cmd[1]);
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

std::map<std::string, std::string> MM_VERIFYCODE::select_by_send(std::string verifyResource, std::string verifyToUser)
{
    /* 1. statement return result. */
    std::map<std::string, std::string> result;

    /* 2. statement bottom using. */
    BASE base;
    DAL_Bottom bottom;

    /* 3. combine cmd. */
    std::map<int, std::string> cmd;
    std::map<std::string, std::string> cmdvar;
    cmdvar[column_two]=verifyResource;
    cmdvar[column_three]=verifyToUser;

    cmd = bottom.select_direct_Bottom(tablename, "_and", cmdvar);

    /* 4. get return. */
    if (cmd[0] == "false")
    {
        result["Status"] = "failed";
        result["Info"] = "409";
        result["body"] = "<<< cmd >>> combine Error -> MM_VERIFYCODE SELECT Single by id";
    }else{
        std::string getcmddoing = datacon::GetInstance().get_execute_result(cmd[1]);
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
