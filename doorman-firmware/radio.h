#ifndef _RADIO_H_
#define _RADIO_H_

void radio_init();
int radio_authenticate_card(unsigned char *);
void radio_transmit_status(int);

#endif
