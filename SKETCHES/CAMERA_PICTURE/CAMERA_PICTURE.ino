
#include "esp_camera.h"
#include "WiFi.h"
#include "WiFiClient.h"
#include "HTTPClient.h"

// Pin definition for CAMERA_MODEL_AI_THINKER
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

//  WiFi credentials
const char* ssid = "spartans";
const char* password = "profession";

void setup() {
  // Initialize serial communications
  Serial.begin(115200);
  // Connect to WiFi network
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
  // Print the IP address
  Serial.println(WiFi.localIP());

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
  
  if(psramFound()){
    config.frame_size = FRAMESIZE_SVGA; // FRAMESIZE_ + QVGA|CIF|VGA|SVGA|XGA|SXGA|UXGA
    config.jpeg_quality = 10;
    config.fb_count = 2;
  } else {
    config.frame_size = FRAMESIZE_SVGA;
    config.jpeg_quality = 10;
    config.fb_count = 2;
  }

  // Init Camera
  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    Serial.printf("Camera init failed with error 0x%x", err);
    return;
  }
  Serial.print("setup done!");
}

void loop() {
  // http.begin("http://192.168.40.138/robocar/stream.php");
  // Take a picture with the ESP32 CAM
  turnOnFlash();
  delay(1000);
  camera_fb_t *fb = esp_camera_fb_get();
  if (!fb) {
    Serial.println("Failed to capture frame");
    turnOffFlash();
    return;
  }
  turnOffFlash();

  // Create an HTTP client and set the destination URL
  HTTPClient http;
  // http.begin("https://robotcar.000webhostapp.com/image.php");
  http.begin("http://192.168.218.138/robocar/image.php");

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
  
  // Wait for a while before taking the next picture
  delay(500);
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

