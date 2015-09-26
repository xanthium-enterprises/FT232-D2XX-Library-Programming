	//======================================================================================//
	// Simple Program to receive data from an external device using D2XX interface          //
	// (ftd2xx.lib) at 9600bps.                                                             //
	// The Program uses a Windows Event to wait for the character to be received.           //
	//======================================================================================//
	// Uses the Following API's -                                                           //
	//-----------------------------                                                         //
    // 		FT_SetDataCharacteristics(); 		D2XX library (ftd2xx.lib)                   //
	//		FT_SetFlowControl(); 				D2XX library (ftd2xx.lib)                   //
	//		FT_Read();						 	D2XX library (ftd2xx.lib)                   //
	//		FT_SetEventNotification(); 			D2XX library (ftd2xx.lib)                   //
	//		FT_GetStatus(); 					D2XX library (ftd2xx.lib)                   //
	//		                                                                                //
	//		CreateEvent();						Win32 API    (windows.h)                    //
    //		WaitForSingleObject();				Win32 API    (windows.h)                    //
	//======================================================================================//
	// Compiler  :	gcc 4.8.1 (MinGW)                                                       //
	// Library   :  ftd2xx.lib                                                              //
	// Commands  :  gcc -o SerialPort_Read_D2XX SerialPort_Read_D2XX.c ftd2xx.lib           //
	// OS        :	Windows(Windows 7)                                                      //
	// Programmer:	Rahul.S                                                                 //
	// Date	     :	14-August-2014                                                          //
	//======================================================================================//

	//======================================================================================//
	//  IF YOU ARE USING Archive CDM 2.08.30 WHQL Certified.zip FROM FTDI WEBSITE           //
	//======================================================================================//
	// ftd2xx.h   - CDM 2.08.30 WHQL Certified\CDM v2.08.30 WHQL Certified\ftd2xx.h         //
	// ftd2xx.lib - CDM 2.08.30 WHQL Certified\CDM v2.08.30 WHQL Certified\i386\ftd2xx.lib  //
	//======================================================================================//


	#include <stdio.h>          // for setvbuf();
	#include <windows.h>		// for windows specific keywords in ftd2xx.h
	#include "ftd2xx.h"			// Header file for ftd2xx.lib
    int main(void)
	{
		setvbuf(stdout,NULL,_IONBF,0);		// required by eclipse cdt to properly-
		setvbuf(stderr,NULL,_IONBF,0);		//-display output in console window

		FT_HANDLE ft_handle;				// Handle to access the chip
		FT_STATUS ft_status;                // To store the status value

		HANDLE    WinHandle;                // Win32 handle for (Windows)Event Creation
		DWORD     dwEventMask;              // Event Mask for setting conditions for triggering the event
		DWORD     RxQueueBytes = 0;			// No Of Bytes in Receive  Queue
		DWORD     TxQueueBytes = 0;			// No Of Bytes in Transmit Queue
		DWORD     EventStatus  = 0;			// current state of	the event status

		char      RxBuffer[256];            // Buffer for received data
		DWORD     BytesReceived = 0;		// number of bytes read from the device(for FT_Read())
		DWORD     BaudRate = 0;             // BaudRate


		//------------------- Opening the Connection to the Chip -------------------//

		ft_status = FT_Open(0,&ft_handle);

		if(ft_status == FT_OK)
			printf("1) - Connection to FT232RL opened Successfully\n");
		else
			printf("E1) - Cannot open Connection to FT232RL \n");



		//-------------------- Setting the BaudRate ------------------------------//

		BaudRate = 9600;    // BaudRate = 9600

		ft_status = FT_SetBaudRate(ft_handle,BaudRate); //Setting up the BaudRate

		if(ft_status == FT_OK)
			printf("2) - Baud Rate set at %d bps\n",BaudRate);
		else
			printf("E2) - Error in setting BaudRate \n");



		//---------------- Setting Data bits,Stop bits,Parity Bits ----------------//

		ft_status = FT_SetDataCharacteristics( ft_handle, 		// Handle of the chip(FT232)
									           FT_BITS_8,       // No of Data bits = 8
									           FT_STOP_BITS_1,  // No of Stop Bits = 1
				                               FT_PARITY_NONE	// Parity = NONE
				                              );
		if(ft_status == FT_OK)
			printf("3) - Format-> 8 DataBits,No Parity,1 Stop Bit (8N1)\n");
		else
			printf("E3) - Error in setting Data Format \n");


		//---------------- Setting Flow Control bits ------------------------------//

		ft_status = FT_SetFlowControl( ft_handle,		// Handle of the chip(FT232)
				                       FT_FLOW_NONE,    // No Flow control
				                       NULL,            // XON  = Null since no Flow control
				                       NULL             // XOFF = Null since no Flow control
				                      );

		if(ft_status == FT_OK)
		    printf("4) - Flow Control = None \n");
		else
			printf("E4) - Error in setting Flow Control \n");

		//------------------------ Creating a Kernel Event -----------------------//

		 WinHandle = CreateEvent( NULL,  		// Default Security Attributes
				                  FALSE, 		// Auto Reset Event
				                  FALSE, 		// Initial State of the Event is Non Signalled
				                  "FT232Event"	// Name of the event (optional)
				                );

		 if( WinHandle == INVALID_HANDLE_VALUE)
			 printf("E5) - ERROR in Creating Event\n");
		 else
			 printf("5) - Event Created Successfully\n");

		 //----------------- Setting up Event Notification ----------------------//

		 dwEventMask = FT_EVENT_RXCHAR; //Receiving a Character should trigger the event

		 ft_status = FT_SetEventNotification( ft_handle,		// Handle of the Chip (FT232)
				 	 	 	 	 	 	 	  dwEventMask,      // Used to Select which action should trigger the Event
				 	 	 	 	 	 	      WinHandle         // Handle of the Windows Event
				                           );
		 if(ft_status == FT_OK)
		 	printf("6) - FT_SetEventNotification() Successful\n");
		 else
		 	printf("E6) - FT_SetEventNotification() Failure \n");

		 //----------------- Waiting for the event to happen -------------------//

		 printf("7) - Waiting for Event to happen\n");

		 WaitForSingleObject( WinHandle,INFINITE); //Waiting for the Event to return,No time out

		 printf("8) - Wait function returned\n");

		 //-------------------- Checking Status of the Chips UART --------------//

		 ft_status = FT_GetStatus( ft_handle,		// Handle to the Chip
				 	 	 	 	   &RxQueueBytes,   // No Of Bytes in Receive  Queue
				 	 	 	 	   &TxQueueBytes,	// No Of Bytes in Transmit Queue
				 	 	 	 	   &EventStatus
				 	 	 	 	  );

		 if(RxQueueBytes  > 0)       // If Data Received
		 {

			 printf("9) - %d bytes  received\n",RxQueueBytes);

			 ft_status = FT_Read( ft_handle,		// Handle to the Chip
					 	 	 	  RxBuffer,     	// Pointer to the Buffer for storing received data
					 	 	 	  RxQueueBytes, 	// No of Bytes in Receive  Queue
					 	 	 	  &BytesReceived	// number of bytes read from the device.
					 	 	 	 );

			 printf("10) - Data Received - %s",RxBuffer);

		 }

		 FT_Close(ft_handle); //Close the handle to the chip
		 getch();

	}
