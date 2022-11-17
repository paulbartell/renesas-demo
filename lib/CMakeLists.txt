# FreeRTOS
# Copyright (C) 2022 Amazon.com, Inc. or its affiliates. All Rights Reserved.
# SPDX-License-Identifier: MIT

add_library( lib_config INTERFACE )
target_include_directories( lib_config INTERFACE config )
target_sources( lib_config
                INTERFACE
                config/core_http_config.h
                config/core_mqtt_agent_config.h
                config/core_mqtt_config.h
                config/core_sntp_config.h
                config/defender_config.h
                config/mqtt_metrics.h
                config/shadow_config.h )


add_subdirectory( freertos )
add_subdirectory( aws )
add_subdirectory( mbedtls )

include( llhttp.cmake )
include( tinycbor.cmake )
