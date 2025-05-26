#include "States.h"
#include <Arduino.h>
#include <PostData.h>
#include <Config.h>
#include <stateMachine/StateMachine.h>
#include "Error.h"
#include <ExponentialBackoff.h>

void statePosting(Context *ctx)
{
    Serial.println("Posting data...");
    CollectorErr status = postOccupancy(API_URL, DEVICE, TOKEN, ctx->devices);

    switch (status)
    {
    case NO_ERR:
        Serial.println("Data posted sucessfully");
        ctx->state = SCANNING;
        break;
    case POST_GUEST_LOGGED_OUT_ERROR:
    case POST_CONNECTION_ERROR:
        Serial.println("Connection error, reconnecting to wifi...");
        ctx->state = CONNECTING;
        break;
    case POST_302_ERROR:
    case POST_NON_200_ERROR:
    case POST_READ_TIMEOUT_ERROR:
        if (!tryBackoff(&(ctx->retryCount)))
        {
            ctx->state = TERMINATED;
        }
        break;
    case POST_EXCEPTION:
        Serial.println("Fatal error, terminating...");
        ctx->state = TERMINATED;
        break;
    }
}