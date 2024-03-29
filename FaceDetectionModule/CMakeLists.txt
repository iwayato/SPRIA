cmake_minimum_required(VERSION 3.8.0)

project(FaceDetectionModule)

add_subdirectory(../dlib dlib_build)

add_executable(FaceDetectionModule FaceDetectionModule.cpp)

target_link_libraries(FaceDetectionModule dlib::dlib)