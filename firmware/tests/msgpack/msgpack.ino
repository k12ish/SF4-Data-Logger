#include <MsgPack.h>

// input to msgpack
int i = 123;
float f = 1.23;
MsgPack::str_t s = "str"; // std::string or String
MsgPack::arr_t<int> v {1, 2, 3}; // std::vector or arx::stdx::vector
MsgPack::map_t<String, float> m {{"one", 1.1}, {"two", 2.2}, {"three", 3.3}}; // std::map or arx::stdx::map

// output from msgpack
int ri;
float rf;
MsgPack::str_t rs;
MsgPack::arr_t<int> rv;
MsgPack::map_t<String, float> rm;

void setup() {
    delay(2000);
    Serial.begin(115200);

    // serialize to msgpack
    MsgPack::Packer packer;
    packer.serialize(i, f, s, v, m);

    Serial.write(packer.data(), packer.size());
}

void loop() {}