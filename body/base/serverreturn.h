#ifndef _SERVERRETURN_HEADER_H_
#define _SERVERRETURN_HEADER_H_

#include "include_base.h"

class SERVERRETURN
{
public:
    SERVERRETURN() {}
    virtual ~SERVERRETURN() {}

    virtual std::map<std::string, std::string> serverreturn_inherit(\
                            std::string interface, \
                            std::map<std::string, std::string> data) = 0;
};

#endif /* _SERVERRETURN_HEADER_H_ */

