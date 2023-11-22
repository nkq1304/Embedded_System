#include <stdio.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "freertos/FreeRTOSConfig.h"

struct TaskRequest
{
    char *taskName;
    TickType_t timeout;
};

QueueHandle_t requestQueue;

void receptionTask(void *parameter)
{

    while (1)
    {
        const char *sendRequest = "Task1";
        // Send the request to the queue
        xQueueSend(requestQueue, &sendRequest, portMAX_DELAY);
        vTaskDelay(1000 / portTICK_PERIOD_MS); // Delay for simulation purposes
    }
}

void functionalTask(void *parameter)
{
    const struct TaskRequest *request = (struct TaskRequest *)parameter;
    const char *taskName = request->taskName;
    const TickType_t timeout = request->timeout / portTICK_PERIOD_MS;

    while (1)
    {
        // Check if there is a request in the queue
        char *receivedRequest;
        if (xQueueReceive(requestQueue, &receivedRequest, 0))
        {
            if (taskName == receivedRequest)
            {
                printf("Received request for %s\n", taskName);
                // Process the request, replace this with actual task logic
            }
            else
            {
                printf("Request is not for %s\n", taskName);
            }
        }
        else
        {
            // No request received during the timeout period
            printf("No request received for %s\n", taskName);
        }

        vTaskDelay(timeout); // Delay for simulation purposes
    }
}

struct TaskRequest task1Request = {"Task1", 5000};
struct TaskRequest task2Request = {"Task2", 2000};

void app_main()
{
    requestQueue = xQueueCreate(10, sizeof(char *));

    // Create the reception task
    xTaskCreate(receptionTask, "ReceptionTask", 10000, NULL, 1, NULL);

    // Create functional tasks (you can have as many as needed)
    xTaskCreate(functionalTask, "FunctionalTask1", 10000, &task1Request, 1, NULL);
    xTaskCreate(functionalTask, "FunctionalTask2", 10000, &task2Request, 1, NULL);
}