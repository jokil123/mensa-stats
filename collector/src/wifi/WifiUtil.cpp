#include <WiFi.h>
bool tryBlockUntilDisconnected(int maxAttempts = 30)
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

bool tryBlockUntilConnection(int maxAttempts = 30)
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