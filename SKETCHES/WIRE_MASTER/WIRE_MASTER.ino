#include <Wire.h>

const int SLAVE_ADDRESS = 8; // the slave address

void setup() {
  Serial.begin(115200); // start the serial communication
  Wire.begin(); // join the I2C bus as a slave
}

void loop() {
  // do nothing
  sendData();
}

// called when data is requested by the master
void sendData(String data) {
  Wire.beginTransmission(SLAVE_ADDRESS);
  Wire.write(data.c_str()); // send the data as a character array
  Wire.endTransmission();
  Serial.println("Sent: " + data); // print the sent data
}
