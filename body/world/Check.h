#ifndef _WORLD_CHECK_HEADER_
#define _WORLD_CHECK_HEADER_

#include "world_include.h"

namespace N_WORLD
{
    class WORLDCHECK : public CHECKDATA
    {
    protected:
        std::map<std::string, std::string> check_inside(std::map<std::string, std::string> data);

    public:
        WORLDCHECK() {}
        virtual ~WORLDCHECK() {}

        std::map<std::string, std::string> check_inter(std::string interface, \
                                   std::map<std::string, std::string> data);
    
    };

};

#endif /* _WORLD_CHECK_HEADER_ */

