#include "SoftwareSerial.h"

SoftwareSerial serial(D6, D5); // RX, TX

String message = "Hello from ESP8266#";
int motion;

void setup() {
  Serial.begin(115200);
  serial.begin(9600);
}

void loop() {
    
  sendString(message);
  Serial.println("send meassage to slave");

  motion = detectMotion();

  Serial.print("motion: ");
  Serial.println(motion);

  delay(1000);
}

// ESP8266 code

void sendString(String str) {
  // Convert the string to a character array
  char data[str.length() + 1];
  str.toCharArray(data, str.length() + 1);

  // Send the character array to the Arduino
  serial.write(data);
}

int detectMotion() {
  int data;
  if (serial.available() > 0) {  
    data = serial.read();
  }     
  return data;
}
