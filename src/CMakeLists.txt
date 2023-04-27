
set(thesey_src
    core/thesey.cpp
    pgpx/frontend.cpp
    pgpx/backend.cpp
    main.cpp
)

include_directories("${PROJECT_SOURCE_DIR}/src/include")

add_executable("thesey" ${thesey_src})