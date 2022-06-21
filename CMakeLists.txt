cmake_minimum_required(VERSION 3.23)
project(ifup-systemd-resolved VERSION 0.0.1)

include(FindPkgConfig)
include(GNUInstallDirs)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FeatureSummary)
find_package(ECM 5.95.0 NO_MODULE)
set_package_properties(
  ECM PROPERTIES
  TYPE REQUIRED
  DESCRIPTION "Extra CMake Modules."
  URL "https://commits.kde.org/extra-cmake-modules")
feature_summary(WHAT REQUIRED_PACKAGES_NOT_FOUND
                FATAL_ON_MISSING_REQUIRED_PACKAGES)
list(APPEND CMAKE_MODULE_PATH ${ECM_MODULE_PATH})
include(KDEInstallDirs)
include(ECMQtDeclareLoggingCategory)

set(IFUP_SRCS src/main.cpp src/specialtypes.cpp)

ecm_qt_declare_logging_category(
  IFUP_SRCS
  HEADER
  generated/ifupdebug.h
  IDENTIFIER
  "LOG_IFUP_SYSTEMD_RESOLVED"
  CATEGORY_NAME
  "sh.tat.ifup-systemd-resolved")

find_package(
  Qt5
  COMPONENTS DBus Network
  REQUIRED)

add_definitions(
  -DQT_NO_CAST_FROM_ASCII
  -DQT_NO_CAST_FROM_BYTEARRAY
  -DQT_NO_CAST_TO_ASCII
  -DQT_NO_SIGNALS_SLOTS_KEYWORDS
  -DQT_NO_URL_CAST_FROM_STRING
  -DQT_STRICT_ITERATORS
  -DQT_USE_FAST_OPERATOR_PLUS
  -DQT_USE_QSTRINGBUILDER)
include_directories(src ${CMAKE_CURRENT_BINARY_DIR}/generated)
add_executable(ifup-systemd-resolved
               ${IFUP_SRCS} ${CMAKE_CURRENT_BINARY_DIR}/generated/ifupdebug.cpp)
target_link_libraries(ifup-systemd-resolved Qt5::DBus Qt5::Network)

install(TARGETS ifup-systemd-resolved)

include(CPack)
