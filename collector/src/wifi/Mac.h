#pragma once

#include <Arduino.h>

void readMacAddress();
void printMac(uint8_t mac[6]);

// Generates a random hostname and MAC address for the ESP32
// This will cut the connection to the current network and reinitialize the WiFi
CollectorErr randomizeDeviceId();