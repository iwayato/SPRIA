cmake_minimum_required(VERSION 3.8.0)

project(FaceDetectionModule)

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

add_subdirectory(../dlib dlib_build)

add_executable(FaceDetectionModule FaceDetectionModule.cpp)

target_link_libraries(FaceDetectionModule ${OpenCV_LIBS})

target_link_libraries(FaceDetectionModule dlib::dlib)