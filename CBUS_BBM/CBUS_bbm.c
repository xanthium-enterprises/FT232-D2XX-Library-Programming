//======================================================================================================//
// Program to put the FT232 chip in CBUS Bit Bang Mode using D2xx Library from FTDI (No ERROR Checking) //
//======================================================================================================//

//======================================================================================================//
// www.xanthium.in							  			                                                //
// Copyright (C) 2015 Rahul.S                                                                           //
//======================================================================================================//

#include <stdio.h>
#include <windows.h> // for windows specific keywords in ftd2xx.h
#include "ftd2xx.h"  // Header file for ftd2xx.lib 
int main(void)
{         
    FT_HANDLE FT_handle; // handle to FT 232 chip
    FT_STATUS FT_status; // status of the FT 232 chip

    UCHAR Mask;     // for selecting which pins are input/output
    UCHAR Mode;     // Selects the mode of operation for the chip
        
    UCHAR UpperNibble_Direction; //whether port is input/output
    UCHAR LowerNibble_Data;      // 4 bit data to be sent

    UpperNibble_Direction = 0xF0; // setting the direction nibble
    LowerNibble_Data      = 0x0F; // setting the data nibble

    Mask =  UpperNibble_Direction | LowerNibble_Data;//OR'ing

    FT_status = FT_Open(0,&FT_handle); // Open a connection to FT232RL

    Mode = 0x20;   // Select Chip mode as CBUS Bit Bang
        
    FT_status = FT_SetBitMode(FT_handle,Mask,Mode);  // Opening  Bit Bang Mode
	getchar();
	
	Mode = 0x00; // Reset the chip
	Mask = 0x00; // 
	FT_status = FT_SetBitMode(FT_handle,Mask,Mode); //Bring back the chip to default mode 
	
    FT_Close(FT_handle);//Close the connection
}