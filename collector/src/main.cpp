#include <Arduino.h>
#include <Wifi.h>
#include <HTTPClient.h>
#include <esp_wifi.h>
#include "PostData.h"

#define WIFI_SSID "RWTH-guests"
#define LOGON_URL "https://access.wlan.rwth-aachen.de/login.php"

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

void connectGuest()
{
    Serial.println("Connecting to RWTH Guest Network");

    WiFi.disconnect();
    delay(1000);
    WiFi.mode(WIFI_STA);
    WiFi.begin();

    uint8_t mac[6] = {(random(0, 255) << 1), random(0, 255), random(0, 255), random(0, 255), random(0, 255), random(0, 255)};
    printMac(mac);

    esp_err_t err = esp_wifi_set_mac(WIFI_IF_STA, mac);

    if (err == ESP_OK)
    {
        Serial.println("Success changing Mac Address: ");
    }
    else
    {
        Serial.print("Error changing Mac Address: ");
        Serial.println(err);
    }

    WiFi.begin(WIFI_SSID);

    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(1000);
    }

    Serial.println("Connected Sucessfully");
    Serial.println(WiFi.localIP());

    readMacAddress();

    HTTPClient http;
    http.begin(LOGON_URL);

    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    int httpResponseCode = http.POST("dest=open");

    if (httpResponseCode > 0)
    {
        Serial.println(httpResponseCode); // Print return code
    }
    else
    {
        Serial.print("Error on sending POST: ");
        Serial.println(httpResponseCode);
    }

    http.end();
}

void setup()
{
    Serial.begin(115200);
    connectGuest();
    postOccupancy("http://173.212.249.144:36001", "test", "", 1);
}

void loop()
{
}
