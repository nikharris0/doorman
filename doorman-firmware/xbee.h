#ifndef _XBEE_H_
#define _XBEE_H_

enum xbee_frame_type {
    AT_CMD = 0x08,
    AT_CMD_QUEUED = 0x09,
    REMOTE_CMD_REQUEST = 0x17,
    REMOTE_CMD_RESPONSE = 0x97,
    AT_CMD_RESPONSE = 0x88,
    MODEM_STATUS = 0x8A,
    TX_REQUEST = 0x10,
    TX_RESPONSE = 0x8B,
    RX_RECIEVED = 0x90,
    RX_DATA_RECIEVED = 0x92,
    NODE_IDENT_INDICATOR = 0x95,
};

enum xbee_at_status {
    OK = 0,
    ERROR,
    INVALID_CMD,
    INVALID_PARAM,
    TX_FAILURE
};

struct xbee_at_frame {
    uint8_t delimiter;
    uint16_t len;
    uint8_t id;
    uint8_t frame_type;
    char cmd[2];
    char *param;
    uint8_t len;
};

struct xbee_at_response_frame {

}

#endif
