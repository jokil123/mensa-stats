WL_NO_SHIELD = 255, // for compatibility with WiFi Shield library
WL_IDLE_STATUS = 0,
WL_NO_SSID_AVAIL = 1,
WL_SCAN_COMPLETED = 2,
WL_CONNECTED = 3,
WL_CONNECT_FAILED = 4,
WL_CONNECTION_LOST = 5,
WL_DISCONNECTED = 6

https://docs.espressif.com/projects/esp-idf/en/stable/esp32/api-reference/error-codes.html

-5 post error code sometimes
-11 read error (internet but no response from server)

# Resetting the flash:

`esptool.py --chip esp32 -p /dev/ttyUSB0 erase_flash`
