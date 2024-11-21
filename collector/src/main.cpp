#include <BLEDevice.h>
#include <BLEScan.h>
#include <Arduino.h>

BLEScan *pBLEScan;

void setup()
{
    Serial.begin(9600);

    BLEDevice::init("");
    pBLEScan = BLEDevice::getScan();
    pBLEScan->setActiveScan(true); // Set active scanning for better results
}

void loop()
{
    Serial.println("Scanning for BLE devices...");
    BLEScanResults foundDevices = pBLEScan->start(1, false); // Scan for 5 seconds

    Serial.printf("Found %d devices\n", foundDevices.getCount());

    // for (int i = 0; i < foundDevices.getCount(); i++)
    // {
    //     BLEAdvertisedDevice device = foundDevices.getDevice(i);
    //     Serial.print("Device Address: ");
    //     Serial.println(device.getAddress().toString().c_str());
    //     Serial.print("Device Name: ");
    //     Serial.println(device.getName().c_str());
    // }

    // delay(10000); // Wait 10 seconds before next scan
}
