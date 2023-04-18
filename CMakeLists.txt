cmake_minimum_required(VERSION 3.12)
project(thesey)

set(CMAKE_CXX_STANDARD 17)

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

set(thesey_binary ${CMAKE_PROJECT_NAME})

add_subdirectory(src)
