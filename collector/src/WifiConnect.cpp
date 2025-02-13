#include <WifiConnect.h>
#include <Arduino.h>
#include <WiFi.h>
#include <esp_wpa2.h> // This is for WPA2 Enterprise connections
#include <esp_wifi.h>
#include <HTTPClient.h>

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

void connectToGuest()
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
    WiFi.setAutoReconnect(true);

    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(WiFi.status());
        Serial.print(" ");
        delay(1000);
    }
    Serial.println();

    Serial.println("Connected Sucessfully");
    Serial.println(WiFi.localIP());

    readMacAddress();

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

    http.end();
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