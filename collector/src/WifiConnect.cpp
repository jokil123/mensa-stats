#include <WifiConnect.h>
#include <Arduino.h>
#include <WiFi.h>
#include <esp_wpa2.h> // This is for WPA2 Enterprise connections

bool connectToWifiSimple(char *ssid, char *password)
{
    Serial.println("Connecting to Wi-Fi...");

    WiFi.begin(ssid, password); // Start Wi-Fi connection

    while (WiFi.status() != WL_CONNECTED)
    { // Wait until connected
        delay(1000);
        Serial.println("Connecting...");
    }

    Serial.println("Connected!");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP()); // Print IP Address

    return true;
}