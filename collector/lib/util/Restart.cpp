#include <Restart.h>
#include <Esp.h>

void Restart()
{
    Serial.printf("Entering Deep Sleep...\n");
    // deepSleep should cause a full system restart (2s just in case)
    ESP.deepSleep(2 * 1000 * 1000);

    // if the reset didnt work, wait and then restart regularly
    Serial.printf("Deep Sleep did not reset execution, restarting regularly...\n");
    delay(500);
    ESP.restart();
}