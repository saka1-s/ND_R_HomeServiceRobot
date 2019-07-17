cmake_minimum_required(VERSION 2.8.3)
project(pick_objects)

## Find catkin macros and libraries
find_package(catkin REQUIRED COMPONENTS
  actionlib
  move_base_msgs
  roscpp
)
catkin_package(CATKIN_DEPENDS)
###########
## Build ##
###########
include_directories(${catkin_INCLUDE_DIRS})
add_executable(pick_objects src/pick_objects.cpp)
target_link_libraries(pick_objects ${catkin_LIBRARIES})

