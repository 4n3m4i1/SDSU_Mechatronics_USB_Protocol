#ifndef MSG_TYPES_H
#define MSG_TYPES_H

#define EMPTY_MSG_SIZE          8
#define SML_MSG_SIZE            16
#define MED_MSG_SIZE            32
#define LRG_MSG_SIZE            64

#define INIT_BYTES              1
#define META_FLAG_BYTES         1
#define TOPIC_BYTES             1
#define SUBTOPIC_BYTES          1
#define DATA_FLAG_BYTES         1
#define RESERVED_BYTES          3
#define NON_DATA_BYTES          (INIT_BYTES+META_FLAG_BYTES+TOPIC_BYTES+ \
                                SUBTOPIC_BYTES+DATA_FLAG_BYTES+RESERVED_BYTES)
                                
#define LRG_MSG_DATA_BYTES      LRG_MSG_SIZE-NON_DATA_BYTES
#define MED_MSG_DATA_BYTES      MED_MSG_SIZE-NON_DATA_BYTES
#define SML_MSG_DATA_BYTES      SML_MSG_SIZE-NON_DATA_BYTES

#include "byte.h"

/* This defines the message protocol */
typedef struct full_message_t
{
    byte_t init         [INIT_BYTES];
    byte_t meta_flags   [META_FLAG_BYTES];
    byte_t topic_id     [TOPIC_BYTES];
    byte_t subtopic_id  [SUBTOPIC_BYTES];
    byte_t data_flags   [DATA_FLAG_BYTES];
    byte_t data         [MED_MSG_DATA_BYTES];
    byte_t reserved     [RESERVED_BYTES];
} full_message_t;

typedef struct message_t
{
    byte_t topic_id     [TOPIC_BYTES];
    byte_t subtopic_id  [SUBTOPIC_BYTES];
    byte_t data_flags   [DATA_FLAG_BYTES];
    byte_t data         [MED_MSG_DATA_BYTES];
} message_t;

typedef enum message_sizes {
    EMPTY_MSG  =  0x00,
    SMALL_MSG  =  0x01,
    MEDIUM_MSG =  0x02,
    LARGE_MSG  =  0x03
} message_sizes;

typedef enum byte_indeces {
    INIT_BYTE_INDEX       =  0x00,
    METAFLAGS_BYTE_INDEX  =  0x01,
    TOPIC_BYTE_INDEX      =  0x02,
    SUBTOPIC_BYTE_INDEX   =  0x03,
    DATAFLAGS_BYTE_INDEX  =  0x04
} byte_indeces;

#endif