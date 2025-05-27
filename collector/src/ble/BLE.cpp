#include "BLE.h"
#include "NimBLEDevice.h"
#include "Config.h"
#include <DelayProgressBar.h>

NimBLEScan *pBLEScan;

void initBLE()
{
    NimBLEDevice::init(DEVICE);
    pBLEScan = NimBLEDevice::getScan();
}

// duration per scan
float countDevices(int duration, int scanCount)
{
    pBLEScan->setActiveScan(true);
    pBLEScan->setDuplicateFilter(1);

    printProgressBarHeader("Scan Progress", scanCount);

    float acc = 0;
    for (int i = 0; i < scanCount; i++)
    {
        pBLEScan->start(duration, false, true);
        delay(duration);

        int devices = pBLEScan->getResults().getCount();
        acc += devices;

        pBLEScan->clearResults();
        pBLEScan->stop();
        Serial.print("=");
    }
    Serial.println("");

    Serial.println("Scans complete");

    return acc / (float)scanCount;
}
