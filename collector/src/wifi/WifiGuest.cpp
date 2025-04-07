#include "WifiConnect.h"
#include <WiFi.h>
#include <Util.h>
#include <esp_wifi.h>
#include "Mac.h"
#include <HTTPClient.h>
#include "WifiUtil.h"

#define WIFI_SSID "RWTH-guests"
#define LOGON_URL "https://access.wlan.rwth-aachen.de/login.php"

bool sendGuestLogin()
{
    Serial.println("Sending POST request to login...");

    HTTPClient http;
    http.begin(LOGON_URL);

    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    http.addHeader("Connection", "keep-alive");
    http.addHeader("Content-Length", "10");
    // collectHeaders(http);
    int httpResponseCode = http.POST("dest=open");
    // collectHeaders(http);

    if (httpResponseCode != 302)
    {
        Serial.print("Error on sending POST: ");
        Serial.println(httpResponseCode);
        http.end();
        return false;
    }

    Serial.println("Logon successful");
    http.end();
    return true;
}

ConnectToGuestError connectToGuest()
{
    Serial.println("Connecting to RWTH Guest Network...");

    // printStackUsage();
    if (!randomizeDeviceId())
    {
        return MAC_RANDOMIZE_ERROR;
    }

    // printHeapUsage();

    // Serial.println("Setting mode to WIFI_STA");
    WiFi.mode(WIFI_STA);
    // Serial.println("Setting auto reconnect to true");
    // WiFi.setAutoReconnect(true);
    // WiFi.enableLongRange(true);
    // Serial.println("Setting SSID");
    // printWifiNetworks();
    WiFi.begin(WIFI_SSID);

    Serial.println("Waiting for connection...");
    tryBlockUntilConnection();

    printWifiInfo();

    if (!sendGuestLogin())
    {
        return LOGIN_ERROR;
    }

    if (!testConnection())
    {
        return PING_FAILURE;
    }

    return NO_ERROR;
}