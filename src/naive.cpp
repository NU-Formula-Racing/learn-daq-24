#include <Arduino.h>

// CONSTANTS
// These aren't real pins btw
#define AMBIENT_TEMP_PIN A0
#define COOLANT_TEMP_PIN 10
#define AMBIENT_R2 10000

#define AMBIENT_A 0.01f
#define AMBIENT_B 0.02f
#define AMBIENT_C 0.03f

#define COOLANT_A 0.01f
#define COOLANT_B 0.015f
#define COOLANT_C 0.03f
#define COOLANT_R2 10000

void setup()
{
    // Setup the pins
    pinMode(AMBIENT_TEMP_PIN, INPUT);
    pinMode(COOLANT_TEMP_PIN, INPUT);
}

void loop()
{
    // Ambient Temperature
    // Caclulate rth
    float ambientRawADC = analogRead(AMBIENT_TEMP_PIN);
    float ambientVout = ambientRawADC * 3.3f / 4095.0f;
    float ambientRth = ((3.3f * AMBIENT_R2) / ambientVout) - AMBIENT_R2;

    // Caculate temeprature using Steinhart-Hart equations
    float ambientTemperature = (1 / 
        (AMBIENT_A +
        (AMBIENT_B * log(ambientRth) + 
        (AMBIENT_C * pow(log(ambientRth), 3)))));
    // Convert from K to C
    ambientTemperature -= 273.15;
    // Print
    Serial.printf("Ambient Temperature : %0.2f", ambientTemperature);

    // Coolant Temperature
    // Calculate rth for coolant
    // Can you find the mistake?
    float coolantRawADC = analogRead(COOLANT_TEMP_PIN);
    float coolantVout = coolantRawADC * 3.3f / 4095.0f;
    float coolantRth = ((3.3f * COOLANT_R2) / coolantVout) - COOLANT_R2;

    // Calculate temperature using Steinhart-Hart equations for coolant
    float coolantTemperature = (1 / 
        (COOLANT_A +
        (COOLANT_B * log(coolantRth) + 
        (COOLANT_C + pow(log(coolantRth), 3)))));
    // Convert from K to C for coolant
    coolantTemperature -= 273.15;

    // Print
    Serial.printf("Coolant Temperature : %0.2f C\n", coolantTemperature);
}