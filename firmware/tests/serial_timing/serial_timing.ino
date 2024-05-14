int time;
int time2;
int delta;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Please enter a character to begin timing:");
}

void loop() {
  // put your main code here, to run repeatedly:
  time = micros();  
}

//This function runs whenever the serial bus receives a message
//Code that should run when that happens, such as changes of system states should be called here, currently it just clears the serial buffer
//to then seemlessly return to the main loop. Be aware that it gets called whenever there is any information in the buffer and that Serial.read
//only read the first byte! The register clearing operation takes around 3.8 us for each character
void serialEvent(){
  time2 = micros();
  delta = time2-time;
  Serial.println(delta);
  Serial.println("Serial Event received. Entered interrupt!");
  time = micros();
  while(Serial.available() > 0){
    int t = Serial.read();
  }
  time2 = micros();
  delta = time2-time;
  Serial.println(delta);
}