# Oscilloscope on STM32F746 Discovery kit
  
![oscilloscope](Document/Picture/osc.jpg)

# Official version of TouchGFX

the following project use the ST touch GFX with no Evaluation watermark

# Features

* 2 input channel
* Sampling rate 1 mega-sample/s per channel
* Maximum input voltage 3.3V
* Rising/Falling edge trigger
* Adjust voltage level, time scale
* Marker for signal mesurement

# Requirements

## Hardware

* STM32F746-DISCO Kit [link](https://www.st.com/en/evaluation-tools/32f746gdiscovery.html)

## Software

These tools are used for developing the application

* Microsoft Visual Studio (Graphical interface development)
* Keil (Embedded firmware development)
* STM32 ST-Link Utility (This tool is used for flasing the application)

# Flashing the application

* Start STM32 ST-Link utility, connect the board to PC, press **Connect to the target** button
* Drag and drop the binary file into ST-Link. Binary file is located in folder *Project/Oscilloscope/Binary*
* On the top menu bar, choose *External Loader -> Add External Loader -> Choose N25Q128A_STM32F746G-DISCO -> Click Validate*
* Click **Program verify**, click **Start**

# Project struture

* Project: source code of the project

  * Oscilloscope
    * Firmware: source code of the firmware
    * Graphic: source code of the graphical interface
* touchgfx: TouchGFX stack

# Contact

email: maher.mastouri@gmail.com
