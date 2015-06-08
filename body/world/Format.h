#ifndef _WORLD_FORMAT_HEADER_H_
#define _WORLD_FORMAT_HEADER_H_

#include "FormatDepand.h"
#include "world_include.h"

namespace N_WORLD
{
    class WORLDFORMAT : public FORMAT
    {
    protected:
        std::map<std::string, std::string> normal_format_inside(std::string interfaceName,  std::map<std::string, std::string> data);

    public:
        WORLDFORMAT() {}
        virtual ~WORLDFORMAT() {}

        std::map<std::string, std::string> format_inter(\
                                   std::string interface, \
                                   std::map<std::string, std::string> data);
    
        std::map<std::string, std::string> format_inter_inherit(\
                                   std::string interface, \
                                   std::map<std::string, std::string> data);
    };
};

#endif /* _WORLD_FORMAT_HEADER_H_ */

