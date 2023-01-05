void setup() {
    pinMode(D5, INPUT);
    pinMode(D6, INPUT);
    pinMode(D7, INPUT);
    pinMode(D8, INPUT);
    Serial.begin(115200);
}

void loop() {
    Serial,print("D5: ");
    Serial,println(digitalRead(D5));
    Serial,print("D6: ");
    Serial,println(digitalRead(D6));
    Serial,print("D7: ");
    Serial,println(digitalRead(D7));
    Serial,print("D8: ");
    Serial,println(digitalRead(D8));
    delay(2000);
}