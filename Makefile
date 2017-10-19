CFLAGS=-g -Wall -mcall-prologues -mmcu=atmega328p -Os
CPP=avr-g++
CC=avr-gcc
OBJ2HEX=avr-objcopy 
LDFLAGS=-Wl,-gc-sections -lpololu_atmega328p

PORT=/dev/ttyACM0
AVRDUDE=avrdude
TARGET=test
OBJECT_FILES=test.o 

all: $(TARGET).hex

clean:
	rm -f *.o *.hex *.obj *.hex

%.hex: %.obj
	$(OBJ2HEX) -R .eeprom -O ihex $< $@

%.o: test.h test.c

%.m3pi.o : %.c
	$(CC) $(CFLAGS) -DM3PI -c -o $@ $<

test.obj: $(OBJECT_FILES)
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@

program: $(TARGET).hex
	$(AVRDUDE) -p m328p -c avrisp2 -P $(PORT) -U flash:w:$(TARGET).hex
