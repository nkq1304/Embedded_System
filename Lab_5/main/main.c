#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include "freertos/FreeRTOS.h"
#include "freertos/FreeRTOSConfig.h"
#include "freertos/timers.h"
#include "softwareTime.h"
#include "freertos/task.h"

TimerHandle_t xTimers[NO_Timer];

TickType_t xTimerPeriod[NO_Timer] = {pdMS_TO_TICKS(10), pdMS_TO_TICKS(2000), pdMS_TO_TICKS(3000)};

uint8_t xMaxTimesTimerExpire[NO_Timer] = {0, 10, 5};
const TimerID_t xTimerID[NO_Timer] = {timer0, timer1, timer2};

static uint32_t Timer1Count = 0;
static uint32_t Timer2Count = 0;
TickType_t xTimeNow;

static void prvTimerCallback(TimerHandle_t xTimer)
{

    BaseType_t timerID = (BaseType_t)pvTimerGetTimerID(xTimer);

    switch (timerID)
    {
    case timer0:
        break;

    case timer1:
        /* Obtain the current tick count. */
        xTimeNow = xTaskGetTickCount();
        /* Output a string to show the time at which the callback was executed. */
        printf("ahihi %ld \n", xTimeNow);
        /* File scope variable. */
        Timer1Count++;

        if (Timer1Count >= xMaxTimesTimerExpire[timer1])
        {
            if (xTimerStop(xTimer, 0) == pdPASS)
            {
                printf("Reached %ld times, Stop timer ahihi successfully\n", Timer1Count);
            }
            else
            {
                printf("Stop timer ahihi failed\n");
            }
        }
        break;

    case timer2:
        /* Obtain the current tick count. */
        xTimeNow = xTaskGetTickCount();
        /* Output a string to show the time at which the callback was executed. */
        printf("ihaha: %ld \n", xTimeNow);
        /* File scope variable. */
        Timer2Count++;

        if (Timer2Count >= xMaxTimesTimerExpire[timer2])
        {
            if (xTimerStop(xTimer, 0) == pdPASS)
            {
                printf("Reached %ld times, Stop timer Ihaha successfully\n", Timer2Count);
            }
            else
            {
                printf("Stop timer ahihi failed\n");
            }
        }
        break;
    default:
        break;
    }
}

void app_main(void)
{

    for (size_t i = 0; i < NO_Timer; i++)
    {
        xTimers[i] = xTimerCreate(
            /* Text name for the software timer - not used by FreeRTOS. */
            "Timer",
            /* The software timer's period in ticks. */
            xTimerPeriod[i],
            /* Setting uxAutoRealod to pdFALSE creates a one-shot software timer. */
            pdTRUE,
            /* This example does not use the timer id. */
            (void *)xTimerID[i],
            /* The callback function to be used by the software timer being created. */
            prvTimerCallback);

        /* Check the software timers were created. */
        if ((xTimers[i] != NULL))
        {
            printf("Timer %d is created \n", i);
            if (xTimerStart(xTimers[i], 0) == pdPASS)
            {
                printf("Timer %d is started \n", i);
            }
        }
    }
    /* As always, this line should not be reached. */
    for (;;)
    {
        vTaskDelay(pdMS_TO_TICKS(1000)); // Keep the loop running or perform other operations here.
    }
}