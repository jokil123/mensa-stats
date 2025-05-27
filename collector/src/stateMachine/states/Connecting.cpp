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
        Serial.println(e.what());
        ctx->state = TERMINATED;
    }

    switch (error)
    {
    case MAC_CHANGE_ERROR:
    case GUEST_LOGIN_POST_ERROR:
        Serial.print(errStr(error));
        Serial.println(": Terminating");
        ctx->state = TERMINATED;
        break;
    case CONNECT_MAX_RETRY_EXCEEDED:
    case PING_FAILED:
        Serial.println(errStr(error));
        if (!tryBackoff(&(ctx->retryCount)))
        {
            ctx->state = TERMINATED;
        }
        break;
    case NO_ERR:
        Serial.println("Connected to wifi");
        ctx->state = SCANNING;
        break;
    default:
        Serial.println("Unknown Error connecting to guest, terminating...");
        Serial.println(errStr(error));
        ctx->state = TERMINATED;
        break;
    }
}