project(KSane)
cmake_minimum_required(VERSION 3.0.0)

if(POLICY CMP0063)
    cmake_policy(SET CMP0063 NEW)
endif()

message(STATUS "-------------------------------------------")
message(STATUS "Starting CMake configuration for: libksane")

# ECM setup (Extended Cmake Modules)
include(FeatureSummary)
set(KF5_VERSION "5.55.0")
find_package(ECM ${KF5_VERSION} REQUIRED NO_MODULE)
set_package_properties(ECM PROPERTIES TYPE REQUIRED DESCRIPTION "Extra CMake Modules." URL "https://commits.kde.org/extra-cmake-modules")
# ECM setup2 and include find same cmake module (copied from /usr/share/kde4/apps/cmake/modules/FindSane.cmake)
set(CMAKE_MODULE_PATH ${KSane_SOURCE_DIR}/cmake-modules ${ECM_MODULE_PATH})

include(FeatureSummary)
include(ECMSetupVersion)
include(ECMGenerateHeaders)
include(ECMInstallIcons)
include(CMakePackageConfigHelpers)
include(CheckFunctionExists)
include(KDEInstallDirs)
include(KDEFrameworkCompilerSettings NO_POLICY_SCOPE)
include(KDECMakeSettings)
include(GenerateExportHeader)

ecm_setup_version(
  ${KF5_VERSION}
  VARIABLE_PREFIX KSANE
  VERSION_HEADER "${CMAKE_CURRENT_BINARY_DIR}/ksane_version.h"
  PACKAGE_VERSION_FILE "${CMAKE_CURRENT_BINARY_DIR}/KF5SaneConfigVersion.cmake"
)

# Dependencies
set(REQUIRED_QT_VERSION "5.7.0")
# Required Qt5 components to build this framework
find_package(Qt5 ${REQUIRED_QT_VERSION} NO_MODULE REQUIRED Core Widgets)

# Required KF5 frameworks
find_package(KF5I18n ${KF5_VERSION} REQUIRED)

if (NOT WIN32)
    find_package(KF5WidgetsAddons ${KF5_VERSION} REQUIRED)
    find_package(KF5TextWidgets ${KF5_VERSION} REQUIRED)

    # Optional KF5 frameworks
    find_package(KF5Wallet ${KF5_VERSION})
    set_package_properties(KF5Wallet PROPERTIES DESCRIPTION "Safe desktop-wide storage for passwords" TYPE OPTIONAL
        PURPOSE "Required to have permanent storage of passwords for scanners"
    )

    # Check if sane API is available.
    find_package(Sane REQUIRED)
    message(STATUS "SANE_FOUND:       ${SANE_FOUND}")
    message(STATUS "SANE_INCLUDE_DIR: ${SANE_INCLUDE_DIR}")
    message(STATUS "SANE_LIBRARY:     ${SANE_LIBRARY}")
    # macro_log_feature(SANE_FOUND "SANE development toolkit" "Scanner Access Now Easy (SANE) development package" "http://www.sane-project.org" TRUE "" "Needed by libksane")
endif (NOT WIN32)

# Subdirectories
if (SANE_FOUND)
    add_subdirectory(src)
    if (BUILD_TESTING)
        add_subdirectory(autotests)
        add_subdirectory(tests)
    endif()
else ()
    add_subdirectory(ksanetwain)
endif()

# Create a Config.cmake and a ConfigVersion.cmake file and install them
set(CMAKECONFIG_INSTALL_DIR "${CMAKECONFIG_INSTALL_PREFIX}/KF5Sane")

configure_package_config_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/KF5SaneConfig.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/KF5SaneConfig.cmake"
  INSTALL_DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
)

install(FILES
  "${CMAKE_CURRENT_BINARY_DIR}/KF5SaneConfig.cmake"
  "${CMAKE_CURRENT_BINARY_DIR}/KF5SaneConfigVersion.cmake"
  DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
  COMPONENT Devel
)

install(EXPORT
  KF5SaneTargets
  DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
  FILE KF5SaneTargets.cmake
  NAMESPACE KF5::
)

install(FILES
  "${CMAKE_CURRENT_BINARY_DIR}/ksane_version.h"
  DESTINATION "${KF5_INCLUDE_INSTALL_DIR}"
  COMPONENT Devel
)

# needed?
#include_directories (${CMAKE_SOURCE_DIR}
#                     ${CMAKE_BINARY_DIR}
#                     ${CMAKE_CURRENT_BINARY_DIR}/libksane)

# =======================================================
# Information to update before to release this library.

# Library version history:
# API      ABI
# 0.1.0 => 0.1.0
# 0.1.1 => 0.1.1
# 0.2.0 => 0.2.0

# Library API version
SET(KSANE_LIB_MAJOR_VERSION "0")
SET(KSANE_LIB_MINOR_VERSION "3")
SET(KSANE_LIB_PATCH_VERSION "1")

# Suffix to add at end of version string. Usual values are:
# "-git"   : alpha code unstable from git. Do not use in production
# "-beta1" : beta1 release.
# "-beta2" : beta2 release.
# "-beta3" : beta3 release.
# "-rc"    : release candidate.
# ""       : final relase. Can be used in production.
SET(KSANE_LIB_SUFFIX_VERSION "")

# Library ABI version used by linker.
# For details : http://www.gnu.org/software/libtool/manual/libtool.html#Updating-version-info
SET(KSANE_LIB_SO_CUR_VERSION "0")
SET(KSANE_LIB_SO_REV_VERSION "2")
SET(KSANE_LIB_SO_AGE_VERSION "1")

# =======================================================
# Set env. variables accordinly.

SET(KSANE_LIB_VERSION_STRING "${KSANE_LIB_MAJOR_VERSION}.${KSANE_LIB_MINOR_VERSION}.${KSANE_LIB_PATCH_VERSION}${KSANE_LIB_SUFFIX_VERSION}")
SET(KSANE_LIB_VERSION_ID "0x0${KSANE_LIB_MAJOR_VERSION}0${KSANE_LIB_MINOR_VERSION}0${KSANE_LIB_PATCH_VERSION}")

SET(KSANE_LIB_SO_VERSION_STRING "${KSANE_LIB_SO_CUR_VERSION}.${KSANE_LIB_SO_REV_VERSION}.${KSANE_LIB_SO_AGE_VERSION}")

# =======================================================

ADD_DEFINITIONS(-DKDE_DEFAULT_DEBUG_AREA=51004) 

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/src/version.h.cmake ${CMAKE_CURRENT_BINARY_DIR}/src/version.h)

# =======================================================

# To prevent warnings from M$ compiler
IF(WIN32 AND MSVC)
    ADD_DEFINITIONS(-D_CRT_SECURE_NO_WARNINGS)
    ADD_DEFINITIONS(-D_ATL_SECURE_NO_WARNINGS)
    ADD_DEFINITIONS(-D_AFX_SECURE_NO_WARNINGS)
ENDIF(WIN32 AND MSVC)

# =======================================================

feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)

