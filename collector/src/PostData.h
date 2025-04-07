#pragma once
#include <HTTPClient.h>

enum PostError
{
    NO_ERROR,
    FATAL_ERROR,
    CONNECTION_ERROR,
    READ_TIMEOUT_ERROR,
    GUEST_LOGGED_OUT_ERROR
};

PostError postOccupancy(const char *api_url, const char *device, const char *token, int occupancy);
