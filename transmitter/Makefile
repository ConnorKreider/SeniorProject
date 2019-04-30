# Makefile for receiver
# Author: Connor Kreider
MCU = atmega328p
TARGET = transmitter
OBJECTS = transmitter.o
F_CPU = 8000000
CFLAGS=-funsigned-char -funsigned-bitfields -ffunction-sections -fno-inline-small-functions -fpack-struct -fshort-enums -fno-strict-aliasing -fno-split-wide-types -Wall -Wstrict-prototypes -std=gnu99 -MMD -MP -O2 -mmcu=${MCU} -g -DF_CPU=$(F_CPU) -I.
#CFLAGS = -Wall -O2 -mmcu=$(MCU) -DF_CPU=$(F_CPU) -I.
CC=avr-gcc
OBJCOPY=avr-objcopy

#when running make flash avr
default: $(TARGET).hex
	avrdude -pm328p -c usbtiny -P usb -U flash:w:$(TARGET).hex:i
	#fuse for 8M lfuse:w:0xE2:m

#create hex file for flashing from elf
$(TARGET).hex: $(TARGET).elf
	$(OBJCOPY) -O ihex -R .eeprom -R .fuse -R .lock $(TARGET).elf $(TARGET).hex

#combined project files into elf
$(TARGET).elf: $(OBJECTS)
	$(CC) -mmcu=${MCU} -o $(TARGET).elf $(OBJECTS)

#remove all created files
clean:
	rm -rf $(TARGET).elf $(OBJECTS) $(TARGET).hex
