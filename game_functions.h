/*
 * game_functions.h
 *
 *  Created on: 11-Jun-2021
 *      Author: Suraj K
 */

#include <stdint.h>


#ifndef TEMPFUN_H_
#define TEMPFUN_H_

#endif /* TEMPFUN_H_ */

tRectangle sRect;
extern tPushButtonWidget DESE;
void touch_DESE(tWidget *psWidget);      // widget on main screen, which when touched starts level-1

extern tPushButtonWidget IISc;
void touch_IISc(tWidget *psWidget);      // widget on main screen, which when touched starts level-2



extern tPushButtonWidget EXIT;
void touch_EXIT(tWidget *psWidget);      // widget on main screen, which when touched exits from main menu

extern tPushButtonWidget REPLAY;
void touch_REPLAY(tWidget *psWidget);   // widget on   GAME OVER screen, which when touched starts same level again

extern tPushButtonWidget BACK;
void touch_BACK(tWidget *psWidget);     // widget on   GAME OVER screen, which when touched , goes back to main menu.




int8_t check_obstruction(int32_t x, int32_t y);

void print_time_taken(void);   // prints the time taken since the start of the level
void game_over(void);           // final screen with Replay and Back widgets
void play_DESE(void);           // level-1
void play_IISc(void);           // level-2
void delay(void);


int n;
int gameover=0;

extern uint8_t lvl;
extern uint8_t playing;
extern uint8_t gflag;
extern uint8_t ms10_count;
extern uint8_t s_count;
extern uint8_t m_count;

uint8_t maze_touch;
uint8_t moved=0;

RectangularButton(DESE, 0, 0, 0, &g_sKentec320x240x16_SSD2119, 80, 105,
                  120, 25, PB_STYLE_FILL | PB_STYLE_TEXT | PB_STYLE_RELEASE_NOTIFY| PB_STYLE_OUTLINE, ClrLightSeaGreen , ClrDarkGreen, 0, ClrDarkBlue,
                  &g_sFontCm18b, "Lvl-1 : DESE ", 0, 0, 0, 0,
                  touch_DESE);
RectangularButton(IISc, 0, 0, 0, &g_sKentec320x240x16_SSD2119, 80, 145,
                  120, 25, PB_STYLE_FILL | PB_STYLE_TEXT| PB_STYLE_RELEASE_NOTIFY| PB_STYLE_OUTLINE, ClrLightBlue , ClrDarkGreen, 0, ClrDarkBlue,
                  &g_sFontCm18b, "Lvl-2 : IISc ", 0, 0, 0, 0,
                  touch_IISc);
RectangularButton(EXIT, 0, 0, 0, &g_sKentec320x240x16_SSD2119, 100, 185,
                  60, 20, PB_STYLE_FILL | PB_STYLE_TEXT| PB_STYLE_RELEASE_NOTIFY| PB_STYLE_OUTLINE, ClrLightBlue , ClrRed, 0, ClrDarkBlue,
                  &g_sFontCm18b, " EXIT ", 0, 0, 0, 0,
                  touch_EXIT);
RectangularButton(REPLAY, 0, 0, 0, &g_sKentec320x240x16_SSD2119, 60, 180,
                  60, 40, PB_STYLE_FILL | PB_STYLE_TEXT| PB_STYLE_RELEASE_NOTIFY| PB_STYLE_OUTLINE, ClrOrange, ClrRed, 0, ClrSnow,
                  &g_sFontCm14b, " REPLAY ", 0, 0, 0, 0,
                  touch_REPLAY);
RectangularButton(BACK, 0, 0, 0, &g_sKentec320x240x16_SSD2119, 200, 180,
                  60, 40, PB_STYLE_FILL | PB_STYLE_TEXT| PB_STYLE_RELEASE_NOTIFY| PB_STYLE_OUTLINE, ClrYellow  , ClrRed, 0, ClrDarkRed,
                  &g_sFontCm14b, " BACK ", 0, 0, 0, 0,
                  touch_BACK);


