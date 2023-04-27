cmake_minimum_required(VERSION 3.12)
project(thesey)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH}
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

set(CMAKE_CXX_STANDARD 17)

set(TH_VERSION_GIT $ENV{VERSION})
if ("${TH_VERSION_GIT}" STREQUAL "")
    execute_process(COMMAND git rev-parse --short HEAD
                    OUTPUT_VARIABLE TH_VERSION_GIT
                    RESULT_VARIABLE TH_VERSION_GIT_RESULT
                    OUTPUT_STRIP_TRAILING_WHITESPACE
                    ERROR_QUIET)

    if(NOT "${TH_VERSION_GIT_RESULT}" STREQUAL "0")
        add_definitions(-DTH_VERSION_GIT="unknown")
    else()
        add_definitions(-DTH_VERSION_GIT="${TH_VERSION_GIT}")
    endif()
else()
    add_definitions(-DTH_VERSION_GIT="${TH_VERSION_GIT}")
endif()

if ("${CMAKE_BUILD_TYPE}" STREQUAL "")
        set(CMAKE_BUILD_TYPE "Debug")
endif()

if ("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
        set(CMAKE_C_FLAGS "-std=${CLANGCOMPILERSTANDART} -pedantic -Wall -Wextra -Wstrict-aliasing -g -O2 -pthread -D_GNU_SOURCE")
        set(OD_DEVEL_LVL -1)
elseif("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
        set(CMAKE_C_FLAGS "-std=${CLANGCOMPILERSTANDART} -pedantic -Wall -Wextra -Wstrict-aliasing -g -O0 -pthread -D_GNU_SOURCE")
        set(OD_DEVEL_LVL 1)
elseif("${CMAKE_BUILD_TYPE}" STREQUAL "ASAN")
        set(CMAKE_C_FLAGS "-std=${CLANGCOMPILERSTANDART} -g -fsanitize=address,undefined -fno-sanitize-recover=all -pedantic -Wall -Wextra -Wstrict-aliasing -g -O0 -pthread -D_GNU_SOURCE")
elseif("${CMAKE_BUILD_TYPE}" STREQUAL "TSAN")
        set(CMAKE_C_FLAGS "-std=${CLANGCOMPILERSTANDART} -g -fsanitize=thread -fno-sanitize-recover=all -pedantic -Wall -Wextra -Wstrict-aliasing -g -O0 -pthread -D_GNU_SOURCE")
endif()

# find_package(Threads REQUIRED)
include (FindPackageHandleStandardArgs)
find_package(PostgreSQL REQUIRED)

set(CMAKE_THREAD_LIBS_INIT "-lpthread")
set(CMAKE_CXX_FLAGS -pthread)

set(thesey_binary ${CMAKE_PROJECT_NAME})

add_subdirectory(src)


message(STATUS "                                                                          ")
message(STATUS "CMAKE_BUILD_TYPE:       ${CMAKE_BUILD_TYPE}")
message(STATUS "POSTGRESQL_INCLUDE_DIR: ${POSTGRESQL_INCLUDE_DIR}")
message(STATUS "POSTGRESQL_LIBRARY:     ${POSTGRESQL_LIBRARY}")
message(STATUS "POSTGRESQL_LIBPGPORT:   ${POSTGRESQL_LIBPGPORT}")
message(STATUS "PG_VERSION_NUM:         ${PG_VERSION_NUM}")
message(STATUS "PQ_LIBRARY:             ${PQ_LIBRARY}")