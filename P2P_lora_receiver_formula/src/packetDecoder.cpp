#include "../include/packetDecoder.h"
#include "../include/packetTypes.h"

int PacketDecoder::getPacketType(uint8_t* data, size_t len) {
    if (len == 0 || data == nullptr) return -1;  // Error checking
    int packetType = (data[0] >> 4) & 0x0F; // isolate the first nibble (high)
    return packetType;  
}

bool parseCarTestPacket(const uint8_t* data, size_t len, CarTestPacket& pack) {
    if (data == nullptr || len < sizeof(CarTestPacket)) {
        return false;  
    }

    size_t offset = 0;

    // Assuming the first byte is split into two nibbles for packetType and Error
    pack.packetType = data[offset] >> 4;  // High nibble for packet type
    pack.packetError = data[offset] & 0xF;  // Low nibble for error
    offset += 1;

    // Next byte for packet length
    pack.packetLength = data[offset];
    offset += 1;

    // Next byte for steering angle
    pack.steeringAngle = data[offset];
    offset += 1;

    // Next four bytes for battery voltage
    if (offset + sizeof(float) > len) return false;
    memcpy(&pack.batteryVoltage, data + offset, sizeof(float));
    offset += sizeof(float);

    // Next four bytes for battery temperature
    if (offset + sizeof(float) > len) return false;
    memcpy(&pack.batteryTemp, data + offset, sizeof(float));
    offset += sizeof(float);

    // Next byte for throttle input
    pack.throttleInput = data[offset];
    offset += 1;

    // Next four bytes for brake pressure
    if (offset + sizeof(float) > len) return false;
    memcpy(&pack.brakePressure, data + offset, sizeof(float));
    offset += sizeof(float);

    // Next four bytes for wheel speed
    if (offset + sizeof(float) > len) return false;
    memcpy(&pack.wheelSpeed, data + offset, sizeof(float));
    offset += sizeof(float);

    // Next four bytes for latitude
    if (offset + sizeof(float) > len) return false;
    memcpy(&pack.latitude, data + offset, sizeof(float));
    offset += sizeof(float);

    // Next four bytes for longitude
    if (offset + sizeof(float) > len) return false;
    memcpy(&pack.longitude, data + offset, sizeof(float));
    offset += sizeof(float);

    // Verify that we have consumed all the data
    return offset == len;
}

/*
Add additional packet types here:

bool parseCarPacket2024(const uint8_t* data, size_t len, CarPacket2025& pack)
*/

void PacketDecoder::decode(uint8_t* data, size_t len, uint8_t packetType) {
    switch (packetType) {
        case 0: {
            // Test packet
            CarTestPacket packet;
            printTestPacket(packet);
        }
        case 1: {
            //legacy (2023) packet
            Serial.print("ERR: Unknown Packet Type at decoder level");
            break;
        }
        case 2: {
            //2024 car packet
            Serial.print("ERR: Unknown Packet Type at decoder level");
            break;
        }
        case 3: {
             //2025 car packet
            Serial.print("ERR: Unknown Packet Type at decoder level");
            break;
        }
        default:
            // This error should never be possible. 
            Serial.print("ERR: Unknown Packet Type at decoder level");
            break;
}

