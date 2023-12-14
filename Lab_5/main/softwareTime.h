#ifndef MAIN_SOFTWARETIMER_H_
#define MAIN_SOFTWARETIMER_H_

#include "freertos/FreeRTOSConfig.h"

// Config
#define configUSE_TIMERS 1
// #define  configTIMER_TASK_STACK_DEPTH 1024
#define NO_Timer 3

typedef enum
{
    timer0,
    timer1,
    timer2
} TimerID_t;

#endif /* MAIN_SOFTWARETIMER_H_ */