void main_menu(void){
gameover=0;



GrImageDraw(&sContext,mainmenu, 0, 0);



    GrContextFontSet(&sContext, &g_sFontCm24b);
    GrContextForegroundSet(&sContext, ClrDarkBlue);
    GrStringDrawCentered(&sContext, " MAZE Game ",-1,140,62 ,0);

    WidgetAdd(WIDGET_ROOT, (tWidget *)&DESE);
    WidgetPaint((tWidget *)&DESE);

    WidgetAdd(WIDGET_ROOT, (tWidget *)&IISc);
    WidgetPaint((tWidget *)&IISc);

    WidgetAdd(WIDGET_ROOT, (tWidget *)&EXIT);
    WidgetPaint((tWidget *)&EXIT);

    while(1)
             {

                  WidgetMessageQueueProcess();
                  if(gameover==1)break;
             }

}

void touch_DESE(tWidget *psWidget)      // this function is called when LEVEL-1: DESE widget is touched.
{

    clr_scrn();
    delay();
// clears the screen and removes the three previously added widgets
   if(gflag==0){
    WidgetRemove((tWidget *)&DESE);
    WidgetRemove((tWidget *)&IISc);
    WidgetRemove((tWidget *)&EXIT);
    delay();
   }


    GrImageDraw(&sContext,mazeDESE,0,0);    // draws the maze DESE

    play_DESE();     // In play_DESE, the actual game control happens

    game_over();
    gameover=0;
    lvl=1;
}

void touch_IISc(tWidget *psWidget) // this function is called when LEVEL-2: IISc widget is touched.
{
    clr_scrn();
    WidgetRemove((tWidget *)&DESE);
    WidgetRemove((tWidget *)&IISc);
    WidgetRemove((tWidget *)&EXIT);

    GrImageDraw(&sContext,iiscmaze,0,0);
        play_IISc();
        game_over();
        gameover=0;
        lvl=2;
}

void touch_EXIT(tWidget *psWidget)
{
    clr_scrn();
    WidgetRemove((tWidget *)&DESE);
    WidgetRemove((tWidget *)&IISc);
    WidgetRemove((tWidget *)&EXIT);
    GrContextFontSet(&sContext, &g_sFontCm16);
    GrContextForegroundSet(&sContext, ClrWhite);
    GrStringDrawCentered(&sContext, "A Project By : Suraj Das K",-1,150,180 ,0);
    GrStringDrawCentered(&sContext, "Sharath Lohith T",-1,215,200 ,0);
    GrStringDrawCentered(&sContext, "Suman J",-1,185,220,0);
}



void touch_BACK(tWidget *psWidget)
{
    WidgetRemove((tWidget *)&BACK);
    WidgetRemove((tWidget *)&REPLAY);
    gameover=1;
    gflag=0;
}

void touch_REPLAY(tWidget *psWidget)
{
    WidgetRemove((tWidget *)&BACK);
    WidgetRemove((tWidget *)&REPLAY);
    gflag=1;
   if(lvl==1) touch_DESE((tWidget *)&DESE); //If player is in level-1, touch_DESE should be simulated when replay is touched
   if(lvl==2) touch_IISc((tWidget *)&IISc); //If player is in level-2, touch_IISc function should be simulated when replay is touched

}


