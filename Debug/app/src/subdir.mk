################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../app/src/uart_f103.c 

OBJS += \
./app/src/uart_f103.o 

C_DEPS += \
./app/src/uart_f103.d 


# Each subdirectory must supply rules for building sources it contributes
app/src/%.o app/src/%.su app/src/%.cyclo: ../app/src/%.c app/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"/home/tdat/STM32CubeIDE/workspace_1.15.1/uart_stm32f103c8t6/drvs" -I"/home/tdat/STM32CubeIDE/workspace_1.15.1/uart_stm32f103c8t6/drvs/inc" -I"/home/tdat/STM32CubeIDE/workspace_1.15.1/uart_stm32f103c8t6/drvs/src" -I"/home/tdat/STM32CubeIDE/workspace_1.15.1/uart_stm32f103c8t6/app" -I"/home/tdat/STM32CubeIDE/workspace_1.15.1/uart_stm32f103c8t6/app/inc" -I"/home/tdat/STM32CubeIDE/workspace_1.15.1/uart_stm32f103c8t6/app/src" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-app-2f-src

clean-app-2f-src:
	-$(RM) ./app/src/uart_f103.cyclo ./app/src/uart_f103.d ./app/src/uart_f103.o ./app/src/uart_f103.su

.PHONY: clean-app-2f-src

