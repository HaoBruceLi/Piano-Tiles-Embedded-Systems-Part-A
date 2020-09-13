# This Makefile deletes all specified files

# Type of files to remove
FILES = *.d *.o

# Use 'del' command on Windows
ifeq ($(OS),Windows_NT)
	RM = del
endif

# Clean folder
.PHONY: clean
clean: 
	-$(RM) $(FILES)
