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
//PART 1 
//     //Read LATA to a temporary variable
//     u32 u32Counter = PORTA; 
//     
//     //Use a bitmask and bitwise operation to clear the 6 LSBs
//     u32Counter &= 0xCF;
//
//     //Use bitwise operation to update the 6 LSBs to the value you want
//     u32Counter++;
//
//     //Write the temporary variable back to LATA
//     LATA = u32Counter;   
     
//PART 2
    
     static int i = 0;
     u8 au8Pattern[] = {0x0C, 0x12, 0x21, 0x12, 0x0C};
     
     LATA = au8Pattern[i];
     
     if(i == 4)
     {
         i = 0;
     }
     else 
     {
         i++;
     }
     
     for(u32 u32Counter = 4000; u32Counter > 0; u32Counter--)
     {
         
     }
    
//Other Pattern
//    static int stateofLED = 0;
//    
//    static u8 u8Pattern[] = {0x00, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x21, 0x22, 0x24, 0x28, 0x30, 0x31, 0x32, 0x34, 0x38, 0x39, 0x3A, 0x3C, 0x3D, 0x3E, 0x3F};
//    
//    LATA = u8Pattern[stateofLED]; 
//    if (stateofLED == 22)
//    {
//     stateofLED = 0;   
//    }
//    else
//    {
//        stateofLED++;
//    }
     
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
