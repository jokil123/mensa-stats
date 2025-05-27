#include "States.h"
#include <Arduino.h>
#include <ble/BLE.h>
#include "Config.h"

void stateScanning(Context *ctx)
{
    try
    {
        Serial.print("Scanning ");
        Serial.print(SCAN_COUNT);
        Serial.println(" times...");
        ctx->devices = countDevices(SCAN_DURATION, SCAN_COUNT);
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
