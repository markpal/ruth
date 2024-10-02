cmake_minimum_required(VERSION 3.29)
project(untitled1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")


add_executable(untitled1 main.cpp)

find_package(OpenMP REQUIRED)

if(OpenMP_CXX_FOUND)
    target_link_libraries(untitled1 PUBLIC OpenMP::OpenMP_CXX)
endif()

