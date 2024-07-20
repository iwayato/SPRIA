cmake_minimum_required(VERSION 3.8.0)

project(FaceFeatureExtractionModule)

add_subdirectory(../dlib dlib_build)

macro(add_example name)
   add_executable(${name} ${name}.cpp)
   target_link_libraries(${name} dlib::dlib )

   if(${CMAKE_VERSION} VERSION_GREATER_EQUAL "3.13.0") 
       target_link_options(${name} PRIVATE $<$<CONFIG:RELEASE>:-s>)
   endif()
endmacro()

macro(add_gui_example name)
   if (DLIB_NO_GUI_SUPPORT)
      message("No GUI support, so we won't build the ${name} example.")
   else()
      add_example(${name})
   endif()
endmacro()

add_gui_example(FaceFeatureExtractionModule)