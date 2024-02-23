/* 
 * @name USB Mechatronics Protocol SAM4E
 * @author Zix
 * @date Feb 22 2024
 * 
 * @brief Defines Message Handling for USB Messages sent to SAM4E
 */

#include "usb_mech.h"

#define BYTE_SIZE 8

/* 
 * @brief Handler functions will go here. To perform specific function, deference this array at the appropriate topic/subtopic index
 *        The data field should be passed as a parameter to these functions
 */
const void (*robot_action[NUM_TOPICS][NUM_SUBTOPICS])(const byte_t* data) =
{
//     {topic1_subtopic1, topic1_subtopic2},
//     {topic2_subtopic1, topic2_subtopic2}
};

/*
 * @brief place appropriate values of message into corresponding field of long_message_t struct
 * @param field - pass in an empty struct of long_message_t and the answers will be "returned" here  
 */
void extract_fields(const byte_t* message, long_message_t* fields) 
{
    for (int i = 0; i < TOPIC_BYTES; i++) {
        fields->topic_id[i] = message[i];
    }
    for (int i = 0; i < SUBTOPIC_BYTES; i++) {
        fields->subtopic_id[i] = message[TOPIC_BYTES + i];
    }
    for (int i = 0; i < FLAG_BYTES; i++) {
        fields->flags[i] = message[TOPIC_BYTES + SUBTOPIC_BYTES + i];
    }
    for (int i = 0; i < LONG_MSG_DATA; i++) {
        fields->data[i] = message[TOPIC_BYTES + SUBTOPIC_BYTES + FLAG_BYTES + i];
    }
    for (int i = 0; i < RESERVED_BYTES; i++) {
        fields->reserved[i] = message[TOPIC_BYTES + SUBTOPIC_BYTES + FLAG_BYTES + LONG_MSG_DATA + i];
    }
}

/*
 * @brief compose an array value into integer value for comparisons
 * @param field - pass in member of long_message_t struct here
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
    robot_action[topic][subtopic](data);
}

/* 
 * @brief Pass in raw buffer rcvd from SAM and process fields to invoke appropriate robot response
 */
void HANDLE_MESSAGE(const byte_t* message)
{
    long_message_t fields;
    extract_fields(message, &fields);
    const int topic = extract_field_value(fields.topic_id, TOPIC_BYTES);
    const int subtopic = extract_field_value(fields.subtopic_id, SUBTOPIC_BYTES);
    const int flags = extract_field_value(fields.flags, FLAG_BYTES);
    const int reserved = extract_field_value(fields.reserved, RESERVED_BYTES);
    perform_functionality(topic, subtopic, flags, fields.data);
}