void play_DESE(void){

playing=1;
n=1;
lvl=1;
m_count=0x00;
s_count=0x00;
maze_touch = 0;
gameover=0;
moved=0;  // flag used in counting touches with maze
int32_t cirx_new,ciry_new, cirx_old, ciry_old; // old and new center pixel co-ordinates of the ball
cirx_new=20;
ciry_new=210;
cirx_old=23;
ciry_old=210;

uint8_t  printskip=0;



    while(n)
          {

            while(!g_vui8I2CDoneFlag)
              {
                // simply wait while waiting for data
                // control exits out of the loop when i2c data transfer is done from senshub to launchpad

              }

           g_vui8I2CDoneFlag = 0;   // clear done flag


           MPU9150DataAccelGetFloat(&g_sMPU9150Inst, pfAccel, pfAccel + 1,    // get accel values
                                                     pfAccel + 2);

           g_ui32PrintSkipCounter++; // used to print only at fixed intervals(without printing unnecessarily)

           if(g_ui32PrintSkipCounter >= PRINT_SKIP_COUNT)  // changing PRINT_SKIP_COUNT macro value can make the ball move faster or slower.

           {

            g_ui32PrintSkipCounter = 0;
            format_data();                  // formats the data in desired way

            if(cSign[0]=='-' && i32IPart[0]>2 && (cirx_new+5) < 319)    // checks if motion sensor is moved to EAST
            { cirx_new=cirx_old+3 ;}                                    // updates the circle's center coordinate by 3 pixels EAST....
            if(cSign[0]==' ' && i32IPart[0]>2 && (cirx_new-5)>3)    // checks if motion sensor is moved to WEST
            { cirx_new=cirx_old-3 ;}                                    // updates the circle's center coordinate by 3 pixels WEST....
            if(cSign[1]=='-' && i32IPart[1]>2 && (ciry_new-5)>3)    // checks if motion sensor is moved to NORTH
            { ciry_new=ciry_old-3 ;}                                    // updates the circle's center coordinate by 3 pixels NORTH....
            if(cSign[1]==' ' && i32IPart[1]>2 && (ciry_new+5) < 239)    // checks if motion sensor is moved to SOUTH
            { ciry_new=ciry_old+3 ;}                                    // updates the circle's center coordinate by 3 pixels SOUTH...


// If theres no obstruction in movement , then its a valid move.

            if(valid_move(cirx_new, ciry_new, cirx_old, ciry_old)){

                GrContextForegroundSet(&sContext, ClrWhite);
               GrCircleFill(&sContext, cirx_old,ciry_old, 2);  // clears the old circle by drawing a circle with background clr(white) at old pixel coordinates
               GrContextForegroundSet(&sContext, ClrRed);
                 GrCircleFill(&sContext, cirx_new,ciry_new, 2); // Draws the red circle with new pixel co-ordinates
                cirx_old=cirx_new;   // update old coordinate values as new values.
                ciry_old=ciry_new;
                moved=1;
            }

            else {cirx_new=cirx_old;
                   ciry_new=ciry_old;
                   if (moved) maze_touch++;
                   moved=0;
                    }

          //
            printskip++;
            if(printskip>10) // the time taken is updated on the game screen once after every 10 ball movements.
            {
                printskip=0;
                print_time_taken();

                }

          }

        if((cirx_new>300)&&(ciry_new<80)&&(ciry_new>20))   // happens when ball reaches finish
            {n=0;
        playing=0;
            }
    }
}



