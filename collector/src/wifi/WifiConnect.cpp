#include <wifi/WifiConnect.h>
#include <wifi/Mac.h>
#include <Arduino.h>
#include <WiFi.h>
#include <esp_wpa2.h> // This is for WPA2 Enterprise connections
#include <esp_wifi.h>
#include <HTTPClient.h>
#include <Util.h>

#define WIFI_SSID "RWTH-guests"
#define LOGON_URL "https://access.wlan.rwth-aachen.de/login.php"

void connectToGuest()
{
    Serial.println("Connecting to RWTH Guest Network...");

    WiFi.disconnect();
    Serial.print("Disconnecting: ");
    while (WiFi.status() == WL_CONNECTED)
    {
        Serial.print(".");
        delay(1000);
    }
    Serial.println();

    // WiFi.config(INADDR_NONE, INADDR_NONE, INADDR_NONE, INADDR_NONE);
    // WiFi.setHostname(randomString(10));
    WiFi.setHostname(randomString(10));
    WiFi.mode(WIFI_STA);

    // WiFi.hostname("a");
    // WiFi.begin();
    WiFi.setAutoReconnect(false);

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

    WiFi.begin(WIFI_SSID);

    Serial.print("Waiting for connection: ");
    int remainingAttempts = 30;
    while (WiFi.status() != WL_CONNECTED)
    {
        if (remainingAttempts == 0)
        {
            Serial.println("Failed to connect to RWTH Guest Network");
            return;
        }

        Serial.print(WiFi.status());
        Serial.print(" ");
        remainingAttempts--;
        delay(1000);
    }
    Serial.println();

    Serial.println("Connected Sucessfully: ");
    Serial.println(WiFi.localIP());
    Serial.println(WiFi.getTxPower());
    Serial.println(WiFi.RSSI());
    Serial.println(WiFi.getHostname());

    Serial.println("Sending POST request to logon...");

    HTTPClient http;
    http.begin(LOGON_URL);

    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    http.addHeader("Connection", "keep-alive");
    http.addHeader("Content-Length", "10");
    int httpResponseCode = http.POST("dest=open");

    if (httpResponseCode != 200)
    {
        Serial.print("Error on sending POST: ");
        Serial.println(httpResponseCode);
    }
    else
    {
        Serial.println("Logon successful");
    }

    http.end();
}

bool connectToWifiSimple(const char *ssid, const char *password)
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

void connectToWifiEnterprise(const char *ssid, const char *username, const char *password)
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