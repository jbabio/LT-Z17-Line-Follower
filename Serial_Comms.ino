void UpdatePIDParameters (){
  bool updated = LOW;                             // Flag to show updated parameters only if something changed.
  while (Serial.available() > 0) {
    switch (Serial.read()){
      case '#':                                   // # -> Update all PID parameters. Syntax: #[int],[float],[float],[float]\n
        maxSpeed = Serial.parseInt();             // Read new maxSpeed from serial.
        Kp = Serial.parseFloat();                 // Read new Kp from serial.
        Kd = Serial.parseFloat();                 // Read new Kd from serial.
        Ki = Serial.parseFloat();                 // Read new Ki from serial.
        updated = HIGH;                           // Something changed.
        break;
      case 'S':                                   // S -> Update maxSpeed parameter. Syntax: S[int]\n
        maxSpeed = Serial.parseInt();             // Read new maxSpeed from serial.
        updated = HIGH;                           // Something changed.
        break;
      case 'P':                                   // P -> Update Kp gain. Syntax: P[float]\n
        Kp = Serial.parseFloat();                 // Read new Kp from serial.
        updated = HIGH;                           // Something changed.
        break;
      case 'I':                                   // I -> Update Ki gain. Syntax: I[float]\n
        Ki = Serial.parseFloat();                 // Read new Ki from serial.
        updated = HIGH;                           // Something changed.
        break;
      case 'D':                                   // D -> Update Kd gain.  Syntax: D[float]\n
        Kd = Serial.parseFloat();                 // Read new Kd from serial.
        updated = HIGH;                           // Something changed.
        break;
      default:                                    // Default: Do nothing
        break;
    }
    if (updated == HIGH){
      SavePIDGainsToEEPROM ();                    // Save new gains & maxSpeed to EEPROM
      SerialPrintPIDParameters(HIGH);
      if (Serial.read() == '\n') {                // look for the newline. That's the end of your sentence
        return;
      }
    }
  }
}

void SerialPrintPIDParameters (bool updatedPIDs){     // Show PID parameters. bool updatedPIDs: HIGH->UPDATED or LOW->CURRENT 
  if (updatedPIDs == HIGH){
    Serial.println("UPDATED PID PARAMETERS");
  }else {
    Serial.println("CURRENT PID PARAMETERS");
  }
  Serial.print("maxSpeed: ");
  Serial.println(maxSpeed);
  Serial.print("Kp: ");
  Serial.println(Kp);
  Serial.print("Kd: ");
  Serial.println(Kd);
  Serial.print("Ki: ");
  Serial.println(Ki);
  Serial.println();
}

 void ShowCalibration(bool origin){                   // Show Qtr calibration values. bool origin: HIGH->EEPROM or LOW->new calibration 
  int a = 16;                                         // Starting memory address, From 0 to 15 are used by PID parameters.
  if (origin == HIGH){
    Serial.println("QTR8 CALIBRATION RESTORED FROM EEPROM:");
  }else {
    Serial.println("NEW QTR8 CALIBRATION:");
  }
  for (int i = 0; i < NUM_SENSORS; i++)
  {
    Serial.print(qtrrc.calibratedMinimumOn[i]);
    Serial.print("\t");                               // prints a tab
  }
  Serial.println();
  
  // print the calibration maximum values measured when emitters were on
  for (int i = 0; i < NUM_SENSORS; i++){
    Serial.print(qtrrc.calibratedMaximumOn[i]);
    Serial.print("\t");                               // prints a tab
  }
  Serial.println();
  //Serial.println();
  //delay(1000);
}

void printReadings(unsigned int sensorValues[NUM_SENSORS], unsigned int position){
  //Serial.println("printReadings");
  // print the sensor values as numbers from 0 to 1000, where 0 means maximum reflectance and
  // 1000 means minimum reflectance, followed by the line position
  /*for (unsigned char i = 0; i < NUM_SENSORS; i++)
  {
    Serial.print(sensorValues[i]);
    Serial.print('\t');
  }*/
  //Serial.println(); // uncomment this line if you are using raw values
  Serial.println(position - CENTER_POINT); // comment this line out if you are using raw values
  //delay(250);
}
