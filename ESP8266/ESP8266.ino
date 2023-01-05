#include "ESP8266WiFi.h"
#include "ESP8266HTTPClient.h"
#include "WiFiClient.h"
#include <Wire.h>

const int SLAVE_ADDRESS = 8; // the slave address

const char* ssid = "spartans";
const char* password = "profession";

String host = "https://robotcar.000webhostapp.com";
// String host = "http://192.168.109.138/robocar";
// const char* host = "robotcar.000webhostapp.com";
// const char* host = "192.168.109.138";
const int httpPort = 80;

String dataFromServer; //data to be sent to ARDUINO UNO via I2C

String mode; // mode switch connected to D0 of ESP8266
String prevMode; // variable to detect switch in operation mode
int motion; // variable to store motion detected state and send it to server

String payload; // data from server

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to the WiFi network");

  Wire.begin(); // join the I2C bus as a slave

  pinMode(D7, INPUT); // motion sensor
}

void loop() {
  motion = readMotion(); // get the motion detected state from Arduino
  makeGetRequest(); // this function updates the values of dataFromServer and mode
  delay(1000);
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
        // find the index of th '#' character      
        int delimiterIndex = payload.indexOf('#');


        dataFromServer = payload.substring(0, delimiterIndex);
        mode = payload.substring(delimiterIndex + 1);    

        Serial.println(payload);
      } 
    } 
    http.end();
    sendData(payload);      
  } else {
    Serial.printf("[HTTP] Unable to connect");    
  }
  // String url = "/robocar/rx.php?id=1&motion="+motion;
  // if (client.connect(host, httpPort)) {
  //   client.print(String("GET ") + url + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "Connection: close\r\n\r\n");
  //   unsigned long timeout = millis();
  //   while (client.available() == 0) {
  //     if (millis() - timeout > 100) {
  //       Serial.println(">>> Client Timeout !");
  //       client.stop();
  //       return;
  //     }
  //   }

  //   while(client.available()) {
  //     String payload = client.readStringUntil('\r');
  //     // find the index of th '#' character      
  //     int delimiterIndex = payload.indexOf('#');


  //     dataFromServer = payload.substring(0, delimiterIndex);
  //     mode = payload.substring(delimiterIndex + 1);    

  //     Serial.print("Payload: ");
  //     Serial.println(payload);
  //     Serial.print("Data From Server: ");
  //     Serial.println(dataFromServer);
  //   }
  // } else {
  //   Serial.println("failed to connect");
  // }
  // client.stop();
}

// function to receive message from arduino uno, the motion data
void detectMotion() {
  int data;
  // if (serial.available() > 0) {  
  if (Serial.available() > 0) {  
    Serial.print("slave detected");
    // data = serial.read();
    data = Serial.read();
    motion = data;
  } 
}

// called when data is requested by the master
void sendData(String data) {
  Wire.beginTransmission(SLAVE_ADDRESS);
  Wire.write(data.c_str()); // send the data as a character array
  Wire.endTransmission();
  Serial.println("Sent: " + data); // print the sent data
}