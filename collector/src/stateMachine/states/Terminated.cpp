#include "States.h"
#include <Arduino.h>
#include <Config.h>

// this state will eventually reboot the microcontroller
// it will wait for some time before rebooting in case the program is in an endless crash cycle
// if the program crashes directly after init it will wait but it immediately restarts
// it it has been running for some time
void stateTerminated(Context *ctx)
{
    unsigned long uptime = millis();

    while (uptime < MIN_UPTIME)
    {
        delay(10 * 1000);
    }

    ESP.restart();
}