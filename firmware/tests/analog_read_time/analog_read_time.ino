int value;
int time;
int time2;
int delta;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(A0, INPUT);
}

void loop() {
  // Time the read of an analog pin and print both the retrieved value and the time taken to the serial port. Test show and average time taken of
  // roughly 116 us
  time = micros();
  value = analogRead(A0);
  time2 = micros();
  delta = time2-time;
  Serial.println(value);
  Serial.println(delta);
  delay(500);
}