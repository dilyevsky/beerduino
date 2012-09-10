
#include <stdint.h>

extern "C" {
#include "pb_decode.h"
#include "pb_encode.h"

#include "beerduino.pb.h"
}

void setup() {
  Serial.begin(9600);
  Serial.println("Hello.");
}

void loop() {
}

void serialEvent() {
  if(Serial.available()) {
    int packet_size = Serial.read();

    uint8_t in_buffer[256];
    int bytes_read = Serial.readBytes((char*)in_buffer, packet_size);
    if (bytes_read != packet_size) {
      // Well... fuck
      return;
    }

    pb_istream_t istream = pb_istream_from_buffer(in_buffer, bytes_read);
    beerduino_Ping ping_msg;
    if(!pb_decode(&istream, beerduino_Ping_fields, &ping_msg)) {
      // Well... fuck
      return;
    }

    beerduino_Echo echo_msg = {ping_msg.id, true, "Hello"};

    uint8_t out_buffer[256];
    pb_ostream_t ostream = pb_ostream_from_buffer(out_buffer,
                                                  sizeof(out_buffer));
    if (pb_encode(&ostream, beerduino_Echo_fields, &echo_msg)) {
      Serial.write(ostream.bytes_written);
      Serial.write(out_buffer, ostream.bytes_written);
    }
  }
}

