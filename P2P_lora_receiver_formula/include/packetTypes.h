#ifndef PACKET_TYPES_H
#define PACKET_TYPES_H

#include <cstdint>
#include <iostream>


struct CarTestPacket {
    uint8_t packetType;    // 1 nibble for type
    uint8_t packetError;   // 1 nibble for Error
    uint8_t packetLength;  // Second byte
    uint8_t steeringAngle; // Third byte
    float batteryVoltage;  // Bytes 4-7
    float batteryTemp;     // Bytes 8-11
    uint8_t throttleInput; // Byte 12
    float brakePressure;   // Bytes 13-16
    float wheelSpeed;      // Bytes 17-20
    float latitude;        // Bytes 21-24
    float longitude;       // Bytes 25-28
};
void printTestPacket(CarTestPacket& pack);

// Define new packet types here (2024 car)

#endif


