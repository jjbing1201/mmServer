#ifndef _TIMER_OF_GLOBAL_H_
#define _TIMER_OF_GLOBAL_H_

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <signal.h>

class GTIMER
{
private:
    enum {REAL=0, VIRTUAL, PROF} module;

protected:
    struct itimerval itv;

public:
    GTIMER();
    virtual ~GTIMER();

    struct itimerval* get_itmer(void);

    int set_timer(int start_pointer, int interval_pointer);

    int get_timer(void);
};

#endif /* _TIMER_OF_GLOBAL_H_ */
