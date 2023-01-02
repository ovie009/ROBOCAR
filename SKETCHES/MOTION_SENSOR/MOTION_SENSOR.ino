int pirPin = 13;                 // PIR Out pin 
int pirStat = 0;                   // PIR status
void setup() {
 pinMode(pirPin, INPUT);     
 Serial.begin(9600);
}
void loop(){
 pirStat = digitalRead(pirPin); 
 if (pirStat == HIGH) {            // if motion detected
   Serial.println("Motion Detected");
 } 
 else {
   Serial.println("NO Motion Detected");
 }
} 
