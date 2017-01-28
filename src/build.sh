#!/bin/bash

# Main build file.
# Build the executable and copy it as intel hex format binary image.
# No Makefile for the moment.

project_name=Lazuli

../checklines.sh

avr-gcc \
	-ansi \
	-std=c89 \
	-pedantic \
	-Wall \
	-Wextra \
	-Werror \
	-Iinclude \
	-mmcu=atmega328p \
	-nostartfiles \
	-nostdlib \
	-nodefaultlibs \
	-T kern/linker.x \
	-o $project_name \
	kern/arch/AVR/interrupt_vectors_table.S \
	kern/arch/AVR/startup.S \
	kern/arch/AVR/arch.c \
	kern/arch/AVR/timer_counter_0.c \
	kern/kernel.c \
	kern/memory.c \
	kern/main.c

avr-objcopy \
	-j .text \
	-j .data \
	-O ihex \
	$project_name \
	$project_name.hex
