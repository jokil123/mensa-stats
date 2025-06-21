#include "States.h"
#include <Arduino.h>
#include <Config.h>
#include <Restart.h>

// this state will eventually reboot the microcontroller
// it will wait for some time before rebooting in case the program is in an endless crash cycle
// if the program crashes directly after init it will wait but it immediately restarts
// it it has been running for some time
void stateTerminated(Context *ctx)
{
    long uptime = millis();
    Serial.printf("Execution terminated (current uptime: %ds)\n", uptime / 1000);
    Serial.printf("Waiting %ds until restart\n", (MIN_UPTIME - uptime) / 1000);
    Serial.printf("ut %d, mup %d, delta %d\n", uptime, MIN_UPTIME, MIN_UPTIME - uptime);

    while (uptime < MIN_UPTIME)
    {
        Serial.print(".");
        delay(10 * 1000);
        uptime = millis();
    }

    Serial.println("Restarting...");
    Restart();
}