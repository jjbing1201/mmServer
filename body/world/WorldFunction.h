#ifndef _WORLD_FUNCTION_HEADER_
#define _WORLD_FUNCTION_HEADER_

#include "world_include.h"

class WORLDFUNCTION
{
protected:
    int _compare_int(int, int);

    int _compare_version(std::vector<std::string>, std::vector<std::string>);

    int _compare_two_version(std::vector<std::string>, std::vector<std::string>);

public:
    WORLDFUNCTION() {}
    virtual ~WORLDFUNCTION() {}

    std::string get_autoincrement_line(std::map<std::string, std::string> data);

    std::string get_autoincrement_line(std::map<std::string, std::string> data, int line);

    std::string get_autoincrement_iline(std::map<std::string, std::string> data,int line);

    std::string get_autoincrement_iline(std::map<std::string, std::string> data,int row, int line);

    void mapPrint(std::map<std::string, std::string> data);

    int compare_big_version(std::string, std::string);

    int compare_big_small_version(std::string,  std::string);

    int compare_version(std::string server_version,\
                         std::string client_version,\
                         std::string user_client_version);

    std::map<std::string, std::string> get_map_of_table_column(\
                std::map<std::string, std::string> data, \
                std::string tablename, std::string quote);

    std::map<std::string, std::string> get_eachmap_of_table(\
                std::string data, std::string tablename);

    std::string map_to_json(std::map<std::string, std::string> data); 
};

#endif /* _WORLD_FUNCTION_HEADER_ */

