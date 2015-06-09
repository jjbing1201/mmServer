project(Server)

set(sources
    base.cpp
    basedata.cpp
    bottom.cpp
    users.cpp
    interfaceusing.cpp
    verifycode.cpp
    messagelist.cpp
    helpmain.cpp
)

set(headers
    include_db.h
    base.h
    basedata.h
    bottom.h
    users.h
    interfaceusing.h
    verifycode.h
    messagelist.h
    helpmain.h
)

include_directories(
    /usr/local/include
)

set(DB_WORLD_LIB_SRCS ${sources} ${headers})
add_library(database SHARED ${DB_WORLD_LIB_SRCS})
