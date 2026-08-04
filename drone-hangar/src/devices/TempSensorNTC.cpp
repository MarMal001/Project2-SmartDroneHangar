#include "TempSensorNTC.h"
#include "Arduino.h"

constexpr float CONVERSION = 5.0 / 3.3; // Volt vcc / 3.3 volt
constexpr float MAX_DAC = 1023.0;
constexpr float KELVIN_CELSIUS_CONV = 273.15;
constexpr float C1 = 1.009249522e-03, C2 = 2.378405444e-04, C3 = 2.019202697e-07;
constexpr float R1 = 10000.0;
constexpr int SAMPLING_RATE = 5;

TempSensorNTC::TempSensorNTC(int p) : pin(p) {
} 
  
float TempSensorNTC::getTemperature() {
    float samples = 0;
    for (int i = 0; i < SAMPLING_RATE; i++) {
        samples += analogRead(pin);
        delay(10);
    }
    float average = samples * CONVERSION / SAMPLING_RATE;
    float logR2 = log(R1 * (MAX_DAC / average - 1.0));
    return 1.0 / (C1 + C2 * logR2 + C3 * logR2 * logR2 * logR2) - KELVIN_CELSIUS_CONV;
}