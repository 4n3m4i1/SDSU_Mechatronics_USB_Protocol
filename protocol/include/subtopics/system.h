#ifndef SYSTEM_H
#define SYSTEM_H

typedef enum system_topic_t
{
    SYSTEM_KILL     = 0x00
} system_topic_t;

void SYSTEM_KILL_F(const unsigned char* data);

#endif