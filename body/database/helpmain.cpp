#include "helpmain.h"

MM_HELPMAIN::MM_HELPMAIN()
{
     tablename = "HelpMain";
     column_one = "helpId";
     column_two = "helpTitle";
     column_three = "helpContext";
     column_four = "helpTimestamp";
     column_five = "helpDelete";
}

std::map<std::string, std::string> MM_HELPMAIN::insert_HELPMAIN(std::string helpTitle, std::string helpContext, std::string helpTimestamp, std::string helpDelete)
{
    /* 1. using bottom to get insert cmd. */
    std::map<std::string, std::string> result;

    /* 1.1 statement bottom using. */
    DAL_Bottom bottom;
    std::map<int, std::string> cmd;

    /* 1.2 combine vars. */
    std::vector<std::string> tmp;
    tmp.push_back("0");
    tmp.push_back(helpTitle);
    tmp.push_back(helpContext);
    tmp.push_back(helpTimestamp);
    tmp.push_back(helpDelete);

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

std::map<std::string, std::string> MM_HELPMAIN::update_HELPMAIN(const std::string &helpId, std::string helpTitle, std::string helpContext, std::string helpTimestamp, std::string helpDelete)
{
    /* 1. statement return result. */
    std::map<std::string, std::string> result;

    /* 2. statement bottom using. */
    DAL_Bottom bottom;
            
    /* 3. combine cmd. */
    std::map<int, std::string> cmd;
        
    std::map<std::string, std::string> changevar;
    changevar[column_two] = helpTitle;
    changevar[column_three] = helpContext;
    changevar[column_four] = helpTimestamp;
    changevar[column_five] = helpDelete;
    
    std::map<std::string, std::string> cmdvar;
    cmdvar[column_one] = helpId;
    
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

std::map<std::string, std::string> MM_HELPMAIN::update_direct_HELPMAIN(const std::string &helpId, std::string which_column, std::string column_context)
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
     
    cmd[0] = "success";
    cmd[1] = "update "+tablename+" set "+get_judge_column+" = "+
              column_context+" where "+column_one+" = "+helpId+";";


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

std::map<std::string, std::string> MM_HELPMAIN::select_all_table(void)
{
        /* 1. statement return result. */
    std::map<std::string, std::string> result;

    /* 2. statement bottom using. */
    BASE base;
    DAL_Bottom bottom;

    /* 3. combine cmd. */
    std::map<int, std::string> cmd;
    cmd[0] = "success";
    cmd[1] = "select * from "+tablename+" where "+column_five+" = 1;";

    /* 4. get return. */
    if (cmd[0] == "false")
    {
        result["Status"] = "failed";
        result["Info"] = "409";
        result["body"] = "<<< cmd >>> combine Error -> MIWA_BBS_THREAD SELECT Single by id";
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

std::map<std::string, std::string> MM_HELPMAIN::select_by_helpList(std::string start_lo, std::string end_lo)
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
    cmd[1] = "select * from "+tablename+" order by "+column_four+" desc limit "+start_lo+","+end_lo+";";

    /* 4. get return. */
    if (cmd[0] == "false")
    {
        result["Status"] = "failed";
        result["Info"] = "409";
        result["body"] = "<<< cmd >>> combine Error -> MIWA_BBS_THREAD SELECT Single by id";
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
