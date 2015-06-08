#include "interfaceusing.h"

MIWA_INTERFACE_USING::MIWA_INTERFACE_USING()
{
    tablename="abb_interface_using";
    column_one="auto_id";
    column_two="interface_name";
    column_three="last_update_time";
    column_four="all_count";
}

std::map<std::string, std::string> MIWA_INTERFACE_USING::insert_INTERFACE_USING(std::string interface_name, std::string last_update_time, std::string all_count)
{
    /* 1. using bottom to get insert cmd. */
    std::map<std::string, std::string> result;

    /* 1.1 statement bottom using. */
    DAL_Bottom bottom;
    std::map<int, std::string> cmd;

    /* 1.2 combine vars. */
    std::vector<std::string> tmp;
    tmp.push_back("0");
    tmp.push_back(interface_name);
    tmp.push_back(last_update_time);
    tmp.push_back(all_count);

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

std::map<std::string, std::string> MIWA_INTERFACE_USING::update_INTERFACE_USING(const std::string &auto_id, std::string interface_name, std::string last_update_time, std::string all_count)
{
    /* 1. statement return result. */
    std::map<std::string, std::string> result;

    /* 2. statement bottom using. */
    DAL_Bottom bottom;
            
    /* 3. combine cmd. */
    std::map<int, std::string> cmd;
        
    std::map<std::string, std::string> changevar;
    changevar[column_two] = interface_name;
    changevar[column_three] = last_update_time;
    changevar[column_four] = all_count;
    
    std::map<std::string, std::string> cmdvar;
    cmdvar[column_one] = auto_id;
    
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

std::map<std::string, std::string> MIWA_INTERFACE_USING::select_by_autoid(std::string auto_id)
{
    /* 1. statement return result. */
    std::map<std::string, std::string> result;

    /* 2. statement bottom using. */
    BASE base;
    DAL_Bottom bottom;

    /* 3. combine cmd. */
    std::map<int, std::string> cmd;
    std::map<std::string, std::string> cmdvar;
    cmdvar[column_one]=auto_id;

    cmd = bottom.select_direct_Bottom(tablename, "None", cmdvar);

    /* 4. get return. */
    if (cmd[0] == "false")
    {
        result["Status"] = "failed";
        result["Info"] = "409";
        result["body"] = "<<< cmd >>> combine Error -> MIWA_INTERFACE_USING SELECT Single by id";
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

std::map<std::string, std::string> MIWA_INTERFACE_USING::select_one_interface(std::string interface_name)
{
    /* 1. statement return result. */
    std::map<std::string, std::string> result;

    /* 2. statement bottom using. */
    BASE base;
    DAL_Bottom bottom;

    /* 3. combine cmd. */
    std::map<int, std::string> cmd;
    std::map<std::string, std::string> cmdvar;
    cmdvar[column_two]=interface_name;

    cmd = bottom.select_direct_Bottom(tablename, "None", cmdvar);

    /* 4. get return. */
    if (cmd[0] == "false")
    {
        result["Status"] = "failed";
        result["Info"] = "409";
        result["body"] = "<<< cmd >>> combine Error -> MIWA_INTERFACE_USING SELECT Single by id";
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

std::map<std::string, std::string> MIWA_INTERFACE_USING::update_one_interface(std::string interface_name)
{
    /* 1. statement return result. */
    std::map<std::string, std::string> result;
    
    /* 2. statement bottom using. */
    DAL_Bottom bottom;
            
    /* 3. combine cmd. */
    std::map<int, std::string> cmd;
    cmd[0] = "success";
    cmd[1] = "update "+tablename+" set "+column_four+" = "+column_four+" + 1,"
            +column_three+" = UNIX_TIMESTAMP() where "+column_two
            +" = '"+interface_name+"';";    

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
