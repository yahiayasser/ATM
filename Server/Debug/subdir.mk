################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../BST_prg.c \
../DIO.c \
../LCD.c \
../MCAL.c \
../Server.c \
../UART.c \
../external_eeprom.c \
../i2c.c \
../main.c 

OBJS += \
./BST_prg.o \
./DIO.o \
./LCD.o \
./MCAL.o \
./Server.o \
./UART.o \
./external_eeprom.o \
./i2c.o \
./main.o 

C_DEPS += \
./BST_prg.d \
./DIO.d \
./LCD.d \
./MCAL.d \
./Server.d \
./UART.d \
./external_eeprom.d \
./i2c.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=11059200UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


