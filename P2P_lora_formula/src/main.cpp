#include <RadioLib.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include "driver/temp_sensor.h"

#define RX_PIN 3// todo fill in
#define TX_PIN 2// todo fill in

// Packet type defs
#define TESTING_PKT 0b0000
#define LEGACY_PKT  0b0001  
#define CAR2024_PKT 0b0010
#define CAR2025_PKT 0b0011

// Error type defs
#define NO_ERR        0b0000
#define CRIT_ERR1     0b0001 
#define CRIT_ERR2     0b0010 
#define CRIT_ERR3     0b0011 
#define CRIT_ERR4     0b0100 
#define NON_CRIT_ERR1 0b0101 

// other 
#define PKT_LEN 28
// #define SEND_OVER_SERIAL
// #define TEST_GPS
// gps stuff
TinyGPSPlus gps; // the TinyGPS++ object

EspSoftwareSerial::UART gpsSerial;

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
 static const uint8_t SYNC_WORD = (uint8_t)0x27;
 static const uint16_t PREAMBLE = 8;

#define TEST_PKT_LEN      5
uint8_t test_pkt[] = {1, 2, 3, 4, 5};

SX1262 radio = new Module(LORA_CS, LORA_DIO1, LORA_NRST, LORA_BUSY);

float get_temp(){
  float raw_temp = 0;
	temp_sensor_read_celsius(&raw_temp);
	raw_temp = (raw_temp * 9.0/5.0) + 32;
  return raw_temp;
}

void insert_float(uint8_t* pkt, float num, int index){
  uint8_t byteArray[sizeof(float)];
	memcpy(byteArray, &num, sizeof(float));
  
  // uint8_t bigend_array[4] = {byteArray[3], byteArray[2], byteArray[1], byteArray[0]};
  for (int i = index; i < (sizeof(float)+index); i++) {
		pkt[i] = byteArray[i - index];
	}
}

// function only called with valid gps info
void create_packet(uint8_t* pkt){
  pkt[0] = (TESTING_PKT << 4) | NO_ERR; // TYPE & ERROR 

  pkt[1] = PKT_LEN; //length of pkt in bytes

  pkt[2] = (uint8_t) gps.course.deg(); // gps heading

  //battery voltage (float)... spoofed val
  pkt[3] = 0;
  pkt[4] = 0;
  pkt[5] = 0;
  pkt[6] = 0;

  // temp
  insert_float(pkt, get_temp(), 7);  

  float cur_speed = static_cast<float>(gps.speed.mph());
  pkt[11] = (uint8_t) (10 * cur_speed); // throttle input spoofed w scaled velocity
  
  insert_float(pkt, 1/(10 * cur_speed), 12); // brake pressure, inverse scaled velocity

  insert_float(pkt, cur_speed, 16); // wheelspeed, replaced w velocity

  insert_float(pkt, static_cast<float>(gps.location.lat()), 20);

  insert_float(pkt, static_cast<float>(gps.location.lng()), 24);
}

void print_pkt(uint8_t* pkt, int len){
  for (int i = 0; i < len; i++){
    // Serial.print("Byte ");
    // Serial.print(i);
    // Serial.print(": ");
    Serial.print(pkt[i], HEX);
    Serial.print(" ");
  }
  Serial.print("\n");
}

void transmit_pkt(uint8_t* my_pkt, int len){
  int state = radio.transmit(my_pkt, len);
  // String mystr = "Penis";
  // uint8_t mystr[] = {45, 46, 47};
  // int state = radio.transmit(mystr, sizeof(mystr));

  if (state == RADIOLIB_ERR_NONE) {// ifthe packet was successfully transmitted
    // print measured data rate
    Serial.print(F("Sent packet with Datarate:\t"));
    Serial.print(radio.getDataRate());
    Serial.println(F(" bps and bytes"));
    print_pkt(my_pkt, len);
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
  gpsSerial.begin(9600, SWSERIAL_8N1, RX_PIN, TX_PIN, false);  // Default baud of NEO-6M GPS module is 9600
  if (!gpsSerial) { // If the object did not initialize, then its configuration is invalid
    Serial.println("Invalid EspSoftwareSerial pin configuration, check config"); 
    while (1) { // Don't continue with invalid configuration
      delay (1000);
    }
  } 

  Serial.println(F("Arduino - GPS module"));

  //config temp sensor
  temp_sensor_config_t temp_sensor = TSENS_CONFIG_DEFAULT();
  temp_sensor.dac_offset = TSENS_DAC_L2;  // TSENS_DAC_L2 is default; L4(-40°C ~ 20°C), L2(-10°C ~ 80°C), L1(20°C ~ 100°C), L0(50°C ~ 125°C)
  temp_sensor_set_config(temp_sensor);
  temp_sensor_start();
}

void loop() {
  #ifdef TEST_GPS
  if(gpsSerial.available() > 0){
    if (gps.encode(gpsSerial.read())) {
      if (gps.location.isValid()) {
        Serial.print(F("- latitude: "));
        Serial.println(gps.location.lat());

        Serial.print(F("- longitude: "));
        Serial.println(gps.location.lng());

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
  #else
  // Check if there's data available on the serial port
  if (gpsSerial.available() > 0){
    if(gps.encode(gpsSerial.read())){
      if (gps.location.isValid() && gps.speed.isValid() && gps.course.isValid()){
        uint8_t my_pkt[PKT_LEN];
        create_packet(my_pkt);

        transmit_pkt(my_pkt, PKT_LEN);
        //todo: tx packet
      } else{
        Serial.println("gps params not valid");
      }
    }
  }
  #endif

  if (millis() > 5000 && gps.charsProcessed() < 10)
    Serial.println(F("No GPS data received: check wiring"));

  #ifdef SEND_OVER_SERIAL
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
  #endif




}