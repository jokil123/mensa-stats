#include "States.h"
#include <Arduino.h>
#include <ble/BLE.h>

void stateScanning(Context *ctx)
{
    try
    {
        Serial.println("Scanning devices...");
        ctx->devices = countDevices(5 * 60 * 1000);
    }
    catch (const std::exception &e)
    {
        Serial.println(e.what());
        ctx->state = TERMINATED;
    }

    Serial.print(ctx->devices);
    Serial.println(" devices scanned successfully");
    ctx->state = POSTING;
}
