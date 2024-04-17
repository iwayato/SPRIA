cmake_minimum_required(VERSION 3.8.0)

project(FaceRecognitionModule)

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

include(FindPkgConfig)
pkg_check_modules(CURLPP REQUIRED curlpp)

add_subdirectory(base64)

add_executable(FaceRecognition FaceRecognitionModule.cpp)

target_link_libraries(FaceRecognition base64)
target_link_libraries(FaceRecognition ${CURLPP_LDFLAGS})
target_link_libraries(FaceRecognition ${OpenCV_LIBS})
