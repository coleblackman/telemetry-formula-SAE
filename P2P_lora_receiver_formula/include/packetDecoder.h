#ifndef PACKET_DECODER_H
#define PACKET_DECODER_H

#include <Arduino.h>
#include "../include/packetTypes.h"

int getPacketType(const uint8_t* data, size_t len);

bool parseCarTestPacket(const uint8_t* data, size_t len, CarTestPacket& pack);

void decode(const uint8_t* data, size_t len, uint8_t packetType);

#endif
