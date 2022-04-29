#include <EmonLib.h>
#include <WiFi.h>
// #include <ArduinoJson.h>

// Define struct to hold the data of each module
typedef struct{
    float voltage;
    float current;
    float real_power;
    float apparent_power;
    float power_factor;
    float vrms;
    float irms;
} module_data;

// Define WiFi credentials
const char *WIFI_SSID = "network_name";
const char *WIFI_PASSWORD = "network_password";

// Create instance of emonLib library
EnergyMonitor module_1;
EnergyMonitor module_2;
EnergyMonitor module_3;
EnergyMonitor module_4;
EnergyMonitor module_5;

// Define calibration values for modules
// TODO: Check if same calibration values work for all modules
// TODO: Set calibration values
const float adc_calibration = 0.0;
const float vcc_calibration = 0.0;
const float vcc_phase_shift = 0.0;

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
const int number_of_samples = 10;
short adc_readings[number_of_samples];
short vcc_readings[number_of_samples];
short measure_count = 0;

// Define measurement interval (milliseconds)
unsigned long measure_interval = 1000;

unsigned long last_measure_time = 0;

// Define module data variables
module_data module_1_data[number_of_samples];
module_data module_2_data[number_of_samples];
module_data module_3_data[number_of_samples];
module_data module_4_data[number_of_samples];
module_data module_5_data[number_of_samples];
// Define module data average variables
module_data module_1_data_avg;
module_data module_2_data_avg;
module_data module_3_data_avg;
module_data module_4_data_avg;
module_data module_5_data_avg;

void print_ip_address(){
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
}
void print_module_data(module_data module_data, int module_number){
    Serial.print("Module: ");
    Serial.println(module_number);
    Serial.print("Voltage: ");
    Serial.print(module_data.voltage);
    Serial.print("\tCurrent: ");
    Serial.print(module_data.current);
    Serial.print("\tReal Power: ");
    Serial.print(module_data.real_power);
    Serial.print("\tApparent Power: ");
    Serial.print(module_data.apparent_power);
    Serial.print("\tPower Factor: ");
    Serial.print(module_data.power_factor);
    Serial.print("\tVRMS: ");
    Serial.print(module_data.vrms);
    Serial.print("\tIRMS: ");
    Serial.println(module_data.irms);
}
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

// Get average of readings
float get_average(module_data module_data[], int number_of_samples, int reading_type){
    float average = 0;	// Initialize average
    switch(reading_type){
        case 1:
            for (int i = 0; i < number_of_samples; i++){
                average += module_data[i].voltage;
            }
            average /= number_of_samples;
            break;
        case 2:
            for (int i = 0; i < number_of_samples; i++){
                average += module_data[i].current;
            }
            average /= number_of_samples;
            break;
        case 3:
            for (int i = 0; i < number_of_samples; i++){
                average += module_data[i].real_power;
            }
            average /= number_of_samples;
            break;
        case 4:
            for (int i = 0; i < number_of_samples; i++){
                average += module_data[i].apparent_power;
            }
            average /= number_of_samples;
            break;
        case 5:
            for (int i = 0; i < number_of_samples; i++){
                average += module_data[i].power_factor;
            }
            average /= number_of_samples;
            break;
        case 6:
            for (int i = 0; i < number_of_samples; i++){
                average += module_data[i].vrms;
            }
            average /= number_of_samples;
            break; 
        case 7:
            for (int i = 0; i < number_of_samples; i++){
                average += module_data[i].irms;
            }
            average /= number_of_samples;   // Return average
            break;
        default:
            Serial.println("Error: Invalid reading type");
            break;
    }
    return average;
}

