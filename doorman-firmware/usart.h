#ifndef _USART_H_
#define _USART_H_

// attiny2313 doc page 113 table 48
#define BAUD_PRESCALE(x,y) (((y / (x * 16UL))) - 1)

void usart_init(unsigned int, unsigned int);
void usart_tx(unsigned char);
void usrt_tx_blob(unsigned char*, unsigned int);
unsigned char usart_rx(void);
int usart_tx_peek(void);

#endif
