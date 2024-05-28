#include <MsgPack.h>

// input to msgpack
MsgPack::arr_t<int> v {1, 2, 3, 4}; // std::vector or arx::stdx::vector
int prev;
int timer;
String mode;

void setup() {
    Serial.begin(115200);
    pinMode(A0, INPUT);
    pinMode(A1, INPUT);
    pinMode(A2, INPUT);
    pinMode(2, OUTPUT);
    pinMode(3, OUTPUT);
    pinMode(4, OUTPUT);
    pinMode(5, OUTPUT);
    digitalWrite(5, HIGH);
    // Wait for start message to be sent
    while (Serial.available()==0){

    }
    if (Serial.available() != 0){
      mode = Serial.readString();
      enable_io(mode);
    }
    
}

void loop() {
    prev = micros();
    v[0] = analogRead(A0);
    v[1] = analogRead(A1);
    v[2] = analogRead(A2);
    v[3] = timer;
    MsgPack::Packer packer;
    packer.serialize(v);
    Serial.write(packer.data(), packer.size());
    timer = micros()-prev;
    if (Serial.available() != 0){
      mode = Serial.readString();
      enable_io(mode);
    }
    delay(2000);
}


void enable_io(String mode){
  digitalWrite(5, HIGH);
  if (mode == "Regular"){
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
  }
  else if (mode == "Augmented"){
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);
    digitalWrite(4, HIGH);
    digitalWrite(5, LOW);
  }

}