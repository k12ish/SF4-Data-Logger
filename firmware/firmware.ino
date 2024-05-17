byte message[9] = {129, 163, 102, 111, 111, 163, 98, 97, 114};

void setup() { Serial.begin(115200); }

void loop() {
  Serial.write(message);
  delay(1000)
}
