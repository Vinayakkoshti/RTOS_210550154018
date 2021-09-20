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


//define timer
//#define NUM_TIMERS 5
//TimerHandle_t xTimers[ NUM_TIMERS ];
/*
TimerCallbackFunction_t vTimerCallback (xTimers)
{
    //to trigger task3 makin
    vTaskPrioritySet(Handler3,20);
}
*/
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


void Task_3(void *argument)
{
    while(1)
    {   
        vTaskSetTimeOutState( &xTimeOut3 );
        printf("In Task 3 : periodicity : 5000\n");

        while( xTaskCheckForTimeOut( &xTimeOut3, &task3) != pdFALSE) // add time stamp with defined time 
        {
             /* Timed out before the wanted number of bytes were available, exit the
            loop. */
            break;
        }
        
         ulTaskNotifyTake( pdTRUE,task3);
    }
 }

