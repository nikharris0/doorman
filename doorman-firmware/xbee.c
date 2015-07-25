#include "xbee.h"

struct xbee_at_frame *xbee_create_at_frame(char cmd[2], void *param, int len)
{
    struct xbee_at_frame *frame = malloc(sizeof(xbee_at_frame));
    frame.delimiter = 0x7E;
    frame.len = 4 + len;
    frame.param = param;

    uint8_t checksum;
    checksum = 0;
    checksum += frame.type + frame.id;
    checksum += frame.cmd[0] + frame.cmd[1];
    checksum += len;

    frame.checksum = 0xFF - checksum;
    return frame;
}
