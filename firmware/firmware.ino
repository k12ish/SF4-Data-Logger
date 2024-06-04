#include <MsgPack.h>

// input to msgpack
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

long measurements;

void loop() {
    MsgPack::Packer packer;                      // Package data
    if(!idle){
      measurements = micros() << 10;                      // Read ports
      measurements += analogRead(A0);
      packer.serialize(measurements);                     // Serialise data
      Serial.write(packer.data(), packer.size()); // Send data
    }
    if (Serial.available() != 0){               // Check for message from host computer
      mode = Serial.readString();               // Read change in mode
      enable_io(mode);                          // Execute change in mode
    }
}


// Function to change IO states
void enable_io(String mode){
  digitalWrite(5, HIGH);                        // Turn off inputs

  MsgPack::str_t s = mode;
  MsgPack::Packer packer;
  packer.serialize(s);                        // Serialise data
  Serial.write(packer.data(), packer.size()); // Send data

  if (mode == "LALL"){                       // Turn on routing for regular lead positions
    digitalWrite(2, HIGH);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
    idle = false;
    // delay(1000);
  }
  else if (mode == "RALL"){                // Turn on routing for right arm - left leg lead positions
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(4, HIGH);
    idle = false;
    // delay(1000);
  }
  else if (mode == "LARA"){                // Turn on routing for left arm - right arm lead positions
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);
    digitalWrite(4, HIGH);
    idle = false;
    // delay(1000);
  }
  else if (mode == "IDLE"){                // Go to idle mode
    digitalWrite(4, LOW);
    idle = true;
    // delay(1000);
  }
}
