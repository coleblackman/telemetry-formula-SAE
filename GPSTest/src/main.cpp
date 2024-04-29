#include <Arduino.h>
#include <SoftwareSerial.h>
#include <TinyGPS++.h>

#define RX_PIN 3 // Arduino Pin connected to the TX of the GPS module
#define TX_PIN 2  // Arduino Pin connected to the RX of the GPS module

/* Serial 2: 
        |ESP32 pin| Heltec pin |
    TX: |GPIO 27  | 21
    RX: |GPIO 25  | 19
*/
TinyGPSPlus gps; // the TinyGPS++ object
// SoftwareSerial gpsSerial(RX_PIN, TX_PIN); // the serial interface to the GPS module
EspSoftwareSerial::UART gpsSerial;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.print(F("Initializing usb uart... "));

  gpsSerial.begin(9600, SWSERIAL_8N1, RX_PIN, TX_PIN, false);  // Default baud of NEO-6M GPS module is 9600
  if (!gpsSerial) { // If the object did not initialize, then its configuration is invalid
    Serial.println("Invalid EspSoftwareSerial pin configuration, check config"); 
    while (1) { // Don't continue with invalid configuration
      delay (1000);
    }
  } 

  // Serial.print(F("Initializing gps uart... "));
}

void loop() {
  if (gpsSerial.available() > 0) {
    if (gps.encode(gpsSerial.read())) {
      if (gps.location.isValid()) {
        Serial.print(F("- latitude: "));
        Serial.println(gps.location.lat(), 6);

        Serial.print(F("- longitude: "));
        Serial.println(gps.location.lng(), 6);

        Serial.print(F("- altitude: "));
        if (gps.altitude.isValid())
          Serial.println(gps.altitude.meters());
        else
          Serial.println(F("INVALID"));
      } else {
        Serial.println(F("- location: INVALID"));
      }

      Serial.print(F("- speed: "));
      if (gps.speed.isValid()) {
        Serial.print(gps.speed.kmph());
        Serial.println(F(" km/h"));
      } else {
        Serial.println(F("INVALID"));
      }

      Serial.print(F("- GPS date&time: "));
      if (gps.date.isValid() && gps.time.isValid()) {
        Serial.print(gps.date.year());
        Serial.print(F("-"));
        Serial.print(gps.date.month());
        Serial.print(F("-"));
        Serial.print(gps.date.day());
        Serial.print(F(" "));
        Serial.print(gps.time.hour());
        Serial.print(F(":"));
        Serial.print(gps.time.minute());
        Serial.print(F(":"));
        Serial.println(gps.time.second());
      } else {
        Serial.println(F("INVALID"));
      }

      Serial.println();
    }
  }

  if (millis() > 5000 && gps.charsProcessed() < 10)
    Serial.println(F("No GPS data received: check wiring"));
    // char s = gpsSerial.read();
    // Serial.print(gpsSerial.read());

}

// put function definitions here:
