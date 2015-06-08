#include "Serverreturn.h"

using namespace N_WORLD;

std::map<std::string, std::string> WORLDRETURN::serverreturn_inherit(\
                            std::string interface, \
                            std::map<std::string, std::string> data)
{
    /* Statement about result. */
    std::map<std::string, std::string> result; 
    std::map<std::string, std::string> cresult;

    /* Different Interface into Different part. */
    if (interface == "ServerConnect")
    {
        WORLDFUNCTION worldfunc;

        uint32 i;
        uint32 count=0;
        int32 table_size = sizeof(interfaceName)/sizeof(_interHandler);
        for(i=0; i<table_size; i++)
        {
            // Get tmp version of each version
            std::string get_tmp_version = interfaceName[i].version;
            // compare tmpversion with user version
            int compare_result = worldfunc.compare_big_version(data["version"], get_tmp_version);
            if ( compare_result == 0 )
            {
                result[anytostr(count)] = interfaceName[i].name;
                count++;
            }
        }    

        if (count != 0)
        {
            result["Status"]="success";
            result["Info"]="200";
            result["body"]="success";
            return result;
        }
        else
            goto world_serverreturn_error;
    } 

    else if (interface == "UserLoginBaseData")
    {
	WORLDFUNCTION worldfunc;
        SERVERETURN_DEPEND depend;

	std::map<std::string, std::string> get_user_status = depend.user_login_base_data(data["username"]);
	if (get_user_status["Status"] != "success") {
	    goto world_serverreturn_error;
	} else {
	    result[anytostr(1)] = worldfunc.map_to_json(get_user_status);
	    goto world_serverreturn_normal;
	}
    }

    else if (interface == "UserMessageNotification") {
	WORLDFUNCTION worldfunc;
        SERVERETURN_DEPEND depend;
	MM_MESSAGELIST messagelist;
	
	std::map<std::string, std::string> messagecount = messagelist.select_by_username(data["cellphone"]);
	if (messagecount["Status"] != "success") {
            goto world_serverreturn_error;
	} else {
	    result["num"] = worldfunc.get_autoincrement_iline(messagecount, 0);
	    goto world_serverreturn_normal;
	}
    }

    else if (interface == "UserMessageList") {
        WORLDFUNCTION worldfunc;
        SERVERETURN_DEPEND depend;
        MM_MESSAGELIST messagelist;

	/* 1. calc queue. */
        std::string now_page;
        if (data["requestPage"] == "")
            now_page = "0";
        else
            now_page = data["requestPage"];

        int _start_location = atoi(now_page.c_str());
        int _end_location = 10;
	
	std::vector< std::map<std::string, std::string> > messagePage = depend.get_messagelist_post(data["username"], anytostr(_start_location), anytostr(_end_location));
	if (messagePage.size() <= 0)
            goto world_serverreturn_error;
        else
        {
            unsigned int i;
            for(i=0; i<messagePage.size(); i++)
               result[anytostr(i)] = worldfunc.map_to_json(messagePage[i]);

            goto world_serverreturn_normal;
        }
    }

world_serverreturn_error:
    result["Status"]="false";
    result["Info"]="408";
    result["body"]="World return error.";
    return result;

world_serverreturn_cover_error:
    cresult["Status"]="false";
    cresult["Info"]="408";
    cresult["body"]="World return error.";
    return cresult;    

world_serverreturn_normal:
    result["Status"]="success";
    result["Info"]="200";
    result["body"]="success";
    return result;
    
    return result;
}
