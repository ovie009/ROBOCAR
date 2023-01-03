#include <Wire.h>

const int SLAVE_ADDRESS = 8;  // Set the slave address

void setup() {
  Wire.begin(D2, D1); // (SDA, SCL) join I2C bus (address optional for master)
  Serial.begin(115200);  // start serial for output
}

void loop() {
  sendData();

  delay(1000);  // delay for 1 second
}

void sendData() {
  // Send data to the slave
  Wire.beginTransmission(SLAVE_ADDRESS);  // start transmission to the slave
  Wire.write("Hello from the master");    // send a string
  Wire.endTransmission();                 // end the transmission
}
