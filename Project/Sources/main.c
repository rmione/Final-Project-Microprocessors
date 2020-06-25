//*********************************************************************  
//*                         Lab 4 MILESTONE 1                          
//*                       McMaster University                         
//*                      2DP4 Microcontrollers                        
//*                          Lab Section 08                           
//*                  Riley Mione mioner 400123989               
//*            Ethan Crane-Vaillancourt cranevae 400117468               
//*********************************************************************
//*********************************************************************
//*                          Description                              
//*                       Lab 4 Milestone 1                                    
//*          LED flashes number of times button is pressed                                                                                                       
//*********************************************************************
// Clock Speed is 6.25 MHz as written                                //

/*Include*/
#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */

/*Prototypes*/
void Lab4Delay1ms(unsigned int numTimes);
void OutCRLF(void);

int counter = 0; // Global counter variable for convenience's sake! 
  
//MAIN.C FOR LAB 4
void main(void) {		
 
//Set Ports
DDRJ = 0xFF;      //set all port J as output

//The next six assignment statements configure the Timer Input Capture                                                   
         
 TIE   = 0x03;

  PERT  = 0x03;

  TIOS  = 0xFC;

  TSCR1 = 0x90;

  TSCR2 = 0x04;

  TCTL3 = 0x00;

  TCTL4 = 0x0A;

         
EnableInterrupts; //CodeWarrior's method of enabling interrupts
 
//Esduino Loops Forever
  for(;;){
  }  
}

  
interrupt  VectorNumber_Vtimch0 void ISR_Vtimch0(void)
{
  unsigned int temp; //DON'T EDIT THIS
  
  int i = 0;
  counter ++; 
  for(i=counter-1; i>=0; i--) {
    PTJ = 0x01; // LED on!
    Lab4Delay1ms(250); 
    PTJ ^= 0x01; // XORs and changes to off. 
    Lab4Delay1ms(250); 
  }

   
  
  //RESETS INTERRUPT
  temp = TC0;       //Refer back to TFFCA, we enabled FastFlagClear, thus by reading the Timer Capture input we automatically clear the flag, allowing another TIC interrupt
  }
  
  interrupt  VectorNumber_Vtimch1 void ISR_Vtimch1(void)
{
  unsigned int temp; //DON'T EDIT THIS
  
  int i = 0;
  counter ++; 
  for(i=counter-1; i>=0; i--) {
    PTJ = 0x01; // LED on!
    Lab4Delay1ms(250); 
    PTJ ^= 0x01; // XORs and changes to off. 
    Lab4Delay1ms(250); 
  }

   
  
  //RESETS INTERRUPT
  temp = TC0;       //Refer back to TFFCA, we enabled FastFlagClear, thus by reading the Timer Capture input we automatically clear the flag, allowing another TIC interrupt
  }

/* FUNCTIONS GO BELOW: Don't Edit */

// Lazy delay function to waste time for 1ms. Avoids the use of the timer, which is being used elsewhere
void Lab4Delay1ms(unsigned int numTimes){
  unsigned int i;
  unsigned int j;
  
  for(j = 0; j<numTimes; j++){
    for(i = 0; i<68; i++){
      // Delay
      PTJ = PTJ;
      PTJ = PTJ;
      PTJ = PTJ;
      PTJ = PTJ;
      PTJ = PTJ;
    }
  }   
}