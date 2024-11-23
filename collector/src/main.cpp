#include <WifiConnect.h>
#include <Arduino.h>
#include <PostData.h>
#include <BLE.h>
#include <VarExpand.h>
#include <dotenv.h>

void setup()
{
    Serial.begin(9600); // Start Serial Monitor
    Serial.println(API_URL);
    Serial.println(DEVICE);
    Serial.println(TOKEN);
    Serial.println(WIFI_SSID);
    Serial.println(WIFI_SECRET);
    connectToWifiSimple(WIFI_SSID, WIFI_SECRET);
    initBLE();
}

void loop()
{
    int deviceCount = countDevices(5);
    Serial.println("Found " + String(deviceCount) + " devices");
    // API_URL)
    postOccupancy("http://173.212.249.144:36001", DEVICE, TOKEN, deviceCount);
}
