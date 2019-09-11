cmake_minimum_required(VERSION 3.12)
project(npp)

add_definitions(-O3)
add_definitions(-std=c++17)
add_definitions(-fconcepts )
#add_definitions(-D_GLIBCXX_DEBUG)


set(CMAKE_CXX_STANDARD 17)

include_directories(NPP)
include_directories(..)
add_subdirectory(NPP)

set(SOURCE_FILES mainNPP.cpp)
add_executable(app_NPP ${SOURCE_FILES} ../OptFrame/Scanner++/Scanner.cpp)
target_link_libraries(app_NPP npp)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(app_NPP Threads::Threads)
