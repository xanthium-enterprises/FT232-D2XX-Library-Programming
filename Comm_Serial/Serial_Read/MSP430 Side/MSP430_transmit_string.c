  
  //------------------------------------------------------------------------//
  // Program to Communicate with PC using UART of MSP430 @9600 bps ,8N!1    //
  // MSP430 will transmit a string of characters  "MSP430" to PC            //
  //------------------------------------------------------------------------//
  // DC0 @ 1MHz                                                             //
  // SMCLK @1MHz                                                            //
  // Waits for characters from PC serial Port                               //
  // Toggles P1.0 on RXing 'A'                                              //
  // Toggles P1.6 on RXing 'B'                                              //
  //------------------------------------------------------------------------//
  //                                                                        //
  // Hardware -> Launchpad Board ,USB2SERIAL Converter (Virtual COM Port)   //
  // Compiled on IAR Embedded Workbench for MSP430 version 5.30.1           //
  // 07-July-2014                                                           //
  // Rahul.S                                                                //
  //------------------------------------------------------------------------//


    #include "msp430g2553.h"
    void main(void)
    {
      WDTCTL = WDTPW + WDTHOLD; // Stop the Watch dog
      
      char TX_Buffer[] = {'M','S','P','4','3','0','\0'};
      char count = 0;
      //------------------- Configure the Clocks -------------------//
        
      if (CALBC1_1MHZ==0xFF)   // If calibration constant erased
         {	
            while(1);          // do not load, trap CPU!!
         } 

      DCOCTL  = 0;             // Select lowest DCOx and MODx settings
      BCSCTL1 = CALBC1_1MHZ;   // Set range
      DCOCTL  = CALDCO_1MHZ;   // Set DCO step + modulation 
       
      //------------------- Configure the Ports  -------------------//
      
      // Setting the UART function for P1.1 & P1.2
      P1SEL  |=  BIT1 + BIT2;  // P1.1 UCA0RXD input
      P1SEL2 |=  BIT1 + BIT2;  // P1.2 UCA0TXD output
      
      // Setting the direction for P1.0 and P1.6
      P1DIR  |=  BIT0 + BIT6;  // P1.0 and P1.6 output
      P1OUT  &= ~BIT0 + BIT6;  // Clear P1.0 and P1.6
        
      //-------------- Configure USCI_A0 in UART mode --------------//  
      
      UCA0CTL1 |=  UCSSEL_2 + UCSWRST;  // USCI Clock = SMCLK,USCI_A0 disabled
      UCA0BR0   =  104;                 //  104 From datasheet table-  
      UCA0BR1   =  0;                   // -selects baudrate =9600,clk = SMCLK
      UCA0MCTL  =  UCBRS_6;             // Modulation value = 6 from datasheet
      
      UCA0CTL1 &= ~UCSWRST;             // Clear UCSWRST to enable USCI_A0
      
      //-------------- Configure USCI_A0 interrupts  --------------// 
      
      //IE2 |= UCA0RXIE;                 //Enable Recieve interrupt 
      _BIS_SR(GIE);
      while (TX_Buffer[count] != '\0')
          {
              while (!(IFG2&UCA0TXIFG)); // USCI_A0 TX buffer ready?
              UCA0TXBUF = TX_Buffer[count];
              count ++;
          }
      
      _BIS_SR(LPM0_bits + GIE);        // Going to LPM0
        
     }//end of main()

    