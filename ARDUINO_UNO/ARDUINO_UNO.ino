#include <Servo.h>
#include <SoftwareSerial.h>
#include <Wire.h>

//Create software serial object to communicate
SoftwareSerial mySerial(3, 2); //SIM800L Tx & Rx is connected to Arduino #3 & #2
// SoftwareSerial serial(11, 10); // RX, TX with ESP8266

const int SLAVE_ADDRESS = 8; // the slave address

String phoneNumber = "+2348165266847";
String message = "Motion Detected in ROBOBAR capture mode, check image here robotcar.000webhostapp.com/capture.php";

Servo myservo;  // create servo object to control a servo
int servoAngle = 90;

// left hand side motors
int in1 = 4; // In1 of L298N connected to pin 4 of Arduino
int in2 = 5; // In2 of L298N connected to pin 5 of Arduino

// forward left and backward left green wire connected to OUT1 of L298N
// forward left and backward left white wire connected to OUT2 of L298N
int GREEN = in1; 
int WHITE = in2; 

// right hand side motors
int in3 = 6; // In3 of L298N connected to pin 6 of Arduino
int in4 = 7; // In4 of L298N connected to pin 7 of Arduino

// forward right red wire connected to OUT3 of L298N
// forward right black wire connected to OUT4 of L298N
int FR_RED = in3;
int FR_BLACK = in4;

// Backward right red wire connected to OUT4 of L298N
// Backward right black wire connected to OUT3 of L298N
int BR_RED = in4;
int BR_BLACK = in3; 

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
  myservo.write(servoAngle);  // sets the servo position according to the scaled value

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
  else if (dataFromServer == "cam_left") { moveStop(); camLeft(); } 
  else if (dataFromServer == "cam_right") { moveStop(); camRight(); }
  else if (dataFromServer == "reset") { moveStop(); camCenter(); }
  else if (dataFromServer == "captured_image") { 
    moveStop(); sendTextMessage(phoneNumber, message);  
  } else { delay(1000); }

  Serial.println(dataFromServer);  // print the received data to the serial monitor
  // loop delay comes from respective functions
}

// turn on mode led to indicate mode
void indicateMode() {
  if (mode == "CAPTURE")
  {
    /* code */
    digitalWrite(modeLed, 1);
  } else if (mode == "STREAM")
  {
    /* code */
    digitalWrite(modeLed, 0);
  }
  
}

void getData() {
  int delimiterIndex = dataFromESP.indexOf('#');
  dataFromServer = dataFromESP.substring(0, delimiterIndex);
  mode = dataFromESP.substring(delimiterIndex + 1); 
  Serial.print("mode: "); 
  Serial.print(mode); 
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


// function to move vehicle forward
// to move forward, turn all four motor in forward direction
void moveForward() {
  // spin left motors forward
  digitalWrite(in1, HIGH); // green wire
  delay(100);
  digitalWrite(in2, LOW); // white wire
  // right motors spin forward
  digitalWrite(in3, HIGH);
  delay(100);
  digitalWrite(in4, LOW);
  delay(3000);
}

// function to move vehicle backward
// to move backward, turn all four motor in backward direction
void moveBackward() {
  // spin left motors backward
  digitalWrite(in1, LOW); // green wire
  delay(100);
  digitalWrite(in2, HIGH); // white wire
  // right motors spin backward
  digitalWrite(in3, LOW);
  delay(100);
  digitalWrite(in4, HIGH);
  delay(3000);
}

//  function to turn right
// to turn right, move left motors forward and right motors backward
void moveLeft() {
  // spin left motors backward
  digitalWrite(in1, LOW); // green wire
  delay(100);
  digitalWrite(in2, HIGH); // white wire
  // right motors spin forward
  digitalWrite(in3, HIGH);
  delay(100);
  digitalWrite(in4, LOW);
  delay(1000);
}

//  function to turn left
// to turn left, move left motors backward and right motors forward
void moveRight() {
  // spin left motors forward
  digitalWrite(in1, HIGH); // green wire
  delay(100);
  digitalWrite(in2, LOW); // white wire
  // right motors spin backward
  digitalWrite(in3, LOW);
  delay(100);
  digitalWrite(in4, HIGH);
  delay(3000);
}

// function to stop moving
void moveStop() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in4, LOW);
  digitalWrite(in3, LOW);
  delay(1000);
}

// function to turn camera attached on servo to the right
void camRight() {
  // check if servo angle has reached its minimum value
  if (servoAngle > 0) { servoAngle -= 10; }
  else { servoAngle = 0; }
  myservo.write(servoAngle);  
  delay(10);
}

void camLeft() {
  // check if servo angle has reached its maximum value
  if (servoAngle < 180) { servoAngle += 10; }
  else { servoAngle = 180; }
  myservo.write(servoAngle);  
  delay(10);
}

void camCenter() {
  // check if servo angle has reached its maximum value
  servoAngle = 90;
  myservo.write(servoAngle);  
  delay(10);
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