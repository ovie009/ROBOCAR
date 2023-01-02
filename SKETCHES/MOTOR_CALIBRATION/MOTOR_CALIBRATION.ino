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

void setup() {
  // put your setup code here, to run once:
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
}

void loop() {
  // to move forward set GREEN HIGH and WHITE LOW
  moveForward();
  delay(5000);
  moveBackward();
  delay(5000);
  turnRight();
  delay(5000);
  turnLeft();
  delay(5000);
}

// block of code to move vehicle forward
// to move forward, turn all four motor in forward direction
void moveForward() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in4, LOW);
  digitalWrite(in3, HIGH);
  delay(100);
}

// block of code to move vehicle backward
// to move backward, turn all four motor in backward direction
void moveBackward() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in4, HIGH);
  digitalWrite(in3, LOW);
  delay(100);
}

//  block of code to turn right
// to turn right, move left motors forward and right motors backward
void turnRight() {
  // moving left motors forward
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  // moving right motors backward
  digitalWrite(in4, HIGH);
  digitalWrite(in3, LOW);
  delay(100);
}

//  block of code to turn left
// to turn left, move left motors backward and right motors forward
void turnLeft() {
  // moving left motors backward
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  // moving right motors forward
  digitalWrite(in4, LOW);
  digitalWrite(in3, HIGH);
  delay(100);
}