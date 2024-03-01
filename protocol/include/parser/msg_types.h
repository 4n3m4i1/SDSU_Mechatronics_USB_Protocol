#ifndef MSG_TYPES_H
#define MSG_TYPES_H

#define SML_MSG_SIZE    16
#define MED_MSG_SIZE    32
#define LRG_MSG_SIZE    64

#define INIT_BYTES      1
#define META_FLAG_BYTES 1
#define TOPIC_BYTES     1
#define SUBTOPIC_BYTES  1
#define DATA_FLAG_BYTES 1
#define RESERVED_BYTES  3
#define NON_DATA_BYTES  TOPIC_BYTES+SUBTOPIC_BYTES+RESERVED_BYTES+FLAG_BYTES
#define LONG_MSG_DATA   LONG_MESSAGE_SIZE-NON_DATA_BYTES

typedef unsigned char byte_t;

#define DEFINE_MESSAGE_STRUCT(name, size) \
typedef struct name##_message_t \
{ \
    byte_t init[INIT_BYTES]; \
    byte_t meta_flags[META_FLAG_BYTES]; \
    byte_t topic_id[TOPIC_BYTES]; \
    byte_t subtopic_id[SUBTOPIC_BYTES]; \
    byte_t data_flags[DATA_FLAG_BYTES]; \
    byte_t data[size]; \
    byte_t reserved[RESERVED_BYTES]; \
} name##_message_t;

DEFINE_MESSAGE_STRUCT(small, SML_MSG_SIZE)
DEFINE_MESSAGE_STRUCT(medium, MED_MSG_SIZE)
DEFINE_MESSAGE_STRUCT(large, LRG_MSG_SIZE)

#endif