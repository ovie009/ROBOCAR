#include <Wire.h>

const int SLAVE_ADDRESS = 8; // the slave address

void setup() {
  Serial.begin(115200); // start the serial communication
  Wire.begin(SLAVE_ADDRESS); // join the I2C bus as a slave
  Wire.onReceive(receiveData); // register the receive callback
}

void loop() {
  // do nothing
}

// called when data is received from the master
void receiveData(int numBytes) {
  String data = "";
  while (Wire.available()) { // loop through all received bytes
    data += (char)Wire.read(); // add the byte to the string
  }
  Serial.println("Received: " + data); // print the received data
}