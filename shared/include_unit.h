#ifndef _UTIL_INCLUDE_HEADER_
#define _UTIL_INCLUDE_HEADER_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

typedef signed int int32;
typedef unsigned int uint32;
typedef unsigned long ulong64;

#define ZLIB_MAX 1024
#define LEVEL_HIGHEST   10
#define LEVEL_NORMAL    0
#define LEVEL_LOWEST    80
#define INTERVAL_LOOP_MUTEX_TIMES           10
#define INTERVAL_LOOP_MUTEX_MILLISECONDS    5000

#define _STRINGIZE(x) #x
#define CONCAT(x, y) CONCAT1(x, y)
#define CONCAT1(x, y) x##y

#endif /* _UTIL_INCLUDE_HEADER_ */

