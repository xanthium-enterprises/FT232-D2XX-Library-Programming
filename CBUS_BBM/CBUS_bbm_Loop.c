
	//====================================================================================================//
	// Program to output all the 4 bit values from 0x00 - 0x0F through CBUS output port                   //
	//====================================================================================================//
	
	//====================================================================================================//
	// www.xanthium.in										                                              //
	// Copyright (C) 2015 Rahul.S                                                                         //
	//====================================================================================================//
	
	//====================================================================================================//
	// The Program puts the FT232 chip in CBUS Bit Bang Mode using D2xx Library and writes from 0x00 to   //
	// 0x0F in a loop through the 4 bit parallel port.                                                    //
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
	// Commands  :  gcc -o CBUS_bbm_Loop CBUS_bbm_Loop.c ftd2xx.lib                                       //
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
		void delay(void);
		
		FT_HANDLE FT_handle; // handle to FT 232 chip
		FT_STATUS FT_status; // status of the FT 232 chip

		UCHAR Mask;     // for selecting which pins are input/output
		UCHAR Mode;     // Selects the mode of operation for the chip
        
		UCHAR UpperNibble_Direction; //whether port is input/output
		UCHAR LowerNibble_Data;      // 4 bit data to be sent

		UpperNibble_Direction = 0xF0; // setting the direction nibble
		LowerNibble_Data      = 0x00; // setting the data nibble
		
		int i = 0;

		Mask =  UpperNibble_Direction | LowerNibble_Data;//OR'ing

		Heading();
		FT_status = FT_Open(0,&FT_handle); // Open a connection to FT232RL

		if(FT_status == FT_OK)             // Error Checking
			printf("\n\n\t  Connection to FT232 opened\n ");
		else 
			printf("\n\t  ERROR! in Opening connection");
		
		Mode = 0x20;   // Select Chip mode as CBUS Bit Bang
		// loop through all the values from 0x00 - 0x0F
        for (i =0; i<16;i++)
		{
			FT_status = FT_SetBitMode(FT_handle,Mask,Mode);  // Opening  Bit Bang Mode
			
			if(FT_status == FT_OK)             // Error Checking
				{
					printf("  \n\t  LowerNibble_Data = 0x%x,",LowerNibble_Data);
				}
			else 
				printf("\n\t  ERROR! in setting CBUS Bit Bang Mode");
				
			delay(); //delay to display
			
			LowerNibble_Data++;	//increment data
			
			Mask =  UpperNibble_Direction | LowerNibble_Data;//OR'ing
	    }
		
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
			printf("\n\t|          Continous Transmission                 |");
			printf("\n\t+-------------------------------------------------+");
		}
		
	void delay(void)
	{ 
		int i =0;
		int j =0;
		for (i = 0; i<0xfff;i++)
			for (j = 0; j<0xFFFF;j++);
	}