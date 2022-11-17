# FreeRTOS Classic Distribution
# Copyright (C) 2022 Amazon.com, Inc. or its affiliates. All Rights Reserved.
# SPDX-License-Identifier: MIT

#
# AWS IoT Device Defender
#
check_init_submodule( IoTDeviceDefender )
add_library( AWS_IoT_DeviceDefender STATIC EXCLUDE_FROM_ALL )

target_sources( AWS_IoT_DeviceDefender
                PRIVATE
                IoTDeviceDefender/source/defender.c )

target_include_directories( AWS_IoT_DeviceDefender
                            PUBLIC
                            IoTDeviceDefender/source/include
                            ../config )

target_sources( AWS_IoT_DeviceDefender
                PUBLIC
                IoTDeviceDefender/source/include/defender.h
                IoTDeviceDefender/source/include/defender_config_defaults.h
                ../config/defender_config.h )

target_link_libraries( AWS_IoT_DeviceDefender PRIVATE FreeRTOS::Logging )

add_library( AWS::IoT::DeviceDefender ALIAS AWS_IoT_DeviceDefender )

#
# AWS IoT Device Shadow
#
check_init_submodule( IoTDeviceShadow )
add_library( AWS_IoT_DeviceShadow STATIC EXCLUDE_FROM_ALL )

target_sources( AWS_IoT_DeviceShadow
                PRIVATE
                IoTDeviceShadow/source/shadow.c )

target_include_directories( AWS_IoT_DeviceShadow
                            PUBLIC
                            IoTDeviceShadow/source/include
                            ../config )

target_sources( AWS_IoT_DeviceShadow
                PUBLIC
                IoTDeviceShadow/source/include/shadow.h
                IoTDeviceShadow/source/include/shadow_config_defaults.h
                ../config/shadow_config.h )

target_link_libraries( AWS_IoT_DeviceShadow PRIVATE FreeRTOS::Logging )

add_library( AWS::IoT::DeviceShadow ALIAS AWS_IoT_DeviceShadow )

#
# AWS IoT Jobs
#
check_init_submodule( IoTJobs )
add_library( AWS_IoT_Jobs STATIC EXCLUDE_FROM_ALL )

target_sources( AWS_IoT_Jobs
                PRIVATE
                IoTJobs/source/jobs.c )

target_include_directories( AWS_IoT_Jobs
                            PUBLIC
                            IoTJobs/source/include )

target_sources( AWS_IoT_Jobs
                PUBLIC
                IoTJobs/source/include/jobs.h )

add_library( AWS::IoT::Jobs ALIAS AWS_IoT_Jobs )

#
# AWS Fleet Provisioning
#
check_init_submodule( IotFleetProvisioning )
add_library( AWS_IoT_FleetProvisioning STATIC EXCLUDE_FROM_ALL )

target_sources( AWS_IoT_FleetProvisioning
                PRIVATE
                IotFleetProvisioning/source/fleet_provisioning.c )

target_include_directories( AWS_IoT_FleetProvisioning
                            PUBLIC
                            IotFleetProvisioning/source/include
                            ../config )

target_sources( AWS_IoT_FleetProvisioning
                PUBLIC
                IotFleetProvisioning/source/include/fleet_provisioning.h
                IotFleetProvisioning/source/include/fleet_provisioning_config_defaults.h
                ../config/fleet_provisioning_config.h )

target_link_libraries( AWS_IoT_FleetProvisioning PRIVATE FreeRTOS::Logging )

add_library( AWS::IoT::FleetProvisioning ALIAS AWS_IoT_FleetProvisioning )


#
# AWS IoT Over The Air updates
#
check_init_submodule( IotOta )
add_library( AWS_IoT_Ota STATIC EXCLUDE_FROM_ALL )

target_sources( AWS_IoT_Ota
                PRIVATE
                IotOta/source/ota.c
                IotOta/source/ota_base64.c
                IotOta/source/ota_cbor.c
                IotOta/source/ota_http.c
                IotOta/source/ota_interface.c
                IotOta/source/ota_mqtt.c )

target_include_directories( AWS_IoT_Ota
                            PUBLIC
                            IotOta/source/include
                            ../config )

target_sources( AWS_IoT_Ota
                PRIVATE
                IotOta/source/include/ota_base64_private.h
                IotOta/source/include/ota_cbor_private.h
                IotOta/source/include/ota_http_private.h
                IotOta/source/include/ota_interface_private.h
                IotOta/source/include/ota_mqtt_private.h
                IotOta/source/include/ota_private.h
                ../config/ota_config.h )

target_sources( AWS_IoT_Ota
                PUBLIC
                IotOta/source/include/ota.h
                IotOta/source/include/ota_appversion32.h
                IotOta/source/include/ota_config_defaults.h
                IotOta/source/include/ota_http_interface.h
                IotOta/source/include/ota_mqtt_interface.h
                IotOta/source/include/ota_os_interface.h
                IotOta/source/include/ota_platform_interface.h )

target_link_libraries( AWS_IoT_Ota
                       PUBLIC
                       FreeRTOS::coreJSON
                       TinyCBOR )

target_link_libraries( AWS_IoT_Ota PRIVATE FreeRTOS::Logging )

add_library( AWS::IoT::Ota ALIAS AWS_IoT_Ota )

#
# AWS Signature v4
#
check_init_submodule( sigv4 )
add_library( AWS_Sigv4 STATIC EXCLUDE_FROM_ALL )

target_sources( AWS_Sigv4
                PRIVATE
                sigv4/source/sigv4.c
                sigv4/source/sigv4_quicksort.c )

target_include_directories( AWS_Sigv4
                            PUBLIC
                            sigv4/source/include
                            ../config )

target_sources( AWS_Sigv4
                PRIVATE
                sigv4/source/include/sigv4_internal.h
                ../config/sigv4_config.h )

target_sources( AWS_Sigv4
                PUBLIC
                sigv4/source/include/sigv4.h
                sigv4/source/include/sigv4_config_defaults.h
                sigv4/source/include/sigv4_quicksort.h )

target_link_libraries( AWS_Sigv4 PRIVATE FreeRTOS::Logging )

add_library( AWS::Sigv4 ALIAS AWS_Sigv4 )
