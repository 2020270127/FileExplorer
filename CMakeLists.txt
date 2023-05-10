cmake_minimum_required(VERSION 3.0.0)
project(fe VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(
    fe fe.cpp
    Algorithm/fileinfo.cpp
    Algorithm/sort.cpp
    Algorithm/search.cpp
)
add_compile_options(-Wall)
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
