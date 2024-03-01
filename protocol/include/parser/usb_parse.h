#ifndef USB_PARSE_H
#define USB_PARSE_H

#include "byte.h"

typedef struct ParsedMsg {
    const int topic;      
    const int subtopic;   
    const int flags;   
    const byte_t* data;   
} ParsedMsg;

/* 
 * Will receive raw buffer from SAM
 */
ParsedMsg PARSE_MESSAGE(const byte_t* message);

#endif