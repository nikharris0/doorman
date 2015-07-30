#include <stdlib.h>
#include <string.h>
#include "xbee.h"

struct xbee_frame *xbee_create_at_frame(uint8_t req_id, unsigned char cmd[2], void *param, int len)
{
    struct xbee_frame *frame = malloc(sizeof(struct xbee_frame));
    frame->delimiter = FT_AT_CMD;
    frame->len = 4 + len;
    frame->frame_type = FT_AT_CMD;
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

struct xbee_frame *xbee_create_tx_request_frame(uint8_t req_id, struct xbee_tx_request *r)
{
    struct xbee_frame *frame = malloc(sizeof(struct xbee_frame));
    frame->delimiter = FT_TX_REQUEST;
    frame->len = 14 + r->len;
    frame->frame_type = FT_TX_REQUEST;
    frame->id = req_id;

    unsigned char *data = malloc(12 + r->len);
    memcpy(data, &r->addr, sizeof(r->addr));
    memcpy(data + sizeof(r->addr), &r->network, sizeof(r->network));
    data[11] = r->radius;
    data[12] = r->opts;
    memcpy(&data + 12, r->data, r->len);

    uint8_t checksum;
    checksum = 0;
    checksum += frame->frame_type + frame->id;

    int x;
    for(x = 0; x < 12 + r->len; x++) {
        checksum += data[x];
    }

    frame->checksum = 0xFF - checksum;
    return frame;
}

int xbee_frame_to_at_response(unsigned char *data, struct xbee_at_response *r)
{
    if(!data || !r || data[0] != FT_AT_CMD_RESPONSE) {
        return 0;
    }

    r->id = data[4];
    r->cmd[0] = data[5];
    r->cmd[1] = data[6];
    r->status = (xbee_at_status)data[7];
    r->reg = NULL;

    uint16_t length;
    memcpy(&length, &data[1], sizeof(length));

    // if the length indicates that the register data is not empty
    // copy that into our AT response struct
    if(length > 5) {
        memcpy(r->reg, data + 8, length - 5);
    }

    return 1;
}

int xbee_frame_to_tx_status(unsigned char *data, struct xbee_tx_status *s)
{
    if(!data || !s || data[0] != FT_TX_RESPONSE) {
        return 0;
    }

    s->id = data[4];
    memcpy(&s->addr, &data[5], sizeof(s->addr));
    s->retries = data[7];
    s->status = data[8];
    s->discovery_status = data[9];

    return 1;
}

int xbee_frame_to_rx_packet(unsigned char *data, struct xbee_rx_packet *p)
{
    if(!data || !p || data[0] != FT_RX_RECIEVED) {
        return 0;
    }

    memcpy(&p->addr, &data[4], sizeof(p->addr));
    memcpy(&p->network, &data[12], sizeof(p->network));
    p->opts = data[14];

    uint16_t len;
    memcpy(&len, &data[1], sizeof(len));
    memcpy(p->data, &data[15], len - 12);
    p->len = len - 12;
    return 1;
}

void xbee_free_at_response(struct xbee_at_response *r)
{
    if(r) {
        if(r->reg) {
            free(r->reg);
        }

        free(r);
    }
}

uint8_t get_frame_id(unsigned char *frame)
{
    return (uint8_t)frame[3];
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
