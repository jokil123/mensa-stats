
#include <Arduino.h>
#include <esp_wifi.h>
#include <Util.h>
#include <WiFi.h>
#include "WifiUtil.h"
#include "Error.h"
#include <Config.h>

#define HOSTNAME_BUFFER_SIZE 10

void readMacAddress()
{
    uint8_t baseMac[6];
    esp_err_t ret = esp_wifi_get_mac(WIFI_IF_STA, baseMac);
    if (ret == ESP_OK)
    {
        Serial.printf("%02x:%02x:%02x:%02x:%02x:%02x\n",
                      baseMac[0], baseMac[1], baseMac[2],
                      baseMac[3], baseMac[4], baseMac[5]);
    }
    else
    {
        Serial.println("Failed to read MAC address");
    }
}

void printMac(uint8_t mac[6])
{
    for (int i = 0; i < 6; i++)
    {
        Serial.print(mac[i], HEX);
        if (i < 5)
        {
            Serial.print(":");
        }
    }
    Serial.println();
}

// Generates a random hostname and MAC address for the ESP32
// This will cut the connection to the current network and reinitialize the WiFi
// throws DISCONNECT_MAX_RETRY_EXCEEDED, MAC_CHANGE_ERROR
CollectorErr randomizeDeviceId()
{
    WiFi.disconnect(true, true);
    CollectorErr res = tryBlockUntilDisconnected(WIFI_MAX_RETRIES);
    if (res != NO_ERR)
    {
        return res;
    }

    char hostnameBuffer[HOSTNAME_BUFFER_SIZE]; // This used to be defined as a top-level variable, but that caused a memory corruption issue
    randomString(hostnameBuffer, HOSTNAME_BUFFER_SIZE);
    WiFi.setHostname(hostnameBuffer);

    WiFi.begin();

    uint8_t mac[6] = {
        static_cast<uint8_t>(random(0, 255) << 1),
        static_cast<uint8_t>(random(0, 255)),
        static_cast<uint8_t>(random(0, 255)),
        static_cast<uint8_t>(random(0, 255)),
        static_cast<uint8_t>(random(0, 255)),
        static_cast<uint8_t>(random(0, 255))};

    esp_err_t err = esp_wifi_set_mac(WIFI_IF_STA, mac);

    if (err != ESP_OK)
    {
        Serial.print("Error changing Mac Address: ");
        Serial.println(err);
        return CollectorErr::MAC_CHANGE_ERROR;
    }

    return CollectorErr::NO_ERR;
}