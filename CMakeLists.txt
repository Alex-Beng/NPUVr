cmake_minimum_required(VERSION 3.1)
project(npuvr LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package( OpenCV REQUIRED )

find_package(mynteye REQUIRED)
message(STATUS "Use mynteye ${mynteye_VERSION}")

if(mynteye_WITH_OPENCV)
  add_definitions(-DWITH_OPENCV)
endif()

MACRO(add_example name)
  ADD_EXECUTABLE(${name} ${name}.cpp)
  TARGET_LINK_LIBRARIES(${name} ${OpenCV_LIBS})
  TARGET_LINK_LIBRARIES(${name} mynteye)
  TARGET_LINK_LIBRARIES(${name} hand_pose)
ENDMACRO()

add_subdirectory(Stereo)
add_subdirectory(Pose)

