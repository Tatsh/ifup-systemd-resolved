cmake_minimum_required(VERSION 3.31)
project(ifup-systemd-resolved VERSION 0.0.1)

option(BUILD_DOCS "Build documentation." OFF)

if(BUILD_DOCS)
  find_package(Doxygen REQUIRED)
  set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${DOXYGEN_OUT} @ONLY)
  add_custom_target(
    doc ALL
    COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
  install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/docs/html
          DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/doc/ifup-systemd-resolved-${version})
endif()

# Qt variables
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
# C++ variables
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# Packages
find_package(ECM NO_MODULE REQUIRED)
find_package(
  Qt6
  COMPONENTS DBus Network CONFIG
  REQUIRED)
# Feature summary
include(FeatureSummary)
feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)
# ECM includes
list(APPEND CMAKE_MODULE_PATH ${ECM_MODULE_PATH})
include(ECMQtDeclareLoggingCategory)
include(KDEInstallDirs)
# Sources and targets
add_subdirectory(src)
# Installation
include(GNUInstallDirs)
install(TARGETS ${CMAKE_PROJECT_NAME})
include(CPack)
