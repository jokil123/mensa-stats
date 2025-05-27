
#include "DelayProgressBar.h"

void progressBarSync(int duration, const char *title, int width)
{
    width = max(width, strlen(title));
    int delayPerChar = duration / width;
    int delayPerCharRemainder = duration % width;

    printProgressBarHeader(title, width);

    for (int i = 0; i < width; i++)
    {
        Serial.print("=");
        delay(delayPerChar);
    }
    delay(delayPerCharRemainder);
    Serial.println();
}

void printProgressBarHeader(const char *title, int width)
{
    width = max(width, strlen(title));

    int leftPadding = max(1, (width - strlen(title)) / 2);
    int rightPadding = max(1, width - strlen(title) - leftPadding);

    for (int i = 0; i < leftPadding; i++)
    {
        Serial.print("_");
    }
    Serial.print(title);
    for (int i = 0; i < rightPadding; i++)
    {
        Serial.print("_");
    }
    Serial.println();
}