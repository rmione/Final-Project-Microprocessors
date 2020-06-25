//*********************************************************************  
//*                         Lab 4 MILESTONE                           
//                    Computer Engineering 2DP4  
//                       McMaster University                       
//                         Final Project
//                    Code Written by Riley Mione
//    References made to MC9S12G Reference Manual and Lecture Slides


// INCLUDE STATEMENTS 
#include <hidef.h>     
#include "derivative.h"    
#include "SCI.h"


// FUNCTION PROTOTYPES
void Lab4Delay1ms(unsigned int numTimes);
void OutCRLF(void);
double arcsin(double angle); 
  
  
// Global Variable Declaration
  
  
int accinput; 
double val;  
int theta; 
    
// Max and min values of the accelerometer
double max = 1599.0; 
double min = 1065.0; 
double mid = 1332.0; 


double bruh(double ratio) {
  // Taylor series approximation of arcsine given the angle in radians 
  double output = ratio + ((ratio*ratio*ratio)/6) + (3*(ratio*ratio*ratio*ratio*ratio)/40) + (5*(ratio*ratio*ratio*ratio*ratio*ratio*ratio)/112);
  return output;                                                                                              
}

void main(void) {		

  // Inside the main loop all the registers are configured
  ATDCTL1 = 0x4F; 
  ATDCTL3 = 0x88; // Right justified w/ one sample per sequence 
  ATDCTL4 = 0x02; 
  ATDCTL5 = 0x26; // Continuous conversion on specified channel (AN4)
  
  // Clock Speed related Registers 
  
  CPMUPROT = 0x26; // allow changes to cpu timing registers
  CPMUFLG = 0x00; // Makes f_pll = fvco/4
  CPMUCLKS = 0x80; // f_bus = f_pll/2 
  CPMUOSC = 0x80;  // 
  CPMUREFDIV = 0x01; 
  CPMUSYNR = 0x01; // Set CPU sync ratio value to 1
  CPMUPOSTDIV = 0x01; // Set CPU post ratio value to 1 
  
  
  DDR1AD = 0x10110000; // First 4 ports are inputs. 
  PER1AD = 0x01001111; // pull up resistors on the inputs
  ATDDIEN =0x10110000;// Ports 0-3 are analog inputs, ports 4-7 are digital. 
  
     /* ESDUINO PORT CONFIGURATION BELOW (Don't Edit) */
  /////////////////////////////////////////////////////  
  //Set Ports
  DDRJ = 0xFF;      //set all port J as output
/*
 * The next six assignment statements configure the Timer Input Capture                                                   
 */           
  TSCR1 = 0x90;    //Timer System Control Register 1
                    // TSCR1[7] = TEN:  Timer Enable (0-disable, 1-enable)
                    // TSCR1[6] = TSWAI:  Timer runs during WAI (0-enable, 1-disable)
                    // TSCR1[5] = TSFRZ:  Timer runs during WAI (0-enable, 1-disable)
                    // TSCR1[4] = TFFCA:  Timer Fast Flag Clear All (0-normal 1-read/write clears interrupt flags)
                    // TSCR1[3] = PRT:  Precision Timer (0-legacy, 1-precision)
                    // TSCR1[2:0] not used

  TSCR2 = 0x04;    //Timer System Control Register 2
                    // TSCR2[7] = TOI: Timer Overflow Interrupt Enable (0-inhibited, 1-hardware irq when TOF=1)
                    // TSCR2[6:3] not used
                    // TSCR2[2:0] = Timer Prescaler Select: See Table22-12 of MC9S12G Family Reference Manual r1.25 (set for bus/1)
  
                    
  TIOS = 0xFC;     //Timer Input Capture or Output capture
                    //set TIC[0] and input (similar to DDR)
  PERT = 0x03;     //Enable Pull-Up resistor on TIC[0] and TIC[1]

  TCTL3 = 0x00;    //TCTL3 & TCTL4 configure which edge(s) to capture
  TCTL4 = 0x0A;    //Configured for falling edge on TIC[0] (channel 0) and TIC[1] (channel 1)

/*
 * The next one assignment statement configures the Timer Interrupt Enable                                                   
 */           
   
  TIE = 0x03;      //Timer Interrupt Enable

/*
 * The next one assignment statement configures the ESDX to catch Interrupt Requests                                                   
 */           
  
	EnableInterrupts; //CodeWarrior's method of enabling interrupts
   
   /////////////////////////////////////////////////////
  /*ESDUINO PORT CONFIGURATION ABOVE*/
 
    /* Esduino Loops Forever*/
  //////////////////////////////////////////////////// 
  SCI_Init(9600); 
  for(;;){
    SCI_OutString("Current Z value ");
    accinput = ATDDR0;
    if (accinput >= mid) {
      val = (accinput - mid)/267;   
    }                   
    else if (accinput <= mid) {
      val = (mid - accinput)/267;
    }
    
    theta = bruh(val); 
    
     
    
    SCI_OutUDec(theta); 
    Lab4Delay1ms(500); 
  }
}         
interrupt  VectorNumber_Vtimch0 void ISR_Vtimch0(void)
{
  /* DECLARE ALL YOUR LOCAL VARIABLES BELOW*/
  /////////////////////////////////////////////////////
  unsigned int temp; //DON'T EDIT THIS


  /* DECLARE ALL YOUR LOCAL VARIABLES ABOVE*/   
  /////////////////////////////////////////////////////
  
    /* YOUR CODE GOES BELOW*/
  //////////////////////////////////////////////////// 
   
  
  
  
  // Available Functions for your use
  // Lab4Delay1ms(a): a*1ms delay
  
  
  
  
  
  
  
    // Functions available for serial communication (NOTE: Look at Challenge 5 on adding additional .c/.h)
  // Serial Communication Functions by default are not provided in this template  
  // SCI_init- Sets the baud rate
  // OutString - Outputs a string to Serial
  // OutChar - Output a character to Serial
  // OutUDec - Output a decimal to Serial
  // OutUHex - Output a hex to Serial
  // To print out a new line use SCI_OutChar(CR)
  
  
     /* YOUR CODE GOES ABOVE*/
  ////////////////////////////////////////////////////  
  
  /* RESETS INTERRUPT (Don't Edit)*/
  ////////////////////////////////////////////////////  
  temp = TC0;       //Refer back to TFFCA, we enabled FastFlagClear, thus by reading the Timer Capture input we automatically clear the flag, allowing another TIC interrupt
  }

 /*
 * This is the Interrupt Service Routine for TIC channel 1 (Code Warrior has predefined the name for you as "Vtimch1"                                                    
 */           
interrupt  VectorNumber_Vtimch1 void ISR_Vtimch1(void)
{

  unsigned int temp; 
  
  
  

  /* RESETS INTERRUPT (Don't Edit)*/
  ////////////////////////////////////////////////////  
  temp = TC1;       //Refer back to TFFCA, we enabled FastFlagClear, thus by reading the Timer Capture input we automatically clear the flag, allowing another TIC interrupt
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
