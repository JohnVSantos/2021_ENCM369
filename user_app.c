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
    //OUTPS Bits [3:0] enables 1:1 postscaler if set to 0000
    T0CON0 = 0x90;
    
  /* (Timer0 Control Register 1) All bits are set to 0. */
    //0b01010100
    //CS Bits [7:5] enables FOSC/4 if set to 010
    //ASYNC Bit 4 enables asynchronous mode if set to 1
    //CKPS Bits [3:0] enables 1:16 prescaler if set to 0100
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
    u8 u8Output_level = DAC1DATL;
    
    //Clear all bits except RA2
    LATA &= 0x08;
    
    if(u8Output_level == 0xFF)
    {
        u8Output_level = 0x00;
        LATA = 0x00;
    }
    
    else
    {
        DAC1DATL = u8Output_level;
        u8Output_level++;
        LATA++;
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
 /* OPTIONAL: range check and handle edge cases */
 /* Disable the timer during config */

 /* Preload TMR0H and TMR0L based on u16TimeXus */

 /* Clear TMR0IF and enable Timer 0 */

  /* Steps */
    u16Time -= 0xFFFF;
  //1) Stop the timer: Disable EN bit in T0CON0 by setting to 0
   /*We only want to change the EN 7th bit (set to 0), 
     ignore other bits (set to 1). */
     T0CON0 &= 0x7F;  
  
  //2) Preset TMROH and TMROL registers to the correct value
    /* Initialize TMROH by shifting u16Time by 8 bits to the right.
     This makes the high byte turn into LSB and the compiler accepts LSB and 
     stops there.*/
     TMR0H = (u16Time >> 8) & 0xFF;
     
    /*Initialize TMROL by clearing the MSB and the compiler will read the LSB and
     stops there */
     TMR0L = u16Time & 0x00FF;
     
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
