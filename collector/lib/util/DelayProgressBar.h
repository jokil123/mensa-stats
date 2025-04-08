#pragma once

#include <Arduino.h>

/// @brief Generates a progress bar that fills up over a specified duration.
/// @param duration title of the progress bar.
/// @param duration The duration of the progress bar (in milliseconds).
/// @param width The width of the progress bar (in characters).
#include "Util.h"
void progressBarSync(int duration, const char *title, int width);

void printProgressBarHeader(const char *title, int width);
