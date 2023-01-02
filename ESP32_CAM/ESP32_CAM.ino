#include "esp_camera.h"
#include "WiFi.h"
#include "WiFiClient.h"
#include "HTTPClient.h"
#include "esp_now.h"
#include "esp_wifi.h" // only for esp_wifi_set_channel()

// WiFi Credentials
const char* ssid = "spartans";
const char* password = "profession";

// ESP NOW Parameters
// Global copy of slave
esp_now_peer_info_t slave;
#define CHANNEL 1
#define PRINTSCANRESULTS 0
#define DELETEBEFOREPAIR 0

// camera configuration pins
#define PWDN_GPIO_NUM     32
#define RESET_GPIO_NUM    -1
#define XCLK_GPIO_NUM      0
#define SIOD_GPIO_NUM     26
#define SIOC_GPIO_NUM     27

#define Y9_GPIO_NUM       35
#define Y8_GPIO_NUM       34
#define Y7_GPIO_NUM       39
#define Y6_GPIO_NUM       36
#define Y5_GPIO_NUM       21
#define Y4_GPIO_NUM       19
#define Y3_GPIO_NUM       18
#define Y2_GPIO_NUM        5
#define VSYNC_GPIO_NUM    25
#define HREF_GPIO_NUM     23
#define PCLK_GPIO_NUM     22

// Set the GPIO pin number for the flash
#define FLASH_GPIO_NUM (gpio_num_t)4
#define MODE_SWITCH (gpio_num_t)13 // mode switch on pin 13 of ESP32 CAM
#define MOTION_SENSOR (gpio_num_t)12 // motion sensor connected on pin 12

WiFiServer server(80);
bool connected = false;
WiFiClient live_client;

// index hmtl of camera server
String index_html = "<meta charset=\"utf-8\"/>\n" \
  "<style>\n" \
  "#content {\n" \
  "display: flex;\n" \
  "flex-direction: column;\n" \
  "justify-content: center;\n" \
  "align-items: center;\n" \
  "text-align: center;\n" \
  "min-height: 100vh;}\n" \
  "</style>\n" \
"<body bgcolor=\"#000000\"><div id=\"content\"><h2 style=\"color:#ffffff\">ROBOCAR LIVE</h2><img src=\"video\"></div></body>";

// variable to switch between streaming mode and capture mode
String mode; // possible values "STREAM"; "CAPTURE";
String IP; // ip address of the cam server

bool motionDetected; // varaible to store motion detected state

void configCamera(){
  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;
  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;
  config.pin_sscb_sda = SIOD_GPIO_NUM;
  config.pin_sscb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;
  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_JPEG;

  // FRAMESIZE_QQVGA: 160x120 pixels
  // FRAMESIZE_HQVGA: 240x176 pixels
  // FRAMESIZE_QVGA: 320x240 pixels
  // FRAMESIZE_CIF: 400x296 pixels
  // FRAMESIZE_VGA: 640x480 pixels
  // FRAMESIZE_SVGA: 800x600 pixels
  // FRAMESIZE_XGA: 1024x768 pixels
  // FRAMESIZE_SXGA: 1280x1024 pixels
  // FRAMESIZE_UXGA: 1600x1200 pixels
  config.frame_size = FRAMESIZE_VGA;
  config.jpeg_quality = 5;
  // The config.jpeg_quality field determines the quality of the images captured
  // It can be set to a value between 0 and 63, the higher the  value the lower the quality
  config.fb_count = 2;

  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    Serial.printf("Camera init failed with error 0x%x", err);
    return;
  }
}

//continue sending camera frame
void liveCam(WiFiClient &client){
  
  camera_fb_t * fb = esp_camera_fb_get();
  if (!fb) {
      Serial.println("Frame buffer could not be acquired");
      return;
  }
  client.print("--frame\n");
  client.print("Content-Type: image/jpeg\n\n");
  client.flush();
  client.write(fb->buf, fb->len);
  client.flush();
  client.print("\n");
  esp_camera_fb_return(fb);
}

