#include "active.h"

static void _child_thread(int n)
{
    char* active_string = "update loop news";
    CHILD_THREAD e;
    e.start(false, (void*)active_string, SCHED_RR, false);
	e.wait();
    return;
}

void ACTIVE_OP::ac_start(void)
{
    /* <<< 1. set child part >>> */
    GTIMER gtimer_child;
    gtimer_child.set_timer(1, LOOP_NEWS_CHECK);
    signal(SIGALRM, _child_thread);

    return;
}
