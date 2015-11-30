/*
  RGB LED control for Motorsport events

  This code is for controlling a track marshal to driver lighting 
  system for use at motorsport events. Individual buttons control 
  RGB led(s), that changes colour according to the button pushed. 
  Currently the three standard traffic light colours(Red, Amber, 
  Green) are coded. Red and Amber flash to catch the driver's eye, 
  while green stay's solid.  

**PINOUT**

Inputs (Tx End):
Button 1(Red)    - 10
Button 2(Yellow) - 11
Button 3(Green)  - 12

Outputs (Rx End):
LED vcc - 4
LED g   - 5
LED r   - 6
LED b   - 7
*/


// RGB led lights {CONTROL, GREEN, RED, BLUE}
int led[]= {4,5,6,7};

// Set pin names for RGB LED
const int ctrlPin = led[0];        // the pin to turn the led on/off
const int greenPin = led[1];       // pin to control the green segment of the led
const int redPin = led[2];        // pin to control the red segment of the led
const int bluePin = led[3];       // pin to control the blue segment of the led
boolean ledState = LOW;
//int fadeAmt = map(fadeAmt, 0, 255, 0, 100);  // Maps the LED brightness to a percantage value

// Buttons {led[0](red), led[1](yellow), led[3](green)}
int buttonRead[] = {1,2,3};

// Timers(milliseconds)
unsigned long prevMillis = 0;
int debounceTime = 5;
int initTime = 1000;


// Variables will change:
boolean buttonState = false;
boolean buttonActive [] = {false,false};

// Light control variables
int activeColour; 


void setup() {
  // Initialise serial communication:
  Serial.begin(9600);
  setupAllPins();
  
}
  void loop() {
    waitForButtonPush(); 
    }   
  
  
  
void setColour(int red, int green, int blue){
      red = 255 - red;
      green = 255 - green;
      blue = 255 - blue;
      analogWrite(redPin, red);
      analogWrite(greenPin, green);
      analogWrite(bluePin, blue);  
      }


// Make the LED flash without using delay function
void runFlashNoDelay(int flashTime){
      unsigned long currentMillis = millis();
      if (currentMillis - prevMillis >= flashTime) {
      // save the last time you blinked the LED
        prevMillis = currentMillis;
      // if the LED is off turn it on and vice-versa:
        if (ledState == LOW) {
          ledState = HIGH;
         } 
        else {
            ledState = LOW;
          }
    // set the LED with the ledState of the variable:
    digitalWrite(ctrlPin, ledState);
  }
    }

//  Make light fade out after stated amount seconds
void runFade(int fadePin, int preFade, int fadeTime, int fadeAmt){
    preFade = preFade * 1000;
    delay(preFade);    
    for (int b = 0; b <= fadeAmt; b++){
    analogWrite(fadePin, b);    
    delay(fadeTime);
        }
}

// Green light
void showGreenLed(){
      setColour(0x00, 0xFF, 0x00);
      activeColour = 3;
      ledState = HIGH;
      digitalWrite(ctrlPin, ledState);
      Serial.flush();
      //runFade(greenPin, 6, 15, 220);
      }

// Yellow light
void showYellowLed(){
      setColour(0xFF, 0x50, 0x00);
      activeColour = 2;
      ledState = HIGH;
      digitalWrite(ctrlPin, ledState);
      runFlashNoDelay(250);
      Serial.flush();
}

// Red light
void showRedLed(){
      setColour(0xFF, 0x00, 0x00);
      activeColour = 1;
      ledState = HIGH;
      digitalWrite(ctrlPin, ledState);
      runFlashNoDelay(500);
      Serial.flush();
   }

// White Light
void showWhiteLed() {
      setColour(0xFF, 0xFF, 0xFF);
      activeColour = 4;
      ledState = HIGH;
      digitalWrite(ctrlPin, ledState);
      Serial.flush();
    }
// Blue Light
void showBlueLed() {
      setColour(0x00, 0x00, 0xFF);
      activeColour = 5;
      ledState = HIGH;
      digitalWrite(ctrlPin, ledState);
      Serial.flush();
    }

void setupAllPins() {
//   Assign led pins
 for (int x = 0; x < 4; x++){
    pinMode(led[x], OUTPUT);
   }
   showYellowLed();
  delay(debounceTime);
}

void waitForButtonPush() {
// read the 3 pushbutton input pins:
  //for (int x = 1; x < 4; x++){  
  while (Serial.available() == 0){
    switch (activeColour){
      case 1:
        runFlashNoDelay(500);
        break;
      case 2:
        runFlashNoDelay(250);
        break;
    }
  }
 if (Serial.available() > 0){
  int data = Serial.read();
  delay(debounceTime);
  if (data == '1'){
    showRedLed();      // Sets the RGB to Red
    }  
  if (data == '2'){
    showYellowLed();      // Sets the RGB to Yellow
     }
  if (data == '3'){
    showGreenLed();     // Sets the RGB to Green
    }
  if (data == '4'){
    showWhiteLed();     // Sets the RGB to White
    }
  if (data == '5'){
    showBlueLed();     // Sets the RGB to White
    }
  }
}
    /*if (activeColour == 1){
         runFlashNoDelay(500);
         }
    if (activeColour == 2){
         runFlashNoDelay(250);
         } 
    else {
      }*/

