#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"


//Task Handlers
TaskHandle_t Handler1,Handler2,Handler3,Handler4,Handler5;

//Task declaration
void Task_1(void *argument);
void Task_2(void *argument);
void Task_3(void *argument);
void Task_4(void *argument);
void Task_5(void *argument);


//Task Periodicity
TickType_t task1=1000 / portTICK_PERIOD_MS;
TickType_t task2=2000 / portTICK_PERIOD_MS;
TickType_t task3=5000 / portTICK_PERIOD_MS;

TickType_t task4=1000 / portTICK_PERIOD_MS;
TickType_t task5=1000 / portTICK_PERIOD_MS; 


//task start time stamp variable
TimeOut_t xTimeOut1;
TimeOut_t xTimeOut2;
TimeOut_t xTimeOut3;
TimeOut_t xTimeOut4;
TimeOut_t xTimeOut5;


QueueHandle_t xQueue1;
UBaseType_t MAX_length = 5,y;

#define MAX sizeof(int)

int SendBuff[MAX],RecieveBuff[MAX];

int send = 20; 
void app_main(void)
{
    xQueue1 = xQueueCreate( MAX_length,sizeof(int));
    
    if(xQueue1==NULL)
    {
        printf("Failed to create queue!!!\n");
    }

    xTaskCreate(Task_1,"TASK1",2048,NULL,10,&Handler1);
    xTaskCreate(Task_2,"TASK2",2048,NULL,10,&Handler2);
    xTaskCreate(Task_3,"TASK3",2048,NULL,10,&Handler3);
    xTaskCreate(Task_4,"TASK4",2048,NULL,10,&Handler4);
    xTaskCreate(Task_5,"TASK5",2048,NULL,10,&Handler5);
    
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

void Task_4(void *argument)
{
    while(1)
    {
        vTaskSetTimeOutState( &xTimeOut4 );

        printf("In task 4 : sending int data(20) over queue\n");
       // send = send + 1;
        
        if( xQueueSend(xQueue1,(int*)&send,(TickType_t)10) != pdPASS )
        {
            printf("Failed to post the message, even after 10 ticks.\n");
        }



        while( xTaskCheckForTimeOut( &xTimeOut4, &task4) != pdFALSE) // add time stamp with defined time 
        {
             /* Timed out before the wanted number of bytes were available, exit the
            loop. */
            break;
        }
        
         ulTaskNotifyTake( pdTRUE,task4);
    
    }
}

void Task_5(void *argument)
{
    while(1)
    {

         vTaskSetTimeOutState( &xTimeOut5 );

        if( xQueueReceive( xQueue1,(int *)RecieveBuff,(TickType_t)10) != pdPASS )
        {
            printf("Failed to Receive the message, even after 10 ticks.\n");
        }      
        else{
            printf("In task 5 got the msg from queue : %d\n",RecieveBuff[0]);
        }

         while( xTaskCheckForTimeOut( &xTimeOut5, &task5) != pdFALSE) // add time stamp with defined time 
        {
             /* Timed out before the wanted number of bytes were available, exit the
            loop. */
            break;
        }
        
         ulTaskNotifyTake( pdTRUE,task5);


    }
 }