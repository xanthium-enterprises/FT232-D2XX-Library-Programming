    //====================================================================================================//
	//       Program to control DTR and RTS pins of FT232 using D2xx Library from FTDI                    //
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
	// Commands  :  gcc -o DTR_RTS_D2XX DTR_RTS_D2XX.c ftd2xx.lib                                         //
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
		
		void Heading(void);
		void Heading_DTR(void);
		void Heading_RTS(void);
		
        Heading();       
        ft_status = FT_Open(0,&ft_handle); //open a connection to the device

		if(ft_status == FT_OK)
            {
				printf("\n\t Connection with FT 232 successfull\n");
				
				FT_SetDtr(ft_handle); //~DTR = 0
				FT_SetRts(ft_handle); //~RTS = 0 
				
				//-------------- Controlling the DTR Pin ----------------------//
				Heading_DTR();
				ft_status = FT_ClrDtr(ft_handle);//function to clear the DTR pin
             
				if(ft_status == FT_OK)
					printf("\n\t DTR Cleared ,~DTR Should be high\n\n");
                printf("\n\t Press any Key");
				getchar();

				ft_status = FT_SetDtr(ft_handle);//function to set the DTR pin
             
				if(ft_status == FT_OK)
					printf("\n\n\t DTR set ,~DTR Should be low\n\n");
					
			    printf("\n\t Press any Key");
				getchar();
				
				//-------------- Controlling the RTS Pin ----------------------//
				Heading_RTS();
				
				ft_status = FT_ClrRts(ft_handle);//function to clear RTS  pin
             
				if(ft_status == FT_OK)
					printf("\n\t RTS Cleared ,~RTS Should be high\n\n");
					
                printf("\n\t Press any Key");
				getchar();

				ft_status = FT_SetRts(ft_handle);//function to set the RTS pin
             
				if(ft_status == FT_OK)
					printf("\n\n\t RTS set ,~RTS Should be low\n\n");
					
			    printf("\n\t Press any Key");
				getchar();
				
				printf("\n\t+----------------------------------------------------------+");
            }
        else 
          {
             printf("\nConnection Failed !");
             printf("\nCheck device connection");
          }

        FT_Close(ft_handle); //Close the connection at the end 
    }

	void Heading(void)
	{
		printf("\n\t+----------------------------------------------------------+");
		printf("\n\t| Controlling DTR and RTS pins of FT232 using D2XX library |");
		printf("\n\t+----------------------------------------------------------+");
	}
	
	void Heading_DTR(void)
	{
		printf("\n\t+-------------------+");
		printf("\n\t|  DTR Pin Control  |");
		printf("\n\t+-------------------+");
	}
	
	void Heading_RTS(void)
	{
		printf("\n\t+-------------------+");
		printf("\n\t|  RTS Pin Control  |");
		printf("\n\t+-------------------+");
	}