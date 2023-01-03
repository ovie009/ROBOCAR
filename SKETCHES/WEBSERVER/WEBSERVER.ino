#include <ESP8266WiFi.h>
#include <Wire.h>

const char* ssid = "spartans";
const char* password = "profession";

const char* host = "robotcar.000webhostapp.com";
// const char* host = "192.168.100.138";
const int httpPort = 80;

byte binSignal = 0; //number to be sent to ARDUINO UNO via I2C

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to the WiFi network");
  // begin wire communication via I2C
  Wire.begin(D2, D3); // (SDA, SCL) join I2C bus (address optional for master)
}

void loop() {

  WiFiClient client;
  
  String url = "/robocar/rx.php?id=1&mode=";
  if (client.connect(host, httpPort)) {
    client.print(String("GET ") + url + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "Connection: close\r\n\r\n");
    unsigned long timeout = millis();
    while (client.available() == 0) {
      if (millis() - timeout > 5000) {
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
      String payloadGet = payload.substring(startIndex, endIndex);

      if (payloadGet == "N/A")
      {
        /* code */
        binSignal = 0;
      }
      else if (payloadGet == "car_forward")
      {
        /* code */
        binSignal = 1;
      }
      else if (payloadGet == "car_backward")
      {
        /* code */
        binSignal = 2;
      }
      else if (payloadGet == "car_left")
      {
        /* code */
        binSignal = 3;
      }
      else if (payloadGet == "car_right")
      {
        /* code */
        binSignal = 4;
      }
      else if (payloadGet == "cam_left")
      {
        /* code */
        binSignal = 5;
      }
      else if (payloadGet == "cam_right")
      {
        /* code */
        binSignal = 6;
      }
      else if (payloadGet == "reset")
      {
        /* code */
        binSignal = 7;
      }
      else if (payloadGet == "standBy")
      {
        /* code */
        binSignal = 9;
      }
      Serial.println(payload);
      Serial.println(payloadGet);
      Serial.println(binSignal);

      Wire.beginTransmission(8); // transmit to device #8
      Wire.write(binSignal);        // sends five bytes
      Wire.endTransmission();    // stop transmitting
    }
  }
  client.stop();
  delay(1000);
}
