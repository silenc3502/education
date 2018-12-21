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
#include <string.h>
#include <stdio.h>
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
#include "HL_sys_core.h"
#include "HL_system.h"
#include "HL_etpwm.h"
#include "HL_gio.h"
#include "HL_can.h"
#include "HL_esm.h"

#define DCNT            8
#define DSIZE           8

uint32 cnt = 0;
uint32 err = 0;
uint32 tx_done = 0;

uint8_t tx_data[DCNT] = {3, 3, 3, 3, 7, 7, 7, 7};
uint8_t rx_data[DCNT];
/* USER CODE END */

int main(void)
{
/* USER CODE BEGIN (3) */
    int tmp = 0, cnt = 3, i, j;

    gioInit();
    etpwmInit();
    canInit();

    etpwmStartTBCLK();
    canEnableErrorNotification(canREG1);

    for(i=0;i<1000;i++)
    {
        for(j=0;j<300000;j++)
                ;

        canTransmit(canREG1, canMESSAGE_BOX1, (const uint8*)&tx_data[0]);
    }

    _enable_interrupt_();

    for(;;)
    {
#if 0
        while(!canIsRxMessageArrived(canREG1, canMESSAGE_BOX2))
            ;
        canGetData(canREG1, canMESSAGE_BOX2, (uint8 *)&rx_data[0]);
#endif

        switch(rx_data[0] - 48)
        {
            case 7:
                for(i = 1; i < 5; i++)
                {
                    tmp += (rx_data[i] - 48) * pow(10, cnt--);
                    printf("rx_data[%d] = 0x%x\n", i, rx_data[i]);
                }

                etpwmREG1->CMPA = tmp;
                break;
        }

        memset(rx_data, 0, sizeof(rx_data));
        cnt = 3;
        tmp = 0;
    }
/* USER CODE END */

    return 0;
}


/* USER CODE BEGIN (4) */
#if 1
void canMessageNotification(canBASE_t *node, uint32_t messageBox)
{
    if(node == canREG1)
    {
        while(!canIsRxMessageArrived(canREG1, canMESSAGE_BOX2))
            ;
        canGetData(canREG1, canMESSAGE_BOX2, (uint8 *)&rx_data[0]);
    }
}
#endif
/* USER CODE END */
