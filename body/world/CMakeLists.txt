project(Server)

set(sources
    WorldFunction.cpp
    WorldSpell.cpp
    Check.cpp
    SDepend.cpp
    Serverreturn.cpp
    ODepend.cpp
    Operation.cpp
    Format.cpp
    FormatDepand.cpp
    Main.cpp
)

set(headers
    world_include.h 
    table_include.h
    WorldSpell.h
    WorldFunction.h
    Check.h
    Format.h
    SDepend.h
    Serverreturn.h 
    ODepend.h
    Operation.h
    FormatDepand.h
    Main.h
)

include_directories(
    /usr/local/include
)

link_directories(
    ${PROJECT_SOURCE_DIR}/../base
)

set(BODY_WORLD_LIB_SRCS ${sources} ${headers})
add_library(world SHARED ${BODY_WORLD_LIB_SRCS})
target_link_libraries(world base)
