WebUSB - Arduino - Cognimates
================

This repository contains an Arduino library for WebUSB-enabling your sketches, forked from the <a href="https://github.com/webusb/arduino"> webusb/arduino</a> repository, along with a sketch compatible with the <a href="https://codelab.cognimates.me">Cognimates codelab</a> Arduino Extension. 

The WebUSB object is a copy of the Arduino SDK's built-in USB serial library.
It creates a WebUSB-compatible vendor-specific interface rather than one marked
as USB CDC-ACM. This prevents operating system drivers from claiming the device
and making it inaccessible to the browser. This library also implements:

 * The WebUSB landing page descriptor, providing a hint to the browser about
   what page the user should navigate to to interact with the device. In
   Google Chrome the presence of this descriptor causes the browser to display
   a notification when the device is connected. The user can click on this
   notification to navigate directly to the provided URL.
 * Microsoft OS 2.0 Descriptors which instruct the Windows operating system
   (8.1 and above) to automatically the `WinUSB.sys` driver so that the browser
   can connect to the device.

Compatible Hardware
-------------------

WebUSB requires an Arduino model that gives the sketch complete control over the USB hardware. This library has been tested with the following models:

 * Arduino Leonardo
 * Arduino/Genuino Micro
 * Arduino/Genuino Zero
 * Arduino MKR1000
 * Arduino MKRZero
 * Arduino MKRFox1200
 * Adafruit Feather 32u4

Getting Started
---------------

1. Install at least version 1.6.11 of the [Arduino IDE](https://www.arduino.cc/en/Main/Software).

2. The WebUSB library provides all the extra low-level USB code necessary for WebUSB support except for one thing: Your device must be upgraded from USB 2.0 to USB 2.1. To do this go into the SDK installation directory and open `hardware/arduino/avr/cores/arduino/USBCore.h`. Then find the line `#define USB_VERSION 0x200` and change `0x200` to `0x210`. That's it!

  **macOS:** Right click on the Ardunio application icon and then click on show package contents menu item. Navigate to `Contents/Java/hardware/arduino/avr/cores/arduino/USBCore.h`
  
  **Warning:** Windows requires USB 2.1 devices to present a Binary Object Store (BOS) descriptor when they are enumerated. The code to support this is added by including the "WebUSB" library in your sketch. If you do not include this library after making this change to the SDK then Windows will no longer be able to recognize your device and you will not be able to upload new sketches to it.

3. Copy (or symlink) the `library/WebUSB` directory from this repository into the `libraries` folder in your sketchbooks directory. Here is a <a href="https://drive.google.com/drive/folders/1TsQmEgvsSLchIRxgtch64fpfYczd_pWB?usp=sharing" target="_blank"> link to the library </a> to make it easier. The images below show the steps you take to do this after clicking on the link to the library: 

  * Download the folder. It will download in the form of a zip file. <br><img src="./instruction_images/download-webusb.png" height=300px style="text-align:center;">

  * Find the zip folder in your computer's files and open the zip file. In this example, the zip folder downloaded into the Mac's "Downloads" folder. Copy the entire "WebUSB" folder. <br><img src="./instruction_images/open-zip.png" height=300px style="text-align:center;">

  * Find your "sketchbooks directory", which is the folder that holds all of your sketches. Your Arduino IDE automatically saves sketches to this folder, and it also holds libraries. It is by default named "Arduino". Open it and find the folder named "libraries". <br> <img src="./instruction_images/libraries-folder.png" height=300px style="text-align:center;">

  * Now, open libraries and paste in the WebUSB folder you copied. You should now see WebUSB inside your libraries folder. <br> <img src="./instruction_images/web-usb.png" height=300px style="text-align:center;">

4. Launch the Arduino IDE. You should see "WebUSB" as an option under "Sketch > Include Library".

5. Download `sketch/cognimates.ino` <a href="https://drive.google.com/uc?export=download&id=1mmxHcXB8tpqtn-FFhOdGpaA19qgJTsuI">here</a>, open it in the Arduino IDE, and program it to your device.

6. Go to https://codelab.cognimates.me, open the Arduino extension, and start playing! 

 **Frequent Issues** 
 1. Make sure you are using Google Chrome - other browsers do not have full support or any support for WebUSB yet. 
 2. Double check that you are using one of the compatible models - the Arduino UNO does not have the hardware necessary to communicate through WebUSB, unfortunately. 
 3. Double check that you have made the correct alterations to your SDK installation and that you've uploaded the sketch correctly. 
 4. After making changes to the SDK, you need to completely close/quit Arduino and open it again. 
