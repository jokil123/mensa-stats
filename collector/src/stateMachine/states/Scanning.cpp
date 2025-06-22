#include "States.h"
#include <Arduino.h>
#include <ble/BLE.h>
#include "Config.h"

void stateScanning(Context *ctx)
{
    // the last scan is new enough, skip the scan and directly post it.
    // this might reduce down times if the post fails and then successfully reconnects.
    if (millis() - ctx->lastScanTime < SCAN_COUNT * SCAN_DURATION && !ctx->dataPosted)
    {
        Serial.printf("Scan is new enough & not posted (%ds / %ds), skipping scan\n", ctx->lastScanTime / 1000, SCAN_COUNT * SCAN_DURATION / 1000);
        ctx->state = POSTING;
        return;
    }
    else
    {
        Serial.printf("Scan out of date or already posted (last: %ds ago (max %ds), posted: %d)\n", (millis() - ctx->lastScanTime) / 1000, SCAN_COUNT * SCAN_DURATION / 1000, ctx->dataPosted);
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

    Serial.printf("%f devices scanned successfully\n", ctx->devices);
    ctx->lastScanTime = millis();
    ctx->dataPosted = false;
    ctx->state = POSTING;
}
