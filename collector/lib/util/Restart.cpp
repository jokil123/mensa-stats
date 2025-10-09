#include <Restart.h>
#include <Esp.h>
#include <Config.h>

void SetupResetPin()
{
    pinMode(RESET_PIN, OUTPUT);
    digitalWrite(RESET_PIN, LOW);
}

void Restart()
{
    Serial.printf("Restarting using reset pin in 5 seconds...\n");
    delay(5000);
    digitalWrite(RESET_PIN, HIGH);

    Serial.printf("Restart unsucessful, retrying using Deep Sleep...\n");
    // deepSleep should cause a full system restart (2s just in case)
    ESP.deepSleep(2 * 1000 * 1000);

    // if the reset didnt work, wait and then restart regularly
    Serial.printf("Deep Sleep did not reset execution, restarting regularly...\n");
    delay(500);
    ESP.restart();
}