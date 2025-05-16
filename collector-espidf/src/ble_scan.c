#include "ble_scan.h"

#include "esp_system.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include <stdio.h>
#include <nimble/ble.h>
#include <host/ble_gap.h>
#include "msc_error.h"

static const char *TAG_BLE = "BLE"; // move this to some shared files

static char addr_str_buffer[18]; // XX:XX:XX:XX:XX:XX + null terminator

char *addr_to_str(const ble_addr_t *addr)
{
    snprintf(addr_str_buffer, sizeof(addr_str_buffer),
             "%02x:%02x:%02x:%02x:%02x:%02x",
             addr->val[5], addr->val[4], addr->val[3],
             addr->val[2], addr->val[1], addr->val[0]);
    return addr_str_buffer;
}

static int ble_gap_event_handler(struct ble_gap_event *event, void *arg)
{
    struct ble_hs_adv_fields fields;
    int rc;

    switch (event->type)
    {
    case BLE_GAP_EVENT_DISC:
        ESP_LOGI(TAG_BLE, "Device Discovered:");
        ESP_LOGI(TAG_BLE, "Address: %s", addr_to_buffer(&event->disc.addr));
        ESP_LOGI(TAG_BLE, "RSSI: %s", event->disc.rssi);
        ESP_LOGI(TAG_BLE, "Event type: %d (0:CONN_ADV, 1:CONN_DIR_ADV, 2:NONCONN_ADV, 3:SCAN_REQ, 4:SCAN_RSP, 5:CONN_ADV_EXT, 6:SCAN_RSP_EXT)", event->disc.event_type);

        rc = ble_hs_adv_parse_fields(&fields, event->disc.data, event->disc.length_data);
        if (rc == 0)
        {
            if (fields.name != NULL)
            {
                ESP_LOGI(TAG_BLE, "Name: %.*s", fields.name_len, fields.name);
            }
            if (fields.name_is_complete)
            {
                ESP_LOGI(TAG_BLE, "Name is complete");
            }
        }

        ESP_LOGI(TAG_BLE, "Adv Data (len %d):", event->disc.length_data);
        for (int i = 0; i < event->disc.length_data; i++)
        {
            printf("%02X", event->disc.data[i]);
        }
        printf("\n");
        return 0;
    case BLE_GAP_EVENT_DISC_COMPLETE:
        ESP_LOGI(TAG_BLE, "Scan complete; reason=%d", event->disc_complete.reason);
        return 0;
    default:
        ESP_LOGD(TAG_BLE, "Other GAP event: %d", event->type);
        return 0;
    }
}

static void ble_app_scan(void)
{
    struct ble_gap_disc_params disc_params;
    int rc;

    disc_params.filter_duplicates = 1;
    disc_params.passive = 1;

    disc_params.itvl = 0;
    disc_params.window = 0;
    disc_params.filter_policy = 0;
    disc_params.limited = 0;

    rc = ble_gap_disc(BLE_OWN_ADDR_PUBLIC, BLE_HS_FOREVER, &disc_params, ble_gap_event_handler, NULL);

    if (rc != 0)
    {
        ESP_LOGE(TAG_BLE, "Error initiating GAP discovery; rc=%d", rc);
    }
    else
    {
        ESP_LOGI(TAG_BLE, "Scanning started...");
    }
}

static void ble_app_on_sync(void)
{
    int rc;

    rc = ble_hs_util_ensure_addr();
}

static void nimble_host_config_init(void)
{
    /* Set host callbacks */
    ble_hs_cfg.reset_cb = on_stack_reset;
    ble_hs_cfg.sync_cb = on_stack_sync;
    ble_hs_cfg.store_status_cb = ble_store_util_status_rr;

    /* Store host configuration */
    ble_store_config_init();
}

static void ble_init()
{
    esp_err_t ret;
    int rc;

    /* NVS flash initialization */
    ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES ||
        ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
    {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    if (ret != ESP_OK)
    {
        ESP_LOGE(TAG, "failed to initialize nvs flash, error code: %d ", ret);
        return;
    }

    /* NimBLE host stack initialization */
    ret = nimble_port_init();
    if (ret != ESP_OK)
    {
        ESP_LOGE(TAG, "failed to initialize nimble stack, error code: %d ",
                 ret);
        return;
    }

    /* GAP service initialization */
    rc = gap_init();
    if (rc != 0)
    {
        ESP_LOGE(TAG, "failed to initialize GAP service, error code: %d", rc);
        return;
    }

    /* NimBLE host configuration initialization */
    nimble_host_config_init();
}