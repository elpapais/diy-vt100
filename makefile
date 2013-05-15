PREFIX=msp430-

PROGNAME=diy-vt100
SRC_DIR=.
BUILD_DIR=$(SRC_DIR)/build
INCLUDE_DIR=$(SRC_DIR)/include
OP_ELF=$(BUILD_DIR)/$(PROGNAME).elf
MCU=msp430g2553

# c compiler
CC=$(PREFIX)gcc
CFLAGS=-Os -mmcu=$(MCU) -I$(INCLUDE_DIR)

MSPDEBUG=mspdebug
DFLAGS=rf2500

all: compile

compile:
	$(CC) $(CFLAGS) -o $(OP_ELF) *.c */*.c

clean:
	rm -f $(BUILD_DIR)/*

burn: compile
	$(MSPDEBUG)  $(DFLAGS) 'prog $(OP_ELF)'
