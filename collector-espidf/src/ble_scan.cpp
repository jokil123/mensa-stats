#include "esp_system.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include <stdio.h>

// #include "nimble/" // Main NimBLE header
#include <set> // For storing unique device addresses

static const char *TAG_BLE = "BLE"; // move this to some shared files

static std::set<std::string> found_advices_adresses;
// static xqueueWhatever queue;

class AdvertisedDeviceCallbacks : public NimBLEAdvertisedDeviceCallbacks
{
    // void onResult(NimBLEAdvertisedDevice *advertised)
};
