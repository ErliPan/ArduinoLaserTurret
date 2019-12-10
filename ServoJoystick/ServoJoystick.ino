#include <Servo.h>
Servo myservo;
Servo myservo2;

int servo1 = 9;
int servo2 = 11;

int joystickX = A6;
int joystickY = A7;

int laser = 6;

int joystickButton = 2;

//Temporary variable to store data
int val, val2;

//Default values
int x = 90;
int y = 90;

bool laserStatus = false;

// Sensibility higher = slower lower = faster
int sens = 400;

void setup() {
  myservo.attach(servo1);
  myservo2.attach(servo2);

  pinMode(joystickButton, INPUT_PULLUP);
  pinMode(laser, OUTPUT);
}

void loop() {
  val = analogRead(joystickX) - 512;
  val2 = analogRead(joystickY) - 512;

  x += val / sens;

  //y += val2 / sens;

  //Using -= because i like inverted input
  y -= val2 / sens;

  if (x > 180) x = 180;
  if (y > 180) y = 180;
  if (x < 0) x = 0;
  if (y < 0) y = 0;

  if (!digitalRead(joystickButton)) {
    laserStatus = !laserStatus;
    digitalWrite(laser, laserStatus);
    // Prevent bounces
    delay(200);
  }
  
  myservo.write(x);
  myservo2.write(y);
  
  delay(13);
}
