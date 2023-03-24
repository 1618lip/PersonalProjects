/*
DIY Reactive Night Lamp
Created by Philip Pincencia
3/21/2023
*/

const int red = 11; // red LED connected to PWM pin 11 
const int green = 10; // green LED connected to PWM pin 10 
const int blue = 9; // blue LED connected to PWM pin 9 
const int sound = A0; // sound sensor connected to analog pin 0
const int motion = 12; // motion sensor connected to PWM pin 12

int state = LOW; // signals if the servo has reached its max rotation. 
int d = 200; // how fast servo spins (delays the rotation)
double k; // variable to store the value from the sound sensor
double t = 0; // to cycle through the LEDs (acts like time)
int r=0; // initial incremental value for the position of the servo
double a1, a2, a3; // variables for the luminosity for each LED

double v = 230; // max luminosity of the LEDs

#include <Servo.h>
Servo myservo;  // create servo object to control a servo
int pos = 0; // initial position of the servo

void setup() {
  // set IO pins
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
  pinMode(sound, INPUT);
  pinMode(motion, INPUT);

  myservo.attach(3); // servo attached to PWM 3
  myservo.write(0); // servo starts in 0th position
  Serial.begin(115200); // 115200 baud
} 

void loop() { 
  if (analogRead(sound) > 490) {
    k = analogRead(sound)*0.8;
    }
  else {
    k=0;
    }
  
  a1 = abs(sin(0.4*t-1))+k;
  a2 = abs(sin(0.4*t))-0.5*k;
  a3 = abs(sin(0.4*t+1))+0.5*k; 

  analogWrite(red, v*a1);
  analogWrite(green, v*a2);
  analogWrite(blue, v*a3); 
  t += 0.0006; // incremental value
  
  if (digitalRead(motion) == HIGH) { // logic for the servo's rotating motion
    if (d == 150) {
      myservo.write(pos + 1);
      }
    d -= 0.02;
    if (d > 0) {
      myservo.write(pos);
      }
    else {
      pos = r;
      myservo.write(pos);
      if (r == 180) {
        state = HIGH;
      }
      if (state == HIGH) {
        r--;
        if (r == 0) {
          state = LOW;
          }
        }
      else {
        r++;
        }
      d = 150;
      }
    }
}