bool CheckButton(int buttonPin){                  // Takes a pin number as parameter and returns a boolean. (HIGH: button pressed)
  static unsigned long lastDebounceTime = 0;      // the last time the output pin was toggled, static type to have global lifetime
  static unsigned long debounceDelay = 50;        // the debounce time; increase if the output flickers, static type to have global lifetime
  static bool buttonState;                        // Reading from the button pin, static type to have global lifetime.
  static bool lastButtonState;                    // The previous reading from the button pin, static type to have global lifetime
  bool buttonPressed = LOW;                       // Variable which value is returned by the function.
  bool reading = digitalRead(buttonPin);          // read the state of the switch
  
  if (reading != lastButtonState) {               // If the switch changed, due to noise or pressing:
    lastDebounceTime = millis();                  // reset the debouncing timer
  }
  if ((millis() - lastDebounceTime) > debounceDelay) {  // current button state has been there longer than debounce delay, take it as current state.
    if (reading != buttonState) {                 // if the button state has changed:
      buttonState = reading;
      if (buttonState == HIGH) {                  // only toggle if the new button state is HIGH
        buttonPressed = !buttonPressed;
      }
    }
  }
  lastButtonState = reading;                      // save the reading.  Next time through the loop,
  return buttonPressed;
}

