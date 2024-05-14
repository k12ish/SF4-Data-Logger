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
  // put your main code here, to run repeatedly:
  time = micros();
  value = analogRead(A0);
  time2 = micros();
  delta = time2-time;
  Serial.println(value);
  Serial.println(delta);
  delay(500);
}

//This function runs whenever the serial bus receives a message
//Code that should run when that happens, such as changes of system states should be called here, currently it just clears the serial buffer
//to then seemlessly return to the main loop. Be aware that it gets called whenever there is any information in the buffer and that Serial.read
//only read the first byte!
void serialEvent(){
  Serial.print("Serial Event received. Entered interrupt!");
  while(Serial.available() > 0){
    int t = Serial.read();
  }
}