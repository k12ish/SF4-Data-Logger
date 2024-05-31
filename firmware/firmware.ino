#include <MsgPack.h>

// input to msgpack
MsgPack::arr_t<int> v {1, 2};             // Data stored as {reading1, reading2, reading3, time passed}
String mode;
bool idle = true;


void setup() {
    Serial.begin(115200);
    pinMode(A0, INPUT);
    pinMode(2, OUTPUT);
    pinMode(3, OUTPUT);
    pinMode(4, OUTPUT);
    digitalWrite(5, HIGH);
    // Wait for start message to be sent
    while (Serial.available()==0){}
    if (Serial.available() != 0){               // Initilise IO for first readings
      mode = Serial.readString();
      enable_io(mode);
    }
    
}


void loop() {
    if(!idle){
      v[0] = analogRead(A0);                      // Read ports
      v[1] = (unsigned int)micros();
      MsgPack::Packer packer;                     // Package data
      packer.serialize(v);                        // Serialise data
      Serial.write(packer.data(), packer.size()); // Send data
    }
    // Serial.println(v[3]);
    if (Serial.available() != 0){               // Check for message from host computer
      mode = Serial.readString();               // Read change in mode
      enable_io(mode);                          // Execute change in mode
    }
}


// Function to change IO states
void enable_io(String mode){
  digitalWrite(5, HIGH);                        // Turn off inputs
  if (mode == "LALL"){                       // Turn on routing for regular lead positions
    MsgPack::str_t s = "LALL";
    MsgPack::Packer packer;
    packer.serialize(s);                        // Serialise data
    Serial.write(packer.data(), packer.size()); // Send data
    digitalWrite(2, HIGH);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
    idle = false;
    // delay(1000);
  }
  else if (mode == "RALL"){                // Turn on routing for augmented lead positions
    MsgPack::str_t s = "RALL";
    MsgPack::Packer packer;
    packer.serialize(s);                        // Serialise data
    Serial.write(packer.data(), packer.size()); // Send data
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(4, HIGH);
    idle = false;
    // delay(1000);
  }
  else if (mode == "LARA"){                // Turn on routing for augmented lead positions
    MsgPack::str_t s = "LARA";
    MsgPack::Packer packer;
    packer.serialize(s);                        // Serialise data
    Serial.write(packer.data(), packer.size()); // Send data
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);
    digitalWrite(4, HIGH);
    idle = false;
    // delay(1000);
  }
  else if (mode == "IDLE"){                // Turn on routing for augmented lead positions
    MsgPack::str_t s = "IDLE";
    MsgPack::Packer packer;
    packer.serialize(s);                        // Serialise data
    Serial.write(packer.data(), packer.size()); // Send data
    digitalWrite(5, HIGH);
    idle = true;
    // delay(1000);
  }
}