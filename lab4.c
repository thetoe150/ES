
#include <stdio.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"
#include "freertos/queue.h"

typedef struct Message {
  char data;
  int funtion_id;
} Message;

void reception_task(void *param);
void functional_Task1(void *param);
void functional_Task2(void *param);
static QueueHandle_t queue;

int queue_len = 5;
void app_main(void)
{
    queue = xQueueCreate(queue_len, sizeof(Message));
   xTaskCreate(reception_task, "reception_task", 10234*2, NULL, 0, NULL);
   xTaskCreate(functional_Task1, "functional_Task1", 10234*2, NULL, 0, NULL);
   xTaskCreate(functional_Task2, "functional_Task2", 10234*2, NULL, 0, NULL);
   fflush(stdout);
   
}

void reception_task(void *param){
    
    printf("At: %u, Hello i'm reception.\n",xTaskGetTickCount());
    Message request;
    request.data = 'u';
    request.funtion_id = 2;
    if(xQueueSend(queue, (void *)&request, 0) == pdTRUE ) 
        printf("At: %u, Hello i'm reception and i post a request.\n",xTaskGetTickCount());
    
    vTaskDelay(2000 / portTICK_PERIOD_MS);

    request.data = 'i';
    request.funtion_id = 1;
    if(xQueueSend(queue, (void *)&request, 0) == pdTRUE ) 
        printf("At: %u, Hello i'm reception and i post a request.\n",xTaskGetTickCount());

    vTaskDelay(5000 / portTICK_PERIOD_MS);

    request.data = 'k';
    request.funtion_id = 2;
    if(xQueueSend(queue, (void *)&request, 0) == pdTRUE ) 
        printf("At: %u, Hello i'm reception and i post a request.\n",xTaskGetTickCount());
    
    vTaskDelete(NULL);
}

void functional_Task1(void *param){
     Message request1;
    while(1){
        if(xQueuePeek(queue, (void *)&request1, 0) == pdTRUE){
            if(request1.funtion_id == 1){
                xQueueReceive(queue, (void *)&request1, 0);
                printf("At: %u, Hello i'm functional_Task1. The message i handle is: %c\n",xTaskGetTickCount(),request1.data);
               
            }
            else printf("At: %u, ERROR: functional_Task1 could not handle the request\n",xTaskGetTickCount());
        }       
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
    vTaskDelete(NULL);
}

void functional_Task2(void *param){
    Message request2;
    while(1){
        if(xQueuePeek(queue, (void *)&request2, 0) == pdTRUE){
            if(request2.funtion_id == 2){
                xQueueReceive(queue, (void *)&request2, 0);
                printf("At: %u, Hello i'm functional_Task2. The message i handle is: %c\n",xTaskGetTickCount(),request2.data);
            }
            else printf("At: %u, ERROR: functional_Task2 could not handle the request\n",xTaskGetTickCount());
        }       
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
    vTaskDelete(NULL);
}