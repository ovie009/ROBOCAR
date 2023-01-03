#include "Wire.h"
#include "ESP8266WiFi.h"

const char* ssid = "spartans";
const char* password = "profession";

// const char* host = "robotcar.000webhostapp.com";
const char* host = "192.168.100.138";
const int httpPort = 80;

String dataFromServer; //data to be sent to ARDUINO UNO via I2C
const int SLAVE_ADDRESS = 8;  // Set the slave address

String mode; // mode switch connected to D0 of ESP8266
String prevMode; // variable to detect switch in operation mode
int motionSensor; // mode switch connected to D1 of ESP8266

void setup() {
  Serial.begin(115200);
  Wire.begin(D2, D1); // (SDA, SCL) join I2C bus (address optional for master)
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to the WiFi network");

  getSettings();
  // prevMode = mode;
}

void loop() {
  getSettings();
  makeGetRequest();
  wireData(); // send data to Arduino Uno
  delay(100);
}

void makeGetRequest() {
  
  WiFiClient client;
  Serial.println("inside get request");
  
  String url = "/robocar/rx.php?id=1&mode="+mode+"&motion="+motionSensor;
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
      int startIndex = payload.indexOf('#') + 1; 
      // find the index of th '#' character          
      int endIndex = payload.indexOf('@'); 

      // get payload
      dataFromServer = payload.substring(startIndex, endIndex);
      // Serial.println(payload);
      // Serial.println(payloadGet);
      Serial.println(dataFromServer);
    }
  } else {
    Serial.println("failed to connect");
  }
  client.stop();
}

// send data to Arduino Uno via I2C
void wireData(){
  // Send data to the slave
  Wire.beginTransmission(SLAVE_ADDRESS);  // start transmission to the slave
  for (int i = 0; i < dataFromServer.length(); i++) { // loop through each character
    Wire.write(dataFromServer[i]); // send the character
  }
  Wire.endTransmission();    // stop transmitting
}

// get mode switch values and motion sensor values
void getSettings() {
  mode = "STREAM";
  motionSensor = 0;
}

