TARGET=test


#### The path to the root of STM32CubeF4 directory ####
CUBE_ROOT_DIR=/home/baiz/Work/stm32/STM32CubeF4/




#### Include path ####

##*.h of this project
INCLUDE = -IInc

## Include files from STM libraries

# stm32f4xx_hal_*.h are located in this path 
INCLUDE += -I$(CUBE_ROOT_DIR)/Drivers/STM32F4xx_HAL_Driver/Inc
# stm32f4xx.h is located in this path
INCLUDE += -I$(CUBE_ROOT_DIR)/Drivers/CMSIS/Device/ST/STM32F4xx/Include
# core_*.h
INCLUDE += -I$(CUBE_ROOT_DIR)/Drivers/CMSIS/Include
# Some defines for F4-Discovery board (Called BSP:Board Support Package)
# For example, the LED3, LED4, etc. are defined here. 
INCLUDE += -I$(CUBE_ROOT_DIR)/Drivers/BSP/STM32F4-Discovery





#SRC PATH
VPATH = Src
VPATH += $(CUBE_ROOT_DIR)/Drivers/STM32F4xx_HAL_Driver/Src
VPATH +=  $(CUBE_ROOT_DIR)/Drivers/BSP/STM32F4-Discovery

# get all *.c in the Src directory
SRCS = main.c  stm32f4xx_hal_msp.c  stm32f4xx_it.c  system_stm32f4xx.c  





#### Basic HAL library
#### You may need to add more file to use

# HAL_Init, HAL_GetREVID, HAL_IncTick, HAL_GetTick, HAL_InitTick
SRCS += stm32f4xx_hal.c
# HAL_RCC_OscConfig, HAL_RCC_ClockConfig
SRCS += stm32f4xx_hal_rcc.c
# HAL_SYSTICK_Config, HAL_NVIC_SetPriority, HAL_NVIC_SetPriorityGrouping
SRCS += stm32f4xx_hal_cortex.c
# GPIO
SRCS += stm32f4xx_hal_gpio.c
# seems to be basic
#SRCS += stm32f4xx_hal_pwr_ex.c

##  Board definitions
SRCS += stm32f4_discovery.c


#### Lib
LIBS = -L$(CUBE_ROOT_DIR)/Drivers/CMSIS/Lib


#### Toolchain setting
CC=arm-none-eabi-gcc
AR=arm-none-eabi-ar
OBJCOPY=arm-none-eabi-objcopy
OBJDUMP=arm-none-eabi-objdump
SIZE=arm-none-eabi-size
GDB=arm-none-eabi-gdb
OCD= openocd

### Compiler flags, copied from https://github.com/stv0g/stm32cube-gcc/blob/master/Makefile
CFLAGS     = -Wall -g -std=c99 -Os
CFLAGS    += -mlittle-endian -mcpu=cortex-m4 -march=armv7e-m -mthumb
CFLAGS    += -mfpu=fpv4-sp-d16 -mfloat-abi=hard
CFLAGS    += -ffunction-sections -fdata-sections


# Linker flags, partially copied from https://github.com/stv0g/stm32cube-gcc/blob/master/Makefile
LDFLAGS    = -Wl,--gc-sections -Wl,-Map=$(TARGET).map $(LIBS) -TSTM32F407VGTx_FLASH.ld

# Enable Semihosting, _exit not defined otherwise
LDFLAGS   += --specs=rdimon.specs -lc -lrdimon


# add startup file to build
STARTUP = startup_stm32f407xx.s


OBJS = $(SRCS:.c=.o)

.PHONY: proj

all: proj

proj: $(TARGET).elf

$(TARGET).elf: $(SRCS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(INCLUDE) $(STARTUP) $^ -o $@
	$(OBJCOPY) -O ihex $(TARGET).elf $(TARGET).hex
	$(OBJCOPY) -O binary $(TARGET).elf $(TARGET).bin

clean:
	rm -f *.o $(TARGET).elf $(TARGET).hex $(TARGET).bin


# Flash the STM32F4
burn: proj
	st-flash write $(TARGET).bin 0x8000000
