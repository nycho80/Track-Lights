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
Button 1(Red)    - 12
Button 2(Yellow) - 11
Button 3(Green)  - 10

Outputs (Rx End):
LED vcc - 4
LED g   - 5
LED r   - 6
LED b   - 7
*/

/* 
// RGB led lights {CONTROL, GREEN, RED, BLUE}
int led[]= {4,5,6,7};

// Set pin names for RGB LED
const int ctrlPin = led[0];        // the pin to turn the led on/off
const int greenPin = led[1];       // pin to control the green segment of the led
const int redPin = led[2];        // pin to control the red segment of the led
const int bluePin = led[3];       // pin to control the blue segment of the led
boolean ledState = LOW;
*/

// PINS:
// Buttons {led[0](red), led[1](yellow), led[3](green)}
int button[] = {12,11,10};
// Sheild power
//int sheildVcc = 13;

// Timers(milliseconds)
unsigned long prevMillis = 0;
int debounceTime = 50;
int initTime = 1000;


// Variables will change:
boolean buttonState = LOW;
boolean buttonActive [] = {false,false};
boolean sheildVccCtrl = HIGH;
int handShake; // Debug Data from Rx

// Variable for current active light colour
int activeColour = 1;         

void setup() {
  // Initialise serial communication:
  Serial.begin(9600);
  Serial1.begin(9600);
  setupPins();
}
  void loop() {
    waitForButtonPush(); 
    }   
  
  
  
/*void setColour(int red, int green, int blue){
      red = 255 - red;
      green = 255 - green;
      blue = 255 - blue;
      analogWrite(redPin, red);
      analogWrite(greenPin, green);
      analogWrite(bluePin, blue);  
      }
*/

/*
// Make the LED flash without using delay function
void runFlashNoDelay(const int flashTime){
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
*/

// Green light
void sendGreen(){
      
      //setColour(0x00, 0xFF, 0x00);
      activeColour = 3;
      Serial.write(activeColour);
      //ledState = HIGH;
      //digitalWrite(ctrlPin, ledState);
      }

// Yellow light
void sendYellow(){
      //setColour(0xFF, 0x80, 0x00);
      activeColour = 2;
      Serial.write(activeColour);
      //ledState = HIGH;
      //digitalWrite(ctrlPin, ledState);
    }

// Red light
void sendRed(){
      //setColour(0xFF, 0x00, 0x00);
      activeColour = 1;
      Serial.write(activeColour);
      //ledState = HIGH;
      //digitalWrite(ctrlPin, ledState);
    }

void setupPins(){
  /* Assign led pins
 for (int x = 0; x < 4; x++){
    pinMode(led[x], OUTPUT);
   }*/
   sendYellow();   
  // Assign button pins
  for (int x = 0; x < 3; x++){
    pinMode(button[x], INPUT);
  }
 // pinMode(sheildVcc, OUTPUT);
  delay(debounceTime);
  //digitalWrite(sheildVcc, sheildVccCtrl);
}

void waitForButtonPush() {
// read the 3 pushbutton input pins:
  for (int x = 0; x < 3; x++){  
    buttonState = digitalRead(button[x]);
    if (buttonState == HIGH){ 
    delay(debounceTime);
     if (x == 0){
        Serial.print('1');      // Sets the RGB to Red
      }  
      if (x == 1){
        Serial.print('2');      // Sets the RGB to Yellow
        }
      if (x == 2){
        Serial.print('3');     // Sets the RGB to Green
        }
      }
  }
}
