void BootMode (){                                 // Normal boot restoring parameters from EEPROM or calibration mode.
  for (int i=0 ; i<1000 ; i++){
  delay(4);                                       // delay 4ms * 1000 iterations = 4 segs waiting for calling calibration.
    if(CheckButton(button_1) == HIGH){            // if button pressed
      SensorCalibration();                        // Performs the calibration of Qtr8RC Sensor and shows it.
      i = 999;                                    // Sets i to 999 to exit the loop without waiting.
    } else {
      if (i == 999){                              // If we reach the last iteration without calling the calibration.
        ReadQTRCalibrationFromEEPROM ();          // Restore the calibration of Qtr8RC Sensor from EEPROM.
      }
    }
  }
}

void WaitForStart(){                              // Wait for the button to be pressed to exit setup() and start loop()
  ToggleLED (LOW, HIGH);                          // LED1 off: calibration ended/parameters restored | LED2 on: Robot ready to start.
  while(true){                                    // Infinite loop
    ReadSerialCommands ();                        // Check for commands through serial interface.
    if(CheckButton(button_1) == HIGH){            // Check if the button was pressed  
      ToggleLED (LOW, LOW);                       // Reset LEDs.
      break;                                      // Break the infinite loop & go to main loop()
    }
  }
}

void PauseCheck(){                                // Check if the pause button is pressed during loop()
  if(CheckButton(button_1) == HIGH){              // Check if we should be paused (pause button presed)
    Pause();                                      // Pause the bot and wait for user input.
  }
}


void Pause(){                                     // Pause the bot and wait for user input.
  brake(motor1, motor2);                          // Stop motors. If not stopped here, they'll continue running at last speed set.
  SerialPrintPIDParameters(LOW);                  // Print current PID Parameters.
  while (CheckButton(button_1) == LOW) {          // Wait for the resume button to be pressed.
    BlinkLED(11, 200);                            // Blink both LEDs simultaniously at 200ms to indicate it's in pause mode.
    ReadSerialCommands ();                        // Check for commands through serial interface.
  }
}
