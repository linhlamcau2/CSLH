################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../vendor/common/llsync/hal/ble_qiot_export.c 

OBJS += \
./vendor/common/llsync/hal/ble_qiot_export.o 


# Each subdirectory must supply rules for building sources it contributes
vendor/common/llsync/hal/%.o: ../vendor/common/llsync/hal/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: TC32 Compiler'
	tc32-elf-gcc -ffunction-sections -fdata-sections -I"E:\Telink_code\SDK_test\firmware" -I"E:\Telink_code\SDK_test\firmware\proj\include" -I"E:\Telink_code\SDK_test\firmware\vendor\common\mi_api\mijia_ble_api" -I"E:\Telink_code\SDK_test\firmware\vendor\common\mi_api\libs" -I"E:\Telink_code\SDK_test\firmware\vendor\common\llsync\sdk_src\include" -I"E:\Telink_code\SDK_test\firmware\vendor\common\llsync\include" -I"E:\Telink_code\SDK_test\firmware\vendor\common\llsync\cfg" -I"E:\Telink_code\SDK_test\firmware\vendor\common\llsync\data_template" -D__PROJECT_MESH_PRO__=1 -D__telink__ -DCHIP_TYPE=CHIP_TYPE_8258 -Wall -O2 -fpack-struct -fshort-enums -finline-small-functions -std=gnu99 -fshort-wchar -fms-extensions -c -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


