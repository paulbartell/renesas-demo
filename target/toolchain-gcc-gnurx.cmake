###############################################################################
# FreeRTOS
# Copyright (C) 2022 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
# SPDX-License-Identifier: MIT
###############################################################################

set(CMAKE_SYSTEM_PROCESSOR              rx)
set(CMAKE_C_COMPILER_ID                 GNU)
set(CMAKE_SYSTEM_NAME                   Generic)

set(CMAKE_TRY_COMPILE_TARGET_TYPE       STATIC_LIBRARY)
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM   NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY   ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE   ONLY)

set(TC_SUFFIX                           ${CMAKE_EXECUTABLE_SUFFIX})

set(CMAKE_C_COMPILER_WORKS              TRUE)
set(CMAKE_CXX_COMPILER_WORKS            TRUE)

set(TC_PREFIX                           rx-elf-)

set(CMAKE_C_FLAGS "-nostdlib --specs=nosys.specs -fdata-sections -ffunction-sections -Wl,--gc-sections -fdiagnostics-parseable-fixits -mcpu=rx64m -misa=v2 -mlittle-endian-data" CACHE INTERNAL "")
set(CMAKE_CXX_FLAGS "-nostdlib ${APP_CXX_FLAGS} ${CMAKE_C_FLAGS} -fno-exceptions" CACHE INTERNAL "")


# Toolchain Utilities
set(CMAKE_AR                            ${TC_PREFIX}ar${TC_SUFFIX} CACHE INTERNAL "")
set(CMAKE_ASM_COMPILER                  ${TC_PREFIX}gcc${TC_SUFFIX} CACHE INTERNAL "")
set(CMAKE_C_COMPILER                    ${TC_PREFIX}gcc${TC_SUFFIX} CACHE INTERNAL "")
set(CMAKE_CXX_COMPILER                  ${TC_PREFIX}g++${TC_SUFFIX} CACHE INTERNAL "" )
set(CMAKE_LINKER                        ${TC_PREFIX}ld${TC_SUFFIX} CACHE INTERNAL "")
set(CMAKE_OBJCOPY                       ${TC_PREFIX}objcopy${TC_SUFFIX} CACHE INTERNAL "")
set(CMAKE_RANLIB                        ${TC_PREFIX}ranlib${TC_SUFFIX} CACHE INTERNAL "")
set(CMAKE_SIZE                          ${TC_PREFIX}size${TC_SUFFIX} CACHE INTERNAL "")
set(CMAKE_STRIP                         ${TC_PREFIX}size${TC_SUFFIX} CACHE INTERNAL "")

set(CMAKE_C_FLAGS_DEBUG                 "-Os -g" CACHE INTERNAL "")
set(CMAKE_C_FLAGS_RELEASE               "-Os -DNDEBUG" CACHE INTERNAL "")
set(CMAKE_CXX_FLAGS_DEBUG               "${CMAKE_C_FLAGS_DEBUG}" CACHE INTERNAL "")
set(CMAKE_CXX_FLAGS_RELEASE             "${CMAKE_C_FLAGS_RELEASE}" CACHE INTERNAL "")
