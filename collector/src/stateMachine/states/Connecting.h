#pragma once

void stateConnecting(Context *ctx)
{
    try
    {
        Serial.println("Connecting to wifi...");
        connectToGuest();
    }
    catch (const std::exception &e)
    {
        Serial.println(e.what());
        ctx->state = TERMINATED;
    }

    Serial.println("Connected to wifi");
    ctx->state = SCANNING;
}