void play_IISc(void){
playing=1;
n=1;
lvl=2;
m_count=0x00;
s_count=0x00;
gameover=0;
maze_touch = 0;
moved=0;
int32_t cirx_new,ciry_new, cirx_old, ciry_old;
uint8_t printskip=0;
cirx_new=23;
ciry_new=200;
cirx_old=20;
ciry_old=220;


    while(n)
          {


            while(!g_vui8I2CDoneFlag)
              {


              }

           g_vui8I2CDoneFlag = 0;   // clear done flag


           MPU9150DataAccelGetFloat(&g_sMPU9150Inst, pfAccel, pfAccel + 1,    // get accel values
                                                     pfAccel + 2);

           g_ui32PrintSkipCounter++; // used to print only at fixed intervals(without printing unnecessarily)

           if(g_ui32PrintSkipCounter >= PRINT_SKIP_COUNT)
               {

            g_ui32PrintSkipCounter = 0;
            format_data();

            if(cSign[0]=='-' && i32IPart[0]>2 && (cirx_new+5) < 319)
            { cirx_new=cirx_old+3 ;}
            if(cSign[0]==' ' && i32IPart[0]>2 && (cirx_new-5)>3)
            { cirx_new=cirx_old-3 ;}
            if(cSign[1]=='-' && i32IPart[1]>2 && (ciry_new-5)>3)
            { ciry_new=ciry_old-3 ;}
            if(cSign[1]==' ' && i32IPart[1]>2 && (ciry_new+5) < 239)
            { ciry_new=ciry_old+3 ;}




            if(valid_move(cirx_new, ciry_new, cirx_old, ciry_old))
            {

                GrContextForegroundSet(&sContext, ClrWhite);
               GrCircleFill(&sContext, cirx_old,ciry_old, 2);
               GrContextForegroundSet(&sContext, ClrRed);
                 GrCircleFill(&sContext, cirx_new,ciry_new, 2);
                cirx_old=cirx_new;
                ciry_old=ciry_new;
                moved=1;
            }

                else
                {
                    cirx_new=cirx_old;
                    ciry_new=ciry_old;
                    if (moved) maze_touch++;
                      moved=0;
                }

                        printskip++;
                       if(printskip>10)
                       {
                           printskip=0;

                           print_time_taken();

                           }

          }

        if((cirx_new>300)&&(ciry_new<230)&&(ciry_new>220))
            {
            n=0;
        playing=0;
        lvl=2;
            }
    }
}


// This function will return 1 if theres no obstruction in path of the ball.


int valid_move(int32_t xnew, int32_t ynew,int32_t xold, int32_t yold ){
    int32_t k=xnew-xold;  // x direction variable
    int32_t l=ynew-yold;  // y direction variable

    int32_t flag=0;  // says if obstruction occurs in path.
    int32_t m;

    int8_t obs;

    //for case when only moved in East direction
     if(k>0 && l==0){
         for ( m=xold;m<=xnew; m++)
         {
            obs=check_obstruction(m,ynew);
            if(obs==1){flag=1;}
         }
     }

     //for case when only moved in West direction
     if(k<0 && l==0){
              for (m=xnew;m<=xold; m++)
              {
                 obs= check_obstruction(m,ynew);  //obs= obstruction occured.!!
                 if(obs==1){flag=1;}
              }
          }
     //for case when only moved in North direction
          if(l<0 && k==0){
                   for (m=ynew;m<=yold; m++)
                   {
                      obs= check_obstruction(xnew,m);  //obs= obstruction occured.!!
                      if(obs==1){flag=1;}
                   }
               }
     //for case when only moved in South direction
           if(l>0 && k==0){
                     for (m=yold;m<=ynew; m++)
                      {
                         obs= check_obstruction(xnew,m);  //obs= obstruction occured.!!
                         if(obs==1){flag=1;}
                      }
                }
     // for case when it move in North East Direction
           if(k>0 && l<0){
               obs=check_obstruction(xold,yold);if(obs==1){flag=1;}
               obs=check_obstruction(xold+1,yold-1);if(obs==1){flag=1;}
               obs=check_obstruction(xold+2,yold-2);if(obs==1){flag=1;}
               obs=check_obstruction(xnew,ynew);    if(obs==1){flag=1;}
           }

     // for case when it moves in North West Direction
           if(k<0 && l<0){
               obs=check_obstruction(xold,yold);if(obs==1){flag=1;}
               obs=check_obstruction(xold-1,yold-1);if(obs==1){flag=1;}
               obs=check_obstruction(xold-2,yold-2);if(obs==1){flag=1;}
               obs=check_obstruction(xnew,ynew);    if(obs==1){flag=1;}
           }
    // for case when it moves in South West Direction
            if(k<0 && l>0){
                 obs=check_obstruction(xold,yold);if(obs==1){flag=1;}
                 obs=check_obstruction(xold-1,yold+1);if(obs==1){flag=1;}
                 obs=check_obstruction(xold-2,yold+2);if(obs==1){flag=1;}
                 obs=check_obstruction(xnew,ynew);    if(obs==1){flag=1;}
           }
     // for case when it moves in South East Direction
              if(k>0 && l>0){
                   obs=check_obstruction(xold,yold);if(obs==1){flag=1;}
                   obs=check_obstruction(xold+1,yold+1);if(obs==1){flag=1;}
                   obs=check_obstruction(xold+2,yold+2);if(obs==1){flag=1;}
                   obs=check_obstruction(xnew,ynew);    if(obs==1){flag=1;}
           }



        if(flag){return 0;}
        return 1;
}


