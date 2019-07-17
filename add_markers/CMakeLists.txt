cmake_minimum_required(VERSION 2.8.3)
project(add_markers)

## Find catkin macros and libraries
find_package(catkin REQUIRED COMPONENTS
  visualization_msgs
  roscpp
)
catkin_package(CATKIN_DEPENDS)
###########
## Build ##
###########
include_directories(${catkin_INCLUDE_DIRS})
add_executable(add_markers src/add_markers.cpp)
target_link_libraries(add_markers ${catkin_LIBRARIES})

