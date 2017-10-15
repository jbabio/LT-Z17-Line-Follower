void ClearEEPROM (){
  if (clrEEPROM == HIGH){           // Clears the EEPROM if commanded.
    for ( int i = 0 ; i < EEPROM.length() ; i++ ){
      EEPROM.write(i, 0);
      BlinkLED(22, 50);
    }
    ToggleLED (LOW, LOW);           // turn the LEDs off when we're done
  }
}

void ResetPIDGains(){
  if (fillEEPROM == HIGH){          // Fills EEPROM with default PID values if commanded.
    int default_maxSpeed = 200;
    float default_Kp = 0.01;
    float default_Kd = 3.00;
    float default_Ki = 0.01;
    EEPROM.put(0, default_maxSpeed);
    EEPROM.put(4, default_Kp);
    EEPROM.put(8, default_Kd);
    EEPROM.put(12, default_Ki);
  }
}

void SavePIDGainsToEEPROM (){
  EEPROM.put(0, maxSpeed);                            // maxSpeed as an int, only needs 2 bytes but I've reserved 4 just in case I change type.
  EEPROM.put(4, Kp);                                  // 4 bytes reserved cause it's a float
  EEPROM.put(8, Kd);                                  // 4 bytes reserved cause it's a float
  EEPROM.put(12, Ki);                                 // 4 bytes reserved cause it's a float
}

void ReadPIDGainsFromEEPROM (){
  EEPROM.get(0, maxSpeed);                            //maxSpeed as an int, only needs 2 bytes but I've reserved 4 just in case I change type.
  EEPROM.get(4, Kp);                                  // 4 bytes reserved cause it's a float
  EEPROM.get(8, Kd);                                  // 4 bytes reserved cause it's a float
  EEPROM.get(12, Ki);                                 // 4 bytes reserved cause it's a float
}

 void SaveQTRCalibrationToEEPROM(){
  int a = 16;                                         //Starting memory address, From 0 to 15 are used by PID gains.
  for (int i = 0; i < NUM_SENSORS; i++)
  {
    EEPROM.put(a, qtrrc.calibratedMinimumOn[i]);      // Store calibratedMinimumOn[i] to eeprom
    a = a + 2;                                        // Add 2 to memory address (each int takes 2 Bytes of EEPROM)
  }
  for (int i = 0; i < NUM_SENSORS; i++)
  {
    EEPROM.put(a, qtrrc.calibratedMaximumOn[i]);      // Store calibratedMaximumOn[i] to eeprom
    a = a + 2;                                        // "a" Keeps increasing with each value stored (each int takes 2 Bytes of EEPROM)
  }
}

void ReadQTRCalibrationFromEEPROM (){
  int a = 16;                                         //Start memory address, From 0 to 15 are used by PID gains.
  qtrrc.calibrate();
  for (int i = 0; i < NUM_SENSORS; i++)
  {
    EEPROM.get(a, qtrrc.calibratedMinimumOn[i]);      // Read calibratedMaximumOn[i] from eeprom
    a = a + 2;                                        // Add 2 to memory address (each int takes 2 Bytes of EEPROM)
  }
  for (int i = 0; i < NUM_SENSORS; i++)
  {
    EEPROM.get(a, qtrrc.calibratedMaximumOn[i]);      // Read calibratedMaximumOn[i] from eeprom
    a = a + 2;                                        // "a" Keeps increasing with each value readed (each int takes 2 Bytes of EEPROM)
  }
  ShowCalibration(HIGH);
}
