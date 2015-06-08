#include "check.h"

std::map<std::string, std::string> CHECKDATA::normal_check_outside(std::map<std::string, std::string> data)
{
    /* 1. statement result return. */
    std::map<std::string, std::string> result;

    if (data["timestamp"].size() > 11)
    {
        result["Status"]="false";
        result["Info"]="408";
        result["body"]="input timestamp length not correct.";
        return result;
    }

    /* --- Step 3A. --- */
    std::map<std::string, std::string> expandjson = json_to_pair(data["data"]);
    if (expandjson["Status"] == "failed")
    {
        return expandjson;
    }

    /* --- Step 3B. --- */

    /* 4. combine result. */
    result = data;
    result.erase("data");
    std::map<std::string, std::string>::iterator emap;
    for(emap=expandjson.begin(); emap!=expandjson.end(); emap++)
    {
        result[emap->first]=emap->second;
    }
    result["Status"]="success";
    result["Info"]="200";

    return result;
}
