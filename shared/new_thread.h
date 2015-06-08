#ifndef _THREAD_HEADER_H_
#define _THREAD_HEADER_H_

#include "include_unit.h"
#include "new_mutex.h"

/* static register function here. and will be friend to class N_Thread */
static void* registerfunc(void*);

class N_Thread
{
private:
    /* Thread id*/
    pthread_t handle;   

    bool started;
    bool detached;

    /* Max & Min ensure nor_priority by different algorithm */
    int max_priority;
    int min_priority;
    int nor_priority;

/* will include mutex for each thread and can be used. 
 * bool will sure this part is exist.
 * when bool is true, could use MC for mutex and condc
*/
private:
    bool has_mutex;
    N_MUTEX_CONDC* MC;

private:
    void* registerfunc_param;

/*
 * run is virtual function and only define in sub class
 * sub class when used will only use recover this run
 * then can be right here.
*/
protected:
    friend void* registerfunc(void *);
    virtual void* run(void *) = 0;

public:
    N_Thread();
    virtual ~N_Thread();

public:
    /*
     *  @brief      :  start a thread by these variables
     *  @variable   : 
     *        => bool  : join_or_detach (false for join , true for detach)  
     *        => void* : param          (recover user used here)
     *        => bool  : mutex_has      (false for no, true for has)
     *        => int   : SCHED Method   (default for SCHED_OTHER, other will
     *                                   define as sched.h)
     *        => int   : user define thread level
     *                   (default for do as calculation, user can choose
                         from thread_inc.h like LEVEL_*)
     *                   
    */
    int start(bool =false, void* =NULL, bool =false, \
              int =SCHED_OTHER, int =LEVEL_NORMAL);

    void  stop();
    /*
     *  @brief      :  sleep for main process
     *  @variable   : 
     *        => uint32 : sleep for milliseconds 1000(millis):1(second)
    */
    void  sleep(uint32);
    void  detach();
    void* wait();

    pthread_t* get_thread_id(void);

    /*
     *  @brief      :  get mutex id 
     *  @return     :  over 0 is right, -1 for no mutex
    */
    ulong64* get_mutex_id(void);
};

#endif /* _THREAD_HEADER_H_ */
