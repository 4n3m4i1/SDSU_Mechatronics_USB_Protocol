/* 
 * @name USB Mechatronics Protocol SAM4E
 * @author Zix
 * @date Feb 22 2024
 * 
 * @brief Defines Message Handling for USB Messages sent to SAM4E
 */

#include "usb_parse.h"
#include "usb_topics.h"
#include "msg_types.h"

#define BYTE_SIZE 8

/*
 * @brief place appropriate values of message into corresponding field of short_message_t struct
 * @param field - pass in an empty struct of short_message_t and the answers will be "returned" here  
 */
void extract_fields(const byte_t* message, small_message_t* fields) 
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
    for (int i = 0; i < SML_MSG_SIZE; i++) {
        fields->data[i] = message[i + parsed_bytes];
    } parsed_bytes += SML_MSG_SIZE;
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
    int field_value = 0;
    for (int i = 0; i < field_size; i++) {
        const int shift_amount = i * BYTE_SIZE;
        const int shifted_byte = field[i] << shift_amount;
        field_value |= shifted_byte;
    }
    return field_value;
}

/* 
 * @brief Handle flags and call the appropriate robot function
 */
void perform_functionality(const int topic, const int subtopic, const int flags, const byte_t* data)
{
    // handle flags here
    robot_actions[topic][subtopic](data);
}

/* 
 * @brief Pass in raw buffer rcvd from SAM and process fields to invoke appropriate robot response
 */
void HANDLE_MESSAGE(const byte_t* message)
{
    small_message_t fields; extract_fields(message, &fields);
    const int init =        extract_field_value(fields.init,        INIT_BYTES);
    const int meta_flags =  extract_field_value(fields.meta_flags,  META_FLAG_BYTES);
    const int topic =       extract_field_value(fields.topic_id,    TOPIC_BYTES);
    const int subtopic =    extract_field_value(fields.subtopic_id, SUBTOPIC_BYTES);
    const int flags =       extract_field_value(fields.data_flags,  DATA_FLAG_BYTES);
    const int reserved =    extract_field_value(fields.reserved,    RESERVED_BYTES);
    perform_functionality   (topic, subtopic, flags, fields.data);
}