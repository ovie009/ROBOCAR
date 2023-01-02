#include <Wire.h>

// SDA - A4 or Arduino Uno connected to D2 of ESP8266
// SCL - A4 or Arduino Uno connected to D3 of ESP8266

void setup() {
  Wire.begin(8);                // join I2C bus with address #8
  Wire.onReceive(receiveEvent); // register event
  Serial.begin(9600);           // start serial for output
}

void loop() {
  delay(100);
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany) {
  int x = Wire.read();    // receive byte as an integer
  Serial.println(x);         // print the integer
}
