#include "../include/packetTypes.h"
#include <RadioLib.h>

void printCarPacket2024(CarPacket2024& pack) {
    //Serial.begin(115200); // uncomment if you get issues with Serial
    Serial.print(pack.packetType); //TODO finish this definition
    Serial.print("\0");
    Serial.print(pack.engineTemperature);
    Serial.print("\0");
    Serial.println(pack.packetLength);

}