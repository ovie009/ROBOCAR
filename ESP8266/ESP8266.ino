#include "ESP8266WiFi.h"
#include "SoftwareSerial.h"

SoftwareSerial serial(D6, D5); // RX, TX
const char* ssid = "spartans";
const char* password = "profession";

// const char* host = "robotcar.000webhostapp.com";
const char* host = "192.168.109.138";
const int httpPort = 80;

String dataFromServer; //data to be sent to ARDUINO UNO via I2C
const int SLAVE_ADDRESS = 8;  // Set the slave address

String mode; // mode switch connected to D0 of ESP8266
String prevMode; // variable to detect switch in operation mode
int motion; // variable to store motion detected state and send it to server

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to the WiFi network");

  // begin serial communication with arduino
  serial.begin(9600);

  getSettings();
  // prevMode = mode;
}

void loop() {
  motion = detectMotion(); // get the motion detected state from Arduino
  makeGetRequest(); // this function updates the values of dataFromServer and mode
  sendString(dataFromServer+"#"+mode);
  delay(100);
}

void makeGetRequest() {
  
  WiFiClient client;
  Serial.println("inside get request");
  
  String url = "/robocar/rx.php?id=1&motion="+motion;
  if (client.connect(host, httpPort)) {
    client.print(String("GET ") + url + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "Connection: close\r\n\r\n");
    unsigned long timeout = millis();
    while (client.available() == 0) {
      if (millis() - timeout > 100) {
        Serial.println(">>> Client Timeout !");
        client.stop();
        return;
      }
    }

    while(client.available()) {
      String payload = client.readStringUntil('\r');
      // find the index of th '#' character      
      int delimiterIndex = payload.indexOf('#');

      dataFromServer = payload.substring(0, delimiterIndex);
      mode = payload.substring(delimiterIndex + 1);    
      
      Serial.println(dataFromServer);
    }
  } else {
    Serial.println("failed to connect");
  }
  client.stop();
}

// function to send message to arduino uno
void sendString(String str) {
  // Convert the string to a character array
  char data[str.length() + 1];
  str.toCharArray(data, str.length() + 1);

  // Send the character array to the Arduino
  serial.write(data);
}

// function to receive message from arduino uno, the motion data
int detectMotion() {
  int data;
  if (serial.available() > 0) {  
    data = serial.read();
  }     
  return data;
}

