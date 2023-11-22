#include <stdio.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/FreeRTOSConfig.h"

struct TaskParams
{
    char *printString;
    TickType_t duration;
    TickType_t delay;
};

volatile uint32_t ulIdleCycleCount = 0UL;

void vApplicationIdleHook(void)
{
    ulIdleCycleCount++;
    printf("Idle Hook is working\n");
}

void Task3(void *pvParameters)
{
    while (1)
    {
        printf("Task 3 is running\n");
        // taskYIELD();
    }
}

void vTaskFunction(void *pvParameters)
{
    struct TaskParams *params = (struct TaskParams *)pvParameters;
    const char *printString = params->printString;
    const TickType_t duration = params->duration / portTICK_PERIOD_MS;
    const TickType_t delay = params->delay / portTICK_PERIOD_MS;

    if (delay == 0)
    {
        while (1)
        {
            printf("%s\n", printString);
        }
    }
    else
    {
        TickType_t startTime = xTaskGetTickCount();
        while (1)
        {
            if (xTaskGetTickCount() - startTime > duration)
            {
                vTaskDelay(delay);

                startTime = xTaskGetTickCount();
            }
            else
            {
                printf("%s\n", printString);
            }
        }
    }

    vTaskDelete(NULL);
}

struct TaskParams task1Params = {"Task 1 is running", 100, 3000};
struct TaskParams task2Params = {"Task 2 is running", 500, 0};

void app_main()
{
    // xTaskCreate(Task3, "Task 3", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL);
    xTaskCreate(vTaskFunction, "Task 2", configMINIMAL_STACK_SIZE, &task2Params, tskIDLE_PRIORITY, NULL);
    xTaskCreate(vTaskFunction, "Task 1", configMINIMAL_STACK_SIZE, &task1Params, tskIDLE_PRIORITY - 1, NULL);
}