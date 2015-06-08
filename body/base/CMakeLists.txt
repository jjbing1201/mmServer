project(Server)

set(sources
    check.cpp
    format.cpp
)

set(headers
    Method.h
    check.h
    format.h
    include_base.h
    operation.h
    serverreturn.h
)

INCLUDE_DIRECTORIES(
    /usr/local/include
)

set(WORLD_BASE_LIB_SRCS ${sources} ${headers})
add_library(base SHARED ${WORLD_BASE_LIB_SRCS})
