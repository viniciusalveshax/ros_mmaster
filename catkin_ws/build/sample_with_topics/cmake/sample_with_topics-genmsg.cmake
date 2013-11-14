# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "sample_with_topics: 1 messages, 0 services")

set(MSG_I_FLAGS "-Isample_with_topics:/home/vinicius/Dropbox/arv/projetos/mestradocomp/Dissertacao/mmaster_hydro/catkin_ws/src/sample_with_topics/msg;-Istd_msgs:/opt/ros/hydro/share/std_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(genlisp REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(sample_with_topics_generate_messages ALL)

#
#  langs = gencpp;genlisp;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(sample_with_topics
  "/home/vinicius/Dropbox/arv/projetos/mestradocomp/Dissertacao/mmaster_hydro/catkin_ws/src/sample_with_topics/msg/Num.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/sample_with_topics
)

### Generating Services

### Generating Module File
_generate_module_cpp(sample_with_topics
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/sample_with_topics
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(sample_with_topics_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(sample_with_topics_generate_messages sample_with_topics_generate_messages_cpp)

# target for backward compatibility
add_custom_target(sample_with_topics_gencpp)
add_dependencies(sample_with_topics_gencpp sample_with_topics_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS sample_with_topics_generate_messages_cpp)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(sample_with_topics
  "/home/vinicius/Dropbox/arv/projetos/mestradocomp/Dissertacao/mmaster_hydro/catkin_ws/src/sample_with_topics/msg/Num.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/sample_with_topics
)

### Generating Services

### Generating Module File
_generate_module_lisp(sample_with_topics
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/sample_with_topics
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(sample_with_topics_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(sample_with_topics_generate_messages sample_with_topics_generate_messages_lisp)

# target for backward compatibility
add_custom_target(sample_with_topics_genlisp)
add_dependencies(sample_with_topics_genlisp sample_with_topics_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS sample_with_topics_generate_messages_lisp)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(sample_with_topics
  "/home/vinicius/Dropbox/arv/projetos/mestradocomp/Dissertacao/mmaster_hydro/catkin_ws/src/sample_with_topics/msg/Num.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/sample_with_topics
)

### Generating Services

### Generating Module File
_generate_module_py(sample_with_topics
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/sample_with_topics
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(sample_with_topics_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(sample_with_topics_generate_messages sample_with_topics_generate_messages_py)

# target for backward compatibility
add_custom_target(sample_with_topics_genpy)
add_dependencies(sample_with_topics_genpy sample_with_topics_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS sample_with_topics_generate_messages_py)


debug_message(2 "sample_with_topics: Iflags=${MSG_I_FLAGS}")


if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/sample_with_topics)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/sample_with_topics
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
add_dependencies(sample_with_topics_generate_messages_cpp std_msgs_generate_messages_cpp)

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/sample_with_topics)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/sample_with_topics
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
add_dependencies(sample_with_topics_generate_messages_lisp std_msgs_generate_messages_lisp)

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/sample_with_topics)
  install(CODE "execute_process(COMMAND \"/usr/bin/python\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/sample_with_topics\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/sample_with_topics
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
add_dependencies(sample_with_topics_generate_messages_py std_msgs_generate_messages_py)
