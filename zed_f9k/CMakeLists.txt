cmake_minimum_required(VERSION 2.8.3)
project(zed_f9k)
set(NODE_NAME "zed_f9k_node" CACHE STRING "Name of the node")
## 添加C++11支持
add_compile_options(-std=c++11)

## 寻找系统中的ROS包和catkin库
find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  sensor_msgs
  geometry_msgs
  zed_f9k_msg
)

## 定义catkin包
catkin_package(
  CATKIN_DEPENDS roscpp rospy std_msgs sensor_msgs geometry_msgs zed_f9k_msg
)

## 包含ROS头文件和catkin头文件
include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

## 定义一个可执行文件
add_executable(${NODE_NAME} app/zed_f9k.cpp)

## 链接所需的库
target_link_libraries(${NODE_NAME}
  ${catkin_LIBRARIES}
)

