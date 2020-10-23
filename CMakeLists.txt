cmake_minimum_required(VERSION 3.1)
project(npuvr LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(OpenCV 3.3.1 QUIET
             COMPONENTS
             core imgcodecs videoio features2d calib3d highgui)
if(NOT OpenCV_FOUND)
    find_package(OpenCV 4.0 REQUIRED
                 COMPONENTS
                 core imgcodecs videoio features2d calib3d highgui)
    if(NOT OpenCV_FOUND)
        message(FATAL_ERROR "OpenCV >= 3.3.1 not found")
    endif()
endif()
message(STATUS "Use OpenCV ${OpenCV_VERSION}")


find_package(mynteye REQUIRED)
message(STATUS "Use mynteye ${mynteye_VERSION}")

if(mynteye_WITH_OPENCV)
  add_definitions(-DWITH_OPENCV)
endif()

add_subdirectory(Stereo)

