#ifndef _DATA_OPERATION_HEADER_H_
#define _DATA_OPERATION_HEADER_H_

#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <map>

class BASE
{
public:
    BASE();
    ~BASE();

    /* part of doing judge. */
    int doingjudge(std::string dovar);
    /* part of split using. */
    std::vector<std::string> split(const std::string &str, std::string quote);
};

#endif /* _DATA_OPERATION_HEADER_H_ */
