################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/BSP/STM32412G-Discovery/stm32412g_discovery.c \
../Drivers/BSP/STM32412G-Discovery/stm32412g_discovery_audio.c \
../Drivers/BSP/STM32412G-Discovery/stm32412g_discovery_eeprom.c \
../Drivers/BSP/STM32412G-Discovery/stm32412g_discovery_lcd.c \
../Drivers/BSP/STM32412G-Discovery/stm32412g_discovery_qspi.c \
../Drivers/BSP/STM32412G-Discovery/stm32412g_discovery_sd.c \
../Drivers/BSP/STM32412G-Discovery/stm32412g_discovery_ts.c 

OBJS += \
./Drivers/BSP/STM32412G-Discovery/stm32412g_discovery.o \
./Drivers/BSP/STM32412G-Discovery/stm32412g_discovery_audio.o \
./Drivers/BSP/STM32412G-Discovery/stm32412g_discovery_eeprom.o \
./Drivers/BSP/STM32412G-Discovery/stm32412g_discovery_lcd.o \
./Drivers/BSP/STM32412G-Discovery/stm32412g_discovery_qspi.o \
./Drivers/BSP/STM32412G-Discovery/stm32412g_discovery_sd.o \
./Drivers/BSP/STM32412G-Discovery/stm32412g_discovery_ts.o 

C_DEPS += \
./Drivers/BSP/STM32412G-Discovery/stm32412g_discovery.d \
./Drivers/BSP/STM32412G-Discovery/stm32412g_discovery_audio.d \
./Drivers/BSP/STM32412G-Discovery/stm32412g_discovery_eeprom.d \
./Drivers/BSP/STM32412G-Discovery/stm32412g_discovery_lcd.d \
./Drivers/BSP/STM32412G-Discovery/stm32412g_discovery_qspi.d \
./Drivers/BSP/STM32412G-Discovery/stm32412g_discovery_sd.d \
./Drivers/BSP/STM32412G-Discovery/stm32412g_discovery_ts.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/STM32412G-Discovery/stm32412g_discovery.o: ../Drivers/BSP/STM32412G-Discovery/stm32412g_discovery.c Drivers/BSP/STM32412G-Discovery/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F413xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/BSP/STM32412G-Discovery/stm32412g_discovery.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/BSP/STM32412G-Discovery/stm32412g_discovery_audio.o: ../Drivers/BSP/STM32412G-Discovery/stm32412g_discovery_audio.c Drivers/BSP/STM32412G-Discovery/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F413xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/BSP/STM32412G-Discovery/stm32412g_discovery_audio.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/BSP/STM32412G-Discovery/stm32412g_discovery_eeprom.o: ../Drivers/BSP/STM32412G-Discovery/stm32412g_discovery_eeprom.c Drivers/BSP/STM32412G-Discovery/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F413xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/BSP/STM32412G-Discovery/stm32412g_discovery_eeprom.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/BSP/STM32412G-Discovery/stm32412g_discovery_lcd.o: ../Drivers/BSP/STM32412G-Discovery/stm32412g_discovery_lcd.c Drivers/BSP/STM32412G-Discovery/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F413xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/BSP/STM32412G-Discovery/stm32412g_discovery_lcd.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/BSP/STM32412G-Discovery/stm32412g_discovery_qspi.o: ../Drivers/BSP/STM32412G-Discovery/stm32412g_discovery_qspi.c Drivers/BSP/STM32412G-Discovery/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F413xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/BSP/STM32412G-Discovery/stm32412g_discovery_qspi.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/BSP/STM32412G-Discovery/stm32412g_discovery_sd.o: ../Drivers/BSP/STM32412G-Discovery/stm32412g_discovery_sd.c Drivers/BSP/STM32412G-Discovery/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F413xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/BSP/STM32412G-Discovery/stm32412g_discovery_sd.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/BSP/STM32412G-Discovery/stm32412g_discovery_ts.o: ../Drivers/BSP/STM32412G-Discovery/stm32412g_discovery_ts.c Drivers/BSP/STM32412G-Discovery/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F413xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/BSP/STM32412G-Discovery/stm32412g_discovery_ts.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

