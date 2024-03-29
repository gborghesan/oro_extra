#
# The find_package macro for Orocos-RTT works best with
# cmake >= 2.6.3
#
cmake_minimum_required(VERSION 2.6.3)

#
# This creates a standard cmake project. You may extend this file with
# any cmake macro you see fit.
#
project(oro_extra)

add_definitions(-std=c++11 -fPIC)


find_package(catkin REQUIRED cmake_modules )
find_package(catkin REQUIRED COMPONENTS roscpp roslib)


# Use 'source orocos_toolchain/env.sh' if the command below fails:
find_package(OROCOS-RTT QUIET)
if (NOT OROCOS-RTT_FOUND)
  message (FATAL_ERROR "\nCould not find Orocos. Please use the shell command\n 'source orocos_toolchain/env.sh' and then run cmake again.")
endif()

# Defines the orocos_* cmake macros. See that file for additional
# documentation.
include( ${OROCOS-RTT_USE_FILE_PATH}/UseOROCOS-RTT.cmake )

# Rest of the configuration is in src/
include_directories(
                include
)


#
# Generates and installs our package. Must be the last statement such
# that it can pick up all above settings.
#


# for seeing files in qtcreator
file(GLOB_RECURSE EXTRA_FILES
    package.xml
    *.ops
    *.lua
    *.py
	include/oro_extra/*
    *.md
    *.launch)
add_custom_target(${PROJECT_NAME}_OTHER_FILES  ${PROJECT_SOURCE_DIR} SOURCES ${EXTRA_FILES})
# end qtcreator

add_subdirectory(test)
add_subdirectory(src-cmp)
add_subdirectory(src)


catkin_add_env_hooks( 20.oro_extra SHELLS sh DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/env_hooks)

orocos_generate_package(  
  INCLUDE_DIRS include
	LIBRARY rtt_period_counter
)

file(GLOB_RECURSE LUA_FILES "*.lua")
file(GLOB_RECURSE SO_FILES "*.so")
install(
  FILES ${LUA_FILES}
  DESTINATION ${CATKIN_GLOBAL_SHARE_DESTINATION}/lua/5.1/rttlua_completion/
)

install(
  TARGETS readline
  DESTINATION ${CATKIN_GLOBAL_SHARE_DESTINATION}/lua/5.1/rttlua_completion/
)


