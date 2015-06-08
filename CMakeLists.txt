cmake_minimum_required(VERSION 2.8)
project(Server)

set(CMAKE_VERBOSE_MAKEFILE on)
set(CMAKE_CXX_FLAGS "-g")
set(CMAKE_CXX_FLAGS_DEBUG "-g3 -Wall")
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -Wall")
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

aux_source_directory(./ SRC_LIST)
aux_source_directory(./shared SHARED_SRC_LIST)
aux_source_directory(./framework FRAMEWORK_SRC_LIST)
aux_source_directory(./config CONFIG_SRC_LIST)
aux_source_directory(./tools ACTIVE_SRC_LIST)
add_subdirectory(body)

list(APPEND SRC_LIST ${SHARED_SRC_LIST})
list(APPEND SRC_LIST ${FRAMEWORK_SRC_LIST})
list(APPEND SRC_LIST ${CONFIG_SRC_LIST})
list(APPEND SRC_LIST ${ACTIVE_SRC_LIST})

include_directories(
    /usr/local/include
    /usr/include
    )

link_directories(
    ${PROJECT_SOURCE_DIR}/lib

    /usr/local/lib
    /usr/lib
    /usr/lib64

    /usr/lib64/mysql/
    )

if(${MY_BUILD_TYPE} MATCHES "debug")
    add_executable(Server_Lisi_01 ${SRC_LIST})
    target_link_libraries(Server_Lisi_01 pthread mysqlclient curl ssl z m)
else()
    add_executable(Server_Lisi_01 ${SRC_LIST})
    target_link_libraries(Server_Lisi_01 pthread mysqlclient curl ssl z m json rt
                            base world body
                            libgutil.a
                            libjson.a 
                            libbasicalgorithm.a 
                            libgmd5.a 
                            libgtimer.a 
                            libnewthread.a
                            libnewmutex.a 
                            libgcharset.a
			    libconhash.a
                            )
endif()

INSTALL(FILES ${PROJECT_SOURCE_DIR}/doc/COPYRIGHT 
              ${PROJECT_SOURCE_DIR}/doc/TODO 
              ${PROJECT_SOURCE_DIR}/doc/README
              ${PROJECT_SOURCE_DIR}/doc/AUTHORS 
              DESTINATION ${PROJECT_SOURCE_DIR})

