#include <stdlib.h>
#include <json/json.h>

#include "format.h"

std::map<std::string, std::string> FORMAT::normal_format_outside(std::map<std::string, std::string> data)
{
    /* 1. statement about return result. */
    std::map<std::string, std::string> result;

    /* 2. normal part for status and Info. */
    result["Status"] = data["Status"];
    result["Info"] = data["Info"];

    Json::Value root;
    Json::Value dataObject;
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
    if (data["body"] == "success")
    {
        root["strInfo"] = Json::Value("None");
    }else{
        root["strInfo"] = Json::Value(data["body"]);
    }

    /* dataObject -> objectValue of JSON. */
    root["dataObject"] = dataObject;

    result["body"] = fast_writer.write(root);

    return result;
}

