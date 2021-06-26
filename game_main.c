/*
 * game_main.c
 *
 *  Created on: 11-Jun-2021
 *      Author: Suraj K
 */
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MiniProject- Creating a MAZE Game using BoostXl-SensHub and BoostXl-k350QVG touch LCD and TM4C123GH6PM launchpad board
//
// PROJECT BY :  SURAJ DAS K
//               Sharath Lohith T
//               Suman J
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "inc/hw_memmap.h"
#include "inc/hw_gpio.h"
#include "inc/hw_nvic.h"
#include "inc/hw_sysctl.h"
#include "inc/hw_types.h"
#include "inc/hw_ints.h"
#include "driverlib/flash.h"
#include "driverlib/sysctl.h"
#include "driverlib/systick.h"
#include "driverlib/uart.h"
#include "driverlib/udma.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "utils/uartstdio.h"
#include "utils/uartstdio.c"
#include "sensorlib/hw_mpu9150.h"   // gyro and accelerometer
#include "sensorlib/hw_ak8975.h"  // magnetometer
#include "sensorlib/i2cm_drv.h"   // Interrupt driven i2c master
#include "sensorlib/ak8975.h"
#include "sensorlib/mpu9150.h"
#include "sensorlib/comp_dcm.h"
#include "grlib/grlib.h"
#include "grlib/widget.h"
#include "grlib/pushbutton.h"

#include "lcd_tools/Kentec320x240x16_ssd2119_spi.h"
#include "lcd_tools/touch.h"

#include "Init_Disp.h"
#include "Init_Sens.h"
#include "images.h"
#include "systic.h"
#include "game_functions.h"
//----------------------------for SensHub---------------------------//
#define MPU9150_I2C_ADDRESS     0x68
extern uint32_t ui32SysClock;
extern tI2CMInstance g_sI2CInst;
extern tMPU9150 g_sMPU9150Inst;
extern uint32_t g_ui32PrintSkipCounter;
extern uint_fast32_t ui32Idx;

extern volatile uint_fast8_t g_vui8I2CDoneFlag;
extern volatile uint_fast8_t g_vui8DataFlag;
extern volatile uint_fast8_t g_vui8ErrorFlag;

extern float pfData[3];
extern int_fast32_t i32IPart[3], i32FPart[3];
extern char cSign[3];



//--------------------------------for Display---------------------//

uint32_t time_interval=1000;
uint32_t ui32SysClock;
uint8_t lvl=0;
uint8_t playing=0;
uint8_t gflag;


extern tContext sContext;
extern tRectangle sRect,Rect_M,Rect_L,Rect_R,Rect_t1,Rect_t2;


int main(void)
   {

    //time print background in maze DESE
    Rect_L.i16XMin = 110;
    Rect_L.i16YMin = 10;
    Rect_L.i16XMax = 210;
    Rect_L.i16YMax = 20;


    // time print background in maze IISc
    Rect_R.i16XMin = 110;
    Rect_R.i16YMin = 229;
    Rect_R.i16XMax = 210;
    Rect_R.i16YMax = 239;


    gflag=0;
    system_init();
    Init_Systick();
    ui32SysClock = SysCtlClockGet();

    Kentec320x240x16_SSD2119Init(ui32SysClock);
    GrContextInit(&sContext, &g_sKentec320x240x16_SSD2119);

    TouchScreenInit(ui32SysClock);
    TouchScreenCallbackSet(WidgetPointerMessage);

    init_mpu_i2c();

    clr_scrn();

    while(1)  main_menu();

    return 0;
}
