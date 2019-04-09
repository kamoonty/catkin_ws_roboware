# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "multi_amr_nectec: 1 messages, 0 services")

set(MSG_I_FLAGS "-Imulti_amr_nectec:/home/kanin/catkin_ws_roboware/src/multi_amr_nectec/msg;-Istd_msgs:/opt/ros/kinetic/share/std_msgs/cmake/../msg;-Igeometry_msgs:/opt/ros/kinetic/share/geometry_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(geneus REQUIRED)
find_package(genlisp REQUIRED)
find_package(gennodejs REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(multi_amr_nectec_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/kanin/catkin_ws_roboware/src/multi_amr_nectec/msg/pos_msg.msg" NAME_WE)
add_custom_target(_multi_amr_nectec_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "multi_amr_nectec" "/home/kanin/catkin_ws_roboware/src/multi_amr_nectec/msg/pos_msg.msg" "geometry_msgs/Point"
)

#
#  langs = gencpp;geneus;genlisp;gennodejs;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(multi_amr_nectec
  "/home/kanin/catkin_ws_roboware/src/multi_amr_nectec/msg/pos_msg.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/multi_amr_nectec
)

### Generating Services

### Generating Module File
_generate_module_cpp(multi_amr_nectec
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/multi_amr_nectec
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(multi_amr_nectec_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(multi_amr_nectec_generate_messages multi_amr_nectec_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/kanin/catkin_ws_roboware/src/multi_amr_nectec/msg/pos_msg.msg" NAME_WE)
add_dependencies(multi_amr_nectec_generate_messages_cpp _multi_amr_nectec_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(multi_amr_nectec_gencpp)
add_dependencies(multi_amr_nectec_gencpp multi_amr_nectec_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS multi_amr_nectec_generate_messages_cpp)

### Section generating for lang: geneus
### Generating Messages
_generate_msg_eus(multi_amr_nectec
  "/home/kanin/catkin_ws_roboware/src/multi_amr_nectec/msg/pos_msg.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/multi_amr_nectec
)

### Generating Services

### Generating Module File
_generate_module_eus(multi_amr_nectec
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/multi_amr_nectec
  "${ALL_GEN_OUTPUT_FILES_eus}"
)

add_custom_target(multi_amr_nectec_generate_messages_eus
  DEPENDS ${ALL_GEN_OUTPUT_FILES_eus}
)
add_dependencies(multi_amr_nectec_generate_messages multi_amr_nectec_generate_messages_eus)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/kanin/catkin_ws_roboware/src/multi_amr_nectec/msg/pos_msg.msg" NAME_WE)
add_dependencies(multi_amr_nectec_generate_messages_eus _multi_amr_nectec_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(multi_amr_nectec_geneus)
add_dependencies(multi_amr_nectec_geneus multi_amr_nectec_generate_messages_eus)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS multi_amr_nectec_generate_messages_eus)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(multi_amr_nectec
  "/home/kanin/catkin_ws_roboware/src/multi_amr_nectec/msg/pos_msg.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/multi_amr_nectec
)

### Generating Services

### Generating Module File
_generate_module_lisp(multi_amr_nectec
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/multi_amr_nectec
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(multi_amr_nectec_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(multi_amr_nectec_generate_messages multi_amr_nectec_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/kanin/catkin_ws_roboware/src/multi_amr_nectec/msg/pos_msg.msg" NAME_WE)
add_dependencies(multi_amr_nectec_generate_messages_lisp _multi_amr_nectec_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(multi_amr_nectec_genlisp)
add_dependencies(multi_amr_nectec_genlisp multi_amr_nectec_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS multi_amr_nectec_generate_messages_lisp)

### Section generating for lang: gennodejs
### Generating Messages
_generate_msg_nodejs(multi_amr_nectec
  "/home/kanin/catkin_ws_roboware/src/multi_amr_nectec/msg/pos_msg.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/multi_amr_nectec
)

### Generating Services

### Generating Module File
_generate_module_nodejs(multi_amr_nectec
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/multi_amr_nectec
  "${ALL_GEN_OUTPUT_FILES_nodejs}"
)

add_custom_target(multi_amr_nectec_generate_messages_nodejs
  DEPENDS ${ALL_GEN_OUTPUT_FILES_nodejs}
)
add_dependencies(multi_amr_nectec_generate_messages multi_amr_nectec_generate_messages_nodejs)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/kanin/catkin_ws_roboware/src/multi_amr_nectec/msg/pos_msg.msg" NAME_WE)
add_dependencies(multi_amr_nectec_generate_messages_nodejs _multi_amr_nectec_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(multi_amr_nectec_gennodejs)
add_dependencies(multi_amr_nectec_gennodejs multi_amr_nectec_generate_messages_nodejs)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS multi_amr_nectec_generate_messages_nodejs)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(multi_amr_nectec
  "/home/kanin/catkin_ws_roboware/src/multi_amr_nectec/msg/pos_msg.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/multi_amr_nectec
)

### Generating Services

### Generating Module File
_generate_module_py(multi_amr_nectec
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/multi_amr_nectec
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(multi_amr_nectec_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(multi_amr_nectec_generate_messages multi_amr_nectec_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/kanin/catkin_ws_roboware/src/multi_amr_nectec/msg/pos_msg.msg" NAME_WE)
add_dependencies(multi_amr_nectec_generate_messages_py _multi_amr_nectec_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(multi_amr_nectec_genpy)
add_dependencies(multi_amr_nectec_genpy multi_amr_nectec_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS multi_amr_nectec_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/multi_amr_nectec)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/multi_amr_nectec
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_cpp)
  add_dependencies(multi_amr_nectec_generate_messages_cpp std_msgs_generate_messages_cpp)
endif()
if(TARGET geometry_msgs_generate_messages_cpp)
  add_dependencies(multi_amr_nectec_generate_messages_cpp geometry_msgs_generate_messages_cpp)
endif()

if(geneus_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/multi_amr_nectec)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/multi_amr_nectec
    DESTINATION ${geneus_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_eus)
  add_dependencies(multi_amr_nectec_generate_messages_eus std_msgs_generate_messages_eus)
endif()
if(TARGET geometry_msgs_generate_messages_eus)
  add_dependencies(multi_amr_nectec_generate_messages_eus geometry_msgs_generate_messages_eus)
endif()

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/multi_amr_nectec)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/multi_amr_nectec
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_lisp)
  add_dependencies(multi_amr_nectec_generate_messages_lisp std_msgs_generate_messages_lisp)
endif()
if(TARGET geometry_msgs_generate_messages_lisp)
  add_dependencies(multi_amr_nectec_generate_messages_lisp geometry_msgs_generate_messages_lisp)
endif()

if(gennodejs_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/multi_amr_nectec)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/multi_amr_nectec
    DESTINATION ${gennodejs_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_nodejs)
  add_dependencies(multi_amr_nectec_generate_messages_nodejs std_msgs_generate_messages_nodejs)
endif()
if(TARGET geometry_msgs_generate_messages_nodejs)
  add_dependencies(multi_amr_nectec_generate_messages_nodejs geometry_msgs_generate_messages_nodejs)
endif()

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/multi_amr_nectec)
  install(CODE "execute_process(COMMAND \"/usr/bin/python\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/multi_amr_nectec\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/multi_amr_nectec
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_py)
  add_dependencies(multi_amr_nectec_generate_messages_py std_msgs_generate_messages_py)
endif()
if(TARGET geometry_msgs_generate_messages_py)
  add_dependencies(multi_amr_nectec_generate_messages_py geometry_msgs_generate_messages_py)
endif()
