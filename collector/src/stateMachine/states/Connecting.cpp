#include "States.h"
#include <Arduino.h>
#include <wifi/WifiConnect.h>
#include "Error.h"
#include <ExponentialBackoff.h>

void stateConnecting(Context *ctx)
{
    CollectorErr error;

    try
    {
        Serial.println("Connecting to wifi...");
        error = connectToGuest();
    }
    catch (const std::exception &e)
    {
        Serial.printf("An ecception occurred while connecting to guest: %s\n", e.what());
        ctx->state = TERMINATED;
    }

    switch (error)
    {
    case MAC_CHANGE_ERROR:
    case GUEST_LOGIN_POST_ERROR:
        Serial.printf("%s: Terminating\n", errStr(error));
        ctx->state = TERMINATED;
        break;
    case CONNECT_MAX_RETRY_EXCEEDED:
    case PING_FAILED:
        Serial.printf("%s: Trying backoff...\n", errStr(error));
        if (!tryBackoff(&(ctx->retryCount), ctx->state))
        {
            ctx->state = TERMINATED;
        }
        break;
    case NO_ERR:
        Serial.println("Connected to wifi");
        ctx->state = SCANNING;
        break;
    default:
        Serial.printf("Unknown Error connecting to guest (%s), terminating...\n", errStr(error));
        ctx->state = TERMINATED;
        break;
    }
}