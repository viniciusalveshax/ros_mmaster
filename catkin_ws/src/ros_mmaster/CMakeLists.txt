cmake_minimum_required(VERSION 2.8.3)
project(ros_mmaster)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  message_generation
)

add_message_files(
  FILES
  Msg.msg
)

add_service_files(
  FILES
  Srv.srv
)

generate_messages(
  DEPENDENCIES
  std_msgs
)

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES ros_mmaster
  CATKIN_DEPENDS roscpp std_msgs message_runtime
#  DEPENDS system_lib
)

include_directories(
  ${catkin_INCLUDE_DIRS}
)

## Declare a cpp library
# add_library(ros_mmaster
#   src/${PROJECT_NAME}/ros_mmaster.cpp
# )

add_executable(mmaster src/mmaster.cpp)

add_dependencies(mmaster mmaster_generate_messages_cpp)

target_link_libraries(mmaster ${catkin_LIBRARIES})
