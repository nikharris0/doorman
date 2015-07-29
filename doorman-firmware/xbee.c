#include <stdlib.h>
#include <string.h>
#include "xbee.h"

struct xbee_frame *xbee_create_at_frame(uint8_t req_id, unsigned char cmd[2], void *param, int len)
{
    struct xbee_frame *frame = malloc(sizeof(struct xbee_frame));
    frame->delimiter = 0x7E;
    frame->len = 4 + len;
    frame->frame_type =FT_AT_CMD;
    frame->id = req_id;

    unsigned char *data = malloc(2 + len);
    memcpy(data, &cmd, sizeof(cmd));
    memcpy(data + sizeof(cmd), param, len);

    uint8_t checksum;
    checksum = 0;
    checksum += frame->frame_type + frame->id;

    int x;
    for(x = 0; x < len; x++) {
        checksum += data[x];
    }

    frame->checksum = 0xFF - checksum;
    return frame;
}

xbee_frame_type get_frame_type(unsigned char *data, int len)
{
    if(len < 3) {
        return FT_UNKNOWN;
    }

    if(data[2] < FT_AT_CMD || data[2] > FT_NODE_IDENT_INDICATOR) {
        return FT_UNKNOWN;
    }

    return (xbee_frame_type)data[2];
}
