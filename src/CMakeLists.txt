set(IFUP_SRCS constants.h main.cpp specialtypes.cpp specialtypes.h)
set(RESOLVE1_MANAGER_XML manager.xml)
set_source_files_properties(${RESOLVE1_MANAGER_XML} PROPERTIES INCLUDE specialtypes.h
                                                               CLASSNAME Resolve1Manager)
qt_add_dbus_interface(IFUP_SRCS ${RESOLVE1_MANAGER_XML} resolve1_interface)
ecm_qt_declare_logging_category(
  IFUP_SRCS
  HEADER
  generated/ifupdebug.h
  IDENTIFIER
  "LOG_IFUP_SYSTEMD_RESOLVED"
  CATEGORY_NAME
  "sh.tat.${CMAKE_PROJECT_NAME}")
add_definitions(
  -DQT_NO_CAST_FROM_ASCII
  -DQT_NO_CAST_FROM_BYTEARRAY
  -DQT_NO_CAST_TO_ASCII
  -DQT_NO_SIGNALS_SLOTS_KEYWORDS
  -DQT_NO_URL_CAST_FROM_STRING
  -DQT_STRICT_ITERATORS
  -DQT_USE_FAST_OPERATOR_PLUS
  -DQT_USE_QSTRINGBUILDER
  -DVERSION=\"${CMAKE_PROJECT_VERSION}\")
if(CMAKE_BUILD_TYPE STREQUAL Debug)
  if(CMAKE_CXX_COMPILER_ID STREQUAL GNU OR CMAKE_CXX_COMPILER_ID STREQUAL Clang)
    add_compile_options(-ggdb -Wall -Werror -Wextra -Wno-unknown-pragmas)
  endif()
endif()
include_directories(. ${CMAKE_CURRENT_BINARY_DIR}/generated ${CMAKE_CURRENT_BINARY_DIR})
add_executable(${CMAKE_PROJECT_NAME} ${IFUP_SRCS}
                                     ${CMAKE_CURRENT_BINARY_DIR}/generated/ifupdebug.cpp)
target_link_libraries(${CMAKE_PROJECT_NAME} Qt5::DBus Qt5::Network)
