#include <Servo.h>

Servo myservo;  // create servo object to control a servo

//int potpin = 0;  // analog pin used to connect the potentiometer
int val = 0;    // variable to read the value from the analog pin
int ctrl = 1;

void setup() {
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  Serial.begin(9600);
  myservo.write(90);     
}

void loop() {
  //val = analogRead(potpin);            // reads the value of the potentiometer (value between 0 and 1023)
  //  val = map(val, 0, 1023, 0, 180);     // scale it to use it with the servo (value between 0 and 180)
  // val = val + ctrl;
  // myservo.write(val);                  // sets the servo position according to the scaled value
  // delay(50);                           // waits for the servo to get there

  // if(val > 180){
  //   ctrl = -1;
  // } else if (val < 0){
  //   ctrl = 1;
  // }
  // Serial.println(val);
}
