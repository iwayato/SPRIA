add_library(base64 SHARED
    base64.h
    base64.cpp)

target_include_directories(base64 PUBLIC
    ${CMAKE_CURRENT_LIST_DIR})