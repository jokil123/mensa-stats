#include "States.h"
#include <Arduino.h>
#include <ble/BLE.h>

void stateInit(Context *ctx)
{
    try
    {
        Serial.println("Starting up...");
        Serial.println("Initializing BLE...");
        initBLE();
    }
    catch (const std::exception &e)
    {
        Serial.printf("An exception occurred initializing BLE (%s)\n", e.what());
        ctx->state = TERMINATED;
    }

    Serial.println("Initialization complete");
    ctx->state = CONNECTING;
}