#ifndef USB_TIMER_H
#define USB_TIMER_H

void set_timer_callback(const void(*callback)(void), const int frequency);

#endif