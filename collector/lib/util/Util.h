#pragma once

#include <Arduino.h>

void printHeapUsage();
void printStackUsage();

float min(float a, float b);
int min(int a, int b);
int max(int a, int b);

void randomString(char *buf, size_t buf_size);

void printTimeSinceStart(bool nl = true);