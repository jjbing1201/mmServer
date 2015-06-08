#ifndef _ACCEPT_HEADER_H_
#define _ACCEPT_HEADER_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>

#include "include_tools.h"

#include "../framework/XPepoll.h"
#include "../framework/XPsocket.h"

class ACCEPT_THREAD : public N_Thread
{
protected:
    void* run(void*);

public:
    ACCEPT_THREAD() {}
    virtual ~ACCEPT_THREAD() {}
};

#endif /* _ACCEPT_HEADER_H_ */
