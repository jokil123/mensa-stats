#include <BLE.h>

#include <BLEDevice.h>
#include <BLEScan.h>
#include <Arduino.h>

// not efficient but I dont have enough mem to do init at the start
int countDevices(int duration)
{
    BLEDevice::init("");
    BLEScan *scan = BLEDevice::getScan();
    scan->setActiveScan(true);

    BLEScanResults foundDevices = scan->start(duration, false); // Scan for 5 seconds
    return foundDevices.getCount();
    BLEDevice::deinit(true);
}