//*********************************************************************  
//*                         Lab 4 MILESTONE                           
//                    Computer Engineering class  
//                       School                       
//                         Final Project
//                    Code Written by 
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
  
  accinput = ATDDR0;
  
  SCI_OutString("Current Z value ");
  
  if (accinput >= (mid+20)) { 
    result = (accinput - mid)/240;  // Normalize the ADC values to get an approximation of the ratio. 
       
 
    }
   
  else {
    result = 0; 
     
    }
 

  // we then send this to the arcsine function to get our current angle. 
  SCI_OutUDec(bruh(result));
  
  
  
}

void main(void) {
  		
  
  // Inside the main loop all the registers are configured
  ATDCTL1 = 0x4F; 
  ATDCTL3 = 0x88; // Right justified w/ one sample per sequence 
  ATDCTL4 = 0x02; 
  ATDCTL5 = 0x25; // Continuous conversion on specified channel (AN4)
  
  // Clock Speed related Registers 
  
  CPMUPROT = 0x26; // allow changes to cpu timing registers
  CPMUFLG = 0x00; // Makes f_pll = fvco/4
  CPMUCLKS = 0x80; // f_bus = f_pll/2 
  CPMUOSC = 0x80;  // 
  CPMUREFDIV = 0x01; 
  CPMUSYNR = 0x01; // Set CPU sync ratio value to 1
  CPMUPOSTDIV = 0x01; // Set CPU post ratio value to 1 
  
  
  DDR1AD = 0x10100000; // First 4 ports are inputs. 
  PER1AD = 0x01011111; // pull up resistors on the inputs
  ATDDIEN =0x10100000;// Ports 0-3 are analog inputs, ports 4-7 are digital. 
  
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
    handler();
    Lab4Delay1ms(250);
    
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
