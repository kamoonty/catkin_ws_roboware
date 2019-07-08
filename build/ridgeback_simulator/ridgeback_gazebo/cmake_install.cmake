# Install script for directory: /home/kanin/catkin_ws_roboware/src/ridgeback_simulator/ridgeback_gazebo

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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/home/kanin/catkin_ws_roboware/build/ridgeback_simulator/ridgeback_gazebo/catkin_generated/installspace/ridgeback_gazebo.pc")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ridgeback_gazebo/cmake" TYPE FILE FILES
    "/home/kanin/catkin_ws_roboware/build/ridgeback_simulator/ridgeback_gazebo/catkin_generated/installspace/ridgeback_gazeboConfig.cmake"
    "/home/kanin/catkin_ws_roboware/build/ridgeback_simulator/ridgeback_gazebo/catkin_generated/installspace/ridgeback_gazeboConfig-version.cmake"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ridgeback_gazebo" TYPE FILE FILES "/home/kanin/catkin_ws_roboware/src/ridgeback_simulator/ridgeback_gazebo/package.xml")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ridgeback_gazebo" TYPE DIRECTORY FILES
    "/home/kanin/catkin_ws_roboware/src/ridgeback_simulator/ridgeback_gazebo/launch"
    "/home/kanin/catkin_ws_roboware/src/ridgeback_simulator/ridgeback_gazebo/Media"
    "/home/kanin/catkin_ws_roboware/src/ridgeback_simulator/ridgeback_gazebo/worlds"
    )
endif()

