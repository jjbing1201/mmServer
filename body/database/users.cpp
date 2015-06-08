#include "users.h"

MM_USERS::MM_USERS()
{
     tablename = "Person";
     column_one = "userid";
     column_two = "username";
     column_three = "password";
     column_four = "userRealname";
     column_five = "userSex";
     column_six = "userAge";
     column_seven = "userAvatar";
     column_eight = "userDefImage";
     column_nine = "userBelongOrgId";
     column_ten = "userPriority";
     column_eleven = "userLastLogin";
     column_twelve = "userLoginType";
     column_thirteen = "userBackupThree";
     column_fourteen = "userBackupFour";
     column_fifteen = "userBackupFive";
}

std::map<std::string, std::string> MM_USERS::insert_USERS(std::string username, std::string password, std::string userRealname, std::string userSex, std::string userAge, std::string userAvatar, std::string userDefImage, std::string userBelongOrgId, std::string userPriority, std::string userLastLogin, std::string userLoginType, std::string userBackupThree, std::string userBackupFour, std::string userBackupFive)
{
    /* 1. using bottom to get insert cmd. */
    std::map<std::string, std::string> result;

    /* 1.1 statement bottom using. */
    DAL_Bottom bottom;
    std::map<int, std::string> cmd;

    /* 1.2 combine vars. */
    std::vector<std::string> tmp;
    tmp.push_back("0");
    tmp.push_back(username);
    tmp.push_back(password);
    tmp.push_back(userRealname);
    tmp.push_back(userSex);
    tmp.push_back(userAge);
    tmp.push_back(userAvatar);
    tmp.push_back(userDefImage);
    tmp.push_back(userBelongOrgId);
    tmp.push_back(userPriority);
    tmp.push_back(userLastLogin);
    tmp.push_back(userLoginType);
    tmp.push_back(userBackupThree);
    tmp.push_back(userBackupFour);
    tmp.push_back(userBackupFive);

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

std::map<std::string, std::string> MM_USERS::update_USERS(const std::string &user_id, std::string username, std::string password, std::string userRealname, std::string userSex, std::string userAge, std::string userAvatar, std::string userDefImage, std::string userBelongOrgId, std::string userPriority, std::string userLastLogin, std::string userLoginType, std::string userBackupThree, std::string userBackupFour, std::string userBackupFive)
{
    /* 1. statement return result. */
    std::map<std::string, std::string> result;

    /* 2. statement bottom using. */
    DAL_Bottom bottom;
            
    /* 3. combine cmd. */
    std::map<int, std::string> cmd;
        
    std::map<std::string, std::string> changevar;
    changevar[column_two] = username;
    changevar[column_three] = password;
    changevar[column_four] = userRealname;
    changevar[column_five] = userSex;
    changevar[column_six] = userAge;
    changevar[column_seven] = userAvatar;
    changevar[column_eight] = userDefImage;
    changevar[column_nine] = userBelongOrgId;
    changevar[column_ten] = userPriority;
    changevar[column_eleven] = userLastLogin;
    changevar[column_twelve] = userLoginType;
    changevar[column_thirteen] = userBackupThree;
    changevar[column_fourteen] = userBackupFour;
    changevar[column_fifteen] = userBackupFive;
    
    std::map<std::string, std::string> cmdvar;
    cmdvar[column_one] = user_id;
    
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

std::map<std::string, std::string> MM_USERS::update_direct_USERS(const std::string &user_id, std::string which_column, std::string column_context)
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
    else if (which_column == "10")
        get_judge_column = column_eleven;
    else if (which_column == "11")
        get_judge_column = column_twelve;
    else if (which_column == "12")
        get_judge_column = column_thirteen;
    else if (which_column == "13")
        get_judge_column = column_fourteen;
    else if (which_column == "14")
        get_judge_column = column_fifteen;
     
    cmd[0] = "success";
    cmd[1] = "update "+tablename+" set "+get_judge_column+" = "+
              column_context+" where "+column_one+" = "+user_id+";";


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

std::map<std::string, std::string> MM_USERS::select_by_userid(std::string user_id)
{
    /* 1. statement return result. */
    std::map<std::string, std::string> result;

    /* 2. statement bottom using. */
    BASE base;
    DAL_Bottom bottom;

    /* 3. combine cmd. */
    std::map<int, std::string> cmd;
    std::map<std::string, std::string> cmdvar;
    cmdvar[column_one]=user_id;

    cmd = bottom.select_direct_Bottom(tablename, "None", cmdvar);

    /* 4. get return. */
    if (cmd[0] == "false")
    {
        result["Status"] = "failed";
        result["Info"] = "409";
        result["body"] = "<<< cmd >>> combine Error -> MM_USERS SELECT Single by id";
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

std::map<std::string, std::string> MM_USERS::select_by_username(std::string user_name)
{
    /* 1. statement return result. */
    std::map<std::string, std::string> result;
    
    /* 2. statement bottom using. */
    BASE base;
    DAL_Bottom bottom;
    
    /* 3. combine cmd. */
    std::map<int, std::string> cmd;
    std::map<std::string, std::string> cmdvar;
    cmdvar[column_two]=user_name;
    
    cmd = bottom.select_direct_Bottom(tablename, "None", cmdvar);
    
    /* 4. get return. */
    if (cmd[0] == "false")
    {
        result["Status"] = "failed";
        result["Info"] = "409";
        result["body"] = "<<< cmd >>> combine Error -> MM_USERS SELECT Single by id"; 
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

std::map<std::string, std::string> MM_USERS::select_by_login(std::string user_name, std::string user_pass)
{
    /* 1. statement return result. */
    std::map<std::string, std::string> result;

    /* 2. statement bottom using. */
    BASE base;
    DAL_Bottom bottom;

    /* 3. combine cmd. */
    std::map<int, std::string> cmd;
    std::map<std::string, std::string> cmdvar;
    cmdvar[column_two]=user_name;
    cmdvar[column_three]=user_pass;

    cmd = bottom.select_direct_Bottom(tablename, "_and", cmdvar);

    /* 4. get return. */
    if (cmd[0] == "false")
    {
        result["Status"] = "failed";
        result["Info"] = "409";
        result["body"] = "<<< cmd >>> combine Error -> MM_USERS SELECT Single by id";
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
