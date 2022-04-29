#include <EmonLib.h>
#include <WiFi.h>
#include <ArduinoJson.h>

// Define WiFi credentials
const char *WIFI_SSID = "network_name";
const char *WIFI_PASSWORD = "network_password";

// Create instance of emonLib library
EnergyMonitor module_1;
EnergyMonitor module_2;
EnergyMonitor module_3;
EnergyMonitor module_4;
EnergyMonitor module_5;

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


// Connect to WiFi network and print ip address
void connect_to_wifi(){
    Serial.println("Connecting to WiFi...");
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    // Wait for connection
    while (WiFi.status() != WL_CONNECTED) {
        Serial.println("Could not connect to WiFi. Retrying in 5 seconds...");
        delay(500);
        Serial.print(".");
    }
    // If connected, print ip address
    if(WiFi.status() == WL_CONNECTED){
        Serial.println("Connected to WiFi!");
        print_ip_address();
    }   
}

void setup(){
    // Initialize serial
    Serial.begin(115200);
    // Connect to WiFi
    connect_to_wifi();
    // Initialize EmonLib for all inputs
    //--------------------------//
    module_1.current(ADC_PIN_1);
    module_1.voltage(VCC_PIN_1);
    
    module_2.current(ADC_PIN_2);
    module_2.voltage(VCC_PIN_2);
    
    module_3.current(ADC_PIN_3);
    module_3.voltage(VCC_PIN_3);
    
    module_4.current(ADC_PIN_4);
    module_4.voltage(VCC_PIN_4);
    
    module_5.current(ADC_PIN_5);
    module_5.voltage(VCC_PIN_5);
    //--------------------------//
    
}