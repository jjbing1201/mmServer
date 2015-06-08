#ifndef _WORLD_OPERATION_HEADER_
#define _WORLD_OPERATION_HEADER_

#include "world_include.h"
#include "table_include.h"
#include "WorldSpell.h"
#include "WorldFunction.h"

#include "ODepend.h"

namespace N_WORLD
{
    class WORLDOPERATION : public OPERATION
    {
    public:
        WORLDOPERATION() {}
        virtual ~WORLDOPERATION() {}

        std::map<std::string, std::string> operation_inherit(\
                            std::string interface, \
                            std::map<std::string, std::string> data);
    };
};

#endif /* _WORLD_OPERATION_HEADER_ */

