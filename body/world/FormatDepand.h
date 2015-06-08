#ifndef _FORMAT_DEPEND_HEADER_
#define _FORMAT_DEPEND_HEADER_

#include "world_include.h"

class WORLDFORMAT_DEPAND
{
public:
    WORLDFORMAT_DEPAND() {}
    virtual ~WORLDFORMAT_DEPAND() {}

    std::map<std::string, std::string> normal_format(\
                                std::map<std::string, std::string> data);

};

#endif /* _FORMAT_DEPEND_HEADER_ */
 
