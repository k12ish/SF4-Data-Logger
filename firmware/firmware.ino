#include <MsgPack.h>

// input to msgpack
MsgPack::arr_t<int> v {1, 2, 3, 4};             // Data stored as {reading1, reading2, reading3, time passed}
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
    while (Serial.available()==0){}
    if (Serial.available() != 0){               // Initilise IO for first readings
      mode = Serial.readString();
      enable_io(mode);
    }
    
}


void loop() {
    timer = micros()-prev;                      // Calculate time step for next sample point
    prev = micros();                            // Save initial time point
    v[0] = analogRead(A0);                      // Read ports
    v[1] = analogRead(A1);
    v[2] = analogRead(A2);
    v[3] = timer;
    MsgPack::Packer packer;                     // Package data
    packer.serialize(v);                        // Serialise data
    Serial.write(packer.data(), packer.size()); // Send data
    // Serial.println(v[3]);
    if (Serial.available() != 0){               // Check for message from host computer
      mode = Serial.readString();               // Read change in mode
      enable_io(mode);                          // Execute change in mode
    }
    delayMicroseconds(300);                     // Adjust timing to roughly 1 kHz sampling
    
}


// Function to change IO states
void enable_io(String mode){
  digitalWrite(5, HIGH);                        // Turn off inputs
  if (mode == "Regular"){                       // Turn on routing for regular lead positions
    // Serial.println("Regular");
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    // delay(1000);
  }
  else if (mode == "Augmented"){                // Turn on routing for augmented lead positions
    // Serial.println("Augmented");
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);
    digitalWrite(4, HIGH);
    digitalWrite(5, LOW);
    // delay(1000);
  }
}