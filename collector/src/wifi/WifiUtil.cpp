#include "WifiUtil.h"
#include <WiFi.h>
#include <ESP32Ping.h>
#include <HTTPClient.h>

bool tryBlockUntilDisconnected(int maxAttempts)
{
    Serial.print("Disconnecting: ");

    int remainingAttempts = maxAttempts;
    while (WiFi.status() == WL_CONNECTED)
    {
        Serial.print(WiFi.status());
        Serial.print(" ");
        if (remainingAttempts == 0)
        {
            Serial.println();
            return false;
        }
        delay(1000);
        remainingAttempts--;
    }
    Serial.println();
    return true;
}

bool tryBlockUntilConnection(int maxAttempts)
{
    Serial.print("Connecting: ");

    int remainingAttempts = maxAttempts;
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(WiFi.status());
        Serial.print(" ");
        if (remainingAttempts == 0)
        {
            Serial.println();
            return false;
        }
        delay(1000);
        remainingAttempts--;
    }
    Serial.println();
    return true;
}

void printWifiInfo()
{
    Serial.println("Connected Properties: ");
    Serial.println(WiFi.localIP());
    Serial.println(WiFi.macAddress());
    Serial.println(WiFi.getHostname());
    Serial.println(WiFi.getTxPower());
    Serial.println(WiFi.RSSI());
}

// This function semi-permanently breaks the esp
// If you use it the flash need to be reset for some reason
void printWifiNetworks()
{
    int n = WiFi.scanNetworks();

    Serial.print("Available SSIDS: ");
    Serial.println(n);
    for (int i = 0; i < n; i++)
    {
        Serial.println(WiFi.SSID(i));
    }
}

bool testConnection(const char *domain)
{
    return Ping.ping(domain);
}

void collectHeaders(HTTPClient &http)
{
    const char *headerKeys[] = {
        "Accept",
        "Accept-Encoding",
        "Authorization",
        "Cache-Control",
        "Connection",
        "Content-Length",
        "Content-Type",
        "Cookie",
        "Expect",
        "From",
        "Host",
        "Max-Forwards",
        "Origin",
        "User-Agent",
        "Access-Control-Allow-Origin",
        "Age",
        "Allow",
        "Cache-Control",
        "Content-Encoding",
        "Date",
        "Server",
        "Set-Cookie",
        "Content-Security-Policy",
        "Refresh",
        "Status",
        "Location"};

    const size_t headerKeysCount = sizeof(headerKeys) / sizeof(headerKeys[0]);
    http.collectHeaders(headerKeys, headerKeysCount);
}

void printHeaders(HTTPClient &http, bool hideEmpty)
{

    Serial.print("======== Headers (");
    Serial.print(http.headers());
    Serial.println("): ========");

    for (int i = 0; i < http.headers(); i++)
    {
        if (http.header(i) == "")
        {
            continue;
        }

        Serial.print(http.headerName(i));
        Serial.print(": ");
        Serial.println(http.header(i));
    }

    Serial.println("========================");
}