/*
   To successfully receive data, the following settings have to be the same
   on both transmitter and receiver:
    - carrier frequency
    - bandwidth
    - spreading factor
*/

// include the library
#include <RadioLib.h>

/****************Pin assignment for the Heltec V3 board******************/
static const int LORA_CS    = 8;      // Chip select pin
static const int LORA_MOSI  = 10;     
static const int LORA_MISO  = 11;
static const int LORA_SCK   = 9;
static const int LORA_NRST  = 12;      // Reset pin
static const int LORA_DIO1  = 14;      // DIO1 switch
static const int LORA_BUSY  = 13; 

/****************LoRa parameters (you need to fill these params)******************/
 static const float FREQ = 902.3;
 static const float BW = 125.;
 static const uint8_t SF = 8;
 static const int8_t TX_PWR = 20;
 static const uint8_t CR = 5;
 static const uint8_t SYNC_WORD = (uint8_t)0x34;
 static const uint16_t PREAMBLE = 8;



bool debug_flag = false;

SX1262 radio = new Module(LORA_CS, LORA_DIO1, LORA_NRST, LORA_BUSY);

// this function is called when a complete packet
// is received by the module
// IMPORTANT: this function MUST be 'void' type
//            and MUST NOT have any arguments!
#if defined(ESP8266) || defined(ESP32)
  ICACHE_RAM_ATTR
#endif



// It is important to remember that ISRs are supposed to be short and are mostly used for triggering flags. 
// doing Serial.print() might fail and cause device resets. This is because Serial.print() uses interrupt to read data, 
// but in an ISR, all other interrupts are suspended, and therefore the operation fails. 

// Helper function to print error messages
void error_message(const char* message, int16_t state) {
  Serial.printf("ERROR!!! %s with error code %d\n", message, state);
  while(true); // loop forever
}

void setup() {
  Serial.begin(115200);


  // Create a transmit interrupt when the button is pressed. 
  pinMode(BUTTON, INPUT);
  attachInterrupt(digitalPinToInterrupt(BUTTON), buttonISR, FALLING);

  if(debug_flag) {
      // initialize SX1262 with default settings
      Serial.print(F("[SX1262] Initializing ... "));

      Serial.print("Frequency in MHz: ");
      Serial.print(FREQ);
      Serial.print("Spreading factor: ");
      Serial.print(SF);
      Serial.print("Bandwidth in kHz: ");
      Serial.print(BW);
  }

  int state = radio.begin();
  if (state == RADIOLIB_ERR_NONE && debug_flag) {
    Serial.println(F("success!"));
  } else {
    if(debug_flag) {
      Serial.print(F("failed, code "));
      Serial.println(state);
    }
    while (true);
  }

  state = radio.setBandwidth(BW);
  if (state != RADIOLIB_ERR_NONE && debug_flag) {
      error_message("BW intialization failed", state);
  }
  state = radio.setFrequency(FREQ);
  if (state != RADIOLIB_ERR_NONE && debug_flag) {
      error_message("Frequency intialization failed", state);
  }
  state = radio.setSpreadingFactor(SF);
  if (state != RADIOLIB_ERR_NONE && debug_flag) {
      error_message("SF intialization failed", state);
  }
  state = radio.setOutputPower(TX_PWR);
  if (state != RADIOLIB_ERR_NONE && debug_flag) {
      error_message("Output Power intialization failed", state);
  }
 
  state = radio.setCurrentLimit(140.0);
  if (state != RADIOLIB_ERR_NONE && debug_flag) {
      error_message("Current limit intialization failed", state);
  }
   radio.setDio1Action(setFlag);    // callback when the RF interrupt is triggered

  if (debug_flag)
    Serial.print(F("[SX1262] Starting to listen ... "));
  state = radio.startReceive();
  if (state == RADIOLIB_ERR_NONE && debug_flag) {
    Serial.println(F("success!"));

  } else {
    if(debug_flag) {
      Serial.print(F("failed, code "));
      Serial.println(state);
    }
    while (true);
  }
}

void loop() {
    // you can read received data as an Arduino String
    String rx_data;
    int state = radio.readData(rx_data);

    if (state == RADIOLIB_ERR_NONE) {

      if (debug_flag) {
        // packet was successfully received
        Serial.println(F("[SX1262] Received packet!"));

        // print data of the packet
        Serial.print(F("[SX1262] Data:\t\t"));
      }
      Serial.println(rx_data);

      if (debug_flag) {
        // print RSSI (Received Signal Strength Indicator)
        Serial.print(F("[SX1262] RSSI:\t\t"));
        Serial.print(radio.getRSSI());
        Serial.println(F(" dBm"));

        // print SNR (Signal-to-Noise Ratio)
        Serial.print(F("[SX1262] SNR:\t\t"));
        Serial.print(radio.getSNR());
        Serial.println(F(" dB"));
      }

    } else if (state == RADIOLIB_ERR_CRC_MISMATCH && debug_flag) {
      // packet was received, but is malformed
      Serial.println(F("CRC error!"));

    } else {
      // some other error occurred
      if (debug_flag) {
        Serial.print(F("failed, code "));
        Serial.println(state);
      }
    }

    // put module back to listen mode
    radio.startReceive();
  
}