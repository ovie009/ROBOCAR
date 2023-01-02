#include "esp_camera.h"

// Set the GPIO pin number for the flash
#define FLASH_GPIO_NUM (gpio_num_t)4
// Set the GPIO pin number for the motion sensor data
#define MOTION_SENSOR (gpio_num_t)7
// Set the GPIO pin number for the mode switch
#define MODE_SWITCH (gpio_num_t)8

void setup() {
  // Initialize the serial monitor
  Serial.begin(115200);

}

void loop() {
  gpio_set_direction(MODE_SWITCH, GPIO_MODE_INPUT);
  gpio_set_direction(MOTION_SENSOR, GPIO_MODE_INPUT);
  // Read the value of pin MODE_SWITCH and pin MOTION_SENSOR
  int modeVal = gpio_get_level(MODE_SWITCH);
  int motionVal = gpio_get_level(MOTION_SENSOR);

  // Print the values to the serial monitor
  Serial.print("Mode Pin: ");
  Serial.println(modeVal);
  Serial.print("Motion Detected: ");
  Serial.println(motionVal);

  // Delay for 1 second
  delay(1000);
}
