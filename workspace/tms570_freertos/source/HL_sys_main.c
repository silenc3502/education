/** @file HL_sys_main.c 
*   @brief Application main file
*   @date 07-July-2017
*   @version 04.07.00
*
*   This file contains an empty main function,
*   which can be used for the application.
*/

/* 
* Copyright (C) 2009-2016 Texas Instruments Incorporated - www.ti.com  
* 
* 
*  Redistribution and use in source and binary forms, with or without 
*  modification, are permitted provided that the following conditions 
*  are met:
*
*    Redistributions of source code must retain the above copyright 
*    notice, this list of conditions and the following disclaimer.
*
*    Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in the 
*    documentation and/or other materials provided with the   
*    distribution.
*
*    Neither the name of Texas Instruments Incorporated nor the names of
*    its contributors may be used to endorse or promote products derived
*    from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
*  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
*  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/


/* USER CODE BEGIN (0) */
/* USER CODE END */

/* Include Files */

#include "HL_sys_common.h"

/* USER CODE BEGIN (1) */
#include <math.h>
/* USER CODE END */

/** @fn void main(void)
*   @brief Application main function
*   @note This function is empty by default.
*
*   This function is called after startup.
*   The user can use this function to implement the application.
*/

/* USER CODE BEGIN (2) */
#include "HL_sci.h"
#include "HL_can.h"
#include "HL_gio.h"
#include "HL_etpwm.h"
#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"

#include "os_queue.h"
#include "os_semphr.h"
#include "os_task.h"

xTaskHandle task0;
xTaskHandle task1;

QueueHandle_t mutex = NULL;

uint8 rx_data[8];

int accel;
int steering;

int collision;

void sci_display(sciBASE_t *, uint8 *, uint32);
void task0_func(void *);
void task1_func(void *);
void wait(uint32);
/* USER CODE END */

int main(void)
{
/* USER CODE BEGIN (3) */
    sciInit();
    gioInit();
    canInit();
    etpwmInit();
    etpwmStartTBCLK();

    etpwmREG1->CMPA = 1000;
    wait(3333333);
    etpwmREG1->CMPA = 2000;
    wait(3333333);
    etpwmREG2->CMPA = 1500;
    wait(3333333);

    canEnableErrorNotification(canREG1);

    vSemaphoreCreateBinary(mutex);

    if(xTaskCreate(task0_func, "decision", configMINIMAL_STACK_SIZE, NULL, 5, &task0))
        for(;;)
            ;

    if(xTaskCreate(task1_func, "decision", configMINIMAL_STACK_SIZE, NULL, 1, &task1))
        for(;;)
            ;

    vTaskStartScheduler();
/* USER CODE END */

    return 0;
}


/* USER CODE BEGIN (4) */
void task0_func(void *pbParameters)
{
    int i, cnt = 3;

    for(;;)
    {
        if (xSemaphoreTake(mutex, ( TickType_t ) 0x01) == pdTRUE)
        {
            if(rx_data[0])
                sci_display(sciREG1, rx_data, 8);

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
                    for(i = 1; i < 5; i++)
                        accel += (rx_data[i] - 0x30) * pow(10, cnt--);

                    etpwmREG1->CMPA = accel;

                    cnt = 3;
                    accel = 0;

                    xSemaphoreGive(mutex);
                    vTaskDelay(10);
                    break;

                case 13:
                    for(i = 1; i < 5; i++)
                        steering += (rx_data[i] - 0x30) * pow(10, cnt--);

                    etpwmREG2->CMPA = steering;

                    cnt = 3;
                    steering = 0;

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
            if(xSemaphoreTake(mutex, (TickType_t)portMAX_DELAY) == pdTRUE)
            {
                gioSetBit(gioPORTB, 2, 1);
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
            gioSetBit(gioPORTB, 2, 0);
            xSemaphoreGive(mutex);
            vTaskDelay(10);
        }
    }
}

void wait(uint32 delay)
{
    int i;

    for(i = 0; i < delay; i++)
        ;
}

void sci_display(sciBASE_t *sci, uint8 *text, uint32 len)
{
    while (len--)
    {
        // Don't need UART Receive
#if 0
        while ((UART->FLR & 0x4) == 4)
            ;
#endif
        sciSendByte(sciREG1, *text++);
    }
    sciSendByte(sciREG1, '\r');
    sciSendByte(sciREG1, '\n');
}

void canMessageNotification(canBASE_t *node, uint32_t messageBox)
{
    while(!canIsRxMessageArrived(canREG1, canMESSAGE_BOX2))
        ;
    canGetData(canREG1, canMESSAGE_BOX2, (uint8 *)&rx_data[0]);
}
/* USER CODE END */
