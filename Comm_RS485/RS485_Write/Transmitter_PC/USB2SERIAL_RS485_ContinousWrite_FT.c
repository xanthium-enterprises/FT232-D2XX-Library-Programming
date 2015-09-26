
	//====================================================================================================//
	// USB to RS485 conversion  using USB2SERIAL V2.0  (Write) (Transmitter Side)                         //
	//----------------------------------------------------------------------------------------------------//
	// Program to send a character through RS485 link from PC/Laptop to MSP430 microcontroller in a loop. //
	// The Program runs on the PC side and uses ftd2xx library from FTDI to communicate with USB2SERIAL-  //
	// hardware board which converts the USB signals to RS485.                                            //       
	//                                                                                                    //
	// Program runs on the PC side (Windows) and transmits a single character in a loop                   //            
	// Program opens a connection to the USB2SERIAL board and sets the Parity bits,baudrate etc for -     //
	// -communication.Program then puts the FT232(in USB2SERIAL board) in CBUS bit bang mode to use CBUS1 //
	// and CBUS2 to control ~RE and DE.                                                                   //
    //                                                                                                    //
	// BaudRate     -> 9600                                                                               //
	// Data formt   -> 8 databits,No parity,1 Stop bit (8N1)                                              //
	// Flow Control -> None                                                                               //
	//----------------------------------------------------------------------------------------------------//
	//                                                                                                    //
    //  |------------|                                                                                    //
	//  | RS485      |                                               +---------+     +-----------+        //
	//  | Write.exe  |             USB2SERIAL V2.0                   |		 RO|---->|P1.1(RXD)  |        //
	//  |------------|            |--------------|                   |      ~RE|-----|P2.1       |        //
	//   \ [][][][][] \===========| USB -> RS485 |~~~~~~~~~~~~~~~~~~~|A,B      |     |           |        //
	//    \------------\   USB    |--------------|      Twisted      |       DE|-----|P2.0       |        //
	//        Laptop                                     Pair        |	     DI|<----|P1.2(TXD)  |        //
	//                                                               +---------+     +-----------+        //
	//                              						            MAX485        MSP430G2553         //
	//                                                                                                    //
	//      [Transmitter] --------------------------------------->   [--------Reciever-----------]        //
	//                                                                                                    //
	//====================================================================================================//
	// Pin Configuration for  USB2SERIAL V2.0 Board                                                       //
	//                                                                                                    //
	//  		+==========================================================+                              //
	//			|	 +-----------+               +---------+               |                              //
	//  		|    |   	  TXD|-------------->|DI       |               |                              //
	// 	 	 +--|	 |        RXD|---------------|RO      A|------+        |                              //
	//	USB	 |	     |USB        |               |         |      |        |                              //
	// 	     +--|    |      CBUS1|---------------|~RE     B|------|--+     |                              //
	//  		|    |	    CBUS2|---------------|DE       |      |  |     |                              //
	//  		|    +-----------+               +---------+      |  |     |                              //
	//			|		FT232RL                     RS485         |  |     |                              //
	//  		+================================================[A]=[B]===+                              //
	//                                                             RS485                                  //
	//                                                                                                    //
	//		 Note :- Put the jumpers on USB2SERIAL V2.0 Board to RS485 mode                               //
	//=========================================================================================================//
	// Compiler  :	gcc 4.8.1 (MinGW)                                                                          //
	// Library   :  ftd2xx.lib                                                                                 //
	// Commands  :  gcc -o USB2SERIAL_RS485_ContinousWrite_FT USB2SERIAL_RS485_ContinousWrite_FT.c ftd2xx.lib  //
	// OS        :	Windows(Windows 7)                                                                         //
	// Programmer:	Rahul.S                                                                                    //
	// Date	     :	17-April-2014                                                                              //
	//=========================================================================================================//

	//====================================================================================================//
	// NOTE:-                                                                                             //
	//			Set the CBUS pins to I/O mode using FT_Prog.exe before running the Program                //
    //          USB2SERIAL jumpers should be set to RS485 mode                                            //
	//====================================================================================================//


	//======================================================================================//
	//  IF YOU ARE USING Archive CDM 2.08.30 WHQL Certified.zip FROM FTDI WEBSITE           //
	//======================================================================================//
	// ftd2xx.h   - CDM 2.08.30 WHQL Certified\CDM v2.08.30 WHQL Certified\ftd2xx.h         //
	// ftd2xx.lib - CDM 2.08.30 WHQL Certified\CDM v2.08.30 WHQL Certified\i386\ftd2xx.lib  //
	//======================================================================================//

	#include <stdio.h>
	#include <windows.h>		// for windows specific keywords in ftd2xx.h
	#include "ftd2xx.h"			// Header file for ftd2xx.lib

    #define RS485_PIN_TRANSMIT

	void main(void)
	{
		void Delay(void);                       // Delay function
		setvbuf(stdout,NULL,_IONBF,0);     		// Used to flush the IO buffers otherwise-
		setvbuf(stderr,NULL,_IONBF,0);     		//-eclipse terminal will behave strangely


		FT_HANDLE ft_handle;               		// Declaring the handle to the chip
		FT_STATUS ft_status;               		// Variable for storing status of the operation

		DWORD     BaudRate;                		// Variable to hold the baud rate
		char      TxByte;                       // Variable to hold the byte to be tx'ed
		DWORD     NoOfBytesWritten = 0;         // No of Bytes written to the port

		UCHAR     Mask;                         // for selecting which pins are input/output
		UCHAR     Mode;                         // Selects the mode of operation for the chip

		int i = 1;

		//-------------------------------  Opening the Connection to the chip -----------------------------------//

		ft_status = FT_Open(0,&ft_handle); 		// Opening a connection to the connected FT232RL chip

		if(ft_status == FT_OK)             		// Error checking for FT_Open()
			printf("Connection to the chip opened successfully\n");
		else
			printf("error in opening connection,Chip not connected or loose cable\n");

		//--------------------------------------------------------------------------------------------------------//




		//-------------------------------  Setting the baud rate of the chip -------------------------------------//

		BaudRate = 9600;                   		// Set BaudRate = 9600
		FT_SetBaudRate(ft_handle,BaudRate);		// Setting the baudrate for the chip for 9600bps

		if(ft_status == FT_OK)             		//Error checking for FT_SetBaudRate()
			printf("Baud rate set to %d\n",BaudRate);
		else
			printf("Error in setting baud rate\n");

		//--------------------------------------------------------------------------------------------------------//



		//--------------------------- Setting Data bits,Stop bits,Parity Bits ------------------------------------//

				ft_status = FT_SetDataCharacteristics( ft_handle, 		// Handle of the chip(FT232)
											           FT_BITS_8,       // No of Data bits = 8
											           FT_STOP_BITS_1,  // No of Stop Bits = 1
						                               FT_PARITY_NONE	// Parity = NONE
						                              );
				if(ft_status == FT_OK)
					printf("Format-> 8 DataBits,No Parity,1 Stop Bit (8N1)\n");
				else
					printf("Error in setting Data Format \n");


				//---------------- Setting Flow Control bits ------------------------------//

				ft_status = FT_SetFlowControl( ft_handle,		// Handle of the chip(FT232)
						                       FT_FLOW_NONE,    // No Flow control
						                       NULL,            // XON  = Null since no Flow control
						                       NULL             // XOFF = Null since no Flow control
						                      );

				if(ft_status == FT_OK)
				    printf("Flow Control = None \n");
				else
					printf("Error in setting Flow Control \n");






		//------------------------ Putting the Chip in CBUS bit Bang Mode ---------------------------------------//

		Mode = 0x20;                                     // Select Chip mode as CBUS Bit Bang

		//--------------------------------------------------------------------------------------------------------------------------------//
		//  Calculating the Mask Value in CBUS Bit Bang Mode                                                                              //
		//													                                                                              //
		//  +------------------------------------------------------+                                                                      //
		//  |<------------------- Mask(8bit) --------------------->|  Mask is an 8 bit Variable                                           //
		//  +-----------------------+------+-----------------------+                                                                      //
		//  |    Direction(4bits)   |      |   Data (4bits)        |  Upper Nibble controls the Direction,LowerNibble controls data bits  //
		//  +-----------------------+------+-----------------------+                                                                      //
		//  |  7  |  6  |  5  |  4  |      |  3  |  2  |  1  |  0  |                                                                      //
		//  +-----+-----+-----+-----+------+-----+-----+-----+-----+                                                                      //
		//  |CBUS3|CBUS2|CBUS1|CBUS0|      |CBUS3|CBUS2|CBUS1|CBUS0|  CBUS1 Connected to ~RE, CBUS2 Connected to DE                       //
		//  +-----+-----+-----+-----+------+-----+-----+-----+-----+                                                                      //
		//  |     |     |  __ |     |      |     |     | __  |     |                         __                                           //
		//  |  x  | DE  |  RE |  x  |      |  x  | DE  | RE  |  x  |  Data For TX,{ CBUS1 -> RE = High } and { CBUS2 -> DE = HIGH }       //
		//  +-----+-----+-----+-----+------+-----+-----+-----+-----+                                                                      //
		//  |  0  |  1  |  1  |  0  |      |  0  |  1  |  1  |  0  |  Direction For TX,{ CBUS1->RE = Output } and { CBUS2->DE = Output }  //
		//  +-----------------------+------+-----------------------+                                                                      //
		//  |                         0x66                         |                                                                      //
		//  +------------------------------------------------------+                                                                      //
		//                                                                                                                                //
        //--------------------------------------------------------------------------------------------------------------------------------//
 
 		Mask =  0x66;  //To activate the RE and DE signals for MAX485,
					   // ~RE -> High 
					   //  DE -> High
					   
		ft_status = FT_SetBitMode(ft_handle,Mask,Mode);  // Opening  Bit Bang Mode to put the chip in Transmit Mode

		if(ft_status == FT_OK)
		   	printf("Opening CBUS Bit Bang Mode successful\n");
		else
		   	printf("ERROR in Opening CBUS Bit Bang Mode\n");
		//--------------------------------------------------------------------------------------------------------//
	
		while(1)
		{
			//-------------------------------  Writing a byte to serial port -----------------------------------------//

			TxByte = 'A';
			ft_status = FT_Write( ft_handle,         // Handle to the chip
								  &TxByte,           // Variable Containing the byte to be Txed
							      sizeof(TxByte),    // sizeof(TxByte) = char
							      &NoOfBytesWritten  // No of Bytes written to the port
							     );

		    if(ft_status == FT_OK)             		 // Error checking for FT_Writee()
		       printf("%c written to the serial port at %d bps - [%d]\n",TxByte,BaudRate,i);
		    else
			   printf("Error in writing to port\n");
			 
			 i++;

		     //--------------------------------------------------------------------------------------------------------//
			 Delay();
		}


		FT_Close(ft_handle);                      // Closing the handle to the chip
		getch();

	}

	Delay()
	{
			int i = 0;
			int j = 0;
			
			for(j = 0;j < 0xFF; j++)
			    {
					for(i = 0;i < 0xFFFF;i++);
					for(i = 0;i < 0xFFFF;i++);
					for(i = 0;i < 0xFF;i++);
					for(i = 0;i < 0xFF;i++);
				}
			
	}