#include "WorldFunction.h"

int WORLDFUNCTION::_compare_int(int _first, int _second)
{
    if (_first > _second)
    {
        return 0;
    }
    else if(_first == _second)
    {
        return 1;
    }
    else
    {
        return 2;
    }

    return -1;
}

int WORLDFUNCTION::_compare_version(std::vector<std::string> first, \
                                     std::vector<std::string> second)
{
    /* 1. compare big version */
    int _compare_result_big = _compare_int(atoi(first[0].c_str()), \
                                           atoi(second[0].c_str()) );
    if (_compare_result_big == 2 or _compare_result_big == -1)
    {
        return -1;
    }

    /* 2. compare small version. */
    int _compare_result_small = _compare_int(atoi(first[1].c_str()), \
                                             atoi(second[1].c_str()) ); 
    if (_compare_result_small == 2 or _compare_result_small == -1)
    {
        return -1;
    }

    /* 3. compare date version */
    int _compare_result_date = _compare_int(atoi(first[2].c_str()), \
                                            atoi(second[2].c_str()) );
    if (_compare_result_date == 2 or _compare_result_date == -1)
    {
        return -1;
    }

    return 0;
}

int WORLDFUNCTION::_compare_two_version(std::vector<std::string> first, \
                          std::vector<std::string> second)
{
    /* 1. compare big version */
    int _compare_result_big = _compare_int(atoi(first[0].c_str()), \
                                           atoi(second[0].c_str()) );    
    if (_compare_result_big != 1)
        return -1;

    /* 2. compare small version */
    int _compare_result_small = _compare_int(atoi(first[1].c_str()), \
                                             atoi(second[1].c_str()) );
    if (_compare_result_small != 1)
        return -1;

    return 0;
}

int WORLDFUNCTION::compare_big_version(std::string example, std::string input)
{
    std::vector<std::string> _example = split(example, ".");
    std::vector<std::string> _input = split(input, ".");

    return _compare_version(_example, _input);
}

int WORLDFUNCTION::compare_big_small_version(std::string example,  std::string input)
{
    std::vector<std::string> _example = split(example, ".");
    std::vector<std::string> _input = split(input, ".");

    return _compare_two_version(_example, _input);
}

int WORLDFUNCTION::compare_version(std::string server_version,\
                         std::string client_version,\
                         std::string user_client_version)
{
    /* compare server part (server_version and client_version) */
    std::vector<std::string> _server = split(server_version, ".");
    std::vector<std::string> _client = split(client_version, ".");
    std::vector<std::string> _user_client = split(user_client_version, ".");

    /* compare server_version and client_version */
    if ( (_compare_two_version(_server, _client)) == -1 )
    {
        return -1;
    }
     
    /* compare client_version and user_client_version */
    if ( (_compare_two_version(_client, _user_client)) == -1 )
    {
        return -1;
    }

    return 0;
}

std::string WORLDFUNCTION::get_autoincrement_line(std::map<std::string, std::string> data)
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


std::string WORLDFUNCTION::get_autoincrement_line(std::map<std::string, std::string> data, int line)
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

std::string WORLDFUNCTION::get_autoincrement_iline(std::map<std::string, std::string> data,int line)
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

std::string WORLDFUNCTION::get_autoincrement_iline(std::map<std::string, std::string> data, int row, int line)
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

void WORLDFUNCTION::mapPrint(std::map<std::string, std::string> data)
{
    std::map<std::string, std::string>::iterator it;
    for(it=data.begin(); it!=data.end(); it++)
    {
        std::cout << "key : " << it->first << " ###  value : " << it->second << std::endl;
    }

    return;
}

