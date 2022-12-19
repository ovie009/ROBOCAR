#include <ESP8266WiFi.h>

const char* ssid = "spartans";
const char* password = "profession";

const char* host = "robotcar.000webhostapp.com";
const int httpPort = 80;

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");
}

void loop() {
  WiFiClient client;
  String url = "/rx.php?id=1";
  if (client.connect(host, httpPort)) {
    client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                 "Host: " + host + "\r\n" +
                 "Connection: close\r\n\r\n");
    unsigned long timeout = millis();
    while (client.available() == 0) {
      if (millis() - timeout > 5000) {
        Serial.println(">>> Client Timeout !");
        client.stop();
        return;
      }
    }
    while(client.available()) {
      String line = client.readStringUntil('\r');
      Serial.print(line);
    }
  }
  client.stop();
  delay(1000);
}
