#include <Arduino.h>
// #include "stateMachine/StateMachine.h"

#include <WiFi.h>
#include <Util.h>
#include <esp_wifi.h>
#include "wifi/Mac.h"

#define hostnameBufferSize 10
char hostnameBuffer[hostnameBufferSize];

// randomizeDeviceID generates a random hostname and MAC address for the ESP32
void randomizeDeviceId()
{
    randomString(hostnameBuffer, hostnameBufferSize - 1);
    WiFi.setHostname(hostnameBuffer);

    WiFi.begin();

    uint8_t mac[6] = {(random(0, 255) << 1), random(0, 255), random(0, 255), random(0, 255), random(0, 255), random(0, 255)};

    esp_err_t err = esp_wifi_set_mac(WIFI_IF_STA, mac);

    if (err == ESP_OK)
    {
        Serial.println("Success changing Mac Address: ");
        printMac(mac);
    }
    else
    {
        Serial.print("Error changing Mac Address: ");
        Serial.println(err);
    }
}

void setup()
{
    Serial.begin(115200);
}

void loop()
{
    randomizeDeviceId();

    WiFi.mode(WIFI_STA);
    WiFi.begin("RWTH-guests");

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
        Serial.print(".");
    }

    Serial.println("Connected to RWTH Guest Network!");
    Serial.println(WiFi.macAddress());
    Serial.println(WiFi.localIP());
    Serial.println(WiFi.getHostname());

    delay(3000);

    WiFi.disconnect(true, true);
    Serial.println("Disconnected from RWTH Guest Network!");
    delay(1000);

    printHeapUsage();
}
