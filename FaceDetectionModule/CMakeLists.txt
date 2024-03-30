cmake_minimum_required(VERSION 3.8.0)

cmake_host_system_information(RESULT HAS_SSE QUERY HAS_SSE)
message(STATUS "HAS_SSE=${HAS_SSE}")

cmake_host_system_information(RESULT HAS_SSE2 QUERY HAS_SSE2)
message(STATUS "HAS_SSE2=${HAS_SSE2}")

cmake_host_system_information(RESULT NUMBER_OF_LOGICAL_CORES QUERY NUMBER_OF_LOGICAL_CORES)
message(STATUS "NUMBER_OF_LOGICAL_CORES=${NUMBER_OF_LOGICAL_CORES}")

cmake_host_system_information(RESULT NUMBER_OF_PHYSICAL_CORES QUERY NUMBER_OF_PHYSICAL_CORES)
message(STATUS "NUMBER_OF_PHYSICAL_CORES=${NUMBER_OF_PHYSICAL_CORES}")

cmake_host_system_information(RESULT TOTAL_PHYSICAL_MEMORY QUERY TOTAL_PHYSICAL_MEMORY)
message(STATUS "TOTAL_PHYSICAL_MEMORY=${TOTAL_PHYSICAL_MEMORY}")

project(FaceDetectionModule)

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

add_subdirectory(../dlib dlib_build)

add_executable(FaceDetectionModule FaceDetectionModule.cpp)

target_link_libraries(FaceDetectionModule ${OpenCV_LIBS})

target_link_libraries(FaceDetectionModule dlib::dlib)