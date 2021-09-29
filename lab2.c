
#include <stdio.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"
#include "driver/gpio.h"

#define BUTTON GPIO_NUM_17

void Task1_printID(void *param);
void Task2_printESP(void *param);
void app_main(void)
{
    if(gpio_reset_pin(BUTTON) == ESP_OK) ;
    if(gpio_set_direction(BUTTON, GPIO_MODE_INPUT) == ESP_OK);
   xTaskCreate(Task1_printID, "task1", 10234*2, NULL, 2, NULL);
   xTaskCreate(Task2_printESP, "task2", 10234*2, NULL, 2, NULL);
   fflush(stdout);
   
}

void Task1_printID(void *param){
    while(1){
        printf("My ID is: 1752443\n");
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
    vTaskDelete(NULL);
}

void Task2_printESP(void *param){
    //vTaskDelay(7000 / portTICK_PERIOD_MS);
    while(1){
        if(gpio_get_level(BUTTON)) 
            printf("ESP32\n");
    }

    vTaskDelete(NULL);
}