void setup() {
  Serial.begin(115200);

  // Set device in STA mode to begin with
  WiFi.mode(WIFI_STA);
  esp_wifi_set_channel(CHANNEL, WIFI_SECOND_CHAN_NONE);
  // Init ESPNow with a fallback logic
  InitESPNow();
  // Once ESPNow is successfully Init, we will register for Send CB to
  // get the status of Trasnmitted packet
  esp_now_register_send_cb(OnDataSent);


  // connect ti WiFi
  WiFi.begin(ssid, password);
  Serial.println("");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  IP = WiFi.localIP().toString();
  Serial.println("IP address: " + IP);
  index_html.replace("server_ip", IP);
  server.begin();
  configCamera();

 // set mode and motion sesor pins 
  gpio_set_direction(MODE_SWITCH, GPIO_MODE_INPUT);
  gpio_set_direction(MOTION_SENSOR, GPIO_MODE_INPUT);
  checkMode();
  detectMotion();
  sendIP(IP+"#"+mode);
}
    
void http_resp(){
  WiFiClient client = server.available();                           
  if (client.connected()) {     
      String req = "";
      while(client.available()){
        req += (char)client.read();
      }
      Serial.println("request " + req);
      int addr_start = req.indexOf("GET") + strlen("GET");
      int addr_end = req.indexOf("HTTP", addr_start);
      if (addr_start == -1 || addr_end == -1) {
          Serial.println("Invalid request " + req);
          return;
      }
      req = req.substring(addr_start, addr_end);
      req.trim();
      Serial.println("Request: " + req);
      client.flush();
  
      String s;
      if (req == "/")
      {
          s = "HTTP/1.1 200 OK\n";
          s += "Content-Type: text/html\n\n";
          s += index_html;
          s += "\n";
          client.print(s);
          client.stop();
      }
      else if (req == "/video")
      {
          live_client = client;
          live_client.print("HTTP/1.1 200 OK\n");
          live_client.print("Content-Type: multipart/x-mixed-replace; boundary=frame\n\n");
          live_client.flush();
          connected = true;
      }
      else
      {
          s = "HTTP/1.1 404 Not Found\n\n";
          client.print(s);
          client.stop();
      }
    }       
}

void loop() {
  checkMode();
  detectMotion();
  // sendIP(IP+"#"+mode);


  Serial.print("mode: ");
  Serial.println(mode);

  if (mode == "STREAM")
  {    
    http_resp();
    if(connected == true){
      // turnOnFlash();
      liveCam(live_client);
    }
    
  }
  else if (mode == "CAPTURE")
  {
    if (motionDetected == true)
    {
      // capture image and send to webserver
      Serial.print("motion detected");
      captureImage();
      // reset motion detetcted state
      motionDetected = false;
    }
  }
  delay(1000);
}

void turnOnFlash() {
  // Set the flash GPIO pin as an output
  gpio_set_direction(FLASH_GPIO_NUM, GPIO_MODE_OUTPUT);
  // Turn on the flash
  gpio_set_level(FLASH_GPIO_NUM, 1);
}

void turnOffFlash() {
  // Turn off the flash
  gpio_set_level(FLASH_GPIO_NUM, 0);
}

void captureImage() {
  turnOnFlash();
  delay(1000);
  camera_fb_t *fb = esp_camera_fb_get();
  if (!fb) {
    Serial.println("Failed to capture frame");
    turnOffFlash();
    return;
  }
  delay(500);
  turnOffFlash();

  // Create an HTTP client and set the destination URL
  HTTPClient http;
  // http.begin("https://robotcar.000webhostapp.com/image.php");
  http.begin("http://192.168.95.138/robocar/image.php");

  // Set the content type to image/jpeg
  http.addHeader("Content-Type", "image/jpeg");

  // Send the request and check the response
  int httpCode = http.POST(fb->buf, fb->len);
  // Serial.println(fb->len);
  if (httpCode > 0) {
    // HTTP header has been send and Server response header has been handled
    Serial.printf("[HTTP] POST... code: %d\n", httpCode);
    // Read the response from the server
    String response = http.getString();
    Serial.println(response);
  } else {
    Serial.printf("[HTTP] POST... failed, error: %s\n", http.errorToString(httpCode).c_str());
  }

  // Release the frame buffer
  esp_camera_fb_return(fb);

  // Close the HTTP connection
  http.end();
}

