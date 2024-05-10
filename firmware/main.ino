int f = 1;
void setup() {
  // put your setup code here, to run once:
pinMode(13, OUTPUT);
Serial.begin(9600);
WaitForRe();
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available() > 0){
    f = int(Serial.read());
  }
  digitalWrite(13, HIGH);
  delay(int(1000/f));
  digitalWrite(13, LOW);
  delay(int(1000/f));
}


void waitForRe() {
  while (Serial.available() <= 0 ){
    Serial.println("Please enter flash frequency in Hz!");
    delay(1000);
  }
}