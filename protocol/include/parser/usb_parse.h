#ifndef USB_PARSE_H
#define USB_PARSE_H

#include "byte.h"

#define INIT_BYTE 0xAB

typedef struct MsgHeader {
    const byte_t  init_valid;
    const byte_t  msg_size; 
} MsgHeader;

typedef struct MsgFields {
    const byte_t topic;      
    const byte_t subtopic;   
    const byte_t data_flags;
    byte_t data[8]; 
} MsgFields;

MsgHeader parse_header(const byte_t* message);
MsgFields parse_fields(const byte_t* message, const byte_t msgSize);

/* 
 * Will receive raw buffer from SAM
 */
void HANDLE_MESSAGE(const byte_t* message);

#endif