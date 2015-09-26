

	//======================================================================================//
	// Simple Program to open a connection to the FTDI chip FT232RL using D2XX interface    //
	// (ftd2xx.lib)  and send a character('A') to the serial port at 9600bps                //
    //======================================================================================//
	// Uses the Following API's -                                                           //
	//-----------------------------                                                         //
	//      FT_Open();							D2XX library (ftd2xx.lib)                   //
	//		FT_SetBaudRate();					D2XX library (ftd2xx.lib)                   //
    // 		FT_SetDataCharacteristics(); 		D2XX library (ftd2xx.lib)                   //
	//		FT_SetFlowControl(); 				D2XX library (ftd2xx.lib)                   //
	//		FT_Write();							D2XX library (ftd2xx.lib)                   //
	//		FT_Close();                         D2XX library (ftd2xx.lib)                	//
	//======================================================================================//
	// Compiler  :	gcc 4.8.1 (MinGW)                                                       //
	// Library   :  ftd2xx.lib                                                              //
	// Commands  :  gcc -o SerialPort_Write_D2XX SerialPort_Write_D2XX.c ftd2xx.lib         //
	// OS        :	Windows(Windows 7)                                                      //
	// Programmer:	Rahul.S                                                                 //
	// Date	     :	04-july-2014                                                            //
	//======================================================================================//

	//======================================================================================//
	//  IF YOU ARE USING Archive CDM 2.08.30 WHQL Certified.zip FROM FTDI WEBSITE           //
	//======================================================================================//
	// ftd2xx.h   - CDM 2.08.30 WHQL Certified\CDM v2.08.30 WHQL Certified\ftd2xx.h         //
	// ftd2xx.lib - CDM 2.08.30 WHQL Certified\CDM v2.08.30 WHQL Certified\i386\ftd2xx.lib  //
	//======================================================================================//

	#include <stdio.h>
	#include <windows.h>		// for windows specific keywords in ftd2xx.h
	#include "ftd2xx.h"			// Header file for ftd2xx.lib
	void main(void)
	{
		FT_HANDLE ft_handle;               		// Declaring the handle to the chip
		FT_STATUS ft_status;               		// Variable for storing status of the operation
		DWORD     BaudRate;                		// Variable to hold the baud rate
		char      TxByte;                       // Variable to hold the byte to be tx'ed
		DWORD     NoOfBytesWritten = 0;         // No of Bytes written to the port



		//-------------------------------  Opening the Connection to the chip -----------------------------------//

		ft_status = FT_Open(0,&ft_handle); 		// Opening a connection to the connected FT232RL chip

		if(ft_status == FT_OK)             		// Error checking for FT_Open()
			printf("\n\n\tConnection to the chip opened successfully\n");
		else
			printf("\terror in opening connection,Chip not connected or loose cable\n");

		//--------------------------------------------------------------------------------------------------------//


		
		//-------------------------------  Setting the baud rate of the chip -------------------------------------//

		BaudRate = 9600;                   		// Set BaudRate = 9600
		FT_SetBaudRate(ft_handle,BaudRate);		// Setting the baudrate for the chip for 9600bps

		if(ft_status == FT_OK)             		//Error checking for FT_SetBaudRate()
			printf("\tBaud rate set to %d\n",BaudRate);
		else
			printf("\tError in setting baud rate\n");

		
		
		//--------------------------- Setting Data bits,Stop bits,Parity Bits ------------------------------------//

		ft_status = FT_SetDataCharacteristics( ft_handle, 		// Handle of the chip(FT232)
											   FT_BITS_8,       // No of Data bits = 8
											   FT_STOP_BITS_1,  // No of Stop Bits = 1
						                       FT_PARITY_NONE	// Parity = NONE
						                      );
		if(ft_status == FT_OK)
			printf("\tFormat-> 8 DataBits,No Parity,1 Stop Bit (8N1)\n");
		else
			printf("\tError in setting Data Format \n");


		//--------------------------------- Setting Flow Control bits -------------------------------------------//

		ft_status = FT_SetFlowControl( ft_handle,		// Handle of the chip(FT232)
				                       FT_FLOW_NONE,    // No Flow control
				                       NULL,            // XON  = Null since no Flow control
				                       NULL             // XOFF = Null since no Flow control
				                      );

		if(ft_status == FT_OK)
			printf("\tFlow Control = None \n");
		else
			printf("\tError in setting Flow Control \n");


		//-------------------------------  Writing a byte to serial port -----------------------------------------//

		TxByte = 'A';
		ft_status = FT_Write( ft_handle,         // Handle to the chip
							  &TxByte,           // Variable Containing the byte to be Txed
							  sizeof(TxByte),    // sizeof(TxByte) = char
							  &NoOfBytesWritten  // No of Bytes written to the port
							 );

		if(ft_status == FT_OK)             		 // Error checking for FT_Writee()
		    printf("\t'%c' written to the serial port at %d bps\n",TxByte,BaudRate);
		else
			printf("\tError in writing to port\n");

		//--------------------------------------------------------------------------------------------------------//


		FT_Close(ft_handle);                      // Closing the handle to the chip
		
		getch();
	}

	