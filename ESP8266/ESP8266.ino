//************************************************************
// this is a simple example that uses the painlessMesh library
// 
// This example shows how to build a mesh with named nodes
//
//************************************************************
#include "namedMesh.h"

// credentials for the mesh connection
#define   MESH_SSID       "Robocar"
#define   MESH_PASSWORD   "Robocar@password"
#define   MESH_PORT       5555

Scheduler     userScheduler; // to control your personal task
namedMesh  mesh;

String nodeName = "ESP8266"; // Name needs to be unique
String messageReceived = "N/A";
String camIPAddress = "192.168.218.43";


Task sendStream( TASK_SECOND*30, TASK_FOREVER, []() {
  String msg = "Stream";
  String to = "ESP32";
  mesh.sendSingle(to, msg); 
}); // start with a one second interval

Task sendCapture( TASK_SECOND*30, TASK_FOREVER, []() {
  String msg = "Capture";
  String to = "ESP32";
  mesh.sendSingle(to, msg); 
}); // start with a one second interval

void setup() {
  Serial.begin(115200);

  mesh.setDebugMsgTypes(ERROR | DEBUG | CONNECTION);  // set before init() so that you can see startup messages

  mesh.init(MESH_SSID, MESH_PASSWORD, &userScheduler, MESH_PORT);

  mesh.setName(nodeName); // This needs to be an unique name! 

  // on receive message from ESP32_CAM update meassage received variable 
  mesh.onReceive([](String &from, String &msg) {
    // Serial.printf("Received message by name from: %s, %s\n", from.c_str(), msg.c_str());
    messageReceived = msg.c_str();
  });

  mesh.onChangedConnections([]() {
    Serial.printf("Changed connection\n");
  });

}

void loop() {
  userScheduler.addTask(sendStream);
  sendStream.enable();
  // it will run the user scheduler as well
  mesh.update();
  Serial.println(messageReceived);
  delay(1000);
}
