################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../drvs/src/uart.c 

OBJS += \
./drvs/src/uart.o 

C_DEPS += \
./drvs/src/uart.d 


# Each subdirectory must supply rules for building sources it contributes
drvs/src/%.o drvs/src/%.su drvs/src/%.cyclo: ../drvs/src/%.c drvs/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"/home/tdat/STM32CubeIDE/workspace_1.15.1/uart_stm32f103c8t6/drvs" -I"/home/tdat/STM32CubeIDE/workspace_1.15.1/uart_stm32f103c8t6/drvs/inc" -I"/home/tdat/STM32CubeIDE/workspace_1.15.1/uart_stm32f103c8t6/drvs/src" -I"/home/tdat/STM32CubeIDE/workspace_1.15.1/uart_stm32f103c8t6/app" -I"/home/tdat/STM32CubeIDE/workspace_1.15.1/uart_stm32f103c8t6/app/inc" -I"/home/tdat/STM32CubeIDE/workspace_1.15.1/uart_stm32f103c8t6/app/src" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-drvs-2f-src

clean-drvs-2f-src:
	-$(RM) ./drvs/src/uart.cyclo ./drvs/src/uart.d ./drvs/src/uart.o ./drvs/src/uart.su

.PHONY: clean-drvs-2f-src

