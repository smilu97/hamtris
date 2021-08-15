cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_STANDARD 14)

project(hamtris)

file(GLOB_RECURSE gui_sources
    common/*.cpp
    common/server/*.cpp
    gui/*.cpp
)

file(GLOB_RECURSE cui_sources
    common/*.cpp
    common/server/*.cpp
    cui/*.cpp
)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(Boost REQUIRED)
find_package(PNG REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})

add_executable(hamtris ${gui_sources})
add_executable(c-hamtris ${cui_sources})

target_include_directories(hamtris
    PUBLIC ./gui
    PUBLIC ./common
    PUBLIC ./common/server
)
target_include_directories(c-hamtris
    PUBLIC ./cui
    PUBLIC ./common
    PUBLIC ./common/server
)

target_link_libraries(hamtris glut GL GLU boost_system png)
target_link_libraries(c-hamtris boost_system)
