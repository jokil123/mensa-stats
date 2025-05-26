#include "ExponentialBackoff.h"
#include "Config.h"
#include <Arduino.h>
#include "Config.h"

void exponentialBackoff(int retries)
{
    delay(pow(retries, BACKOFF_EXPONENT) * BACKOFF_FACTOR);
}

bool tryBackoff(int *retries)
{
    if (*retries > MAX_RETRIES)
    {
        return false;
        (*retries) = 0;
    }

    exponentialBackoff(*retries);
    (*retries)++;

    return true;
}