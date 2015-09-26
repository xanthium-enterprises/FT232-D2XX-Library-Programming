	//====================================================================================================//
	// Asynchronous Bit Bang Mode using D2xx Library                                                      //
	//====================================================================================================//
	// www.xanthium.in										                                              //
	// Copyright (C) 2015 Rahul.S                                                                         //
	//====================================================================================================//
	
	//====================================================================================================//
	// Compiler  :	gcc 4.8.1 (MinGW)                                                                     //
	// Library   :  ftd2xx.lib                                                                            //
	// Commands  :  gcc -o Asynchronous_BBM Asynchronous_BBM.c ftd2xx.lib                                 //
	// OS        :	Windows(Windows 7)                                                                    //
	// Programmer:	Rahul.S                                                                               //
	// Date	     :	15-April-2015                                                                         //
	//====================================================================================================//
	

#include <stdio.h>
#include <windows.h>  // for windows specific keywords in ftd2xx.h
#include "ftd2xx.h"   // Header file for ftd2xx.lib 
int main(void)
    {
        FT_HANDLE FT_handle;    // handle to FT 232 chip
        FT_STATUS FT_status;    // status of the FT 232 chip

        UCHAR Mask;             // for selecting which pins are input/output
        UCHAR Mode;             // Selects the mode of operation for the chip
        DWORD BaudRate;         // for selecting the Baud Rate
        UCHAR Buffer = 0xAA;    // data to be written to the port
        DWORD BytesWritten = 0; // No of bytes written by FT_Write()
              
        FT_status = FT_Open(0,&FT_handle); // Open  a connection to FT232RL
        
        Mode = 0x01;              // Select Chip mode as Asynchronous Bit Bang
        Mask = 0xff;              // 8 bit port all output

        FT_status = FT_SetBitMode(FT_handle,Mask,Mode); //sets Asynchronous BBM
        
        BaudRate = 9600;       // Setting the Baud rate to 9600

        FT_status = FT_SetBaudRate(FT_handle,BaudRate); //Sets FT232 to 9600 baud
        
        FT_status = FT_Write( FT_handle,      // handle to the chip
                              &Buffer,        // address of the data
                              sizeof(Buffer), // Size of the Buffer
                              &BytesWritten   // Number of bytes written 
                            );

         getchar();           // Press any key to reset the chip 
        
         Mode = 0x00;         // Mask = 0x00 will reset the chip and-
                              // -get it out of Asynchronous mode
         FT_status = FT_SetBitMode(FT_handle,Mask,Mode); // Reset the chip 
        
         FT_Close(FT_handle); // Close the Serial port connection
     }