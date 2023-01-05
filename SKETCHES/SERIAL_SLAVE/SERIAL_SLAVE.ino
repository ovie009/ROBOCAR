#include <SoftwareSerial.h>

SoftwareSerial serial(11, 10); // RX, TX
int motion;
int motionSensor = 8;

String data = "null";
void setup() {
  Serial.begin(9600);
  serial.begin(9600);
  Serial.println("setup complete");
  pinMode(motionSensor, INPUT);
  delay(1000);
}

void loop() {
  data = receiveString();
  Serial.print("Data Received: ");
  Serial.println(data);
  delay(1000);
}

// Arduino code

String receiveString() {
  // Create a string to store the received data
  String str = "";

  // Read data from the serial port until a newline character is received
  while (true) {
    // Serial.println("inside loop");
    if (serial.available() > 0) {
      char c = serial.read();
      // Serial.println("inside serial");
      if (c == '#') {
        break;
      }
      str += c;
    }
  }
  serial.write(readMotion());
  return str;
}

int readMotion(){
  motion = digitalRead(motionSensor);
  Serial.print("motion: ");
  Serial.println(motion);
  return motion;
}