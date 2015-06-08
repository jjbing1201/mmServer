#ifndef _OPERATION_DLL_HEADER_H_
#define _OPERATION_DLL_HEADER_H_

#include "include_base.h"

class OPERATION
{
public:
    OPERATION() {}
    virtual ~OPERATION() {}

    virtual std::map<std::string, std::string> operation_inherit(\
                            std::string interface, \
                            std::map<std::string, std::string> data) = 0;
};

#endif /* _OPERATION_DLL_HEADER_H_ */

