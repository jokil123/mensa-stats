#pragma once
#include "Error.h"

CollectorErr connectToWifiEnterprise(const char *ssid, const char *username, const char *password);
CollectorErr connectToWifiSimple(const char *ssid, const char *password);

CollectorErr connectToGuest();