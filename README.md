## Programming FT232 chip using D2XX library 

------------------------------------------------------------------------------------------------------------------------------------------

![](http://www.xanthium.in/sites/default/files/site-images/ft232-develop-d2xx-library/ft232-development-d2xx-library-620px.jpg)

A short introduction on using D2XX library to program the advanced functions of FT232 (USB to Serial Converter) chip from FTDI.

Using D2XX library, you can turn the humble FT232 usb to serial converter to a

- **USB to Parallal Converter chip With 8 bit** wide parallal Port (Asynchronous Bit Bang Mode)
- **USB to Parallal Converter chip With 4 bit** wide parallal Port (CBUS Bit Bang Mode)
 

## D2XX drivers

- Project requires D2XX drivers from FTDI.(ftd2xx.lib and ftd2xx.h) 
- Download the **D2XX drivers**  from the [FTDI Website](https://www.ftdichip.com/Drivers/D2XX.htm)

 

## Compilation link Issues

 - Compiling the code (GCC/Visual Studio) on Windows 10 is causing Link Issues
 - Refer this [Stack Exchange to Solve the Issue](https://stackoverflow.com/questions/35919382/using-d2xx-of-ftdi-with-c)
 

## Online Tutorial

[D2XX Library Programming Tutorials using FTDI lib](http://www.xanthium.in/ftdi-ft232-chip-development-using-d2xx-library)


 - The D2XX library **ftd2xx.lib** and the Header File **ftd2xx.h** should be in the same folder when you are compiling the code.
 - The code can be compiled using GCC compiler.
 

## FTDI LED 7 Segment Control

Here is an interesting application in which a 

[Segment display is controlled without using a microcontroller](http://xanthium.in/interfacing-7-segment-led-display-with-ft232-and-d2xx-library). 


## Repo Details

- **Asynch_BBM** directory contains code for **Asynchronous Bit Bang Mode** of FT232
- **CBUS_BBM** directory contains code for **CBUS Bit Bang Mode** of FT232
- **RTS_DTR_Control** directory contains code for controlling **RTS and DTR pins of FT232**
- **Comm_Serial** directory contains code for communicating serially using D2XX Library
- **Comm_RS485** directory contains code for communicating using RS485 Protocol using D2XX Library
 


For RS485 Communication you will require a <a href = "http://xanthium.in/USB-to-Serial-RS232-RS485-Converter">USB to RS485 Converter like this one </a>




Here is a Screenshot of the CBUS mode in Action 

<img src = "http://www.xanthium.in/sites/default/files/site-images/ft232-cbus-bit-bang-mode/compiling-ft232-cbus-bit-bang-code-d2xx.jpg" />

