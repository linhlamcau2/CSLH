################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../vendor/common/nlc/nlc_blcnlcp.c \
../vendor/common/nlc/nlc_ctrl_client.c \
../vendor/common/nlc/nlc_sensor.c \
../vendor/common/nlc/sensor_ocs_gpio.c \
../vendor/common/nlc/sensor_zsir1000.c 

OBJS += \
./vendor/common/nlc/nlc_blcnlcp.o \
./vendor/common/nlc/nlc_ctrl_client.o \
./vendor/common/nlc/nlc_sensor.o \
./vendor/common/nlc/sensor_ocs_gpio.o \
./vendor/common/nlc/sensor_zsir1000.o 


# Each subdirectory must supply rules for building sources it contributes
vendor/common/nlc/%.o: ../vendor/common/nlc/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: TC32 Compiler'
	tc32-elf-gcc -ffunction-sections -fdata-sections -I"C:\Users\NV-Smart03\Downloads\telink_code\CSLH_BLE\CSLH_BLE\firmware" -I"C:\Users\NV-Smart03\Downloads\telink_code\CSLH_BLE\CSLH_BLE\firmware\proj\include" -I"C:\Users\NV-Smart03\Downloads\telink_code\CSLH_BLE\CSLH_BLE\firmware\vendor\common\mi_api\mijia_ble_api" -I"C:\Users\NV-Smart03\Downloads\telink_code\CSLH_BLE\CSLH_BLE\firmware\vendor\common\mi_api\libs" -I"C:\Users\NV-Smart03\Downloads\telink_code\CSLH_BLE\CSLH_BLE\firmware\vendor\common\llsync\sdk_src\include" -I"C:\Users\NV-Smart03\Downloads\telink_code\CSLH_BLE\CSLH_BLE\firmware\vendor\common\llsync\include" -I"C:\Users\NV-Smart03\Downloads\telink_code\CSLH_BLE\CSLH_BLE\firmware\vendor\common\llsync\cfg" -I"C:\Users\NV-Smart03\Downloads\telink_code\CSLH_BLE\CSLH_BLE\firmware\vendor\common\llsync\data_template" -D__PROJECT_MESH__=1 -D__telink__ -DCHIP_TYPE=CHIP_TYPE_8258 -Wall -O2 -fpack-struct -fshort-enums -finline-small-functions -std=gnu99 -fshort-wchar -fms-extensions -c -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


