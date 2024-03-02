/* 
 * @name USB Mechatronics Protocol Generic Parser 
 * @author Zix
 * @date Feb 22 2024
 * 
 * @brief Defines Message Handling for USB Messages sent to Embedded System
 */

#include "mech_usb_protocol.h"
#include <string.h>

#define LENGTH(array) sizeof(array) / sizeof(array[0])
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define POSITIVE(value) MAX(value, 0)

/*
 * @brief place appropriate values of message into corresponding field of either small/medium/large _message_t struct
 * @param field - pass in an empty struct of desired message_t and the answers will be "returned" here  
 */
void extract_fields(const byte_t* message, const int data_size, message_t* fields) 
{
    int parsed_bytes = 0;
    const int field_sizes[] = {TOPIC_BYTES, SUBTOPIC_BYTES, DATA_FLAG_BYTES, data_size};
    byte_t* field_start = (byte_t*)fields;
    for (int i = 0; i < LENGTH(field_sizes); i++) {
        memcpy(&field_start[parsed_bytes], &message[parsed_bytes], field_sizes[i]);
        parsed_bytes += field_sizes[i];
    }
}

/*
 * @brief compose an array value into integer value for comparisons
 * @param field - pass in member of message_t struct here
 */
int extract_field_value(const byte_t* field, const int field_size)
{
    #define BYTE_SIZE 8
    int field_value = 0;
    for (int i = 0; i < field_size; i++) {
        const int shift_amount = i * BYTE_SIZE;
        const int shifted_byte = field[i] << shift_amount;
        field_value |= shifted_byte;
    }
    return field_value;
}

/* 
 * @brief Pass in raw buffer rcvd from SAM and process fields
 */
MsgFields parse_fields(const byte_t* message, const byte_t data_size)
{
    message_t fields;       extract_fields(message, data_size, &fields);
    const int topic =       extract_field_value(fields.topic_id,    TOPIC_BYTES);
    const int subtopic =    extract_field_value(fields.subtopic_id, SUBTOPIC_BYTES);
    const int data_flags =  extract_field_value(fields.data_flags,  DATA_FLAG_BYTES);
    MsgFields parsed_fields = (MsgFields)
    {
        .topic = topic,
        .subtopic = subtopic,
        .data_flags = data_flags,
    };
    memcpy(&parsed_fields.data, &fields.data, data_size);
    return parsed_fields;
}

/* 
 * @brief Handle flags(TODO) and call the appropriate robot function
 */
void perform_functionality(const MsgFields* msg_fields)
{
    robot_actions[msg_fields->topic][msg_fields->subtopic](msg_fields->data);
}

/* 
 * @brief Public Function that will take message from buffer and perform appropriate response.
 * This can be called in Main loop, pass in buffer with received USB message
 */
void HANDLE_MESSAGE(const byte_t* message, const byte_t msg_size)
{
    const MsgFields fields = parse_fields(message, msg_size);
    perform_functionality(&fields);
}