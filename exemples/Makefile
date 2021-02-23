PROJECT = awesomesauce
BUILD_DIR = build

SHARED_DIR = ../lib
CXXFILES = main.cxx itm.cxx
CFILES += pwm.c
#AFILES += api-asm.S

DEVICE=stm32f407vgt6
OOCD_FILE = ../stm32f4discovery.cfg

# You shouldn't have to edit anything below here.
VPATH += $(SHARED_DIR)
INCLUDES += $(patsubst %,-I%, . $(SHARED_DIR))
OPENCM3_DIR=../libopencm3

include $(OPENCM3_DIR)/mk/genlink-config.mk
include ../rules.mk
include $(OPENCM3_DIR)/mk/genlink-rules.mk
