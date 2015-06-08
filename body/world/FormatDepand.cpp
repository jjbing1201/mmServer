#include "FormatDepand.h"

std::map<std::string, std::string> WORLDFORMAT_DEPAND::normal_format(\
                                std::map<std::string, std::string> data)
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
        root["strInfo"] = Json::Value("None");
    }else{
        root["strInfo"] = Json::Value(data["body"]);
    }

    std::map<std::string, std::string>::iterator it;
    for(it=data.begin(); it!=data.end(); it++)
    {
        if (it->first == "Status" or it->first == "Info" or it->first == "body")

        {

        }else{
            dataObject[it->first] = it->second;
        }
    }
    root["dataObject"]=dataObject;
    result["body"] = fast_writer.write(root);

    return result;
}
