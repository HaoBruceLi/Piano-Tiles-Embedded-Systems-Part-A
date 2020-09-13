# File:   Makefile
# Author: Narottam Royal
# Date:   5 Oct 2018
# Descr:  ENCE260 Assignment Makefile


# Target file
TARGET = testing
SUBDIRS = ../drivers ../drivers/avr ../display


######### NO NEED TO EDIT ANYTHING BELOW THIS LINE #########


# Definitions
CC = avr-gcc
CFLAGS = -mmcu=atmega32u2 -Os -Wall -Wstrict-prototypes -Wextra -g $(addprefix -I , $(SUBDIRS))
LDFLAGS = -lm
CPP = avr-cpp
OBJCOPY = avr-objcopy
SIZE = avr-size
FILE = $(basename $(TARGET))
SRC = $(wildcard *.c $(addsuffix /*.c, $(SUBDIRS)))
OBJ = $(SRC:.c=.o)
DEP = $(OBJ:.o=.d)
DEPFLAGS = -MM -MT $(@:.d=.o)

# Use 'del' command on Windows
ifeq ($(OS),Windows_NT)
	RM = del
endif


# Default target
all: $(FILE).elf


# Compile: create object files from c files
%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $< $(LDFLAGS)


# Link: create ELF output file from object files
$(FILE).elf: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
	$(SIZE) $@


# Include dependencies
%.d: %.c
	@$(CPP) $(CFLAGS) $< $(DEPFLAGS) >$@
-include $(DEP)


# Target: clean project
.PHONY: clean $(SUBDIRS)
clean: $(SUBDIRS)
	-$(RM) *.d *.elf *.hex *.o


$(SUBDIRS):
	@$(MAKE) -s -C $@


# Target: program project
.PHONY: program
program: $(FILE).elf
	$(OBJCOPY) -O ihex $(FILE).elf $(FILE).hex
	dfu-programmer atmega32u2 erase
	dfu-programmer atmega32u2 flash $(FILE).hex
	dfu-programmer atmega32u2 start
