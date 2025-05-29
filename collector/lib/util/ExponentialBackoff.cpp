#include "ExponentialBackoff.h"
#include "Config.h"
#include <Arduino.h>
#include "Config.h"

void exponentialBackoff(int retries)
{
    int t = 0;

    if (retries != 0)
    {
        t = pow(BACKOFF_EXPONENT, retries - 1) * BACKOFF_FACTOR;
    }

    Serial.printf("Waiting %d millis (%d retries)\n", t, retries);
    delay(t);
}

int lastState = 0;
bool tryBackoff(int *retries, int state)
{
    // reset counter if state changes
    if (lastState != state)
    {
        (*retries) = 0;
        lastState = state;
    }

    // fail if the max tries have been exceeded
    if (*retries > MAX_RETRIES)
    {
        Serial.println("Max retries exceeded");
        (*retries) = 0;
        return false;
    }

    // wait backoff and wait
    exponentialBackoff(*retries);
    (*retries)++;

    return true;
}