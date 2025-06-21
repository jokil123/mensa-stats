#include "States.h"
#include <Arduino.h>
#include <Config.h>
#include <Restart.h>

void stateWatchdog(Context *ctx)
{
    if (millis() > MAX_UPTIME)
    {
        Serial.printf("Device uptime more than MAX_TIME_SINCE_SUCCESS, restarting in 5 seconds...\n");
        delay(5000);
        Restart();
    }

    unsigned long timeSinceSucess = millis() - ctx->lastPostSucessTime;

    if (timeSinceSucess > MAX_TIME_SINCE_SUCCESS)
    {
        Serial.printf("Device has been failing for more than MAX_TIME_SINCE_SUCCESS, restartig in 5 seconds...\n");
        delay(5000);
        Restart();
    }

    Serial.println("Watchdog OK!");
}