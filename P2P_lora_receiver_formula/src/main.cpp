#include <RadioLib.h> // inherits all the stdlibs for arduino and such
#include "../include/packetDecoder.h"

/*

This code module runs on the Heltec v3 board, which is a LoRa transceiver.

This board needs to be connected via USB to a base station 

This code sends a decoded packet (that it receives over LoRa) to the base station

It uses UART over Serial over USB.


*/


/****************Motorsports Parameters********************/

#define MAX_PACKET_SIZE 28 // This needs to equal the largest size for any packet type

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
static const uint8_t SF = 8; // Spreading factor - must be the same between sender and receiver
static const uint8_t CR = 5;
static const uint8_t SYNC_WORD = 0x34;
static const uint16_t PREAMBLE = 8;

SX1262 radio = new Module(LORA_CS, LORA_DIO1, LORA_NRST, LORA_BUSY);

bool debug_flag = false;

void error_message(const char* message, int16_t state) {
  Serial.printf("ERROR!!! %s with error code %d\n", message, state);
  while(true); // loop forever
}

void setup() {
  Serial.begin(115200);

  if (debug_flag) {
      Serial.print(F("[SX1262] Initializing ... "));
      Serial.print("Frequency in MHz: ");
      Serial.print(FREQ);
      Serial.print(" Spreading factor: ");
      Serial.print(SF);
      Serial.print(" Bandwidth in kHz: ");
      Serial.println(BW);
  }

  int state = radio.begin();
  if (state != RADIOLIB_ERR_NONE) {
    error_message("Radio initialization failed", state);
  }

  // Set Lora modulation parameters
  state = radio.setFrequency(FREQ);
  if (state != RADIOLIB_ERR_NONE) {
    error_message("Frequency initialization failed", state);
  }
  state = radio.setBandwidth(BW);
  if (state != RADIOLIB_ERR_NONE) {
    error_message("Bandwidth initialization failed", state);
  }
  state = radio.setSpreadingFactor(SF);
  if (state != RADIOLIB_ERR_NONE) {
    error_message("Spreading Factor initialization failed", state);
  }
  state = radio.setCodingRate(CR);
  if (state != RADIOLIB_ERR_NONE) {
    error_message("Coding Rate initialization failed", state);
  }
  state = radio.setSyncWord(SYNC_WORD);
  if (state != RADIOLIB_ERR_NONE) {
    error_message("Sync Word initialization failed", state);
  }
  state = radio.setPreambleLength(PREAMBLE);
  if (state != RADIOLIB_ERR_NONE) {
    error_message("Preamble Length initialization failed", state);
  }

  // Set to listen
  state = radio.startReceive();
  if (state != RADIOLIB_ERR_NONE) {
    error_message("Start Receive failed", state);
  }
  if (debug_flag) {
    Serial.println(F("[SX1262] Listening..."));
  }
}

void loop() {
  uint8_t rx_buffer[MAX_PACKET_SIZE];
  int16_t state = radio.readData(rx_buffer, sizeof(rx_buffer));

  if (state == RADIOLIB_ERR_NONE) {
    // data receive was successful

    //  This code prints the unformatted undecoded packet (raw)
    if (debug_flag) {
      for (size_t i = 1; i < sizeof(rx_buffer) && rx_buffer[i] != '\0'; i++) {
        Serial.print(rx_buffer[i], HEX);
        Serial.print(" ");
      }
      Serial.println();
    }
    else {
      // idenfity the packet type (what year is the car?)
      int packetType = PacketDecoder::getPacketType(rx_buffer, sizeof(rx_buffer)); //functions are static
      // decode the packet according to its type 
      // This code also sends the decoded message over Serial to the base station
      PacketDecoder::decode(rx_buffer, sizeof(rx_buffer), packetType);    
      
    }



    if (debug_flag) {
      Serial.print(F("[SX1262] RSSI:\t\t"));
      Serial.print(radio.getRSSI());
      Serial.println(F(" dBm"));
      Serial.print(F("[SX1262] SNR:\t\t"));
      Serial.print(radio.getSNR());
      Serial.println(F(" dB"));
    }

  } else if (state == RADIOLIB_ERR_CRC_MISMATCH && debug_flag) {
    Serial.println(F("CRC error!"));
  } else {
    if (debug_flag) {
      Serial.print(F("Receive failed, code "));
      Serial.println(state);
    }
  }

  // put module back to listen mode
  radio.startReceive();
}
