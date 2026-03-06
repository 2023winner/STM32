# Makefile for STM32 Balance Car

# Toolchain settings
CC = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy
SIZE = arm-none-eabi-size

# Target settings
TARGET = balance_car

# Source files
SRCS = User/main.c \
       User/stm32f10x_it.c \
       Hardware/Motor.c \
       Hardware/PWM.c \
       Hardware/OLED.c \
       Hardware/Key.c \
       Hardware/Blooth.c \
       Hardware/NRF24L01.c \
       Hardware/Mpu6050/mpu6050.c \
       Hardware/Mpu6050/MPU6050_I2C.c \
       Hardware/Mpu6050/inv_mpu.c \
       Hardware/Mpu6050/inv_mpu_dmp_motion_driver.c \
       Hardware/PID.c \
       System/Delay.c \
       System/sys.c \
       Start/system_stm32f10x.c \
       Start/core_cm3_minimal.c \
       Library/stm32f10x_gpio.c \
       Library/stm32f10x_rcc.c \
       Library/stm32f10x_tim.c \
       Library/stm32f10x_usart.c \
       Library/stm32f10x_i2c.c \
       Library/misc.c

# Assembly files
# ASMS = Start/startup_stm32f10x_md.s

# Include directories
INCS = -IUser \
       -IHardware \
       -IHardware/Mpu6050 \
       -ISystem \
       -IStart \
       -ILibrary

# Compiler flags
CFLAGS = -mcpu=cortex-m3 -mthumb -std=c99 -Wall -O2 \
         -DSTM32F10X_MD -DUSE_STDPERIPH_DRIVER \
         $(INCS)

# Linker flags
LDFLAGS = -mcpu=cortex-m3 -mthumb -TStart/stm32f10x_flash.ld \
          -Wl,-Map=$(TARGET).map --specs=nosys.specs -lc -lm -Wl,--no-warn-rwx-segments

# Object files
OBJS = $(SRCS:.c=.o)

# Default target
all: $(TARGET).hex size

# Compile C files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Compile assembly files
%.o: %.s
	$(CC) $(CFLAGS) -c $< -o $@

# Link
$(TARGET).elf: $(OBJS)
	$(CC) $(LDFLAGS) $^ -o $@

# Generate hex file
$(TARGET).hex: $(TARGET).elf
	$(OBJCOPY) -O ihex $< $@

# Generate bin file
$(TARGET).bin: $(TARGET).elf
	$(OBJCOPY) -O binary $< $@

# Show size
size:
	$(SIZE) $(TARGET).elf

# Clean
clean:
	-del /Q $(OBJS) $(TARGET).elf $(TARGET).hex $(TARGET).bin $(TARGET).map 2>nul

# Flash using STM32CubeProgrammer
flash:
	STM32_Programmer_CLI -c port=SWD -w $(TARGET).hex -v -rst

# Flash using openocd
flash_openocd:
	openocd -f interface/stlink.cfg -f target/stm32f1x.cfg -c "program $(TARGET).hex verify reset exit"

.PHONY: all clean flash flash_openocd size
