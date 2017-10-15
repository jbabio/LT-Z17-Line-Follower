//****************  Line Follower robot LTBR-Z17 by J. Alberto Babío Pérez  ****************//
//                            PID based control algorithm                                   //
//   Pololu 10:1 micro motor, Pololu Qtr8rc, TB6612FNG, Atmega 1284P(Mightycore)            //
//   REFERENCES:                                                                            //
//   https://www.pololu.com/docs/0J19/all                                                   //
//   https://www.arduino.cc/en/Reference/EEPROM                                             //
//   https://forum.pololu.com/t/qtr-calibration-values-from-eeprom/6823                     //
//   http://www.arduino.cc/en/Tutorial/BlinkWithoutDelay                                    //
//   http://www.arduino.cc/en/Tutorial/Debounce                                             //
//   https://www.thorlabs.com/tutorials.cfm?tabID=5dfca308-d07e-46c9-baa0-4defc5c40c3e      //
//   https://www.arduino.cc/en/Tutorial/SwitchCase2                                         //
//   http://wiki.makespacemadrid.org/index.php?title=M%C3%B3dulo_HM-10
//******************************************************************************************//

#include <QTRSensors.h>
#include <SparkFun_TB6612.h>
#include <EEPROM.h>
#include "HAL.h"

// Track Settings
  int line_type = 0;                                // 0 for black line, 1 for white line

// Setup Flags
  bool clrEEPROM = LOW;                             // HIGH to clear EEPROM memory, Normally LOW
  bool fillEEPROM = LOW;                            // HIGH to fill the EEPROM with default values, Normally LOW
  bool bootMode = LOW;
  //bool verboseReadingOut = LOW;                   // Flag to output verbose QTR8 readings

// Qtr8 global Variables
  unsigned int sensorValues[NUM_SENSORS];
  unsigned int position;

// PID gain and speed valuesalues are extracted from EEPROM in setup()
  int maxSpeed;                                     // Speed setting, (MAX 255)
  float Kp;                                         // Proportional Gain
  float Kd;                                         // Derivative Gain
  float Ki;                                         // Integral Gain

  unsigned long GoneOutOfTrackMillis;               // Variable to store millis() value when the bot goes out of track.
void setup()
{
  Serial.begin(9600);
  delay(100);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(button_1, INPUT_PULLUP);
  ClearEEPROM ();                                   // Checks clrEEPROM flag & clears EEPROM if needed.
  ResetPIDGains();                                  // Checks fillEEPROM flag & fills EEPROM with default values if needed.
  ReadPIDGainsFromEEPROM ();                        // Recovers PID gains from EEPROM at start.
  ToggleLED (HIGH, HIGH);                           // Turn on both leds indicating calibration can be performed pressing the buton.
  BootMode ();                                      // Normal boot restoring parameters from EEPROM or calibration mode.
  SerialPrintPIDParameters(LOW);                    // Shows current PID parameters (LOW parameter)
  WaitForStart();                                   // Wait for the button to be pressed to start line tracking.
}       

void loop(){
  BlinkLED(22, 200);                                // LEDs swing at 200ms. bot is tracing the line.
  PauseCheck();                                     // Check button presses
  pid(maxSpeed, Kp, Ki, Kd);                        // PID function call
  GoneOutOfTrackMillis = millis();                  // millis() value when the bot gone out for timeout calculation.
  OutOfTrack();                                     // Out of track function call
}
 
 

