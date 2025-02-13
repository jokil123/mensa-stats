#pragma once

void connectToWifiEnterprise(char *ssid, char *username, char *password);
bool connectToWifiSimple(char *ssid, char *password);

void connectToGuest();