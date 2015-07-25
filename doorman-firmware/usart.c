#include "usart.h"
#include <avr/io.h>

void usart_init(unsigned int baud, unsigned int cpu)
{
    UBRRH = (unsigned char)(BAUD_PRESCALE(baud, cpu) >> 8);
    UBRRL = (unsigned char)BAUD_PRESCALE(baud, cpu);
}

void usart_tx(unsigned char byte)
{
    while( !(UCSRA & (1 << UDRE)) );
    UDR = byte;
}

unsigned char usart_rx(void)
{
    while( !(UCSRA & (1 << RXC)) );
    return UDR;
}
