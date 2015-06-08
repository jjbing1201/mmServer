#ifndef _TOOLS_FUNCTION_HEADER_
#define _TOOLS_FUNCTION_HEADER_

#include <iostream>
#include <map>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <json/json.h>

#include "../shared/util.h"

class TOOLSFUNCTION
{
public:
	std::string get_autoincrement_line(std::map<std::string, std::string> data);

    std::string get_autoincrement_line(std::map<std::string, std::string> data, int line);

    std::string get_autoincrement_iline(std::map<std::string, std::string> data,int line);

    std::string get_autoincrement_iline(std::map<std::string, std::string> data,int row, int line);

	std::map<std::string, std::string> get_map_of_table_column(\
                std::map<std::string, std::string> data, \
                std::string tablename, std::string quote);

    std::map<std::string, std::string> get_eachmap_of_table(\
                std::string data, std::string tablename);
};



#endif /* _TOOLS_FUNCTION_HEADER_ */
