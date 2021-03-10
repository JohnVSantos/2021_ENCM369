/*!*********************************************************************************************************************
@file user_app.c                                                                
@brief User's tasks / applications are written here.  This description
should be replaced by something specific to the task.

------------------------------------------------------------------------------------------------------------------------
GLOBALS
- NONE

CONSTANTS
- NONE

TYPES
- NONE

PUBLIC FUNCTIONS
- NONE

PROTECTED FUNCTIONS
- void UserApp1Initialize(void)
- void UserApp1Run(void)


**********************************************************************************************************************/

#include "configuration.h"

/***********************************************************************************************************************
Global variable definitions with scope across entire project.
All Global variable names shall start with "G_<type>UserApp1"
***********************************************************************************************************************/
static u8 UserApp_au8sinTable[] =
{
0x80,0x83,0x86,0x89,0x8c,0x8f,0x92,0x95,0x98,0x9b,0x9e,0xa2,0xa5,0xa7,0xaa,0xad,
0xb0,0xb3,0xb6,0xb9,0xbc,0xbe,0xc1,0xc4,0xc6,0xc9,0xcb,0xce,0xd0,0xd3,0xd5,0xd7,
0xda,0xdc,0xde,0xe0,0xe2,0xe4,0xe6,0xe8,0xea,0xeb,0xed,0xee,0xf0,0xf1,0xf3,0xf4,
0xf5,0xf6,0xf8,0xf9,0xfa,0xfa,0xfb,0xfc,0xfd,0xfd,0xfe,0xfe,0xfe,0xff,0xff,0xff,
0xff,0xff,0xff,0xff,0xfe,0xfe,0xfe,0xfd,0xfd,0xfc,0xfb,0xfa,0xfa,0xf9,0xf8,0xf6,
0xf5,0xf4,0xf3,0xf1,0xf0,0xee,0xed,0xeb,0xea,0xe8,0xe6,0xe4,0xe2,0xe0,0xde,0xdc,
0xda,0xd7,0xd5,0xd3,0xd0,0xce,0xcb,0xc9,0xc6,0xc4,0xc1,0xbe,0xbc,0xb9,0xb6,0xb3,
0xb0,0xad,0xaa,0xa7,0xa5,0xa2,0x9e,0x9b,0x98,0x95,0x92,0x8f,0x8c,0x89,0x86,0x83,
0x80,0x7c,0x79,0x76,0x73,0x70,0x6d,0x6a,0x67,0x64,0x61,0x5d,0x5a,0x58,0x55,0x52,
0x4f,0x4c,0x49,0x46,0x43,0x41,0x3e,0x3b,0x39,0x36,0x34,0x31,0x2f,0x2c,0x2a,0x28,
0x25,0x23,0x21,0x1f,0x1d,0x1b,0x19,0x17,0x15,0x14,0x12,0x11,0x0f,0x0e,0x0c,0x0b,
0x0a,0x09,0x07,0x06,0x05,0x05,0x04,0x03,0x02,0x02,0x01,0x01,0x01,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x01,0x01,0x01,0x02,0x02,0x03,0x04,0x05,0x05,0x06,0x07,0x09,
0x0a,0x0b,0x0c,0x0e,0x0f,0x11,0x12,0x14,0x15,0x17,0x19,0x1b,0x1d,0x1f,0x21,0x23,
0x25,0x28,0x2a,0x2c,0x2f,0x31,0x34,0x36,0x39,0x3b,0x3e,0x41,0x43,0x46,0x49,0x4c,
0x4f,0x52,0x55,0x58,0x5a,0x5d,0x61,0x64,0x67,0x6a,0x6d,0x70,0x73,0x76,0x79,0x7c
};
/* New variables */
volatile u8 G_u8UserAppFlags;                             /*!< @brief Global state flags */


/*--------------------------------------------------------------------------------------------------------------------*/
/* Existing variables (defined in other files -- should all contain the "extern" keyword) */
extern volatile u32 G_u32SystemTime1ms;                   /*!< @brief From main.c */
extern volatile u32 G_u32SystemTime1s;                    /*!< @brief From main.c */
extern volatile u32 G_u32SystemFlags;                     /*!< @brief From main.c */


/***********************************************************************************************************************
Global variable definitions with scope limited to this local application.
Variable names shall start with "UserApp_<type>" and be declared as static.
***********************************************************************************************************************/


/**********************************************************************************************************************
Function Definitions
**********************************************************************************************************************/

/*--------------------------------------------------------------------------------------------------------------------*/
/*! @publicsection */                                                                                            
/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------*/
/*! @protectedsection */                                                                                            
/*--------------------------------------------------------------------------------------------------------------------*/

