
#include <stdio.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"

void Task1(void *param);
void Task2(void *param);
void Task3(void *param);
void app_main(void)
{
   xTaskCreate(Task1, "task1", 10234*2, NULL, 0, NULL);
   xTaskCreate(Task2, "task2", 10234*2, NULL, 0, NULL);
   xTaskCreate(Task3, "task3", 10234*2, NULL, 2, NULL);
   vTaskStartScheduler();
   
   fflush(stdout);
   
}

void Task1(void *param){
    while(1){
        printf("At: %u, Hello i'm Task 3.\n",xTaskGetTickCount());
        //vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
    vTaskDelete(NULL);
}

void Task2(void *param){
    while(1){
        printf("At: %u, Hello i'm Task 2.\n",xTaskGetTickCount());
        //vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
    vTaskDelete(NULL);
}

void Task3(void *param){
    while(1){
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        printf("At: %u, Hello i'm Task 1. I have the highest priority.\n",xTaskGetTickCount());
    }
    vTaskDelete(NULL);
}