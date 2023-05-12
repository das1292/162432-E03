#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>

#include "app.h"

#define ONE_VOLT 310
#define ONE_TENTH_VOLT 31
#define ONE_HUNDREDTH_VOLT 3
#define SCALE 308L

#define LCD_SendCommand(command, delay) { PMADDR = 0x0000; PMDIN1 = command; LCD_Wait(delay); }
#define LCD_COMMAND_CLEAR_SCREEN        0x01
#define LCD_COMMAND_RETURN_HOME         0x02
#define LCD_COMMAND_ENTER_DATA_MODE     0x06
#define LCD_COMMAND_CURSOR_OFF          0x0C
#define LCD_COMMAND_CURSOR_ON           0x0F
#define LCD_COMMAND_MOVE_CURSOR_LEFT    0x10
#define LCD_COMMAND_MOVE_CURSOR_RIGHT   0x14
#define LCD_COMMAND_SET_MODE_8_BIT      0x38
#define LCD_COMMAND_ROW_0_HOME          0x80
#define LCD_COMMAND_ROW_1_HOME          0xC0

void Update_LCD ( void ) ;
void SYS_Initialize ( void ) ;
extern void ConvertADCVoltage ( unsigned int  ) ;
extern void Hex2Dec ( unsigned char ) ;


APP_DATA appData = {
                    .msg1 = "Witaj" ,
                    .msg2 = "Wcisnij przycisk s3 by kontynuowac" ,
                    .msgT = "Time 00: 00: 00 " ,
                    .msgADC = " Pot = 0.00 Vdc "
} ;


char t1[] = "WYDZIAL";
char t2[] = "  INFORMATYCZNY";
char t3[] = "WYDZIAL         INFORMATYCZNY";
char t4[] = "   ZAPRASZAMY    ";
char t5[] = "!!!ZAPRASZAMY!!!";

char r_open[] = "   W    M    I    I  ";
char r_close[] = "   W    M   I    I  ";


void delay(int x)
{
    for (int i = x * SCALE; i > 0; i--)
        Nop();
}

void pause()
{
    delay(500);
    delay(500);
    delay(500);
    delay(500);
    delay(500);
}

void pause2()
{
    pause();
    pause();
    pause();
    pause();
    pause();
}

void z1(void)
{
    for(int i=0; i<=1; i++)
    {
    LCD_PutString(t1, strlen(t1));
    pause();
    pause();
    pause();
    LCD_ClearScreen();
    pause();
    
    LCD_CarriageReturn () ;
    LCD_ShiftCursorDown () ;
    LCD_PutString(t2, strlen(t2));
    pause();
    pause();
    pause();
    LCD_ClearScreen();
    pause();
    }

    
    pause();
    for(int i=0; i<=1; i++)
    {
    LCD_PutString(t3, strlen(t3));
    pause();
    LCD_ClearScreen();
    pause();
    }
    
    LCD_PutString(t3, strlen(t3));
    pause2();
    
    LCD_ClearScreen();
    
}

void z2(void)
{
    for(int i=0; i<=2; i++)
    {
    LCD_PutString(r_open, strlen(r_open));
    pause();
    pause();
    LCD_ClearScreen();
    LCD_PutString(r_close, strlen(r_close));
    pause();
    pause();
    LCD_ClearScreen();
    }
    
    LCD_PutString(r_open, strlen(r_open));
    pause2();
    pause2();
    LCD_ClearScreen();
    
}


void z3(void)
{
    for(int i=0; i<=2; i++)
    {
    LCD_PutString(t5, strlen(t5));
    pause();
    pause();
    LCD_ClearScreen();
    
    LCD_PutString(t4, strlen(t4));
    pause();
    pause();
    LCD_ClearScreen();
    }
    
    LCD_PutString(t5, strlen(t5));
    pause2();
    
    LCD_ClearScreen();
    
}

int main ( void )
{


    //Wywo?anie procedury inicjalizacji systemu
    SYS_Initialize ( ) ;

    //Sprawdzenie czy przycisk s3 zostal wcisniety
    while (!BUTTON_IsPressed ( BUTTON_S3 )) ;

    //Timer inicjalizacji
    TIMER_SetConfiguration ( TIMER_CONFIGURATION_RTCC ) ;


    while ( 1 )
    {

        z1();
        z2();
        z3();
        
        
    } ;
}

void Update_LCD ( void )
{
    LCD_PutChar ( 'T' ) ;
    LCD_PutChar ( 'i' ) ;
    LCD_PutChar ( 'm' ) ;
    LCD_PutChar ( 'e' ) ;
    LCD_PutChar ( ' ' ) ;
    LCD_PutChar ( appData.a10 + 0x30 ) ;
    LCD_PutChar ( appData.a1 + 0x30 ) ;

    Hex2Dec ( appData.min ) ;
    LCD_PutChar ( ':' ) ;
    LCD_PutChar ( ' ' ) ;
    LCD_PutChar ( appData.a10 + 0x30 ) ;
    LCD_PutChar ( appData.a1 + 0x30 ) ;

    Hex2Dec ( appData.sec ) ;
    LCD_PutChar ( ':' ) ;
    LCD_PutChar ( ' ' ) ;
    LCD_PutChar ( appData.a10 + 0x30 ) ;
    LCD_PutChar ( appData.a1 + 0x30 ) ;

}

void Hex2Dec ( unsigned char count )
{
    //reset wartosci
    appData.a100 = 0 ;
    appData.a10  = 0 ;
    appData.a1 = 0 ;

    while ( count >= 10 )
    {

        if ( count >= 200 )
        {
            count -= 200 ;
            appData.a100 = 0x02 ;
        }

        if (count >= 100)
        {
            count -= 100 ;
            appData.a100++ ;
        }

        if (count >= 10 )
        {
            count -= 10 ;
            appData.a10++ ;
        }
    }

    appData.a1 = count ;
}
