include_directories(. ${CMAKE_CURRENT_BINARY_DIR}/generated ${CMAKE_CURRENT_BINARY_DIR})

if(CMAKE_BUILD_TYPE STREQUAL Debug AND (CMAKE_CXX_COMPILER_ID STREQUAL GNU OR CMAKE_CXX_COMPILER_ID
                                                                              STREQUAL Clang))
  set(DEBUG_FLAGS -ggdb -Wall -Werror -Wextra -Wno-unknown-pragmas)
endif()
set(QT_DEPS Qt6::DBus Qt6::Network)

set(LIBIFUP_SRCS specialtypes.cpp specialtypes.h up.cpp up.h)

set(RESOLVE1_MANAGER_XML manager.xml)
set_source_files_properties(${RESOLVE1_MANAGER_XML} PROPERTIES INCLUDE specialtypes.h
                                                               CLASSNAME Resolve1Manager)
qt_add_dbus_interface(LIBIFUP_SRCS ${RESOLVE1_MANAGER_XML} resolve1_interface)

ecm_qt_declare_logging_category(
  LIBIFUP_SRCS
  HEADER
  generated/ifupdebug.h
  IDENTIFIER
  "LOG_IFUP_SYSTEMD_RESOLVED"
  CATEGORY_NAME
  "sh.tat.${CMAKE_PROJECT_NAME}")

add_library(ifup STATIC ${LIBIFUP_SRCS} ${CMAKE_CURRENT_BINARY_DIR}/generated/ifupdebug.cpp)
target_compile_options(ifup PRIVATE ${DEBUG_FLAGS})
target_link_libraries(ifup PRIVATE ${QT_DEPS})

add_executable(${CMAKE_PROJECT_NAME} main.cpp)
target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE ${DEBUG_FLAGS})
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE ifup ${QT_DEPS})

if(BUILD_TESTS)
  enable_testing()
  include(FetchContent)
  FetchContent_Declare(googletest
                       URL https://github.com/google/googletest/archive/refs/tags/v1.17.0.zip)
  FetchContent_MakeAvailable(googletest)
  add_executable(${CMAKE_PROJECT_NAME}-tests test.cpp)
  target_compile_options(${CMAKE_PROJECT_NAME}-tests PRIVATE ${DEBUG_FLAGS})
  if(CMAKE_COMPILER_IS_GNUCXX)
    target_compile_options(${CMAKE_PROJECT_NAME}-tests PRIVATE --coverage)
  endif()
  target_link_libraries(${CMAKE_PROJECT_NAME}-tests PRIVATE ifup ${QT_DEPS} GTest::gtest_main
                                                            GTest::gmock gcov)
  include(GoogleTest)
  gtest_discover_tests(${CMAKE_PROJECT_NAME}-tests)
endif()
