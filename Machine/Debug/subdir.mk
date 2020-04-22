################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ATM.c \
../ATM_private.c \
../DIO.c \
../KEYPAD.c \
../LCD.c \
../MCAL.c \
../Scheduler.c \
../Scheduler_CFG.c \
../TIMER.c \
../UART.c \
../main.c 

OBJS += \
./ATM.o \
./ATM_private.o \
./DIO.o \
./KEYPAD.o \
./LCD.o \
./MCAL.o \
./Scheduler.o \
./Scheduler_CFG.o \
./TIMER.o \
./UART.o \
./main.o 

C_DEPS += \
./ATM.d \
./ATM_private.d \
./DIO.d \
./KEYPAD.d \
./LCD.d \
./MCAL.d \
./Scheduler.d \
./Scheduler_CFG.d \
./TIMER.d \
./UART.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=11059200UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