void checkMode() {
  if (gpio_get_level(MODE_SWITCH) == 1 )
  {
    // if switch is on set mode to streaming Mode
    mode = "STREAM";
  }
  else if (gpio_get_level(MODE_SWITCH) == 0 )
  {
    // if switch is on set mode to capture Mode
    mode = "STREAM";
    // mode = "CAPTURE";
  }
}

void detectMotion() {
  if (gpio_get_level(MOTION_SENSOR) == 1 )
  {
    // if motion is detected update motion detected state
    motionDetected = true;
  }
  else if (gpio_get_level(MOTION_SENSOR) == 0 )
  {
    // if motion is detected update motion detected state
    motionDetected = false;
  }
}

// ESP NOW FUNCTIONS // ESP NOW FUNCTIONS // ESP NOW FUNCTIONS
// ESP NOW FUNCTIONS // ESP NOW FUNCTIONS // ESP NOW FUNCTIONS
// ESP NOW FUNCTIONS // ESP NOW FUNCTIONS // ESP NOW FUNCTIONS

// Init ESP Now with fallback
void InitESPNow() {
  // WiFi.disconnect();
  if (esp_now_init() == ESP_OK) {
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

// Scan for slaves in AP mode
void ScanForSlave() {
  int16_t scanResults = WiFi.scanNetworks(false, false, false, 300, CHANNEL); // Scan only on one channel
  // reset on each scan
  bool slaveFound = 0;
  memset(&slave, 0, sizeof(slave));

  Serial.println("");
  if (scanResults == 0) {
    Serial.println("No WiFi devices in AP Mode found");
  } else {
    Serial.print("Found "); Serial.print(scanResults); Serial.println(" devices ");
    for (int i = 0; i < scanResults; ++i) {
      // Print SSID and RSSI for each device found
      String SSID = WiFi.SSID(i);
      int32_t RSSI = WiFi.RSSI(i);
      String BSSIDstr = WiFi.BSSIDstr(i);

      if (PRINTSCANRESULTS) {
        Serial.print(i + 1);
        Serial.print(": ");
        Serial.print(SSID);
        Serial.print(" (");
        Serial.print(RSSI);
        Serial.print(")");
        Serial.println("");
      }
      delay(10);
      // Check if the current device starts with `Slave`
      if (SSID.indexOf("Slave") == 0) {
        // SSID of interest
        Serial.println("Found a Slave.");
        Serial.print(i + 1); Serial.print(": "); Serial.print(SSID); Serial.print(" ["); Serial.print(BSSIDstr); Serial.print("]"); Serial.print(" ("); Serial.print(RSSI); Serial.print(")"); Serial.println("");
        // Get BSSID => Mac Address of the Slave
        int mac[6];
        if ( 6 == sscanf(BSSIDstr.c_str(), "%x:%x:%x:%x:%x:%x",  &mac[0], &mac[1], &mac[2], &mac[3], &mac[4], &mac[5] ) ) {
          for (int ii = 0; ii < 6; ++ii ) {
            slave.peer_addr[ii] = (uint8_t) mac[ii];
          }
        }

        slave.channel = CHANNEL; // pick a channel
        slave.encrypt = 0; // no encryption

        slaveFound = 1;
        // we are planning to have only one slave in this example;
        // Hence, break after we find one, to be a bit efficient
        break;
      }
    }
  }

  if (slaveFound) {
    Serial.println("Slave Found, processing..");
  } else {
    Serial.println("Slave Not Found, trying again.");
  }

  // clean up ram
  WiFi.scanDelete();
}

// Check if the slave is already paired with the master.
// If not, pair the slave with master
bool manageSlave() {
  if (slave.channel == CHANNEL) {
    if (DELETEBEFOREPAIR) {
      deletePeer();
    }

    Serial.print("Slave Status: ");
    // check if the peer exists
    bool exists = esp_now_is_peer_exist(slave.peer_addr);
    if ( exists) {
      // Slave already paired.
      Serial.println("Already Paired");
      return true;
    } else {
      // Slave not paired, attempt pair
      esp_err_t addStatus = esp_now_add_peer(&slave);
      if (addStatus == ESP_OK) {
        // Pair success
        Serial.println("Pair success");
        return true;
      } else if (addStatus == ESP_ERR_ESPNOW_NOT_INIT) {
        // How did we get so far!!
        Serial.println("ESPNOW Not Init");
        return false;
      } else if (addStatus == ESP_ERR_ESPNOW_ARG) {
        Serial.println("Invalid Argument");
        return false;
      } else if (addStatus == ESP_ERR_ESPNOW_FULL) {
        Serial.println("Peer list full");
        return false;
      } else if (addStatus == ESP_ERR_ESPNOW_NO_MEM) {
        Serial.println("Out of memory");
        return false;
      } else if (addStatus == ESP_ERR_ESPNOW_EXIST) {
        Serial.println("Peer Exists");
        return true;
      } else {
        Serial.println("Not sure what happened");
        return false;
      }
    }
  } else {
    // No slave found to process
    Serial.println("No Slave found to process");
    return false;
  }
}

void deletePeer() {
  esp_err_t delStatus = esp_now_del_peer(slave.peer_addr);
  Serial.print("Slave Delete Status: ");
  if (delStatus == ESP_OK) {
    // Delete success
    Serial.println("Success");
  } else if (delStatus == ESP_ERR_ESPNOW_NOT_INIT) {
    // How did we get so far!!
    Serial.println("ESPNOW Not Init");
  } else if (delStatus == ESP_ERR_ESPNOW_ARG) {
    Serial.println("Invalid Argument");
  } else if (delStatus == ESP_ERR_ESPNOW_NOT_FOUND) {
    Serial.println("Peer not found.");
  } else {
    Serial.println("Not sure what happened");
  }
}

void sendData(String data) {
  // Check if the slave is still connected
  bool exists = esp_now_is_peer_exist(slave.peer_addr);
  if (exists) {
    // Send the data
    esp_err_t result = esp_now_send(slave.peer_addr, (uint8_t*) data.c_str(), data.length()+1);
    if (result == ESP_OK) {
      Serial.println("Data sent successfully");
    } else {
      Serial.println("Error sending data");
    }
  } else {
    // If the slave is not connected, re-pair
    manageSlave();
  }
}

// callback when data is sent from Master to Slave
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("Rolling Back Settings");
  char macStr[18];
  snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x",
           mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
  // Serial.print("Last Packet Sent to: "); Serial.println(macStr);
  Serial.print("Last Packet Send Status: "); Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");

  // Reset WiFi mode
  // WiFi.disconnect(true);
  // WiFi.mode(WIFI_OFF);
  // // Reset ESP-NOW
  // esp_now_deinit();

  // WiFiServer server(80);

  // WiFi.begin(ssid, password);
  // Serial.println("");
  // while (WiFi.status() != WL_CONNECTED) {
  //   delay(500);
  //   Serial.print(".");
  // }
  // Serial.println("");
  // IP = WiFi.localIP().toString();
  // Serial.println("IP address: " + IP);
  // index_html.replace("server_ip", IP);
  // server.begin();
}

void sendIP(String IP) {
  // In the loop we scan for slave
  ScanForSlave();
  // If Slave is found, it would be populate in `slave` variable
  // We will check if `slave` is defined and then we proceed further
  if (slave.channel == CHANNEL) { // check if slave channel is defined
    // `slave` is defined
    // Add slave as peer if it has not been added already
    bool isPaired = manageSlave();
    if (isPaired) {
      // pair success or already paired
      // Send data to device
      sendData(IP);
    } else {
      // slave pair failed
      Serial.println("Slave pair failed!");
    }
  }
  else {
    // No slave found to process
      Serial.println("No SLave found");
  }
}