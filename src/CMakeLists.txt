set(IFUP_SRCS main.cpp specialtypes.cpp specialtypes.h up.cpp up.h)
set(IFUP_TESTS_SRC specialtypes.cpp specialtypes.h test.cpp up.cpp up.h)
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
include_directories(. ${CMAKE_CURRENT_BINARY_DIR}/generated ${CMAKE_CURRENT_BINARY_DIR})
add_executable(${CMAKE_PROJECT_NAME} ${IFUP_SRCS}
                                     ${CMAKE_CURRENT_BINARY_DIR}/generated/ifupdebug.cpp)
if(CMAKE_BUILD_TYPE STREQUAL Debug)
  if(CMAKE_CXX_COMPILER_ID STREQUAL GNU OR CMAKE_CXX_COMPILER_ID STREQUAL Clang)
    target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE -ggdb -Wall -Werror -Wextra
                                                         -Wno-unknown-pragmas)
  endif()
endif()
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE Qt6::DBus Qt6::Network)

if(BUILD_TESTS)
  enable_testing()
  qt_add_dbus_interface(IFUP_TESTS_SRC ${RESOLVE1_MANAGER_XML} resolve1_interface)
  ecm_qt_declare_logging_category(
    IFUP_TESTS_SRC
    HEADER
    generated/ifupdebug.h
    IDENTIFIER
    "LOG_IFUP_SYSTEMD_RESOLVED"
    CATEGORY_NAME
    "sh.tat.${CMAKE_PROJECT_NAME}")
  include(FetchContent)
  FetchContent_Declare(googletest
                       URL https://github.com/google/googletest/archive/refs/tags/v1.17.0.zip)
  FetchContent_MakeAvailable(googletest)
  add_executable(${CMAKE_PROJECT_NAME}-tests ${IFUP_TESTS_SRC})
  target_compile_options(${CMAKE_PROJECT_NAME}-tests PRIVATE -ggdb -Wall -Werror -Wextra
                                                             -Wno-unknown-pragmas --coverage)
  if(CMAKE_COMPILER_IS_GNUCXX)
    target_compile_options(${CMAKE_PROJECT_NAME}-tests PRIVATE --coverage)
  endif()
  target_link_libraries(${CMAKE_PROJECT_NAME}-tests PRIVATE Qt6::DBus Qt6::Network
                                                            GTest::gtest_main GTest::gmock gcov)
  include(GoogleTest)
  gtest_discover_tests(${CMAKE_PROJECT_NAME}-tests)
endif()
