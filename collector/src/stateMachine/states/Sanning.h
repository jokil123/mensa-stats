#pragma once

void stateScanning(Context *ctx)
{
    int devices = 0;

    try
    {
        Serial.println("Scanning devices...");
        devices = countDevices(10000);
    }
    catch (const std::exception &e)
    {
        Serial.println(e.what());
        ctx->state = TERMINATED;
    }

    ctx->devices = devices;

    Serial.print(ctx->devices);
    Serial.println(" devices scanned successfully");
    ctx->state = POSTING;
}