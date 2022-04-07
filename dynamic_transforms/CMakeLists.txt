cmake_minimum_required(VERSION 2.8.3)
project(calibration)

add_definitions(-std=c++11)

set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${CMAKE_CURRENT_SOURCE_DIR}/cmake")

find_package(catkin REQUIRED COMPONENTS
  nav_msgs
  geometry_msgs
  roscpp
  rospy
  std_msgs
  sensor_msgs
  tf
  tf2
  dynamic_reconfigure
)

include_directories(
  ${catkin_INCLUDE_DIRS}
)

catkin_python_setup()

generate_dynamic_reconfigure_options(
  cfg/Transform.cfg
)

catkin_package()

catkin_package(
 INCLUDE_DIRS include
 LIBRARIES genicam arghandler
 CATKIN_DEPENDS roscpp rospy std_msgs nav_msgs tf tf2 dynamic_reconfigure
# DEPENDS system_lib
)

include_directories(
  ${catkin_INCLUDE_DIRS}
  include
)

add_executable(dynamic_transform_publisher src/dynamic_transform_publisher_node.cpp)

target_link_libraries(dynamic_transform_publisher
  ${catkin_LIBRARIES}
)

add_executable(odom_to_tf src/odom_to_tf.cpp)

target_link_libraries(odom_to_tf
  ${catkin_LIBRARIES}
)

add_dependencies(dynamic_transform_publisher ${PROJECT_NAME}_gencfg)
