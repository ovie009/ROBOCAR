//----------------------------------------Include the NodeMCU ESP8266 Library
//----------------------------------------see here: https://www.youtube.com/watch?v=8jMr94B8iN0 to add NodeMCU ESP8266 library and board
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>
//----------------------------------------

#define ON_Board_LED 2  //--> Defining an On Board LED (GPIO2 = D4), used for indicators when the process of connecting to a wifi router

#define LED_D8 15 //--> Defines an LED Pin. D8 = GPIO15

//----------------------------------------SSID and Password of your WiFi router.
const char* ssid = "spartans"; //--> Your wifi name or SSID.
const char* password = "profession"; //--> Your wifi password.
//----------------------------------------

//----------------------------------------Web Server address / IPv4
// If using IPv4, press Windows key + R then type cmd, then type ipconfig (If using Windows OS).
const char *host = "http://192.168.2.138/";
//----------------------------------------

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
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
  // Serial.println("");
  // Serial.print("Successfully connected to : ");
  // Serial.println(ssid);
  // Serial.print("IP address: ");
  // Serial.println(WiFi.localIP());
  // Serial.println();
  //----------------------------------------
}

void loop() {
  // put your main code here, to run repeatedly:
  HTTPClient http; //--> Declare object of class HTTPClient
  WiFiClient wificlient; 

  //----------------------------------------Getting Data from MySQL Database
  String GetAddress, LinkGet, getData;
  int id = 1; //--> ID in Database
  GetAddress = "ROBOCAR/RX.php"; 
  LinkGet = host + GetAddress; //--> Make a Specify request destination
  getData = "id=" + String(id);
  // Serial.println("----------------Connect to Server-----------------");
  // Serial.println("Get LED Status from Server or Database");
  // Serial.print("Request Link : ");
  // Serial.println(LinkGet);
  http.begin(wificlient, LinkGet); //--> Specify request destination
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");    //Specify content-type header
  int httpCodeGet = http.POST(getData); //--> Send the request
  String payloadGet = http.getString(); //--> Get the response payload from server
  // Serial.print("Response Code : "); //--> If Response Code = 200 means Successful connection, if -1 means connection failed. For more information see here : https://en.wikipedia.org/wiki/List_of_HTTP_status_codes
  // Serial.println(httpCodeGet); //--> Print HTTP return code
  // Serial.print("Returned data from Server : ");
  // Serial.println(payloadGet); //--> Print request response payload

  // if (payloadGet == "1") {
  //   digitalWrite(LED_D8, HIGH); //--> Turn off Led
  // }
  // if (payloadGet == "0") {
  //   digitalWrite(LED_D8, LOW); //--> Turn off Led
  // }
  //----------------------------------------
  
  Serial.println(payloadGet);
  // Serial.println("----------------Closing Connection----------------");
  http.end(); //--> Close connection
  // Serial.println();
  // Serial.println("Please wait 5 seconds for the next connection.");
  // Serial.println();
  delay(300); //--> GET Data at every 1 seconds
}


// ESP8266 NODEMCU Board Manager https://arduino.esp8266.com/stable/package_esp8266com_index.json search of esp8266 in the borad manager and install

// ESP32 CAM Board Manager https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json search of esp32 in the borad manager and install

// https://dl.espressif/dl/package_esp32_index.json