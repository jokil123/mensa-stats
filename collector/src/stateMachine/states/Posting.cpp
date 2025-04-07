#include "States.h"
#include <Arduino.h>
#include <PostData.h>
#include <Config.h>
#include <stateMachine/StateMachine.h>

void statePosting(Context *ctx)
{
    Serial.println("Posting data...");
    PostError status = postOccupancy(API_URL, DEVICE, TOKEN, ctx->devices);

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
    case READ_TIMEOUT_ERROR:
        Serial.println("Couldn't reach api, retrying in 10 seconds...");
        delay(10000);
        ctx->state = POSTING;
        break;
    case GUEST_LOGGED_OUT_ERROR:
        Serial.println("Trying to reconnect...");
        ctx->state = CONNECTING;
        break;
    }
}