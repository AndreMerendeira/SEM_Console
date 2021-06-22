SHELL := /bin/bash

SERIAL:=/dev/ttyUSB0

CC:=gcc
CFLAGS:=-g -Wall

INCLUDE+=-I.

SRC:=console.c rs232comm.c sem_platform.c sem_script.c

CONSOLE_CMD=./console -s $(SERIAL)

run: console
	$(CONSOLE_CMD)

console: $(SRC)
	$(CC) $(CFLAGS) $(INCLUDE) $(SRC) -o $@

clean:
	@rm -f *# *~ console *.bin *.log

.PHONY: run clean
