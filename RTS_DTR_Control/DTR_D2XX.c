    //====================================================================================================//
	//   Program to control DTR and RTS pins of FT232 using D2xx Library from FTDI (Simple)               //
	//====================================================================================================//
	
	//====================================================================================================//
	// www.xanthium.in										                                              //
	// Copyright (C) 2015 Rahul.S                                                                         //
	//====================================================================================================//
	
	//====================================================================================================//
	// Hardware Used:-                                                                                    //
	// USB2SERIAL Converter - FT232 based USB to Serial/RS232/RS485 Converter                             //
	//----------------------------------------------------------------------------------------------------//
	//====================================================================================================//
	// Compiler  :	gcc 4.8.1 (MinGW)                                                                     //
	// Library   :  ftd2xx.lib                                                                            //
	// Commands  :  gcc -o DTR_D2XX DTR_D2XX.c ftd2xx.lib                                                 //
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
    void main()
    {
        FT_HANDLE ft_handle; // handle to the USB ic ,
        FT_STATUS ft_status; // for status report(error,io status etc),
                //open a connection to the device
        ft_status = FT_Open(0,&ft_handle); 


        if(ft_status == FT_OK)
          {
             printf("\nConnection with FT 232 successfull\n");


             //function to clear the DTR pin
             ft_status = FT_ClrDtr(ft_handle);
             
             if(ft_status == FT_OK)
                printf("\n DTR Cleared ,Should be high\n\n");
                
             system("PAUSE");


             //function to set the DTR pin
             ft_status = FT_SetDtr(ft_handle);
             
             if(ft_status == FT_OK)
                printf("\n\n DTR set ,Should be low\n\n");
          }
        else 
          {
             printf("\nConnection Failed !");
             printf("\nCheck device connection");
          }

        FT_Close(ft_handle); //Close the connection at the end 
    }