#include <Arduino.h>
#include "PostData.h"
#include "WifiConnect.h"
#include "dotenv.h"
#include "BLE.h"
#include "Util.h"

void setup()
{
    Serial.begin(115200);

    Serial.println("Connecting to wifi...");
    connectToGuest();
    Serial.println("Connected to wifi");

    initBLE();

    for (int i = 0; i < 10; i++)
    {
        Serial.println("Scaning devices...");
        int devices = countDevices(5 * 60 * 1000);
        Serial.print(devices);
        Serial.println(" devices scanned successfully");
        // printHeapUsage();

        Serial.println("Posting data...");
        int status = postOccupancy("https://mensa-stats.joshualung.com", DEVICE, TOKEN, devices);
        Serial.println("Data posted sucessfully");
        // printHeapUsage();
    }

    // printHeapUsage();
}

long backoff = 1000;

void loop()
{
    // connectToGuest();

    // while (true)
    // {
    //     int devices = countDevices(5 * 60);
    //     int status = postOccupancy("http://173.212.249.144:36001", DEVICE, TOKEN, devices);

    //     if (status == -1)
    //     {
    //         Serial.println("Error on sending POST");
    //         break;
    //     }
    //     else if (status == 200)
    //     {
    //         Serial.println("POST sent successfully");
    //         backoff = 1000;
    //     }
    //     else
    //     {
    //         Serial.println("Unknown error");
    //         break;
    //     }
    // }

    // delay(backoff);
    // backoff *= 2;
}
