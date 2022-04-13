################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/BSP/Components/lis302dl/lis302dl.c 

OBJS += \
./Drivers/BSP/Components/lis302dl/lis302dl.o 

C_DEPS += \
./Drivers/BSP/Components/lis302dl/lis302dl.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/Components/lis302dl/lis302dl.o: ../Drivers/BSP/Components/lis302dl/lis302dl.c Drivers/BSP/Components/lis302dl/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F413xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/BSP/Components/lis302dl/lis302dl.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

