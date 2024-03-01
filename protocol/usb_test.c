#include <stdio.h>
#include "usb_protocol.h"

/* 
 * @brief Test USB Protocol
 */

/* ****************************** ************************* *********************************** */
/* ****************************** ************************* *********************************** */
/* ****************************** Quick Unit Test Framework *********************************** */
/* ****************************** ************************* *********************************** */
/* ****************************** ************************* *********************************** */

#include <stdio.h>
#include <stdbool.h>

typedef bool (*TestFunc)(void);

typedef struct Test {
    const char* name;
    TestFunc func;
} Test;

Test tests[100];
int numTests = 0;

#define TEST(name) \
    bool name##_test(void); \
    __attribute__((constructor)) \
    bool register_##name##_test(void) { \
        tests[numTests++] = (Test){#name, name##_test}; \
    } \
    bool name##_test(void)

void run_tests(void) 
{
    int numPassed = 0;
    for (int i = 0; i < numTests; i++) 
    {
        printf("Running test: %s\n", tests[i].name);
        const bool passed = tests[i].func();
        if (passed) 
        {
            printf("Test %s passed.\n\n", tests[i].name);
            numPassed++;
        }
        else
        {
            printf("Test %s failed.\n\n", tests[i].name);
        }
    }
    printf("%d/%d tests passed.\n", numPassed, numTests);
}

#define ASSERT_EQ(actual, expected) \
    if (!(expected==actual)) { \
        printf("Assertion failed, Was expecting value %d but was passed %d\n", expected, actual); \
        return false; \
    } \
    else { \
        printf("Assertion Passed, Was expecting value %d and got %d\n", expected, actual); \
    }\

/* ****************************** ************************* *********************************** */
/* ****************************** ************************* *********************************** */
/* ********************************************************************************************** */


TEST(test_robot_actions) 
{
    init_robot_actions();
    const byte_t data[16] = {0};
    robot_actions[SYSTEM][SYSTEM_KILL](data);
    return true;
}

void MOTOR_MOVE_F(const byte_t* data)
{
    for (int i = 0; i < 8; i++) 
    {
        ASSERT_EQ(i, data[i]);
    }
}

TEST(test_small_message_send) 
{
    init_robot_actions();
    set_robot_action(MOTORS, MOTOR_MOVE, &MOTOR_MOVE_F);
    const MetaFlags meta_flags = (MetaFlags){.MSG_SIZE = SMALL_MSG};
    const byte_t flags_byte = COMPOSE_META_FLAGS(&meta_flags);
    const byte_t message[16] = {INIT_BYTE, flags_byte, MOTORS, MOTOR_MOVE, EMPTY_FIELD,
                                0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
                                EMPTY_FIELD, EMPTY_FIELD, EMPTY_FIELD};
    HANDLE_MESSAGE(message);
    return true;
}

void MOTOR_MOVE_F_24(const byte_t* data)
{
    for (int i = 0; i < 24; i++) 
    {
        ASSERT_EQ(i, data[i]);
    }
}

TEST(test_medium_message_send) 
{
    init_robot_actions();
    set_robot_action(MOTORS, MOTOR_MOVE, &MOTOR_MOVE_F_24);
    const MetaFlags meta_flags = (MetaFlags){.MSG_SIZE = MEDIUM_MSG};
    const byte_t flags_byte = COMPOSE_META_FLAGS(&meta_flags);
    const byte_t message[32] = {INIT_BYTE, flags_byte, MOTORS, MOTOR_MOVE, EMPTY_FIELD,
                                0, 1, 2, 3, 4, 5, 6, 7, 8, 
                                9, 10, 11, 12, 13, 14, 15, 16, 
                                17, 18, 19, 20, 21, 22, 23,
                                EMPTY_FIELD, EMPTY_FIELD, EMPTY_FIELD};
    HANDLE_MESSAGE(message);
    return true;
}

TEST(test_small_msg_rcv) 
{
    const byte_t rawMsg[SML_MSG_SIZE] = 
    {
        0xAB, 0x01, 0x01, 0x04,
        0x01, 0x02, 0x03, 0x04,
        0x01, 0x02, 0x03, 0x04,
        0x01, 0x02, 0x03, 0x04,
    };
    const MsgHeader header = parse_header(rawMsg);
    ASSERT_EQ(header.msg_size, 16); 
    const MsgFields fields = parse_fields(rawMsg, header.msg_size);
    ASSERT_EQ(fields.topic, 0x01);
    ASSERT_EQ(fields.subtopic, 0x04);
    ASSERT_EQ(fields.data_flags, 0x01);
    return true;
}

TEST(test_large_msg_rcv) 
{
    const byte_t rawMsg[MED_MSG_SIZE] = 
    {
        0xAB, 0x02, 0x02, 0x04,
        0x01, 0x02, 0x03, 0x04,
        0x01, 0x02, 0x03, 0x04,
        0x01, 0x02, 0x03, 0x04,
        0xAB, 0x02, 0x02, 0x04,
        0x01, 0x02, 0x03, 0x04,
        0x01, 0x02, 0x03, 0x04,
        0x01, 0x02, 0x03, 0x04
    };
    const MsgHeader header = parse_header(rawMsg);
    ASSERT_EQ(header.msg_size, 32);
    const MsgFields fields = parse_fields(rawMsg, header.msg_size);
    ASSERT_EQ(fields.topic, 0x02);
    ASSERT_EQ(fields.subtopic, 0x04);
    ASSERT_EQ(fields.data_flags, 0x01);
    return true;
}

TEST(valid_msg_rcv) 
{
    const byte_t rawMsg[SML_MSG_SIZE] = 
    {
        0xAB, 0x02, 0x02, 0x04,
        0x01, 0x02, 0x03, 0x04,
        0x01, 0x02, 0x03, 0x04,
        0x01, 0x02, 0x03, 0x04,
    };
    const MsgHeader header = parse_header(rawMsg);
    ASSERT_EQ(header.init_valid, true);
    return true;
}

TEST(invalid_msg_rcv) 
{
    const byte_t rawMsg[SML_MSG_SIZE] = 
    {
        0xBB, 0x02, 0x02, 0x04,
        0x01, 0x02, 0x03, 0x04,
        0x01, 0x02, 0x03, 0x04,
        0x01, 0x02, 0x03, 0x04,
    };
    const MsgHeader header = parse_header(rawMsg);
    ASSERT_EQ(header.init_valid, false);
    return true;
}

void main(void) 
{
    run_tests();
}