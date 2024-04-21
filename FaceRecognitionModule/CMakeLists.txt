cmake_minimum_required(VERSION 3.8.0)

project(FaceRecognitionModule)

find_package(CURL REQUIRED)
# find_package(GraphQLParser REQUIRED)
# find_package(OpenCV REQUIRED)

# include_directories(${OpenCV_INCLUDE_DIRS})

add_subdirectory(base64)

add_executable(FaceRecognition FaceRecognitionModule.cpp)

target_link_libraries(FaceRecognition base64)
target_link_libraries(FaceRecognition CURL::libcurl)
# target_link_libraries(FaceRecognition GraphQLParser::GraphQLParser)
# target_link_libraries(FaceRecognition ${OpenCV_LIBS})
