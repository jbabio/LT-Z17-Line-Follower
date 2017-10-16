void SensorCalibration(){
  for (int i = 0; i < 100; i++)         // Calibration routine
  {                                     // To perform calibration you should sense dark surface then light surface
    BlinkLED(1, 50);                    // Blink LED1 at 50ms to indicate it's in QTR calibration mode. 
    qtrrc.calibrate();                  // Sensor calibration
    delay (40);
  }
      ShowCalibration(LOW);
      SaveQTRCalibrationToEEPROM();
}


