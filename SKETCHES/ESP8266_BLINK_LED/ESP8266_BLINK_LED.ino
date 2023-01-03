void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(16, INPUT);
  pinMode(5, INPUT);
  pinMode(2, INPUT);
  pinMode(14, INPUT);
  pinMode(13, INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("PIN 0: ");
  Serial.println(digitalRead(16));
  Serial.print("PIN 1: ");
  Serial.println(digitalRead(5));
  Serial.print("PIN 4: ");
  Serial.println(digitalRead(2));
  Serial.print("PIN 5: ");
  Serial.println(digitalRead(14));
  Serial.print("PIN 7: ");
  Serial.println(digitalRead(13));
  Serial.println("");
  delay(1000);
}
