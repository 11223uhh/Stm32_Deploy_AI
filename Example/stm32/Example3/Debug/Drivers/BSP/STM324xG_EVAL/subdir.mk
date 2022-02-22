################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/BSP/STM324xG_EVAL/stm324xg_eval.c \
../Drivers/BSP/STM324xG_EVAL/stm324xg_eval_audio.c \
../Drivers/BSP/STM324xG_EVAL/stm324xg_eval_camera.c \
../Drivers/BSP/STM324xG_EVAL/stm324xg_eval_eeprom.c \
../Drivers/BSP/STM324xG_EVAL/stm324xg_eval_io.c \
../Drivers/BSP/STM324xG_EVAL/stm324xg_eval_lcd.c \
../Drivers/BSP/STM324xG_EVAL/stm324xg_eval_sd.c \
../Drivers/BSP/STM324xG_EVAL/stm324xg_eval_sram.c \
../Drivers/BSP/STM324xG_EVAL/stm324xg_eval_ts.c 

OBJS += \
./Drivers/BSP/STM324xG_EVAL/stm324xg_eval.o \
./Drivers/BSP/STM324xG_EVAL/stm324xg_eval_audio.o \
./Drivers/BSP/STM324xG_EVAL/stm324xg_eval_camera.o \
./Drivers/BSP/STM324xG_EVAL/stm324xg_eval_eeprom.o \
./Drivers/BSP/STM324xG_EVAL/stm324xg_eval_io.o \
./Drivers/BSP/STM324xG_EVAL/stm324xg_eval_lcd.o \
./Drivers/BSP/STM324xG_EVAL/stm324xg_eval_sd.o \
./Drivers/BSP/STM324xG_EVAL/stm324xg_eval_sram.o \
./Drivers/BSP/STM324xG_EVAL/stm324xg_eval_ts.o 

C_DEPS += \
./Drivers/BSP/STM324xG_EVAL/stm324xg_eval.d \
./Drivers/BSP/STM324xG_EVAL/stm324xg_eval_audio.d \
./Drivers/BSP/STM324xG_EVAL/stm324xg_eval_camera.d \
./Drivers/BSP/STM324xG_EVAL/stm324xg_eval_eeprom.d \
./Drivers/BSP/STM324xG_EVAL/stm324xg_eval_io.d \
./Drivers/BSP/STM324xG_EVAL/stm324xg_eval_lcd.d \
./Drivers/BSP/STM324xG_EVAL/stm324xg_eval_sd.d \
./Drivers/BSP/STM324xG_EVAL/stm324xg_eval_sram.d \
./Drivers/BSP/STM324xG_EVAL/stm324xg_eval_ts.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/STM324xG_EVAL/stm324xg_eval.o: ../Drivers/BSP/STM324xG_EVAL/stm324xg_eval.c Drivers/BSP/STM324xG_EVAL/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F413xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/BSP/STM324xG_EVAL/stm324xg_eval.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/BSP/STM324xG_EVAL/stm324xg_eval_audio.o: ../Drivers/BSP/STM324xG_EVAL/stm324xg_eval_audio.c Drivers/BSP/STM324xG_EVAL/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F413xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/BSP/STM324xG_EVAL/stm324xg_eval_audio.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/BSP/STM324xG_EVAL/stm324xg_eval_camera.o: ../Drivers/BSP/STM324xG_EVAL/stm324xg_eval_camera.c Drivers/BSP/STM324xG_EVAL/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F413xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/BSP/STM324xG_EVAL/stm324xg_eval_camera.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/BSP/STM324xG_EVAL/stm324xg_eval_eeprom.o: ../Drivers/BSP/STM324xG_EVAL/stm324xg_eval_eeprom.c Drivers/BSP/STM324xG_EVAL/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F413xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/BSP/STM324xG_EVAL/stm324xg_eval_eeprom.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/BSP/STM324xG_EVAL/stm324xg_eval_io.o: ../Drivers/BSP/STM324xG_EVAL/stm324xg_eval_io.c Drivers/BSP/STM324xG_EVAL/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F413xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/BSP/STM324xG_EVAL/stm324xg_eval_io.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/BSP/STM324xG_EVAL/stm324xg_eval_lcd.o: ../Drivers/BSP/STM324xG_EVAL/stm324xg_eval_lcd.c Drivers/BSP/STM324xG_EVAL/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F413xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/BSP/STM324xG_EVAL/stm324xg_eval_lcd.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/BSP/STM324xG_EVAL/stm324xg_eval_sd.o: ../Drivers/BSP/STM324xG_EVAL/stm324xg_eval_sd.c Drivers/BSP/STM324xG_EVAL/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F413xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/BSP/STM324xG_EVAL/stm324xg_eval_sd.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/BSP/STM324xG_EVAL/stm324xg_eval_sram.o: ../Drivers/BSP/STM324xG_EVAL/stm324xg_eval_sram.c Drivers/BSP/STM324xG_EVAL/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F413xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/BSP/STM324xG_EVAL/stm324xg_eval_sram.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/BSP/STM324xG_EVAL/stm324xg_eval_ts.o: ../Drivers/BSP/STM324xG_EVAL/stm324xg_eval_ts.c Drivers/BSP/STM324xG_EVAL/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F413xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/BSP/STM324xG_EVAL/stm324xg_eval_ts.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

