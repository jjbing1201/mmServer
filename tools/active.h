#ifndef _ACTIVE_HEADER_H_
#define _ACTIVE_HEADER_H_

#include "include_tools.h"

#include "child.h"

class ACTIVE_OP : public CHILD_THREAD
{
private:
    int global_start;
    int global_interval;

protected:
    int* get_global_start(void) { return &global_start; }
    int* get_global_interval(void) { return &global_interval; }

//protected:
//    void _child_thread(int);

public:
    ACTIVE_OP(int _start=DEFAULT_START_SECONDS, \
              int _interval=DEFAULT_INTER_SECONDS) : \
              global_start(_start), global_interval(_interval) {}
    virtual ~ACTIVE_OP() {}

    void ac_start(void);
};

#endif /* _ACTIVE_HEADER_H_ */

