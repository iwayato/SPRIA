cmake_minimum_required(VERSION 3.8.0)

project(Client)

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

add_subdirectory(../dlib dlib_build)

add_executable(Client Client.cpp)

target_link_libraries(Client ${OpenCV_LIBS})

target_link_libraries(Client dlib::dlib)