################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/basic.c \
../Core/Src/can1.c \
../Core/Src/fnd4_tm1637.c \
../Core/Src/hc-sr04.c \
../Core/Src/lcd_keypad.c \
../Core/Src/lcd_st7789v.c \
../Core/Src/led.c \
../Core/Src/main.c \
../Core/Src/pn532.c \
../Core/Src/rfid_pn532.c \
../Core/Src/sg90_servo.c \
../Core/Src/stepmotor-uln2003.c \
../Core/Src/stm32f4xx_hal_msp.c \
../Core/Src/stm32f4xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32f4xx.c \
../Core/Src/thermo_dht11.c \
../Core/Src/work.c 

OBJS += \
./Core/Src/basic.o \
./Core/Src/can1.o \
./Core/Src/fnd4_tm1637.o \
./Core/Src/hc-sr04.o \
./Core/Src/lcd_keypad.o \
./Core/Src/lcd_st7789v.o \
./Core/Src/led.o \
./Core/Src/main.o \
./Core/Src/pn532.o \
./Core/Src/rfid_pn532.o \
./Core/Src/sg90_servo.o \
./Core/Src/stepmotor-uln2003.o \
./Core/Src/stm32f4xx_hal_msp.o \
./Core/Src/stm32f4xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32f4xx.o \
./Core/Src/thermo_dht11.o \
./Core/Src/work.o 

C_DEPS += \
./Core/Src/basic.d \
./Core/Src/can1.d \
./Core/Src/fnd4_tm1637.d \
./Core/Src/hc-sr04.d \
./Core/Src/lcd_keypad.d \
./Core/Src/lcd_st7789v.d \
./Core/Src/led.d \
./Core/Src/main.d \
./Core/Src/pn532.d \
./Core/Src/rfid_pn532.d \
./Core/Src/sg90_servo.d \
./Core/Src/stepmotor-uln2003.d \
./Core/Src/stm32f4xx_hal_msp.d \
./Core/Src/stm32f4xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32f4xx.d \
./Core/Src/thermo_dht11.d \
./Core/Src/work.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su Core/Src/%.cyclo: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/basic.cyclo ./Core/Src/basic.d ./Core/Src/basic.o ./Core/Src/basic.su ./Core/Src/can1.cyclo ./Core/Src/can1.d ./Core/Src/can1.o ./Core/Src/can1.su ./Core/Src/fnd4_tm1637.cyclo ./Core/Src/fnd4_tm1637.d ./Core/Src/fnd4_tm1637.o ./Core/Src/fnd4_tm1637.su ./Core/Src/hc-sr04.cyclo ./Core/Src/hc-sr04.d ./Core/Src/hc-sr04.o ./Core/Src/hc-sr04.su ./Core/Src/lcd_keypad.cyclo ./Core/Src/lcd_keypad.d ./Core/Src/lcd_keypad.o ./Core/Src/lcd_keypad.su ./Core/Src/lcd_st7789v.cyclo ./Core/Src/lcd_st7789v.d ./Core/Src/lcd_st7789v.o ./Core/Src/lcd_st7789v.su ./Core/Src/led.cyclo ./Core/Src/led.d ./Core/Src/led.o ./Core/Src/led.su ./Core/Src/main.cyclo ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/pn532.cyclo ./Core/Src/pn532.d ./Core/Src/pn532.o ./Core/Src/pn532.su ./Core/Src/rfid_pn532.cyclo ./Core/Src/rfid_pn532.d ./Core/Src/rfid_pn532.o ./Core/Src/rfid_pn532.su ./Core/Src/sg90_servo.cyclo ./Core/Src/sg90_servo.d ./Core/Src/sg90_servo.o ./Core/Src/sg90_servo.su ./Core/Src/stepmotor-uln2003.cyclo ./Core/Src/stepmotor-uln2003.d ./Core/Src/stepmotor-uln2003.o ./Core/Src/stepmotor-uln2003.su ./Core/Src/stm32f4xx_hal_msp.cyclo ./Core/Src/stm32f4xx_hal_msp.d ./Core/Src/stm32f4xx_hal_msp.o ./Core/Src/stm32f4xx_hal_msp.su ./Core/Src/stm32f4xx_it.cyclo ./Core/Src/stm32f4xx_it.d ./Core/Src/stm32f4xx_it.o ./Core/Src/stm32f4xx_it.su ./Core/Src/syscalls.cyclo ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.cyclo ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32f4xx.cyclo ./Core/Src/system_stm32f4xx.d ./Core/Src/system_stm32f4xx.o ./Core/Src/system_stm32f4xx.su ./Core/Src/thermo_dht11.cyclo ./Core/Src/thermo_dht11.d ./Core/Src/thermo_dht11.o ./Core/Src/thermo_dht11.su ./Core/Src/work.cyclo ./Core/Src/work.d ./Core/Src/work.o ./Core/Src/work.su

.PHONY: clean-Core-2f-Src

