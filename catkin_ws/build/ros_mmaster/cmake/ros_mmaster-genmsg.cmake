# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "ros_mmaster: 1 messages, 1 services")

set(MSG_I_FLAGS "-Iros_mmaster:/home/vinicius/Dropbox/arv/projetos/mestradocomp/Dissertacao/mmaster_hydro/catkin_ws/src/ros_mmaster/msg;-Istd_msgs:/home/vinicius/.ros/hydro/share/std_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(genlisp REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(ros_mmaster_generate_messages ALL)

#
#  langs = gencpp;genlisp;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(ros_mmaster
  "/home/vinicius/Dropbox/arv/projetos/mestradocomp/Dissertacao/mmaster_hydro/catkin_ws/src/ros_mmaster/msg/Msg.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/ros_mmaster
)

### Generating Services
_generate_srv_cpp(ros_mmaster
  "/home/vinicius/Dropbox/arv/projetos/mestradocomp/Dissertacao/mmaster_hydro/catkin_ws/src/ros_mmaster/srv/Srv.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/ros_mmaster
)

### Generating Module File
_generate_module_cpp(ros_mmaster
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/ros_mmaster
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(ros_mmaster_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(ros_mmaster_generate_messages ros_mmaster_generate_messages_cpp)

# target for backward compatibility
add_custom_target(ros_mmaster_gencpp)
add_dependencies(ros_mmaster_gencpp ros_mmaster_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS ros_mmaster_generate_messages_cpp)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(ros_mmaster
  "/home/vinicius/Dropbox/arv/projetos/mestradocomp/Dissertacao/mmaster_hydro/catkin_ws/src/ros_mmaster/msg/Msg.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/ros_mmaster
)

### Generating Services
_generate_srv_lisp(ros_mmaster
  "/home/vinicius/Dropbox/arv/projetos/mestradocomp/Dissertacao/mmaster_hydro/catkin_ws/src/ros_mmaster/srv/Srv.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/ros_mmaster
)

### Generating Module File
_generate_module_lisp(ros_mmaster
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/ros_mmaster
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(ros_mmaster_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(ros_mmaster_generate_messages ros_mmaster_generate_messages_lisp)

# target for backward compatibility
add_custom_target(ros_mmaster_genlisp)
add_dependencies(ros_mmaster_genlisp ros_mmaster_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS ros_mmaster_generate_messages_lisp)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(ros_mmaster
  "/home/vinicius/Dropbox/arv/projetos/mestradocomp/Dissertacao/mmaster_hydro/catkin_ws/src/ros_mmaster/msg/Msg.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/ros_mmaster
)

### Generating Services
_generate_srv_py(ros_mmaster
  "/home/vinicius/Dropbox/arv/projetos/mestradocomp/Dissertacao/mmaster_hydro/catkin_ws/src/ros_mmaster/srv/Srv.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/ros_mmaster
)

### Generating Module File
_generate_module_py(ros_mmaster
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/ros_mmaster
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(ros_mmaster_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(ros_mmaster_generate_messages ros_mmaster_generate_messages_py)

# target for backward compatibility
add_custom_target(ros_mmaster_genpy)
add_dependencies(ros_mmaster_genpy ros_mmaster_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS ros_mmaster_generate_messages_py)


debug_message(2 "ros_mmaster: Iflags=${MSG_I_FLAGS}")


if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/ros_mmaster)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/ros_mmaster
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
add_dependencies(ros_mmaster_generate_messages_cpp std_msgs_generate_messages_cpp)

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/ros_mmaster)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/ros_mmaster
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
add_dependencies(ros_mmaster_generate_messages_lisp std_msgs_generate_messages_lisp)

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/ros_mmaster)
  install(CODE "execute_process(COMMAND \"/usr/bin/python\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/ros_mmaster\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/ros_mmaster
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
add_dependencies(ros_mmaster_generate_messages_py std_msgs_generate_messages_py)
