################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/basic.c \
../Core/Src/button.c \
../Core/Src/can.c \
../Core/Src/led.c \
../Core/Src/main.c \
../Core/Src/pn532.c \
../Core/Src/pn532_stm32f1.c \
../Core/Src/spi1.c \
../Core/Src/stm32f1xx_hal_msp.c \
../Core/Src/stm32f1xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32f1xx.c \
../Core/Src/work.c 

OBJS += \
./Core/Src/basic.o \
./Core/Src/button.o \
./Core/Src/can.o \
./Core/Src/led.o \
./Core/Src/main.o \
./Core/Src/pn532.o \
./Core/Src/pn532_stm32f1.o \
./Core/Src/spi1.o \
./Core/Src/stm32f1xx_hal_msp.o \
./Core/Src/stm32f1xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32f1xx.o \
./Core/Src/work.o 

C_DEPS += \
./Core/Src/basic.d \
./Core/Src/button.d \
./Core/Src/can.d \
./Core/Src/led.d \
./Core/Src/main.d \
./Core/Src/pn532.d \
./Core/Src/pn532_stm32f1.d \
./Core/Src/spi1.d \
./Core/Src/stm32f1xx_hal_msp.d \
./Core/Src/stm32f1xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32f1xx.d \
./Core/Src/work.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su Core/Src/%.cyclo: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/basic.cyclo ./Core/Src/basic.d ./Core/Src/basic.o ./Core/Src/basic.su ./Core/Src/button.cyclo ./Core/Src/button.d ./Core/Src/button.o ./Core/Src/button.su ./Core/Src/can.cyclo ./Core/Src/can.d ./Core/Src/can.o ./Core/Src/can.su ./Core/Src/led.cyclo ./Core/Src/led.d ./Core/Src/led.o ./Core/Src/led.su ./Core/Src/main.cyclo ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/pn532.cyclo ./Core/Src/pn532.d ./Core/Src/pn532.o ./Core/Src/pn532.su ./Core/Src/pn532_stm32f1.cyclo ./Core/Src/pn532_stm32f1.d ./Core/Src/pn532_stm32f1.o ./Core/Src/pn532_stm32f1.su ./Core/Src/spi1.cyclo ./Core/Src/spi1.d ./Core/Src/spi1.o ./Core/Src/spi1.su ./Core/Src/stm32f1xx_hal_msp.cyclo ./Core/Src/stm32f1xx_hal_msp.d ./Core/Src/stm32f1xx_hal_msp.o ./Core/Src/stm32f1xx_hal_msp.su ./Core/Src/stm32f1xx_it.cyclo ./Core/Src/stm32f1xx_it.d ./Core/Src/stm32f1xx_it.o ./Core/Src/stm32f1xx_it.su ./Core/Src/syscalls.cyclo ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.cyclo ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32f1xx.cyclo ./Core/Src/system_stm32f1xx.d ./Core/Src/system_stm32f1xx.o ./Core/Src/system_stm32f1xx.su ./Core/Src/work.cyclo ./Core/Src/work.d ./Core/Src/work.o ./Core/Src/work.su

.PHONY: clean-Core-2f-Src

