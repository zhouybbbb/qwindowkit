function(truncate_url _input _output _last_delim)
    string(FIND "${_input}" "/" _last_slash REVERSE)
    string(FIND "${_input}" ":" _last_colon REVERSE)

    if(_last_slash GREATER _last_colon)
        set(_last_delim_pos ${_last_slash})
        set(_last_delim_char "/")
    else()
        set(_last_delim_pos ${_last_colon})
        set(_last_delim_char ":")
    endif()

    if(_last_delim_pos GREATER -1)
        string(SUBSTRING "${_input}" 0 ${_last_delim_pos} _truncated)
    else()
        set(_truncated "")
    endif()

    set(${_output} "${_truncated}" PARENT_SCOPE)
    set(${_last_delim} ${_last_delim_char} PARENT_SCOPE)
endfunction()

# Modify this variable according to your project structure
set(_source_dir ${CMAKE_CURRENT_SOURCE_DIR}/qmsetup)
# set(_source_dir ${CMAKE_CURRENT_BINARY_DIR}/_packages/qmsetup)

# Check repository existence
if(NOT EXISTS ${_source_dir})
    # Get parent repository git path
    find_package(Git REQUIRED)
    execute_process(
        COMMAND ${GIT_EXECUTABLE} config --get remote.origin.url
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        OUTPUT_VARIABLE _parent_url
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )

    # Up twice
    set(_last_delim)
    truncate_url(${_parent_url} _parent_url _last_delim)
    truncate_url(${_parent_url} _parent_url _last_delim)

    # Get git path
    set(_url "${_parent_url}${_last_delim}stdware/qmsetup.git")

    # Run git clone
    message(STATUS "Running git clone ${_url}")
    set(_output_content)
    execute_process(
        COMMAND ${GIT_EXECUTABLE} clone --recursive --branch main ${_url} ${_source_dir}
        RESULT_VARIABLE _git_result
        OUTPUT_VARIABLE _output_content
        ERROR_VARIABLE _output_content
    )

    if(NOT _git_result EQUAL "0")
        message(FATAL_ERROR "Git clone of qmsetup failed: ${_output_content}")
    endif()
endif()

# Import install function
include("${_source_dir}/cmake/modules/InstallPackage.cmake")

# Install package in place
set(_package_path)
qm_install_package(qmsetup
    SOURCE_DIR ${_source_dir}
    BUILD_TYPE Release
    RESULT_PATH _package_path
)

# Find package again
find_package(qmsetup REQUIRED PATHS ${_package_path})

# Update import path
set(qmsetup_DIR ${_package_path} CACHE PATH "" FORCE)