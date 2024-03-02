#include "usb_actions.h"

/* 
 * @brief Packages all robot actions into a jump table
 * The jump table can be edited here --> set_robot_actions <-- to point to desired functions
 * Make sure to use enum values for editing the jump table provided from subtopic headers
 */

/* ********************************************************************************************* */
/* *********************************** Init extern variable ************************************ */

void (*robot_actions[NUM_TOPICS][NUM_SUBTOPICS])(const byte_t* data) = {0};

/* ********************************************************************************************* */
/* ********************************************************************************************* */


/* ********************************************************************************************* */
/* **************************************** Prototypes ***************************************** */
void NOP(const byte_t* data);
void set_robot_actions(void);
void init_robot_actions(void);
/* ********************************************************************************************* */
/* ********************************************************************************************* */


/* PUBLIC API - called from main */
void init_robot_actions(void)
{
    for (int i = 0; i < NUM_TOPICS; i++) {
        for (int j = 0; j < NUM_SUBTOPICS; j++) {
            robot_actions[i][j] = &NOP;
        }
    }
    set_robot_actions();
}

/* ****************************** ************************ ****************************** */
/* ****************************** SET ROBOT FUNCTIONS HERE ****************************** */
/* ****************************** ************************ ****************************** */

void set_robot_actions(void)
{
    robot_actions[SYSTEM][SYSTEM_KILL] = &SYSTEM_KILL_F;
}

/* ****************************** ************************ ****************************** */
/* ****************************** ************************ ****************************** */
/* ****************************** ************************ ****************************** */

void set_robot_action(const byte_t topic, const byte_t subtopic, const void (*action)(const byte_t* data))
{
    robot_actions[topic][subtopic] = action;
}

void NOP(const byte_t* data) {}