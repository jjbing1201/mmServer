#include "SDepend.h"

std::map<std::string, std::string> SERVERETURN_DEPEND::user_login_base_data(const std::string& username)
{
    /* Statement. */
    WORLDFUNCTION worldfunc;
    MM_USERS users;
    std::map<std::string, std::string> result;

    std::map<std::string, std::string> check_user_exist = users.select_by_username(username);
    if (check_user_exist["Status"] != "success") {
	return check_user_exist;
    } else {
	result = worldfunc.get_map_of_table_column(check_user_exist, "Person", "\r\n");
	result["Status"] = "success";
	return result;
    }
}

std::vector< std::map<std::string, std::string> > SERVERETURN_DEPEND::get_messagelist_post(std::string userName, std::string start_location, std::string end_location)
{
    WORLDFUNCTION worldfunc;
    MM_MESSAGELIST messagelist;

    uint32 i;
    std::vector< std::map<std::string, std::string> > result;

    std::map<std::string, std::string> messagePage = messagelist.select_by_messageList(userName, start_location, end_location);
    if (messagePage["Status"] != "success") {
        return result;
    } else {
	/* analyst each thread. */
        std::vector<std::string> each_line = split(messagePage["body"], "\r\n");
        for(i=1; i<each_line.size(); i++)
        {
	    std::map<std::string, std::string> get_each_message = worldfunc.get_eachmap_of_table(each_line[i], "MessageList");
	    result.push_back(get_each_message); 
	}

	return result;
    }
}

std::vector< std::map<std::string, std::string> > SERVERETURN_DEPEND::get_helplist_post(std::string start_location, std::string end_location)
{
    WORLDFUNCTION worldfunc;
    MM_HELPMAIN helpmain;

    int i;
    std::vector< std::map<std::string, std::string> > result;

    std::map<std::string, std::string> helpPage = helpmain.select_by_helpList(start_location, end_location);
    if (helpPage["Status"] != "success") {
	return result;
    } else {
	/* analyst each thread. */
        std::vector<std::string> each_line = split(helpPage["body"], "\r\n");
        for(i=1; i<each_line.size(); i++)
        {
            std::map<std::string, std::string> get_each_help = worldfunc.get_eachmap_of_table(each_line[i], "HelpMain");
            result.push_back(get_each_help);
        }

        return result;
    }
}
