# OnStepX Encoder Bridge

# Important Note

This is an Serial interface Encoder Bridge for OnStepX.

# Installing the board Platform for your hardware
Before you can flash the firmware on your ESP8266 or ESP32 device, you need to install the ESP8266 OR ESP32
platform for the Arduino IDE.  If using an Arduino M0 or Teensy you don't need to perform this step.  For the
Teensy's you instead need to install the Teensyduino.exe package to add support to the Arduino IDE.

Under the menu File->Preferences open the dialog and add this line in the additional "Boards Manager" area:
  http://arduino.esp8266.com/stable/package_esp8266com_index.json,https://dl.espressif.com/dl/package_esp32_index.json


Then, from the "Tools, Boards, Boards Manager" menu select and install the ESP8266, ESP32, etc. as required.  

# Flashing The Encoder Bridge
The exact flashing procedure depends on which device you will be using.

In the Arduino IDE, pick your device from "Tools, Boards" menu.

Most devices have a USB port you plug into then a virtual serial port appears, direct the Arduino IDE to use that serial port and upload.  Be sure the device is not electrically connected to anything but the USB cable when it is plugged in.

# Using the EncoderBridge (EB)
Setup of the EB is very similar to the SmartWebServer but only where it relates to encoder functionality and serial interfaces.  Encoders in OnStepX, the SWS, and the EncoderBridge all use the same underlying libraries and have similar settings.  When the EB is running it does nothing but keep track of the Axis1 and optionally Axis2 encoders and pass their counts to OnStepX when asked.  You can see this work manually in the Arduino Serial Monitor by selecting a baud rate it supports and using the USB/Serial interface.  Sending a "1" to the EB will result in a reply with the Axis1 count (if enabled.)  Sending "2" will similarly result in a reply for Axis2 (if enabled.)  There's also an "E" or "W" suffix sometimes returned to pass error and warning states along to reflect any background errors that might have occured, like a BiSS-C CRC failure or an AB encoder sequence that's invalid (some state changes should never happen and the code guesses at the correct action ("W") or outright fails ("E" no count action.)

In OnStepX you then use #define AXISn_ENCODER SERIAL_BRIDGE and add lines with #define ENCODER_SERIAL Serial2 (for example) with the hardware serial UART interface to use and #define ENCODER_SERIAL_BAUD 460800 (matching the EB) with the buad rate.  Some platforms also accept #define's ENCODER_SERIAL_RX and ENCODER_SERIAL_TX to set the pins.  These settings will often be mostly the same as those used for the SERIAL_B command channel *which should be disabled* if using this, as the SWS usually isn't present and you don't want both running on the same serial interface!

Once this is all setup the OnStepX EncoderBridge acts like any other encoder type.

