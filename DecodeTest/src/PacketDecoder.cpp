#include "../include/packetDecoder.h"

int PacketDecoder::getPacketType(uint8_t* data, size_t len) {
    if (len == 0 || data == nullptr) return -1;  // Error checking
    return data[0];  
}

String PacketDecoder::decode(uint8_t* data, size_t len, uint8_t packetType) {
    String decoded;
    for (size_t i = 1; i < len; i++) {  // Start from 1 to skip the packet type
        decoded += (char)data[i];  // Convert each byte to char and append to String
    }
    return decoded;
}
