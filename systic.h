

#include <stdio.h>
#include <stdlib.h>
#include "inc/tm4c123gh6pm.h"



#define UPDATE_DELAY_RESET  100
void Init_Systick(void);
void Systick_INT_Handler(void);

uint8_t ms10_count;
uint8_t s_count;
uint8_t m_count;

extern uint8_t playing;

char min[9];
char sec[6];
char ms10[3];


char time[10];
//


void Init_Systick(void){

    NVIC_ST_RELOAD_R = 400000;                                    /* reload with number of clocks per second 15999 */
    NVIC_ST_CTRL_R = 7;                                          /* enable SysTick interrupt, use system clock */
    NVIC_SYS_PRI3_R=(NVIC_SYS_PRI3_R & 0x1FFFFFFF) | 0x20000000; /*  priority 3 */
}

void Systick_INT_Handler(void){



    if(playing){
        ms10_count=ms10_count+1;
        if(ms10_count==99)
        {
            ms10_count=0;

            s_count=s_count+1;

            if(s_count==59)
            {
                s_count=0;
                m_count=m_count+1;
                if(m_count>=60)m_count=0;
            }
        }



    }
}
