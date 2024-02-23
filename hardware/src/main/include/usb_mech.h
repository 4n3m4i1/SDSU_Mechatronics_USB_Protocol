#ifndef USB_MECH_H
#define USB_MECH_H

#define LONG_MESSAGE_SIZE 64

#define TOPIC_BYTES 2
#define SUBTOPIC_BYTES 2
#define FLAG_BYTES 2
#define RESERVED_BYTES 2
#define NON_DATA_BYTES TOPIC_BYTES+SUBTOPIC_BYTES+RESERVED_BYTES+FLAG_BYTES
#define LONG_MSG_DATA LONG_MESSAGE_SIZE-NON_DATA_BYTES

#define NUM_TOPICS 6
#define NUM_SUBTOPICS 6

typedef unsigned char byte_t;

typedef struct long_message_t
{
    byte_t topic_id    [TOPIC_BYTES];
    byte_t subtopic_id [SUBTOPIC_BYTES];
    byte_t flags       [FLAG_BYTES];
    byte_t data        [LONG_MSG_DATA];
    byte_t reserved    [RESERVED_BYTES];
} long_message_t;

typedef enum device_topic_t
{
    CONTROLLER      = 0,
    SYSTEM_MONITOR  = 1,
    POWER_SYSTEM    = 2,
    MOTION_CONTROL  = 3,
    RESERVED        = 4,
    AUXILLARY       = 5
} device_topic_t;

/* 
 * Will receive raw buffer from SAM
 */
void HANDLE_MESSAGE(const byte_t* message);

#endif