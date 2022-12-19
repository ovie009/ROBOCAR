#include <WiFi.h>
#include <WebServer.h>
#include <esp_camera.h>
#include <esp_timer.h>
#include <esp_http_server.h>

const char* ssid = "your_ssid";
const char* password = "your_password";

WebServer server(80);

void setup() {
  Serial.begin(115200);
  delay(10);

  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  // Start the server
  server.begin();
  Serial.println("Server started");

  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
}

void loop() {
  // Handle client requests
  server.handleClient();
}

// HTTP request handler for the video stream
void handleVideoStream() {
  // Set the content type to "multipart/x-mixed-replace" for a streaming response
  server.sendHeader("Content-Type", "multipart/x-mixed-replace; boundary=frame");
  server.send(200);

  // Initialize the camera
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
  config.frame_size = FRAMESIZE_UXGA;
  config.jpeg_quality = 12;
  config.fb_count = 1;

  // Initialize the camera
  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
  Serial.println("Camera init failed");
  return;
  }

  // Start streaming the video
  while (true) {
  // Capture a frame from the camera
  camera_fb_t *fb = esp_camera_fb_get();
  if (!fb) {
  Serial.println("Failed to capture frame");
  return;
  }
  // Send the frame to the client
  server.sendContent("--frame\r\n");
  server.sendContent("Content-Type: image/jpeg\r\n");
  server.sendContent("Content-Length: ");
  server.sendContent(fb->len);
  server.sendContent("\r\n\r\n");
  server.sendContent((const char*)fb->buf, fb->len);
  server.sendContent("\r\n");

  // Free the frame buffer
  esp_camera_fb_return(fb);

  // Delay to maintain the desired frame rate
  delay(1000 / 30);
  }
  }

  // Set up the HTTP route for the video stream
  void setupVideoStreamRoute() {
  server.on("/stream", HTTP_GET, {
  handleVideoStream();
  });
  }  

