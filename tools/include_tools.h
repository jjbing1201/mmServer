#ifndef _INCLUDE_TOOLS_HEADER_
#define _INCLUDE_TOOLS_HEADER_

#include <iostream>
#include <stdlib.h>
#include <unistd.h>

#include "../shared/charset.h"
#include "../shared/gtimer.h"
#include "../shared/new_thread.h"
#include "../shared/basicalgorithm.h"

#define DEFAULT_START_SECONDS   10
#define DEFAULT_INTER_SECONDS   86400*1
#define DEFAULT_SUB_THREAD_SECONDS  86400*1
#define LOOP_NEWS_CHECK 10

#define SMS_LENGTH 240
#define SMS_RETURN_LENGTH 256
#define SMS_CONTENT 1024*2

#endif /* _INCLUDE_TOOLS_HEADER_ */
