#include "stm32f4xx.h"
#include "freeRTOS.h"
#include "task.h"

void LEDInitialize(void){
	
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOH, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	
	GPIO_Init(GPIOH,&GPIO_InitStructure);
}

#define LED1_TASK_PRIO             (tskIDLE_PRIORITY+1)
#define LED2_TASK_PRIO             (tskIDLE_PRIORITY+2)
 
 
 
void LED1_Toggle_Task(void *pvParameters);
void LED2_Toggle_Task(void *pvParameters);

int main(void){
	
	LEDInitialize();
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);               //0,1,2,3,4
	
	xTaskCreate(LED1_Toggle_Task, "LED1", configMINIMAL_STACK_SIZE, NULL, LED1_TASK_PRIO, NULL);
	xTaskCreate(LED2_Toggle_Task, "LED2", configMINIMAL_STACK_SIZE, NULL, LED2_TASK_PRIO, NULL);
	
	/* Start the scheduler. */
	vTaskStartScheduler();

	/* If all is well, the scheduler will now be running, and the following line
	will never be reached.  If the following line does execute, then there was
	insufficient FreeRTOS heap memory available for the idle and/or timer tasks
	to be created.  See the memory management section on the FreeRTOS web site
	for more details. */
	for( ;; );
}

void LED1_Toggle_Task(void * pvParameters)
{
    unsigned int n_iCnt = 0;
    for(;;)
    {
        if((n_iCnt % 2) == 0)
        {
            GPIO_SetBits(GPIOH,GPIO_Pin_2);
        }
        else if((n_iCnt % 2) == 1)
        {
            GPIO_ResetBits(GPIOH,GPIO_Pin_2);
        }
        //printf("LED1 CNT:%d\r\n",n_iCnt);
        //vTaskDelay(500);
        vTaskDelay(1000);
        n_iCnt++;
    }
}
 
void LED2_Toggle_Task(void * pvParameters)
{
    unsigned int n_iCnt = 0;
    for(;;)
    {
        if((n_iCnt % 2) == 0)
        {
            GPIO_SetBits(GPIOH,GPIO_Pin_3);
        }
        else if((n_iCnt % 2) == 1)
        {
            GPIO_ResetBits(GPIOH,GPIO_Pin_3);
        }
            
        vTaskDelay(500);
        n_iCnt++;
    }
}
