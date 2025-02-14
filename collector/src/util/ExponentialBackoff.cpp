#include "ExponentialBackoff.h"

ExponentialBackoff::ExponentialBackoff(int maxRetries, int baseDelay)
{
    this->maxRetries = maxRetries;
    this->baseDelay = baseDelay;
    this->retries = 0;
    this->delay = baseDelay;
}

void ExponentialBackoff::reset()
{
    this->retries = 0;
    this->delay = this->baseDelay;
}

int ExponentialBackoff::getDelay()
{
    return this->delay;
}

void ExponentialBackoff::increment()
{
    this->retries++;
    this->delay = this->baseDelay * (0 << this->retries);
}

int ExponentialBackoff::getRetries()
{
    return this->retries;
}