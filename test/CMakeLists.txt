# FreeRTOS
# Copyright (C) 2022 Amazon.com, Inc. or its affiliates. All Rights Reserved.
# SPDX-License-Identifier: MIT


add_library( unity_test_runtime STATIC EXCLUDE_FROM_ALL )

target_sources( unity_test_runtime
                PRIVATE
                runtime/fr_test_platform.c
                runtime/fr_test_runner.c
                runtime/unity/src/unity.c )

target_include_directories( unity_test_runtime
                            PUBLIC
                            runtime
                            runtime/unity/src )

target_sources( unity_test_runtime
                PUBLIC
                runtime/unity/src/unity.h
                runtime/unity/src/unity_internal.h
                runtime/test_execution_config.h
                runtime/test_param_config.h
                runtime/unity_config.h )

add_executable( transport_interface_test
                freertos_lib_integration/transport_interface/transport_interface_test.c )

target_link_libraries( transport_interface_test
                       PRIVATE
                       FreeRTOS::Kernel
                       FreeRTOS::coreMQTT
                       FreeRTOS::TCP
                       tls_transport
                       unity_test_runtime )


