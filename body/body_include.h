#ifndef _BODY_INCLUDE_HEADER_
#define _BODY_INCLUDE_HEADER_

#include "../shared/md5.h"
#include "../shared/util.h"
#include "../shared/gerror.h"
#include "../shared/logger.h"
#include "../shared/basicalgorithm.h"

#include "Master.h"

class Compare_int
{
public:
    Compare_int(int a, int b, int c):first(a), second(b), third(c) {}
    int first;
    int second;
    int third;
    
    bool operator < (const Compare_int &m) const
    {
        //return first > m.first;
        if (first == m.first)
        {
            return third < m.third;
        }
        else
        {
            return first > m.first;
        }
    }
};

#endif /* _BODY_INCLUDE_HEADER_ */

