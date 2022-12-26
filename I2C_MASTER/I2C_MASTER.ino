#include <Wire.h>

void setup() {
  Wire.begin(D2, D3); // (SDA, SCL) join I2C bus (address optional for master)
}

byte x = 0;

void loop() {
  Wire.beginTransmission(8); // transmit to device #8
  Wire.write(x);        // sends five bytes
  Wire.endTransmission();    // stop transmitting
  delay(100);

  x++;
}
