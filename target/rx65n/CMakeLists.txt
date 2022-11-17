# FreeRTOS
# Copyright (C) 2022 Amazon.com, Inc. or its affiliates. All Rights Reserved.
# SPDX-License-Identifier: MIT

add_library( platform_config INTERFACE )

target_sources( platform_config
                INTERFACE
                    config/FreeRTOSConfig.h
                    smc_gen/r_bsp/platform.h
                    smc_gen/r_config/r_bsp_config.h )

target_include_directories( platform_config
                            INTERFACE
                                config
                                smc_gen/r_bsp
                                smc_gen/r_config )