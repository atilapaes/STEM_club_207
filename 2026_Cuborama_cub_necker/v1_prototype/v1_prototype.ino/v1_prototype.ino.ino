#include <Arduino.h>
#include <TM1637Display.h>
#define CLK 17
#define DIO 18
TM1637Display display(CLK, DIO);

// Patterns of blinking
int pattern = 0;
int n_patterns = 8;

const int buttonPin = 19; // Push button pin

// Define the array with your digital pins for LEDs
int pinCount = 17;
//byte ledPins[] = {1,0,2,3,4,5,6,7,8,9,10,11,12,13,14,16,15};
byte ledPins[] = {1,0,2,3,4,5,6,7,15,16,14,13,12,9,8}; // circular

byte blueledPins[] = {1,0,3,4,6,7,8,9,13,14,16};
byte orangeledPins[] = {2, 5, 12,15};
int bluepinCount = 11;
int orangepinCount =4;



int read_potentiometer(float d) {
  int sensorValue = analogRead(A6);
  // Integer math: simplify to 0-10 range
  int pot_level = sensorValue*(d/1023.0);
  return pot_level;
}

int incremenent_pattern(int p,int n_p) {
  if (p == n_p) {
    p = 0;
  } else {
    p = p + 1;
  }
  return p;
}

void all_leds_off(){
  for (int i = 0; i < pinCount; i++) {
    digitalWrite(ledPins[i], LOW);
  }
}
void setup() {
  Serial.begin(9600); // Start serial communication
  pinMode(buttonPin, INPUT_PULLUP);

  // Define all pins as output at once
  for (int i = 0; i < pinCount; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
  pinMode(7, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);
  display.setBrightness(2); //0 to 3 level of brightness
  display.showNumberDec(pattern);
  delay(1000);
  display.showNumberDec(207);

}

void loop() {
  digitalWrite(10, HIGH);
  digitalWrite(11, HIGH);
  // CHASING LIGHTS
  if (pattern == 0) { 
    for (int i = 0; i < pinCount; i++) {
    digitalWrite(ledPins[i], HIGH);
    int level = read_potentiometer(20); 
    delay(100*(level+1)); // Delay ajusted by the potentiomer. The +1 is to avoid delay 0
    digitalWrite(ledPins[i], LOW);  // Turn off LED
    
    if (digitalRead(buttonPin)==HIGH){ // If button is pressed, change the bink pattern
      pattern = incremenent_pattern(pattern,n_patterns);
      all_leds_off();
      display.showNumberDec(pattern);
      delay(1000);
      display.showNumberDec(207);
      delay(1000);
      break;  // quit the loop of the current pattern
      }
    }

  // Ping Pong
  } else if (pattern == 1) { 
    for (int i = 0; i < pinCount; i++) {
    int level = read_potentiometer(20); 
    digitalWrite(ledPins[i], HIGH); // Turn on LED
    delay(25*(level+1)); // Delay ajusted by the potentiomer. The +1 is to avoid delay 0
    digitalWrite(ledPins[i], LOW);  // Turn off LED
    
    if (digitalRead(buttonPin)==HIGH){ // If button is pressed, change the bink pattern
      pattern = incremenent_pattern(pattern,n_patterns);
      all_leds_off();
      display.showNumberDec(pattern);
      delay(1000);
      display.showNumberDec(207);

      delay(1000);
      break;  // quit the loop of the current pattern
      }
    }
    
    for (int i = pinCount -1; i >=0 ; i--) {
    digitalWrite(ledPins[i], HIGH); // Turn on LED
    int level = read_potentiometer(20); 
    delay(25*(level+1)); // Delay ajusted by the potentiomer. The +1 is to avoid delay 0
    digitalWrite(ledPins[i], LOW);  // Turn off LED

    if (digitalRead(buttonPin)==HIGH){ // If button is pressed, change the bink pattern
      pattern = incremenent_pattern(pattern,n_patterns);
      all_leds_off();
      display.showNumberDec(pattern);
      delay(1000);
      display.showNumberDec(207);

      delay(1000);
      break;  // quit the loop of the current pattern
      }
    }

  //Chasing Dark
  } else if (pattern == 2) { 
    for (int i = 0; i < pinCount; i++) {
    digitalWrite(ledPins[i], HIGH); // Turn on LED
    delay(5);
    }
    for (int i = 0; i < pinCount; i++) {
    digitalWrite(ledPins[i], LOW); // Turn on LED
    int level = read_potentiometer(20); 
    delay(25*(level+1)); // Delay ajusted by the potentiomer. The +1 is to avoid delay 0
    digitalWrite(ledPins[i], HIGH);  // Turn off LED
    
    if (digitalRead(buttonPin)==HIGH){ // If button is pressed, change the bink pattern
      pattern = incremenent_pattern(pattern,n_patterns);
      all_leds_off();
      display.showNumberDec(pattern);
      delay(1000);
      display.showNumberDec(207);
      delay(1000);
      break;  // quit the loop of the current pattern
      }
    }

    //Train of 2 wagons
  } else if (pattern == 3) { 
    
    digitalWrite(ledPins[0], HIGH);
    int level = read_potentiometer(20); 
    delay(25*(level+1)); // Delay ajusted by the potentiomer. The +1 is to avoid delay 0
    
    for (int i = 0; i < pinCount; i++) {
      if ( i != 9 ) {
        digitalWrite(ledPins[i], HIGH); // Turn on LED
        digitalWrite(ledPins[i+1], HIGH);
        int level = read_potentiometer(20); 
        delay(25*(level+1)); // Delay ajusted by the potentiomer. The +1 is to avoid delay 0
        digitalWrite(ledPins[i], LOW);  // Turn off LED
        digitalWrite(ledPins[i+1], LOW);  // Turn off LED

        if (digitalRead(buttonPin)==HIGH){ // If button is pressed, change the bink pattern
          pattern = incremenent_pattern(pattern,n_patterns);
          all_leds_off();
          display.showNumberDec(pattern);
          delay(1000);
          display.showNumberDec(207);
          delay(1000);
          break;  // quit the loop of the current pattern
          }
        }
    }
    digitalWrite(ledPins[9], HIGH);
    level = read_potentiometer(20); 
    delay(25*(level+1)); // Delay ajusted by the potentiomer. The +1 is to avoid delay 0
    digitalWrite(ledPins[9], LOW);  // Turn off LED


  // LOADING
  } else if (pattern == 4) {
    for (int i = 0; i < pinCount; i++) {
      int level = read_potentiometer(10); 
      delay(20*(level+1)); // Delay ajusted by the potentiomer. The +1 is to avoid delay 0
      for (int j =0; j <= i; j++) {
        digitalWrite(ledPins[j], HIGH); // Turn on LED  
      }
      if (digitalRead(buttonPin)==HIGH){ // If button is pressed, change the bink pattern
        pattern = incremenent_pattern(pattern,n_patterns);
        all_leds_off();
        display.showNumberDec(pattern);
        delay(1000);
        display.showNumberDec(207);
        delay(1000);
        break;  // quit the loop of the current pattern
        }
      }
    for (int i = 0; i < pinCount; i++) {
      int level = read_potentiometer(10); 
      delay(20*(level+1)); // Delay ajusted by the potentiomer. The +1 is to avoid delay 0
      for (int j =0; j <= i; j++) {
        digitalWrite(ledPins[j], LOW); // Turn on LED  
      }
      if (digitalRead(buttonPin)==HIGH){ // If button is pressed, change the bink pattern
        pattern = incremenent_pattern(pattern,n_patterns);
        all_leds_off();
        display.showNumberDec(pattern);
        delay(1000);
        display.showNumberDec(207);
        delay(1000);
        break;  // quit the loop of the current pattern
        }
      }

  //FILL AND EMPTY
  } else if (pattern == 5) {
    for (int i = 0; i < pinCount; i++) {
      int level = read_potentiometer(10); 
      delay(20*(level+1)); // Delay ajusted by the potentiomer. The +1 is to avoid delay 0
      for (int j =0; j <= i; j++) {
        digitalWrite(ledPins[j], HIGH); // Turn on LED  
      }
      if (digitalRead(buttonPin)==HIGH){ // If button is pressed, change the bink pattern
        pattern = incremenent_pattern(pattern,n_patterns);
        all_leds_off();
        display.showNumberDec(pattern);
        delay(1000);
        display.showNumberDec(207);
        delay(1000);
        break;  // quit the loop of the current pattern
        }
      }
    int level = read_potentiometer(10); 
    delay(20*(level+1)); // Delay ajusted by the potentiomer. The +1 is to avoid delay 0
    for (int i = pinCount -1; i >= 0; i--) {
      int level = read_potentiometer(10); 
      delay(20*(level+1)); // Delay ajusted by the potentiomer. The +1 is to avoid delay 0
      digitalWrite(ledPins[i], LOW); // Turn on LED  
      
      if (digitalRead(buttonPin)==HIGH){ // If button is pressed, change the bink pattern
        pattern = incremenent_pattern(pattern,n_patterns);
        all_leds_off();
        display.showNumberDec(pattern);
        delay(1000);
        display.showNumberDec(207);
        delay(1000);
        break;  // quit the loop of the current pattern
        }
      }

  // BLINKING
  } else if (pattern == 6) { 
    for (int i = 0; i < pinCount; i++) {
      int level = read_potentiometer(20); 
      for (int i = 0; i < pinCount; i++) {
        digitalWrite(ledPins[i], HIGH); // Turn on LED
      }
      delay(75*(level+1)); // Delay ajusted by the potentiomer. The +1 is to avoid delay 0
      for (int i = 0; i < pinCount; i++) {
        digitalWrite(ledPins[i], LOW); // Turn on LED
      }
      delay(75*(level+1)); // Delay ajusted by the potentiomer. The +1 is to avoid delay 0
      if (digitalRead(buttonPin)==HIGH){ // If button is pressed, change the bink pattern
        pattern = incremenent_pattern(pattern,n_patterns);
        all_leds_off();
        display.showNumberDec(pattern);
        delay(1000);
        display.showNumberDec(207);
        delay(1000);
        break;  // quit the loop of the current pattern
        }
      }


  // BLINKING BLUE THAN ORANGE
  } else if (pattern == 7) { 
    for (int i = 0; i < pinCount; i++) {
      int level = read_potentiometer(10); 
      for (int i = 0; i < bluepinCount; i++) {
        digitalWrite(blueledPins[i], HIGH); // Turn on LED
      }
      delay(200*(level+1)); // Delay ajusted by the potentiomer. The +1 is to avoid delay 0
      for (int i = 0; i < bluepinCount; i++) {
        digitalWrite(blueledPins[i], LOW); // Turn on LED
      }
      
      if (digitalRead(buttonPin)==HIGH){ // If button is pressed, change the bink pattern
        pattern = incremenent_pattern(pattern,n_patterns);
        all_leds_off();
        display.showNumberDec(pattern);
        delay(1000);
        display.showNumberDec(207);
        delay(1000);
        break;  // quit the loop of the current pattern
      }
      
      level = read_potentiometer(10); 
      for (int i = 0; i < orangepinCount; i++) {
        digitalWrite(orangeledPins[i], HIGH); // Turn on LED
      }
      delay(200*(level+1)); // Delay ajusted by the potentiomer. The +1 is to avoid delay 0
      
      for (int i = 0; i < orangepinCount; i++) {
        digitalWrite(orangeledPins[i], LOW); // Turn on LED
      }
      
      if (digitalRead(buttonPin)==HIGH){ // If button is pressed, change the bink pattern
        pattern = incremenent_pattern(pattern,n_patterns);
        all_leds_off();
        display.showNumberDec(pattern);
        delay(1000);
        display.showNumberDec(207);
        delay(1000);
        break;  // quit the loop of the current pattern
        }
      }  

// ALL LEDS ON
  } else if (pattern == 8) {
    for (int i = 0; i < pinCount; i++) {
    digitalWrite(ledPins[i], HIGH); // Turn on LED
    delay(5);
    if (digitalRead(buttonPin)==HIGH){ // If button is pressed, change the bink pattern
      pattern = incremenent_pattern(pattern,n_patterns);
      all_leds_off();
      display.showNumberDec(pattern);
      delay(1000);
      display.showNumberDec(207);
      delay(1000);
      break;  // quit the loop of the current pattern
      }
    }

  } else {
    if (digitalRead(buttonPin)==HIGH){ // If button is pressed, change the bink pattern
        pattern = incremenent_pattern(pattern,n_patterns);
        all_leds_off();
        display.showNumberDec(pattern);
        delay(1000);
        display.showNumberDec(207);
        delay(1000);
        //break;  // quit the loop of the current pattern
        }
  }

}

