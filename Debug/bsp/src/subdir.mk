################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../bsp/src/fmc.c \
../bsp/src/usart.c 

OBJS += \
./bsp/src/fmc.o \
./bsp/src/usart.o 

C_DEPS += \
./bsp/src/fmc.d \
./bsp/src/usart.d 


# Each subdirectory must supply rules for building sources it contributes
bsp/src/%.o bsp/src/%.su: ../bsp/src/%.c bsp/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DSTM32F746xx -c -I"C:/Users/stage/Desktop/http_server/f746_fmc/cmsis/core" -I"C:/Users/stage/Desktop/http_server/f746_fmc/cmsis/device/inc" -I"C:/Users/stage/Desktop/http_server/f746_fmc/bsp/inc" -I"C:/Users/stage/Desktop/http_server/f746_fmc/app/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-bsp-2f-src

clean-bsp-2f-src:
	-$(RM) ./bsp/src/fmc.d ./bsp/src/fmc.o ./bsp/src/fmc.su ./bsp/src/usart.d ./bsp/src/usart.o ./bsp/src/usart.su

.PHONY: clean-bsp-2f-src

