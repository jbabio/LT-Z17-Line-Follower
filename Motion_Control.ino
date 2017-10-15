 void pid(int maxSpeed, float Kp, float Ki, float Kd){
  static int  derivative=0, proportional=0, integral=0, pwm_output=0;  // Variables for PID, static type to have global lifetime
  static int error[6] = { 0,0,0,0,0,0 };                               // Last 6 proportional values to calculate Integral value, static type to have global lifetime
  int i = 0;                                                        // Generic counter.
  position = qtrrc.readLine(sensorValues, QTR_EMITTERS_ON, (line_type));
  proportional = (position) - CENTER_POINT;                         // Obtaining the proportional value (error)
  for ( i = 0 ; i < 6 ; i++ ){
    integral += error[i];                                           // Sum last 6 errors to calculate "integral" value.
  }
  derivative = (proportional - error[0]);                           //Obtain derivative value (error[0] contains last proportional value)
  pwm_output =( proportional * Kp ) + ( derivative * Kd ) + (integral*Ki);
  
  if ( pwm_output > maxSpeed )   pwm_output = maxSpeed;             // Limit positive PWM output to maxSpeed
  if ( pwm_output < -maxSpeed )  pwm_output = -maxSpeed;            // Limit negative PWM output to -maxSpeed
  
  if (pwm_output < 0) {
  motor1.drive(maxSpeed);
  motor2.drive(maxSpeed+pwm_output);
  }
 
  if (pwm_output >0) {
    motor1.drive(maxSpeed-pwm_output);
    motor2.drive(maxSpeed);
  }
 // Preparation for next run
  for ( i = 5 ; i > 0 ; i-- ) {
    error[i] = error[i - 1];                                        // Shift all errors one position up, discarding oldest one.
  }
  error[0] = proportional;                                          // Add the last proportional value (error) as "error[0]"
  integral= 0;                                                      // Set "integral" to 0
}

void OutOfTrack(){                                                  // Contingency routine to find the line if it was lost.
  bool outOfTrackFlag;
  unsigned long timeoutInterval = 1000;                             // Timeout (in millisenconds) to search for the line.
  unsigned long timeoutCurrentMillis;                               // Current millis()for timeout calculation.
  int threshold = 700;
  position = qtrrc.readLine(sensorValues, QTR_EMITTERS_ON, (line_type));
  if (position<=500)                                                // Went out of the line on the right side.
  {
    outOfTrackFlag = HIGH;
    motor1.drive(maxSpeed);                                         // Left motor at topspeed to push the "nose" to the line
    motor2.drive(-maxSpeed);                                        // Right motor at topspeed backwards to reduce turning radius
    while(outOfTrackFlag == HIGH)                                   // Closed loop trying to find the line. Ended when the line is found or by timeout.
    {
      BlinkLED(22, 50);                                             // LEDs swing at 50ms. Line was lost, bot attempts to recover its path.
      PauseCheck();                                                 // Keep checking button presses
      qtrrc.read(sensorValues);                                     // Read sensor.  
      if ( sensorValues[0]>threshold || sensorValues[1]>threshold ) // Check if one of the outer sensors detected the line
      {
        outOfTrackFlag = LOW;                                       // Line was found -> Exit while() & Return to loop(),
      }
      timeoutCurrentMillis = millis(); 
      if (timeoutCurrentMillis - GoneOutOfTrackMillis >= timeoutInterval) {
        outOfTrackFlag = LOW;                                       // Exit while() due to Timeout.
        Pause();                                                    // Pause the bot and wait for user input.
      }
    }
  }
  if (position>=6500)                                               // Went out of the line on the left side.
  { 
    outOfTrackFlag = HIGH;
    motor1.drive(-maxSpeed);                                        // Left motor at topspeed backwards to reduce turning radius
    motor2.drive(maxSpeed);                                         // Right motor at topspeed to push the "nose" to the line
    while(outOfTrackFlag == HIGH)                                   // Closed loop trying to find the line. Ended when the line is found or by timeout.
    {
      BlinkLED(22, 50);                                             // LEDs swing at 50ms. Line was lost, bot attempts to recover its path. 
      PauseCheck();                                                 // Keep checking button presses
      qtrrc.read(sensorValues);
      if (sensorValues[7]>threshold || sensorValues[6]>threshold )  // Check if one of the outer sensors detected the line
      {
        outOfTrackFlag = LOW;                                       // Line was found -> Exit while() & Return to loop(),
      }
      timeoutCurrentMillis = millis(); 
      if (timeoutCurrentMillis - GoneOutOfTrackMillis >= timeoutInterval) {
        outOfTrackFlag = LOW;
        Pause();                                                    // Pause the bot and wait for user input.
      }
    }
  }
}


