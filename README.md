# LT-Z17 Line Follower
(https://oshwdem.org/)

<img src="https://raw.githubusercontent.com/jbabio/LT-Z17-Line-Follower/master/LT-Z17.jpg" width="400">

Line follower bot for the Line following contest at OSHWDem 2017

## Hardware Used:
  * Robot base: Custom 3D printed base. (will be released)
  * Main Electronics: Custom made board with Atmega 1284P(Mightycore bootloader)
  * Motors: 2x Pololu 10:1 HPCB 6V DUAL-SHAFT
  * Motor Driver: TB6612FNG
  * Sensors:
    * Pololu Qtr8rc
  * Comunications: HM-10 Bluetooth module.
    
## Acknowledgements

* Pololu for  the QTRSensors library and great documentation.
* SparkFun for  the SparkFun_TB6612 library and great documentation.
* Arduino comunity for the platform, documentation and support.
  * https://www.arduino.cc/en/Reference/EEPROM  
  * http://www.arduino.cc/en/Tutorial/BlinkWithoutDelay  
  * http://www.arduino.cc/en/Tutorial/Debounce
  * https://www.arduino.cc/en/Tutorial/SwitchCase2
* Hans (MCUdude) for the Mighty Core bootloader. (https://github.com/MCUdude)
* ThorLabs for the explanation of PID (https://www.thorlabs.com/tutorials.cfm?tabID=5dfca308-d07e-46c9-baa0-4defc5c40c3e)
* makespacemadrid.org fot the documentation about the HM-10 Module. (http://wiki.makespacemadrid.org/index.php?title=M%C3%B3dulo_HM-10)
* Anyone who create or share Open Source Hardware or Software.

## Dependencies.
Pololu QTRSensors library for Arduino, If you are using version 1.6.2 or later of the Arduino software, you can use the Library Manager to install this library. MIT License.
  * https://github.com/pololu/qtr-sensors-arduino
  * https://www.pololu.com/docs/0J19/all
  
SparkFun SparkFun Motor Driver - Dual TB6612FNG (1A) Arduino Library, If you are using version 1.6.2 or later of the Arduino software, you can use the Library Manager to install this library. MIT License.
  * https://github.com/sparkfun/SparkFun_TB6612FNG_Arduino_Library

Default Arduino EEPROM V 2.0 Library. LGPL License.
  * https://www.arduino.cc/en/Reference/EEPROM

## Current status

Fully functional.

## Known issues

None at the moment.

## Todo

* Read IR Sensors -> DONE
* Control motors -> DONE
* PID algorithm -> DONE
* EEPROM: format and save defaults-> DONE
* EEPROM: update parameters-> DONE
* EEPROM: retrieve parameters-> DONE
* Human interface: LEDs-> DONE
* Human interface: Button-> DONE
* Human interface: serial-> DONE
