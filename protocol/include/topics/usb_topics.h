#ifndef USB_TOPICS_H
#define USB_TOPICS_H

#define NUM_TOPICS    256
#define NUM_SUBTOPICS 256

#include "system.h"
#include "power.h"
#include "motor.h"

typedef unsigned char byte_t;

typedef enum device_topic_t
{
    SYSTEM          = 0x00,
    RESERVED        = 0x01,
    POWER           = 0x02,
    MOTORS          = 0x10
} device_topic_t;

/* 
 * @brief Handler functions will go here. To perform specific function, deference this array at the appropriate topic/subtopic index
 *        The data field should be passed as a parameter to these functions
 */
extern void (*robot_actions[NUM_TOPICS][NUM_SUBTOPICS])(const byte_t* data);

void init_robot_actions();

#endif