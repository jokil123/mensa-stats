#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "Config.h"

#include "NimBLEDevice.h"
#include "NimBLEScan.h"
#include "NimBLEAdvertisedDevice.h"

#define TASK_DEFAULT_STACK_SIZE 2048

static const char *TAG_BLE = "BLE";
static const char *TAG_UPLOAD = "UPLOAD";
static const char *TAG_WIFI = "WIFI";
static const char *TAG_GENERAL = "COLLECTOR";

// does a wifi multiscan (for example 5x10s) and sends it down a queue
void bluetooth_scan_task(void *pvParameters)
{
    ESP_LOGI(TAG_BLE, "Started ble task");
}

// uploads the data when new data is available
// will wait for wifi connection
void data_upload_task(void *pvParameters)
{
}

// ensures wifi connection and continually monitors the connection
void wifi_connect_task(void *pvParameters)
{
}

// reboots the esp32 every 24 hours
void reboot_task(void *pvParameters)
{
}

void app_main()
{
    ESP_LOGI(TAG_GENERAL, "Starting mensa stats collector");

    xTaskCreate(bluetooth_scan_task, "bluetooth_scan_task", TASK_DEFAULT_STACK_SIZE, NULL, 6, NULL);
    xTaskCreate(data_upload_task, "data_upload_task", TASK_DEFAULT_STACK_SIZE, NULL, 6, NULL);
    xTaskCreate(wifi_connect_task, "wifi_connect_task", TASK_DEFAULT_STACK_SIZE, NULL, 6, NULL);
    xTaskCreate(reboot_task, "reboot_task", TASK_DEFAULT_STACK_SIZE, NULL, 6, NULL);

    ESP_LOGI(TAG_GENERAL, "Setup finished");
}