cmake_minimum_required(VERSION 2.8.3)
project(zed_f9k_msg)
## 添加C++11支持
add_compile_options(-std=c++11)

## 寻找系统中的ROS包和catkin库
find_package(catkin REQUIRED COMPONENTS
  message_generation
  roscpp
  rospy
  std_msgs
)

add_message_files(
    FILES
    ZEDF9K.msg
)

# generate_messages(
#     DEPENDENCIES
#     std_msgs
# )

#执行时依赖
catkin_package(
  CATKIN_DEPENDS roscpp rospy std_msgs message_runtime
)
