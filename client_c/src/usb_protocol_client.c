#include "usb_protocol_client.h"
#include "usb_device_handle.h"

#define STARTER_BYTES 5

int sys_kill()
{
    byte_t message[SML_MSG_SIZE] =      {
                                            INIT_BYTE,   EMPTY_MSG,   SYSTEM,      SYSTEM_KILL,
                                            EMPTY_FIELD, EMPTY_FIELD, EMPTY_FIELD, EMPTY_FIELD,
                                            EMPTY_FIELD, EMPTY_FIELD, EMPTY_FIELD, EMPTY_FIELD, 
                                            EMPTY_FIELD, EMPTY_FIELD, EMPTY_FIELD, EMPTY_FIELD,
                                        };
    send_message(message, SML_MSG_SIZE);
}

int move_motors(const byte_t* thrusts)
{
    byte_t message[SML_MSG_SIZE] =      {
                                            INIT_BYTE,   SMALL_MSG,   MOTORS,      MOTOR_MOVE,
                                            EMPTY_FIELD, EMPTY_FIELD, EMPTY_FIELD, EMPTY_FIELD,
                                            EMPTY_FIELD, EMPTY_FIELD, EMPTY_FIELD, EMPTY_FIELD, 
                                            EMPTY_FIELD, EMPTY_FIELD, EMPTY_FIELD, EMPTY_FIELD,
                                        };
    memcpy(message+STARTER_BYTES, thrusts, SML_MSG_SIZE-NON_DATA_BYTES);
    send_message(message, SML_MSG_SIZE);
}

void construct_message(const message_t* message, const int msg_size, byte_t* buffer)
{
    buffer[TOPIC_BYTE_INDEX]     = message->topic_id;
    buffer[SUBTOPIC_BYTE_INDEX]  = message->subtopic_id;
    buffer[DATAFLAGS_BYTE_INDEX] = message->data_flags;
    memcpy(message+STARTER_BYTES, message->data, msg_size-NON_DATA_BYTES);
}