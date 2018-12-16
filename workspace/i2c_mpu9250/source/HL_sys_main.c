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
#include "mpu9250.h"

#define    MPU9250_ADDRESS            0x68
#define    MAG_ADDRESS                0x0C

#define    GYRO_FULL_SCALE_250_DPS    0x00
#define    GYRO_FULL_SCALE_500_DPS    0x08
#define    GYRO_FULL_SCALE_1000_DPS   0x10
#define    GYRO_FULL_SCALE_2000_DPS   0x18

#define    ACC_FULL_SCALE_2_G        0x00
#define    ACC_FULL_SCALE_4_G        0x08
#define    ACC_FULL_SCALE_8_G        0x10
#define    ACC_FULL_SCALE_16_G       0x18

#define R2D  180 / M_PI
#define GYRO2DEGREE_PER_SEC  65.5

uint32 rx_data = 0;
uint32 tmp = 0;
uint32 value = 0;

volatile char acc_data[6];
volatile char gyro_data[6];
volatile char mag_data[8];

#define IDX     2

uint32 duty_arr[IDX] = {1000, 2000};

float ax, ay, az, gx, gy, gz, mx, my, mz;

double pitch;
double roll;

int16_t accelCount[3];
int16_t gyroCount[3];
int16_t magCount[3];

float magCalibration[3] = {0, 0, 0} , magbias[3] = {0, 0, 0};
float gyroBias[3] = {0, 0, 0}, accelBias[3] = {0, 0, 0};
/* USER CODE END */

/** @fn void main(void)
*   @brief Application main function
*   @note This function is empty by default.
*
*   This function is called after startup.
*   The user can use this function to implement the application.
*/

/* USER CODE BEGIN (2) */
/* USER CODE END */

int main(void)
{
/* USER CODE BEGIN (3) */
    char txt_buf[256] = {0};
    unsigned int buf_len;
    volatile int i;


    sciInit();

    disp_set("SCI Configuration Success!!\n\r\0");

    gioInit();

    disp_set("GIO Init Success!!\n\r\0");

    i2cInit();
    wait(10000000);
    disp_set("I2C Init Success!!\n\r\0");

    uint8 c = readByte(MPU9250_ADDRESS, WHO_AM_I_MPU9250);
    sprintf(txt_buf, "I AM = %x\n\r\0", c);

    buf_len = strlen(txt_buf);
    sciDisplayText(sciREG1, (uint8 *) txt_buf, buf_len);

    if(c == 0x71)
    {
        calibrateMPU9250(gyroBias, accelBias);
        disp_set("MPU9250 calibration Success!!!!!!\n\r\0");

        initMPU9250();
        disp_set("MPU9250 Init Success!!!!!!\n\r\0");

        initAK8963(magCalibration);
        disp_set("MPU9250 AK8963 Init Success!!!!!!\n\r\0");

        get_offset_value();
        disp_set("gyro_offset_setting Success!!\n\r\0");

        rtiInit();
        rtiEnableNotification(rtiREG1, rtiNOTIFICATION_COMPARE0);
        _enable_IRQ_interrupt_();
        rtiStartCounter(rtiREG1, rtiCOUNTER_BLOCK0);

        disp_set("RTI Init Success!!\n\r\0");

        wait(1000000);
    }
    else
    {
        disp_set("MPU9250 doesn't work!!!");
        while(1);
    }

    for(;;)
    {
        if(readByte(MPU9250_ADDRESS, INT_STATUS) & 0x01)
        {
            readAccelData(accelCount);  // Read the x/y/z adc values
            getAres();

            ax = (float) accelCount[0] * aRes; // - accelBias[0];
            ay = (float) accelCount[1] * aRes; // - accelBias[1];
            az = (float) accelCount[2] * aRes; // - accelBias[2];

            readGyroData(gyroCount);  // Read the x/y/z adc values
            getGres();

            gx = (float) gyroCount[0] * gRes;
            gy = (float) gyroCount[1] * gRes;
            gz = (float) gyroCount[2] * gRes;

            readMagData(magCount);  // Read the x/y/z adc values
            getMres();
            magbias[0] = +470.0;
            magbias[1] = +120.0;
            magbias[2] = +125.0;

            mx = (float) magCount[0] * mRes * magCalibration[0] - magbias[0];
            my = (float) magCount[1] * mRes * magCalibration[1] - magbias[1];
            mz = (float) magCount[2] * mRes * magCalibration[2] - magbias[2];

            sprintf(txt_buf, "acc_x = %f \t acc_y = %f \t acc_z = %f \n\r\0",
                    1000 * ax  , 1000 * ay  , 1000 * az );

            buf_len = strlen(txt_buf);
            sciDisplayText(sciREG1, (uint8 *) txt_buf, buf_len);
            wait(3000000);

            sprintf(txt_buf, "GYRO_x = %d \t GYRO_y = %d \t GYRO_z = %d \n\r\0",
                       ((int)gx)  , ((int)gy)  , ((int)gz) );

            buf_len = strlen(txt_buf);
            sciDisplayText(sciREG1, (uint8 *) txt_buf, buf_len);
            wait(1000000);

//            sprintf(txt_buf, "MAG_x = %f \t MAG_y = %f \t MAG_z = %f \n\r\0",
//                    mx  , my  , mz );
//
//            buf_len = strlen(txt_buf);
//            sciDisplayText(sciREG1, (uint8 *) txt_buf, buf_len);
//            wait(1000000);


//            sprintf(txt_buf, "roll = %lf \t pitch = %lf\n\r\0", roll *100, pitch*100);
//
//            buf_len = strlen(txt_buf);
//            sciDisplayText(sciREG1, (uint8 *) txt_buf, buf_len);
//            wait(1000000);
//            get_roll_pitch();
//            sprintf(txt_buf,
//                    "roll = %d \t pitch = %d  \n\r\0",
//                    (int)angle_roll_acc, (int)angle_pitch_acc);
//
//            buf_len = strlen(txt_buf);
//            sciDisplayText(sciREG1, (uint8 *) txt_buf, buf_len);
//            wait(3000000);
        }

    }
/* USER CODE END */

    return 0;
}

/* USER CODE BEGIN (4) */
void rtiNotification(rtiBASE_t *rtiREG, uint32 notification) { }
/* USER CODE END */
