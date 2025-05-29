#include "States.h"
#include <Arduino.h>
#include <ble/BLE.h>
#include "Config.h"

void stateScanning(Context *ctx)
{
    // the last scan is new enough, skip the scan and directly post it.
    // this might reduce down times if the post fails and then successfully reconnects.
    if (ctx->lastScanTime < SCAN_COUNT * SCAN_DURATION && ctx->devices != -1)
    {
        Serial.printf("Scan is new enough (%ds), skipping scan\n", ctx->lastScanTime / 1000);
        ctx->state = POSTING;
        return;
    }

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
    ctx->lastScanTime = millis();
    ctx->state = POSTING;
}
