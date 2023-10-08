#include <Arduino.h>
#include "thermistorSensor.hpp"

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


// Create objects
ThermistorSensor ambientTempSensor(AMBIENT_TEMP_PIN, AMBIENT_R2);
ThermistorSensor coolantTempSensor(COOLANT_TEMP_PIN, COOLANT_R2);

void setup()
{
    // Setup coefficents
    ambientTempSensor.SetSteinhartHartCoefficents(AMBIENT_A, AMBIENT_B, AMBIENT_C);
    coolantTempSensor.SetSteinhartHartCoefficents(COOLANT_A, COOLANT_B, COOLANT_C);
}

void loop()
{
    ambientTempSensor.Print();
    coolantTempSensor.Print();
}