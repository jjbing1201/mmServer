#include "toolfunc.h"

std::string TOOLSFUNCTION::get_autoincrement_line(std::map<std::string, std::string> data)
{
    /* 1. statement return using. */
    std::string result;

    /* 2. using vector to get first column. */
    std::vector<std::string> tmp = split(data["body"], "\r\n");
    std::vector<std::string> tmp_inform = split(tmp[1], "\t\t");

    /* 3. assignment. */
    result = tmp_inform[0];

    return result;
}                                            
    
        
std::string TOOLSFUNCTION::get_autoincrement_line(std::map<std::string, std::string> data, int line)
{   
    /* 1. statement return using. */
    std::string result;

    /* 2. using vector to get first column. */
    std::vector<std::string> tmp = split(data["body"], "\r\n");
    std::vector<std::string> tmp_inform = split(tmp[line-1], "\t\t");

    /* 3. assignment. */
    result = tmp_inform[0];

    return result;
}
    
std::string TOOLSFUNCTION::get_autoincrement_iline(std::map<std::string, std::string> data,int line)
{
    /* 1. statement return using. */
    std::string result;

    /* 2. using vector to get first column. */ 
    std::vector<std::string> tmp = split(data["body"], "\r\n");
    std::vector<std::string> tmp_inform = split(tmp[1], "\t\t");

    /* 3. assignment. */
    result = tmp_inform[line];
    
    return result;
}
    
std::string TOOLSFUNCTION::get_autoincrement_iline(std::map<std::string, std::string> data, int row, int line)
{   
    /* 1. statement return using. */
    std::string result;

    /* 2. using vector to get first column. */
    std::vector<std::string> tmp = split(data["body"], "\r\n");
    std::vector<std::string> tmp_inform = split(tmp[line], "\t\t");
        
    /* 3. assignment. */
    result = tmp_inform[row];
    
    return result;
}


std::map<std::string, std::string> TOOLSFUNCTION::get_map_of_table_column(std::map<std::string, std::string> data, std::string tablename, std::string quote)
{
	/* 1. statement return using. */
    std::map<std::string, std::string> result;
    
    /* 2. using vector to get column. */
    std::vector<std::string> tmp = split(data["body"], quote);
    std::vector<std::string> tmp_inform = split(tmp[1], "\t\t");

    if (tablename == "news_main")
    {
        result["auto_id"] = tmp_inform[0];
        result["send_user_id"] = tmp_inform[1];
        result["send_user_nick_name"] = tmp_inform[2];
        result["send_context"] = tmp_inform[3];
        result["send_attachment"] = tmp_inform[4];
        result["send_time"] = tmp_inform[5];
        result["send_async"] = tmp_inform[6];
        result["send_backup"] = tmp_inform[7];
		result["send_user_icon"] = tmp_inform[8];
    }
	else if (tablename == "relation_abb_friends")
    {   
        result["auto_id"] = tmp_inform[0];
        result["user_id"] = tmp_inform[1];
        result["opsite_id"] = tmp_inform[2];
        result["timestamp"] = tmp_inform[3];
        result["f_status"] = tmp_inform[4];
    }

	return result;
}

std::map<std::string, std::string> TOOLSFUNCTION::get_eachmap_of_table(std::string data, std::string tablename)
{
	/* 1. statement return using. */
    std::map<std::string, std::string> result;
        
    std::vector<std::string> tmp_inform = split(data, "\t\t");
    
    /* 2. using vector to get column. */
	if (tablename == "news_main")
    {
        result["auto_id"] = tmp_inform[0];
        result["send_user_id"] = tmp_inform[1];
        result["send_user_nick_name"] = tmp_inform[2];
        result["send_context"] = tmp_inform[3];
        result["send_attachment"] = tmp_inform[4];
        result["send_time"] = tmp_inform[5];
        result["send_async"] = tmp_inform[6];
        result["send_backup"] = tmp_inform[7];
		result["send_user_icon"] = tmp_inform[8];
    }
	else if (tablename == "relation_abb_friends")
    {   
        result["auto_id"] = tmp_inform[0];
        result["user_id"] = tmp_inform[1];
        result["opsite_id"] = tmp_inform[2];
        result["timestamp"] = tmp_inform[3];
        result["f_status"] = tmp_inform[4];
    }

	return result;
}




