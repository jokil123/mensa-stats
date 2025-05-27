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

bool tryBackoff(int *retries)
{
    if (*retries > MAX_RETRIES)
    {
        Serial.println("Max retries exceeded");
        (*retries) = 0;
        return false;
    }

    exponentialBackoff(*retries);
    (*retries)++;

    return true;
}