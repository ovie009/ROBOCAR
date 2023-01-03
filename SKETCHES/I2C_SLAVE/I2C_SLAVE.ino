#include <Wire.h>

const int SLAVE_ADDRESS = 8;  // Set the slave address

void setup() {
  Serial.begin(9600);  // start serial for output

  // Initialize the slave
  Wire.begin();        // join i2c bus (address optional for master)
  Wire.begin(SLAVE_ADDRESS);
  Wire.onReceive(receiveData);
  Wire.onRequest(sendData);
}

// Function that executes whenever data is requested by the master
void sendData() {
  // Wire.beginTransmission(SLAVE_ADDRESS);  // start transmission to the slave
  Wire.write("Hello from slave");  // send a string
  // Wire.endTransmission();                 // end the transmission
}

// Function that executes whenever data is received from the master
void receiveData(int numBytes) {
  String data = "";
  while (Wire.available()) {  // loop through all the received bytes
    data += (char)Wire.read();  // add the received byte to the string
  }
  Serial.println(data);  // print the received data to the serial monitor
}

void loop() {
  // Do nothing here
  Serial.println("slave running");
  delay(1000);
}
