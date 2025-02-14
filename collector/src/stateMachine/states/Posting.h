#pragma once

#include <Arduino.h>
#include <PostData.h>
#include <dotenv.h>
#include <stateMachine/StateMachine.h>

void statePosting(Context *ctx)
{
    Serial.println("Posting data...");
    PostError status = postOccupancy("https://mensa-stats.joshualung.com", DEVICE, TOKEN, ctx->devices);

    switch (status)
    {
    case NO_ERROR:
        Serial.println("Data posted sucessfully");
        ctx->state = SCANNING;
        break;
    case FATAL_ERROR:
        Serial.println("Fatal error, terminating...");
        ctx->state = TERMINATED;
        break;
    case CONNECTION_ERROR:
        Serial.println("Connection error, reconnecting to wifi...");
        ctx->state = CONNECTING;
        break;
    }
}