#pragma once

void connectToWifiEnterprise(const char *ssid, const char *username, const char *password);
bool connectToWifiSimple(const char *ssid, const char *password);

enum ConnectToGuestError
{
    NO_ERROR,
    MAC_RANDOMIZE_ERROR,
    MAX_RETRY_EXCEEDED,
    LOGIN_ERROR,
    PING_FAILURE,
};

ConnectToGuestError connectToGuest();