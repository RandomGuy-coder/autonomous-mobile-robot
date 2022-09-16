cmake_minimum_required(VERSION 3.0.2)
project(mapping)

## Compile as C++11, supported in ROS Kinetic and newer
add_compile_options(-std=c++11)
find_package(Qt5 COMPONENTS Core REQUIRED)
find_package(catkin REQUIRED COMPONENTS roscpp rospy std_msgs genmsg find_object_2d)

catkin_package(
  CATKIN_DEPENDS
  find_object_2d
)


include_directories(${catkin_INCLUDE_DIRS})

add_executable(rotate_camera src/rotatecamera.cpp)

target_link_libraries(rotate_camera ${catkin_LIBRARIES})

add_executable(object_detect src/object_recognition.cpp)
target_link_libraries(object_detect ${catkin_LIBRARIES})
target_link_libraries(object_detect Qt5::Core)
