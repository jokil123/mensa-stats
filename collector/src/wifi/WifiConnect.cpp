#include <wifi/WifiConnect.h>
#include <wifi/Mac.h>
#include <Arduino.h>
#include <WiFi.h>
#include <esp_wpa2.h> // This is for WPA2 Enterprise connections
#include <esp_wifi.h>
#include <HTTPClient.h>
#include <util/Util.h>

#define WIFI_SSID "RWTH-guests"
#define LOGON_URL "https://access.wlan.rwth-aachen.de/login.php"

void connectToGuest()
{
    Serial.println("Connecting to RWTH Guest Network");
    WiFi.disconnect();
    delay(1000);

    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID); // Directly begin with SSID

    Serial.println("Connecting to RWTH Guest Network...");
    WiFi.setAutoReconnect(true);

    int reconnectAttempts = 0;
    while (WiFi.status() != WL_CONNECTED)
    {
        reconnectAttempts++;
        Serial.print("Reconnect Attempt: ");
        Serial.print(reconnectAttempts);
        Serial.print(", WiFi Status: ");
        Serial.println(WiFi.status());
        delay(1000);
        if (reconnectAttempts > 30)
        { // Timeout after 30 seconds (adjustable)
            Serial.println("Reconnection timed out. Exiting connectToGuest().");
            return; // Exit the function after timeout
        }
    }
    Serial.println();

    Serial.println("Connected Successfully");
    Serial.println(WiFi.localIP());

    Serial.println("Exiting connectToGuest() after successful connection.");
}

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

void connectToWifiEnterprise(char *ssid, char *username, char *password)
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
}