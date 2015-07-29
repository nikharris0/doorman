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

typedef enum {
    TX_STATUS_SUCCESS = 0x00,
    TX_STATUS_MAC_ACK_FAIL = 0x01,
    TX_STATUS_CCA_FAIL = 0x02,
    TX_STATUS_INVALID_DEST = 0x15,
    TX_STATUS_NETWORK_ACK_FAIL = 0x21,
    TX_STATUS_NO_NETWORK = 0x22,
    TX_STATUS_SELF_ADDR = 0x23,
    TX_STATUS_ADDR_NOT_FOUND = 0x24,
    TX_STATUS_NO_ROUTE = 0x25,
    TX_STATUS_NO_RELAY = 0x26,
    TX_STATUS_INVALID_BIND_TABLE = 0x2B,
    TX_STATUS_RESOURCE_ERR = 0x2C,
    TX_STATUS_BROADCAST_APS = 0x2D,
    TX_STATUS_UNICAST_APS = 0x2E,
    TX_STATUS_RESOURCE2_ERR = 0x32,
    TX_STATUS_DATA_TOO_LARGE = 0x74,
    TX_STATUS_IND_MSG_UNREQUEST = 0x75
} xbee_tx_status;

typedef enum {
    DISC_STATUS_NO_OVERHEAD = 0x00,
    DISC_STATUS_ADDR_DISCOVERY = 0x01,
    DISC_STATUS_RESOURCE_ERR = 0x32,
    DISC_STATUS_DATA_TOO_LARGE = 0x74,
    DISC_STATUS_IND_MSG_UNREQUEST = 0x75
} xbee_discovery_status;

typedef enum {
    TX_OPT_DISABLE_ACK = 0x01,
    TX_OPT_ENABLE_APS_ENC = 0x20,
} tx_request_option;

typedef enum {
    RX_OPT_ACK = 0x01,
    RX_OPT_BROADCAST = 0x01,
    RX_OPT_APS = 0x20,
    RX_OPT_END_DEVICE = 0x40
} rx_packet_option;

struct xbee_frame {
    uint8_t delimiter;
    uint16_t len;
    uint8_t frame_type;
    uint8_t id;
    unsigned char *data;
    uint8_t checksum;
};

struct xbee_tx_request {
    uint64_t addr;
    uint16_t network;
    uint8_t radius;
    tx_request_option opts;
    unsigned char * data;
    int len;
};

struct xbee_at_response {
    uint8_t id;
    char cmd[2];
    xbee_at_status status;
    unsigned char *reg;
};

struct xbee_tx_status {
    uint8_t id;
    uint16_t addr;
    uint8_t retries;
    uint8_t status;
    uint8_t discovery_status;
};

struct xbee_rx_packet {
    uint8_t id;
    uint16_t addr;
    uint8_t network;
    rx_packet_option opts;
    unsigned char * data;

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
