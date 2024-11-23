#include <WifiConnect.h>
#include <Arduino.h>
#include <PostData.h>
#include <BLE.h>
#include <VarExpand.h>

void setup()
{
    Serial.begin(9600); // Start Serial Monitor
    Serial.println(STR(API_URL));
    Serial.println(STR(DEVICE));
    Serial.println(STR(TOKEN));
    Serial.println(STR(WIFI_SSID));
    Serial.println(STR(WIFI_SECRET));
    connectToWifiSimple(STR(WIFI_SSID), STR(WIFI_SECRET));
    initBLE();
}

void loop()
{
    int deviceCount = countDevices(5);
    Serial.println("Found " + String(deviceCount) + " devices");
    // STR(API_URL)
    postOccupancy("http://173.212.249.144:36001", STR(DEVICE), STR(TOKEN), deviceCount);
}
