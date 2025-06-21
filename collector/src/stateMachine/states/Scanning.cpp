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
        Serial.printf("Scanning %d times...\n", SCAN_COUNT);
        ctx->devices = countDevices(SCAN_DURATION, SCAN_COUNT);
    }
    catch (const std::exception &e)
    {
        Serial.printf("An exception occured while scanning (%s)\n", e.what());
        ctx->state = TERMINATED;
    }

    Serial.printf("%d devices scanned successfully\n", ctx->devices);
    ctx->lastScanTime = millis();
    ctx->state = POSTING;
}
