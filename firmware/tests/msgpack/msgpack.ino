#include <MsgPack.h>

// input to msgpack
MsgPack::arr_t<int> v {1, 2, 3, 4}; // std::vector or arx::stdx::vector
int prev;
int timer;

void setup() {
    Serial.begin(115200);
    pinMode(A0, INPUT);
    pinMode(A1, INPUT);
    pinMode(A2, INPUT);
   
    // Wait for start message to be sent
    while (Serial.available()==0){
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
    delay(2000);
}