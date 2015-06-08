#ifndef _CHILD_HEADER_
#define _CHILD_HEADER_

#include "include_tools.h"
#include "toolfunc.h"
#include "tool_table.h"

#include "../shared/util.h"

class CHILD_THREAD : public N_Thread
{
protected:
    void* run(void *);

public:
    CHILD_THREAD() {}
    virtual ~CHILD_THREAD() {}
};

#endif /* _CHILD_HEADER_ */