void setup(){
    // Initialize serial
    Serial.begin(115200);
    // Connect to WiFi
    connect_to_wifi();
    // Initialize EmonLib for all inputs
    //--------------------------//
    module_1.current(ADC_PIN_1, adc_calibration);
    module_1.voltage(VCC_PIN_1, vcc_calibration, vcc_phase_shift);
    
    module_2.current(ADC_PIN_2, adc_calibration);
    module_2.voltage(VCC_PIN_2, vcc_calibration, vcc_phase_shift);

    module_3.current(ADC_PIN_3, adc_calibration);
    module_3.voltage(VCC_PIN_3, vcc_calibration, vcc_phase_shift);

    module_4.current(ADC_PIN_4, adc_calibration);
    module_4.voltage(VCC_PIN_4, vcc_calibration, vcc_phase_shift);

    module_5.current(ADC_PIN_5, adc_calibration);
    module_5.voltage(VCC_PIN_5, vcc_calibration, vcc_phase_shift);
    //--------------------------//
}
void loop(){
    unsigned long current_time = millis();
    // Measure current and voltage, calculate power and print to serial
    for(measure_count = 0; measure_count < number_of_samples; measure_count++){
        //--------------------------//
        module_1_data[measure_count].real_power = module_1.realPower; // Calculate real power
        module_1_data[measure_count].apparent_power = module_1.apparentPower; // Calculate apparent power
        module_1_data[measure_count].power_factor = module_1.powerFactor; // Calculate power factor
        module_1_data[measure_count].vrms = module_1.Vrms; // Calculate voltage rms
        module_1_data[measure_count].irms = module_1.Irms; // Calculate current rms
        //--------------------------//
        module_2_data[measure_count].real_power = module_2.realPower; // Calculate real power
        module_2_data[measure_count].apparent_power = module_2.apparentPower; // Calculate apparent power
        module_2_data[measure_count].power_factor = module_2.powerFactor; // Calculate power factor
        module_2_data[measure_count].vrms = module_2.Vrms; // Calculate voltage rms
        module_2_data[measure_count].irms = module_2.Irms; // Calculate current rms
        //--------------------------//
        module_3_data[measure_count].real_power = module_3.realPower; // Calculate real power
        module_3_data[measure_count].apparent_power = module_3.apparentPower; // Calculate apparent power
        module_3_data[measure_count].power_factor = module_3.powerFactor; // Calculate power factor
        module_3_data[measure_count].vrms = module_3.Vrms; // Calculate voltage rms
        module_3_data[measure_count].irms = module_3.Irms; // Calculate current rms
        //--------------------------//
        module_4_data[measure_count].real_power = module_4.realPower; // Calculate real power
        module_4_data[measure_count].apparent_power = module_4.apparentPower; // Calculate apparent power
        module_4_data[measure_count].power_factor = module_4.powerFactor; // Calculate power factor
        module_4_data[measure_count].vrms = module_4.Vrms; // Calculate voltage rms
        module_4_data[measure_count].irms = module_4.Irms; // Calculate current rms
        //--------------------------//
        module_5_data[measure_count].real_power = module_5.realPower; // Calculate real power
        module_5_data[measure_count].apparent_power = module_5.apparentPower; // Calculate apparent power
        module_5_data[measure_count].power_factor = module_5.powerFactor; // Calculate power factor
        module_5_data[measure_count].vrms = module_5.Vrms; // Calculate voltage rms
        module_5_data[measure_count].irms = module_5.Irms; // Calculate current rms
        //--------------------------//
    }
    //--------------------------//
    // Get measurement average
    //--------------------------//
    module_1_data_avg.current = get_average(module_1_data, number_of_samples, 1);
    module_1_data_avg.voltage = get_average(module_1_data, number_of_samples, 2);
    module_1_data_avg.real_power = get_average(module_1_data, number_of_samples, 3);
    module_1_data_avg.apparent_power = get_average(module_1_data, number_of_samples, 4);
    module_1_data_avg.power_factor = get_average(module_1_data, number_of_samples, 5);
    module_1_data_avg.vrms = get_average(module_1_data, number_of_samples, 6);
    module_1_data_avg.irms = get_average(module_1_data, number_of_samples, 7);
    //--------------------------//
    module_2_data_avg.current = get_average(module_2_data, number_of_samples, 1);
    module_2_data_avg.voltage = get_average(module_2_data, number_of_samples, 2);
    module_2_data_avg.real_power = get_average(module_2_data, number_of_samples, 3);
    module_2_data_avg.apparent_power = get_average(module_2_data, number_of_samples, 4);
    module_2_data_avg.power_factor = get_average(module_2_data, number_of_samples, 5);
    module_2_data_avg.vrms = get_average(module_2_data, number_of_samples, 6);
    module_2_data_avg.irms = get_average(module_2_data, number_of_samples, 7);
    //--------------------------//
    module_3_data_avg.current = get_average(module_3_data, number_of_samples, 1);
    module_3_data_avg.voltage = get_average(module_3_data, number_of_samples, 2);
    module_3_data_avg.real_power = get_average(module_3_data, number_of_samples, 3);
    module_3_data_avg.apparent_power = get_average(module_3_data, number_of_samples, 4);
    module_3_data_avg.power_factor = get_average(module_3_data, number_of_samples, 5);
    module_3_data_avg.vrms = get_average(module_3_data, number_of_samples, 6);
    module_3_data_avg.irms = get_average(module_3_data, number_of_samples, 7);
    //--------------------------//
    module_4_data_avg.current = get_average(module_4_data, number_of_samples, 1);
    module_4_data_avg.voltage = get_average(module_4_data, number_of_samples, 2);
    module_4_data_avg.real_power = get_average(module_4_data, number_of_samples, 3);
    module_4_data_avg.apparent_power = get_average(module_4_data, number_of_samples, 4);
    module_4_data_avg.power_factor = get_average(module_4_data, number_of_samples, 5);
    module_4_data_avg.vrms = get_average(module_4_data, number_of_samples, 6);
    module_4_data_avg.irms = get_average(module_4_data, number_of_samples, 7);
    //--------------------------//
    module_5_data_avg.current = get_average(module_5_data, number_of_samples, 1);
    module_5_data_avg.voltage = get_average(module_5_data, number_of_samples, 2);
    module_5_data_avg.real_power = get_average(module_5_data, number_of_samples, 3);
    module_5_data_avg.apparent_power = get_average(module_5_data, number_of_samples, 4);
    module_5_data_avg.power_factor = get_average(module_5_data, number_of_samples, 5);
    module_5_data_avg.vrms = get_average(module_5_data, number_of_samples, 6);
    module_5_data_avg.irms = get_average(module_5_data, number_of_samples, 7);
    //--------------------------//
    // Print to serial
    //--------------------------//
    print_module_data(module_1_data_avg, 1);
    print_module_data(module_2_data_avg, 2);
    print_module_data(module_3_data_avg, 3);
    print_module_data(module_4_data_avg, 4);
    print_module_data(module_5_data_avg, 5);
    
    //--------------------------//
    // Measure time and wait for next measurement
    //--------------------------//
    while(millis() - current_time < measurement_interval)
    {
        // Do nothing
    }
    if(current_time - last_measure_time > measure_interval) last_measure_time = current_time;
    //--------------------------//
}