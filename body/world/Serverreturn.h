#ifndef _WORLD_SERVER_RETURN_HEADER_
#define _WORLD_SERVER_RETURN_HEADER_

#include "world_include.h"
#include "table_include.h"
#include "WorldSpell.h"
#include "WorldFunction.h"

#include "SDepend.h"

#include "../Master.h"

namespace N_WORLD
{
    class WORLDRETURN : public SERVERRETURN
    {
    public:
        WORLDRETURN() {}
        virtual ~WORLDRETURN() {}

        std::map<std::string, std::string> serverreturn_inherit(\
                            std::string interface, \
                            std::map<std::string, std::string> data);
    };
};

#endif /* _WORLD_SERVER_RETURN_HEADER_ */
