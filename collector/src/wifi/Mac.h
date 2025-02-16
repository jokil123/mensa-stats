#pragma once

#include <Arduino.h>

void readMacAddress();
void printMac(uint8_t mac[6]);

// randomizeDeviceID generates a random hostname and MAC address for the ESP32
// void randomizeDeviceId();