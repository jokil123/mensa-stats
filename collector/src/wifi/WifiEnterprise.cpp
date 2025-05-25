#include "WifiConnect.h"
#include <Arduino.h>
#include <WiFi.h>
#include <esp_wpa2.h>

CollectorErr connectToWifiEnterprise(const char *ssid, const char *username, const char *password)
{
    WiFi.mode(WIFI_STA);

    // Configure WPA2 Enterprise settings
    esp_wifi_sta_wpa2_ent_set_identity((uint8_t *)username, strlen(username)); // Username
    esp_wifi_sta_wpa2_ent_set_username((uint8_t *)username, strlen(username)); // Username
    esp_wifi_sta_wpa2_ent_set_password((uint8_t *)password, strlen(password)); // Password

    // Optional: If a CA certificate is required
    // Replace `ca_cert` with your actual certificate content
    // const char *ca_cert = "-----BEGIN CERTIFICATE-----\n...\n-----END CERTIFICATE-----";
    // esp_wifi_sta_wpa2_ent_set_ca_cert((uint8_t *)ca_cert, strlen(ca_cert));

    // Initialize WPA2 Enterprise
    esp_wifi_sta_wpa2_ent_enable();

    // Connect to the Wi-Fi network
    WiFi.begin(ssid);

    Serial.println("Connecting to Wi-Fi...");

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
        Serial.print(".");
    }

    Serial.println("\nConnected to Wi-Fi!");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());

    return NO_ERR;
}