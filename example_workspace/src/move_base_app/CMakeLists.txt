cmake_minimum_required(VERSION 2.8.3)
project(move_base_app)

find_package(catkin REQUIRED rosjava_build_tools)

catkin_android_setup(assemble${CMAKE_BUILD_TYPE})

catkin_package()