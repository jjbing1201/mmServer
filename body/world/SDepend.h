#ifndef _SERVERRETURN_DEPEND_HEADER_
#define _SERVERRETURN_DEPEND_HEADER_

#include "world_include.h"
#include "table_include.h"

#include "WorldSpell.h"
#include "WorldFunction.h"

class SERVERETURN_DEPEND
{
public:
    SERVERETURN_DEPEND() {}
    virtual ~SERVERETURN_DEPEND() {}

    std::map<std::string, std::string> user_login_base_data(const std::string&);

    std::vector< std::map<std::string, std::string> > get_messagelist_post(std::string userName, std::string start_location, std::string end_location);

    std::vector< std::map<std::string, std::string> > get_helplist_post();
};

#endif /* _SERVERRETURN_DEPEND_HEADER_ */

