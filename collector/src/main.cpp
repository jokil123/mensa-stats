#include <WifiConnect.h>
#include <Arduino.h>
#include <PostData.h>
#include <BLE.h>

char *host = "https://panel.trigonstudios.com";
char *route = "/api/occupancy/mensa-academica-01";
char *apiUrl = strcat(host, route);

// Replace these with your network credentials
char *ssid = "Joshua's S21+";
char *password = "12345678";

void setup()
{
    Serial.begin(9600); // Start Serial Monitor
    connectToWifiSimple(ssid, password);
    initBLE();
}

void loop()
{
    int devices = countDevices(2);
    Serial.println("Found " + String(devices) + " devices");

    Serial.println("Posting to " + String(apiUrl));
    postOccupancy(apiUrl, devices);
}
