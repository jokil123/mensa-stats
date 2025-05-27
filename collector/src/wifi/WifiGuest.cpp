#include "WifiConnect.h"
#include <WiFi.h>
#include <Util.h>
#include <esp_wifi.h>
#include "Mac.h"
#include <HTTPClient.h>
#include "WifiUtil.h"
#include "Error.h"
#include <Config.h>

#define WIFI_SSID "RWTH-guests"
#define LOGON_URL "https://access.wlan.rwth-aachen.de/login.php"

// throws GUEST_LOGIN_POST_ERROR
CollectorErr sendGuestLogin()
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
        return CollectorErr::GUEST_LOGIN_POST_ERROR;
    }

    Serial.println("Logon successful");
    http.end();
    return CollectorErr::NO_ERR;
}

// throws MAC_CHANGE_ERROR, CONNECT_MAX_RETRY_EXCEEDED, GUEST_LOGIN_POST_ERROR, PING_FAILED
CollectorErr connectToGuest()
{
    CollectorErr res;

    Serial.println("Connecting to RWTH Guest Network...");

    // printStackUsage();
    if (randomizeDeviceId() != NO_ERR)
    {
        Serial.println("Error changing mac address");
        return CollectorErr::MAC_CHANGE_ERROR;
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
    res = tryBlockUntilConnection(WIFI_MAX_RETRIES);
    if (res != NO_ERR)
    {
        return res;
    }

    printWifiInfo();

    res = sendGuestLogin();
    if (res != NO_ERR)
    {
        return res;
    }

    res = testConnection();
    if (res != NO_ERR)
    {
        return res;
    }

    return CollectorErr::NO_ERR;
}