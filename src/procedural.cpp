#include <Arduino.h>

// CONSTANTS
#define AMBIENT_TEMP_PIN A0
#define COOLANT_TEMP_PIN 10
#define AMBIENT_R2 10000
#define COOLANT_R2 10000

#define AMBIENT_A 0.01f
#define AMBIENT_B 0.02f
#define AMBIENT_C 0.03f

#define COOLANT_A 0.01f
#define COOLANT_B 0.015f
#define COOLANT_C 0.03f

void setup()
{
    // Setup the pins
    pinMode(AMBIENT_TEMP_PIN, INPUT);
    pinMode(COOLANT_TEMP_PIN, INPUT);
}

float adcToRth(int pin, float R2) 
{
    float rawADC = analogRead(pin);
    float Vout = rawADC * 3.3f / 4095.0f;
    return ((3.3f * R2) / Vout) - R2;
}

float getTemperature(float A, float B, float C, float Rth) 
{
    // Calculate temperature using Steinhart-Hart equations
    float temperature = (1 / (A + (B * log(Rth) + (C * pow(log(Rth), 3)))));
    
    // Convert from K to C
    temperature -= 273.15;

    return temperature;
}

void loop()
{
    // Ambient
    float ambientRth = adcToRth(AMBIENT_TEMP_PIN, AMBIENT_R2);
    float ambientTemperature = getTemperature(AMBIENT_A, AMBIENT_B, AMBIENT_C, ambientRth);
    Serial.printf("Ambient Temperature : %0.2f C\n", ambientTemperature);

    // Coolant
    float coolantRth = adcToRth(COOLANT_TEMP_PIN, COOLANT_R2);
    float coolantTemperature = getTemperature(COOLANT_A, COOLANT_B, COOLANT_C, coolantRth);
    Serial.printf("Coolant Temperature : %0.2f C\n", coolantTemperature);
}
