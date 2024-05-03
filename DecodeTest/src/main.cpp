#include <RadioLib.h>
#include "../include/packetDecoderTest.h"

/****************Pin assignment for the Heltec V3 board******************/
static const int LORA_CS    = 8;      // Chip select pin
static const int LORA_MISO  = 11;
static const int LORA_SCK   = 9;
static const int LORA_NRST  = 12;     // Reset pin
static const int LORA_DIO1  = 14;     // DIO1 switch
static const int LORA_BUSY  = 13; 

/****************LoRa parameters******************/
static const float FREQ = 902.3;  // in MHz
static const float BW = 125.0;    // in kHz
static const uint8_t SF = 8;
static const uint8_t CR = 5;
static const uint8_t SYNC_WORD = 0x34;
static const uint16_t PREAMBLE = 8;

SX1262 radio = new Module(LORA_CS, LORA_DIO1, LORA_NRST, LORA_BUSY);

bool debug_flag = true;

void error_message(const char* message, int16_t state) {
  Serial.printf("ERROR!!! %s with error code %d\n", message, state);
  while(true); // loop forever
}

void setup() {
  Serial.begin(115200);
  Serial.println("Beginning packet decoding tests");
  // Testing stuff
  

}
void loop() {
  
}