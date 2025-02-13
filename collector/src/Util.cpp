#include <Util.h>
#include <HardwareSerial.h>
#include <Arduino.h>

void printHeapUsage()
{
    float percentage = (ESP.getFreeHeap() / (float)ESP.getHeapSize()) * 100;

    Serial.print("Free heap: ");
    Serial.print(ESP.getFreeHeap());
    Serial.print(" (");
    Serial.print(percentage);
    Serial.println("%)");
}