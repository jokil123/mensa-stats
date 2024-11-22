#include <BLE.h>

#include <BLEDevice.h>
#include <BLEScan.h>
#include <Arduino.h>

BLEScan *pBLEScan;

void initBLE()
{
    BLEDevice::init("");
    pBLEScan = BLEDevice::getScan();
    pBLEScan->setActiveScan(true); // Set active scanning for better results
}

int countDevices(int duration)
{
    BLEScanResults foundDevices = pBLEScan->start(duration, false); // Scan for 5 seconds
    return foundDevices.getCount();
}