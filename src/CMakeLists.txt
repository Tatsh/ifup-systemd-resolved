include_directories(. ${CMAKE_CURRENT_BINARY_DIR}/generated ${CMAKE_CURRENT_BINARY_DIR})

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

add_library(libifup STATIC ${LIBIFUP_SRCS} ${CMAKE_CURRENT_BINARY_DIR}/generated/ifupdebug.cpp)
target_link_libraries(libifup PRIVATE Qt6::DBus Qt6::Network)

add_executable(${CMAKE_PROJECT_NAME} main.cpp)
if(CMAKE_BUILD_TYPE STREQUAL Debug AND (CMAKE_CXX_COMPILER_ID STREQUAL GNU OR CMAKE_CXX_COMPILER_ID
                                                                              STREQUAL Clang))
  target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE -ggdb -Wall -Werror -Wextra
                                                       -Wno-unknown-pragmas)
endif()
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE libifup Qt6::DBus Qt6::Network)

if(BUILD_TESTS)
  enable_testing()
  include(FetchContent)
  FetchContent_Declare(googletest
                       URL https://github.com/google/googletest/archive/refs/tags/v1.17.0.zip)
  FetchContent_MakeAvailable(googletest)
  add_executable(${CMAKE_PROJECT_NAME}-tests test.cpp)
  target_compile_options(${CMAKE_PROJECT_NAME}-tests PRIVATE -ggdb -Wall -Werror -Wextra
                                                             -Wno-unknown-pragmas)
  if(CMAKE_COMPILER_IS_GNUCXX)
    target_compile_options(${CMAKE_PROJECT_NAME}-tests PRIVATE --coverage)
  endif()
  target_link_libraries(${CMAKE_PROJECT_NAME}-tests PRIVATE libifup Qt6::DBus Qt6::Network
                                                            GTest::gtest_main GTest::gmock gcov)
  include(GoogleTest)
  gtest_discover_tests(${CMAKE_PROJECT_NAME}-tests)
endif()
