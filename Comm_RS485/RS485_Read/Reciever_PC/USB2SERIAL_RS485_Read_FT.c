
	//====================================================================================================//
	// USB to RS485 conversion using USB2SERIAL V2.0 (Read) (Reciever Side)                               //
	//----------------------------------------------------------------------------------------------------//
	// Program waits for the character transmitted by the MSP430 along the RS485 link and displays the    //       
	// recieved character on the PC Console.USB2SERIAL V2.0 board is used to convert the RS485 signals to //
	// USB which is then read by the PC.                                                                  //
	//                                                                                                    //
	// Program runs on the PC side (Windows) and waits for a character send by the MSP430.Program opens   //
	// a connection to the USB2SERIAL board and sets the Parity bits,baudrate etc for communication.      //
	// Program then puts the FT232 (in USB2SERIAL board) in CBUS bit bang mode to use CBUS1 and CBUS2     //
	// to control ~RE and DE.                                                                             //
    //                                                                                                    //
	// BaudRate     -> 9600                                                                               //
	// Data formt   -> 8 databits,No parity,1 Stop bit (8N1)                                              //
	// Flow Control -> None                                                                               //
	//----------------------------------------------------------------------------------------------------//
	//                                                                                                    //
    //  |------------|                                                                                    //
	//  | RS485      |                                               +---------+     +-----------+        //
	//  | Read.exe   |             USB2SERIAL V2.0                   |		 RO|---->|P1.1(RXD)  |        //
	//  |------------|            |--------------|                   |      ~RE|-----|P2.1       |        //
	//   \ [][][][][] \===========| USB <- RS485 |~~~~~~~~~~~~~~~~~~~|A,B      |     |           |        //
	//    \------------\   USB    |--------------|      Twisted      |       DE|-----|P2.0       |        //
	//        Laptop                                     Pair        |	     DI|<----|P1.2(TXD)  |        //
	//                                                               +---------+     +-----------+        //
	//                              						            MAX485        MSP430G2553         //
	//                                                                                                    //
	//    [ Reciever ] <------------------------------------------- [--------Transmitter-----------]      //
	//                                                                                                    //
	//====================================================================================================//
	// Pin Configuration for  USB2SERIAL V2.0 Board                                                       //
	//                                                                                                    //
	//  		+==========================================================+                              //
	//			|	 +-----------+               +---------+               |                              //
	//  		|    |   	  TXD|-------------->|DI       |               |                              //
	// 	 	 +--|	 |        RXD|<--------------|RO      A|------+        |                              //
	//	USB	 |	     |USB        |               |         |      |        |                              //
	// 	     +--|    |      CBUS1|---------------|~RE     B|------|--+     |                              //
	//  		|    |	    CBUS2|---------------|DE       |      |  |     |                              //
	//  		|    +-----------+               +---------+      |  |     |                              //
	//			|		FT232RL                     RS485         |  |     |                              //
	//  		+================================================[A]=[B]===+                              //
	//                                                             RS485                                  //
	//                                                                                                    //
	//		 Note :- Put the jumpers on USB2SERIAL V2.0 Board to RS485 mode                               //
	//====================================================================================================//
	// Compiler  :	gcc 4.8.1 (MinGW)                                                                     //
	// Library   :  ftd2xx.lib                                                                            //
	// Commands  :  gcc -o USB2SERIAL_RS485_Read_FT USB2SERIAL_RS485_Read_FT.c ftd2xx.lib                 //
	// OS        :	Windows(Windows 7)                                                                    //
	// Programmer:	Rahul.S                                                                               //
	// Date	     :	17-April-2015                                                                         //
	//====================================================================================================//
	//====================================================================================================//
	// www.xanthium.in										                                              //
	// Copyright (C) 2015 Rahul.S                                                                         //
	//====================================================================================================//
	//====================================================================================================//
	// NOTE:-                                                                                             //
	//			Set the CBUS pins to I/O mode using FT_Prog.exe before running the Program                //
    //                                                                                                    //
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
		setvbuf(stdout,NULL,_IONBF,0);     		// Used to flush the IO buffers otherwise-
		setvbuf(stderr,NULL,_IONBF,0);     		//-eclipse terminal will behave strangely


		FT_HANDLE ft_handle;               		// Declaring the handle to the chip
		FT_STATUS ft_status;               		// Variable for storing status of the operation

		DWORD     BaudRate;                		// Variable to hold the baud rate
		char      RxBuffer[100];                // Char Array to store the received bytes

		UCHAR     Mask;                         // for selecting which pins are input/output
		UCHAR     Mode;                         // Selects the mode of operation for the chip

		HANDLE    WindowsEventHandle;			// Win32 handle for (Windows)Event Creation
		DWORD     dwEventMask;					// Event Mask for setting conditions for triggering the event
		DWORD     RxQueueBytes  = 0;		    // No Of Bytes in Receive  Queue
		DWORD     TxQueueBytes  = 0;			// No Of Bytes in Transmit Queue
		DWORD     EventStatus   = 0;			// current state of	the event status
		DWORD     BytesReceived = 0;            // No of Bytes received
		DWORD     Count = 0;
		
		printf("\n\n\n   +========================================================+");
		printf("\n   |      RS485 Mode - Reception (using ftd2xx.lib)         |");
		printf("\n   +========================================================+");

		//-------------------------------  Opening the Connection to the chip -----------------------------------//

		ft_status = FT_Open(0,&ft_handle); 		// Opening a connection to the connected FT232RL chip

		if(ft_status == FT_OK)             		// Error checking for FT_Open()
			printf("\n\n    Connection to the chip opened successfully");
		else
			printf("\n\n    Error in opening connection,Chip not connected or loose cable");

		//--------------------------------------------------------------------------------------------------------//




		//-------------------------------  Setting the baud rate of the chip -------------------------------------//

		BaudRate = 9600;                   		// Set BaudRate = 9600
		FT_SetBaudRate(ft_handle,BaudRate);		// Setting the baudrate for the chip for 9600bps

		if(ft_status == FT_OK)             		//Error checking for FT_SetBaudRate()
			printf("\n\n    Baud rate set to %d",BaudRate);
		else
			printf("\n\n    Error in setting baud rate");

		//--------------------------------------------------------------------------------------------------------//



		//--------------------------- Setting Data bits,Stop bits,Parity Bits ------------------------------------//

				ft_status = FT_SetDataCharacteristics( ft_handle, 		// Handle of the chip(FT232)
											           FT_BITS_8,       // No of Data bits = 8
											           FT_STOP_BITS_1,  // No of Stop Bits = 1
						                               FT_PARITY_NONE	// Parity = NONE
						                              );
				if(ft_status == FT_OK)
					printf("\n    Format-> 8 DataBits,No Parity,1 Stop Bit (8N1)");
				else
					printf("\n    Error in setting Data Format");


		//----------------------------- Setting Flow Control bits ------------------------------------------------//

				ft_status = FT_SetFlowControl( ft_handle,		// Handle of the chip(FT232)
						                       FT_FLOW_NONE,    // No Flow control
						                       NULL,            // XON  = Null since no Flow control
						                       NULL             // XOFF = Null since no Flow control
						                      );

				if(ft_status == FT_OK)
				    printf("\n    Flow Control = None");
				else
					printf("\n    Error in setting Flow Control ");


		//---------------------------------- Setting Timeouts ---------------------------------------------------//
				
				ft_status = FT_SetTimeouts(ft_handle,500,500); //Read/Write Timeout =500 MilliSeconds
				if(ft_status == FT_OK)
					printf("\n    Timeouts Set");
				else
					printf("\n    Error in setting Time outs");

		//------------------------ Putting the Chip in CBUS bit Bang Mode ---------------------------------------//

		Mode = 0x20;                                     // Select Chip mode as CBUS Bit Bang

		//--------------------------------------------------------------------------------------------------------------------------------------//
		//  Calculating the Mask Value in CBUS Bit Bang Mode                                                                                    //
		//																																		//
		//  +------------------------------------------------------+                                                                            //
		//	|<------------------- Mask(8bit) --------------------->|     Mask is an 8 bit Variable                                              //
		//  +-----------------------+------+-----------------------+                                                                            //
		//  |    Direction(4bits)   |      |   Data (4bits)        |	 Upper Nibble controls the Direction,LowerNibble controls data bits     //
		//  +-----------------------+------+-----------------------+                                                                            //
		//  |  7  |  6  |  5  |  4  |      |  3  |  2  |  1  |  0  |                                                                            //
		//  +-----+-----+-----+-----+------+-----+-----+-----+-----+                        __                                                  //
		//  |CBUS3|CBUS2|CBUS1|CBUS0|      |CBUS3|CBUS2|CBUS1|CBUS0|     CBUS1 Connected to RE, CBUS2 Connected to DE                           //
		//  +-----+-----+-----+-----+------+-----+-----+-----+-----+                                                                            //
		//	|     |		|  __ |     |      |     |     | __  |     |                            __                                              //
		//  |  x  | DE  |  RE |  x  |      |  x  | DE  | RE  |  x  |     Data For RX,{ CBUS1 -> RE = LOW } and { CBUS2 -> DE = LOW }            //
		//  +-----+-----+-----+-----+------+-----+-----+-----+-----+                                 __                                         //
		//  |  0  |  1  |  1  |  0  |      |  0  |  0  |  0  |  0  |     Direction For TX,{ CBUS1 -> RE = Output } and { CBUS2 -> DE = Output } //
		//  +-----------------------+------+-----------------------+                                                                            //
		//  |                         0x60                         |                                                                            //
		//  +------------------------------------------------------+                                                                            //
		//                                                                                                                                      //
        //--------------------------------------------------------------------------------------------------------------------------------------//

 		Mask =  0x60;  //To activate the RE and DE signals for MAX485,

		ft_status = FT_SetBitMode(ft_handle,Mask,Mode);  // Opening  Bit Bang Mode to put the chip in Transmit Mode

		if(ft_status == FT_OK)
		   	printf("\n\n    Opening CBUS Bit Bang Mode successful");
		else
		   	printf("\n\n    Error in Opening CBUS Bit Bang Mode");
		//--------------------------------------------------------------------------------------------------------//



		//-------------------------------------- Creating a Kernel Event -----------------------------------------//

		WindowsEventHandle = CreateEvent( NULL,  		// Default Security Attributes
						                  FALSE, 		// Auto Reset Event
						                  FALSE, 		// Initial State of the Event is Non Signalled
						                  "FT232Event"	// Name of the event
						                 );

		if(WindowsEventHandle == INVALID_HANDLE_VALUE)
			printf("\n\n    Error in Creating Event");
		else
		    printf("\n\n    Event Created Successfully");



		//-------------------------------- Setting up Event Notification --------------------------------------------//

		dwEventMask = FT_EVENT_RXCHAR; //Receiving a Character should trigger the event

		ft_status = FT_SetEventNotification( ft_handle,		    // Handle of the Chip (FT232)
						 	 	 	 	 	 dwEventMask,       // Used to Select which action should trigger the Event
						 	 	 	 	 	 WindowsEventHandle // Handle of the Windows Event
						                    );
		 if(ft_status == FT_OK)
			printf("\n    FT_SetEventNotifiation() Successful");
		 else
			printf("\n    FT_SetEventNotifiation() Failure ");



		//---------------------------- Waiting for the event to happen -----------------------------------------------//

		printf("\n\n    Waiting for Event to happen.....");

		WaitForSingleObject(WindowsEventHandle,INFINITE); //Waiting for the Event to return,No time out

		printf("\n\n    Wait function returned");

		//---------------------------------- Checking Status of the Chips UART ---------------------------------------//

		ft_status = FT_GetStatus( ft_handle,		// Handle to the Chip
						 	 	  &RxQueueBytes,    // No Of Bytes in Receive  Queue
						 	 	  &TxQueueBytes,	// No Of Bytes in Transmit Queue
						 	 	  &EventStatus
						 	 	 );

				 if(RxQueueBytes  > 0)       // If Data Received
				 {

					 printf("\n\n    %d bytes  received\n\n",RxQueueBytes);

					 ft_status = FT_Read( ft_handle,		// Handle to the Chip
							 	 	 	  RxBuffer,     	// Pointer to the Buffer for storing received data
							 	 	 	  RxQueueBytes, 	// No of Bytes in Receive  Queue
							 	 	 	  &BytesReceived	// number of bytes read from the device.
							 	 	 	 );

					 printf("    ");
					 while(Count < RxQueueBytes)
					 { 
						printf("%c",RxBuffer[Count]);
						Count++;
					 }

				 }



		FT_Close(ft_handle);                      // Closing the handle to the chip
		printf("\n\n   +========================================================+\n\n\n");
		getch();
	}
