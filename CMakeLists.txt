cmake_minimum_required(VERSION 2.8.3)
project(turtlebot_walker)

## Compile as C++11, supported in ROS Kinetic and newer
add_compile_options(-std=c++11)

find_package(
    catkin REQUIRED COMPONENTS
    roscpp
    rospy
    std_msgs
    message_generation
    tf
)

# Generate added messages and services with any dependencies listed here
generate_messages(
    DEPENDENCIES
    std_msgs
)

## System dependencies are found with CMake's conventions
# find_package(Boost REQUIRED COMPONENTS system)

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES beginner_tutorials
#  CATKIN_DEPENDS roscpp rospy std_msgs
#  DEPENDS system_lib
)

include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)

add_executable(walker src/main.cpp)
target_link_libraries(walker ${catkin_LIBRARIES})
add_dependencies(walker turtlebot_walker_generate_messages_cpp)

if(CATKIN_ENABLE_TESTING)
    find_package(rostest REQUIRED)
    #add_rostest_gtest(serviceTest launch/serviceTest.test test/test.cpp)
    #target_link_libraries(serviceTest ${catkin_LIBRARIES})
endif()