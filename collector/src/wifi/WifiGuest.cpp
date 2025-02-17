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
    int httpResponseCode = http.POST("dest=open");

    if (httpResponseCode != 200)
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

void connectToGuest()
{
    Serial.println("Connecting to RWTH Guest Network...");

    // printStackUsage();
    randomizeDeviceId();
    // printHeapUsage();

    // Serial.println("Setting mode to WIFI_STA");
    WiFi.mode(WIFI_STA);
    // Serial.println("Setting auto reconnect to true");
    // WiFi.setAutoReconnect(true);
    // WiFi.enableLongRange(true);
    // Serial.println("Setting SSID");
    WiFi.begin(WIFI_SSID);

    Serial.println("Waiting for connection...");
    tryBlockUntilConnection();

    printWifiInfo();

    sendGuestLogin();
}