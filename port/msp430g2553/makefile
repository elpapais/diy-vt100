PREFIX=msp430-

OP_ELF=$(BUILD_DIR)/$(PROGNAME).elf
MCU=msp430g2553

# c compiler
CC=$(PREFIX)gcc
CFLAGS=-O2 -std=c99 -Wall -mmcu=$(MCU) -I$(HW_DIR)/include/ -I$(INCLUDE_DIR)

MSPDEBUG=mspdebug
DFLAGS=rf2500

all: compile

compile:
	cd $(BUILD_DIR); \
	\
	$(CC) $(CFLAGS) \
	-o $(OP_ELF) \
	$(SRC_DIR)/*.c \
	$(SRC_DIR)/*/*.c \
	$(HW_DIR)/*/*.c

clean:
	rm -f $(BUILD_DIR)/*

burn: compile
	$(MSPDEBUG)  $(DFLAGS) 'prog $(OP_ELF)'
