#pragma once

class ExponentialBackoff
{
private:
    int maxRetries;
    int baseDelay;
    int retries;
    int delay;

public:
    ExponentialBackoff(int maxRetries, int baseDelay);
    void reset();
    int getDelay();
    void increment();
    int getRetries();
};