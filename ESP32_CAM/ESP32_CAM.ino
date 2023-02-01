// ESP32 ESP NOW Master  Code
#include "esp_camera.h"
#include "WiFi.h"
#include "WiFiClient.h"
#include "HTTPClient.h"

// WiFi Credentials
const char* ssid = "Robotcar";
const char* password = "Robotcar";

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
String prevMode; // variable to store previous mode
String IP; // ip address of the cam server
String settings; // settings variable

int flash;
int motionDetected; // varaible to store motion detected state

String tolerance; // the tolerance value to detect motion could
// possible 3 values LOW = 5, AVERAGE = 10, HIGH = 15,
int motionCount = 0;

void setup() {
  Serial.begin(115200); // begin serial communication, for debugging
  // connect to WiFi
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
  server.begin(); // begin streaming server on the ESP IP Address
  configCamera(); // configure the camera settings

}

void loop() {

  // Serial.println(requestSettings());

  settings = requestSettings();
  processSettings(settings);

  Serial.print("mode: ");
  Serial.println(mode);
  Serial.print("flash: ");
  Serial.println(flash);
  Serial.print("motion: ");
  Serial.println(motionDetected);
  Serial.print("tolerance: ");
  Serial.println(tolerance);

  if (mode == "STREAM")
  {    
    http_resp();
    if(connected == true){
      if (flash == 1) { turnOnFlash(); } 
      else { turnOffFlash(); }
      liveCam(live_client);
    }
    
  }

  else if (mode == "CAPTURE")
  {
    if (motionDetected == 1)
    {
      motionCount += 1;
      Serial.print("motion count: ");
      Serial.println(motionCount); 
      motionDetected = 0;
      if (motionCount == 5 && tolerance == "LOW" || motionCount == 10 && tolerance == "AVERAGE" || motionCount == 15 && tolerance == "HIGH") {
        String response;
        response = captureImage();
        Serial.println(response);
        motionCount = 0;
      }
    }
  }
  delay(1000);
}

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
  config.frame_size = FRAMESIZE_SVGA;
  config.jpeg_quality = 10;
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

String captureImage() {
  turnOnFlash();
  delay(1000);
  camera_fb_t *fb = esp_camera_fb_get();
  if (!fb) {
    Serial.println("Failed to capture frame");
    turnOffFlash();
    return "camera failed!";
  }
  delay(500);
  turnOffFlash();
  String response;
  // Create an HTTP client and set the destination URL
  HTTPClient http;
  http.begin("http://robocar-stream.000webhostapp.com/image.php");
  // http.begin("http://192.168.235.138/robocar/image.php");

  // Set the content type to image/jpeg
  http.addHeader("Content-Type", "image/jpeg");

  // Send the request and check the response
  int httpCode = http.POST(fb->buf, fb->len);
  // Serial.println(fb->len);
  if (httpCode > 0) {
    // HTTP header has been send and Server response header has been handled
    Serial.printf("[HTTP] POST... code: %d\n", httpCode);
    // Read the response from the server
    response = http.getString();
    Serial.println(response);
    // return response;
  } else {
    Serial.printf("[HTTP] POST... failed, error: %s\n", http.errorToString(httpCode).c_str());
    response = http.errorToString(httpCode).c_str();
  }

  // Release the frame buffer
  esp_camera_fb_return(fb);

  // Close the HTTP connection
  http.end();

  return response;
}

String requestSettings() {

  String payload; // response from the server
  // Create the HTTP client
  HTTPClient http;

  // Set the URL for the request
  String url = "http://robocar-stream.000webhostapp.com/settings.php?IP="+IP;
  // String url = "http://192.168.235.138/robocar/settings.php?IP="+IP;

  // Send the GET request
  http.begin(url);
  int httpCode = http.GET();

  // Check the response status code
  if (httpCode > 0) {
    // Get the response payload
    payload = http.getString();
    Serial.println(payload);
  } else {
    Serial.println("Error: " + http.errorToString(httpCode));
    payload = http.errorToString(httpCode);
  }

  // Close the connection
  http.end();
  return payload;
}

void processSettings(String settingsData) {
  int firstDelimiterIndex = settingsData.indexOf('#');
  int secondDelimiterIndex = settingsData.indexOf('&');
  int thirdDelimiterIndex = settingsData.indexOf('@');


  mode = settingsData.substring(0, firstDelimiterIndex);
  flash = settingsData.substring(firstDelimiterIndex + 1, secondDelimiterIndex).toInt();
  motionDetected = settingsData.substring(secondDelimiterIndex + 1, thirdDelimiterIndex).toInt();
  tolerance = settingsData.substring(thirdDelimiterIndex + 1);
}