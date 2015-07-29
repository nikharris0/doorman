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

void usrt_tx_blob(unsigned char *b, unsigned int len)
{
    int x;
    for(x = 0; x < len; x++) {
        usart_tx(b[x]);
    }
}

unsigned char usart_rx(void)
{
    while( !(UCSRA & (1 << RXC)) );
    return UDR;
}

int usart_tx_peek(void)
{
    return (UCSRA & (1 << RXC));
}
