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

void printStackUsage()
{
    uint32_t freeStack = uxTaskGetStackHighWaterMark(NULL);
    Serial.print("Free stack: ");
    Serial.println(freeStack);
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

void randomString(char *buf, size_t buf_size)
{
    if (buf == NULL || buf_size == 0)
    {
        return; // Handle invalid input, or perhaps return an error code in real embedded system
    }

    size_t i = 0;
    // Generate characters until buffer is almost full (leave space for null terminator)
    while (i < buf_size - 1)
    {
        // Generate a random number between 0 and 25 (inclusive)
        long randomNumber = random(0, 25);

        // Convert the random number to a lowercase letter 'a' to 'z'
        char randomChar = 'a' + (char)randomNumber;

        buf[i] = randomChar;
        i++;
    }

    // Null-terminate the string to make it a valid C string
    buf[i] = '\0';
}

void printTimeSinceStart(bool nl)
{
    unsigned long currentMillis = millis();

    unsigned long totalSeconds = currentMillis / 1000;
    int seconds = totalSeconds % 60;

    unsigned long totalMinutes = totalSeconds / 60;
    int minutes = totalMinutes % 60;

    unsigned long hours = totalMinutes / 60;

    if (hours < 10)
    {
        Serial.print("0");
    }
    Serial.print(hours);
    Serial.print(":");

    if (minutes < 10)
    {
        Serial.print("0");
    }
    Serial.print(minutes);
    Serial.print(":");

    if (seconds < 10)
    {
        Serial.print("0");
    }
    Serial.print(seconds);

    if (nl)
    {
        Serial.println("");
    }
    else
    {
        Serial.print(": ");
    }
}