# Makefile for receiver
# Author: Connor Kreider
MCU = atmega328
TARGET = receiver
OBJECTS = receiver.o
F_CPU = 8000000
CFLAGS = -Wall -mmcu=$(MCU) -DF_CPU=$(F_CPU) -I.
CC=avr-gcc
OBJCOPY=avr-objcopy

#when running make flash avr
default: $(TARGET).hex
	avrdude -pm328p -c usbtiny -P usb -V -F -U flash:w:$(TARGET).hex:i
	#fuse for 8M lfuse:w:0xE2:m

#create hex file for flashing from elf
$(TARGET).hex: $(TARGET).elf
	$(OBJCOPY) -O ihex $(TARGET).elf $(TARGET).hex

#combined project files into elf
$(TARGET).elf: $(OBJECTS)
	$(CC) -o $(TARGET).elf $(OBJECTS)

#remove all created files
clean:
	rm -rf $(TARGET).elf $(OBJECTS) $(TARGET).hex
