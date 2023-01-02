// ESP8266 ESP NOW Slave code
#include "espnow.h"
#include "Wire.h"
#include "ESP8266WiFi.h"

// channel for ESP NOW Connection
#define CHANNEL 1
// String message = "esp now failed!"; // message received from esp now
String message = "192.168.95.43#STREAM"; // message received from esp now

const char* ssid = "spartans";
const char* password = "profession";

const char* host = "robotcar.000webhostapp.com";
const int httpPort = 80;

byte binSignal = 0; //number to be sent to ARDUINO UNO via I2C

String IP; // IP address of ESP32 cam to be received from ESP32 CAM using ESP NOW
String mode; // mode of operation, also being treceived from ESP32 CAM using ESP NOW
String captured; // variable to store image captured state
// yes = image captured; no = image not captured; failed = capture failed;

void setup() {
  Serial.begin(115200);
  Serial.println("ESPNow/Basic/Slave Example");
  //Set device in AP mode to begin with
  WiFi.mode(WIFI_AP_STA);
  // configure device AP mode
  configDeviceAP();
  // This is the mac address of the Slave in AP Mode
  Serial.print("AP MAC: "); Serial.println(WiFi.softAPmacAddress());
  // Init ESPNow with a fallback logic
  InitESPNow();
  // Once ESPNow is successfully Init, we will register for recv CB to
  // get recv packer info.
  esp_now_register_recv_cb(OnDataRecv);

  WiFi.begin(ssid, password, CHANNEL);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to the WiFi network");
}

void loop() {
  if (message == "esp now failed!")
  {
    /* code */
    binSignal = 8;
    espNowFailedToServer(); // make server aware esp now connection failed
  }

  else if (message == "image captured!")
  {
    /* code */
    binSignal = 9;
    captured = "yes";
    makeGetRequest(IP, mode, captured); // make request to server
  } 

  else if (message == "image captured failed!")
  {
    /* code */
    binSignal = 10;
    captured = "failed";
    makeGetRequest(IP, mode, captured);  // make request to server
  } 
  
  else {
    String IP;
    String mode;
    int splitIndex = message.indexOf('#');
    if (splitIndex != -1) {
      IP = message.substring(0, splitIndex);
      mode = message.substring(splitIndex + 1);
      captured = "no";
      // Serial.println(IP);
      // Serial.println(mode);
      makeGetRequest(IP, mode, captured);
    }
  }

  wireData(); // send data to Arduino Uno
  delay(2000);
}

void makeGetRequest(String IP, String mode, String captured) {
  WiFiClient client;
  
  String url = "/rx.php?id=1&mode="+mode+"&IP="+IP+"&captured="+captured;
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
      // Serial.println(payload);
      Serial.println(payloadGet);
      Serial.println(binSignal);
    }
  }
  client.stop();
}

void espNowFailedToServer() {
  WiFiClient client;
  
  String url = "/esp_failed.php?id=1";
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
    }
  }
}

// Init ESP Now with fallback
void InitESPNow() {
  WiFi.disconnect();
  if (esp_now_init() == ERR_OK) {
    Serial.println("ESPNow Init Success");
  }
  else {
    Serial.println("ESPNow Init Failed");
    // Retry InitESPNow, add a counte and then restart?
    // InitESPNow();
    // or Simply Restart
    ESP.restart();
  }
}

// config AP SSID
void configDeviceAP() {
  const char *SSID = "Slave_1";
  bool result = WiFi.softAP(SSID, "Slave_1_Password", CHANNEL, 0);
  if (!result) {
    Serial.println("AP Config failed.");
  } else {
    Serial.println("AP Config Success. Broadcasting with AP: " + String(SSID));
    Serial.print("AP CHANNEL "); Serial.println(WiFi.channel());
  }
}

void OnDataRecv(uint8_t* mac_addr, uint8_t* data, uint8_t data_len) {
  char macStr[18];
  snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x",
           mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
  Serial.print("Last Packet Recv from: "); Serial.println(macStr);

  // Convert the received data to a null-terminated string
  char dataStr[data_len + 1];
  memcpy(dataStr, data, data_len);
  dataStr[data_len] = '\0';

  Serial.print("Last Packet Recv Data: "); Serial.println(dataStr);
  Serial.println("");
  message = dataStr;
}

// reset WiFi
void WiFiReset() {
  WiFi.persistent(false);
  WiFi.disconnect();
  WiFi.mode(WIFI_OFF);
}

void wireData() {
  Wire.beginTransmission(8); // transmit to device #8
  Wire.write(binSignal);        // sends five bytes
  Wire.endTransmission();    // stop transmitting
}