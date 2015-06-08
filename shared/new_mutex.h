#ifndef _NEW_MUTEX_OF_THREAD_
#define _NEW_MUTEX_OF_THREAD_

#include "include_unit.h"

class N_MUTEX_CONDC
{
private:
    ulong64 mutexcondc_id; 
    pthread_mutex_t Mutex;
    pthread_cond_t Condc;

protected:
    void mutex_init();
    void mutex_destroy();
    void mutex_sleep(int);

public:
    N_MUTEX_CONDC();
    virtual ~N_MUTEX_CONDC();

    int Lock_mutex(int=INTERVAL_LOOP_MUTEX_TIMES,\
                   int=INTERVAL_LOOP_MUTEX_MILLISECONDS);

    int Unlock_mutex(int=INTERVAL_LOOP_MUTEX_TIMES,\
                     int=INTERVAL_LOOP_MUTEX_MILLISECONDS);

    ulong64* get_id();
};

#endif /* _NEW_MUTEX_OF_THREAD_ */

