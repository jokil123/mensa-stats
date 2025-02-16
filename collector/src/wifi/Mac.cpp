
#include <Arduino.h>
#include <esp_wifi.h>
#include <Util.h>
#include <WiFi.h>

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

// void randomizeDeviceId()
// {
//     WiFi.setHostname(randomString(10));

//     uint8_t mac[6] = {(random(0, 255) << 1), random(0, 255), random(0, 255), random(0, 255), random(0, 255), random(0, 255)};

//     esp_err_t err = esp_wifi_set_mac(WIFI_IF_STA, mac);

//     if (err == ESP_OK)
//     {
//         Serial.println("Success changing Mac Address: ");
//         printMac(mac);
//     }
//     else
//     {
//         Serial.print("Error changing Mac Address: ");
//         Serial.println(err);
//     }
// }
