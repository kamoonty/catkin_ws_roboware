# Install script for directory: /home/kanin/catkin_ws_roboware/src/ros_controllers/rqt_joint_trajectory_controller

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/kanin/catkin_ws_roboware/install")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  include("/home/kanin/catkin_ws_roboware/build/ros_controllers/rqt_joint_trajectory_controller/catkin_generated/safe_execute_install.cmake")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/home/kanin/catkin_ws_roboware/build/ros_controllers/rqt_joint_trajectory_controller/catkin_generated/installspace/rqt_joint_trajectory_controller.pc")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/rqt_joint_trajectory_controller/cmake" TYPE FILE FILES
    "/home/kanin/catkin_ws_roboware/build/ros_controllers/rqt_joint_trajectory_controller/catkin_generated/installspace/rqt_joint_trajectory_controllerConfig.cmake"
    "/home/kanin/catkin_ws_roboware/build/ros_controllers/rqt_joint_trajectory_controller/catkin_generated/installspace/rqt_joint_trajectory_controllerConfig-version.cmake"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/rqt_joint_trajectory_controller" TYPE FILE FILES "/home/kanin/catkin_ws_roboware/src/ros_controllers/rqt_joint_trajectory_controller/package.xml")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/rqt_joint_trajectory_controller" TYPE FILE FILES "/home/kanin/catkin_ws_roboware/src/ros_controllers/rqt_joint_trajectory_controller/plugin.xml")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/rqt_joint_trajectory_controller" TYPE DIRECTORY FILES "/home/kanin/catkin_ws_roboware/src/ros_controllers/rqt_joint_trajectory_controller/resource")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/rqt_joint_trajectory_controller" TYPE PROGRAM FILES "/home/kanin/catkin_ws_roboware/src/ros_controllers/rqt_joint_trajectory_controller/scripts/rqt_joint_trajectory_controller")
endif()