std::map<std::string, std::string> WORLDFUNCTION::get_map_of_table_column(std::map<std::string, std::string> data, std::string tablename, std::string quote)
{
    /* 1. statement return using. */
    std::map<std::string, std::string> result;

    /* 2. using vector to get column. */
    std::vector<std::string> tmp = split(data["body"], quote);
    std::vector<std::string> tmp_inform = split(tmp[1], "\t\t");
    
    if (tablename == "Person")
    {   
        result["userid"] = tmp_inform[0];
        result["username"] = tmp_inform[1];
        result["password"] = tmp_inform[2];
        result["userRealname"] = tmp_inform[3];
        result["userSex"] = tmp_inform[4];
        result["userAge"] = tmp_inform[5];
        result["userAvatar"] = tmp_inform[6];
        result["userDefImage"] = tmp_inform[7];
        result["userBelongOrgId"] = tmp_inform[8];
        result["userPriority"] = tmp_inform[9];
        result["userLastLogin"] = tmp_inform[10];
        result["userLoginType"] = tmp_inform[11];
        result["userBackupThree"] = tmp_inform[12];
        result["userBackupFour"] = tmp_inform[13];
        result["userBackupFive"] = tmp_inform[14];
    } else if (tablename == "VerifyCode") {
        result["verifyId"] = tmp_inform[0];
        result["verifyResource"] = tmp_inform[1];
        result["verifyToUser"] = tmp_inform[2];
        result["verifyNumber"] = tmp_inform[3];
        result["verifyCreateTime"] = tmp_inform[4];
        result["verifyDelay"] = tmp_inform[5];
    } else if (tablename == "MessageList") {
	result["mid"] = tmp_inform[0];
        result["libraryId"] = tmp_inform[1];
        result["ruleId"] = tmp_inform[2];
        result["mContext"] = tmp_inform[3];
        result["userId"] = tmp_inform[4];
        result["userName"] = tmp_inform[5];
        result["createTime"] = tmp_inform[6];
        result["nowStatus"] = tmp_inform[7];
        result["hashId"] = tmp_inform[8];
    } 
    return result;
}

std::map<std::string, std::string> WORLDFUNCTION::get_eachmap_of_table(std::string data, std::string tablename)
{
    /* 1. statement return using. */
    std::map<std::string, std::string> result;
    
    std::vector<std::string> tmp_inform = split(data, "\t\t");

    /* 2. using vector to get column. */
    if (tablename == "Person")
    {
	result["userid"] = tmp_inform[0];
        result["username"] = tmp_inform[1];
        result["password"] = tmp_inform[2];
        result["userRealname"] = tmp_inform[3];
        result["userSex"] = tmp_inform[4];
        result["userAge"] = tmp_inform[5];
        result["userAvatar"] = tmp_inform[6];
        result["userDefImage"] = tmp_inform[7];
        result["userBelongOrgId"] = tmp_inform[8];
        result["userPriority"] = tmp_inform[9];
        result["userLastLogin"] = tmp_inform[10];
        result["userLoginType"] = tmp_inform[11];
        result["userBackupThree"] = tmp_inform[12];
        result["userBackupFour"] = tmp_inform[13];
        result["userBackupFive"] = tmp_inform[14];
    } else if (tablename == "VerifyCode") {
	result["verifyId"] = tmp_inform[0];
        result["verifyResource"] = tmp_inform[1];
        result["verifyToUser"] = tmp_inform[2];
        result["verifyNumber"] = tmp_inform[3];
        result["verifyCreateTime"] = tmp_inform[4];
        result["verifyDelay"] = tmp_inform[5];
    } else if (tablename == "MessageList") {
        result["mid"] = tmp_inform[0];
        result["libraryId"] = tmp_inform[1];
        result["ruleId"] = tmp_inform[2];
        result["mContext"] = tmp_inform[3];
        result["userId"] = tmp_inform[4];
        result["userName"] = tmp_inform[5];
        result["createTime"] = tmp_inform[6];
        result["nowStatus"] = tmp_inform[7];
        result["hashId"] = tmp_inform[8];
    }
    return result;
}

std::string WORLDFUNCTION::map_to_json(std::map<std::string, std::string> data)
{
    Json::FastWriter fast_writer;

    Json::Value tmp;

    std::map<std::string, std::string>::iterator jsonit;
    for(jsonit=data.begin(); jsonit!=data.end(); jsonit++)
    {
        tmp[jsonit->first]=jsonit->second;
    }

    return fast_writer.write(tmp);
}
