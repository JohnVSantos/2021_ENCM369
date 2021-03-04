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
    //EN Bit 7 enables TImer0 if set to 1
    //Bit 6 is Don't care
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
 //Counter Initialization
 u32 u32Counter = PORTA; 
 
 while(u32Counter <= 0xBF)    
 {
     
  u32Counter++;
  LATA = u32Counter;
  
  //Delay
  for(u32 u32Counter = 800000; u32Counter > 0; u32Counter--)
  {
      
  }
  
 }
} /* end UserAppRun */

/*--------------------------------------------------------------------
void TimeXus(INPUT_PARAMETER_)
Sets Timer0 to count u16Microseconds_
Requires:
- Timer0 configured such that each timer tick is 1 microsecond
- INPUT_PARAMETER_ is the value in microseconds to time from 1 to 65535
Promises:
- Pre-loads TMR0H:L to clock out desired period
- TMR0IF cleared
- Timer0 enabled
*/
void TimeXus(INPUT_PARAMETER_)
{
 /* OPTIONAL: range check and handle edge cases */
 /* Disable the timer during config */

 /* Preload TMR0H and TMR0L based on u16TimeXus */

 /* Clear TMR0IF and enable Timer 0 */

  /* Steps */
  //1) Stop the timer: Disable EN bit in T0CON0 by setting to 0
  T0CON0 = 0x10;  
  
  //2) Preset TMROH and TMROL registers to the correct value
  TMROH = 0x00;
  TMROL = 0x00;
} /* end TimeXus () */


/*------------------------------------------------------------------------------------------------------------------*/
/*! @privatesection */                                                                                            
/*--------------------------------------------------------------------------------------------------------------------*/





/*--------------------------------------------------------------------------------------------------------------------*/
/* End of File                                                                                                        */
/*--------------------------------------------------------------------------------------------------------------------*/