//This function compares the pixel coordinates(x,y) it gets with the corresponding blueprint image of the maze which was stored as 2D array of 0s and 1s.


int8_t pixel_obstruction(int32_t x, int32_t y){
    int16_t x40_cord= x/8;
    int16_t x8_cord=x%8;

    int8_t temp;
    int8_t flag=0;



    switch(x8_cord){
    case(0):if(lvl==1)
            temp=deseMAZE_blueprint[y][x40_cord] & 0x80;
            if(lvl==2)
                temp=iiscMAZE_blueprint[y][x40_cord] & 0x80;
            if(temp==0x00) {flag=1;} break;

    case(1):if(lvl==1)
            temp=deseMAZE_blueprint[y][x40_cord] & 0x40;
            if(lvl==2)
                temp=iiscMAZE_blueprint[y][x40_cord] & 0x40;
            if(temp==0x00) {flag=1;}break;

    case(2):if(lvl==1)
            temp=deseMAZE_blueprint[y][x40_cord] & 0x20;
            if(lvl==2)
            temp=iiscMAZE_blueprint[y][x40_cord] & 0x20;
            if(temp==0x00) {flag=1;}break;

    case(3):if(lvl==1)
            temp=deseMAZE_blueprint[y][x40_cord] & 0x10;
            if(lvl==2)
            temp=iiscMAZE_blueprint[y][x40_cord] & 0x10;
            if(temp==0x00) {flag=1;}break;

    case(4):if(lvl==1)
            temp=deseMAZE_blueprint[y][x40_cord] & 0x08;
            if(lvl==2)
            temp=iiscMAZE_blueprint[y][x40_cord] & 0x08;
            if(temp==0x00) {flag=1;}break;

    case(5):if(lvl==1)
            temp=deseMAZE_blueprint[y][x40_cord] & 0x04;
            if(lvl==2)
            temp=iiscMAZE_blueprint[y][x40_cord] & 0x04;
            if(temp==0x00) {flag=1;}break;

    case(6):if(lvl==1)
            temp=deseMAZE_blueprint[y][x40_cord] & 0x02;
            if(lvl==2)
            temp=iiscMAZE_blueprint[y][x40_cord] & 0x02;
            if(temp==0x00) {flag=1;}break;
    case(7):if(lvl==1)
            temp=deseMAZE_blueprint[y][x40_cord] & 0x01;
            if(lvl==2)
            temp=iiscMAZE_blueprint[y][x40_cord] & 0x01;
            if(temp==0x00) {flag=1;}break;    }


    if(flag==1) return 1;
    else   return 0;
}


// Check_obstruction funtion will check for possible contact of ball pixels with maze walls.//
// This function check for all possible pixels of the ball.


