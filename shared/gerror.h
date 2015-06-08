#ifndef _BASE_ERROR_HEADER_H_
#define _BASE_ERROR_HEADER_H_

#include <iostream>
#include <string.h>

class ErrorBase
{
public:
    ErrorBase() {}
    virtual ~ErrorBase() {}

    std::string format_globalerror(std::string, std::string);
};

#endif /* _BASE_ERROR_HEADER_H_ */

