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
/* USER CODE END */

/** @fn void main(void)
*   @brief Application main function
*   @note This function is empty by default.
*
*   This function is called after startup.
*   The user can use this function to implement the application.
*/

/* USER CODE BEGIN (2) */
#include "HL_system.h"
#include "HL_gio.h"
#include "HL_sci.h"
/* USER CODE END */

#define TSIZE       12

uint8 text[TSIZE] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '\n', '\r'};

void sci_display(sciBASE_t *sci, uint8 *text, uint32 len);
// It's not real time
void wait(uint32 time);

#define UART        sciREG1

int main(void)
{
/* USER CODE BEGIN (3) */
    gioInit();
    gioSetDirection(gioPORTA, 0xffffffff);
    gioSetPort(gioPORTA, 0xffffffff);

    sciInit();

    for(;;)
    {
        sci_display(UART, &text[0], TSIZE);
    }
/* USER CODE END */

    return 0;
}

/* USER CODE BEGIN (4) */
void sci_display(sciBASE_t *sci, uint8 *text, uint32 len)
{
    while(len--)
    {
        if(*text == '3')
        {
            gioSetBit(gioPORTA, 2, 0);
            gioSetBit(gioPORTA, 1, 0);
            gioSetBit(gioPORTA, 0, 1);
        }
        else if(*text == '6')
        {
            gioSetBit(gioPORTA, 2, 0);
            gioSetBit(gioPORTA, 1, 1);
            gioSetBit(gioPORTA, 0, 0);
        }
        else if(*text == '9')
        {
            gioSetBit(gioPORTA, 2, 1);
            gioSetBit(gioPORTA, 2, 0);
            gioSetBit(gioPORTA, 2, 0);
        }

        while((UART->FLR & 0x4) == 4)
            ;
        sciSendByte(UART, *text++);
        wait(3333333);
    }
}

void wait(uint32 time)
{
    int i;

    for(i = 0; i < time; i++)
        ;
}
/* USER CODE END */
