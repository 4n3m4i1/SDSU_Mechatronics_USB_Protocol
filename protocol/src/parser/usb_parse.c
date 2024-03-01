/* 
 * @name USB Mechatronics Protocol SAM4E
 * @author Zix
 * @date Feb 22 2024
 * 
 * @brief Defines Message Handling for USB Messages sent to SAM4E
 */

#include "usb_protocol.h"
#include <string.h>

#define FIRST_BYTE(message)  message[0]
#define SECOND_BYTE(message) message[1]

/*
 * @brief place appropriate values of message into corresponding field of either small/medium/large _message_t struct
 * @param field - pass in an empty struct of desired message_t and the answers will be "returned" here  
 */
void extract_fields(const byte_t* message, const int data_size, message_t* fields) 
{
    int parsed_bytes = 0;
    for (int i = 0; i < INIT_BYTES; i++) {
        fields->init[i] = message[i + parsed_bytes];
    } parsed_bytes += INIT_BYTES;
    for (int i = 0; i < META_FLAG_BYTES; i++) {
        fields->meta_flags[i] = message[i + parsed_bytes];
    } parsed_bytes += META_FLAG_BYTES;
    for (int i = 0; i < TOPIC_BYTES; i++) {
        fields->topic_id[i] = message[i + parsed_bytes];
    } parsed_bytes += TOPIC_BYTES;
    for (int i = 0; i < SUBTOPIC_BYTES; i++) {
        fields->subtopic_id[i] = message[i + parsed_bytes];
    } parsed_bytes += SUBTOPIC_BYTES;
    for (int i = 0; i < DATA_FLAG_BYTES; i++) {
        fields->data_flags[i] = message[i + parsed_bytes];
    } parsed_bytes += DATA_FLAG_BYTES;
    for (int i = 0; i < data_size; i++) {
        fields->data[i] = message[i + parsed_bytes];
    } parsed_bytes += data_size;
    for (int i = 0; i < RESERVED_BYTES; i++) {
        fields->reserved[i] = message[i + parsed_bytes];
    }
}

/*
 * @brief compose an array value into integer value for comparisons
 * @param field - pass in member of short_message_t struct here
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

MsgHeader parse_header(const byte_t* message)
{
    const byte_t init_valid = FIRST_BYTE(message) == INIT_BYTE;
    const MetaFlags metaFlags = EXTRACT_META_FLAGS(SECOND_BYTE(message));
    return (MsgHeader)
    {
        .init_valid = init_valid,
        .msg_size   = metaFlags.MSG_SIZE
    };
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
 * @brief Handle flags and call the appropriate robot function
 */
void perform_functionality(const MsgFields* msg_fields, const byte_t num_data_bytes)
{
    // handle_flags(msg_fields->flags);
    robot_actions[msg_fields->topic][msg_fields->subtopic](msg_fields->data);
}

void HANDLE_MESSAGE(const byte_t* message)
{
    const MsgHeader header = parse_header(message);
    if (!header.init_valid) return;
    const byte_t num_data_bytes = header.msg_size - NON_DATA_BYTES;
    const MsgFields fields = parse_fields(message, num_data_bytes);
    perform_functionality(&fields, num_data_bytes);
}