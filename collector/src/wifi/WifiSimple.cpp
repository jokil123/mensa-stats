#include "WifiConnect.h"
#include <Arduino.h>
#include <WiFi.h>

CollectorErr connectToWifiSimple(const char *ssid, const char *password)
{
    Serial.println("Connecting to Wi-Fi...");

    WiFi.begin(ssid, password); // Start Wi-Fi connection

    while (WiFi.status() != WL_CONNECTED)
    { // Wait until connected
        delay(1000);
        Serial.println("Connecting...");
    }

    Serial.println("Connected!");
    Serial.printf("IP Address: %s\n", WiFi.localIP().toString().c_str());

    return NO_ERR;
}