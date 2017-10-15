void ToggleLED(bool led1State, bool led2State){
  digitalWrite(led1, led1State);
  digitalWrite(led2, led2State);
}

void BlinkLED(int blinkMode, int blinkInterval){
  static bool led1State = LOW;                              // LED 1 state holder, static type to have global lifetime
  static bool led2State = LOW;                              // LED 2 state holder, static type to have global lifetime
  static unsigned long previousMillis = 0;                  // Last time LEDs were updated, static type to have global lifetime
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= blinkInterval) {
    previousMillis = currentMillis;                         // save the last time you blinked the LED
    switch (blinkMode) {
      case 1:    // 1: Blink LED1
        if (led1State == LOW) {
          led1State = HIGH;
        } else {
          led1State = LOW;
        }
        led2State = LOW;
        break;
      case 2:    // 2: Blink LED2
        led1State = LOW;
        if (led2State == LOW) {
          led2State = HIGH;
        } else {
          led2State = LOW;
        }
        break;
      case 11:    // 11: Blink LED1 & LED2 simultanuously
        if (led1State == LOW) {
          led1State = HIGH;
          led2State = HIGH;
        } else {
          led1State = LOW;
          led2State = LOW;
        }
        break;
      case 22:    // 22: Blink LED1 & LED2 alternatively
        if (led1State == LOW) {
          led1State = HIGH;
          led2State = LOW;
        } else {
          led1State = LOW;
          led2State = HIGH;
        }
        break;
    }   
    ToggleLED (led1State, led2State);
  }
}

