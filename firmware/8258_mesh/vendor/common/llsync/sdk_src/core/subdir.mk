################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../vendor/common/llsync/sdk_src/core/ble_qiot_utils_mesh.c 

OBJS += \
./vendor/common/llsync/sdk_src/core/ble_qiot_utils_mesh.o 


# Each subdirectory must supply rules for building sources it contributes
vendor/common/llsync/sdk_src/core/%.o: ../vendor/common/llsync/sdk_src/core/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: TC32 Compiler'
	tc32-elf-gcc -ffunction-sections -fdata-sections -I"C:\Users\NV-Smart03\Downloads\telink_code\CSLH_BLE\CSLH_BLE\firmware" -I"C:\Users\NV-Smart03\Downloads\telink_code\CSLH_BLE\CSLH_BLE\firmware\proj\include" -I"C:\Users\NV-Smart03\Downloads\telink_code\CSLH_BLE\CSLH_BLE\firmware\vendor\common\mi_api\mijia_ble_api" -I"C:\Users\NV-Smart03\Downloads\telink_code\CSLH_BLE\CSLH_BLE\firmware\vendor\common\mi_api\libs" -I"C:\Users\NV-Smart03\Downloads\telink_code\CSLH_BLE\CSLH_BLE\firmware\vendor\common\llsync\sdk_src\include" -I"C:\Users\NV-Smart03\Downloads\telink_code\CSLH_BLE\CSLH_BLE\firmware\vendor\common\llsync\include" -I"C:\Users\NV-Smart03\Downloads\telink_code\CSLH_BLE\CSLH_BLE\firmware\vendor\common\llsync\cfg" -I"C:\Users\NV-Smart03\Downloads\telink_code\CSLH_BLE\CSLH_BLE\firmware\vendor\common\llsync\data_template" -D__PROJECT_MESH__=1 -D__telink__ -DCHIP_TYPE=CHIP_TYPE_8258 -Wall -O2 -fpack-struct -fshort-enums -finline-small-functions -std=gnu99 -fshort-wchar -fms-extensions -c -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


