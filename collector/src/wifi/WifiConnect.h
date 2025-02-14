#pragma once

void connectToWifiEnterprise(const char *ssid, const char *username, const char *password);
bool connectToWifiSimple(const char *ssid, const char *password);

void connectToGuest();