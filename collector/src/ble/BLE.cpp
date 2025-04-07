#include "NimBLEDevice.h"
#include "Config.h"
#include <DelayProgressBar.h>

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

    // delay(duration);
    delayProgressBar(duration, "Scan Progress", 64);

    int devices = pBLEScan->getResults().getCount();

    pBLEScan->clearResults();
    pBLEScan->stop();

    return devices;
}
