#include <EmonLib.h>
#include <WiFi.h>
#include <ArduinoJson.h>

// Define WiFi credentials
const char *WIFI_SSID = "network_name";
const char *WIFI_PASSWORD = "network_password";

// Create instance of emonLib library
EnergyMonitor emon1;

// Define ADC inputs
const int ADC_PIN_1 = 30;
const int ADC_PIN_2 = 31;
const int ADC_PIN_3 = 32;
const int ADC_PIN_4 = 33;
const int ADC_PIN_5 = 34;

// Define VCC inputs
const int VCC_PIN_1 = 35;
const int VCC_PIN_2 = 36;
const int VCC_PIN_3 = 37;
const int VCC_PIN_4 = 38;
const int VCC_PIN_5 = 39;

// Define array of ADC and VCC readings
short adc_readings[30];
short vcc_readings[30];
short measure_count = 0;
unsigned long last_measure_time = 0;
unsigned long finished_setup_time = 0;
