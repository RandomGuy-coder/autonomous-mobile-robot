cmake_minimum_required(VERSION 3.0.2)
project(mapping)

## Compile as C++11, supported in ROS Kinetic and newer
add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS roscpp rospy std_msgs genmsg)

catkin_package(
  CATKIN_DEPENDS
)


include_directories(${catkin_INCLUDE_DIRS})

add_executable(${PROJECT_NAME}_node src/rotatecamera.cpp)


target_link_libraries(${PROJECT_NAME}_node
  ${catkin_LIBRARIES}
)


