#pragma once

enum PostError
{
    NO_ERROR,
    FATAL_ERROR,
    CONNECTION_ERROR,
};

PostError postOccupancy(const char *api_url, const char *device, const char *token, int occupancy);