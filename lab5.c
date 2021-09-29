
#include <stdio.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"
#include "freertos/timers.h"

void Task1(void *param);
void Task2(void *param);
void Task3(void *param);

static TimerHandle_t Timer1 = NULL;
static TimerHandle_t Timer2 = NULL;

void TimerCallback(TimerHandle_t xTimer);

uint32_t count1 = 1;
uint32_t count2 = 1;

void app_main(void)
{
    Timer1 = xTimerCreate("Auto-reload timer", 2000 / portTICK_PERIOD_MS, pdTRUE, (void *)1, TimerCallback);
    Timer2 = xTimerCreate("Auto-reload timer", 3000 / portTICK_PERIOD_MS, pdTRUE, (void *)2, TimerCallback);

    xTimerStart(Timer1,portMAX_DELAY);
    xTimerStart(Timer2,portMAX_DELAY);
   fflush(stdout);   
}

void TimerCallback(TimerHandle_t xTimer){
    if((uint32_t)pvTimerGetTimerID(xTimer) == 1){
        if(count1 <= 10){
            printf("At: %u, ahihi - The %uth time.\n",xTaskGetTickCount(),count1);
            count1++;
    
            if(count1 > 10){
                xTimerStop(xTimer, 0);
                printf("Timer1 stop here at: %u.\n",xTaskGetTickCount());
            }
        }
    }

    if((uint32_t)pvTimerGetTimerID(xTimer) == 2){
        if(count2 <= 5){
            printf("At: %u, ihaha - The %uth time.\n",xTaskGetTickCount(),count2);
            count2++;
        
            if(count2 > 5){
                xTimerStop(xTimer, 0);
                printf("Timer2 stop here at %u.\n",xTaskGetTickCount());
            }
        }
    }
}


