
#include <Keyboard.h>
#include "Mouse.h"
 
const int contAttackButton = 7;
const int switchPin = 2;      // switch to turn on and off mouse control
const int mouseButton = 6;    // input pin for the mouse pushButton
const int xAxis = A0;         // joystick X axis
const int yAxis = A1;         // joystick Y axis
const int ledPin = 8;         // Mouse control LED
const int counter = 13;
int range = 12;               // output range of X or Y movement
int responseDelay = 15;        // response delay of the mouse, in ms
int threshold = range / 4;    // resting threshold
int center = range / 2;       // resting position value
bool mouseIsActive = false;    // whether or not to control the mouse
int lastSwitchState = LOW;        // previous switch state
int pushButton = 2;
bool contAttackEnabled = false;
int axe = A3;
int pickAxe = A5;
 
unsigned long axeHitLastTime;
int hitInbetweenTimeInMili = 500;

unsigned long hits = 0;

const int joystickLeftButton = 11;
const int joystickRightButton = 12;
bool enableSprint = false;

const int menuOpen = 10;
const int eat = 9;
const int esc = 11;

// the setup routine runs once when you press reset:
#line 37 "J:\\Work\\Teenenggr\\Projects\\46 - Minecraft\\wasd\\wasd.ino"
void setup();
#line 62 "J:\\Work\\Teenenggr\\Projects\\46 - Minecraft\\wasd\\wasd.ino"
void loop();
#line 114 "J:\\Work\\Teenenggr\\Projects\\46 - Minecraft\\wasd\\wasd.ino"
void mouseRead();
#line 152 "J:\\Work\\Teenenggr\\Projects\\46 - Minecraft\\wasd\\wasd.ino"
int readAxis(int thisAxis);
#line 171 "J:\\Work\\Teenenggr\\Projects\\46 - Minecraft\\wasd\\wasd.ino"
void readAxe();
#line 188 "J:\\Work\\Teenenggr\\Projects\\46 - Minecraft\\wasd\\wasd.ino"
void readPickAxe();
#line 198 "J:\\Work\\Teenenggr\\Projects\\46 - Minecraft\\wasd\\wasd.ino"
void increaseCount();
#line 202 "J:\\Work\\Teenenggr\\Projects\\46 - Minecraft\\wasd\\wasd.ino"
void timeCheckAndMouseClick();
#line 37 "J:\\Work\\Teenenggr\\Projects\\46 - Minecraft\\wasd\\wasd.ino"
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  // make the pushbutton's pin an input:
  pinMode(pushButton, INPUT);
  pinMode(mouseButton, INPUT);
  pinMode(joystickLeftButton, INPUT);
  pinMode(joystickRightButton, INPUT);
  pinMode(counter, OUTPUT);
  pinMode(contAttackButton, INPUT_PULLUP);

  pinMode(menuOpen, INPUT);
  pinMode(eat, INPUT);
//  pinMode(esc, INPUT);
  
  pinMode(5, INPUT);
  pinMode(2, INPUT);
  pinMode(3, INPUT);  
  pinMode(4, INPUT);

  // take control of the mouse:
  Mouse.begin();
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input pin:
  boolean b1 = digitalRead(5);
  boolean B2 = digitalRead(2);
  boolean B3 = digitalRead(3);
  boolean B4 = digitalRead(4);

  if (b1 == HIGH) {
    Keyboard.press('w');
  } else {
    Keyboard.release('w');
  }
  if (B2 == HIGH) {
    Keyboard.press('s');
  } else {
    Keyboard.release('s');
  }
  if (B3 == HIGH) {
    Keyboard.press('d');
  } else {
    Keyboard.release('d');
  }
  if (B4 == HIGH) {
    Keyboard.press('a');
  } else {
    Keyboard.release('a');
  }

  if(digitalRead(menuOpen) == HIGH) {
    Keyboard.press('e');
  } else {
    Keyboard.release('e');
  }

  if(digitalRead(contAttackButton) == HIGH) {
    contAttackEnabled = true;
  } else {
    contAttackEnabled = false;
  }
//  if(digitalRead(esc) == HIGH) {
//    Keyboard.press(KEY_ESC);
//  } else {
//    Keyboard.release(KEY_ESC);
//  }
  
  mouseRead();
  readAxe();
  readPickAxe();
  timeCheckAndMouseClick();
  delay(responseDelay);        // delay in between reads for stability
}

void mouseRead() {
  int xReading = readAxis(A0);
  int yReading = readAxis(A1);
  Mouse.move(xReading, yReading, 0);

  if(digitalRead(eat) == HIGH) {
    if (!Mouse.isPressed(MOUSE_RIGHT)) {
      Mouse.press(MOUSE_RIGHT);
    }
  } else {
    if (Mouse.isPressed(MOUSE_RIGHT)) {
      Mouse.release(MOUSE_RIGHT);
    }
  }
  
  if (digitalRead(mouseButton) == LOW) {
    enableSprint = !enableSprint;
    if (enableSprint) {
      Keyboard.press(KEY_LEFT_CTRL); 
    } else {
      Keyboard.release(KEY_LEFT_CTRL); 
    }
  }

  if(digitalRead(joystickLeftButton) == HIGH) {
    Keyboard.press(KEY_LEFT_SHIFT);
  } else {
    Keyboard.release(KEY_LEFT_SHIFT);
  }

  if(digitalRead(joystickRightButton) == HIGH) {
    Keyboard.press(0x20);
  } else {
    Keyboard.release(0x20);
  }
}


int readAxis(int thisAxis) {
  // read the analog input:
  int reading = analogRead(thisAxis);

  // map the reading from the analog input range to the output range:
  reading = map(reading, 0, 1023, 0, range);

  // if the output reading is outside from the rest position threshold, use it:
  int distance = reading - center;

  if (abs(distance) < threshold) {
    distance = 0;
  }

  // return the distance for this axis:
  return distance;
}


void readAxe() {
  int val = analogRead(axe);
//  Serial.println(val);
  if (val >= 400) {
    Serial.println(val);
    axeHitLastTime = millis();
    hits += 1;
    increaseCount();
    if (!contAttackEnabled) {
//     Mouse.press(MOUSE_LEFT);
      
//      digitalWrite(counter, LOW);
    }
  }
  
}

void readPickAxe() {
  int val = analogRead(pickAxe);
  if (val >= 500) {
    axeHitLastTime = millis();
    hits += 1;
    increaseCount();
  }
  
}

void increaseCount() {
  digitalWrite(counter, HIGH); 
}

void timeCheckAndMouseClick() {
  int hitTime =  hitInbetweenTimeInMili ;
  if (millis() - axeHitLastTime > 70) {
    digitalWrite(counter,LOW);
  }
  if (millis() - axeHitLastTime < hitTime) {
    if (!Mouse.isPressed(MOUSE_LEFT)) {
      Mouse.press(MOUSE_LEFT);
 //      digitalWrite(counter,LOW);
    }
  } else {
//    Serial.println("OFF");
    if (Mouse.isPressed(MOUSE_LEFT)) {
      Mouse.release(MOUSE_LEFT);
      digitalWrite(counter,LOW);
    }
  }
}
