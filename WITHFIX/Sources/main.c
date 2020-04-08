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
#define PI (3.14)
// FUNCTION PROTOTYPES
void Lab4Delay1ms(unsigned int numTimes);
void OutCRLF(void);
int accinput;
double result;
int bruh(double ratio); 
  
  
// Global Variable Declaration
  
  
 
//double val;  
int theta;
//double result; 
    
// Max and min values of the accelerometer
double max = 1599.0; 
double min = 1065.0; 
double mid = 1332.0; 

short ones;
short tens;
int setup[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09}; // Array of DDR1AD setups
//int setup_p[] = {0b00000, 0b00001, 0b00010, 0b00011, 0b00100, 0b00101, 0b00110, 0b00111, 0b01000, 0b01001};

double result;


int bruh(double ratio) {
  /* Taylor series approximation of arcsine given the angle in radians 
     This approximation is not very good. The angles are a good margin off.
     I can correct for this in the normalization equation by lowering the denominator */
     
  double output = ratio + ((ratio*ratio*ratio)/6.0) + (3*(ratio*ratio*ratio*ratio*ratio)/40.0) + (5*(ratio*ratio*ratio*ratio*ratio*ratio*ratio)/112.0);
  // We want to return the angle in degrees
  return (output*(180/PI));                                                                                              
}

void OutCRLF(void){
  SCI_OutChar(CR);
  SCI_OutChar(LF);
  PTJ ^= 0x20;          // toggle LED D2
}




void handler() {
  // having a handler function promotes seperation of concerns . 
  
  accinput = ATDDR0;
  
  SCI_OutString("Current Angle: ");
  
  if (accinput >= (mid+20)) { 
    result = (accinput - mid)/240;  // Normalize the ADC values to get an approximation of the ratio. 
    theta = bruh(result);  
 
    }
   
  else {
    result = 0;
    theta = 0;  
     
    }
 
  
  // we then send this to the arcsine function to get our current angle. 
  SCI_OutUDec(theta);
  if (theta > 90) {
    // This case catches angles out of range. 
    ones = 0;
    tens = 9;
  } 
  
  else {
    ones = theta%10; // ones column of the decimal number
    tens = theta/10; // tens column of the decimal number
  }
  
  
 
   
  // This sets the registers equal to the BCD output needed. 
  PT1AD = setup[ones]; 
  PT0AD = setup[tens]; 
  
  
  
  
  
  
}

void main(void) {
  		
  
  // Inside the main loop all the registers are configured
  ATDCTL1 = 0x4F; 
  ATDCTL3 = 0x88; // Right justified w/ one sample per sequence 
  ATDCTL4 = 0x02; 
  ATDCTL5 = 0x24; // Continuous conversion on specified channel (AN4)
  
  // Clock Speed related Registers 
  
  CPMUPROT = 0x26; // allow changes to cpu timing registers
  CPMUFLG = 0x00; // Makes f_pll = fvco/4
  CPMUCLKS = 0x80; // f_bus = f_pll/2 
  CPMUOSC = 0x80;  // 
  CPMUREFDIV = 0x01; 
  CPMUSYNR = 0x01; // Set CPU sync ratio value to 1
  CPMUPOSTDIV = 0x01; // Set CPU post ratio value to 1 
  
  //DDRP = 0x1F; 
  
  DDR1AD = 0b10001111; // First 4 ports are inputs. 
  PER1AD = 0x01110000; // pull up resistors on the inputs
  DDR0AD = 0x0F;
 
  ATDDIEN= 0x10100000;// Ports 0-3 are analog inputs, ports 4-7 are digital. 
  
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
  
                    
  TIOS = 0xB0;     //Timer Input Capture or Output capture
                    //set TIC[0] and input (similar to DDR)
  PERT = 0x10;     //Enable Pull-Up resistor on TIC[0] and TIC[1]

  TCTL3 = 0x00;    //TCTL3 & TCTL4 configure which edge(s) to capture
  TCTL4 = 0x10;    //Configured for falling edge on TIC[0] (channel 0) and TIC[1] (channel 1)

/*
 * The next one assignment statement configures the Timer Interrupt Enable                                                   
 */           
   
  TIE = 0x03;      //Timer Interrupt Enable

/*
 * The next one assignment statement configures the ESDX to catch Interrupt Requests                                                   
 */           
  
	EnableInterrupts; //CodeWarrior's method of enabling interrupts
   
   ////////////////a/////////////////////////////////////
  /*ESDUINO PORT CONFIGURATION ABOVE*/
 
    /* Esduino Loops Forever*/
  //////////////////////////////////////////////////// 
  SCI_Init(9600); 
  
  for(;;){
    handler();
    Lab4Delay1ms(400);
    
  }
}



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

interrupt  VectorNumber_Vtimch0 void ISR_Vtimch0(void)
{
  /* DECLARE ALL YOUR LOCAL VARIABLES BELOW*/
  /////////////////////////////////////////////////////
  unsigned int temp; //DON'T EDIT THIS


  /* DECLARE ALL YOUR LOCAL VARIABLES ABOVE*/   
  /////////////////////////////////////////////////////
  
    /* YOUR CODE GOES BELOW*/
  //////////////////////////////////////////////////// 
   
  SCI_OutString("Hello");
  
  
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
  temp = TC1;       //Refer back to TFFCA, we enabled FastFlagClear, thus by reading the Timer Capture input we automatically clear the flag, allowing another TIC interrupt
  }


