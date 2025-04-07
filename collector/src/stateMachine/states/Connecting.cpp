#include "States.h"
#include <Arduino.h>
#include <wifi/WifiConnect.h>

void stateConnecting(Context *ctx)
{
    ConnectToGuestError error;

    try
    {
        Serial.println("Connecting to wifi...");
        error = connectToGuest();
    }
    catch (const std::exception &e)
    {
        Serial.println(e.what());
        ctx->state = TERMINATED;
    }

    switch (error)
    {
    case NO_ERROR:
        Serial.println("Connected to wifi");
        ctx->state = SCANNING;
        break;
    default:
        Serial.println("Failed to Connect, Terminating...");
        ctx->state = TERMINATED;
        break;
    }
}