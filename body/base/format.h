#ifndef _RETURN_FORMAT_HEADER_H_
#define _RETURN_FORMAT_HEADER_H_

#include "include_base.h"

class FORMAT : public ErrorBase
{
public:
    FORMAT( int _outside=DEFAULT_FORMAT_OUTSIDE, \
            int _inside=DEFAULT_FORMAT_INSIDE) : \
            has_outside_format(_outside), \
            has_inside_format(_inside) {}
    virtual ~FORMAT() {}

    int* get_outside_format(void) { return &has_outside_format; }
    int* get_inside_format(void) { return &has_inside_format; }

    std::map<std::string, std::string> normal_format_outside(\
                                std::map<std::string, std::string> data);

    virtual std::map<std::string, std::string> normal_format_inside(std::string interfaceName, std::map<std::string, std::string> data) = 0;

private:
    int has_outside_format;
    int has_inside_format;
};

#endif /* _RETURN_FORMAT_HEADER_H_ */

