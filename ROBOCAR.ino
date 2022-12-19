//----------------------------------------Include the NodeMCU ESP8266 Library
//----------------------------------------see here: https://www.youtube.com/watch?v=8jMr94B8iN0 to add NodeMCU ESP8266 library and board
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>
#include <Wire.h>
//----------------------------------------

#define ON_Board_LED 2  //--> Defining an On Board LED (GPIO2 = D4), used for indicators when the process of connecting to a wifi router

#define LED_D8 15 //--> Defines an LED Pin. D8 = GPIO15

//----------------------------------------SSID and Password of your WiFi router.
const char* ssid = "spartans"; //--> Your wifi name or SSID.
const char* password = "profession"; //--> Your wifi password.
//----------------------------------------

//----------------------------------------Web Server address 
const char *host = "robotcar.000webhostapp.com";
//----------------------------------------
byte binSignal = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Wire.begin(D2, D3); // join I2C bus (address optional for master)
  delay(500);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password); //--> Connect to your WiFi router
  // Serial.println("");
    
  pinMode(ON_Board_LED,OUTPUT); //--> On Board LED port Direction output
  digitalWrite(ON_Board_LED, HIGH); //--> Turn off Led On Board

  pinMode(LED_D8,OUTPUT); //--> LED port Direction output
  digitalWrite(LED_D8, LOW); //--> Turn off Led

  //----------------------------------------Wait for connection
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    //----------------------------------------Make the On Board Flashing LED on the process of connecting to the wifi router.
    digitalWrite(ON_Board_LED, LOW);
    delay(250);
    digitalWrite(ON_Board_LED, HIGH);
    delay(250);
    //----------------------------------------
  }
  //----------------------------------------
  digitalWrite(ON_Board_LED, HIGH); //--> Turn off the On Board LED when it is connected to the wifi router.
  //----------------------------------------If successfully connected to the wifi router, the IP Address that will be visited is displayed in the serial monitor

}

void loop() {
  // put your main code here, to run repeatedly:
  HTTPClient http; //--> Declare object of class HTTPClient
  WiFiClient wificlient; 

  //----------------------------------------Getting Data from MySQL Database
  String GetAddress, LinkGet, getData;
  int id = 1; //--> ID in Database
  GetAddress = "/tx.php"; 
  LinkGet = host + GetAddress; //--> Make a Specify request destination
  getData = "id=" + String(id);
  http.begin(wificlient, LinkGet); //--> Specify request destination
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");    //Specify content-type header
  int httpCodeGet = http.POST(getData); //--> Send the request
  String payloadGet = http.getString(); //--> Get the response payload from server
  
  Serial.println(payloadGet);
  // Serial.println("----------------Closing Connection----------------");

  if (payloadGet == "car_forward")
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
  else
  {
    /* code */
    binSignal = 0;
  }

  Serial.print("Payload: ");
  Serial.println(payloadGet);
  Serial.print("Binary Signal: ");
  Serial.println(binSignal);
  
  Wire.beginTransmission(8); // transmit to device #8
  Wire.write(binSignal);        // sends five bytes
  Wire.endTransmission();    // stop transmitting
  delay(100);
  
  http.end(); //--> Close connection
  delay(2000); //--> GET Data at every 1 seconds
}

// ESP8266 NODEMCU Board Manager https://arduino.esp8266.com/stable/package_esp8266com_index.json search of esp8266 in the borad manager and install

// ESP32 CAM Board Manager https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json search of esp32 in the borad manager and install

// https://dl.espressif/dl/package_esp32_index.json
