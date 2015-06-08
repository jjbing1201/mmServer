#include "base.h"

BASE::BASE()
{

}

BASE::~BASE()
{

}

int BASE::doingjudge(std::string dovar)
{
    std::vector<std::string> tmp = split(dovar, "\r\n");
    return tmp.size();
}


std::vector<std::string> BASE::split(const std::string &str, std::string quote)
{
    std::string newstr = str+quote;
    std::vector<std::string> result;

    while(newstr.find(quote) != std::string::npos)
    {
        std::string tmp = newstr.substr(0, newstr.find(quote));
        newstr = newstr.erase(0, newstr.find(quote)+quote.size());
        if (strlen(tmp.c_str()) == 0)
        {
            continue;
        }else{
            result.push_back(tmp);
        }
    }
    return result;
}
