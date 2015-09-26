## Programming FT232 chip using D2XX library 
<img src = "http://www.xanthium.in/sites/default/files/site-images/ft232-develop-d2xx-library/ft232-development-d2xx-library-620px.jpg" />

A short introduction on using D2XX library to program the advanced function of FT232 (USB to Serial Converter) chip from FTDI.

Using D2XX library you can turn the humble FT232 usb to serial converter to a

- **USB to Parallal Converter chip With 8 bit** wide parallal Port (Asynchronous Bit Bang Mode)
- **USB to Parallal Converter chip With 4 bit** wide parallal Port (CBUS Bit Bang Mode)
 

The <a href = "http://www.xanthium.in/ftdi-ft232-chip-development-using-d2xx-library">**Full Tutorial which explains how to configure the library and use it to program the chip can be found here**</a>. 

Here is an interesting application in which a <a href ="http://xanthium.in/interfacing-7-segment-led-display-with-ft232-and-d2xx-library">7 Segment display is controlled without using a microcontroller</a>. 

- **Asynch_BBM** directory contains code for **Asynchronous Bit Bang Mode** of FT232
- **CBUS_BBM** directory contains code for **CBUS Bit Bang Mode** of FT232
- **RTS_DTR_Control** directory contains code for controlling **RTS and DTR pins of FT232**

The D2XX library **ftd2xx.lib** and the Header File **ftd2xx.h** should be in the same folder when you are compiling the code.

The code can be compiled using GCC compiler.

Here is a Screenshot of the CBUS mode in Action 

<img src = "http://www.xanthium.in/sites/default/files/site-images/ft232-cbus-bit-bang-mode/compiling-ft232-cbus-bit-bang-code-d2xx.jpg" />

