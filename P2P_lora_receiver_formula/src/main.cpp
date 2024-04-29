#include <RadioLib.h>

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
  String rx_data;
  int state = radio.readData(rx_data);

  if (state == RADIOLIB_ERR_NONE) {
    Serial.println(rx_data);

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
