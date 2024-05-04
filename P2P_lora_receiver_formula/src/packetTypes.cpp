#include "../include/packetTypes.h"
#include <RadioLib.h>

void printTestPacket(CarTestPacket& pack) {
    //Serial.begin(115200); // uncomment if you get issues with Serial
    Serial.print(pack.packetType); Serial.print(",");
    Serial.print(pack.packetError); Serial.print(",");
    Serial.print(pack.packetLength); Serial.print(",");
    Serial.print(pack.steeringAngle); Serial.print(",");
    Serial.print(pack.batteryVoltage); Serial.print(",");
    Serial.print(pack.batteryTemp); Serial.print(",");
    Serial.print(pack.throttleInput); Serial.print(",");
    Serial.print(pack.brakePressure); Serial.print(",");
    Serial.print(pack.wheelSpeed); Serial.print(",");
    Serial.print(pack.latitude, 8); Serial.print(",");
    Serial.print(pack.longitude, 8); Serial.print(","); //Note that Serial.print defaults to 2 decimal places, that is why we specify 8 here.
    Serial.println();
}

/*
ADD NEW PACKETS FOR ADDITIONAL YEARS HERE

void printCarPacket2025(CarPacket2025& pack) {
    ...
}


*/