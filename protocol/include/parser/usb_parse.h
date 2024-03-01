#ifndef USB_PARSE_H
#define USB_PARSE_H

typedef unsigned char byte_t;

/* 
 * Will receive raw buffer from SAM
 */
void HANDLE_MESSAGE(const byte_t* message);

#endif