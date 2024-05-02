#ifndef PACKET_DECODER_H
#define PACKET_DECODER_H

#include <Arduino.h>

class PacketDecoder {
public:
    static int getPacketType(uint8_t* data, size_t len);
    static String decode(uint8_t* data, size_t len, uint8_t packetType);
};

#endif
