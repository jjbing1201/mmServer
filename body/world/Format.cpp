#include "Format.h"

using namespace N_WORLD;

std::map<std::string, std::string> WORLDFORMAT::normal_format_inside(std::string interfaceName,  std::map<std::string, std::string> data)
{
    /* Statement about return => result. */
    std::map<std::string, std::string> result;

    /* 2. normal part for status and Info. */
    result["Status"] = data["Status"];
    result["Info"] = data["Info"];
    
    Json::Value dataObject;
    Json::Value root;
    Json::Reader reader;
    Json::FastWriter fast_writer;
    
    /* inteface -> string */
    root["ResponseID"] = interfaceName;

    /* code -> Integer */ 
    if (data["Status"] == "success")
    {   
        root["code"] = Json::Value(0);
    }else{
        root["code"] = Json::Value(1);
    }
    
    root["incode"] = data["Info"];
    
    /* strInfo -> string */
    if (data["Status"] == "success")
    {   
        root["strInfo"] = Json::Value(data["body"]);
    }else{
        root["strInfo"] = Json::Value(data["body"]);
    }
        
    std::map<std::string, std::string>::iterator it;
    for(it=data.begin(); it!=data.end(); it++)
    {
        if (it->first == "Status" or it->first == "Info" or it->first == "body")
        {
        
        }else{
            dataObject["details"].append(it->second);
        }
    }
    root["statusCode"] = data["statusCode"];
    root["dataObject"]=dataObject;
    result["body"] = fast_writer.write(root);
    
    return result;    
}

std::map<std::string, std::string> WORLDFORMAT::format_inter(\
                                    std::string interface, \
                                    std::map<std::string, std::string> data)
{
    /* Statement about return => result. */
    std::map<std::string, std::string> result;

    /* <<< Into Interface. >>> */
    if (interface == "ServerConnect")
    {
        result = normal_format_outside(data);
    }

    return result;
}

std::map<std::string, std::string> WORLDFORMAT::format_inter_inherit(\
                                   std::string interface, \
                                   std::map<std::string, std::string> data)
{
    /* Statement about return => result. */
    std::map<std::string, std::string> result;

    /* <<< Into Interface. >>> */
    if (interface == "ServerConnect" || 
	interface == "UserLogin" || 
	interface == "UserVerifyCode" || 
	interface == "UserRegister" || 
	interface == "UserPrivateFillin" || 
	interface == "UserResetPass" || 
	interface == "UserMessageNotification" || 
	interface == "UserMessageList" || 
	interface == "UserDataNotification" || 
	interface == "UserHelpList" || 
	interface == "UserMessageEachCheck" || 
	interface == "UserCheckVerifyCode" || 
	interface == "UserLoginBaseData")
        result = normal_format_inside(interface, data);
    
    return result;
}
