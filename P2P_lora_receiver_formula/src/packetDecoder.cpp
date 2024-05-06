#include "../include/packetDecoder.h"
#include "../include/packetTypes.h"

int getPacketType(const uint8_t* data, size_t len) {
    if (len == 0 || data == nullptr) return -1;  // Error checking
    int packetType = (data[0] >> 4) & 0x0F; // isolate the first nibble (high)
    return packetType;  
}

bool parseCarTestPacket(const uint8_t* data, size_t len, CarTestPacket& pack) {
   

    uint8_t offset = 0;
    pack.packetType = data[offset] >> 4;  // High nibble for packet type
    pack.packetError = data[offset] & 0xF;  // Low nibble for error
    offset += 1;
    pack.packetLength = data[offset];
    offset += 1;
    pack.steeringAngle = data[offset];
    offset += 1;
    if (offset + sizeof(float) > len) {
        Serial.print("6. Offset: ");// debugging stuff, you can remove
        Serial.println(offset);

        //you do need this return statement though
        return false;
    }
    memcpy(&pack.batteryVoltage, data + offset, sizeof(float)); // copy the data at mem addr + offset into the struct
    offset += sizeof(float); //add4
    if (offset + sizeof(float) > len) {
        Serial.print("5. Offset: ");// debugging stuff, you can remove
        Serial.println(offset);
        return false;
    }
    memcpy(&pack.batteryTemp, data + offset, sizeof(float));
    offset += sizeof(float);
    pack.throttleInput = data[offset];
    offset += 1;
    if (offset + sizeof(float) > len) {
        Serial.print("4. Offset: ");// debugging stuff, you can remove
        Serial.println(offset);
        return false;
    }
    memcpy(&pack.brakePressure, data + offset, sizeof(float));
    offset += sizeof(float);
    if (offset + sizeof(float) > len) {
        Serial.print("3. Offset: ");// debugging stuff, you can remove
        Serial.println(offset);
        return false;
    }
    memcpy(&pack.wheelSpeed, data + offset, sizeof(float));
    offset += sizeof(float);
    if (offset + sizeof(float) > len) {
        Serial.print("2. Offset: ");// debugging stuff, you can remove
        Serial.println(offset);
        return false;
    }
    memcpy(&pack.latitude, data + offset, sizeof(float));
    offset += sizeof(float);
    if (offset + sizeof(float) > len) {
        Serial.print("1. Offset: "); // debugging stuff, you can remove
        Serial.println(offset);
        return false;
    }
    memcpy(&pack.longitude, data + offset, sizeof(float));
    offset += sizeof(float);


    return offset == len;
}

void decode(const uint8_t* data, size_t len, uint8_t packetType) {
    switch (packetType) {
        case 0: {
            CarTestPacket packet;
            if (!parseCarTestPacket(data , len, packet)) {
                Serial.print("ERROR OCCURRED WHILE PARSING PACKET");
            } else {
                printTestPacket(packet);
            }
            break;
        }
        case 1: // 2024 car
        case 2: // 2025 car
        case 3:
            Serial.print("ERR: Unknown Packet Type at decoder level");
            break;
        default:
            Serial.print("ERR: Unknown Packet Type at decoder level");
            break;
    }
}
