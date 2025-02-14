#pragma once

#include <Arduino.h>

/// @brief Generates a progress bar that fills up over a specified duration.
/// @param duration title of the progress bar.
/// @param duration The duration of the progress bar (in milliseconds).
/// @param width The width of the progress bar (in characters).
#include "Util.h"
void delayProgressBar(int duration, const char *title, int width)
{
    width = max(width, strlen(title));
    int delayPerChar = duration / width;
    int delayPerCharRemainder = duration % width;

    int leftPadding = (width - strlen(title)) / 2;
    int rightPadding = width - strlen(title) - leftPadding;

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

    for (int i = 0; i < width; i++)
    {
        Serial.print("=");
        delay(delayPerChar);
    }
    delay(delayPerCharRemainder);
    Serial.println();
}