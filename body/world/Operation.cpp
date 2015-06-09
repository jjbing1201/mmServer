#include "Operation.h"
#include "../../tools/sms.h"
#include "../../framework/AlgorithmHash.h"

using namespace N_WORLD; 

std::map<std::string, std::string> WORLDOPERATION::operation_inherit(\
                            std::string interface, \
                            std::map<std::string, std::string> data)
{
    /* Statement about result. */
    std::map<std::string, std::string> result;

    /* Different Interface into Different part. */
    if (interface == "ServerConnect")
    {
        /* Part 1. check platform. */
        if (data["platform"] == "ANDROID" or data["platform"] == "IOS") {}
        else 
            goto world_operation_error; 

        /* Part 2. check type. */
        INIReader reader("config.ini");

        std::string _type = reader.Get("METHOD", data["type"].c_str(), "-1");
        if (_type == "-1")
            goto world_operation_error;

        std::string server_version = reader.Get("SERVER_VERSION", "configserver"
, "0.0.000000");
        std::string client_version = reader.Get(data["platform"].c_str(), _type.
c_str(), "0.0.000000");

        /* Part 3. compare about version. */
        WORLDFUNCTION worldfunc;
        int compare_result = worldfunc.compare_version(\
                server_version, client_version, data["version"]);
        if ( compare_result == -1 )
        {
            goto world_operation_error;
        }

        goto world_operation_normal;
    }

    else if (interface == "UserLogin")
    {
        WORLDFUNCTION worldfunc;
        OPERATION_DEPEND depend;
	MM_USERS users;

        uint32 nowtime = nowtimestamp();
        std::string now_time = anytostr(nowtime);

	std::map<std::string, std::string> check_user_exist = users.select_by_login(data["username"], data["password"]);
	if (check_user_exist["Status"] != "success")
            goto world_operation_error;
	
	goto world_operation_normal;
    }

    else if (interface == "UserVerifyCode")
    {
        WORLDFUNCTION worldfunc;
        OPERATION_DEPEND depend;
        MM_VERIFYCODE verifycode;
	MESSAGE_SMS sms;

	/* 1. get default variables */
        uint32 nowtime = nowtimestamp();
        std::string now_time = anytostr(nowtime);

	uint32 createcode = urand(100000, 888888);
        std::string string_code = anytostr(createcode);
	std::string send_data = "【温尔科技】欢迎使用体温HOLTER，您的确认码是"+string_code+"，请输入确认码完成验证(如非本人操作，可不予理会)";

        /* 2. check data exist. */
	std::map<std::string, std::string> get_ensure_telephone = verifycode.select_by_send(data["verifyType"], data["cellphone"]);
	if (get_ensure_telephone["Status"] != "success") {
	    std::map<std::string, std::string> new_verifycode = verifycode.insert_VERIFYCODE(data["verifyType"], data["cellphone"], string_code, now_time);
  	    if (new_verifycode["Status"] != "success") {
		goto world_operation_error;
	    } else {
		sms.push_notification_of_sms((char*)data["cellphone"].c_str(), (char*)send_data.c_str()); 
		goto world_operation_normal;
	    }
	} else {
	    std::string verify_id = worldfunc.get_autoincrement_line(get_ensure_telephone);
	    std::map<std::string, std::string> update_verifycode = verifycode.update_VERIFYCODE(verify_id, data["verifyType"], data["cellphone"], string_code, now_time);
	    if (update_verifycode["Status"] != "success") {
                goto world_operation_error;
            } else {
		sms.push_notification_of_sms((char*)data["cellphone"].c_str(), (char*)send_data.c_str());
                goto world_operation_normal;
            }
	}
    }

    else if (interface == "UserRegister")
    {
	WORLDFUNCTION worldfunc;
        OPERATION_DEPEND depend;
	MM_USERS users;
	MM_VERIFYCODE verifycode;
	
	/* 1. get default variables */
        uint32 nowtime = nowtimestamp();
        std::string now_time = anytostr(nowtime);

	/* 2. check user exist. */
	std::map<std::string, std::string> select_exist_user = users.select_by_username(data["cellphone"]);
	if (select_exist_user["Status"] != "success") {
	    /* 3.1 check token pass. */
   	    std::map<std::string, std::string> token_pass = verifycode.select_by_send(data["registerresource"], data["cellphone"]);
	    if (token_pass["Status"] != "success") {
		result["body"] = "register token not found, please reapply for.";
		goto world_operation_normal_nocover;	
	    } else {
		/* 3.2. input token error. */
		std::map<std::string, std::string> check_token = worldfunc.get_map_of_table_column(token_pass, "VerifyCode", "\r\n");
		if (check_token["verifyNumber"] != data["verifycode"]) {
		    result["body"] = "token input error, please check.";
		    goto world_operation_normal_nocover;
		} 
		    
		/* 3.3 token delay */
		if (nowtime > atoi(check_token["verifyCreateTime"].c_str()) + atoi(check_token["verifyDelay"].c_str())) {
		    result["body"] = "token delay, please reapply.";
		    goto world_operation_normal_nocover;	
		}    		
	    }

	    std::map<std::string, std::string> insert_new_users = users.insert_USERS(data["cellphone"],  data["password"], "None", "1", "0", "None", "None", "None", "0", now_time);
	    if (insert_new_users["Status"] != "success") {
		return insert_new_users;
	    } else {
		goto world_operation_normal;
	    }
	} else {
	    result["body"] = "user already exist.";
	    goto world_operation_normal_nocover;
	}
    }

    else if (interface == "UserPrivateFillin")
    {
        WORLDFUNCTION worldfunc;
        OPERATION_DEPEND depend;
        MM_USERS users;

        /* 1. get default variables */
        uint32 nowtime = nowtimestamp();
        std::string now_time = anytostr(nowtime);

	/* 2. get user id */
 	std::map<std::string, std::string> select_exist_user = users.select_by_username(data["cellphone"]);
	if (select_exist_user["Status"] != "success") {
	    return select_exist_user;
	} else {
	    std::map<std::string, std::string> user_detail = worldfunc.get_map_of_table_column(select_exist_user, "Person", "\r\n");
	    
	    std::map<std::string, std::string> update_user_private = users.update_USERS(user_detail["userid"], user_detail["username"], user_detail["password"], data["realname"], data["gender"], data["age"], user_detail["userAvatar"], user_detail["userDefImage"], user_detail["userBelongOrgId"], user_detail["userPriority"], now_time); 
	    goto world_operation_normal;
	}
    }

    else if (interface == "UserResetPass")
    {
        WORLDFUNCTION worldfunc;
        OPERATION_DEPEND depend;
        MM_USERS users;
	MM_VERIFYCODE verifycode;

	/* 1. get default variables */
        uint32 nowtime = nowtimestamp();
        std::string now_time = anytostr(nowtime);

	/* 2. get user id */
	std::map<std::string, std::string> select_exist_user = users.select_by_username(data["cellphone"]);
        if (select_exist_user["Status"] != "success") {
            return select_exist_user;
        } else {
	    /* 3.1 check token pass. */
            std::map<std::string, std::string> token_pass = verifycode.select_by_send("3", data["cellphone"]);
            if (token_pass["Status"] != "success") {
                result["body"] = "register token not found, please reapply for.";
                goto world_operation_normal_nocover;
            } else {
                /* 3.2. input token error. */
                std::map<std::string, std::string> check_token = worldfunc.get_map_of_table_column(token_pass, "VerifyCode", "\r\n");
                if (check_token["verifyNumber"] != data["verifycode"]) {
                    result["body"] = "token input error, please check.";
                    goto world_operation_normal_nocover;
                }

                /* 3.3 token delay */
                if (nowtime > atoi(check_token["verifyCreateTime"].c_str()) + atoi(check_token["verifyDelay"].c_str())) {
                    result["body"] = "token delay, please reapply.";
                    goto world_operation_normal_nocover;
                }
            }	    

	    /* 4.1 do Operation Reset */
	    std::map<std::string, std::string> user_detail = worldfunc.get_map_of_table_column(select_exist_user, "Person", "\r\n");

	    std::map<std::string, std::string> update_user_password = users.update_USERS(user_detail["userid"], user_detail["username"], data["newpass"], user_detail["userRealname"], user_detail["userSex"], user_detail["userAge"], user_detail["userAvatar"], user_detail["userDefImage"], user_detail["userBelongOrgId"], user_detail["userPriority"], now_time);
	    goto world_operation_normal;
	}
    }

    else if (interface == "UserDataNotification")
    {
        WORLDFUNCTION worldfunc;
        OPERATION_DEPEND depend;
	MM_BASEDATA basedata;
 	
	uint32 nowtime = nowtimestamp();
        std::string now_time = anytostr(nowtime);

        std::string baseTablename = "baseData_";

 	// userName + deviceName + devicePart + serverTime +nowTemp
 	std::string keydata = data["userName"]+data["deviceName"]+data["devicePart"]+now_time+data["nowTemp"];
	std::map<std::string, std::string> getNodeInfo = bdhash::GetInstance().nodeGet(keydata);
	if (getNodeInfo["nodeId"] == "0") {
	    goto world_operation_error;
	} else {
	    baseTablename += getNodeInfo["nodeId"]; 
	    basedata.insert_BASEDATA(baseTablename, data["nowTemp"], "hashId", data["deviceName"], data["devicePart"], data["serviceUUID"], data["lastTemp"], data["userName"], data["userID"], data["clientTime"], now_time, data["clientVersion"], "0", "1000000000");

	    goto world_operation_normal;
        }
    }

world_operation_error:
    result["Status"]="false";
    result["Info"]="408";
    result["body"]="Operation return error.";
    return result;

world_operation_normal:
    result["Status"]="success";
    result["Info"]="200";
    result["body"]="success";
    return result;

world_operation_normal_nocover:
    result["Status"]="success";
    result["Info"]="200";
    return result;

    return result;
}
