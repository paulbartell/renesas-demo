# FreeRTOS
# Copyright (C) 2022 Amazon.com, Inc. or its affiliates. All Rights Reserved.
# SPDX-License-Identifier: MIT

cmake_minimum_required(VERSION 3.16)

find_package( Git )
if(NOT Git_FOUND)
    message(STATUS "Git was not found.. skipping submodule operations")
endif()

function( check_init_submodule submodule_path )
    if( NOT EXISTS "${CMAKE_CURRENT_LIST_DIR}/${submodule_path}/.git" )
        if( Git_FOUND )
            message( STATUS "Initializing submodule: ${submodule_path}")
            execute_process( COMMAND ${GIT_EXECUTABLE} submodule update --init --checkout ${submodule_path}
                             WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
                             RESULT_VARIABLE GIT_SUBMOD_RESULT)
        else()
            message( FATAL_ERROR "Git binary is not available and library submodule ${submodule_path} was not found." )
        endif()
    endif()
endfunction()

macro( target_headers )
    list(POP_FRONT ${ARGV} target_name)
    target_sources( ${target_name} PUBLIC ${ARGV} )
endmacro()

set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR} )
set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib )
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib )

set( FREERTOS_PLUS_CONFIGURED TRUE PARENT_SCOPE )

include( target/toolchain-gcc-gnurx.cmake )

project( "FreeRTOS Renesas RX Reference Integration" )

add_subdirectory( target )

add_subdirectory( source )

add_subdirectory( lib )
# add_subdirectory( test )
