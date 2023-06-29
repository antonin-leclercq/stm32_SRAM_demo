################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../cmsis/device/src/startup_stm32f746xx.s 

C_SRCS += \
../cmsis/device/src/system_stm32f7xx.c 

OBJS += \
./cmsis/device/src/startup_stm32f746xx.o \
./cmsis/device/src/system_stm32f7xx.o 

S_DEPS += \
./cmsis/device/src/startup_stm32f746xx.d 

C_DEPS += \
./cmsis/device/src/system_stm32f7xx.d 


# Each subdirectory must supply rules for building sources it contributes
cmsis/device/src/%.o: ../cmsis/device/src/%.s cmsis/device/src/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m7 -g3 -c -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@" "$<"
cmsis/device/src/%.o cmsis/device/src/%.su: ../cmsis/device/src/%.c cmsis/device/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DSTM32F746xx -c -I"C:/Users/stage/Desktop/http_server/f746_fmc/cmsis/core" -I"C:/Users/stage/Desktop/http_server/f746_fmc/cmsis/device/inc" -I"C:/Users/stage/Desktop/http_server/f746_fmc/bsp/inc" -I"C:/Users/stage/Desktop/http_server/f746_fmc/app/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-cmsis-2f-device-2f-src

clean-cmsis-2f-device-2f-src:
	-$(RM) ./cmsis/device/src/startup_stm32f746xx.d ./cmsis/device/src/startup_stm32f746xx.o ./cmsis/device/src/system_stm32f7xx.d ./cmsis/device/src/system_stm32f7xx.o ./cmsis/device/src/system_stm32f7xx.su

.PHONY: clean-cmsis-2f-device-2f-src

