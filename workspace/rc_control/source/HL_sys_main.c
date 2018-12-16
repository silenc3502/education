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
#include "stdio.h"
#include "string.h"
#include "HL_gio.h"
#include "HL_sci.h"
#include "HL_system.h"
#include "HL_ecap.h"
#include "HL_etpwm.h"
/* USER CODE END */

/** @fn void main(void)
*   @brief Application main function
*   @note This function is empty by default.
*
*   This function is called after startup.
*   The user can use this function to implement the application.
*/

/* USER CODE BEGIN (2) */
#define UART                sciREG1
char txt_buf[256] = { 0 };
unsigned int buf_len;

int led_on;
int motor_pwm;

void sci_display(sciBASE_t *sci, uint8 *text, uint32 len)
{
    while (len--)
    {
        while ((UART->FLR & 0x4) == 4)
            ;
        sciSendByte(UART, *text++);
    }
}

void wait(int delay)
{
    int i;

    for(i = 0; i < delay; i++)
        ;
}
/* USER CODE END */

int main(void)
{
/* USER CODE BEGIN (3) */
    sciInit();

    sprintf(txt_buf, "sci init success!!!\n\r\0");
    buf_len = strlen(txt_buf);
    sci_display(UART, (uint8 *) txt_buf, buf_len);

    gioInit();

    sprintf(txt_buf, "gio init success!!!\n\r\0");
    buf_len = strlen(txt_buf);
    sci_display(UART, (uint8 *) txt_buf, buf_len);

    etpwmInit();

    sprintf(txt_buf, "etpwm init success!!!\n\r\0");
    buf_len = strlen(txt_buf);
    sci_display(UART, (uint8 *) txt_buf, buf_len);

    etpwmStartTBCLK();
    ecapInit();

    sprintf(txt_buf, "ecap init success!!!\n\r\0");
    buf_len = strlen(txt_buf);
    sci_display(UART, (uint8 *) txt_buf, buf_len);

    _enable_interrupt_();

    ecapStartCounter(ecapREG1);
    ecapStartCounter(ecapREG2);
    ecapStartCounter(ecapREG3);
    ecapStartCounter(ecapREG4);
    ecapEnableCapture(ecapREG1);
    ecapEnableCapture(ecapREG2);
    ecapEnableCapture(ecapREG3);
    ecapEnableCapture(ecapREG4);

    for(;;)
        ;
/* USER CODE END */

    return 0;
}


/* USER CODE BEGIN (4) */
void ecapNotification(ecapBASE_t *ecap, uint16 flags)
{
    uint32 cap[3];
    //float64 elev,rudd,ail,thro;

    cap[0] = ecapGetCAP1(ecapREG1);
    cap[1] = ecapGetCAP2(ecapREG1);
#if 0
    cap[2] = ecapGetCAP1(ecapREG2);
    cap[3] = ecapGetCAP2(ecapREG2);
    cap[4] = ecapGetCAP1(ecapREG3);
    cap[5] = ecapGetCAP2(ecapREG3);
    cap[6] = ecapGetCAP1(ecapREG4);
    cap[7] = ecapGetCAP2(ecapREG4);
#endif

    //ail  = (cap[3] - cap[2]) * 1000 / VCLK3_FREQ / 1000; // ecap2  channel 1
    led_on = (cap[1] - cap[0]) * 1000 / VCLK3_FREQ / 1000; // ecap1  channel 2
    //thro = (cap[5] - cap[4]) * 1000 / VCLK3_FREQ / 1000; // ecap3  channel 3
    //rudd = (cap[7] - cap[6]) * 1000 / VCLK3_FREQ / 1000; // ecap4  channel 4

    sprintf(txt_buf, "led_on = %d ms\n\r\0", led_on);
    buf_len = strlen(txt_buf);
    sci_display(UART, (uint8 *) txt_buf, buf_len);

    if(led_on > 1800)
        gioSetBit(gioPORTA, 4, 1);
    else
        gioSetBit(gioPORTA, 4, 0);

    motor_pwm = led_on - 500;
    etpwmREG1->CMPA = motor_pwm * 1.25;

    wait(10000);
}
/* USER CODE END */
