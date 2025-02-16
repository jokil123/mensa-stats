#include "Util.h"
#include <HardwareSerial.h>
#include <Arduino.h>

float lower = 100;

void printHeapUsage()
{
    float percentage = (ESP.getFreeHeap() / (float)ESP.getHeapSize()) * 100;

    Serial.print("Free heap: ");
    Serial.print(ESP.getFreeHeap());

    Serial.print(" (");
    Serial.print(percentage);
    Serial.print("%)");

    lower = min(lower, percentage);
    Serial.print(" (min ");
    Serial.print(lower);
    Serial.print("%)");
    Serial.println();
}

float min(float a, float b)
{
    if (a < b)
    {
        return a;
    }
    else
    {
        return b;
    }
}

int min(int a, int b)
{
    if (a < b)
    {
        return a;
    }
    else
    {
        return b;
    }
}

int max(int a, int b)
{
    if (a > b)
    {
        return a;
    }
    else
    {
        return b;
    }
}

// This implmentation used to cause a memory leak
void randomString(char *buf, int length)
{
    for (int i = 0; i < length; i++)
    {
        buf[i] = random(0, 26) + 'a';
    }
    buf[length] = '\0';
}