/*!--------------------------------------------------------------------------------------------------------------------
@fn void UserAppInitialize(void)

@brief
Initializes the application's variables.

Should only be called once in main init section.

Requires:
- NONE

Promises:
- NONE

*/
void UserAppInitialize(void)
{
  /* LED Initialization */
    LATA = 0x80;
    
  /* Timer0 Control Register Initialization to turn timer on, asynchronous mode, 
   16-bit * FOSC/4, 1:x prescaler, 1:1 postscaler */
    
  /* (Timer0 Control Register 0) */
    //0b10010000
    //EN Bit 7 enables Timer0 if set to 1
    //Bit 6 is don't care
    //OUT Bit 5 is Timer0 output
    //MD16 Bit 4 enables 16-bit timer if set to 1
    //OUTPS Bits [3:0] enables 1:1 postscaler if set to 0000. Postscalers makes it slower.
    T0CON0 = 0x90;
    
  /* (Timer0 Control Register 1) All bits are set to 0. */
    //0b01010100
    //CS Bits [7:5] enables FOSC/4 if set to 010
    //ASYNC Bit 4 enables asynchronous mode if set to 1
    //CKPS Bits [3:0] enables 1:16 prescaler if set to 0100. Prescalers makes it faster.
    T0CON1 = 0x54;

} /* end UserAppInitialize() */

  
/*!----------------------------------------------------------------------------------------------------------------------
@fn void UserAppRun(void)

@brief Application code that runs once per system loop

Requires:
- 

Promises:
- 

*/
void UserAppRun(void)
{
/* Producing Triangle Waveform */
    //Changing DAC1DATL changes the voltage level, thus changes the output register
//    static bool max_level;
//    
//    if(DAC1DATL == 0xFF)
//    {
//        max_level = true;
//    }
//    
//    if(DAC1DATL == 0x00)
//    {
//        max_level = false;
//    }
//    
//    if(max_level)
//    {
//        DAC1DATL--;
//    }
//    
//    else
//    {
//        DAC1DATL++; 
//    }
    
 /* Producing Sinusoid */
    
    //index the array
    static int index = 0;
    
    //checks if the last point in the array is reached
    static bool last_value = false;
    
    
    if(index == 255)
    {
        //last point in array is reached
        last_value = true;
    }
    
    if(last_value)
    {
        //This sets DAC1DATL to the last point of the array
        DAC1DATL = UserApp_au8sinTable[index];
        
        //Roll back to zero since the last point is reached
        index = 0;
        last_value = false;
    }
    else
    {
        //Set DAC1DATL to the points in the array
        DAC1DATL = UserApp_au8sinTable[index];
        
        //Increment by 4 is to increment by 3 since index starts at zero.
        index += 3;
    }
    
} /* end UserAppRun */

/*--------------------------------------------------------------------
void TimeXus(u16 u16Time)
Sets Timer0 to count u16Microseconds_
Requires:
- Timer0 configured such that each timer tick is 1 microsecond
- INPUT_PARAMETER_ is the value in microseconds to time from 1 to 65535
Promises:
- Pre-loads TMR0H:L to clock out desired period
- TMR0IF cleared
- Timer0 enabled
*/
void TimeXus(u16 u16Time)
{
 /*u16Time equates to the number of ticks the clock processes before it overflows (0xFFFF)
  and the flag toggles. The clock is configured to run every 1 microsecond per tick*/
    
            /* OPTIONAL: range check and handle edge cases */
            /* Disable the timer during config */

            /* Preload TMR0H and TMR0L based on u16TimeXus */

            /* Clear TMR0IF and enable Timer 0 */

  /* Steps */
    
  //1) Stop the timer: Disable EN bit in T0CON0 by setting to 0
    /*We only want to change the EN 7th bit (set to 0), 
      ignore other bits (set to 1). */
     T0CON0 &= 0x7F;  
  
  //2) Preset TMROH and TMROL registers to the correct value
    /* Initialize TMROH by shifting u16Time by 8 bits to the right.
     This makes the high byte turn into LSB and the compiler accepts LSB and 
     stops there.*/
     //TMR0H = (u16Time >> 8) & 0xFF;
     TMR0H = (0xFFFF - u16Time) >> 8;
     
    /*Initialize TMROL by clearing the MSB and the compiler will read the LSB and
     stops there */
     TMR0L = 0xFFFF - u16Time;
     
  //3) Clear the TMR0IF bit (flag) that lives in the PIR3 register. Set Timer0
     /*Page 162: 7th bit is TMR0IF
       Clear means AND*/
       PIR3 &= 0x7F;
       T0CON0 |= 0x80;
    
  //4) Start the timer
       //DEBUG AND WATCH
            
} /* end TimeXus () */


/*------------------------------------------------------------------------------------------------------------------*/
/*! @privatesection */                                                                                            
/*--------------------------------------------------------------------------------------------------------------------*/





/*--------------------------------------------------------------------------------------------------------------------*/
/* End of File                                                                                                        */
/*--------------------------------------------------------------------------------------------------------------------*/
