#ifndef _XBEE_H_
#define _XBEE_H_

#include <stdint.h>

typedef enum {
    FT_AT_CMD = 0x08,
    FT_AT_CMD_QUEUED = 0x09,
    FT_AT_CMD_RESPONSE = 0x88,
    FT_REMOTE_CMD_REQUEST = 0x17,
    FT_REMOTE_CMD_RESPONSE = 0x97,
    FT_MODEM_STATUS = 0x8A,
    FT_TX_REQUEST = 0x10,
    FT_TX_RESPONSE = 0x8B,
    FT_RX_RECIEVED = 0x90,
    FT_RX_DATA_RECIEVED = 0x92,
    FT_NODE_IDENT_INDICATOR = 0x95,
    FT_UNKNOWN = 0xFF,
} xbee_frame_type;

typedef enum {
    AT_STATUS_OK = 0,
    AT_STATUS_ERROR,
    AT_STATUS_INVALID_CMD,
    AT_STATUS_INVALID_PARAM,
    AT_STATUS_TX_FAILURE
} xbee_at_status;

struct xbee_frame {
    uint8_t delimiter;
    uint16_t len;
    uint8_t frame_type;
    uint8_t id;
    unsigned char *data;
    uint8_t checksum;
};

struct xbee_at_response {
    uint8_t id;
    char cmd[2];
    xbee_at_status status;
    void *reg;
};

struct xbee_tx_request_frame {
    uint8_t delimiter;
    uint16_t len;
    uint8_t frame_type;
    uint8_t id;
    uint64_t destination;
    uint16_t network;
    uint8_t broadcast_radius;
    uint8_t options;
    char data[8];
    uint8_t checksum;
};

#endif
