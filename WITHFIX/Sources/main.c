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
int arc_sine(double ratio); 
  
  
// Global Variable Declaration
  
int mode = 0;  
int state = 1;
int theta;

// Max and min values of the accelerometer
double max = 1599.0; 
double min = 1065.0; 
double mid = 1332.0; 

short ones;
short tens;
int setup[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09}; // Array of DDR1AD setups
//int setup_p[] = {0b00000, 0b00001, 0b00010, 0b00011, 0b00100, 0b00101, 0b00110, 0b00111, 0b01000, 0b01001};

double result;
int counter = 0;

int arc_sine(double ratio) {
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
  
  if (mode == 0){
    ATDCTL5 = 0x24;
    accinput = ATDDR0;
  }
  else if (mode == 1) {
    ATDCTL5 = 0x25; // Change the channel to AN5
    accinput = ATDDR0;
  }
  
  //SCI_OutString("Current Angle: ");
  
  // The middle point has an extra 20 point ceiling/buffer to work with. 
  if (accinput >= (mid+20)) { 
    result = (accinput - mid)/240;  // Normalize the ADC values to get an approximation of the ratio. 
    theta = arc_sine(result);  
 
    }
   
  else {
    result = 0;
    theta = 0;  
     
    }
 
  
  // we then send this to the arcsine function to get our current angle. 
  //SCI_OutUDec(mode);
  
  //OutCRLF();
  if (theta > 90) {
    // This case catches angles out of range. 
    ones = 0;
    tens = 9;
    theta = 90; 
  } 
  
  
  else {
    ones = theta%10; // ones column of the decimal number
    tens = theta/10; // tens column of the decimal number
  }
  
  //SCI_OutUDec(mode);
  
  SCI_OutUDec(theta);
  OutCRLF();
 
   
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

 // Now starts timer and interrupt register configuration.
  TIE   = 0x03;

  PERT  = 0x03;

  TIOS  = 0xFC;

  TSCR1 = 0x90;

  TSCR2 = 0x04;

  TCTL3 = 0x00;

  TCTL4 = 0x0A;      
  
	EnableInterrupts; //CodeWarrior's method of enabling interrupts
   
   ////////////////a/////////////////////////////////////
  /*ESDUINO PORT CONFIGURATION ABOVE*/
 
    /* Esduino Loops Forever*/
  //////////////////////////////////////////////////// 
  
  SCI_Init(9600);
  while(state==1){
    
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
  unsigned int temp; //DON'T EDIT THIS
  
  mode++; 
  mode%=2;
  temp = TC0; 
}
  
  interrupt  VectorNumber_Vtimch1 void ISR_Vtimch1(void)
{
  unsigned int temp; //DON'T EDIT THIS
  
  state++;
  state%=2; 
  temp = TC0;       //Refer back to TFFCA, we enabled FastFlagClear, thus by reading the Timer Capture input we automatically clear the flag, allowing another TIC interrupt
  }



