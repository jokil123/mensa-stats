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
    CollectorErr error = postOccupancy(API_URL, DEVICE, TOKEN, ctx->devices);

    switch (error)
    {
    case NO_ERR:
        Serial.println("Data posted sucessfully");
        ctx->lastPostSucessTime = millis();
        ctx->state = SCANNING;
        break;
    case POST_GUEST_LOGGED_OUT_ERROR:
    case POST_CONNECTION_ERROR:
    case POST_302_ERROR:
        Serial.printf("Connection error (%s), reconnecting to wifi...\n", errStr(error));
        ctx->state = CONNECTING;
        break;
    case POST_NON_200_ERROR:
    case POST_READ_TIMEOUT_ERROR:
        Serial.printf("%s: attempting backoff\n", errStr(error));
        if (!tryBackoff(&(ctx->retryCount), ctx->state))
        {
            ctx->state = TERMINATED;
        }
        break;
    case POST_EXCEPTION:
        Serial.printf("%s: Fatal error, terminating...\n", errStr(error));
        ctx->state = TERMINATED;
        break;
    }
}