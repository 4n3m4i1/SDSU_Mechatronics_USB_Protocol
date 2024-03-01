#include "usb_topics.h"

void (*robot_actions[NUM_TOPICS][NUM_SUBTOPICS])(const byte_t* data) = {0};

void NOP(const byte_t* data) {};

void set_robot_actions()
{
    robot_actions[SYSTEM][SYSTEM_KILL] = &SYSTEM_KILL_F;
}

void init_robot_actions()
{
    for (int i = 0; i < NUM_TOPICS; i++) {
        for (int j = 0; j < NUM_SUBTOPICS; j++) {
            robot_actions[i][j] = &NOP;
        }
    }
    set_robot_actions();
}

