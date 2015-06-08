#ifndef _SINGLE_TON_H_
#define _SINGLE_TON_H_

#include <iostream>
#include <string.h>
#include <stdlib.h>

template <typename T>
class SINGLETON
{
private:
    static T *instance_;

    static void init()
    {
        if (instance_ == 0)
        {
            instance_ = new T;
            atexit(Destroy);
        }
    }

    static void Destroy()
    {
        delete instance_;
    }

    SINGLETON(const SINGLETON &other);
    SINGLETON &operator=(const SINGLETON &other);
    SINGLETON();
    virtual ~SINGLETON();

public:
    static T &GetInstance()
    {
        init();
        return *instance_;
    }
};

template <typename T>
T *SINGLETON<T>::instance_ = NULL;

#endif /* _SINGLE_TON_H_ */

