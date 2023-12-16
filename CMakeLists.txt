cmake_minimum_required(VERSION 3.17)

project(QWindowKit VERSION 0.0.1.1 LANGUAGES CXX)

# ----------------------------------
# Configure Options
# ----------------------------------
option(QWINDOWKIT_DISABLE_FETCH_PACKAGES "Disable fetching remote packages if not found" OFF)

# ----------------------------------
# Build Options
# ----------------------------------
option(QWINDOWKIT_BUILD_STATIC "Build static libraries" OFF)
option(QWINDOWKIT_BUILD_WIDGETS "Build widgets module" ON)
option(QWINDOWKIT_BUILD_QUICK "Build quick module" ON)
option(QWINDOWKIT_BUILD_STYLE_SUPPORT "Build style support module" ON)
option(QWINDOWKIT_BUILD_EXAMPLES "Build examples" OFF)
option(QWINDOWKIT_BUILD_DOCUMENTATIONS "Build documentations" OFF)
option(QWINDOWKIT_INSTALL "Install library" ON)

option(QWINDOWKIT_FORCE_QT_WINDOW_CONTEXT "Enable Qt Window Context anyway" OFF)

# ----------------------------------
# CMake Settings
# ----------------------------------
if(MSVC)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /manifest:no")
    set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} /manifest:no")
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} /manifest:no")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /utf-8")

    if(NOT DEFINED CMAKE_DEBUG_POSTFIX)
        set(CMAKE_DEBUG_POSTFIX "d")
    endif()
elseif(MINGW)
    set(CMAKE_STATIC_LIBRARY_PREFIX "")
    set(CMAKE_SHARED_LIBRARY_PREFIX "")
endif()

if(QWINDOWKIT_INSTALL)
    include(GNUInstallDirs)
    include(CMakePackageConfigHelpers)
endif()

# ----------------------------------
# Project Variables
# ----------------------------------
set(QWINDOWKIT_VERSION ${PROJECT_VERSION})
set(QWINDOWKIT_INSTALL_NAME ${PROJECT_NAME})

# ----------------------------------
# Find basic dependencies
# ----------------------------------
if(QWINDOWKIT_DISABLE_FETCH_PACKAGES)
    find_package(qmsetup REQUIRED)
else()
    find_package(qmsetup QUIET)

    if(NOT TARGET qmsetup::library)
        include("cmake/setup-qmsetup.cmake")
    endif()
endif()

qm_import(Filesystem)
qm_init_directories()

# ----------------------------------
# Add source modules
# ----------------------------------
add_subdirectory(src)

if(QWINDOWKIT_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()