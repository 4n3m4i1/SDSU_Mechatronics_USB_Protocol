#include <stdio.h>
#include "usb_protocol.h"

/* 
 * @brief Test USB Protocol
 */

void test_robot_actions(void)
{
    init_robot_actions();
    robot_actions[SYSTEM][SYSTEM_KILL](0);
}

void test_msg_rcv(void)
{
    const byte_t rawMsg[SML_MSG_SIZE] = {
                                        0x01, 0x02, 0x03, 0x04,
                                        0x01, 0x02, 0x03, 0x04,
                                        0x01, 0x02, 0x03, 0x04,
                                        0x01, 0x02, 0x03, 0x04
                                     };
    const ParsedMsg parsedMsg = PARSE_MESSAGE(rawMsg);
    printf("%d\n", parsedMsg.topic);
    printf("%d\n", parsedMsg.subtopic);
    printf("%d\n", parsedMsg.flags);
}

void main(void)
{
    test_robot_actions();
    test_msg_rcv();
}