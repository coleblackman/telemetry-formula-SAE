#include "../include/packetTypes.h"
#include <RadioLib.h>

void printTestPacket(const CarTestPacket& pack) {
    //Serial.begin(115200); // uncomment if you get issues with Serial
    Serial.print(pack.packetType); Serial.print("\0");
    Serial.print(pack.packetError); Serial.print("\0");
    Serial.print(pack.packetLength); Serial.print("\0");
    Serial.print(pack.steeringAngle); Serial.print("\0");
    Serial.print(pack.batteryVoltage); Serial.print("\0");
    Serial.print(pack.batteryTemp); Serial.print("\0");
    Serial.print(pack.throttleInput); Serial.print("\0");
    Serial.print(pack.brakePressure); Serial.print("\0");
    Serial.print(pack.wheelSpeed); Serial.print("\0");
    Serial.print(pack.latitude); Serial.print("\0");
    Serial.print(pack.longitude); Serial.print("\0");
    Serial.println();
}

void printCarPacket2024(CarPacket2024& pack) {
    //Serial.begin(115200); // uncomment if you get issues with Serial
    // ADD PRINT STATEMENTS FOR ADDITIONAL YEARS HERE
}



/*
ADD NEW PACKETS FOR ADDITIONAL YEARS HERE

void printCarPacket2025(CarPacket2025& pack) {
    ...
}


*/