#include "../include/packetDecoder.h"
#include "../include/packetTypes.h"

int PacketDecoder::getPacketType(uint8_t* data, size_t len) {
    if (len == 0 || data == nullptr) return -1;  // Error checking
    int packetType = (data[0] >> 4) & 0x0F; // isolate the first nibble (high)
    return packetType;  
}

bool parseCarTestPacket(const uint8_t* data, size_t len, CarTestPacket& pack)
{
    if (data == nullptr || len < sizeof(CarTestPacket)) { //   checking input validity
        return false;  
    }

    size_t offset = 0;
    packet.packetType = data[offset];
    offset += sizeof(packet.packetType);
    // etc.
    if (offset + sizeof(float) <= length) {  // Ensure there's enough data for a float
        memcpy(&packet.batteryVoltage, data + offset, sizeof(float));
        offset += sizeof(float);
    } else {
        return false;  // Not enough data for battery voltage
    }

    return offset == length; // Did we parse the anticipated size of data?
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

