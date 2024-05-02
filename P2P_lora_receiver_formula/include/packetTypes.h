#ifndef PACKET_TYPES_H
#define PACKET_TYPES_H

#include <cstdint>
#include <iostream>

struct CarTestPacket {
    uint8_t packetType;
    uint8_t packetLength;
    uint8_t steeringAngle;
    float engineTemperature;
    uint8_t throttleInput;
};

struct CarPacket2024 {
    uint8_t packetType;
    uint8_t packetLength;
    uint8_t steeringAngle;
    float batteryVoltage;
    uint8_t brakePressure;
};

void printTestPacket(CarTestPacket& pack);

void printCarPacket2024(CarPacket2024& pack);



/*
ADD NEW PACKETS HERE 

struct CarPacket2025 {
    ...
}
*/

#endif