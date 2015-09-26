
	//====================================================================================================//
	//       Program to put the FT232 chip in CBUS Bit Bang Mode using D2xx Library from FTDI             //
	//====================================================================================================//
	
	//====================================================================================================//
	// www.xanthium.in										                                              //
	// Copyright (C) 2015 Rahul.S                                                                         //
	//====================================================================================================//
	
	//====================================================================================================//
	// The Program puts the FT232 chip in CBUS Bit Bang Mode using D2xx Library and writes 0xFF to the    //
	//  4 bit parallel port.                                                                              //
	//====================================================================================================//
	
	//====================================================================================================//
	// Hardware Used:-                                                                                    //
	// USB2SERIAL Converter - FT232 based USB to Serial/RS232/RS485 Converter                             //
	//----------------------------------------------------------------------------------------------------//
	// Pin Configuration                                                                                  //           
	// 		CBUS0 --> D0 ---+                                                                             //
	// 		CBUS1 --> D1    |____ 4 bit Parallel Port                                                     //
	// 		CBUS2 --> D2    |                                                                             //
	//		CBUS3 --> D3 ---+                                                                             //
	//====================================================================================================//
	// Compiler  :	gcc 4.8.1 (MinGW)                                                                     //
	// Library   :  ftd2xx.lib                                                                            //
	// Commands  :  gcc -o CBUS_bbm_Verbose CBUS_bbm_Verbose.c ftd2xx.lib                                 //
	// OS        :	Windows(Windows 7)                                                                    //
	// Programmer:	Rahul.S                                                                               //
	// Date	     :	16-April-2015                                                                         //
	//====================================================================================================//
	
	//======================================================================================//
	//  IF YOU ARE USING Archive CDM 2.08.30 WHQL Certified.zip FROM FTDI WEBSITE           //
	//======================================================================================//
	// ftd2xx.h   - CDM 2.08.30 WHQL Certified\CDM v2.08.30 WHQL Certified\ftd2xx.h         //
	// ftd2xx.lib - CDM 2.08.30 WHQL Certified\CDM v2.08.30 WHQL Certified\i386\ftd2xx.lib  //
	//======================================================================================//
	
	#include <stdio.h>
	#include <windows.h> // for windows specific keywords in ftd2xx.h
	#include "ftd2xx.h"  // Header file for ftd2xx.lib 
	int main(void)
	{    
		void Heading(void);
	
		FT_HANDLE FT_handle; // handle to FT 232 chip
		FT_STATUS FT_status; // status of the FT 232 chip

		UCHAR Mask;     // for selecting which pins are input/output
		UCHAR Mode;     // Selects the mode of operation for the chip
        
		UCHAR UpperNibble_Direction; //whether port is input/output
		UCHAR LowerNibble_Data;      // 4 bit data to be sent

		UpperNibble_Direction = 0xF0; // setting the direction nibble
		LowerNibble_Data      = 0x0F; // setting the data nibble

		Mask =  UpperNibble_Direction | LowerNibble_Data;//OR'ing

		Heading();
		FT_status = FT_Open(0,&FT_handle); // Open a connection to FT232RL

		if(FT_status == FT_OK)             // Error Checking
			printf("\n\n\t  Connection to FT232 opened ");
		else 
			printf("\n\t  ERROR! in Opening connection");
		
		Mode = 0x20;   // Select Chip mode as CBUS Bit Bang
        
		FT_status = FT_SetBitMode(FT_handle,Mask,Mode);  // Opening  Bit Bang Mode
	
		if(FT_status == FT_OK)             // Error Checking
			{
				printf("\n\n\t  Mode = 0x%x, CBUS Bit Bang Mode Selected",Mode);
				printf("  \n\t  Mask = 0x%x, Direction = All 4 bits output",Mask);
			}
		else 
			printf("\n\t  ERROR! in setting CBUS Bit Bang Mode");
	
		printf("\n\n\t  Press any key to exit from CBUS Bit Bang Mode\n");
		getchar();
	
		Mode = 0x00; // Reset the chip
		Mask = 0x00; // 
		FT_status = FT_SetBitMode(FT_handle,Mask,Mode); //Bring back the chip to default mode 
	
		FT_Close(FT_handle);//Close the connection
		printf("\n\t+-------------------------------------------------+");
	}

	void Heading(void)
		{
			printf("\n\t+-------------------------------------------------+");
			printf("\n\t|     CBUS Bit Bang Mode using D2XX library       |");
			printf("\n\t+-------------------------------------------------+");
		}