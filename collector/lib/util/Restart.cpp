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
    Serial.printf("Restarting in 5 seconds...\n");
    delay(5000);
    digitalWrite(RESET_PIN, HIGH);
}