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
	    cresult["statusCode"]="-10";
	    goto world_serverreturn_cover_error;
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
	    cresult["statusCode"]="-11";
            goto world_serverreturn_cover_error;
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

        int _start_location = atoi(now_page.c_str())*10;
        int _end_location = 10;
	
	std::vector< std::map<std::string, std::string> > messagePage = depend.get_messagelist_post(data["username"], anytostr(_start_location), anytostr(_end_location));
	if (messagePage.size() <= 0)
	{
	    cresult["statusCode"]="-12";
            goto world_serverreturn_cover_error;
	}
        else
        {
            unsigned int i;
            for(i=0; i<messagePage.size(); i++)
               result[anytostr(i)] = worldfunc.map_to_json(messagePage[i]);

            goto world_serverreturn_normal;
        }
    }

    else if (interface == "UserHelpList") {
        WORLDFUNCTION worldfunc;
        SERVERETURN_DEPEND depend;
	MM_HELPMAIN helpmain;

	std::string now_page;

	if (data["pages"] == "")
            now_page = "0";
        else
            now_page = data["pages"];

        int _start_location = atoi(now_page.c_str())*5;
        int _end_location = 5;

        std::vector< std::map<std::string, std::string> > helpPage = depend.get_helplist_post(anytostr(_start_location), anytostr(_end_location));
        if (helpPage.size() <= 0)
	{
	    cresult["statusCode"] = "-13";
            goto world_serverreturn_cover_error;
	}
        else
        {
            unsigned int i;
            for(i=0; i<helpPage.size(); i++)
               result[anytostr(i)] = worldfunc.map_to_json(helpPage[i]);

            goto world_serverreturn_normal;
        }	
    }

    else if (interface == "UserCheckVerifyCode") {
        WORLDFUNCTION worldfunc;
        SERVERETURN_DEPEND depend;
	MM_USERS users;
	MM_VERIFYCODE verifycode;

	uint32 nowtime = nowtimestamp();
        std::string now_time = anytostr(nowtime);

	std::map<std::string, std::string> select_exist_user = users.select_by_username(data["cellphone"]);
        if (select_exist_user["Status"] == "success") {
            /* 3.1 check token pass. */
            std::map<std::string, std::string> token_pass = verifycode.select_by_send(data["registerresource"], data["cellphone"]);
            if (token_pass["Status"] != "success") {
                cresult["body"] = "register token not found, please reapply for.";
                cresult["statusCode"] = "-1";
                goto world_serverreturn_cover_error;
            } else {
                /* 3.2. input token error. */
                std::map<std::string, std::string> check_token = worldfunc.get_map_of_table_column(token_pass, "VerifyCode", "\r\n");
                if (check_token["verifyNumber"] != data["verifycode"]) {
                    cresult["body"] = "token input error, please check.";
                    cresult["statusCode"] = "-2";
                    goto world_serverreturn_cover_error;
                }

                /* 3.3 token delay */
                if (nowtime > atoi(check_token["verifyCreateTime"].c_str()) + atoi(check_token["verifyDelay"].c_str())) {
                    cresult["body"] = "token delay, please reapply.";
                    cresult["statusCode"] = "-3";
                    goto world_serverreturn_cover_error;
                }
            }
	} else {
	    cresult["statusCode"] = "-14";
	    goto world_serverreturn_cover_error;
	}

        goto world_serverreturn_normal;
    }

world_serverreturn_error:
    result["Status"]="false";
    result["Info"]="408";
    result["body"]="World return error.";
    result["statusCode"]="1";
    return result;

world_serverreturn_cover_error:
    cresult["Status"]="success";
    cresult["Info"]="200";
    cresult["body"]="success";
    return cresult;    

world_serverreturn_normal:
    result["Status"]="success";
    result["Info"]="200";
    result["body"]="success";
    result["statusCode"]="0";
    return result;
    
    return result;
}
