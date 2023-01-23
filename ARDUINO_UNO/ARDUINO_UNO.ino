#include <Servo.h>
#include <SoftwareSerial.h>
#include <Wire.h>

//Create software serial object to communicate
SoftwareSerial mySerial(3, 2); //SIM800L Tx & Rx is connected to Arduino #3 & #2
// SoftwareSerial serial(11, 10); // RX, TX with ESP8266

const int SLAVE_ADDRESS = 8; // the slave address

String phoneNumber = "+2348122249247";
String message = "Motion Detected in ROBOBAR capture mode, check image here http://robotcar.000webhostapp.com/capture.php";

Servo myservo;  // create servo object to control a servo
int servoAngle;

// left hand side motors
// forward left (FR) and backward left (BR) green wire connected to OUT1 of L298N
// forward left (FR) and backward left (BR) white wire connected to OUT2 of L298N
int in1 = 4; // In1 of L298N connected to pin 4 of Arduino
int in2 = 5; // In2 of L298N connected to pin 5 of Arduino


// right hand side motors
// forward right (FR) and backward right (BR) red wire connected to OUT3 of L298N
// forward right (FR) and backward right (BR) black wire connected to OUT4 of L298N
int in3 = 10; // In3 of L298N connected to pin 10 of Arduino
int in4 = 11; // In4 of L298N connected to pin 11 of Arduino

int FR_RED = in3;
int FR_BLACK = in4;

String mode; // mode variable
int modeLed = 13; // mode LED indicator

String dataFromServer;
String dataFromESP;

void setup() {
  Serial.begin(115200); // start serial for output

  pinMode(modeLed, OUTPUT); // declare pinmode for mode led indicator

  // pins for motor
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  myservo.attach(9);  // attaches the servo on pin 10 to the servo object

  //Begin serial communication with Arduino and ESP8266
  // serial.begin(115200);

  Wire.begin(SLAVE_ADDRESS); // join the I2C bus as a slave
  Wire.onReceive(receiveData); // register the receive callback

  //Begin serial communication with Arduino and SIM800L
  mySerial.begin(9600);
}

void loop() {
  // dataFromESP = receiveString();
  getData(); // get dataFromServer and Mode
  indicateMode();
  // use dataFromServer
  if (dataFromServer == "N/A") { moveStop(); }
  else if (dataFromServer == "car_forward") { moveForward(); }
  else if (dataFromServer == "car_backward") { moveBackward(); }
  else if (dataFromServer == "car_left") { moveLeft(); }
  else if (dataFromServer == "car_right") { moveRight(); }
  else if (dataFromServer == "cam_left") { moveStop(); moveCam(); } 
  else if (dataFromServer == "cam_right") { moveStop(); moveCam(); }
  else if (dataFromServer == "reset") { moveStop(); moveCam(); }
  else if (dataFromServer == "captured_image") { 
    moveStop(); sendTextMessage(phoneNumber, message);  
  } else { delay(1000); }

  Serial.println(dataFromServer);  // print the received data to the serial monitor
  // loop delay comes from respective functions
}

// turn on mode led to indicate mode
void indicateMode() {
  mode.toLowerCase();
  Serial.print("mode length: ");
  Serial.println(mode.length());
  if (mode.length() == 7) {
    /* code */
    Serial.println("in capture");
    digitalWrite(modeLed, 1);
  } else if (mode.length() == 6) {
    /* code */
    Serial.println("in stream");
    digitalWrite(modeLed, 0);
  }
  
}

void getData() {
  int delimiter1 = dataFromESP.indexOf('#');
  int delimiter2 = dataFromESP.indexOf('@');
  dataFromServer = dataFromESP.substring(0, delimiter1);
  mode = dataFromESP.substring(delimiter1 + 1, delimiter2); 
  servoAngle = dataFromESP.substring(delimiter2 + 1).toInt(); 
  Serial.print("mode: "); 
  Serial.println(mode); 
  Serial.print("servo angle: "); 
  Serial.println(servoAngle); 
  indicateMode(); // turn on mode led
}


// called when data is received from the master
void receiveData(int numBytes) {
  String data = "";
  while (Wire.available()) { // loop through all received bytes
    data += (char)Wire.read(); // add the byte to the string
  }
  Serial.println("Received: " + data); // print the received data
  dataFromESP = data;
}


// function to move vehicle backward
// to move backward, turn all four motor in backward direction
void moveForward() {
  // spin left motors backward
  digitalWrite(in1, HIGH); // green wire
  digitalWrite(in2, LOW); // white wire
  // right motors spin backward
  digitalWrite(in4, HIGH);
  digitalWrite(in3, LOW);
  delay(1000);
}

// function to move vehicle forward
// to move forward, turn all four motor in forward direction
void moveBackward() {
  // spin left motors forward
  digitalWrite(in2, HIGH); // white wire
  digitalWrite(in1, LOW); // green wire
  // right motors spin forward
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  delay(1000);
}

//  function to turn right
// to turn right, move left motors forward and right motors backward
void moveLeft() {
  // spin left motors backward
  digitalWrite(in2, LOW); // white wire
  digitalWrite(in1, LOW); // green wire
  // right motors spin forward
  digitalWrite(in4, HIGH);
  digitalWrite(in3, LOW);
  delay(500);
}

//  function to turn left
// to turn left, move left motors backward and right motors forward
void moveRight() {
  // spin left motors forward
  digitalWrite(in1, HIGH); // green wire
  digitalWrite(in2, LOW); // white wire
  // right motors spin backward
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  delay(500);
}

// function to stop moving
void moveStop() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in4, LOW);
  digitalWrite(in3, LOW);
  delay(1000);
}

void moveCam() {
  myservo.write(servoAngle);  // set servo angle
  delay(100);
}

// function to send text message after image capture
void sendTextMessage(String phoneNumber, String message) {
   // Set the phone number for the message
  mySerial.println("AT+CMGS=\"" + phoneNumber + "\"");
  delay(1000);

  // Send the message
  mySerial.println(message);
  delay(1000);

  // Send the End of Transmission character to send the message
  mySerial.write(26);
  delay(3000);

  dataFromServer = "N/A";
}