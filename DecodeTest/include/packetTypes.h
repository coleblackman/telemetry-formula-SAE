#ifndef PACKET_TYPES_H
#define PACKET_TYPES_H

#include <cstdint>
#include <iostream>

struct CarPacket2024 {
    uint8_t packetType;
    uint8_t packetLength;
    uint8_t steeringAngle;
    float engineTemperature;
    uint8_t throttleInput;
};

struct CarPacket2025 {
    uint8_t packetType;
    uint8_t packetLength;
    uint8_t steeringAngle;
    float batteryVoltage;
    uint8_t brakePressure;
};

#endif