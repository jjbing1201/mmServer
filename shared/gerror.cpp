#include <stdlib.h>
#include <json/json.h>

#include "gerror.h"

std::string ErrorBase::format_globalerror(std::string incode, \
                                          std::string description)
{
    /* 1. statement about return result. */
    std::string result;

    /* 2. normal part for status and Info. */
    Json::Value root;
    Json::Value dataObject;
    Json::FastWriter fast_writer;

    root["code"] = Json::Value(1);
    root["incode"] = Json::Value(incode);
    root["strInfo"] = Json::Value(description);

    root["dataObject"] = dataObject;

    return fast_writer.write(root);
}
