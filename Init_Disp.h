/*
 * Init_Disp.h
 *
 *  Created on: 09-Jun-2021
 *      Author: Suraj K
 */

void system_init(void);
void ms_delay(uint32_t );
void clr_scrn(void);

tContext sContext;
tRectangle sRect,Rect_M,Rect_L,Rect_R,Rect_t1,Rect_t2;


void system_init(void)
{
   FPUEnable();
    FPUStackingDisable();
    SysCtlClockSet(SYSCTL_SYSDIV_5 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ | SYSCTL_OSC_MAIN);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    IntMasterEnable();
}


void ms_delay(uint32_t delay)
{
    SysCtlDelay(((SysCtlClockGet())/3000)*delay);
}





void clr_scrn(void){
    sRect.i16XMin = 0;
      sRect.i16YMin = 0;
      sRect.i16XMax = 319;
      sRect.i16YMax = 239;
      GrContextForegroundSet(&sContext, ClrBlack);
      GrRectFill(&sContext, &sRect);
}
