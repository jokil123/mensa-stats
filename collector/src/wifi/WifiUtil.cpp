#include "WifiUtil.h"
#include <WiFi.h>
#include <ESP32Ping.h>
#include <HTTPClient.h>
#include <Error.h>

// throws DISCONNECT_MAX_RETRY_EXCEEDED
CollectorErr tryBlockUntilDisconnected(int maxAttempts)
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
            return CollectorErr::DISCONNECT_MAX_RETRY_EXCEEDED;
        }
        delay(1000);
        remainingAttempts--;
    }
    Serial.println();
    return CollectorErr::NO_ERR;
}

// throws CONNECT_MAX_RETRY_EXCEEDED
CollectorErr tryBlockUntilConnection(int maxAttempts)
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
            return CollectorErr::CONNECT_MAX_RETRY_EXCEEDED;
        }
        delay(1000);
        remainingAttempts--;
    }
    Serial.println();
    return CollectorErr::NO_ERR;
}

void printWifiInfo()
{
    Serial.println("Connection Properties: ");
    Serial.printf("- Local IP:    %s\n", WiFi.localIP().toString().c_str());
    Serial.printf("- Mac Address: %s\n", WiFi.macAddress().c_str());
    Serial.printf("- Hostname:    %s\n", WiFi.getHostname());
    Serial.printf("- TX Power:    %d\n", WiFi.getTxPower());
    Serial.printf("- RSSI:        %d\n", WiFi.RSSI());
}

// This function semi-permanently breaks the esp
// If you use it the flash need to be reset for some reason
void printWifiNetworks()
{
    int n = WiFi.scanNetworks();

    Serial.printf("Available SSIDS: %d\n", n);
    for (int i = 0; i < n; i++)
    {
        Serial.printf("- %s\n", WiFi.SSID(i));
    }
}

// throws PING_FAILED
CollectorErr testConnection(const char *domain)
{
    if (Ping.ping(domain))
    {
        return CollectorErr::NO_ERR;
    }
    else
    {
        return CollectorErr::PING_FAILED;
    }
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

    Serial.printf("======== Headers (%d) ========\n", http.headers());

    for (int i = 0; i < http.headers(); i++)
    {
        if (http.header(i) == "")
        {
            continue;
        }

        Serial.printf("%s: %s \n", http.headerName(i).c_str(), http.header(i).c_str());
    }

    Serial.println("========================");
}