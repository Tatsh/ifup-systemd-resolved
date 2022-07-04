cmake_minimum_required(VERSION 3.23)
project(ifup-systemd-resolved VERSION 0.0.1)
# Qt variables
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
# C++ variables
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# Packages
find_package(ECM 5.95.0 NO_MODULE REQUIRED)
find_package(
  Qt5
  COMPONENTS DBus Network
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
