add_library(hand_pose SHARED hand_pose.cpp)
target_include_directories(hand_pose PUBLIC  ${PROJECT_SOURCE_DIR}/Pose)

# add_executable(hand_demo hand_demo.cpp)
# target_link_libraries(hand_demo hand_pose)
# target_link_libraries(hand_demo hand_pose)


add_example(hand_demo)