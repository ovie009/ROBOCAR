#include "ESP8266WiFi.h"
#include "ESP8266HTTPClient.h"
#include "WiFiClient.h"
#include <Wire.h>

const int SLAVE_ADDRESS = 8; // the slave address

const char* ssid = "Robotcar";
const char* password = "Robotcar";

String host = "http://robotcar.000webhostapp.com";
// String host = "http://192.168.235.138/robocar";
const int httpPort = 80;

String dataFromServer; //data to be sent to ARDUINO UNO via I2C

String mode; // mode switch connected to D0 of ESP8266
String prevMode; // variable to detect switch in operation mode
int motion; // variable to store motion detected state and send it to server

String payload; // data from server

void setup() {
  Serial.begin(115200); // begin serial communication for debugging
  WiFi.begin(ssid, password); // connect to WiFi network
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to the WiFi network");

  Wire.begin(); // begin wire communication via I2C
  pinMode(D8, INPUT); // motion sensor
}

void loop() {
  motion = readMotion(); // get the motion detected state from Arduino
  makeGetRequest(); // this function updates the values of dataFromServer and mode
  delay(500);
}

int readMotion(){
  int motionValue = digitalRead(D7);
  Serial.print("motion: ");
  Serial.println(motionValue);
  return motionValue;
}

void makeGetRequest() {
  WiFiClient client;
  HTTPClient http;
  Serial.println("inside get request");
  String motionString = String(motion);
  String page = "rx.php?id=1&motion="+motionString;
  String url = host + "/" + page;
  if (http.begin(client, url)) {
    Serial.print("GET...");
    int httpCode =  http.GET();

    if (httpCode > 0) {
      Serial.printf("[HTTP] GET... code: %d", httpCode);
      Serial.println("");
        // if request is successful
      if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
        payload = http.getString();
        Serial.print("payload: ");
        Serial.println(payload);
      } 
    } 
    http.end();
    sendData(payload); // send payload to arduino uno  
  } else {
    Serial.printf("[HTTP] Unable to connect");    
  }
}

// called when data is requested by the master
void sendData(String data) {
  Wire.beginTransmission(SLAVE_ADDRESS);
  Wire.write(data.c_str()); // send the data as a character array
  Wire.endTransmission();
  Serial.println("Sent: " + data); // print the sent data
}