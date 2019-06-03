#include "HL_sys_common.h"
#include <math.h>

#include "HL_sci.h"
#include "HL_system.h"
#include "HL_gio.h"
#include "HL_can.h"
#include "HL_etpwm.h"
#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"

#include "os_queue.h"
#include "os_semphr.h"
#include "os_task.h"

xTaskHandle task0;
xTaskHandle task1;

QueueHandle_t mutex=NULL;

uint8 rx_data[8];
uint8_t tx_data[8]={3,3,3,3,7,7,7,7};

int accel;
int steering;
int collision;

void sci_display(sciBASE_t *, uint8 *, uint32);
void task0_func(void *);
void task1_func(void *);
void wait(uint32);



main(void)
{
    int i, j;

    sciInit();
    gioInit();
    canInit();
    etpwmInit();
    etpwmStartTBCLK();

    //_enable_IRQ_interrupt_();

    for(i = 0; i < 100; i++)
    {
        for(j = 0; j < 1000000; j++)
            ;
        canTransmit(canREG1, canMESSAGE_BOX1, (const uint8 *)&tx_data[0]);
    }







    etpwmREG1->CMPA=1000;
    wait(33333333);
    etpwmREG1->CMPA=2000;
    wait(33333333);
    etpwmREG2->CMPA=1500;
    wait(33333333);

    canEnableErrorNotification(canREG1);
    vSemaphoreCreateBinary(mutex);

    if(xTaskCreate(task0_func, "decision", configMINIMAL_STACK_SIZE,NULL,5,&task0)!=pdTRUE)
    {
        for(;;)
            ;
    }

    if(xTaskCreate(task1_func, "collision_detect",configMINIMAL_STACK_SIZE, NULL, 1, &task1)!=pdTRUE)
    {
        for(;;)
            ;
    }

    vTaskStartScheduler();


    return 0;
}

void task0_func(void *pbParameters)
{
    int i, cnt=3;


    for(;;)
    {
        if(xSemaphoreTake(mutex, (TickType_t)0x01)==pdTRUE)
        {
#if 1
            if(canIsRxMessageArrived(canREG1,canMESSAGE_BOX2))
                canGetData(canREG1, canMESSAGE_BOX2, (uint8 *)&rx_data[0]);
#endif


#if 0
            if(rx_data[0])
                sci_display(sciREG1, rx_data, 8);
#endif

            switch(rx_data[0])
            {
            case 1:
                gioToggleBit(gioPORTA, 4);

                xSemaphoreGive(mutex);
                vTaskDelay(10);
                break;

            case 6:
                collision = true;
                break;
            case 12:
                for(i=1; i<5;i++)
                    accel += rx_data[i]*pow(10, cnt--);

                etpwmREG1->CMPA=accel;

                cnt=3;
                accel=0;
                xSemaphoreGive(mutex);
                vTaskDelay(10);
                break;
            case 13:
                for(i=1;i<5;i++)
                    steering +=(rx_data[i])*pow(10,cnt--);
                etpwmREG2->CMPA=steering;
                cnt=3;
                steering=0;

                xSemaphoreGive(mutex);
                vTaskDelay(10);
                break;

            default:
                xSemaphoreGive(mutex);
                vTaskDelay(10);
                break;


            }
        }

        xSemaphoreGive(mutex);
        vTaskDelay(10);
    }
}

void task1_func(void *pbParameters)
{
    for(;;)
    {
        if(collision)
        {
            if(xSemaphoreTake(mutex, (TickType_t)portMAX_DELAY)==pdTRUE)
            {
                //gioSetBit(gioPORTB,2,1);
                etpwmREG3->CMPA=2300;
                vTaskDelay(10);

            }
            else
            {
                xSemaphoreGive(mutex);
                vTaskDelay(10);

            }
        }
        else
        {
            //gioSetBit(gioPORTB,2,0);
            etpwmREG3->CMPA=0;
            xSemaphoreGive(mutex);
            vTaskDelay(10);

        }
    }

}

void sci_display(sciBASE_t *sci, uint8 *text, uint32 len)
{
    while(len--)
    {

        // no need UART Receive
#if 1
        while((sciREG1->FLR & 0x4) == 4)
            ;

#endif
        sciSendByte(sciREG1, *text++);
    }
    sciSendByte(sciREG1, '\r');
    sciSendByte(sciREG1, '\n');
}

void wait (uint32 delay)
{
    int i;
    for(i=0;i<delay;i++)
        ;
}

#if 0
void canMessageNotification(canBASE_t *node, uint32_t messageBox)
{
    while(!canIsRxMessageArrived(canREG1,canMESSAGE_BOX2))
        ;
    canGetData(canREG1, canMESSAGE_BOX2, (uint8 *)&rx_data[0]);
}
#endif
