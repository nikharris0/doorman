NAME = doorman
MCU = attiny2313

DRIVER = usbtiny

CC = avr-gcc
OBJCOPY = avr-objcopy
CFLAGS += -Wall -g -Os -mmcu=$(MCU)

FILES = main.c xbee.c radio.c usart.c

all:
	avr-gcc $(CFLAGS) -o $(NAME).elf $(FILES)
	avr-objcopy -O ihex $(NAME).elf $(NAME).hex

flash:
	sudo avrdude -c $(DRIVER) -p $(MCU) -U flash:w:$(NAME).hex

fuses:
	sudo avrdude -c $(DRIVER) -p $(MCU) -U lfuse:w:0xe4:m -U hfuse:w:0xdf:m

clean:
	rm *.elf
	rm *.hex