int8_t check_obstruction(int32_t x, int32_t y){

    int8_t flag=0;

    if(pixel_obstruction(x,y)) flag=1;
    if(pixel_obstruction(x,y-1)) flag=1;
    if(pixel_obstruction(x,y-2)) flag=1;
    if(pixel_obstruction(x,y+1)) flag=1;
    if(pixel_obstruction(x,y+2)) flag=1;

    // pixels to the right
    if(pixel_obstruction(x+1,y)) flag=1;
    if(pixel_obstruction(x+2,y)) flag=1;
    if(pixel_obstruction(x+1,y-1)) flag=1;
    if(pixel_obstruction(x+1,y-2)) flag=1;
    if(pixel_obstruction(x+2,y-1)) flag=1;
    if(pixel_obstruction(x+1,y+1)) flag=1;
    if(pixel_obstruction(x+2,y+1)) flag=1;
    if(pixel_obstruction(x+1,y+2)) flag=1;

    // pixels to the left

    if(pixel_obstruction(x-1,y)) flag=1;
    if(pixel_obstruction(x-2,y)) flag=1;
    if(pixel_obstruction(x-1,y-1)) flag=1;
    if(pixel_obstruction(x-1,y-2)) flag=1;
    if(pixel_obstruction(x-2,y-1)) flag=1;
    if(pixel_obstruction(x-1,y+1)) flag=1;
    if(pixel_obstruction(x-1,y+2)) flag=1;
    if(pixel_obstruction(x-2,y+1)) flag=1;

    if(flag) return 1;
    else return 0;
    }



void game_over(void){

    WidgetRemove((tWidget *)&DESE);
    WidgetRemove((tWidget *)&IISc);
    WidgetRemove((tWidget *)&EXIT);
    clr_scrn();
    GrImageDraw(&sContext,gameoverimg,50,0);
    char minbuf[3];
    char secbuf[3];
    char ms10buf[3];
    char mazetouchbuff[6];
    itoa(m_count,minbuf,10);
    itoa(s_count,secbuf,10);
    itoa(ms10_count,ms10buf,10);
    itoa(maze_touch,mazetouchbuff,10);
    char time_taken[20]=" ";
    strcat(time_taken,minbuf);
    strcat(time_taken," M : ");
    strcat(time_taken,secbuf);
    strcat(time_taken," S : ");
    strcat(time_taken,ms10buf);
    strcat(time_taken," ms");


      GrContextFontSet(&sContext, &g_sFontCm16);
      GrContextForegroundSet(&sContext, ClrWhite);
      GrStringDrawCentered(&sContext,"MAZE Completed in  ",-1,80,100 ,0);
      GrStringDrawCentered(&sContext,"You Touched the Maze  ",-1,90,130 ,0);
      GrStringDrawCentered(&sContext," times...  ",-1,250,130 ,0);

      GrContextForegroundSet(&sContext, ClrYellow);
      GrStringDrawCentered(&sContext,time_taken,20,200,100 ,0);
      GrStringDrawCentered(&sContext,mazetouchbuff,20,200,130 ,0);

      WidgetAdd(WIDGET_ROOT, (tWidget *)&BACK);
      WidgetPaint((tWidget *)&BACK);

      WidgetAdd(WIDGET_ROOT, (tWidget *)&REPLAY);
      WidgetPaint((tWidget *)&REPLAY);

}

void delay(void){
    int k=0;
         for (k=0;k<1000;k++)
         {
             asm("NOP");
         }
}


void print_time_taken(void)
{

    char time_taken[20]=" ";
    char minbuf[3];
    char secbuf[3];
    char ms10buf[3];
    itoa(m_count,minbuf,10);
    itoa(s_count,secbuf,10);
    itoa(ms10_count,ms10buf,10);

    strcat(time_taken,minbuf);
    strcat(time_taken," m : ");
    strcat(time_taken,secbuf);
    strcat(time_taken," s : ");
    strcat(time_taken,ms10buf);
    strcat(time_taken," ms");

    GrContextFontSet(&sContext, &g_sFontCm12b);
    GrContextBackgroundSet(&sContext, ClrWhite);
    GrContextForegroundSet(&sContext, ClrGreen);

    if(lvl==1) GrStringDrawCentered(&sContext,time_taken,20,155,15 ,1); // in level 1, time is printed at top

    if(lvl==2) GrStringDrawCentered(&sContext,time_taken,20,160,234 ,1);//  in level 2, time is printed at bottom

}


