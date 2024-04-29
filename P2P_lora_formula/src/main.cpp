#include <RadioLib.h>
#include <TinyGPS++.h>

#define RX_PIN 0// todo fill in
#define TX_PIN 0// todo fill in

// gps stuff
TinyGPSPlus gps; // the TinyGPS++ object
// todo: use proper serial connection setup ---> USE "Serial1"  
// SoftwareSerial gpsSerial(RX_PIN, TX_PIN); // the serial interface to the GPS module

//Configure for the Heltec board pinout
// SX1262 LoRa chip
static const int LORA_CS    = 8;      // Chip select pin
static const int LORA_MOSI  = 10;     
static const int LORA_MISO  = 11;
static const int LORA_SCK   = 9;
static const int LORA_NRST  = 12;      // Reset pin
static const int LORA_DIO1  = 14;      // DIO1 switch
static const int LORA_BUSY  = 13; 
static const int BUTTON     = 0;

int num_sent = 0;
// lora parameters

// you can receive these packets on any LoRa receiver, as long as carrier frequency, BW, and SF are the same

 static const float FREQ = 902.3;
 static const float BW = 125.;
 static const uint8_t SF = 11;
 static const int8_t TX_PWR = 22;
 static const uint8_t CR = 5;
 static const uint8_t SYNC_WORD = (uint8_t)0x34;
 static const uint16_t PREAMBLE = 8;


SX1262 radio = new Module(LORA_CS, LORA_DIO1, LORA_NRST, LORA_BUSY);

// Note: remember to remove Serial.print() statements before going to production on the car; could fail and reset the device. This is because Serial.print() uses interrupt to read data, 
// but in an ISR, all other interrupts are suspended, and therefore the operation fails.

// Helper function to print error messages
void error_message(const char* message, int16_t state) {
  Serial.printf("ERROR!!! %s with error code %d\n", message, state);
  while(true); 
}

void setup() {
  Serial.begin(115200);
  Serial.print(F("Initializing ... "));

  Serial.print("Frequency in MHz: ");
  Serial.print(FREQ);
  Serial.print("Spreading factor: ");
  Serial.print(SF);
  Serial.print("Bandwidth in kHz: ");
  Serial.print(BW);

  int state = radio.begin();
  if (state == RADIOLIB_ERR_NONE) {
    Serial.println(F("success!"));
  } else {
    Serial.print(F("failed, code "));
    Serial.println(state);
    while (true);
  }

  state = radio.setBandwidth(BW);
  if (state != RADIOLIB_ERR_NONE) {
      error_message("BW intialization failed", state);
  }
  state = radio.setFrequency(FREQ);
  if (state != RADIOLIB_ERR_NONE) {
      error_message("Frequency intialization failed", state);
  }
  state = radio.setSpreadingFactor(SF);
  if (state != RADIOLIB_ERR_NONE) {
      error_message("SF intialization failed", state);
  }
  state = radio.setOutputPower(TX_PWR);
  if (state != RADIOLIB_ERR_NONE) {
      error_message("Output Power intialization failed", state);
  }
 
  state = radio.setCurrentLimit(140.0);
  if (state != RADIOLIB_ERR_NONE) {
      error_message("Current limit intialization failed", state);
  }
  // gps stuff
  // gpsSerial.begin(9600);
  Serial.println(F("Arduino - GPS module"));
}

void loop() {
  // Check if there's data available on the serial port
  if (Serial.available() > 0) {
    String tx_payload = Serial.readString(); // Read data from the serial port
    // You may want to add some validation or processing here
    
    Serial.print(F("Transmitting packet ... "));

    // Transmit the received data
    int state = radio.transmit(tx_payload);

    if (state == RADIOLIB_ERR_NONE) {// ifthe packet was successfully transmitted

      // print measured data rate
      Serial.print(F("Datarate:\t"));
      Serial.print(radio.getDataRate());
      Serial.println(F(" bps"));
    } else if (state == RADIOLIB_ERR_PACKET_TOO_LONG) {
      // the supplied packet was longer than 256 bytes
      Serial.println(F("too long longer than 256B"));
    } else if (state == RADIOLIB_ERR_TX_TIMEOUT) {
      // timeout occured while transmitting packet
      Serial.println(F("timed out, failed to transmit your packet"));
    } else {
      // some other error occurred
      Serial.print(F("failed (did not time out), code "));
      Serial.println(state);
    }
  }
  //  else if(gpsSerial.available() > 0){
  //   if (gps.encode(gpsSerial.read())) {
  //     if (gps.location.isValid()) {
  //       Serial.print(F("- latitude: "));
  //       Serial.println(gps.location.lat());

  //       Serial.print(F("- longitude: "));
  //       Serial.println(gps.location.lng());

  //       Serial.print(F("- altitude: "));
  //       if (gps.altitude.isValid())
  //         Serial.println(gps.altitude.meters());
  //       else
  //         Serial.println(F("INVALID"));
  //     } else {
  //       Serial.println(F("- location: INVALID"));
  //     }

  //     Serial.print(F("- speed: "));
  //     if (gps.speed.isValid()) {
  //       Serial.print(gps.speed.kmph());
  //       Serial.println(F(" km/h"));
  //     } else {
  //       Serial.println(F("INVALID"));
  //     }

  //     Serial.print(F("- GPS date&time: "));
  //     if (gps.date.isValid() && gps.time.isValid()) {
  //       Serial.print(gps.date.year());
  //       Serial.print(F("-"));
  //       Serial.print(gps.date.month());
  //       Serial.print(F("-"));
  //       Serial.print(gps.date.day());
  //       Serial.print(F(" "));
  //       Serial.print(gps.time.hour());
  //       Serial.print(F(":"));
  //       Serial.print(gps.time.minute());
  //       Serial.print(F(":"));
  //       Serial.println(gps.time.second());
  //     } else {
  //       Serial.println(F("INVALID"));
  //     }

  //     Serial.println();
  //   }
  // }


}