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


void loop() {
    if(!idle){
      // MsgPack Start byte: Begin 32 bit unsigned integer
      Serial.write(0xce);
      unsigned int read = analogRead(A0);
      Serial.write((read >> 8) & 0xFF);
      Serial.write((read & 0xFF)); 
      unsigned int time = micros();
      Serial.write((time >> 8) & 0xFF);
      Serial.write((time & 0xFF)); 
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
    digitalWrite(4, LOW);
    idle = false;
    // delay(1000);
  }
  else if (mode == "LARA"){                // Turn on routing for left arm - right arm lead positions
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);
    digitalWrite(4, LOW);
    idle = false;
    // delay(1000);
  }
  else if (mode == "IDLE"){                // Go to idle mode
    digitalWrite(4, HIGH);
    idle = true;
    // delay(1000);
  }
}
