################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../app/src/main.c \
../app/src/smallprintf.c \
../app/src/stm32f7xx_it.c 

OBJS += \
./app/src/main.o \
./app/src/smallprintf.o \
./app/src/stm32f7xx_it.o 

C_DEPS += \
./app/src/main.d \
./app/src/smallprintf.d \
./app/src/stm32f7xx_it.d 


# Each subdirectory must supply rules for building sources it contributes
app/src/%.o app/src/%.su: ../app/src/%.c app/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DSTM32F746xx -c -I"C:/Users/stage/Desktop/http_server/f746_fmc/cmsis/core" -I"C:/Users/stage/Desktop/http_server/f746_fmc/cmsis/device/inc" -I"C:/Users/stage/Desktop/http_server/f746_fmc/bsp/inc" -I"C:/Users/stage/Desktop/http_server/f746_fmc/app/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-app-2f-src

clean-app-2f-src:
	-$(RM) ./app/src/main.d ./app/src/main.o ./app/src/main.su ./app/src/smallprintf.d ./app/src/smallprintf.o ./app/src/smallprintf.su ./app/src/stm32f7xx_it.d ./app/src/stm32f7xx_it.o ./app/src/stm32f7xx_it.su

.PHONY: clean-app-2f-src

