#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "freertos/timers.h"

//Task Handlers
TaskHandle_t Handler1,Handler2,Handler3;

//Task declaration
void Task_1(void *argument);
void Task_2(void *argument);
void Task_3(void *argument);


//Task Periodicity
TickType_t task1=1000 / portTICK_PERIOD_MS;
TickType_t task2=2000 / portTICK_PERIOD_MS;
TickType_t task3=5000 / portTICK_PERIOD_MS;

TickType_t tim=10000 / portTICK_PERIOD_MS;

//task start time stamp variable
TimeOut_t xTimeOut1;
TimeOut_t xTimeOut2;
TimeOut_t xTimeOut3;

void *const timer_Id;
TimerHandle_t my_timer_handle;

void myTimerCallback(TimerHandle_t xTimer)
{
    printf("Inside OneShot Timer callback\n");
}


void app_main(void)
{
/*
    xTimers[0] = xTimerCreate("Timer",tim,pdFALSE,( void * ) 0,vTimerCallback(TimerHandle_t*));
    xTimerStart( xTimers[0 ], 0 );
*/
    xTaskCreate(Task_1,"TASK1",2048,NULL,10,&Handler1);
    xTaskCreate(Task_2,"TASK2",2048,NULL,10,&Handler2);
    xTaskCreate(Task_3,"TASK3",2048,NULL,10,&Handler3);  
}
void Task_1(void *argument)
{
    while(1)
    {  
        vTaskSetTimeOutState( &xTimeOut1 );
        printf("In Task 1 : periodicity : 1000\n");

        while( xTaskCheckForTimeOut( &xTimeOut1, &task1 ) != pdFALSE) // add time stamp with defined time 
        {
             /* Timed out before the wanted number of bytes were available, exit the
            loop. */
            break;
        }

         ulTaskNotifyTake( pdTRUE,task1);
    }
 }

void Task_2(void *argument)
{
    while(1)
    {   
        vTaskSetTimeOutState( &xTimeOut2 );
        printf("In Task 2 : periodicity : 2000\n");

        while( xTaskCheckForTimeOut( &xTimeOut2, &task2) != pdFALSE) // add time stamp with defined time 
        {
             /* Timed out before the wanted number of bytes were available, exit the
            loop. */
            break;
        }
        
         ulTaskNotifyTake( pdTRUE,task2);
    }
 }

void *const timer_id;
TimerHandle_t timer_handle;

void Task_3(void *argument)
{
    printf("Created task 3, Periodicity = 5000ms\n");
    my_timer_handle = xTimerCreate("my_timer", (10000 / portTICK_PERIOD_MS),pdFALSE,timer_Id,myTimerCallback);

    xTimerStart(my_timer_handle, 1);
    while (1)
    {
        printf("task3\n");
        vTaskDelay(5000 / portTICK_PERIOD_MS);
    }
}