# FreeRTOS Classic Distribution
# Copyright (C) 2022 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
# SPDX-License-Identifier: MIT

set(MBEDTLS_VERSION 3.2.1)

option(CONFIG_NET_TLS_MBEDTLS "Build MbedTLS" ON)

if( CONFIG_NET_TLS_MBEDTLS )
    set(MBEDTLS_TARGET_PREFIX "MbedTLS_")
    set(MBEDTLS_DIR ${CMAKE_CURRENT_LIST_DIR}/mbedtls_lib )

    check_init_submodule( mbedtls_lib )

    option(USE_STATIC_MBEDTLS_LIBRARY "" ON)
    option(USE_SHARED_MBEDTLS_LIBRARY "" OFF)

    # For compatibility with MbedTLS 3.2.1+
    function(link_to_source base_name)
    endfunction()

    add_library( mbedtls_platform STATIC EXCLUDE_FROM_ALL )

    target_sources( mbedtls_platform
                    PRIVATE
                    mbedtls_freertos_port.c
                    mbedtls_entropy_tsip.c )

    target_link_libraries( mbedtls_platform
                           PUBLIC
                               FreeRTOS::Kernel
                               FreeRTOS::Logging
                           PRIVATE
                               MbedTLS_mbedcrypto
                               MbedTLS_mbedtls
                               MbedTLS_mbedx509
                               mbedtls_config )
    target_include_directories( mbedtls_platform
                                PRIVATE
                                ${MBEDTLS_DIR}/library )

    add_subdirectory( mbedtls_lib/library )

    target_compile_definitions( MbedTLS_mbedcrypto
                                PUBLIC
                                "MBEDTLS_CONFIG_FILE=\"mbedtls_config_v${MBEDTLS_VERSION}.h\"" )

    target_include_directories( MbedTLS_mbedcrypto PUBLIC include )

    target_link_libraries( MbedTLS_mbedcrypto PUBLIC mbedtls_platform )


    add_library(Mbed::TLS ALIAS MbedTLS_mbedtls)
    add_library(Mbed::Crypto ALIAS MbedTLS_mbedcrypto)
    add_library(Mbed::X509 ALIAS MbedTLS_mbedx509)
endif()
