#include "esp_camera.h"
#include "esp_http_server.h"
#include "esp_https_ota.h"
#include "esp_timer.h"
#include "esp_log.h"
#include "esp_system.h"
#include "esp_event_loop.h"
#include "nvs_flash.h"
#include "driver/gpio.h"

#include "lwip/err.h"
#include "lwip/sys.h"

#include "Arduino.h"
#include "WiFi.h"
#include <HTTPClient.h>

#define CAMERA_MODEL_AI_THINKER
#include "camera_pins.h"

// Replace with your own WiFi SSID and password
const char* ssid = "spartans";
const char* password = "profession";

// Declare frame buffer variables
camera_fb_t *fb;
uint8_t *fb_data;
size_t fb_len;

void setup() {
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }

  // Initialize camera
  esp_err_t err = camera_init();
  if (err != ESP_OK) {
    Serial.println("Error initializing camera");
    return;
  }
}

void loop() {
  // Capture image from camera
  fb = esp_camera_fb_get();
  if (!fb) {
    Serial.println("Error getting frame buffer from camera");
    return;
  }

  // Set up HTTP client
  HTTPClient http;

  // Set URL for HTTP POST request
  http.begin("https://robotcar.000webhostapp.com/stream");

  // Set content type for multipart/form-data POST request
  http.addHeader("Content-Type", "multipart/form-data");

  // Add image data to POST request
  fb_data = fb->buf;
  fb_len = fb->len;
  http.addFile("image", "image.jpg", "image/jpeg", fb_data, fb_len);

  // Send POST request and get response
  int httpCode = http.POST();

  // Check response code
  if (httpCode > 0) {
    Serial.printf("HTTP POST request successful. Response code: %d\n", httpCode);
  } else {
    Serial.printf("Error sending HTTP POST request. Error code: %d\n", httpCode);
  }

  // End HTTP client
  http.end();

  // Free frame buffer
  esp_camera_fb_return(fb);
}
