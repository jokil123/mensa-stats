#include "NimBLEDevice.h"
#include "dotenv.h"

NimBLEScan *pBLEScan;

void initBLE()
{
    NimBLEDevice::init(DEVICE);
    pBLEScan = NimBLEDevice::getScan();
}

int countDevices(int duration)
{
    pBLEScan->setActiveScan(true);
    pBLEScan->setDuplicateFilter(1);

    pBLEScan->start(duration, false, true);

    delay(duration);

    int devices = pBLEScan->getResults().getCount();

    pBLEScan->clearResults();
    pBLEScan->stop();

    return devices;
}

// #include <BLE.h>

// #include <BLEDevice.h>
// #include <BLEScan.h>
// #include <Arduino.h>

// BLEScan *scan;

// void initBLE()
// {
//     BLEDevice::init("");
//     scan = BLEDevice::getScan();
//     scan->setActiveScan(true);
// }

// // call init before use
// int countDevices(int duration)
// {
//     BLEScanResults foundDevices = scan->start(duration, false); // Scan for 5 seconds
//     return foundDevices.getCount();
// }