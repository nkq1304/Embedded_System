/* Hello World Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include <inttypes.h>
#include "sdkconfig.h"

// Libraries needed for the use of FreeRTOS.
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_chip_info.h"
#include "esp_system.h"
#include "esp_spi_flash.h"
#include "esp_flash.h"

// Library needed for GPIO functions.
#include "driver/gpio.h"

// Macro defining the GPIO for our input button.
#define BUTTON_GPIO 18

// This function prints out my student ID every 1 second.
void printStudentID(void* parameter)
{
    while (1)
    {
        printf("2014334 - 2012348\n");
        printf("Nguyen Kim Quynh - Nguyen Phan Anh Tuan\n");
        // Wait for 1s.
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }

    // Delete the task. This will never be reached.
    vTaskDelete(NULL);
}

void setup_gpio(void){
    // Select pin 0 as a GPIO pin.
    esp_rom_gpio_pad_select_gpio(BUTTON_GPIO);
    // Specify that the pin is an input pin.
    gpio_set_direction(BUTTON_GPIO, GPIO_MODE_INPUT);
    // Specify the pull mode as pulldown.
    gpio_set_pull_mode(BUTTON_GPIO, GPIO_PULLDOWN_ONLY);
}

// This function prints "ESP32" whenever the button connected
// to pin 0 is pressed.
void printESP32(void* parameter)
{
    unsigned int flag = 0;
    while (1)
    {
        if(gpio_get_level(BUTTON_GPIO) != 0){
            flag = 0;
            vTaskDelay(18/portTICK_PERIOD_MS);
        }
        if(gpio_get_level(BUTTON_GPIO) == 0){
            vTaskDelay(27/portTICK_PERIOD_MS);

            if(gpio_get_level(BUTTON_GPIO) == 0){
                if(flag ==0){
                    printf("ESP32\n");
                    flag=1;
                }
            }
        }
    }
    // Delete the task. This will never be reached.
    vTaskDelete(NULL);
}

void app_main(void)
{
    setup_gpio();
    // Create the two tasks. printESP32 has a higher priority.
    xTaskCreate(&printStudentID, "printStudentID", 1024*2, (void*) 0, tskIDLE_PRIORITY + 1, NULL);
    xTaskCreate(&printESP32, "printESP32", 1024*2, (void*) 0, tskIDLE_PRIORITY + 2, NULL);
}