	
	//====================================================================================================//
	//    Program to put the FT232 chip in Asynchronous Bit Bang Mode using D2xx Library from FTDI        //
	//====================================================================================================//
	
	//====================================================================================================//
	// www.xanthium.in										                                              //
	// Copyright (C) 2015 Rahul.S                                                                         //
	//====================================================================================================//
	
	//====================================================================================================//
	// The Program puts the FT232 chip in Asynchronous Bit Bang Mode using D2xx Library and writes 0xAA   //
	// to the 8 bit parallel port.                                                                        //
	//====================================================================================================//
	// Hardware Used:-                                                                                    //
	// USB2SERIAL Converter - FT232 based USB to Serial/RS232/RS485 Converter                             //
	//----------------------------------------------------------------------------------------------------//
	// Pin Configuration                                                                                  //                            
	//	(FT232)  TXD -> D0 --+                                                                            //
	//  (FT232)  RXD -> D1   |                                                                            //
	//  (FT232) ~RTS -> D2   |                                                                            //
 	//  (FT232) ~CTS -> D3   |--- 8 bit Parallel Port                                                     //
	//  (FT232) ~DTR -> D4   |                                                                            //
	//  (FT232) ~DSR -> D5   |                                                                            //
	//  (FT232) ~DCD -> D6   |                                                                            //
	//  (FT232) ~RI  -> D7 --+                                                                            //
	//====================================================================================================//
	// Compiler  :	gcc 4.8.1 (MinGW)                                                                     //
	// Library   :  ftd2xx.lib                                                                            //
	// Commands  :  gcc -o Asynchronous_BBM Asynchronous_BBM.c ftd2xx.lib                                 //
	// OS        :	Windows(Windows 7)                                                                    //
	// Programmer:	Rahul.S                                                                               //
	// Date	     :	15-April-2015                                                                         //
	//====================================================================================================//
	
	//======================================================================================//
	//  IF YOU ARE USING Archive CDM 2.08.30 WHQL Certified.zip FROM FTDI WEBSITE           //
	//======================================================================================//
	// ftd2xx.h   - CDM 2.08.30 WHQL Certified\CDM v2.08.30 WHQL Certified\ftd2xx.h         //
	// ftd2xx.lib - CDM 2.08.30 WHQL Certified\CDM v2.08.30 WHQL Certified\i386\ftd2xx.lib  //
	//======================================================================================//
	
	#include <stdio.h>
	#include <windows.h>  // for windows specific keywords in ftd2xx.h
	#include "ftd2xx.h"   // Header file for ftd2xx.lib 
	int main(void)
		{
		
			void Heading(void);
		
			FT_HANDLE FT_handle;    // handle to FT 232 chip
			FT_STATUS FT_status;    // status of the FT 232 chip

			UCHAR Mask;             // for selecting which pins are input/output
			UCHAR Mode;             // Selects the mode of operation for the chip
			DWORD BaudRate;         // for selecting the Baud Rate
			UCHAR Buffer = 0xAA;    // data to be written to the port
			DWORD BytesWritten = 0; // No of bytes written by FT_Write()
        
			Heading();
			FT_status = FT_Open(0,&FT_handle); // Open  a connection to FT232RL
		
			if(FT_status == FT_OK)             // Error Checking
				printf("\n\n\t  Connection to FT232 opened ");
			else 
				printf("\n\t  ERROR! in Opening connection");
			
			Mode = 0x01;              // Select Chip mode as Asynchronous Bit Bang
			Mask = 0xff;              // Direction Mask,8 bit port all output

			FT_status = FT_SetBitMode(FT_handle,Mask,Mode); //sets Asynchronous BBM
		
			if(FT_status == FT_OK)             // Error Checking
				{
					printf("\n\n\t  Mode = 0x%x, Asynchronous Bit Bang Mode Selected",Mode);
					printf("  \n\t  Mask = 0x%x, Direction = All 8 bits output",Mask);
				}
			else 
				printf("\n\t  ERROR! in setting Asynchronous Bit Bang Mode");
			
			BaudRate = 9600;       // Setting the Baud rate to 9600

			FT_status = FT_SetBaudRate(FT_handle,BaudRate); //Sets FT232 to 9600 baud
        
			if(FT_status == FT_OK)             // Error Checking
				{
					printf("\n\n\t  Baudrate Set at %d bps",BaudRate);
				}
			else 
				printf("\n\t  ERROR! in setting Baudrate");
			
			// Write 0xAA to the 8 bit data port
			FT_status = FT_Write( FT_handle,      // handle to the chip
								  &Buffer,        // address of the data
                                  sizeof(Buffer), // Size of the Buffer
                                  &BytesWritten   // Number of bytes written 
                                );
			if(FT_status == FT_OK)             // Error Checking
				{
					printf("\n\n\t  0x%x Written to 8 bit port @ %d bps",Buffer,BaudRate);
				}
			else 
				printf("\n\t  ERROR! in Writing to Port");					
		
			printf("\n\n\t  Press any key to exit from Asynchronous Bit Bang Mode");		
			getchar();           // Press any key to reset the chip 
		
			Mode = 0x00;         // Mask = 0x00 will reset the chip and-
                             // -get it out of Asynchronous mode
		
			FT_status = FT_SetBitMode(FT_handle,Mask,Mode); // Reset the chip 
		
			if(FT_status == FT_OK)             // Error Checking
				{
					printf("\n\n\t  FT232 exited from Asynchronous Bit Bang Mode");
					printf("\n\n\t  Press any key to exit");
					printf("\n\t+-------------------------------------------------+");
				}
				
			FT_Close(FT_handle); // Close the Serial port connection
			getchar();           // Press any key  to exit
		}

	void Heading(void)
	{
		printf("\n\t+-------------------------------------------------+");
		printf("\n\t|  Asynchronous Bit Bang Mode using D2XX library  |");
		printf("\n\t+-------------------------------------------------+");
	}